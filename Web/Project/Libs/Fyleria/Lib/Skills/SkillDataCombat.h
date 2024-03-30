// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#ifndef _GECKO_SKILLDATA_COMBAT_H_
#define _GECKO_SKILLDATA_COMBAT_H_

#include "Skills/SkillData.h"
#include "Skills/SkillTypes.h"

namespace Gecko
{

class SkillDataCombat : public SkillData
{
public:

    // Constructors
    SkillDataCombat();
    SkillDataCombat(const Json& jsonData);

    // Skill tree type
    static IndexedString GetTreeType()
    {
        return IndexedString(SkillTreeType(SkillTreeType::Combat)._to_string());
    }

    // Create combat action
    CharacterActionSharedPtrList CreateCombatActions(const IndexedString& sCharacterID, const IndexedString& sWeaponSet) const;
};

// Typedef
MAKE_TYPE_TYPEDEFS(SkillDataCombat);

// JSON Converters
void to_json(Json& jsonData, const SkillDataCombat& obj);
void from_json(const Json& jsonData, SkillDataCombat& obj);
MAKE_JSON_GENERIC_TYPE_CONVERTERS_DECL(SkillDataCombat, SkillDataCombat);

};

#endif
