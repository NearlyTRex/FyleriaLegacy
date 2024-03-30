// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

#ifndef _GECKO_ITEMDATA_ARMOR_H_
#define _GECKO_ITEMDATA_ARMOR_H_

// Internal includes
#include "Items/ItemData.h"
#include "Items/ItemTypes.h"
#include "Stats/StatChange.h"

namespace Gecko
{

class ItemDataArmor : public ItemData
{
public:

    // Constructors
    ItemDataArmor();
    ItemDataArmor(const Json& jsonData);

    // Destructor
    virtual ~ItemDataArmor();

    // Clear all data
    virtual void Clear() override;

    // Item tree type
    static String GetTreeType()
    {
        return String(ItemTreeType(ItemTreeType::Armor)._to_string());
    }

    // Create armor action
    CharacterActionArray CreateArmorActions(const String& sCharacterID, const String& sWeaponSet) const;

    // Stat percents
    MAKE_RAW_TYPE_ACCESSORS(BluntDefendPercent, Float);
    MAKE_RAW_TYPE_ACCESSORS(PierceDefendPercent, Float);
    MAKE_RAW_TYPE_ACCESSORS(SlashDefendPercent, Float);
    MAKE_RAW_TYPE_ACCESSORS(MagicDefendPercent, Float);

    // Stat changes
    MAKE_RAW_TYPE_ACCESSORS(StatChanges, StatChangeArray);
};

// Typedef
MAKE_COMMON_TYPEDEFS(ItemDataArmor);

// JSON Converters
void to_json(Json& jsonData, const ItemDataArmor& obj);
void from_json(const Json& jsonData, ItemDataArmor& obj);

};

#endif
