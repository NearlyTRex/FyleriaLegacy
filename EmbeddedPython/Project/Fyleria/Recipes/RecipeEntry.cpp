// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

// Internal includes
#include "Recipes/RecipeEntry.h"

namespace Gecko
{

RecipeEntry::RecipeEntry()
{
}

RecipeEntry::RecipeEntry(const Json& jsonData)
{
    from_json(jsonData, *this);
}

RecipeEntry::~RecipeEntry()
{
}

void RecipeEntry::Clear()
{
    // Chance to success
    SetChanceToSucceed(0);

    // Input type
    SetInputPotionName("");
    SetInputIngredientName("");
    SetInputWeaponName("");
    SetInputArmorName("");

    // Output type
    SetOutputPotionName("");
    SetOutputIngredientName("");
    SetOutputWeaponName("");
    SetOutputArmorName("");

    // Input amount
    SetInputAmount(0);

    // Output amount
    SetOutputAmount(0);
}

void to_json(Json& jsonData, const RecipeEntry& obj)
{
    // Chance to success
    SET_JSON_DATA(ChanceToSucceed);

    // Input type
    SET_JSON_DATA(InputPotionName);
    SET_JSON_DATA(InputIngredientName);
    SET_JSON_DATA(InputWeaponName);
    SET_JSON_DATA(InputArmorName);

    // Output type
    SET_JSON_DATA(OutputPotionName);
    SET_JSON_DATA(OutputIngredientName);
    SET_JSON_DATA(OutputWeaponName);
    SET_JSON_DATA(OutputArmorName);

    // Input amount
    SET_JSON_DATA(InputAmount);

    // Output amount
    SET_JSON_DATA(OutputAmount);
}

void from_json(const Json& jsonData, RecipeEntry& obj)
{
    // Chance to success
    SET_OBJ_DATA(ChanceToSucceed, Float);

    // Input type
    SET_OBJ_DATA(InputPotionName, String);
    SET_OBJ_DATA(InputIngredientName, String);
    SET_OBJ_DATA(InputWeaponName, String);
    SET_OBJ_DATA(InputArmorName, String);

    // Output type
    SET_OBJ_DATA(OutputPotionName, String);
    SET_OBJ_DATA(OutputIngredientName, String);
    SET_OBJ_DATA(OutputWeaponName, String);
    SET_OBJ_DATA(OutputArmorName, String);

    // Input amount
    SET_OBJ_DATA(InputAmount, Int);

    // Output amount
    SET_OBJ_DATA(OutputAmount, Int);
}

};
