// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#include "Stats/StatChangeEntry.h"

namespace Gecko
{

StatChangeEntry::StatChangeEntry()
{
    // Applicable round or attack number
    SetRound(0);
    SetAttack(0);
    SetDefend(0);

    // Delta amount is from the source character
    SetDeltaPercent(0);
    SetDeltaFloat(0);
    SetDeltaInt(0);
    SetDeltaBool(false);
    SetDeltaString(IndexedString(""));
    SetDeltaFloatList({});
    SetDeltaIntList({});
    SetDeltaBoolList({});
    SetDeltaStringList({});

    // Full amount is from the destination character
    SetFullPercent(0);
    SetFullFloat(0);
    SetFullInt(0);
    SetFullBool(false);
    SetFullString(IndexedString(""));
    SetFullFloatList({});
    SetFullIntList({});
    SetFullBoolList({});
    SetFullStringList({});

    // Operation type (Add, Multiply, etc)
    SetOperationType(IndexedString("None"));

    // Stats to serve as source and destination
    SetSourceStatType(IndexedString("None"));
    SetDestinationStatType(IndexedString("None"));
}

StatChangeEntry::StatChangeEntry(const Json& jsonData)
{
    from_json(jsonData, *this);
}

void to_json(Json& jsonData, const StatChangeEntry& obj)
{
    // Applicable round or attack number
    SET_JSON_DATA_IF_NOT_DEFAULT(Round, 0);
    SET_JSON_DATA_IF_NOT_DEFAULT(Attack, 0);
    SET_JSON_DATA_IF_NOT_DEFAULT(Defend, 0);

    // Delta amount is from the source character
    SET_JSON_DATA_IF_NOT_DEFAULT(DeltaPercent, 0);
    SET_JSON_DATA_IF_NOT_DEFAULT(DeltaFloat, 0);
    SET_JSON_DATA_IF_NOT_DEFAULT(DeltaInt, 0);
    SET_JSON_DATA_IF_NOT_DEFAULT(DeltaBool, false);
    SET_JSON_DATA_IF_NOT_DEFAULT(DeltaString, IndexedString(""));
    SET_JSON_DATA_IF_NOT_EMPTY(DeltaFloatList);
    SET_JSON_DATA_IF_NOT_EMPTY(DeltaIntList);
    SET_JSON_DATA_IF_NOT_EMPTY(DeltaBoolList);
    SET_JSON_DATA_IF_NOT_EMPTY(DeltaStringList);

    // Full amount is from the destination character
    SET_JSON_DATA_IF_NOT_DEFAULT(FullPercent, 0);
    SET_JSON_DATA_IF_NOT_DEFAULT(FullFloat, 0);
    SET_JSON_DATA_IF_NOT_DEFAULT(FullInt, 0);
    SET_JSON_DATA_IF_NOT_DEFAULT(FullBool, false);
    SET_JSON_DATA_IF_NOT_DEFAULT(FullString, IndexedString(""));
    SET_JSON_DATA_IF_NOT_EMPTY(FullFloatList);
    SET_JSON_DATA_IF_NOT_EMPTY(FullIntList);
    SET_JSON_DATA_IF_NOT_EMPTY(FullBoolList);
    SET_JSON_DATA_IF_NOT_EMPTY(FullStringList);

    // Operation type (Add, Multiply, etc)
    SET_JSON_DATA_IF_NOT_DEFAULT(OperationType, IndexedString("None"));

    // Stats to serve as source and destination
    SET_JSON_DATA_IF_NOT_DEFAULT(SourceStatType, IndexedString("None"));
    SET_JSON_DATA_IF_NOT_DEFAULT(DestinationStatType, IndexedString("None"));

    // Character IDs for applying
    SET_JSON_DATA_IF_NOT_DEFAULT(SourceCharacterID, IndexedString(""));
    SET_JSON_DATA_IF_NOT_EMPTY(DestinationCharacterIDs);
}

void from_json(const Json& jsonData, StatChangeEntry& obj)
{
    // Applicable round or attack number
    obj.SetRound(GET_JSON_DATA_OR_DEFAULT(Round, Int, 0));
    obj.SetAttack(GET_JSON_DATA_OR_DEFAULT(Attack, Int, 0));
    obj.SetDefend(GET_JSON_DATA_OR_DEFAULT(Defend, Int, 0));

    // Delta amount is from the source character
    obj.SetDeltaPercent(GET_JSON_DATA_OR_DEFAULT(DeltaPercent, Float, 0));
    obj.SetDeltaFloat(GET_JSON_DATA_OR_DEFAULT(DeltaFloat, Float, 0));
    obj.SetDeltaInt(GET_JSON_DATA_OR_DEFAULT(DeltaInt, Int, 0));
    obj.SetDeltaBool(GET_JSON_DATA_OR_DEFAULT(DeltaBool, Bool, false));
    obj.SetDeltaString(GET_JSON_DATA_OR_DEFAULT(DeltaString, IndexedString, IndexedString("")));
    obj.SetDeltaFloatList(GET_JSON_DATA_OR_DEFAULT(DeltaFloatList, FloatList, FloatList()));
    obj.SetDeltaIntList(GET_JSON_DATA_OR_DEFAULT(DeltaIntList, IntList, IntList()));
    obj.SetDeltaBoolList(GET_JSON_DATA_OR_DEFAULT(DeltaBoolList, BoolList, BoolList()));
    obj.SetDeltaStringList(GET_JSON_DATA_OR_DEFAULT(DeltaStringList, IndexedStringList, IndexedStringList()));

    // Full amount is from the destination character
    obj.SetFullPercent(GET_JSON_DATA_OR_DEFAULT(FullPercent, Float, 0));
    obj.SetFullFloat(GET_JSON_DATA_OR_DEFAULT(FullFloat, Float, 0));
    obj.SetFullInt(GET_JSON_DATA_OR_DEFAULT(FullInt, Int, 0));
    obj.SetFullBool(GET_JSON_DATA_OR_DEFAULT(FullBool, Bool, false));
    obj.SetFullString(GET_JSON_DATA_OR_DEFAULT(FullString, IndexedString, IndexedString("")));
    obj.SetFullFloatList(GET_JSON_DATA_OR_DEFAULT(FullFloatList, FloatList, FloatList()));
    obj.SetFullIntList(GET_JSON_DATA_OR_DEFAULT(FullIntList, IntList, IntList()));
    obj.SetFullBoolList(GET_JSON_DATA_OR_DEFAULT(FullBoolList, BoolList, BoolList()));
    obj.SetFullStringList(GET_JSON_DATA_OR_DEFAULT(FullStringList, IndexedStringList, IndexedStringList()));

    // Operation type (Add, Multiply, etc)
    obj.SetOperationType(GET_JSON_DATA_OR_DEFAULT(OperationType, IndexedString, IndexedString("None")));

    // Stats to serve as source and destination
    obj.SetSourceStatType(GET_JSON_DATA_OR_DEFAULT(SourceStatType, IndexedString, IndexedString("None")));
    obj.SetDestinationStatType(GET_JSON_DATA_OR_DEFAULT(DestinationStatType, IndexedString, IndexedString("None")));

    // Character IDs for applying
    obj.SetSourceCharacterID(GET_JSON_DATA_OR_DEFAULT(SourceCharacterID, IndexedString, IndexedString("")));
    obj.SetDestinationCharacterIDs(GET_JSON_DATA_OR_DEFAULT(DestinationCharacterIDs, IndexedStringList, IndexedStringList()));
}

MAKE_JSON_GENERIC_TYPE_CONVERTERS_IMPL(StatChangeEntry, StatChangeEntry);

};
