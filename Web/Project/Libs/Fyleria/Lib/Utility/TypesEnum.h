// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#ifndef _GECKO_TYPES_ENUMS_H_
#define _GECKO_TYPES_ENUMS_H_

// External includes
#include <enum.h>

// Internal includes
#include "Utility/IndexedString.h"
#include "Utility/Macros.h"
#include "Utility/TypesSimple.h"

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

MAKE_ENUM_GETSTRINGLIST_DECL(OperationType);
MAKE_ENUM_GETSTRINGLIST_DECL(ComparisonType);

MAKE_ENUM_CONVERTERS_DECL(OperationType);
MAKE_ENUM_CONVERTERS_DECL(ComparisonType);

MAKE_ENUM_GETSTRINGLIST_DECL(FileType);
MAKE_ENUM_CONVERTERS_DECL(FileType);

};

#endif
