// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

// Internal includes
#include "Items/ItemDataArmor.h"

namespace Gecko
{

ItemDataArmor::ItemDataArmor()
    : ItemData()
{
}

ItemDataArmor::ItemDataArmor(const Json& jsonData)
    : ItemData(jsonData)
{
    from_json(jsonData, *this);
}

ItemDataArmor::~ItemDataArmor()
{
}

void ItemDataArmor::Clear()
{
    // Base clear
    ItemData::Clear();

    // Stat percents
    SetBluntDefendPercent(0);
    SetPierceDefendPercent(0);
    SetSlashDefendPercent(0);
    SetMagicDefendPercent(0);

    // Stat changes
    SetStatChanges({});
}

CharacterActionArray ItemDataArmor::CreateArmorActions(const String& sCharacterID, const String& sWeaponSet) const
{
    CharacterActionArray vNewActions;
    return vNewActions;
}

void to_json(Json& jsonData, const ItemDataArmor& obj)
{
    // Stat percents
    SET_JSON_DATA(BluntDefendPercent);
    SET_JSON_DATA(PierceDefendPercent);
    SET_JSON_DATA(SlashDefendPercent);
    SET_JSON_DATA(MagicDefendPercent);

    // Stat changes
    SET_JSON_DATA(StatChanges);
}

void from_json(const Json& jsonData, ItemDataArmor& obj)
{
    // Stat percents
    SET_OBJ_DATA(BluntDefendPercent, Float);
    SET_OBJ_DATA(PierceDefendPercent, Float);
    SET_OBJ_DATA(SlashDefendPercent, Float);
    SET_OBJ_DATA(MagicDefendPercent, Float);

    // Stat changes
    SET_OBJ_DATA(StatChanges, StatChangeArray);
}

};
