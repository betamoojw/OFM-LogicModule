#pragma once

#include <inttypes.h>
// #include <KnxHelper.h>
#include "string"
#include "tinyexpr.h"
#include <LogicValue.h>

#define NUM_NATIVE_FUNCTIONS 38
#define NUM_RECURSION_DEPTH 30

class LogicFunction
{
  private:
    LogicFunction();
    ~LogicFunction();

    static double e1;
    static double e2;
    static double out;
    static char sFormulaBuffer[100];
    // bind variables and functions to parser
    static const uint8_t sVarsSize;
    static te_variable sVars[];
    static uint8_t sRecursionCounter;

    static LogicValue (*nativeFunction[NUM_NATIVE_FUNCTIONS])(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld);
    static LogicValue (*userFunction[30])(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld);

    static double myIf(double iCondition, double iTrue, double iFalse);
    static double myIf2(double iCondition1, double iTrue1, double iCondition2, double iTrue2, double iFalse);
    static double myIf3(double iCondition1, double iTrue1, double iCondition2, double iTrue2, double iCondition3, double iTrue3, double iFalse);
    static double myRound(double iValue, double iPrecision);
    static double myNan();
    static double myB1(double iE1, double iE2, double iOut);
    static double myB2(double iE1, double iE2, double iOut);
    static double myB3(double iE1, double iE2, double iOut);
    static double myB4(double iE1, double iE2, double iOut);
    static double myB5(double iE1, double iE2, double iOut);
    static double myB6(double iE1, double iE2, double iOut);
    static double myB7(double iE1, double iE2, double iOut);
    static double myB8(double iE1, double iE2, double iOut);
    static double myB9(double iE1, double iE2, double iOut);
    static double myB10(double iE1, double iE2, double iOut);
    static double myB11(double iE1, double iE2, double iOut);
    static double myB12(double iE1, double iE2, double iOut);
    static double myB13(double iE1, double iE2, double iOut);
    static double myB14(double iE1, double iE2, double iOut);
    static double myB15(double iE1, double iE2, double iOut);
    static double myB16(double iE1, double iE2, double iOut);
    static double myB17(double iE1, double iE2, double iOut);
    static double myB18(double iE1, double iE2, double iOut);
    static double myB19(double iE1, double iE2, double iOut);
    static double myB20(double iE1, double iE2, double iOut);
    static double myB21(double iE1, double iE2, double iOut);
    static double myB22(double iE1, double iE2, double iOut);
    static double myB23(double iE1, double iE2, double iOut);
    static double myB24(double iE1, double iE2, double iOut);
    static double myB25(double iE1, double iE2, double iOut);
    static double myB26(double iE1, double iE2, double iOut);
    static double myB27(double iE1, double iE2, double iOut);
    static double myB28(double iE1, double iE2, double iOut);
    static double myB29(double iE1, double iE2, double iOut);
    static double myB30(double iE1, double iE2, double iOut);

    static const std::string logPrefix(uint8_t iFormulaIndex);
    static uint8_t toLower(const char *iSource, char *iTarget);
    static LogicValue callUserFormula(uint8_t iFormulaIndex, double iE1, double iE2, double iOut);

    // implemented native functions, as an simple example
    static LogicValue nativeAdd(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld);
    static LogicValue nativeSubtract(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld);
    static LogicValue nativeMultiply(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld);
    static LogicValue nativeDivide(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld);
    static LogicValue nativeAverage(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld);
    static LogicValue nativeMinimum(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld);
    static LogicValue nativeMaximum(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld);
    static LogicValue nativeModulo(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld);
    static LogicValue nativeAnd(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld);
    static LogicValue nativeOr(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld);
    static LogicValue nativeXor(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld);
    static LogicValue nativeLShift(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld);
    static LogicValue nativeRShift(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld);
    static LogicValue nativeBool2Int(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld);
    static LogicValue nativeSmooth(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld);
    static LogicValue nativeIncrementE1(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld);
    static LogicValue nativeIncrementE2(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld);
    static LogicValue nativeIncrementA(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld);
    static LogicValue nativeDecrementE1(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld);
    static LogicValue nativeDecrementE2(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld);
    static LogicValue nativeDecrementA(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld);
    static LogicValue nativeAddE1(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld);
    static LogicValue nativeAddE2(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld);
    static LogicValue nativeAddE1PlusE2(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld);
    static LogicValue nativeAddE1MinusE2(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld);
    static LogicValue nativeSubtractE1(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld);
    static LogicValue nativeSubtractE2(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld);
    static LogicValue nativeSubtractE1PlusE2(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld);
    static LogicValue nativeSubtractE1MinusE2(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld);
    static LogicValue nativeMinimumA(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld);
    static LogicValue nativeMaximumA(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld);
    static LogicValue nativeLShiftE1(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld);
    static LogicValue nativeLShiftE2(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld);
    static LogicValue nativeLShiftA(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld);
    static LogicValue nativeRShiftE1(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld);
    static LogicValue nativeRShiftE2(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld);
    static LogicValue nativeRShiftA(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld);
    static LogicValue nativePower(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld);

    // user functions (empty, implemented by user)
    static LogicValue userFunction01(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld);
    static LogicValue userFunction02(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld);
    static LogicValue userFunction03(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld);
    static LogicValue userFunction04(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld);
    static LogicValue userFunction05(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld);
    static LogicValue userFunction06(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld);
    static LogicValue userFunction07(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld);
    static LogicValue userFunction08(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld);
    static LogicValue userFunction09(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld);
    static LogicValue userFunction10(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld);
    static LogicValue userFunction11(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld);
    static LogicValue userFunction12(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld);
    static LogicValue userFunction13(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld);
    static LogicValue userFunction14(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld);
    static LogicValue userFunction15(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld);
    static LogicValue userFunction16(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld);
    static LogicValue userFunction17(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld);
    static LogicValue userFunction18(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld);
    static LogicValue userFunction19(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld);
    static LogicValue userFunction20(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld);
    static LogicValue userFunction21(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld);
    static LogicValue userFunction22(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld);
    static LogicValue userFunction23(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld);
    static LogicValue userFunction24(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld);
    static LogicValue userFunction25(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld);
    static LogicValue userFunction26(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld);
    static LogicValue userFunction27(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld);
    static LogicValue userFunction28(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld);
    static LogicValue userFunction29(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld);
    static LogicValue userFunction30(uint8_t _channelIndex, uint8_t DptE1, LogicValue E1, uint8_t DptE2, LogicValue E2, uint8_t *DptOut, LogicValue iOld);

  public:
    static LogicValue callFunction(uint8_t _channelIndex, uint8_t iId, uint8_t iDptE1, LogicValue iE1, uint8_t iDptE2, LogicValue iE2, uint8_t *cDptOut, LogicValue iOld);
    static void processFunctionPropertyFormula(std::string iLogPrefix, bool iCalculate, uint8_t *iData, uint8_t *eResultData, uint8_t &eResultLength);
    static void handleFunctionPropertyCheckFormula(uint8_t *iData, uint8_t *eResultData, uint8_t &eResultLength);
    static void handleFunctionPropertyTestFormula(uint8_t *iData, uint8_t *eResultData, uint8_t &eResultLength);
};
