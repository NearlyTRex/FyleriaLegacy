// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

// Internal includes
#include "Saves/Save.h"

namespace Gecko
{

Save::Save()
{
}

Save::Save(const Json& jsonData)
{
    from_json(jsonData, *this);
}

Save::Save(const String& jsonString)
{
    from_json(JsonParse(jsonString), *this);
}

Save::~Save()
{
}

void Save::Clear()
{
    // Slot
    SetSlot("");

    // Time
    SetTime(0);

    // Description
    SetDescription("");

    // Parties
    SetParties({});

    // Characters
    SetCharacters({});
}

void to_json(Json& jsonData, const Save& obj)
{
    // Slot
    SET_JSON_DATA(Slot);

    // Time
    SET_JSON_DATA(Time);

    // Description
    SET_JSON_DATA(Description);

    // Party
    SET_JSON_DATA(Parties);

    // Characters
    SET_JSON_DATA(Characters);
}

void from_json(const Json& jsonData, Save& obj)
{
    // Slot
    SET_OBJ_DATA(Slot, String);

    // Time
    SET_OBJ_DATA(Time, ULongLong);

    // Description
    SET_OBJ_DATA(Description, String);

    // Party
    SET_OBJ_DATA(Parties, CharacterPartyArray);

    // Characters
    SET_OBJ_DATA(Characters, CharacterArray);
}

};
