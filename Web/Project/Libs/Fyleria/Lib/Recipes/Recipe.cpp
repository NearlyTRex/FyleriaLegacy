// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#include "Recipes/Recipe.h"

namespace Gecko
{

Recipe::Recipe()
{
    // Chance to success
    SetChanceToSucceed(0);

    // Ingredients
    SetIngredients({});

    // Results
    SetResults({});
}

Recipe::Recipe(const Json& jsonData)
{
    from_json(jsonData, *this);
}

void to_json(Json& jsonData, const Recipe& obj)
{
    // Chance to success
    SET_JSON_DATA_IF_NOT_DEFAULT(ChanceToSucceed, 0);

    // Ingredients
    SET_JSON_DATA_IF_NOT_EMPTY(Ingredients);

    // Results
    SET_JSON_DATA_IF_NOT_EMPTY(Results);
}

void from_json(const Json& jsonData, Recipe& obj)
{
    // Chance to success
    obj.SetChanceToSucceed(GET_JSON_DATA_OR_DEFAULT(ChanceToSucceed, Float, 0));

    // Ingredients
    obj.SetIngredients(GET_JSON_DATA_OR_DEFAULT(Ingredients, RecipeEntryList, RecipeEntryList()));

    // Results
    obj.SetResults(GET_JSON_DATA_OR_DEFAULT(Results, RecipeEntryList, RecipeEntryList()));
}

MAKE_JSON_GENERIC_TYPE_CONVERTERS_IMPL(Recipe, Recipe);

};
