// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#include "Character/CharacterPartyItem.h"
#include "Character/CharacterTypes.h"
#include "Items/ItemTypes.h"
#include "Items/ItemTree.h"

namespace Gecko
{

CharacterPartyItem::CharacterPartyItem()
{
    // Item tree index
    SetTreeIndex({});

    // Item amount
    SetAmount(0);

    // Number of equips (must be less than or equal to the amount of the item)
    SetEquipCount(0);

    // Applicable equipment slots
    SetApplicableEquipmentSlots({});
}

Bool CharacterPartyItem::DoesMatchSlot(const IndexedString& sSlot) const
{
    return STDVectorDoesIntersectElement<IndexedString>(GetApplicableEquipmentSlots(), sSlot);
}

Bool CharacterPartyItem::CanAddAmount(UInt uAmount) const
{
    return true;
}

Bool CharacterPartyItem::CanRemoveAmount(UInt uAmount) const
{
    return (uAmount <= GetAmount()) && (GetAmount() - uAmount > GetEquipCount());
}

Bool CharacterPartyItem::CanEquipAmount(UInt uAmount) const
{
    return (uAmount <= GetAmount()) && (GetEquipCount() + uAmount <= GetAmount());
}

Bool CharacterPartyItem::CanUnequipAmount(UInt uAmount) const
{
    return (uAmount <= GetAmount()) && (uAmount <= GetEquipCount());
}

Bool CharacterPartyItem::AddAmount(UInt uAmount)
{
    if(CanAddAmount(uAmount))
    {
        const UInt kuMaxUInt = STDNumericLimits<UInt>::max();
        UInt uNewAmount = STDClip<UInt>(GetAmount() + uAmount, 0, kuMaxUInt);
        SetAmount(uNewAmount);
        return true;
    }
    return false;
}

Bool CharacterPartyItem::RemoveAmount(UInt uAmount)
{
    if(CanRemoveAmount(uAmount))
    {
        const UInt kuMaxInt = STDNumericLimits<Int>::max();
        Int iNewAmount = STDClip<Int>((Int)GetAmount() - (Int)uAmount, 0, kuMaxInt);
        SetAmount((UInt)iNewAmount);
        return true;
    }
    return false;
}

Bool CharacterPartyItem::EquipAmount(UInt uAmount)
{
    if(CanEquipAmount(uAmount))
    {
        SetEquipCount(GetEquipCount() + uAmount);
        return true;
    }
    return false;
}

Bool CharacterPartyItem::UnequipAmount(UInt uAmount)
{
    if(CanUnequipAmount(uAmount))
    {
        SetEquipCount(GetEquipCount() - uAmount);
        return true;
    }
    return false;
}

void to_json(Json& jsonData, const CharacterPartyItem& obj)
{
    // Item tree index
    SET_JSON_DATA_IF_NOT_EMPTY(TreeIndex);

    // Item amount
    SET_JSON_DATA_IF_NOT_DEFAULT(Amount, 0);

    // Number of equips (must be less than or equal to the amount of the item)
    SET_JSON_DATA_IF_NOT_DEFAULT(EquipCount, 0);

    // Applicable equipment slots
    SET_JSON_DATA_IF_NOT_EMPTY(ApplicableEquipmentSlots);
}

void from_json(const Json& jsonData, CharacterPartyItem& obj)
{
    // Item tree index
    obj.SetTreeIndex(GET_JSON_DATA_OR_DEFAULT(TreeIndex, TreeIndex, TreeIndex()));

    // Item amount
    obj.SetAmount(GET_JSON_DATA_OR_DEFAULT(Amount, UByte, 0));

    // Number of equips (must be less than or equal to the amount of the item)
    obj.SetEquipCount(GET_JSON_DATA_OR_DEFAULT(EquipCount, UByte, 0));

    // Applicable equipment slots
    obj.SetApplicableEquipmentSlots(GET_JSON_DATA_OR_DEFAULT(ApplicableEquipmentSlots, IndexedStringList, IndexedStringList()));
}

MAKE_JSON_GENERIC_TYPE_CONVERTERS_IMPL(CharacterPartyItem, CharacterPartyItem);

};
