// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

#ifndef _GECKO_SKILLDATA_COMBAT_H_
#define _GECKO_SKILLDATA_COMBAT_H_

// Internal includes
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

    // Destructor
    virtual ~SkillDataCombat();

    // Clear all data
    virtual void Clear() override;

    // Skill tree type
    static String GetTreeType()
    {
        return String(SkillTreeType(SkillTreeType::Combat)._to_string());
    }

    // Create combat action
    CharacterActionArray CreateCombatActions(const String& sCharacterID, const String& sWeaponSet) const;
};

// Typedef
MAKE_COMMON_TYPEDEFS(SkillDataCombat);

// JSON Converters
void to_json(Json& jsonData, const SkillDataCombat& obj);
void from_json(const Json& jsonData, SkillDataCombat& obj);

};

#endif
