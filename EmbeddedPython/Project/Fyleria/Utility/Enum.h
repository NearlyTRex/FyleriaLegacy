// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

#ifndef _GECKO_UTILITY_ENUMS_H_
#define _GECKO_UTILITY_ENUMS_H_

// External includes
#include <enum.h>

// Internal includes
#include "Utility/Assert.h"
#include "Utility/Macros.h"
#include "Utility/Types.h"

namespace Gecko
{

BETTER_ENUM(OperationType, Int,
    None,
    Add,
    Subtract,
    Multiply,
    Divide,
    Modulus,
    Set
);

BETTER_ENUM(ComparisonType, Int,
    None,
    And,
    Or
);

BETTER_ENUM(FileType, Int,
    None,
    TextJson,
    BinaryCBOR,
    BinaryMsgPack
);

template <typename T>
StringArray GetEnumNames()
{
    StringArray vTypeNames;
    for (const char* name : T::_names())
    {
        vTypeNames.push_back(name);
    }
    return vTypeNames;
}

template <typename T>
T GetEnumFromString(const String& sType)
{
    return T::_from_string(sType.c_str());
}

template <typename T>
T GetEnumFromStringOrNone(const String& sType)
{
    if(T::_is_valid(sType.c_str()))
    {
        return T::_from_string(sType.c_str());
    }
    return +T::None;
}

template <typename T>
Bool IsValidEnumString(const String& sType)
{
    return T::_is_valid(sType.c_str());
}

template <typename T>
Bool IsNoneTypeForEnum(const String& sType)
{
    return (sType == (+T::None)._to_string());
}

template <typename T>
String GetNoneTypeForEnum()
{
    return (+T::None)._to_string();
}

};

#endif
