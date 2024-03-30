// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

#ifndef _GECKO_SKILLDATA_ALCHEMY_H_
#define _GECKO_SKILLDATA_ALCHEMY_H_

// Internal includes
#include "Skills/SkillData.h"
#include "Skills/SkillTypes.h"
#include "Recipes/Recipe.h"

namespace Gecko
{

class SkillDataAlchemy : public SkillData
{
public:

    // Constructors
    SkillDataAlchemy();
    SkillDataAlchemy(const Json& jsonData);

    // Destructor
    virtual ~SkillDataAlchemy();

    // Clear all data
    virtual void Clear() override;

    // Skill tree type
    static String GetTreeType()
    {
        return String(SkillTreeType(SkillTreeType::Alchemy)._to_string());
    }

    // Recipes
    MAKE_RAW_TYPE_ACCESSORS(Recipes, RecipeArray);
};

// Typedef
MAKE_COMMON_TYPEDEFS(SkillDataAlchemy);

// JSON Converters
void to_json(Json& jsonData, const SkillDataAlchemy& obj);
void from_json(const Json& jsonData, SkillDataAlchemy& obj);

};

#endif
