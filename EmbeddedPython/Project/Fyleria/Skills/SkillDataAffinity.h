// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

#ifndef _GECKO_SKILLDATA_AFFINITY_H_
#define _GECKO_SKILLDATA_AFFINITY_H_

// Internal includes
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

    // Destructor
    virtual ~SkillDataAffinity();

    // Clear all data
    virtual void Clear() override;

    // Skill tree type
    static String GetTreeType()
    {
        return String(SkillTreeType(SkillTreeType::Affinity)._to_string());
    }
};

// Typedef
MAKE_COMMON_TYPEDEFS(SkillDataAffinity);

// JSON Converters
void to_json(Json& jsonData, const SkillDataAffinity& obj);
void from_json(const Json& jsonData, SkillDataAffinity& obj);

};

#endif
