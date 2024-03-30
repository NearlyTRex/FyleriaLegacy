// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#ifndef _GECKO_SKILLDATA_BREAKDOWN_H_
#define _GECKO_SKILLDATA_BREAKDOWN_H_

#include "Skills/SkillData.h"
#include "Skills/SkillTypes.h"
#include "Recipes/Recipe.h"

namespace Gecko
{

class SkillDataBreakdown : public SkillData
{
public:

    // Constructors
    SkillDataBreakdown();
    SkillDataBreakdown(const Json& jsonData);

    // Skill tree type
    static IndexedString GetTreeType()
    {
        return IndexedString(SkillTreeType(SkillTreeType::Breakdown)._to_string());
    }

    // Recipes
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(Recipes, RecipeList);
};

// Typedef
MAKE_TYPE_TYPEDEFS(SkillDataBreakdown);

// JSON Converters
void to_json(Json& jsonData, const SkillDataBreakdown& obj);
void from_json(const Json& jsonData, SkillDataBreakdown& obj);
MAKE_JSON_GENERIC_TYPE_CONVERTERS_DECL(SkillDataBreakdown, SkillDataBreakdown);

};

#endif
