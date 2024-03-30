// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#ifndef _GECKO_ITEMDATA_INGREDIENT_H_
#define _GECKO_ITEMDATA_INGREDIENT_H_

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

    // Item tree type
    static IndexedString GetTreeType()
    {
        return IndexedString(ItemTreeType(ItemTreeType::Ingredient)._to_string());
    }

    // Stat changes
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(StatChanges, StatChangeList);
};

// Typedef
MAKE_TYPE_TYPEDEFS(ItemDataIngredient);

// JSON Converters
void to_json(Json& jsonData, const ItemDataIngredient& obj);
void from_json(const Json& jsonData, ItemDataIngredient& obj);
MAKE_JSON_GENERIC_TYPE_CONVERTERS_DECL(ItemDataIngredient, ItemDataIngredient);

};

#endif
