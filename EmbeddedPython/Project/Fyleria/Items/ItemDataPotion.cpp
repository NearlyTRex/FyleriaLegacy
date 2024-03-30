// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

// Internal includes
#include "Items/ItemDataPotion.h"

namespace Gecko
{

ItemDataPotion::ItemDataPotion()
    : ItemData()
{
}

ItemDataPotion::ItemDataPotion(const Json& jsonData)
    : ItemData(jsonData)
{
    from_json(jsonData, *this);
}

ItemDataPotion::~ItemDataPotion()
{
}

void ItemDataPotion::Clear()
{
    // Base clear
    ItemData::Clear();

    // Stat changes
    SetStatChanges({});
}

CharacterActionArray ItemDataPotion::CreatePotionActions(const String& sCharacterID, const String& sWeaponSet) const
{
    CharacterActionArray vNewActions;
    return vNewActions;
}

void to_json(Json& jsonData, const ItemDataPotion& obj)
{
    // Stat changes
    SET_JSON_DATA(StatChanges);
}

void from_json(const Json& jsonData, ItemDataPotion& obj)
{
    // Stat changes
    SET_OBJ_DATA(StatChanges, StatChangeArray);
}

};
