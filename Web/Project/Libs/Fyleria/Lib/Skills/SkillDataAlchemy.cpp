// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#include "Skills/SkillDataAlchemy.h"

namespace Gecko
{

SkillDataAlchemy::SkillDataAlchemy()
    : SkillData()
{
    // Recipes
    SetRecipes({});
}

SkillDataAlchemy::SkillDataAlchemy(const Json& jsonData)
    : SkillData(jsonData)
{
    from_json(jsonData, *this);
}

void to_json(Json& jsonData, const SkillDataAlchemy& obj)
{
}

void from_json(const Json& jsonData, SkillDataAlchemy& obj)
{
    // Recipes
    obj.SetRecipes(GET_JSON_DATA_OR_DEFAULT(Recipes, RecipeList, RecipeList()));
}

MAKE_JSON_GENERIC_TYPE_CONVERTERS_IMPL(SkillDataAlchemy, SkillDataAlchemy);

};
