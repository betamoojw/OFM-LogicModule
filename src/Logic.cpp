#include "Logic.h"
#include "LogicFunction.h"
#include "OpenKNX.h"
#include "PCA9632.h"
#include "Timer.h"
#include "TimerRestore.h"

#include "ModuleVersionCheck.h"

Logic openknxLogic;

uint8_t Logic::sMagicWord[] = {0xAE, 0x49, 0xD2, 0x9F};
Timer &Logic::sTimer = Timer::instance();                      // singleton
TimerRestore &Logic::sTimerRestore = TimerRestore::instance(); // singleton

uint16_t Logic::flashSize()
{
    // Version + Data (Channel * Inputs * (Dpt + Value))
    return 1 + (LOG_ChannelCount * 2 * 5);
}

const std::string Logic::name()
{
    return "Logic";
}

const std::string Logic::version()
{
    return MODULE_LogicModule_Version;
}

Logic::Logic()
{
    // init KoLookup (robustness)
    addKoLookup(0, 0, 0);
    mNumKoLookups = 0;
}

Logic::~Logic()
{
}

LogicChannel *Logic::getChannel(uint8_t iChannelId)
{
    return mChannel[iChannelId];
}

uint8_t Logic::getChannelId(LogicChannel *iChannel)
{
    uint8_t lResult = -1;
    for (uint8_t lIndex = 0; lIndex < mNumChannels; lIndex++)
    {
        if (mChannel[lIndex] == iChannel)
        {
            lResult = lIndex;
            break;
        }
    }
    return lResult;
}

void Logic::addKoLookup(uint16_t iKoNumber, uint8_t iChannelId, uint8_t iIOIndex)
{
    // first implementation, in future we use sorted insert
    mKoLookup[mNumKoLookups].koNumber = iKoNumber;
    mKoLookup[mNumKoLookups].channelIndex = iChannelId;
    mKoLookup[mNumKoLookups].ioIndex = iIOIndex;
    if (mNumKoLookups < cCountKoLookups)
        mNumKoLookups++;
}

bool Logic::getKoLookup(uint16_t iKoNumber, sKoLookup **iKoLookup)
{
    sKoLookup *lIterator = *iKoLookup;
    uint16_t lIterationCount = 0;
    if (*iKoLookup == 0)
        lIterator = &mKoLookup[0];
    else
        lIterator++;
    while (lIterator->koNumber > 0 && lIterationCount < mNumKoLookups)
    {
        lIterationCount++;
        if (lIterator->koNumber == iKoNumber)
        {
            *iKoLookup = lIterator;
            return true;
        }
        else
        {
            lIterator++;
        }
    }
    return false;
}

// REVIEW
// bool Logic::prepareChannels()
void Logic::prepareChannels()
{
    // bool lResult = false;
    logDebugP("prepareChannels");
    for (uint8_t lIndex = 0; lIndex < mNumChannels; lIndex++)
    {
        // Important: lResult has to be the last argument in this OR,
        // otherwise prepareChannel might be not called
        // lResult = mChannel[lIndex]->prepareChannel() || lResult;
        mChannel[lIndex]->prepareChannel();
    }
}

// we trigger all associated internal inputs with the new value
void Logic::processAllInternalInputs(LogicChannel *iChannel, bool iValue)
{
    // search for any internal input associated to this channel
    uint8_t lChannelId = getChannelId(iChannel);
    for (uint8_t lIndex = 0; lIndex < mNumChannels; lIndex++)
    {
        LogicChannel *lChannel = mChannel[lIndex];
        lChannel->processInternalInputs(lChannelId, iValue);
    }
}

void Logic::processAfterStartupDelay()
{
    logDebugP("afterStartupDelay");
    logIndentUp();

    if (ParamLOG_VacationRead)
        KoLOG_Vacation.requestObjectRead();

    prepareChannels();

    // TODO FIXME: Repeated Reading
    // TODO FIXME: Implementation for DPT19
    logIndentDown();
}

// REVIEW: Check if handling is equivalent to Commons v1 implementation
void Logic::processReadRequests()
{
    // TODO obsolete durch kompakteres firstLoop()
    // static bool sLogicProcessReadRequestsCalled = false;
    static uint32_t sDelay = 19000;

    /*
    // the following code should be called only once after initial startup delay
    if (!sLogicProcessReadRequestsCalled) {
        if (knx.paramByte(LOG_VacationRead) & LOG_VacationReadMask)
        {
            knx.getGroupObject(LOG_KoVacation).requestObjectRead();
        }
        // we put this here, because all other places are too early, knx stack is not up to date to send according init values
        // got from flash storage
        prepareChannels();
        sLogicProcessReadRequestsCalled = true;
    }
    */

    // date and time are red from bus every 30 seconds until a response is received
    if (ParamBASE_ReadTimeDate)
    {
        eTimeValid lValid = sTimer.isTimerValid();
        if (delayCheck(sDelay, 30000) && lValid != tmValid)
        {
            // logDebugP("Time Valid? %i", lValid);
            sDelay = millis();
            if (ParamBASE_CombinedTimeDate)
            {
                // combined date and time
                KoBASE_Time.requestObjectRead();
            }
            else
            {
                // date and time from separate KOs
                if (lValid != tmMinutesValid)
                    KoBASE_Time.requestObjectRead();
                if (lValid != tmDateValid)
                    KoBASE_Date.requestObjectRead();
            }
        }
        // if date and/or time is known, we read also summertime information
        if (sDelay > 0 && lValid == tmValid)
        {
            sDelay = 0;
            KoBASE_IsSummertime.requestObjectRead();
        }
    }
}

bool Logic::sendReadRequest(GroupObject &ko)
{
    // ensure, that we do not send too many read requests at the same time
    if (delayCheck(readRequestDelay, 300)) // 3 per second
    {
        // we handle input KO and we send only read requests, if KO is uninitialized
        if (!ko.initialized())
            ko.requestObjectRead();
        readRequestDelay = delayTimerInit();
        return true;
    }
    return false;
}

void Logic::readFlash(const uint8_t *iBuffer, const uint16_t iSize)
{
    if (iSize == 0) // first call - without data
        return;

    uint8_t lVersion = openknx.flash.readByte();
    if (lVersion != 1) // version unknown
    {
        logDebugP("Wrong version of flash data (%i)", lVersion);
        return;
    }

    uint8_t lMaxChannels = (iSize - 1) / (2 * 5);
    logDebugP("Reading channel data from flash (%i/%i)", lMaxChannels, mNumChannels);
    for (uint8_t lIndex = 0; lIndex < MIN(mNumChannels, lMaxChannels); lIndex++)
    {
        mChannel[lIndex]->restore();
    }
}

void Logic::writeFlash()
{
    openknx.flash.writeByte(1); // Version
    for (uint8_t lIndex = 0; lIndex < MIN(mNumChannels, LOG_ChannelCount); lIndex++)
    {
        mChannel[lIndex]->save();
    }
}

// on input level, all dpt > 1 values are converted to bool by the according converter
void Logic::processInputKo(GroupObject &iKo)
{
    // we have to check first, if external KO are used
    sKoLookup *lKoLookup = nullptr;
    while (getKoLookup(iKo.asap(), &lKoLookup))
    {
        LogicChannel *lChannel = mChannel[lKoLookup->channelIndex];
        lChannel->processInput(lKoLookup->ioIndex);
    }
    if (iKo.asap() == BASE_KoTime)
    {
        if (ParamBASE_CombinedTimeDate)
        {
            KNXValue value = "";

            // first ensure we have a valid data-time content
            // (including the correct length)
            if (iKo.tryValue(value, getDPT(VAL_DPT_19)))
            {

                // use raw value, as current version of knx do not provide access to all fields
                // TODO DPT19: check integration of extended DPT19 access into knx or OpenKNX-Commons
                // size is ensured to be 8 Byte
                uint8_t *raw = iKo.valueRef();

                /*
                const bool flagFault = raw[6] & 0x80;
                // ignore working day (WD, NWD): raw[6] & 0x40, raw[6] & 0x20
                const bool flagNoYear = raw[6] & 0x10;
                const bool flagNoDate = raw[6] & 0x08;
                // ignore NDOW: raw[6] & 0x04
                const bool flagNoTime = raw[6] & 0x02;
                const bool flagSuti = raw[6] & 0x01;
                // ignore quality of clock (CLQ): raw[7] & 0x80
                // ignore synchronisation source reliablity (SRC): raw[7] & 0x40
                */

                // ignore inputs with:
                // * F - fault
                // * NY - missing year
                // * ND - missing date
                // * NT - missing time
                if (!(raw[6] & (DPT19_FAULT | DPT19_NO_YEAR | DPT19_NO_DATE | DPT19_NO_TIME)))
                {
                    struct tm lTmp = value;
                    sTimer.setDateTimeFromBus(&lTmp);
                    const bool lSummertime = raw[6] & DPT19_SUMMERTIME;
                    // TODO check using ParamLOG_SummertimeAll
                    if (((knx.paramByte(BASE_SummertimeAll) & BASE_SummertimeAllMask) >> BASE_SummertimeAllShift) == VAL_STIM_FROM_DPT19)
                        sTimer.IsSummertime(lSummertime);
                }
            }
        }
        else
        {
            KNXValue value = "";
            // ensure we have a valid time content
            if (iKo.tryValue(value, getDPT(VAL_DPT_10)))
            {
                struct tm lTmp = value;
                sTimer.setTimeFromBus(&lTmp);
            }
        }
    }
    else if (iKo.asap() == BASE_KoDate)
    {
        KNXValue value = "";
        // ensure we have a valid date content
        if (iKo.tryValue(value, getDPT(VAL_DPT_11)))
        {
            struct tm lTmp = value;
            sTimer.setDateFromBus(&lTmp);
        }
    }
    else if (iKo.asap() == BASE_KoIsSummertime)
    {
        sTimer.IsSummertime(iKo.value(getDPT(VAL_DPT_1)));
    }
#ifdef BUZZER_PIN
    else if (iKo.asap() == LOG_KoBuzzerLock)
    {
        // turn off buzzer in case of lock
        if (iKo.value(getDPT(VAL_DPT_1)))
            noTone(BUZZER_PIN);
    }
#endif
#ifdef I2C_RGBLED_DEVICE_ADDRESS
    else if (iKo.asap() == LOG_KoLedLock)
    {
        // turn off LED in case of lock
        if (iKo.value(getDPT(VAL_DPT_1)))
            PCA9632_SetColor(0, 0, 0);
    }
#endif
    // REVIEW: Wäre dieser Check nicht im LogicChannel besser aufgehoben?
    // Nein, denn dann müsste man alle channels durchgehen, um den richtigen zu finden
    // So wird nur der Kanal berechnet, der dann final prozessiert wird.
    else if (iKo.asap() >= LOG_KoOffset + LOG_KoKOfE1 && iKo.asap() < LOG_KoOffset + LOG_KoKOfE1 + mNumChannels * LOG_KoBlockSize)
    {
        uint16_t lKoNumber = iKo.asap() - LOG_KoOffset - LOG_KoKOfE1;
        uint8_t lChannelId = lKoNumber / LOG_KoBlockSize;
        uint8_t lIOIndex = lKoNumber % LOG_KoBlockSize + 1;
        LogicChannel *lChannel = mChannel[lChannelId];
        lChannel->processInput(lIOIndex);
    }
}

const char* Logic::helpCommands[Logic::helpCommandCount] = {"logic help", "logic time", "logic easter", "logic sun", "logic sun+DDMM", "logic lim", "logic lim res", "logic chNN", "logic chNN lim", "logic chNN res"};

void Logic::showHelp()
{
    if (!knx.configured())
        return;

    openknx.console.printHelpLine("logic time", "Print current time");
    openknx.console.printHelpLine("logic easter", "Print calculated easter Sunday date");
    openknx.console.printHelpLine("logic sun", "Print sunrise and sunset times");
    openknx.console.printHelpLine("logic sun+DDMM", "Print sunrise/sunset at elevation +/- degree/minute");

    openknx.console.printHelpLine("logic lim", "Show call limit counter max value and channel");
    openknx.console.printHelpLine("logic lim res", "Reset all call limit counter");
    openknx.console.printHelpLine("logic chNN", "List logic channel NN, i.e. logic ch05");
    openknx.console.printHelpLine("logic chNN lim", "Show if this cannel reached call limit");
    openknx.console.printHelpLine("logic chNN res", "Resets call limit counter for this channel");
}


bool Logic::processCommand(const std::string iCmd, bool iDebugKo)
{
    bool lResult = false;

    if (!knx.configured())
        return lResult;

    if (iCmd.substr(0, 6) != "logic " || iCmd.length() < 7)
        return lResult;

    if (iCmd.length() >= 10 && iCmd.substr(6, 2) == "ch")
    {
        // Command ch<nn>: Logic inputs and output of last execution
        // find channel and dispatch
        uint16_t lIndex = std::stoi(iCmd.substr(8, 2)) - 1;
        if (lIndex < ParamLOG_VisibleChannels)
        {
            lResult = mChannel[lIndex]->processCommand(iCmd, iDebugKo);
        }
    }
    else if (iCmd.length() >= 7 && iCmd.substr(6, 1) == "t") // time
    {
        // return internal time (might differ from external)
        uint8_t lHour = sTimer.getHour();
        uint8_t lMinute = sTimer.getMinute();
        uint8_t lSecond = sTimer.getSecond();
        uint8_t lDay = sTimer.getDay();
        uint8_t lMonth = sTimer.getMonth();
        uint16_t lYear = sTimer.getYear();
        // this if prevents stupid warnings
        if (lHour < 24 && lMinute < 60 && lSecond < 60 && lDay < 32 && lMonth < 13)
        {
            logInfoP("Module ISO-Time: %04d-%02d-%02d %02d:%02d:%02d", lYear, lMonth, lDay, lHour, lMinute, lSecond);
            if (iDebugKo)
            {
                openknx.console.writeDiagnoseKo("%02d:%02d:%02d %02d.%02d", lHour, lMinute, lSecond, lDay, lMonth);
            }
        }
        lResult = true;
    }
    else if (iCmd.length() >= 9 && iCmd.substr(6, 3) == "sun")
    {
        if (iCmd.length() == 14 && (iCmd.substr(9, 1) == "-" || iCmd.substr(9, 1) == "+"))
        {
            // return sunrise and sunset for a specific elevation teSDD,
            // where S=Sign(+,-) and DD ist elevation in degree
            double lDegree = std::stod(iCmd.substr(9, 3));
            uint8_t lMinute = std::stoi(iCmd.substr(12, 2));
            lDegree = (lDegree + lMinute / 60.0);
            sTime lSunrise;
            sTime lSunset;
            sTimer.getSunDegree(SUN_SUNRISE, lDegree, &lSunrise);
            sTimer.getSunDegree(SUN_SUNSET, lDegree, &lSunset);
            // this if prevents stupid warnings
            if (lSunrise.hour >= 0 && lSunrise.hour < 24 && lSunrise.minute >= 0 && lSunrise.minute < 60 && lSunset.hour >= 0 && lSunset.hour < 24 && lSunset.minute >= 0 && lSunset.minute < 60)
            {
                logInfoP("Sunrise: %02d:%02d Sunset: %02d:%02d", lSunrise.hour, lSunrise.minute, lSunset.hour, lSunset.minute);
                if (iDebugKo)
                {
                    openknx.console.writeDiagnoseKo("R%02d:%02d S%02d:%02d", lSunrise.hour, lSunrise.minute, lSunset.hour, lSunset.minute);
                }
                lResult = true;
            }
        }
        else if (iCmd.length() == 9)
        {
            // return sunrise and sunset
            sTime *lSunrise = sTimer.getSunInfo(SUN_SUNRISE);
            sTime *lSunset = sTimer.getSunInfo(SUN_SUNSET);
            // this if prevents stupid warnings
            if (lSunrise->hour >= 0 && lSunrise->hour < 24 && lSunrise->minute >= 0 && lSunrise->minute < 60 && lSunset->hour >= 0 && lSunset->hour < 24 && lSunset->minute >= 0 && lSunset->minute < 60)
            {
                logInfoP("Sunrise: %02d:%02d Sunset: %02d:%02d", lSunrise->hour, lSunrise->minute, lSunset->hour, lSunset->minute);
                if (iDebugKo)
                    openknx.console.writeDiagnoseKo("R%02d:%02d S%02d:%02d", lSunrise->hour, lSunrise->minute, lSunset->hour, lSunset->minute);
                lResult = true;
            }
        }
        else
        {
            logInfoP("Command format is logic sun[+-]DDMM");
            if (iDebugKo)
                openknx.console.writeDiagnoseKo("-> sun+-DDMM");
        }
    }
    else if (iCmd.length() >= 7 && iCmd.substr(6, 1) == "e") // easter
    {
        // calculate easter date
        logInfoP("Easter date: %02d.%02d", sTimer.getEaster()->day, sTimer.getEaster()->month);
        if (iDebugKo)
            openknx.console.writeDiagnoseKo("O%02d.%02d", sTimer.getEaster()->day, sTimer.getEaster()->month);
        lResult = true;
    }
    else if (iCmd.length() >= 7 && iCmd.length() <= 9 && iCmd.substr(6, 1) == "l") // limit
    {
        // display max call limit and according channel
        logInfoP("Call limit %02d on channel %02d", LogicChannel::pLoadCounterMax, LogicChannel::pLoadChannel + 1);
        if (iDebugKo)
            openknx.console.writeDiagnoseKo("LIM %02d, CH %02d", LogicChannel::pLoadCounterMax, LogicChannel::pLoadChannel + 1);
        lResult = true;
    }
    else if (iCmd.length() >= 7 && iCmd.substr(6, 5) == "lim r") // limit
    {
        initLoadCounter(true);
        logInfoP("All call counters were reset!");
        if (iDebugKo)
            openknx.console.writeDiagnoseKo("Reset all");
        lResult = true;
    }
    else if (iCmd.length() >= 7 && iCmd.substr(6, 1) == "h") // help
    {
        showHelp();
        if (iDebugKo)
        {
            openknx.console.writeDiagnoseKo("-> time");
            openknx.console.writeDiagnoseKo(""); // workaround, on mass output each 2nd line ist skipped
            openknx.console.writeDiagnoseKo("-> easter");
            openknx.console.writeDiagnoseKo("");
            openknx.console.writeDiagnoseKo("-> sun");
            openknx.console.writeDiagnoseKo("");
            openknx.console.writeDiagnoseKo("-> sun[+-]DDMM");
            openknx.console.writeDiagnoseKo("");
            openknx.console.writeDiagnoseKo("-> lim");
            openknx.console.writeDiagnoseKo("");
            openknx.console.writeDiagnoseKo("-> lim res");
            openknx.console.writeDiagnoseKo("");
            openknx.console.writeDiagnoseKo("-> chNN");
            openknx.console.writeDiagnoseKo("");
            openknx.console.writeDiagnoseKo("-> chNN lim");
            openknx.console.writeDiagnoseKo("");
            openknx.console.writeDiagnoseKo("-> chNN res");
        }
        lResult = true;
    }
    return lResult;
}

void Logic::initLoadCounter(bool iAll)
{
    LogicChannel::pLoadCounterMax = 0;
    LogicChannel::pLoadChannel = 0;
    uint8_t lChannel;
    for (lChannel = 0; lChannel < mNumChannels; lChannel++)
    {
        if (iAll)
        {
            mChannel[lChannel]->pLoadCounter = 0;
        }
        else if (mChannel[lChannel]->pLoadCounter >= LOAD_COUNTER_MAX)
        {
            LogicChannel::pLoadCounterMax = LOAD_COUNTER_MAX;
            LogicChannel::pLoadChannel = lChannel;
            break;
        }
    }
}

void Logic::debug()
{
    // // logInfoP("Aktuelle Zeit: %s", sTimer.getTimeAsc());
    // sTimer.debug();
#ifdef ARDUINO_ARCH_RP2040
    // logInfoP("Free Heap: %i", rp2040.getFreeHeap());
#endif
}

void Logic::setup()
{
    // check for hidden parameters
    logInfoP("Setting: Buzzer available: %d", ParamLOG_BuzzerInstalled);
    logInfoP("Setting: RGBLed available: %d", ParamLOG_LedInstalled);
    // setup channels, not possible in constructor, because knx is not configured there
    // get number of channels from knxprod
    mNumChannels = ParamLOG_VisibleChannels; // LOG_ChannelCount;
    for (uint8_t lIndex = 0; lIndex < mNumChannels; lIndex++)
    {
        mChannel[lIndex] = new LogicChannel(lIndex);
    }
    // setup buzzer
#ifdef BUZZER_PIN
    pinMode(BUZZER_PIN, OUTPUT);
#endif
    bool lTimezoneSign = ParamBASE_TimezoneSign;
    int8_t lTimezone = ParamBASE_TimezoneValue;
    lTimezone = lTimezone * (lTimezoneSign ? -1 : 1);
    bool lUseSummertime = (ParamBASE_SummertimeAll == VAL_STIM_FROM_INTERN);
    uint64_t lHolidayBitmask = holidaysToUInt64(knx.paramData(LOG_Neujahr), 5);
    sTimer.setup(ParamBASE_Longitude, ParamBASE_Latitude, ParamBASE_Timezone, lUseSummertime, lHolidayBitmask); // do not fetch just ParamLOG_Neujahr here, we need the whole bitfield
    // for TimerRestore we prepare all Timer channels
    for (uint8_t lIndex = 0; lIndex < mNumChannels; lIndex++)
    {
        LogicChannel *lChannel = mChannel[lIndex];
        lChannel->startTimerRestoreState();
    }
}

uint64_t Logic::holidaysToUInt64(uint8_t *iData, uint8_t iCount)
{
    uint64_t l = 0;
    uint8_t *p = (uint8_t *)&l;
    for (uint8_t i = 0; i < iCount; i++)
        p[7-i] = iData[i];
    return l;
}

void Logic::loop()
{
    if (!openknx.afterStartupDelay())
        return;
    uint32_t lLoopTime = millis();
    processReadRequests();
    sTimer.loop(); // clock and timer async methods
    // special case timer handling, we have to loop through all channels once
    if (sTimer.isTimerValid() && sTimer.minuteChanged())
    {
        for (uint8_t lChannelNr = 0; lChannelNr < mNumChannels; lChannelNr++)
        {
            LogicChannel *lChannel = mChannel[lChannelNr];
            lChannel->startTimerInput();
        }
        sendHoliday();
        sTimer.clearMinuteChanged();
    }

    // we loop on all channels and execute pipeline
    uint8_t lChannelsProcessed = 0;
    // for (uint8_t lIndex = 0; lIndex < mNumChannels; lIndex++)
    while (lChannelsProcessed < mNumChannels && openknx.freeLoopTime())
    {
        LogicChannel *lChannel = mChannel[mChannelIterator++];
        lChannel->loop();
        lChannelsProcessed++;
        // the following operations are done only once after iteration of all channels
        if (mChannelIterator >= mNumChannels)
        {
            mChannelIterator = 0;
            // here we do actions which happen after all channels are iterated
            processTimerRestore();
        }
    }
    if (lChannelsProcessed < mNumChannels)
        logTraceP("loop time reduced after %i channels", lChannelsProcessed);
    if (millis() - lLoopTime > 4)
        logTraceP("LoopTime: %i", millis() - lLoopTime);
}

// start timer implementation
void Logic::processTimerRestore()
{
    static uint32_t sTimerRestoreDelay = 1;
    // if (!knx.configured())
    //     return;

    if (sTimerRestoreDelay == 0)
        return;
    if (sTimer.isTimerValid() == tmValid && delayCheck(sTimerRestoreDelay, 500))
    {
        sTimerRestoreDelay = millis();
        if (sTimerRestoreDelay == 0)
            sTimerRestoreDelay = 1; // prevent set to 0 in case of timer overflow
        if (sTimerRestore.getDayIteration() < 365)
        {
            if (sTimerRestore.getDayIteration() == 0)
            {
                // initialize RestoreTimer
                sTimerRestore.setup(sTimer);
            }
            else
            {
                sTimerRestore.decreaseDay();
            }
            // loopSubmodules();
        }
        else
        {
            // stop timer restore processing in logic...
            sTimerRestoreDelay = 0;
            // ... and in each channel
            for (uint8_t lIndex = 0; lIndex < mNumChannels; lIndex++)
            {
                LogicChannel *lChannel = mChannel[lIndex];
                lChannel->stopTimerRestoreState();
            }
        }
    }
}

// send holiday information on bus
void Logic::sendHoliday()
{
    if (sTimer.holidayChanged())
    {
        // write the newly calculated holiday information into KO (can be read externally)

        KoLOG_Holiday1.valueNoSend(sTimer.holidayToday(), getDPT(VAL_DPT_5));
        KoLOG_Holiday2.valueNoSend(sTimer.holidayTomorrow(), getDPT(VAL_DPT_5));
        sTimer.clearHolidayChanged();
        if (ParamLOG_HolidaySend)
        {
            // and send it, if requested by application setting
            KoLOG_Holiday1.objectWritten();
            KoLOG_Holiday2.objectWritten();
        }
    }
}

tm &Logic::Now()
{
    return sTimer.mNow;
}

bool Logic::timeValid()
{
    return sTimer.isTimerValid();
}

bool Logic::processFunctionProperty(uint8_t objectIndex, uint8_t propertyId, uint8_t length, uint8_t *data, uint8_t *resultData, uint8_t &resultLength)
{
    if (!knx.configured() || objectIndex != 160 || propertyId != 4)
        return false;

    switch (data[0])
    {
        case 1:
            LogicFunction::handleFunctionPropertyCheckFormula(data, resultData, resultLength);
            return true;
        case 2:
            LogicFunction::handleFunctionPropertyTestFormula(data, resultData, resultLength);
            return true;
        default:
            return false;
    }
}
