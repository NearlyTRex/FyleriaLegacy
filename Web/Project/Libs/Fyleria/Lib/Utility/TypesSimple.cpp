// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#include "Utility/TypesSimple.h"

namespace Gecko
{

WString STDConvertStringToWideString(const String& sString)
{
    STDWStringConvert<STDUTF8AndUTF16Conversion<WByte>> converter;
    return converter.from_bytes(sString);
}

String STDConvertWideStringToString(const WString& sWideString)
{
    STDWStringConvert<STDUTF8AndUTF16Conversion<WByte>> converter;
    return converter.to_bytes(sWideString);
}

String STDGetGameTime(ULongLong uTime)
{
    const UInt uSecondMax = 60;
    const UInt uMinuteMax = 60;
    const UInt uHourMax = 12;
    ULongLong uLeftover = 0;
    ULongLong uDays = 0;
    ULong uHours = 0;
    ULong uMinutes = 0;
    ULong uSeconds = 0;

    // Calculate days and get leftover for hours
    uDays = static_cast<ULongLong>(uTime / (uSecondMax * uMinuteMax * uHourMax));
    uLeftover = static_cast<ULongLong>(uTime % (uSecondMax * uMinuteMax * uHourMax));

    // Calculate hours and get leftover for minutes
    uHours = static_cast<ULongLong>(uLeftover / (uSecondMax * uMinuteMax));
    uLeftover = static_cast<ULongLong>(uLeftover % (uSecondMax * uMinuteMax));

    // Calcualte minutes and get leftover for seconds
    uMinutes = static_cast<ULongLong>(uLeftover / uSecondMax);
    uLeftover = static_cast<ULongLong>(uLeftover % uSecondMax);

    // Use leftover for seconds
    uSeconds = uLeftover;

    // Return formatted string
    OutputStringStream ssOutput;
    ssOutput << uDays << ":";
    ssOutput << STDSetFill('0') << STDSetWidth(2) << uHours << ':';
    ssOutput << STDSetFill('0') << STDSetWidth(2) << uMinutes << ':';
    ssOutput << STDSetFill('0') << STDSetWidth(2) << uSeconds;
    return ssOutput.str();
}

};
