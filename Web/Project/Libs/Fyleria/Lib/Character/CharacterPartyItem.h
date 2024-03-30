// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#ifndef _GECKO_CHARACTER_PARTY_ITEM_H_
#define _GECKO_CHARACTER_PARTY_ITEM_H_

#include "Utility/IndexedString.h"
#include "Utility/Macros.h"
#include "Utility/Tree.h"
#include "Utility/TypesEnum.h"

namespace Gecko
{

class CharacterPartyItem
{
public:

    // Constructors
    CharacterPartyItem();

    // Does the type match the given slot?
    Bool DoesMatchSlot(const IndexedString& sSlot) const;

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
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(TreeIndex, TreeIndex);

    // Item amount
    MAKE_RAW_BASIC_TYPE_ACCESSORS(Amount, UByte);

    // Number of equips (must be less than or equal to the amount of the item)
    MAKE_RAW_BASIC_TYPE_ACCESSORS(EquipCount, UByte);

    // Applicable equipment slots
    MAKE_RAW_BASIC_TYPE_ACCESSORS(ApplicableEquipmentSlots, IndexedStringList);
};

// Typedef
MAKE_TYPE_TYPEDEFS(CharacterPartyItem);

// JSON Converters
void to_json(Json& jsonData, const CharacterPartyItem& obj);
void from_json(const Json& jsonData, CharacterPartyItem& obj);
MAKE_JSON_GENERIC_TYPE_CONVERTERS_DECL(CharacterPartyItem, CharacterPartyItem);

};

#endif
