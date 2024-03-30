// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

#ifndef _GECKO_SKILLDATA_BREAKDOWN_H_
#define _GECKO_SKILLDATA_BREAKDOWN_H_

// Internal includes
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

    // Destructor
    virtual ~SkillDataBreakdown();

    // Clear all data
    virtual void Clear() override;

    // Skill tree type
    static String GetTreeType()
    {
        return String(SkillTreeType(SkillTreeType::Breakdown)._to_string());
    }

    // Recipes
    MAKE_RAW_TYPE_ACCESSORS(Recipes, RecipeArray);
};

// Typedef
MAKE_COMMON_TYPEDEFS(SkillDataBreakdown);

// JSON Converters
void to_json(Json& jsonData, const SkillDataBreakdown& obj);
void from_json(const Json& jsonData, SkillDataBreakdown& obj);

};

#endif
