// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#include "Character/CharacterActionEntry.h"

namespace Gecko
{

CharacterActionEntry::CharacterActionEntry()
    : SerializableToJson()
{
    // Action types
    SetActionTypes({});

    // Hand
    SetHandType(IndexedString("None"));

    // Whether hand is using a shield
    SetIsHandTypeShield(false);

    // Target
    SetDestinationTargetType(IndexedString("None"));

    // Character
    SetDestinationCharacterID(IndexedString(""));

    // Result
    SetResult({});
}

CharacterActionEntry::CharacterActionEntry(const Json& jsonData)
    : SerializableToJson(jsonData)
{
}

CharacterActionEntry::CharacterActionEntry(const String& jsonString)
    : SerializableToJson(JsonParse(jsonString))
{
}

Bool CharacterActionEntry::operator==(const CharacterActionEntry& other) const
{
    return (Json(*this) == Json(other));
}

Bool CharacterActionEntry::operator!=(const CharacterActionEntry& other) const
{
    return not operator==(other);
}

MAKE_JSON_BASIC_TYPE_CONVERTERS_IMPL(CharacterActionEntry);
MAKE_JSON_GENERIC_TYPE_CONVERTERS_IMPL(CharacterActionEntry, CharacterActionEntry);

};
