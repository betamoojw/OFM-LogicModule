#include "LogicFunction.h"
#include "KnxHelper.h"
#include "OpenKNX.h"
#include "knx.h"
#include "knxprod.h"
#include "tinyexpr.h"

// native functions, implemented as a simple example how to use user functions
LogicValue LogicFunction::nativeAdd(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld)
{
    return E1 + E2;
}

LogicValue LogicFunction::nativeSubtract(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld)
{
    return E1 - E2;
}

LogicValue LogicFunction::nativeMultiply(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld)
{
    return E1 * E2;
}

LogicValue LogicFunction::nativeDivide(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld)
{
    return E1 / E2;
}

LogicValue LogicFunction::nativeAverage(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld)
{
    return (float)(E1 + E2) / 2;
}

LogicValue LogicFunction::nativeMinimum(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld)
{
    return (E1 < E2) ? E1 : E2;
}

LogicValue LogicFunction::nativeMaximum(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld)
{
    return (E1 > E2) ? E1 : E2;
}

LogicValue LogicFunction::nativeModulo(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld)
{
    return (int32_t)E1 % (int32_t)E2;
}

LogicValue LogicFunction::nativeAnd(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld)
{
    return (int32_t)E1 & (int32_t)E2;
}

LogicValue LogicFunction::nativeOr(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld)
{
    return (int32_t)E1 | (int32_t)E2;
}

LogicValue LogicFunction::nativeXor(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld)
{
    return (int32_t)E1 ^ (int32_t)E2;
}

LogicValue LogicFunction::nativeLShift(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld)
{
    return (int32_t)E1 << (int32_t)E2;
}

LogicValue LogicFunction::nativeRShift(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld)
{
    return (int32_t)E1 >> (int32_t)E2;
}

LogicValue LogicFunction::nativeBool2Int(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld)
{
    // we assume E1, E2 are boolean
    // if not, standard conversion applies
    return (uint8_t)((bool)E2 * 2 + (bool)E1);
}

LogicValue LogicFunction::nativeSmooth(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld)
{
    if (E1.isInitial() || E2.isInitial())
        return 0.0f;
    if ((bool)E2 == 0)
        return 0.0f;
    if (iOld.isInitial())
        return E1;
    else
        return iOld + (E1 - iOld) / E2;
}

LogicValue LogicFunction::nativeIncrementE1(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld)
{
    return E1 + LogicValue((uint8_t)1);
}

LogicValue LogicFunction::nativeIncrementE2(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld)
{
    return E2 + LogicValue((uint8_t)1);
}

LogicValue LogicFunction::nativeIncrementA(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld)
{
    return iOld + LogicValue((uint8_t)1);
}

LogicValue LogicFunction::nativeDecrementE1(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld)
{
    return E1 - LogicValue((uint8_t)1);
}

LogicValue LogicFunction::nativeDecrementE2(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld)
{
    return E2 - LogicValue((uint8_t)1);
}

LogicValue LogicFunction::nativeDecrementA(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld)
{
    return iOld - LogicValue((uint8_t)1);
}

LogicValue LogicFunction::nativeAddE1(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld)
{
    return iOld + E1;
}

LogicValue LogicFunction::nativeAddE2(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld)
{
    return iOld + E2;
}

LogicValue LogicFunction::nativeAddE1PlusE2(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld)
{
    return iOld + (E1 + E2);
}

LogicValue LogicFunction::nativeAddE1MinusE2(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld)
{
    return iOld + (E1 - E2);
}

LogicValue LogicFunction::nativeSubtractE1(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld)
{
    return iOld - E1;
}

LogicValue LogicFunction::nativeSubtractE2(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld)
{
    return iOld - E2;
}

LogicValue LogicFunction::nativeSubtractE1PlusE2(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld)
{
    return iOld - (E1 + E2);
}

LogicValue LogicFunction::nativeSubtractE1MinusE2(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld)
{
    return iOld - (E1 - E2);
}

LogicValue LogicFunction::nativeMinimumA(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld)
{
    if (E1 < E2 && E1 < iOld)
        return E1;
    else if (E2 < E1 && E2 < iOld)
        return E2;
    else
        return iOld;
}

LogicValue LogicFunction::nativeMaximumA(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld)
{
    if (E1 > E2 && E1 > iOld)
        return E1;
    else if (E2 > E1 && E2 > iOld)
        return E2;
    else
        return iOld;
}

LogicValue LogicFunction::nativeLShiftE1(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld)
{
    return (int32_t)E1 << 1;
}

LogicValue LogicFunction::nativeLShiftE2(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld)
{
    return (int32_t)E2 << 1;
}

LogicValue LogicFunction::nativeLShiftA(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld)
{
    return (int32_t)iOld << 1;
}

LogicValue LogicFunction::nativeRShiftE1(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld)
{
    return (int32_t)E1 >> 1;
}

LogicValue LogicFunction::nativeRShiftE2(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld)
{
    return (int32_t)E2 >> 1;
}

LogicValue LogicFunction::nativeRShiftA(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld)
{
    return (int32_t)iOld >> 1;
}

// do not touch after this point

LogicFunction::LogicFunction(){};

LogicFunction::~LogicFunction(){};

LogicValue (*LogicFunction::nativeFunction[NUM_NATIVE_FUNCTIONS])(uint8_t, uint8_t, LogicValue, uint8_t, LogicValue, uint8_t *, LogicValue){
    nativeAdd,
    nativeSubtract,
    nativeMultiply,
    nativeDivide,
    nativeAverage,
    nativeMinimum,
    nativeMaximum,
    nativeModulo,
    nativeAnd,
    nativeOr,
    nativeXor,
    nativeLShift,
    nativeRShift,
    nativeBool2Int,
    nativeSmooth,
    nativeIncrementE1,
    nativeIncrementE2,
    nativeIncrementA,
    nativeDecrementE1,
    nativeDecrementE2,
    nativeDecrementA,
    nativeAddE1,
    nativeAddE2,
    nativeAddE1PlusE2,
    nativeAddE1MinusE2,
    nativeSubtractE1,
    nativeSubtractE2,
    nativeSubtractE1PlusE2,
    nativeSubtractE1MinusE2,
    nativeMinimumA,
    nativeMaximumA,
    nativeLShiftE1,
    nativeLShiftE2,
    nativeLShiftA,
    nativeRShiftE1,
    nativeRShiftE2,
    nativeRShiftA};

LogicValue (*LogicFunction::userFunction[30])(uint8_t, uint8_t, LogicValue, uint8_t, LogicValue, uint8_t *, LogicValue){
    userFunction01,
    userFunction02,
    userFunction03,
    userFunction04,
    userFunction05,
    userFunction06,
    userFunction07,
    userFunction08,
    userFunction09,
    userFunction10,
    userFunction11,
    userFunction12,
    userFunction13,
    userFunction14,
    userFunction15,
    userFunction16,
    userFunction17,
    userFunction18,
    userFunction19,
    userFunction20,
    userFunction21,
    userFunction22,
    userFunction23,
    userFunction24,
    userFunction25,
    userFunction26,
    userFunction27,
    userFunction28,
    userFunction29,
    userFunction30};

// dispatcher
LogicValue LogicFunction::callFunction(uint8_t _channelIndex, uint8_t iId, uint8_t iDptE1, LogicValue iE1, uint8_t iDptE2, LogicValue iE2, uint8_t *cDptOut, LogicValue iOld)
{
    if (iId > 0 && iId <= NUM_NATIVE_FUNCTIONS)
    {
        LogicValue lResult = nativeFunction[iId - 1](_channelIndex, iDptE1, iE1, iDptE2, iE2, cDptOut, iOld);
        return lResult;
    }
    else if (iId > 200 && iId <= 230)
    {
        uint8_t lFormulaIndex = iId - 201;
        LogicValue lResult = (float)0.0;
        bool lFormulaActive = knx.paramByte(LOG_UserFormula1Active + lFormulaIndex * (LOG_UserFormula2Active - LOG_UserFormula1Active)) & LOG_UserFormula1ActiveMask;
        if (lFormulaActive)
            lResult = callUserFormula(_channelIndex, lFormulaIndex, iDptE1, iE1, iDptE2, iE2, cDptOut, iOld);
        else
            lResult = userFunction[iId - 201](_channelIndex, iDptE1, iE1, iDptE2, iE2, cDptOut, iOld);
        return lResult;
    }
    return (uint8_t)0;
}

double LogicFunction::myIf(double iCondition, double iTrue, double iFalse)
{
    return iCondition ? iTrue : iFalse;
}

uint8_t LogicFunction::toLower(const char *iSource, char *iTarget)
{
    uint8_t lCharIndex = 0;
    for (lCharIndex = 0; lCharIndex < 100 && iSource[lCharIndex] > 0; lCharIndex++)
    {
        char lChar = iSource[lCharIndex];
        if (lChar >= 65 && lChar <= 90) lChar += 32; // convert to lowercase
        iTarget[lCharIndex] = lChar;
    }
    iTarget[100] = 0; // ensure zero termination
    return lCharIndex;
}

LogicValue LogicFunction::callUserFormula(uint8_t _channelIndex, uint8_t iFormulaIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld)
{
    double lResult = 0;
    const char *lEtsFormula = (char *)knx.paramData(LOG_UserFormula1 + iFormulaIndex * (LOG_UserFormula2 - LOG_UserFormula1));
    logDebug(logPrefix, "Evaluating: %s", lEtsFormula);
    char lFormula[100] = {0};
    toLower(lEtsFormula, lFormula);

    // bind variables and functions to parser
    te_variable lVars[] = {
        {"e1", &e1},
        {"e2", &e2},
        {"a", &out},
        {"if", (double *)myIf, TE_FUNCTION3}};

    // parse formula
    int lError;
    te_expr *lParsedFormula = te_compile(lFormula, lVars, 4, &lError);

    if (lParsedFormula)
    {
        e1 = E1;
        e2 = E2;
        out = iOld;
        logDebug(logPrefix, "Values: e1=%f, e2=%f, a=%f", e1, e2, out);
        lResult = te_eval(lParsedFormula);
        logDebug(logPrefix, "Result: %f", lResult);
        te_free(lParsedFormula);
    }
    else
    {
        /* Show the user where the error is at. */
        const char lErrorChar = lEtsFormula[lError - 1];
        // lFormula[lError - 1] = 0;
        logDebug(logPrefix, "Error near '%c': %.*s -->%c<-- %s", lErrorChar, lError - 1, lEtsFormula, lErrorChar, lEtsFormula + lError);
    }

    return LogicValue((float)lResult);
}

void LogicFunction::handleFunctionPropertyCheckFormula(uint8_t *iData, uint8_t *eResultData, uint8_t &eResultLength)
{
    logInfo(logPrefix, "Function property: Check user formula");
    logIndentUp();

    uint8_t lFormulaIndex = iData[1] - 1;
    logDebug(logPrefix, "FormulaIndex: %d", lFormulaIndex);
    uint8_t lFormulaLength = iData[2];
    // const char *lEtsFormula = (char *)knx.paramData(LOG_UserFormula1 + lFormulaIndex * (LOG_UserFormula2 - LOG_UserFormula1));
    const char *lEtsFormula = (char *)iData + 3;
    logDebug(logPrefix, "Checking: %s", lEtsFormula);
    char lFormula[100] = {0};
    uint8_t lReceivedLen = toLower(lEtsFormula, lFormula);
    if (lReceivedLen == lFormulaLength)
    {
        // bind variables and functions to parser
        te_variable lVars[] = {
            {"e1", &e1},
            {"e2", &e2},
            {"a", &out},
            {"if", (double *)myIf, TE_FUNCTION3}};

        // parse formula
        int lError;
        te_expr *lParsedFormula = te_compile(lFormula, lVars, 4, &lError);
        if (lParsedFormula)
        {
            eResultData[0] = 0;
            te_free(lParsedFormula);
            logDebug(logPrefix, "Formula is OK!");
        }
        else
        {
            eResultData[0] = lError;
            logDebug(logPrefix, "Error near '%c' at position %d!", lEtsFormula[lError - 1], lError);
        }
    }
    else
    {
        eResultData[0] = -1;
        logDebug(logPrefix, "Received formula is too short - most probably an APDU problem. Got %i, should be %i", lReceivedLen, lFormulaLength);
    }
    eResultLength = 1;
    logIndentDown();
}
