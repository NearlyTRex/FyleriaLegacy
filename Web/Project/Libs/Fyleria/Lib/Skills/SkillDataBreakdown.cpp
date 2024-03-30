// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#include "Skills/SkillDataBreakdown.h"

namespace Gecko
{

SkillDataBreakdown::SkillDataBreakdown()
    : SkillData()
{
    // Recipes
    SetRecipes({});
}

SkillDataBreakdown::SkillDataBreakdown(const Json& jsonData)
    : SkillData(jsonData)
{
    from_json(jsonData, *this);
}

void to_json(Json& jsonData, const SkillDataBreakdown& obj)
{
}

void from_json(const Json& jsonData, SkillDataBreakdown& obj)
{
    // Recipes
    obj.SetRecipes(GET_JSON_DATA_OR_DEFAULT(Recipes, RecipeList, RecipeList()));
}

MAKE_JSON_GENERIC_TYPE_CONVERTERS_IMPL(SkillDataBreakdown, SkillDataBreakdown);

};
