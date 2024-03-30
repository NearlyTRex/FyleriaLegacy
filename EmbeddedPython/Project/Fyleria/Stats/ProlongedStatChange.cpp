// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

// Internal includes
#include "Stats/ProlongedStatChange.h"

namespace Gecko
{

ProlongedStatChange::ProlongedStatChange()
{
}

ProlongedStatChange::ProlongedStatChange(const Json& jsonData)
{
    from_json(jsonData, *this);
}

ProlongedStatChange::ProlongedStatChange(const String& jsonString)
{
    from_json(JsonParse(jsonString), *this);
}

ProlongedStatChange::~ProlongedStatChange()
{
}

void ProlongedStatChange::Clear()
{
    // Relevant stat change
    SetStatChangeEntry({});

    // Valid round
    SetRound(-1);

    // Valid attack
    SetAttack(-1);

    // Valid defend
    SetDefend(-1);
}

void to_json(Json& jsonData, const ProlongedStatChange& obj)
{
    // Relevant stat change
    SET_JSON_DATA(StatChangeEntry);

    // Valid round
    SET_JSON_DATA(Round);

    // Valid attack
    SET_JSON_DATA(Attack);

    // Valid defend
    SET_JSON_DATA(Defend);
}

void from_json(const Json& jsonData, ProlongedStatChange& obj)
{
    // Relevant stat change
    SET_OBJ_DATA(StatChangeEntry, StatChangeEntry);

    // Valid round
    SET_OBJ_DATA(Round, Int);

    // Valid attack
    SET_OBJ_DATA(Attack, Int);

    // Valid defend
    SET_OBJ_DATA(Defend, Int);
}

};
