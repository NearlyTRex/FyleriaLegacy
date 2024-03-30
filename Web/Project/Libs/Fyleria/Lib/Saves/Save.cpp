// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#include "Saves/Save.h"

namespace Gecko
{

Save::Save()
    : SerializableToJson()
{
    // Slot
    SetSlot(0);

    // Time
    SetTime(0);

    // Description
    SetDescription("");

    // Party
    SetParty({});

    // Characters
    SetCharacters({});
}

Save::Save(const Json& jsonData)
    : SerializableToJson(jsonData)
{
}

Save::Save(const String& jsonString)
    : SerializableToJson(JsonParse(jsonString))
{
}

MAKE_JSON_BASIC_TYPE_CONVERTERS_IMPL(Save);
MAKE_JSON_GENERIC_TYPE_CONVERTERS_IMPL(Save, Save);

};
