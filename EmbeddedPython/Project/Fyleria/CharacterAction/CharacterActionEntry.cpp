// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

// Internal includes
#include "CharacterAction/CharacterActionEntry.h"

namespace Gecko
{

CharacterActionEntry::CharacterActionEntry()
{
}

CharacterActionEntry::CharacterActionEntry(const Json& jsonData)
{
    from_json(jsonData, *this);
}

CharacterActionEntry::CharacterActionEntry(const String& jsonString)
{
    from_json(JsonParse(jsonString), *this);
}

CharacterActionEntry::~CharacterActionEntry()
{
}

void CharacterActionEntry::Clear()
{
    // Action types
    SetActionTypes({});

    // Hand
    SetHandType("");

    // Whether hand is using a shield
    SetIsHandTypeShield(false);

    // Target
    SetDestinationTargetType("");

    // Character
    SetDestinationCharacterIDs({});

    // Result
    SetResults({});
}

Bool CharacterActionEntry::DoesMatchActionType(const String& sType) const
{
    return STDFindData(GetActionTypes().begin(), GetActionTypes().end(), sType) != GetActionTypes().end();
}

Bool CharacterActionEntry::operator==(const CharacterActionEntry& other) const
{
    return (Json(*this) == Json(other));
}

Bool CharacterActionEntry::operator!=(const CharacterActionEntry& other) const
{
    return not operator==(other);
}

void to_json(Json& jsonData, const CharacterActionEntry& obj)
{
    // Action types
    SET_JSON_DATA(ActionTypes);

    // Hand
    SET_JSON_DATA(HandType);

    // Whether hand is using a shield
    SET_JSON_DATA(IsHandTypeShield);

    // Target
    SET_JSON_DATA(DestinationTargetType);

    // Character
    SET_JSON_DATA(DestinationCharacterIDs);

    // Result
    SET_JSON_DATA(Results);
}

void from_json(const Json& jsonData, CharacterActionEntry& obj)
{
    // Action types
    SET_OBJ_DATA(ActionTypes, StringArray);

    // Hand
    SET_OBJ_DATA(HandType, String);

    // Whether hand is using a shield
    SET_OBJ_DATA(IsHandTypeShield, Bool);

    // Target
    SET_OBJ_DATA(DestinationTargetType, String);

    // Character
    SET_OBJ_DATA(DestinationCharacterIDs, StringArray);

    // Result
    SET_OBJ_DATA(Results, CharacterActionEntry::CharacterActionResultMapType);
}

};
