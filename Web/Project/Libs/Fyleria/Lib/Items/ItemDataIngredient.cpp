// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#include "Items/ItemDataIngredient.h"

namespace Gecko
{

ItemDataIngredient::ItemDataIngredient()
    : ItemData()
{
    // Stat changes
    SetStatChanges({});
}

ItemDataIngredient::ItemDataIngredient(const Json& jsonData)
    : ItemData(jsonData)
{
    from_json(jsonData, *this);
}

void to_json(Json& jsonData, const ItemDataIngredient& obj)
{
}

void from_json(const Json& jsonData, ItemDataIngredient& obj)
{
    // Stat changes
    obj.SetStatChanges(GET_JSON_DATA_OR_DEFAULT(StatChanges, StatChangeList, StatChangeList()));
}

MAKE_JSON_GENERIC_TYPE_CONVERTERS_IMPL(ItemDataIngredient, ItemDataIngredient);

};
