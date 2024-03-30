// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

#ifndef _GECKO_ITEMDATA_INGREDIENT_H_
#define _GECKO_ITEMDATA_INGREDIENT_H_

// Internal includes
#include "Items/ItemData.h"
#include "Items/ItemTypes.h"
#include "Stats/StatChange.h"

namespace Gecko
{

class ItemDataIngredient : public ItemData
{
public:

    // Constructors
    ItemDataIngredient();
    ItemDataIngredient(const Json& jsonData);

    // Destructor
    virtual ~ItemDataIngredient();

    // Clear all data
    virtual void Clear() override;

    // Item tree type
    static String GetTreeType()
    {
        return String(ItemTreeType(ItemTreeType::Ingredient)._to_string());
    }

    // Stat changes
    MAKE_RAW_TYPE_ACCESSORS(StatChanges, StatChangeArray);
};

// Typedef
MAKE_COMMON_TYPEDEFS(ItemDataIngredient);

// JSON Converters
void to_json(Json& jsonData, const ItemDataIngredient& obj);
void from_json(const Json& jsonData, ItemDataIngredient& obj);

};

#endif
