// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#include "Items/ItemDataArmor.h"

namespace Gecko
{

ItemDataArmor::ItemDataArmor()
    : ItemData()
{
    // Stat percents
    SetBluntDefendPercent(0);
    SetPierceDefendPercent(0);
    SetSlashDefendPercent(0);
    SetMagicDefendPercent(0);

    // Stat changes
    SetStatChanges({});
}

ItemDataArmor::ItemDataArmor(const Json& jsonData)
    : ItemData(jsonData)
{
    from_json(jsonData, *this);
}

CharacterActionSharedPtrList ItemDataArmor::CreateArmorActions(const IndexedString& sCharacterID, const IndexedString& sWeaponSet) const
{
    CharacterActionSharedPtrList vNewActions;
    return vNewActions;
}

void to_json(Json& jsonData, const ItemDataArmor& obj)
{
}

void from_json(const Json& jsonData, ItemDataArmor& obj)
{
    // Stat percents
    obj.SetBluntDefendPercent(GET_JSON_DATA_OR_DEFAULT(BluntDefendPercent, Float, 0));
    obj.SetPierceDefendPercent(GET_JSON_DATA_OR_DEFAULT(PierceDefendPercent, Float, 0));
    obj.SetSlashDefendPercent(GET_JSON_DATA_OR_DEFAULT(SlashDefendPercent, Float, 0));
    obj.SetMagicDefendPercent(GET_JSON_DATA_OR_DEFAULT(MagicDefendPercent, Float, 0));

    // Stat changes
    obj.SetStatChanges(GET_JSON_DATA_OR_DEFAULT(StatChanges, StatChangeList, StatChangeList()));
}

MAKE_JSON_GENERIC_TYPE_CONVERTERS_IMPL(ItemDataArmor, ItemDataArmor);

};
