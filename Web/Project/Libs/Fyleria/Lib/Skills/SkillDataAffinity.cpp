// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#include "Skills/SkillDataAffinity.h"

namespace Gecko
{

SkillDataAffinity::SkillDataAffinity()
    : SkillData()
{
}

SkillDataAffinity::SkillDataAffinity(const Json& jsonData)
    : SkillData(jsonData)
{
    from_json(jsonData, *this);
}

void to_json(Json& jsonData, const SkillDataAffinity& obj)
{
}

void from_json(const Json& jsonData, SkillDataAffinity& obj)
{
}

MAKE_JSON_GENERIC_TYPE_CONVERTERS_IMPL(SkillDataAffinity, SkillDataAffinity);

};
