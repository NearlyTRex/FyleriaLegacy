// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

// Internal includes
#include "Recipes/Recipe.h"
#include "Recipes/RecipeEntry.h"
#include "Utility/Macros.h"
#include "Utility/Python.h"

PYBIND11_EMBEDDED_MODULE(GeckoRecipes, m)
{
    // Recipe.h
    PyBindClass<Gecko::Recipe>(m, "Recipe")
        WRAPPING_ADD_CONSTRUCTOR_SIMPLE()
        WRAPPING_ADD_METHOD_SIMPLE(Clear, Gecko::Recipe)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(ChanceToSucceed, Gecko::Recipe)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(Ingredients, Gecko::Recipe)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(Results, Gecko::Recipe)
    ;
    PyBindVector<Gecko::RecipeArray>(m, "RecipeArray");

    // RecipeEntry.h
    PyBindClass<Gecko::RecipeEntry>(m, "RecipeEntry")
        WRAPPING_ADD_CONSTRUCTOR_SIMPLE()
        WRAPPING_ADD_METHOD_SIMPLE(Clear, Gecko::RecipeEntry)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(ChanceToSucceed, Gecko::RecipeEntry)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(InputPotionName, Gecko::RecipeEntry)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(InputIngredientName, Gecko::RecipeEntry)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(InputWeaponName, Gecko::RecipeEntry)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(InputArmorName, Gecko::RecipeEntry)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(OutputPotionName, Gecko::RecipeEntry)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(OutputIngredientName, Gecko::RecipeEntry)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(OutputWeaponName, Gecko::RecipeEntry)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(OutputArmorName, Gecko::RecipeEntry)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(InputAmount, Gecko::RecipeEntry)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(OutputAmount, Gecko::RecipeEntry)
    ;
    PyBindVector<Gecko::RecipeEntryArray>(m, "RecipeEntryArray");
}
