// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

// Internal includes
#include "Items/ItemDataWeapon.h"

namespace Gecko
{

ItemDataWeapon::ItemDataWeapon()
    : ItemData()
{
}

ItemDataWeapon::ItemDataWeapon(const Json& jsonData)
    : ItemData(jsonData)
{
    from_json(jsonData, *this);
}

ItemDataWeapon::~ItemDataWeapon()
{
}

void ItemDataWeapon::Clear()
{
    // Base clear
    ItemData::Clear();

    // Stat percents
    SetBluntAttackPercent(0);
    SetPierceAttackPercent(0);
    SetSlashAttackPercent(0);

    // Stat changes
    SetStatChanges({});
}

CharacterActionArray ItemDataWeapon::CreateWeaponActions(const String& sCharacterID, const String& sWeaponSet) const
{
    CharacterActionArray vNewActions;
    return vNewActions;
}

void to_json(Json& jsonData, const ItemDataWeapon& obj)
{
    // Stat percents
    SET_JSON_DATA(BluntAttackPercent);
    SET_JSON_DATA(PierceAttackPercent);
    SET_JSON_DATA(SlashAttackPercent);

    // Stat changes
    SET_JSON_DATA(StatChanges);
}

void from_json(const Json& jsonData, ItemDataWeapon& obj)
{
    // Stat percents
    SET_OBJ_DATA(BluntAttackPercent, Float);
    SET_OBJ_DATA(PierceAttackPercent, Float);
    SET_OBJ_DATA(SlashAttackPercent, Float);

    // Stat changes
    SET_OBJ_DATA(StatChanges, StatChangeArray);
}

};
