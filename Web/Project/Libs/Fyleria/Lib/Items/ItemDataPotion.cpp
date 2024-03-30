// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#include "Items/ItemDataPotion.h"

namespace Gecko
{

ItemDataPotion::ItemDataPotion()
    : ItemData()
{
    // Stat changes
    SetStatChanges({});
}

ItemDataPotion::ItemDataPotion(const Json& jsonData)
    : ItemData(jsonData)
{
    from_json(jsonData, *this);
}

CharacterActionSharedPtrList ItemDataPotion::CreatePotionActions(const IndexedString& sCharacterID, const IndexedString& sWeaponSet) const
{
    CharacterActionSharedPtrList vNewActions;
    return vNewActions;
}

void to_json(Json& jsonData, const ItemDataPotion& obj)
{
}

void from_json(const Json& jsonData, ItemDataPotion& obj)
{
    // Stat changes
    obj.SetStatChanges(GET_JSON_DATA_OR_DEFAULT(StatChanges, StatChangeList, StatChangeList()));
}

MAKE_JSON_GENERIC_TYPE_CONVERTERS_IMPL(ItemDataPotion, ItemDataPotion);

};
