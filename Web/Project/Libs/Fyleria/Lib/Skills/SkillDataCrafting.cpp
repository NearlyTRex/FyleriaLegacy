// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#include "Skills/SkillDataCrafting.h"

namespace Gecko
{

SkillDataCrafting::SkillDataCrafting()
    : SkillData()
{
    // Recipes
    SetRecipes({});
}

SkillDataCrafting::SkillDataCrafting(const Json& jsonData)
    : SkillData(jsonData)
{
    from_json(jsonData, *this);
}

void to_json(Json& jsonData, const SkillDataCrafting& obj)
{
}

void from_json(const Json& jsonData, SkillDataCrafting& obj)
{
    // Recipes
    obj.SetRecipes(GET_JSON_DATA_OR_DEFAULT(Recipes, RecipeList, RecipeList()));
}

MAKE_JSON_GENERIC_TYPE_CONVERTERS_IMPL(SkillDataCrafting, SkillDataCrafting);

};
