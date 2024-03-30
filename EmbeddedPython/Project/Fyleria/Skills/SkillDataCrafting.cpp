// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

// Internal includes
#include "Skills/SkillDataCrafting.h"

namespace Gecko
{

SkillDataCrafting::SkillDataCrafting()
    : SkillData()
{
}

SkillDataCrafting::SkillDataCrafting(const Json& jsonData)
    : SkillData(jsonData)
{
    from_json(jsonData, *this);
}

SkillDataCrafting::~SkillDataCrafting()
{
}

void SkillDataCrafting::Clear()
{
    // Base clear
    SkillData::Clear();

    // Recipes
    SetRecipes({});
}

void to_json(Json& jsonData, const SkillDataCrafting& obj)
{
    // Recipes
    SET_JSON_DATA(Recipes);
}

void from_json(const Json& jsonData, SkillDataCrafting& obj)
{
    // Recipes
    SET_OBJ_DATA(Recipes, RecipeArray);
}

};
