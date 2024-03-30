// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

// Internal includes
#include "Skills/SkillDataAlchemy.h"

namespace Gecko
{

SkillDataAlchemy::SkillDataAlchemy()
    : SkillData()
{
}

SkillDataAlchemy::SkillDataAlchemy(const Json& jsonData)
    : SkillData(jsonData)
{
    from_json(jsonData, *this);
}

SkillDataAlchemy::~SkillDataAlchemy()
{
}

void SkillDataAlchemy::Clear()
{
    // Base clear
    SkillData::Clear();

    // Recipes
    SetRecipes({});
}

void to_json(Json& jsonData, const SkillDataAlchemy& obj)
{
    // Recipes
    SET_JSON_DATA(Recipes);
}

void from_json(const Json& jsonData, SkillDataAlchemy& obj)
{
    // Recipes
    SET_OBJ_DATA(Recipes, RecipeArray);
}

};
