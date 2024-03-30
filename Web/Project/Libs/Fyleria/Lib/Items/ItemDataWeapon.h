// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#ifndef _GECKO_ITEMDATA_WEAPON_H_
#define _GECKO_ITEMDATA_WEAPON_H_

#include "Items/ItemData.h"
#include "Items/ItemTypes.h"
#include "Stats/StatChange.h"

namespace Gecko
{

class ItemDataWeapon : public ItemData
{
public:

    // Constructors
    ItemDataWeapon();
    ItemDataWeapon(const Json& jsonData);

    // Item tree type
    static IndexedString GetTreeType()
    {
        return IndexedString(ItemTreeType(ItemTreeType::Weapon)._to_string());
    }

    // Create weapon action
    CharacterActionSharedPtrList CreateWeaponActions(const IndexedString& sCharacterID, const IndexedString& sWeaponSet) const;

    // Stat percents
    MAKE_RAW_BASIC_TYPE_ACCESSORS(BluntAttackPercent, Float);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(PierceAttackPercent, Float);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(SlashAttackPercent, Float);

    // Stat changes
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(StatChanges, StatChangeList);
};

// Typedef
MAKE_TYPE_TYPEDEFS(ItemDataWeapon);

// JSON Converters
void to_json(Json& jsonData, const ItemDataWeapon& obj);
void from_json(const Json& jsonData, ItemDataWeapon& obj);
MAKE_JSON_GENERIC_TYPE_CONVERTERS_DECL(ItemDataWeapon, ItemDataWeapon);

};

#endif
