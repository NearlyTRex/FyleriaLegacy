// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#include "Character/CharacterProgressItem.h"

namespace Gecko
{

CharacterProgressItem::CharacterProgressItem()
{
    // Item tree index
    SetTreeIndex({});

    // Item slot
    SetItemSlot(IndexedString("None"));
}

CharacterProgressItem::CharacterProgressItem(const Json& jsonData)
{
    from_json(jsonData, *this);
}

void to_json(Json& jsonData, const CharacterProgressItem& obj)
{
    // Item tree index
    SET_JSON_DATA_IF_NOT_EMPTY(TreeIndex);

    // Item slot
    SET_JSON_DATA_IF_NOT_DEFAULT(ItemSlot, IndexedString("None"));
}

void from_json(const Json& jsonData, CharacterProgressItem& obj)
{
    // Item tree index
    obj.SetTreeIndex(GET_JSON_DATA_OR_DEFAULT(TreeIndex, TreeIndex, TreeIndex()));

    // Item slot
    obj.SetItemSlot(GET_JSON_DATA_OR_DEFAULT(ItemSlot, IndexedString, IndexedString("None")));
}

MAKE_JSON_GENERIC_TYPE_CONVERTERS_IMPL(CharacterProgressItem, CharacterProgressItem);

Bool operator==(const CharacterProgressItem& a, const CharacterProgressItem& b)
{
    return (
        (a.GetTreeIndex() == b.GetTreeIndex()) &&
        (a.GetItemSlot() == b.GetItemSlot())
    );
}

};
