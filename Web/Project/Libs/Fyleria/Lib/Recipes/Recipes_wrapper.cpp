// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#include "Recipes/Recipe.h"
#include "Recipes/RecipeEntry.h"
#include "Utility/Macros.h"
#include "Utility/Serializable.h"
#include "Utility/TypesPython.h"

PYBIND11_EMBEDDED_MODULE(GeckoRecipes, m)
{
    // Recipe.h
    PyBindClass<Gecko::Recipe>(m, "Recipe")
        WRAPPING_ADD_CONSTRUCTOR_SIMPLE()
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(ChanceToSucceed, Gecko::Recipe)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(Ingredients, Gecko::Recipe)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(Results, Gecko::Recipe)
    ;
    PyBindVector<Gecko::RecipeList>(m, "RecipeList");
    WRAPPING_STANDALONE_METHOD_SIMPLE(ConvertRecipeToJsonString, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(ConvertRecipeListToJsonString, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetRecipeFromJsonString, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetRecipeListFromJsonString, Gecko);

    // RecipeEntry.h
    PyBindClass<Gecko::RecipeEntry>(m, "RecipeEntry")
        WRAPPING_ADD_CONSTRUCTOR_SIMPLE()
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(ChanceToSucceed, Gecko::RecipeEntry)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(InputPotionName, Gecko::RecipeEntry)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(InputIngredientName, Gecko::RecipeEntry)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(InputWeaponName, Gecko::RecipeEntry)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(InputArmorName, Gecko::RecipeEntry)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(OutputPotionName, Gecko::RecipeEntry)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(OutputIngredientName, Gecko::RecipeEntry)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(OutputWeaponName, Gecko::RecipeEntry)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(OutputArmorName, Gecko::RecipeEntry)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(InputAmount, Gecko::RecipeEntry)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(OutputAmount, Gecko::RecipeEntry)
    ;
    PyBindVector<Gecko::RecipeEntryList>(m, "RecipeEntryList");
    WRAPPING_STANDALONE_METHOD_SIMPLE(ConvertRecipeEntryToJsonString, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(ConvertRecipeEntryListToJsonString, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetRecipeEntryFromJsonString, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetRecipeEntryListFromJsonString, Gecko);
}
