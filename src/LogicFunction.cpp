#include "LogicFunction.h"
#include "KnxHelper.h"
#include "knx.h"
#include "knxprod.h"
// #include "LogicValue.h"

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
        LogicValue lResult = userFunction[iId - 201](_channelIndex, iDptE1, iE1, iDptE2, iE2, cDptOut, iOld);
        return lResult;
    }
    return (uint8_t)0;
}
