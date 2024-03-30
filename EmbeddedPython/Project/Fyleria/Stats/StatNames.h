// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

#ifndef _GECKO_STAT_NAMES_H_
#define _GECKO_STAT_NAMES_H_

// Internal includes
#include "Utility/Types.h"

namespace Gecko
{

// Types
typedef SafeStringUnorderedSet SafeStatNameSetType;

// Stat names
SafeStatNameSetType& GetBoolStatNames();
SafeStatNameSetType& GetByteStatNames();
SafeStatNameSetType& GetShortStatNames();
SafeStatNameSetType& GetIntStatNames();
SafeStatNameSetType& GetLongStatNames();
SafeStatNameSetType& GetLongLongStatNames();
SafeStatNameSetType& GetUByteStatNames();
SafeStatNameSetType& GetUShortStatNames();
SafeStatNameSetType& GetUIntStatNames();
SafeStatNameSetType& GetULongStatNames();
SafeStatNameSetType& GetULongLongStatNames();
SafeStatNameSetType& GetFloatStatNames();
SafeStatNameSetType& GetDoubleStatNames();
SafeStatNameSetType& GetLongDoubleStatNames();
SafeStatNameSetType& GetStringStatNames();
SafeStatNameSetType& GetStringArrayStatNames();

// Determine stat value types
Bool IsStatBool(const String& sStat);
Bool IsStatByte(const String& sStat);
Bool IsStatShort(const String& sStat);
Bool IsStatInt(const String& sStat);
Bool IsStatLong(const String& sStat);
Bool IsStatLongLong(const String& sStat);
Bool IsStatUByte(const String& sStat);
Bool IsStatUShort(const String& sStat);
Bool IsStatUInt(const String& sStat);
Bool IsStatULong(const String& sStat);
Bool IsStatULongLong(const String& sStat);
Bool IsStatFloat(const String& sStat);
Bool IsStatDouble(const String& sStat);
Bool IsStatLongDouble(const String& sStat);
Bool IsStatString(const String& sStat);
Bool IsStatStringArray(const String& sStat);

// Initialize all stat names
void InitializeAllStatNames();

};

#endif
