// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

#ifndef _GECKO_UTILITY_CONVERTERS_H_
#define _GECKO_UTILITY_CONVERTERS_H_

// Internal includes
#include "Utility/Types.h"

namespace Gecko
{

// Convert string to wide string
WString ConvertStringToWideString(const String& sString);

// Convert wide string to string
String ConvertWideStringToString(const WString& sWideString);

// Convert game time to string
String ConvertGameTimeToString(ULongLong uTime);

// Convert string to simple case string
String ConvertToSimpleCaseString(const String& sString);

// Convert to url encoded string
String ConvertToUrlEncodedString(const String& sString);

// Convert to url decoded string
String ConvertToUrlDecodedString(const String& sString);

// Convert byte to hex string
String ConvertByteToHexString(UByte uByte);

// Convert hex string to byte
UByte ConvertHexStringToByte(const String& sString);

// Convert string to token array
StringArray ConvertStringToTokenArray(const String& sString, const String& sChars);

// Convert query string to string map
StringMap ConvertQueryStringToStringMap(const String& sQuery);

// Convert path to file URI
String ConvertPathToFileUri(const String& sPath);

// Convert size to string containing the correct type
String ConvertSizeToString(FixedSigned64 uSize);

};

#endif
