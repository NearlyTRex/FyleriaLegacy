// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#ifndef _GECKO_ITEMDATA_POTION_H_
#define _GECKO_ITEMDATA_POTION_H_

#include "Items/ItemData.h"
#include "Items/ItemTypes.h"
#include "Stats/StatChange.h"

namespace Gecko
{

class ItemDataPotion : public ItemData
{
public:

    // Constructors
    ItemDataPotion();
    ItemDataPotion(const Json& jsonData);

    // Item tree type
    static IndexedString GetTreeType()
    {
        return IndexedString(ItemTreeType(ItemTreeType::Potion)._to_string());
    }

    // Create potion action
    CharacterActionSharedPtrList CreatePotionActions(const IndexedString& sCharacterID, const IndexedString& sWeaponSet) const;

    // Stat changes
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(StatChanges, StatChangeList);
};

// Typedef
MAKE_TYPE_TYPEDEFS(ItemDataPotion);

// JSON Converters
void to_json(Json& jsonData, const ItemDataPotion& obj);
void from_json(const Json& jsonData, ItemDataPotion& obj);
MAKE_JSON_GENERIC_TYPE_CONVERTERS_DECL(ItemDataPotion, ItemDataPotion);

};

#endif
