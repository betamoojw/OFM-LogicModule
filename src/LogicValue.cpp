#include "LogicValue.h"
#include "Logic.h"

#include <cstdlib>
#include <cstring>
#include <ctime>
#include <math.h>
#include <stdio.h>

void LogicValue::setType(ValueType iType)
{
    _type = iType;
    _isInitial = false;
}

LogicValue::LogicValue(bool value)
{
    _value.boolValue = value;
    setType(BoolType);
}

LogicValue::LogicValue(uint8_t value)
{
    _value.ucharValue = value;
    setType(UCharType);
}

LogicValue::LogicValue(uint16_t value)
{
    _value.ushortValue = value;
    setType(UShortType);
}

LogicValue::LogicValue(uint32_t value)
{
    _value.uintValue = value;
    setType(UIntType);
}

// LogicValue::LogicValue(uint64_t value)
// {
//     _value.ulongValue = value;
//     setType(ULongType);
// }

LogicValue::LogicValue(int8_t value)
{
    _value.charValue = value;
    setType(CharType);
}

LogicValue::LogicValue(int16_t value)
{
    _value.shortValue = value;
    setType(ShortType);
}

LogicValue::LogicValue(int32_t value)
{
    _value.intValue = value;
    setType(IntType);
}

// LogicValue::LogicValue(int64_t value)
// {
//     _value.longValue = value;
//     setType(LongType);
// }

LogicValue::LogicValue(double value)
{
    _value.doubleValue = value;
    setType(DoubleType);
}

LogicValue::LogicValue(float value)
{
    _value.floatValue = value;
    setType(FloatType);
}

LogicValue::LogicValue(const char* value)
{
    _value.stringValue = value;
    setType(StringType);
}

LogicValue::operator bool() const
{
    return boolValue();
}

LogicValue::operator uint8_t() const
{
    return ucharValue();
}

LogicValue::operator uint16_t() const
{
    return ushortValue();
}

LogicValue::operator uint32_t() const
{
    return uintValue();
}

// LogicValue::operator uint64_t() const
// {
//     return ulongValue();
// }

LogicValue::operator int8_t() const
{
    return charValue();
}

LogicValue::operator int16_t() const
{
    return shortValue();
}

LogicValue::operator int32_t() const
{
    return intValue();
}

// LogicValue::operator int64_t() const
// {
//     return longValue();
// }

LogicValue::operator double() const
{
    return doubleValue();
}

LogicValue::operator float() const
{
    return floatValue();
}

LogicValue::operator const char*() const
{
    return stringValue();
}

LogicValue& LogicValue::operator=(const bool value)
{
    _value.boolValue = value;
    setType(BoolType);
    return *this;
}

LogicValue& LogicValue::operator=(const uint8_t value)
{
    _value.ucharValue = value;
    setType(UCharType);
    return *this;
}

LogicValue& LogicValue::operator=(const uint16_t value)
{
    _value.ushortValue = value;
    setType(UShortType);
    return *this;
}

LogicValue& LogicValue::operator=(const uint32_t value)
{
    _value.uintValue = value;
    setType(UIntType);
    return *this;
}

// LogicValue& LogicValue::operator=(const uint64_t value)
// {
//     _value.ulongValue = value;
//     setType(ULongType);
//     return *this;
// }

LogicValue& LogicValue::operator=(const int8_t value)
{
    _value.charValue = value;
    setType(CharType);
    return *this;
}

LogicValue& LogicValue::operator=(const int16_t value)
{
    _value.shortValue = value;
    setType(ShortType);
    return *this;
}

LogicValue& LogicValue::operator=(const int32_t value)
{
    _value.intValue = value;
    setType(IntType);
    return *this;
}

// LogicValue& LogicValue::operator=(const int64_t value)
// {
//     _value.longValue = value;
//     setType(LongType);
//     return *this;
// }

LogicValue& LogicValue::operator=(const double value)
{
    _value.doubleValue = value;
    setType(DoubleType);
    return *this;
}

LogicValue& LogicValue::operator=(const float value)
{
    _value.floatValue = value;
    setType(FloatType);
    return *this;
}

LogicValue& LogicValue::operator=(const char* value)
{
    _value.stringValue = value;
    setType(StringType);
    return *this;
}

void LogicValue::setInternal(const uint32_t value)
{
    switch (_type)
    {
        case BoolType:
            _value.boolValue = (value != 0);
            break;
        case UCharType:
            _value.ucharValue = value;
            break;
        case UShortType:
            _value.ushortValue = value;
            break;
        case UIntType:
            _value.uintValue = value;
            break;
        // case ULongType:
        //     _value.ulongValue = value;
        //     break;
        case CharType:
            _value.charValue = value;
            break;
        case ShortType:
            _value.shortValue = value;
            break;
        case IntType:
            _value.intValue = value;
            break;
        // case LongType:
        //     _value.longValue = value;
        //     break;
        case DoubleType:
            _value.doubleValue = value;
            break;
        case FloatType:
            _value.floatValue = value;
            break;
    }
    _isInitial = false;
}

void LogicValue::setInternal(const int32_t value)
{
    switch (_type)
    {
        case BoolType:
            _value.boolValue = (value != 0);
            break;
        case UCharType:
            _value.ucharValue = value;
            break;
        case UShortType:
            _value.ushortValue = value;
            break;
        case UIntType:
            _value.uintValue = value;
            break;
        // case ULongType:
        //     _value.ulongValue = value;
        //     break;
        case CharType:
            _value.charValue = value;
            break;
        case ShortType:
            _value.shortValue = value;
            break;
        case IntType:
            _value.intValue = value;
            break;
        // case LongType:
        //     _value.longValue = value;
        //     break;
        case DoubleType:
            _value.doubleValue = value;
            break;
        case FloatType:
            _value.floatValue = value;
            break;
    }
    _isInitial = false;
}

void LogicValue::setInternal(const float value)
{
    switch (_type)
    {
        case BoolType:
            _value.boolValue = (value != 0);
            break;
        case UCharType:
            _value.ucharValue = value;
            break;
        case UShortType:
            _value.ushortValue = value;
            break;
        case UIntType:
            _value.uintValue = value;
            break;
        // case ULongType:
        //     _value.ulongValue = value;
        //     break;
        case CharType:
            _value.charValue = value;
            break;
        case ShortType:
            _value.shortValue = value;
            break;
        case IntType:
            _value.intValue = value;
            break;
        // case LongType:
        //     _value.longValue = value;
        //     break;
        case DoubleType:
            _value.doubleValue = value;
            break;
        case FloatType:
            _value.floatValue = value;
            break;
    }
    _isInitial = false;
}

void LogicValue::setInternal(const char* value)
{
    switch (_type)
    {
        case CharType:
            _value.stringValue = value;
            break;
    }
    _isInitial = false;
}

LogicValue& LogicValue::operator++()
{
    switch (_type)
    {
        case BoolType:
            _value.boolValue = !_value.boolValue;
            return *this;
        case UCharType:
        case UShortType:
        case UIntType:
            // case ULongType:
            setInternal(uintValue() + 1);
            return *this;
        case CharType:
        case ShortType:
        case IntType:
            // case LongType:
            setInternal(intValue() + 1);
            return *this;
        case FloatType:
            setInternal(floatValue() + 1);
            return *this;
        case DoubleType:
            setInternal(doubleValue() + 1);
            return *this;
    }
    return *this;
}

LogicValue& LogicValue::operator+=(const int32_t value)
{
    switch (_type)
    {
        case UCharType:
        case UShortType:
        case UIntType:
            // case ULongType:
            setInternal(uintValue() + value);
            return *this;
        case CharType:
        case ShortType:
        case IntType:
            // case LongType:
            setInternal(intValue() + value);
            return *this;
        case FloatType:
            setInternal(floatValue() + value);
            return *this;
        case DoubleType:
            setInternal(doubleValue() + value);
            return *this;
    }
    return *this;
}

LogicValue& LogicValue::operator+=(const float value)
{
    switch (_type)
    {
        case UCharType:
        case UShortType:
        case UIntType:
            // case ULongType:
            setInternal(uintValue() + value);
            return *this;
        case CharType:
        case ShortType:
        case IntType:
            // case LongType:
            setInternal(intValue() + value);
            return *this;
        case FloatType:
            setInternal(floatValue() + value);
            return *this;
        case DoubleType:
            setInternal(doubleValue() + value);
            return *this;
    }
    return *this;
}

LogicValue LogicValue::operator+(LogicValue const& value)
{
    if (_type == FloatType || value._type == FloatType)
    {
        LogicValue lValue = floatValue() + value.floatValue();
        return lValue;
    }
    else if (_type == DoubleType || value._type == DoubleType)
    {
        LogicValue lValue = doubleValue() + value.doubleValue();
        return lValue;
    }
    else
    {
        LogicValue lValue = intValue() + value.intValue();
        return lValue;
    }
}

LogicValue LogicValue::operator-(LogicValue const& value)
{
    if (_type == FloatType || value._type == FloatType)
    {
        LogicValue lValue = floatValue() - value.floatValue();
        return lValue;
    }
    else if (_type == DoubleType || value._type == DoubleType)
    {
        LogicValue lValue = doubleValue() - value.doubleValue();
        return lValue;
    }
    else
    {
        LogicValue lValue = intValue() - value.intValue();
        return lValue;
    }
}

LogicValue LogicValue::operator*(LogicValue const& value)
{
    if (_type == FloatType || value._type == FloatType)
    {
        LogicValue lValue = floatValue() * value.floatValue();
        return lValue;
    }
    else if (_type == DoubleType || value._type == DoubleType)
    {
        LogicValue lValue = doubleValue() * value.doubleValue();
        return lValue;
    }
    else
    {
        LogicValue lValue = intValue() * value.intValue();
        return lValue;
    }
}

LogicValue LogicValue::operator/(LogicValue const& value)
{
    if (_type == FloatType || value._type == FloatType)
    {
        LogicValue lValue = floatValue() / value.floatValue();
        return lValue;
    }
    else if (_type == DoubleType || value._type == DoubleType)
    {
        LogicValue lValue = doubleValue() / value.doubleValue();
        return lValue;
    }
    else
    {
        LogicValue lValue = intValue() / value.intValue();
        return lValue;
    }
}

LogicValue LogicValue::operator^(LogicValue const& value)
{
    if (_type == FloatType || value._type == FloatType)
    {
        LogicValue lValue = pow(floatValue(), value.floatValue());
        return lValue;
    }
    else if (_type == DoubleType || value._type == DoubleType)
    {
        LogicValue lValue = pow(doubleValue(), value.doubleValue());
        return lValue;
    }
    else
    {
        LogicValue lValue = intValue() ^ value.intValue();
        return lValue;
    }
}

LogicValue LogicValue::operator-(const int32_t value)
{
    LogicValue lValue = false;
    switch (_type)
    {
        case UCharType:
        case UShortType:
        case UIntType:
            // case ULongType:
            lValue._type = _type;
            lValue.setInternal(uintValue() - value);
            return lValue;
        case CharType:
        case ShortType:
        case IntType:
            // case LongType:
            lValue._type = _type;
            setInternal(intValue() - value);
            return lValue;
        case FloatType:
            lValue._type = _type;
            setInternal(floatValue() - value);
            return lValue;
        case DoubleType:
            lValue._type = _type;
            setInternal(doubleValue() - value);
            return lValue;
    }
    return lValue;
}

LogicValue LogicValue::operator-(const float value)
{
    LogicValue lValue = false;
    switch (_type)
    {
        case UCharType:
        case UShortType:
        case UIntType:
            // case ULongType:
            lValue._type = _type;
            lValue.setInternal(uintValue() - value);
            return lValue;
        case CharType:
        case ShortType:
        case IntType:
            // case LongType:
            lValue._type = _type;
            setInternal(intValue() - value);
            return lValue;
        case FloatType:
            lValue._type = _type;
            setInternal(floatValue() - value);
            return lValue;
        case DoubleType:
            lValue._type = _type;
            setInternal(doubleValue() - value);
            return lValue;
    }
    return lValue;
}

bool LogicValue::operator>(LogicValue const& value)
{
    if (_type == FloatType || value._type == FloatType)
        return (floatValue() > value.floatValue());
    else if (_type == DoubleType || value._type == DoubleType)
        return (doubleValue() > value.doubleValue());
    else if (_type == UIntType && value._type == UIntType)
        return (uintValue() > value.uintValue());
    else if (_type == UIntType)
        return ((int64_t)uintValue() > (int64_t)value.intValue());
    else if (value._type == UIntType)
        return ((int64_t)intValue() > (int64_t)value.uintValue());
    else
        return (intValue() > value.intValue());
}

bool LogicValue::operator<(LogicValue const& value)
{
    if (_type == FloatType || value._type == FloatType)
        return (floatValue() < value.floatValue());
    else if (_type == DoubleType || value._type == DoubleType)
        return (doubleValue() < value.doubleValue());
    else if (_type == UIntType && value._type == UIntType)
        return (uintValue() < value.uintValue());
    else if (_type == UIntType)
        return ((int64_t)uintValue() < (int64_t)value.intValue());
    else if (value._type == UIntType)
        return ((int64_t)intValue() < (int64_t)value.uintValue());
    else
        return (intValue() < value.intValue());
}

bool LogicValue::operator>=(LogicValue const& value)
{
    if (_type == FloatType || value._type == FloatType)
        return (floatValue() >= value.floatValue());
    else if (_type == DoubleType || value._type == DoubleType)
        return (doubleValue() >= value.doubleValue());
    else if (_type == UIntType && value._type == UIntType)
        return (uintValue() >= value.uintValue());
    else if (_type == UIntType)
        return ((int64_t)uintValue() >= (int64_t)value.intValue());
    else if (value._type == UIntType)
        return ((int64_t)intValue() >= (int64_t)value.uintValue());
    else
        return (intValue() >= value.intValue());
}

bool LogicValue::operator<=(LogicValue const& value)
{
    if (_type == FloatType || value._type == FloatType)
        return (floatValue() <= value.floatValue());
    else if (_type == DoubleType || value._type == DoubleType)
        return (doubleValue() <= value.doubleValue());
    else if (_type == UIntType && value._type == UIntType)
        return (uintValue() <= value.uintValue());
    else if (_type == UIntType)
        return ((int64_t)uintValue() <= (int64_t)value.intValue());
    else if (value._type == UIntType)
        return ((int64_t)intValue() <= (int64_t)value.uintValue());
    else
        return (intValue() <= value.intValue());
}

bool LogicValue::boolValue() const
{
    if (_isInitial)
        return false;
    switch (_type)
    {
        case BoolType:
            return _value.boolValue;
        case UCharType:
        case UShortType:
        case UIntType:
        // case ULongType:
        case CharType:
        case ShortType:
        case IntType:
            // case LongType:
            return intValue() != 0;
        case FloatType:
            return _value.floatValue != 0;
        case DoubleType:
            return _value.doubleValue != 0;
        case StringType:
            return strcmp(_value.stringValue, "true") == 0 || strcmp(_value.stringValue, "True") == 0 || intValue() != 0 || floatValue() != 0;
    }
    return 0;
}

uint8_t LogicValue::ucharValue() const
{
    if (_isInitial)
        return 0;
    switch (_type)
    {
        case UCharType:
            return _value.ucharValue;
        case BoolType:
        case UShortType:
        case UIntType:
            // case ULongType:
            return (uint8_t)uintValue();
        case CharType:
        case ShortType:
        case IntType:
        // case LongType:
        case DoubleType:
        case FloatType:
        case StringType:
            return (uint8_t)intValue();
    }
    return 0;
}

uint16_t LogicValue::ushortValue() const
{
    if (_isInitial)
        return 0;
    switch (_type)
    {
        case UShortType:
            return _value.ushortValue;
        case BoolType:
        case UCharType:
        case UIntType:
            // case ULongType:
            return (uint16_t)uintValue();
        case CharType:
        case ShortType:
        case IntType:
        // case LongType:
        case DoubleType:
        case FloatType:
        case StringType:
            return (uint16_t)intValue();
    }
    return 0;
}

uint32_t LogicValue::uintValue() const
{
    if (_isInitial)
        return 0;
    switch (_type)
    {
        case UIntType:
            return _value.uintValue;
        case BoolType:
            return _value.boolValue ? 1 : 0;
        case UCharType:
            return _value.ucharValue;
        case UShortType:
            return _value.ushortValue;
        // case ULongType:
        //     return (int32_t)ulongValue();
        case CharType:
            return _value.charValue;
        case ShortType:
            return _value.shortValue;
        case IntType:
            return _value.intValue;
        // case LongType:
        case DoubleType:
            return _value.doubleValue;
        case FloatType:
            return _value.floatValue;
        case StringType:
            return strtol(_value.stringValue, NULL, 0);
    }
    return 0;
}

// uint64_t LogicValue::ulongValue() const
// {
//     switch (_type)
//     {
//         case ULongType:
//             return _value.ulongValue;
//         case BoolType:
//             return _value.boolValue ? 1 : 0;
//         case UCharType:
//             return (uint64_t)_value.ucharValue;
//         case UShortType:
//             return (uint64_t)_value.ushortValue;
//         case UIntType:
//             return (uint64_t)_value.uintValue;
//         case CharType:
//             return (uint64_t)_value.charValue;
//         case ShortType:
//             return (uint64_t)_value.shortValue;
//         case IntType:
//             return (uint64_t)_value.intValue;
//         case LongType:
//             return (uint64_t)_value.longValue;
//         case DoubleType:
//             return (uint64_t)(_value.doubleValue + 0.5);
//         case StringType:
//             // return (uint64_t)strtoul(_value.stringValue, NULL, 0);
//             return 0;
//     }
//     return 0;
// }

int8_t LogicValue::charValue() const
{
    if (_isInitial)
        return 0;
    switch (_type)
    {
        case CharType:
            return _value.charValue;
        case BoolType:
        case UCharType:
        case UShortType:
        case UIntType:
            // case ULongType:
            return (int8_t)uintValue();
        case ShortType:
        case IntType:
        // case LongType:
        case DoubleType:
        case FloatType:
        case StringType:
            return (int8_t)intValue();
    }
    return 0;
}

int16_t LogicValue::shortValue() const
{
    if (_isInitial)
        return 0;
    switch (_type)
    {
        case ShortType:
            return _value.shortValue;
        case BoolType:
        case UCharType:
        case UShortType:
        case UIntType:
            // case ULongType:
            return (int16_t)uintValue();
        case CharType:
        case IntType:
        // case LongType:
        case DoubleType:
        case FloatType:
        case StringType:
            return (int16_t)intValue();
    }
    return 0;
}

int32_t LogicValue::intValue() const
{
    if (_isInitial)
        return 0;
    switch (_type)
    {
        case IntType:
            return _value.intValue;
        case BoolType:
            return _value.boolValue ? 1 : 0;
        case UCharType:
            return _value.ucharValue;
        case UShortType:
            return _value.ushortValue;
        case UIntType:
            return _value.uintValue;
        // case ULongType:
        //     return (int32_t)ulongValue();
        case CharType:
            return _value.charValue;
        case ShortType:
            return _value.shortValue;
        // case LongType:
        case DoubleType:
            return _value.doubleValue;
        case FloatType:
            return _value.floatValue;
        case StringType:
            return strtol(_value.stringValue, NULL, 0);
    }
    return 0;
}

// int64_t LogicValue::longValue() const
// {
//     switch (_type)
//     {
//         case LongType:
//             return _value.longValue;
//         case BoolType:
//             return _value.boolValue ? 1 : 0;
//         case UCharType:
//             return (int64_t)_value.ucharValue;
//         case UShortType:
//             return (int64_t)_value.ushortValue;
//         case UIntType:
//             return (int64_t)_value.uintValue;
//         case ULongType:
//             return (int64_t)_value.uintValue;
//         case CharType:
//             return (int64_t)_value.charValue;
//         case ShortType:
//             return (int64_t)_value.shortValue;
//         case IntType:
//             return (int64_t)_value.intValue;
//         case DoubleType:
//             return (int64_t)(_value.doubleValue);
//         case StringType:
//             // return strtol(_value.stringValue, NULL, 0);
//             return 0;
//     }
//     return 0;
// }

double LogicValue::doubleValue() const
{
    if (_isInitial)
        return 0;
    switch (_type)
    {
        case DoubleType:
            return _value.doubleValue;
        case BoolType:
            return _value.boolValue ? 1 : 0;
        case UCharType:
            return _value.ucharValue;
        case UShortType:
            return _value.ushortValue;
        case UIntType:
            return _value.uintValue;
        // case ULongType:
        //     return _value.uintValue;
        case CharType:
            return _value.charValue;
        case ShortType:
            return _value.shortValue;
        case IntType:
            return _value.intValue;
        // case LongType:
        //     return _value.longValue;
        case FloatType:
            return _value.floatValue;
        case StringType:
            return strtod(_value.stringValue, NULL);
            return 0;
    }
    return 0;
}

float LogicValue::floatValue() const
{
    if (_isInitial)
        return 0;
    switch (_type)
    {
        case FloatType:
            return _value.floatValue;
        case BoolType:
            return _value.boolValue ? 1 : 0;
        case UCharType:
            return _value.ucharValue;
        case UShortType:
            return _value.ushortValue;
        case UIntType:
            return _value.uintValue;
        // case ULongType:
        //     return _value.uintValue;
        case CharType:
            return _value.charValue;
        case ShortType:
            return _value.shortValue;
        case IntType:
            return _value.intValue;
        // case LongType:
        //     return _value.longValue;
        case DoubleType:
            return _value.doubleValue;
        case StringType:
            return strtof(_value.stringValue, NULL);
    }
    return 0;
}

const char* LogicValue::stringValue() const
{

    if (_isInitial)
        return 0;
    switch (_type)
    {
        // case DoubleType:
        case BoolType:
        case UCharType:
        case UShortType:
        // case ULongType:
        case UIntType:
            sprintf(openknxLogic.gBuffer, "%u", _value.uintValue);
            return openknxLogic.gBuffer;
        case CharType:
        case ShortType:
        // case LongType:
        case IntType:
            sprintf(openknxLogic.gBuffer, "%i", _value.intValue);
            return openknxLogic.gBuffer;
        case FloatType:
        case DoubleType:
            sprintf(openknxLogic.gBuffer, "%f", _value.doubleValue);
            return openknxLogic.gBuffer;
        case StringType:
            return _value.stringValue;
    }
    return 0;
}

bool LogicValue::isInitial()
{
    return _isInitial;
}
void LogicValue::isInitial(bool iValue)
{
    _isInitial = iValue;
}