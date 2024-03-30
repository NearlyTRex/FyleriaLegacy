// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

// Internal includes
#include "Stats/StatChangeEntry.h"

namespace Gecko
{

StatChangeEntry::StatChangeEntry()
{
}

StatChangeEntry::StatChangeEntry(const Json& jsonData)
{
    from_json(jsonData, *this);
}

StatChangeEntry::~StatChangeEntry()
{
}

void StatChangeEntry::Clear()
{
    // Applicable round or attack number
    SetRound(0);
    SetAttack(0);
    SetDefend(0);

    // Delta amounts
    SetDeltaFloat(0);
    SetDeltaInt(0);

    // Full amounts
    SetFullPercent(0);
    SetFullFloat(0);
    SetFullInt(0);
    SetFullBool(false);
    SetFullString("");
    SetFullFloatArray({});
    SetFullIntArray({});
    SetFullBoolArray({});
    SetFullStringArray({});

    // Operation type (Add, Multiply, etc)
    SetOperationType("");

    // Stats to serve as source and destination
    SetSourceStatType("");
    SetDestinationStatType("");
}

void to_json(Json& jsonData, const StatChangeEntry& obj)
{
    // Applicable round or attack number
    SET_JSON_DATA(Round);
    SET_JSON_DATA(Attack);
    SET_JSON_DATA(Defend);

    // Delta amounts
    SET_JSON_DATA(DeltaFloat);
    SET_JSON_DATA(DeltaInt);

    // Full amounts
    SET_JSON_DATA(FullPercent);
    SET_JSON_DATA(FullFloat);
    SET_JSON_DATA(FullInt);
    SET_JSON_DATA(FullBool);
    SET_JSON_DATA(FullString);
    SET_JSON_DATA(FullFloatArray);
    SET_JSON_DATA(FullIntArray);
    SET_JSON_DATA(FullBoolArray);
    SET_JSON_DATA(FullStringArray);

    // Operation type (Add, Multiply, etc)
    SET_JSON_DATA(OperationType);

    // Stats to serve as source and destination
    SET_JSON_DATA(SourceStatType);
    SET_JSON_DATA(DestinationStatType);

    // Character IDs for applying
    SET_JSON_DATA(SourceCharacterID);
    SET_JSON_DATA(DestinationCharacterIDs);
}

void from_json(const Json& jsonData, StatChangeEntry& obj)
{
    // Applicable round or attack number
    SET_OBJ_DATA(Round, Int);
    SET_OBJ_DATA(Attack, Int);
    SET_OBJ_DATA(Defend, Int);

    // Delta amounts
    SET_OBJ_DATA(DeltaFloat, Float);
    SET_OBJ_DATA(DeltaInt, Int);

    // Full amounts
    SET_OBJ_DATA(FullPercent, Float);
    SET_OBJ_DATA(FullFloat, Float);
    SET_OBJ_DATA(FullInt, Int);
    SET_OBJ_DATA(FullBool, Bool);
    SET_OBJ_DATA(FullString, String);
    SET_OBJ_DATA(FullFloatArray, FloatArray);
    SET_OBJ_DATA(FullIntArray, IntArray);
    SET_OBJ_DATA(FullBoolArray, BoolArray);
    SET_OBJ_DATA(FullStringArray, StringArray);

    // Operation type (Add, Multiply, etc)
    SET_OBJ_DATA(OperationType, String);

    // Stats to serve as source and destination
    SET_OBJ_DATA(SourceStatType, String);
    SET_OBJ_DATA(DestinationStatType, String);

    // Character IDs for applying
    SET_OBJ_DATA(SourceCharacterID, String);
    SET_OBJ_DATA(DestinationCharacterIDs, StringArray);
}

};
