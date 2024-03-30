// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#ifndef _GECKO_CHARACTER_ACTION_H_
#define _GECKO_CHARACTER_ACTION_H_

#include "Character/CharacterActionEntry.h"
#include "Utility/IndexedString.h"
#include "Utility/Macros.h"
#include "Utility/TypesEnum.h"
#include "Utility/TypesJson.h"
#include "Utility/PolymorphicBase.h"

namespace Gecko
{

class CharacterAction : public PolymorphicBase, public STDEnableSharedFromThis<CharacterAction>
{
public:

    // Constructors
    CharacterAction();
    CharacterAction(const Json& jsonData);

    // Get list of character IDs
    virtual IndexedStringList GetAllCharacterIDs() const;

    // Get list of action types from all entries
    virtual IndexedStringList GetAllActionTypes() const;

    // Get list of destination target types from all entries
    virtual IndexedStringList GetAllDestinationTargetTypes() const;

    // Are all character IDs valid
    virtual Bool AreAllCharacterIDsValid() const;

    // Prepare character IDs
    virtual Bool PrepareCharacterIDs();

    // Stages for running the action
    // These are broken up so that the UI can proceed once it has finished
    virtual Bool Setup() = 0;
    virtual Bool Finish() = 0;
    virtual Bool GenerateResult() = 0;
    virtual Bool ApplyResult() = 0;

    // Run type
    MAKE_RAW_BASIC_TYPE_ACCESSORS(RunType, IndexedString);

    // Order
    MAKE_RAW_BASIC_TYPE_ACCESSORS(Order, Short);

    // Cost
    MAKE_RAW_BASIC_TYPE_ACCESSORS(CostAP, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(CostHP, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(CostMP, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(CostEP, UByte);

    // Applicable weapon set
    MAKE_RAW_BASIC_TYPE_ACCESSORS(WeaponSet, IndexedString);

    // Action entries
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(ActionEntries, CharacterActionEntryList);

    // Previous action types
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(PreviousActionTypes, IndexedStringList);

    // Skill
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(SkillTreeIndex, TreeIndex);

    // Item
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(ItemTreeIndex, TreeIndex);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(ItemAmount, UByte);

    // Targets
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(SourceTargetType, IndexedString);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(AreDestinationTargetsIdentical, Bool);

    // Characters
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(SourceCharacterID, IndexedString);
};

// Typedef
MAKE_TYPE_TYPEDEFS(CharacterAction);

// Factory functions
CharacterActionSharedPtr MakePolymorphicCharacterAction(const Json& jsonData);

// JSON Converters
void to_json(Json& jsonData, const CharacterAction& obj);
void to_json(Json& jsonData, const CharacterActionSharedPtr& pObj);
void to_json(Json& jsonData, const CharacterActionSharedPtrList& vObjs);
void from_json(const Json& jsonData, CharacterAction& obj);
void from_json(const Json& jsonData, CharacterActionSharedPtr& pObj);
void from_json(const Json& jsonData, CharacterActionSharedPtrList& vObjs);
MAKE_JSON_GENERIC_TYPE_CONVERTERS_DECL(CharacterAction, CharacterActionSharedPtr);

};

#endif
