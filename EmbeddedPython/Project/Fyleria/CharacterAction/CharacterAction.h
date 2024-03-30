// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

#ifndef _GECKO_CHARACTER_ACTION_H_
#define _GECKO_CHARACTER_ACTION_H_

// Internal includes
#include "CharacterAction/CharacterActionEntry.h"
#include "Utility/ResultManager.h"
#include "Utility/Macros.h"
#include "Utility/Enum.h"
#include "Utility/Json.h"

namespace Gecko
{

class CharacterAction
{
public:

    // Constructors
    CharacterAction();
    CharacterAction(const Json& jsonData);
    CharacterAction(const String& jsonString);

    // Destructor
    virtual ~CharacterAction();

    // Clear all data
    void Clear();

    // Get array of character IDs
    StringArray GetAllCharacterIDs() const;
    MAKE_MODULE_RESULT_VARIANT(GetAllCharacterIDs);

    // Get array of action types from all entries
    StringArray GetAllActionTypes() const;
    MAKE_MODULE_RESULT_VARIANT(GetAllActionTypes);

    // Get array of destination target types from all entries
    StringArray GetAllDestinationTargetTypes() const;
    MAKE_MODULE_RESULT_VARIANT(GetAllDestinationTargetTypes);

    // Are all character IDs valid
    Bool AreAllCharacterIDsValid() const;
    MAKE_MODULE_RESULT_VARIANT(AreAllCharacterIDsValid);

    // Prepare character IDs
    Bool PrepareCharacterIDs();
    MAKE_MODULE_RESULT_VARIANT(PrepareCharacterIDs);

    // Run type
    MAKE_RAW_TYPE_ACCESSORS(RunType, String);

    // Order
    MAKE_RAW_TYPE_ACCESSORS(Order, Short);

    // Cost
    MAKE_RAW_TYPE_ACCESSORS(CostAP, UByte);
    MAKE_RAW_TYPE_ACCESSORS(CostHP, UByte);
    MAKE_RAW_TYPE_ACCESSORS(CostMP, UByte);
    MAKE_RAW_TYPE_ACCESSORS(CostEP, UByte);

    // Applicable weapon set
    MAKE_RAW_TYPE_ACCESSORS(WeaponSet, String);

    // Action entries
    MAKE_RAW_TYPE_ACCESSORS(ActionEntries, CharacterActionEntryArray);

    // Previous action types
    MAKE_RAW_TYPE_ACCESSORS(PreviousActionTypes, StringArray);

    // Skill
    MAKE_RAW_TYPE_ACCESSORS(SkillTreeIndex, TreeIndex);

    // Item
    MAKE_RAW_TYPE_ACCESSORS(ItemTreeIndex, TreeIndex);
    MAKE_RAW_TYPE_ACCESSORS(ItemAmount, UByte);

    // Targets
    MAKE_RAW_TYPE_ACCESSORS(SourceTargetType, String);

    // Characters
    MAKE_RAW_TYPE_ACCESSORS(SourceCharacterID, String);
};

// Typedef
MAKE_COMMON_TYPEDEFS(CharacterAction);

// JSON Converters
void to_json(Json& jsonData, const CharacterAction& obj);
void from_json(const Json& jsonData, CharacterAction& obj);

};

#endif
