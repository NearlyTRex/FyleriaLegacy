// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#ifndef _GECKO_STAT_CHANGE_ENTRY_H_
#define _GECKO_STAT_CHANGE_ENTRY_H_

#include "Utility/IndexedString.h"
#include "Utility/Macros.h"
#include "Utility/TypesEnum.h"
#include "Utility/TypesJson.h"

namespace Gecko
{

// POD class for stat change entries
class StatChangeEntry
{
public:

    // Constructors
    StatChangeEntry();
    StatChangeEntry(const Json& jsonData);

    // Applicable round or attack number
    MAKE_RAW_BASIC_TYPE_ACCESSORS(Round, Short);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(Attack, Short);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(Defend, Short);

    // Delta amount is from the source character
    MAKE_RAW_BASIC_TYPE_ACCESSORS(DeltaPercent, Float);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(DeltaFloat, Float);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(DeltaInt, Int);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(DeltaBool, Bool);
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(DeltaString, IndexedString);
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(DeltaFloatList, FloatList);
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(DeltaIntList, IntList);
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(DeltaBoolList, BoolList);
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(DeltaStringList, IndexedStringList);

    // Full amount is from the destination character
    MAKE_RAW_BASIC_TYPE_ACCESSORS(FullPercent, Float);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(FullFloat, Float);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(FullInt, Int);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(FullBool, Bool);
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(FullString, IndexedString);
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(FullFloatList, FloatList);
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(FullIntList, IntList);
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(FullBoolList, BoolList);
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(FullStringList, IndexedStringList);

    // Operation type (Add, Multiply, etc)
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(OperationType, IndexedString);

    // Stats to serve as source and destination
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(SourceStatType, IndexedString);
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(DestinationStatType, IndexedString);

    // Character IDs for applying
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(SourceCharacterID, IndexedString);
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(DestinationCharacterIDs, IndexedStringList);
};

// Typedefs
MAKE_TYPE_TYPEDEFS(StatChangeEntry);

// JSON Converters
void to_json(Json& jsonData, const StatChangeEntry& obj);
void from_json(const Json& jsonData, StatChangeEntry& obj);
MAKE_JSON_GENERIC_TYPE_CONVERTERS_DECL(StatChangeEntry, StatChangeEntry);

};

#endif
