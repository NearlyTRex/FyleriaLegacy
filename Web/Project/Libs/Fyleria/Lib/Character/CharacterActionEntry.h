// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#ifndef _GECKO_CHARACTER_ACTION_ENTRY_H_
#define _GECKO_CHARACTER_ACTION_ENTRY_H_

#include "Character/CharacterActionResult.h"
#include "Utility/IndexedString.h"
#include "Utility/Macros.h"
#include "Utility/TypesJson.h"
#include "Utility/Serializable.h"

namespace Gecko
{

class CharacterActionEntry : public SerializableToJson
{
public:

    // Constructors
    CharacterActionEntry();
    explicit CharacterActionEntry(const Json& jsonData);
    explicit CharacterActionEntry(const String& jsonString);

    // Action types
    MAKE_JSON_BASIC_TYPE_ACCESSORS(ActionTypes, IndexedStringList);

    // Hand
    MAKE_JSON_BASIC_TYPE_ACCESSORS(HandType, IndexedString);

    // Whether hand is using a shield
    MAKE_JSON_BASIC_TYPE_ACCESSORS(IsHandTypeShield, Bool);

    // Target
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DestinationTargetType, IndexedString);

    // Character
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DestinationCharacterID, IndexedString);

    // Result
    MAKE_JSON_BASIC_TYPE_ACCESSORS(Result, CharacterActionResult);

    // Comparisons
    Bool operator==(const CharacterActionEntry& other) const;
    Bool operator!=(const CharacterActionEntry& other) const;
};

// Typedef
MAKE_TYPE_TYPEDEFS(CharacterActionEntry);

// JSON Converters
MAKE_JSON_BASIC_TYPE_CONVERTERS_DECL(CharacterActionEntry);
MAKE_JSON_GENERIC_TYPE_CONVERTERS_DECL(CharacterActionEntry, CharacterActionEntry);

};

#endif
