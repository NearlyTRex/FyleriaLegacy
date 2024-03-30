// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

#ifndef _GECKO_CHARACTER_ACTION_ENTRY_H_
#define _GECKO_CHARACTER_ACTION_ENTRY_H_

// Internal includes
#include "CharacterAction/CharacterActionResult.h"
#include "Utility/Macros.h"
#include "Utility/Json.h"

namespace Gecko
{

class CharacterActionEntry
{
public:

    // Types
    typedef STDUnorderedMap<String, CharacterActionResult> CharacterActionResultMapType;

    // Constructors
    CharacterActionEntry();
    CharacterActionEntry(const Json& jsonData);
    CharacterActionEntry(const String& jsonString);

    // Destructor
    virtual ~CharacterActionEntry();

    // Clear all data
    void Clear();

    // Determine if action type is a match
    Bool DoesMatchActionType(const String& sType) const;

    // Action types
    MAKE_RAW_TYPE_ACCESSORS(ActionTypes, StringArray);

    // Hand
    MAKE_RAW_TYPE_ACCESSORS(HandType, String);

    // Whether hand is using a shield
    MAKE_RAW_TYPE_ACCESSORS(IsHandTypeShield, Bool);

    // Target
    MAKE_RAW_TYPE_ACCESSORS(DestinationTargetType, String);

    // Character
    MAKE_RAW_TYPE_ACCESSORS(DestinationCharacterIDs, StringArray);

    // Result
    MAKE_RAW_TYPE_ACCESSORS(Results, CharacterActionResultMapType);

    // Comparisons
    Bool operator==(const CharacterActionEntry& other) const;
    Bool operator!=(const CharacterActionEntry& other) const;
};

// Typedef
MAKE_COMMON_TYPEDEFS(CharacterActionEntry);

// JSON Converters
void to_json(Json& jsonData, const CharacterActionEntry& obj);
void from_json(const Json& jsonData, CharacterActionEntry& obj);

};

#endif
