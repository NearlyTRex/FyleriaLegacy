// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#ifndef _GECKO_SKILLDATA_CRAFTING_H_
#define _GECKO_SKILLDATA_CRAFTING_H_

#include "Skills/SkillData.h"
#include "Skills/SkillTypes.h"
#include "Recipes/Recipe.h"

namespace Gecko
{

class SkillDataCrafting : public SkillData
{
public:

    // Constructors
    SkillDataCrafting();
    SkillDataCrafting(const Json& jsonData);

    // Skill tree type
    static IndexedString GetTreeType()
    {
        return IndexedString(SkillTreeType(SkillTreeType::Crafting)._to_string());
    }

    // Recipes
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(Recipes, RecipeList);
};

// Typedef
MAKE_TYPE_TYPEDEFS(SkillDataCrafting);

// JSON Converters
void to_json(Json& jsonData, const SkillDataCrafting& obj);
void from_json(const Json& jsonData, SkillDataCrafting& obj);
MAKE_JSON_GENERIC_TYPE_CONVERTERS_DECL(SkillDataCrafting, SkillDataCrafting);

};

#endif
