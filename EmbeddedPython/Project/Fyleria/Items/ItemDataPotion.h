// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

#ifndef _GECKO_ITEMDATA_POTION_H_
#define _GECKO_ITEMDATA_POTION_H_

// Internal includes
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

    // Destructor
    virtual ~ItemDataPotion();

    // Clear all data
    virtual void Clear() override;

    // Item tree type
    static String GetTreeType()
    {
        return String(ItemTreeType(ItemTreeType::Potion)._to_string());
    }

    // Create potion action
    CharacterActionArray CreatePotionActions(const String& sCharacterID, const String& sWeaponSet) const;

    // Stat changes
    MAKE_RAW_TYPE_ACCESSORS(StatChanges, StatChangeArray);
};

// Typedef
MAKE_COMMON_TYPEDEFS(ItemDataPotion);

// JSON Converters
void to_json(Json& jsonData, const ItemDataPotion& obj);
void from_json(const Json& jsonData, ItemDataPotion& obj);

};

#endif
