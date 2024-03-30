// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

// Internal includes
#include "Utility/Converters.h"
#include "Utility/Boost.h"
#include "Utility/Errors.h"
#include "Utility/Uri.h"

namespace Gecko
{

WString ConvertStringToWideString(const String& sString)
{
    STDWStringConvert<STDUTF8AndUTF16Conversion<WByte>> converter;
    return converter.from_bytes(sString);
}

String ConvertWideStringToString(const WString& sWideString)
{
    STDWStringConvert<STDUTF8AndUTF16Conversion<WByte>> converter;
    return converter.to_bytes(sWideString);
}

String ConvertGameTimeToString(ULongLong uTime)
{
    const UInt uSecondMax = 60;
    const UInt uMinuteMax = 60;
    const UInt uHourMax = 12;
    ULongLong uLeftover = 0;
    ULongLong uDays = 0;
    ULongLong uHours = 0;
    ULongLong uMinutes = 0;
    ULongLong uSeconds = 0;

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

String ConvertToSimpleCaseString(const String& sString)
{
    StringStream sStrString;
    bool bNewWord = true;
    for(const auto byte : sString)
    {
        bNewWord = bNewWord || STDIsSpace(byte);
        if(STDIsAlphaNumeric(byte))
        {
            if (bNewWord)
            {
                sStrString << static_cast<Byte>(STDToUpper(byte));
                bNewWord = false;
            }
            else
            {
                sStrString << static_cast<Byte>(STDToLower(byte));
            }
        }
        else
        {
            sStrString << byte;
        }
    }
    return sStrString.str();
}

String ConvertToUrlEncodedString(const String& sString)
{
    OutputStringStream sStrStream;
    for(SizeType i = 0; i < sString.length(); i++)
    {
        Short iVal = sString.at(i);
        if(
            iVal == 45 || // hyphen
            (iVal >= 48 && iVal <= 57) || // 0-9
            (iVal >= 65 && iVal <= 90) || // A-Z
            iVal == 95 || // underscore
            (iVal >= 97 && iVal <= 122) || // a-z
            iVal == 126 // tilde
        )
        {
            sStrStream << sString.at(i);
        }
        else
        {
            sStrStream << ConvertByteToHexString(sString.at(i));
        }
    }
    return sStrStream.str();
}

String ConvertToUrlDecodedString(const String& sString)
{
    OutputStringStream sStrStream;
    for(SizeType i = 0; i < sString.length(); i++)
    {
        if(sString.at(i) == '%')
        {
            String sTempStr(sString.substr(i + 1, 2));
            sStrStream << ConvertHexStringToByte(sTempStr);
            i += 2;
        }
        else
        {
            sStrStream << sString.at(i);
        }
    }
    return sStrStream.str();
}

String ConvertByteToHexString(UByte uByte)
{
    Short iVal = uByte;
    StringStream sStrStream;
    sStrStream << "%" << STDSetWidth(2) << STDSetFill('0') << STDHex << iVal;
    return sStrStream.str();
}

UByte ConvertHexStringToByte(const String& sString)
{
    Short iVal = 0;
    if(!sString.empty())
    {
        InputStringStream sStrStream(sString);
        sStrStream >> STDHex >> iVal;
        if(sStrStream.fail())
        {
            THROW_RUNTIME_ERROR("Stream decode failure");
        }
    }
    return static_cast<UByte>(iVal);
}

StringArray ConvertStringToTokenArray(const String& sString, const String& sChars)
{
    StringArray vTokens;
    BoostCharSeparator<Byte> charSeparator(sChars.c_str());
    BoostTokenizer<BoostCharSeparator<Byte>> tokens(sString, charSeparator);
    for (const auto& t : tokens)
    {
        vTokens.push_back(t);
    }
    return vTokens;
}

StringMap ConvertQueryStringToStringMap(const String& sQuery)
{
    StringMap tMap;
    StringArray vQuerySegments = ConvertStringToTokenArray(ConvertToUrlDecodedString(sQuery), "&");
    for(auto& sSegment : vQuerySegments)
    {
        StringArray vParts = ConvertStringToTokenArray(sSegment, "=");
        if(vParts.size() == 2)
        {
            tMap.insert({vParts[0], vParts[1]});
        }
        else if(vParts.size() == 1)
        {
            tMap.insert({vParts[0], ""});
        }
    }
    return tMap;
}

String ConvertPathToFileUri(const String& sPath)
{
    STDVector<String::value_type> vPathChars((sPath.size() * 3) + 10, 0);
    if(ParseFilenameAsUri(sPath.c_str(), vPathChars.data()) == 0)
    {
        return String(vPathChars.begin(), vPathChars.end());
    }
    return sPath;
}

String ConvertSizeToString(FixedSigned64 uSize)
{
    STDOutputStringStream sStream;
    const Int iBytesPerKilobyte = 1024;
    const STDVector<String> vUnits = {"B", "KB", "MB", "GB", "TB", "PB"};
    Int iCurrentUnit = 0;
    while (uSize > iBytesPerKilobyte)
    {
        uSize /= iBytesPerKilobyte;
        iCurrentUnit++;
    }
    sStream << STDFixed << STDSetPrecision(2) << uSize << " " << vUnits.at(iCurrentUnit);
    return sStream.str();
}

};
