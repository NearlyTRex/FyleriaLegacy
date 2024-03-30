// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#include "Recipes/RecipeEntry.h"

namespace Gecko
{

RecipeEntry::RecipeEntry()
{
    // Chance to success
    SetChanceToSucceed(0);

    // Input type
    SetInputPotionName(IndexedString(""));
    SetInputIngredientName(IndexedString(""));
    SetInputWeaponName(IndexedString(""));
    SetInputArmorName(IndexedString(""));

    // Output type
    SetOutputPotionName(IndexedString(""));
    SetOutputIngredientName(IndexedString(""));
    SetOutputWeaponName(IndexedString(""));
    SetOutputArmorName(IndexedString(""));

    // Input amount
    SetInputAmount(0);

    // Output amount
    SetOutputAmount(0);
}

RecipeEntry::RecipeEntry(const Json& jsonData)
{
    from_json(jsonData, *this);
}

void to_json(Json& jsonData, const RecipeEntry& obj)
{
    // Chance to success
    SET_JSON_DATA_IF_NOT_DEFAULT(ChanceToSucceed, 0);

    // Input type
    SET_JSON_DATA_IF_NOT_DEFAULT(InputPotionName, IndexedString(""));
    SET_JSON_DATA_IF_NOT_DEFAULT(InputIngredientName, IndexedString(""));
    SET_JSON_DATA_IF_NOT_DEFAULT(InputWeaponName, IndexedString(""));
    SET_JSON_DATA_IF_NOT_DEFAULT(InputArmorName, IndexedString(""));

    // Output type
    SET_JSON_DATA_IF_NOT_DEFAULT(OutputPotionName, IndexedString(""));
    SET_JSON_DATA_IF_NOT_DEFAULT(OutputIngredientName, IndexedString(""));
    SET_JSON_DATA_IF_NOT_DEFAULT(OutputWeaponName, IndexedString(""));
    SET_JSON_DATA_IF_NOT_DEFAULT(OutputArmorName, IndexedString(""));

    // Input amount
    SET_JSON_DATA_IF_NOT_DEFAULT(InputAmount, 0);

    // Output amount
    SET_JSON_DATA_IF_NOT_DEFAULT(OutputAmount, 0);
}

void from_json(const Json& jsonData, RecipeEntry& obj)
{
    // Chance to success
    obj.SetChanceToSucceed(GET_JSON_DATA_OR_DEFAULT(ChanceToSucceed, Float, 0));

    // Input type
    obj.SetInputPotionName(GET_JSON_DATA_OR_DEFAULT(InputPotionName, IndexedString, IndexedString("")));
    obj.SetInputIngredientName(GET_JSON_DATA_OR_DEFAULT(InputIngredientName, IndexedString, IndexedString("")));
    obj.SetInputWeaponName(GET_JSON_DATA_OR_DEFAULT(InputWeaponName, IndexedString, IndexedString("")));
    obj.SetInputArmorName(GET_JSON_DATA_OR_DEFAULT(InputArmorName, IndexedString, IndexedString("")));

    // Output type
    obj.SetOutputPotionName(GET_JSON_DATA_OR_DEFAULT(OutputPotionName, IndexedString, IndexedString("")));
    obj.SetOutputIngredientName(GET_JSON_DATA_OR_DEFAULT(OutputIngredientName, IndexedString, IndexedString("")));
    obj.SetOutputWeaponName(GET_JSON_DATA_OR_DEFAULT(OutputWeaponName, IndexedString, IndexedString("")));
    obj.SetOutputArmorName(GET_JSON_DATA_OR_DEFAULT(OutputArmorName, IndexedString, IndexedString("")));

    // Input amount
    obj.SetInputAmount(GET_JSON_DATA_OR_DEFAULT(InputAmount, Int, 0));

    // Output amount
    obj.SetOutputAmount(GET_JSON_DATA_OR_DEFAULT(OutputAmount, Int, 0));
}

MAKE_JSON_GENERIC_TYPE_CONVERTERS_IMPL(RecipeEntry, RecipeEntry);

};
