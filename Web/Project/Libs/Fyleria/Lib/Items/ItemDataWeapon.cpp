// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#include "Items/ItemDataWeapon.h"

namespace Gecko
{

ItemDataWeapon::ItemDataWeapon()
    : ItemData()
{
    // Stat percents
    SetBluntAttackPercent(0);
    SetPierceAttackPercent(0);
    SetSlashAttackPercent(0);

    // Stat changes
    SetStatChanges({});
}

ItemDataWeapon::ItemDataWeapon(const Json& jsonData)
    : ItemData(jsonData)
{
    from_json(jsonData, *this);
}

CharacterActionSharedPtrList ItemDataWeapon::CreateWeaponActions(const IndexedString& sCharacterID, const IndexedString& sWeaponSet) const
{
    CharacterActionSharedPtrList vNewActions;
    return vNewActions;
}

void to_json(Json& jsonData, const ItemDataWeapon& obj)
{
}

void from_json(const Json& jsonData, ItemDataWeapon& obj)
{
    // Stat percents
    obj.SetBluntAttackPercent(GET_JSON_DATA_OR_DEFAULT(BluntAttackPercent, Float, 0));
    obj.SetPierceAttackPercent(GET_JSON_DATA_OR_DEFAULT(PierceAttackPercent, Float, 0));
    obj.SetSlashAttackPercent(GET_JSON_DATA_OR_DEFAULT(SlashAttackPercent, Float, 0));

    // Stat changes
    obj.SetStatChanges(GET_JSON_DATA_OR_DEFAULT(StatChanges, StatChangeList, StatChangeList()));
}

MAKE_JSON_GENERIC_TYPE_CONVERTERS_IMPL(ItemDataWeapon, ItemDataWeapon);

};
