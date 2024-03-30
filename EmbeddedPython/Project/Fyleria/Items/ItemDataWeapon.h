// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

#ifndef _GECKO_ITEMDATA_WEAPON_H_
#define _GECKO_ITEMDATA_WEAPON_H_

// Internal includes
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

    // Destructor
    virtual ~ItemDataWeapon();

    // Clear all data
    virtual void Clear() override;

    // Item tree type
    static String GetTreeType()
    {
        return String(ItemTreeType(ItemTreeType::Weapon)._to_string());
    }

    // Create weapon action
    CharacterActionArray CreateWeaponActions(const String& sCharacterID, const String& sWeaponSet) const;

    // Stat percents
    MAKE_RAW_TYPE_ACCESSORS(BluntAttackPercent, Float);
    MAKE_RAW_TYPE_ACCESSORS(PierceAttackPercent, Float);
    MAKE_RAW_TYPE_ACCESSORS(SlashAttackPercent, Float);

    // Stat changes
    MAKE_RAW_TYPE_ACCESSORS(StatChanges, StatChangeArray);
};

// Typedef
MAKE_COMMON_TYPEDEFS(ItemDataWeapon);

// JSON Converters
void to_json(Json& jsonData, const ItemDataWeapon& obj);
void from_json(const Json& jsonData, ItemDataWeapon& obj);

};

#endif
