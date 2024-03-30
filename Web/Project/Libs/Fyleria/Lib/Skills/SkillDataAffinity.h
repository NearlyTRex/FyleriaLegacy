// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#ifndef _GECKO_SKILLDATA_AFFINITY_H_
#define _GECKO_SKILLDATA_AFFINITY_H_

#include "Skills/SkillData.h"
#include "Skills/SkillTypes.h"

namespace Gecko
{

class SkillDataAffinity : public SkillData
{
public:

    // Constructors
    SkillDataAffinity();
    SkillDataAffinity(const Json& jsonData);

    // Skill tree type
    static IndexedString GetTreeType()
    {
        return IndexedString(SkillTreeType(SkillTreeType::Affinity)._to_string());
    }
};

// Typedef
MAKE_TYPE_TYPEDEFS(SkillDataAffinity);

// JSON Converters
void to_json(Json& jsonData, const SkillDataAffinity& obj);
void from_json(const Json& jsonData, SkillDataAffinity& obj);
MAKE_JSON_GENERIC_TYPE_CONVERTERS_DECL(SkillDataAffinity, SkillDataAffinity);

};

#endif
