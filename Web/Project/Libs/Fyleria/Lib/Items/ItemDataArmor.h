// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#ifndef _GECKO_ITEMDATA_ARMOR_H_
#define _GECKO_ITEMDATA_ARMOR_H_

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

    // Item tree type
    static IndexedString GetTreeType()
    {
        return IndexedString(ItemTreeType(ItemTreeType::Armor)._to_string());
    }

    // Create armor action
    CharacterActionSharedPtrList CreateArmorActions(const IndexedString& sCharacterID, const IndexedString& sWeaponSet) const;

    // Stat percents
    MAKE_RAW_BASIC_TYPE_ACCESSORS(BluntDefendPercent, Float);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(PierceDefendPercent, Float);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(SlashDefendPercent, Float);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(MagicDefendPercent, Float);

    // Stat changes
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(StatChanges, StatChangeList);
};

// Typedef
MAKE_TYPE_TYPEDEFS(ItemDataArmor);

// JSON Converters
void to_json(Json& jsonData, const ItemDataArmor& obj);
void from_json(const Json& jsonData, ItemDataArmor& obj);
MAKE_JSON_GENERIC_TYPE_CONVERTERS_DECL(ItemDataArmor, ItemDataArmor);

};

#endif
