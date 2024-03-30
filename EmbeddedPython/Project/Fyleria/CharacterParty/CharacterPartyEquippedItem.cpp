// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

// Internal includes
#include "CharacterParty/CharacterPartyEquippedItem.h"

namespace Gecko
{

CharacterPartyEquippedItem::CharacterPartyEquippedItem()
{
}

CharacterPartyEquippedItem::CharacterPartyEquippedItem(const Json& jsonData)
{
    from_json(jsonData, *this);
}

void to_json(Json& jsonData, const CharacterPartyEquippedItem& obj)
{
    // Item tree index
    SET_JSON_DATA(ItemTreeIndex);

    // Item slot
    SET_JSON_DATA(ItemSlot);
}

void from_json(const Json& jsonData, CharacterPartyEquippedItem& obj)
{
    // Item tree index
    SET_OBJ_DATA(ItemTreeIndex, TreeIndex);

    // Item slot
    SET_OBJ_DATA(ItemSlot, String);
}

Bool operator==(const CharacterPartyEquippedItem& a, const CharacterPartyEquippedItem& b)
{
    return (
        (a.GetItemTreeIndex() == b.GetItemTreeIndex()) &&
        (a.GetItemSlot() == b.GetItemSlot())
    );
}

};
