// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

#ifndef _GECKO_CHARACTER_PARTY_ITEM_H_
#define _GECKO_CHARACTER_PARTY_ITEM_H_

// Internal includes
#include "Utility/Macros.h"
#include "Utility/Tree.h"
#include "Utility/Enum.h"

namespace Gecko
{

class CharacterPartyItem
{
public:

    // Constructors
    CharacterPartyItem();
    CharacterPartyItem(const Json& jsonData);

    // Does the type match the given slot?
    Bool DoesMatchSlot(const String& sSlot) const;

    // Can amount be added/removed?
    Bool CanAddAmount(UInt uAmount) const;
    Bool CanRemoveAmount(UInt uAmount) const;

    // Can amount be equipped/unequipped?
    Bool CanEquipAmount(UInt uAmount) const;
    Bool CanUnequipAmount(UInt uAmount) const;

    // Operations
    Bool AddAmount(UInt uAmount);
    Bool RemoveAmount(UInt uAmount);
    Bool EquipAmount(UInt uAmount);
    Bool UnequipAmount(UInt uAmount);

    // Item tree index
    MAKE_RAW_TYPE_ACCESSORS(ItemTreeIndex, TreeIndex);

    // Item amount
    MAKE_RAW_TYPE_ACCESSORS(ItemAmount, UByte);

    // Number of equips (must be less than or equal to the amount of the item)
    MAKE_RAW_TYPE_ACCESSORS(EquipCount, UByte);

    // Applicable equipment slots
    MAKE_RAW_TYPE_ACCESSORS(ApplicableEquipmentSlots, StringArray);
};

// Typedef
MAKE_COMMON_TYPEDEFS(CharacterPartyItem);

// JSON Converters
void to_json(Json& jsonData, const CharacterPartyItem& obj);
void from_json(const Json& jsonData, CharacterPartyItem& obj);

};

#endif
