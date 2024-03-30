// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

#ifndef _GECKO_CHARACTER_PARTY_MEMBER_H_
#define _GECKO_CHARACTER_PARTY_MEMBER_H_

// Internal includes
#include "CharacterParty/CharacterPartyEquippedItem.h"
#include "Utility/Macros.h"
#include "Utility/Tree.h"
#include "Utility/Enum.h"

namespace Gecko
{

class CharacterPartyMember
{
public:

    // Constructors
    CharacterPartyMember();
    CharacterPartyMember(const Json& jsonData);

    // Get item counts
    UInt GetEquippedItemTypeCount(const TreeIndex& index) const;
    UInt GetEquippedWeaponCount(const String& sWeaponSet) const;
    UInt GetEquippedShieldCount(const String& sWeaponSet) const;

    // Check if an item can be added/removed
    Bool CanAddEquippedItem(const TreeIndex& index) const;
    Bool CanRemoveEquippedItem(const TreeIndex& index) const;

    // Add/remove equipped items
    Bool AddEquippedItem(const TreeIndex& index, const String& sEquipSlot);
    Bool RemoveEquippedItem(const TreeIndex& index, const String& sEquipSlot);

    // Get primary/secondary hand info
    Bool GetHandInfoByWeaponSet(const String& sWeaponSet,
        TreeIndex& primaryItemIndex,
        TreeIndex& secondaryItemIndex,
        StringArray& vPrimaryActionTypes,
        StringArray& vSecondaryActionTypes) const;

    // Character ID
    MAKE_RAW_TYPE_ACCESSORS(CharacterID, String);

    // Character target type
    MAKE_RAW_TYPE_ACCESSORS(CharacterTargetType, String);

    // Equipped items
    MAKE_RAW_TYPE_ACCESSORS(EquippedItems, CharacterPartyEquippedItemArray);
};

// Typedef
MAKE_COMMON_TYPEDEFS(CharacterPartyMember);

// JSON Converters
void to_json(Json& jsonData, const CharacterPartyMember& obj);
void from_json(const Json& jsonData, CharacterPartyMember& obj);

};

#endif
