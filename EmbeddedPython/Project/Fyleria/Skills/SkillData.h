// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

#ifndef _GECKO_SKILLDATA_H_
#define _GECKO_SKILLDATA_H_

// Internal includes
#include "CharacterAction/CharacterAction.h"
#include "Stats/StatChange.h"
#include "Utility/Macros.h"
#include "Utility/Enum.h"
#include "Utility/Json.h"

namespace Gecko
{

class SkillData
{
public:

    // Constructors
    SkillData();
    SkillData(const Json& jsonData);

    // Destructor
    virtual ~SkillData();

    // Clear all data
    virtual void Clear();

    // Is actionable
    Bool IsActionable() const;

    // Get number of attack/defend requirements
    void GetNumberOfAttackAndDefendRequirements(Int& iAttacks, Int& iDefends) const;

    // Determine if this has only attack requirements
    Bool DoesHaveOnlyAttackRequirements() const;

    // Determine if this has only defend requirements
    Bool DoesHaveOnlyDefendRequirements() const;

    // Get intersecting attack requirements
    Bool GetIntersectingRequirementTypes(
        const StringArray& vPrimaryActionTypes,
        const StringArray& vSecondaryActionTypes,
        StringArray& vPrimaryAttackIntersections,
        StringArray& vPrimaryDefendIntersections,
        StringArray& vSecondaryAttackIntersections,
        StringArray& vSecondaryDefendIntersections) const;

    // Does meet action requirements
    Bool DoesMeetActionRequirements(const String& sCharacterID, const String& sWeaponSet) const;

    // Create base character action
    CharacterActionArray CreateBaseActions(const String& sCharacterID, const String& sWeaponSet) const;

    // Run types
    MAKE_RAW_TYPE_ACCESSORS(RunTypes, StringArray);

    // Data class
    MAKE_RAW_TYPE_ACCESSORS(DataClass, String);

    // Skill rank
    MAKE_RAW_TYPE_ACCESSORS(SkillRank, UByte);

    // Skill name
    MAKE_RAW_TYPE_ACCESSORS(SkillName, String);

    // Skill description
    MAKE_RAW_TYPE_ACCESSORS(SkillDescription, String);

    // Skill type
    MAKE_RAW_TYPE_ACCESSORS(SkillType, String);

    // Skill costs
    MAKE_RAW_TYPE_ACCESSORS(SkillCostAP, UByte);
    MAKE_RAW_TYPE_ACCESSORS(SkillCostHP, UByte);

    // Skill index
    MAKE_RAW_TYPE_ACCESSORS(SkillTreeIndex, TreeIndex);

    // Stat changes
    MAKE_RAW_TYPE_ACCESSORS(StatChanges, StatChangeArray);
};

// Typedef
MAKE_COMMON_TYPEDEFS(SkillData);

// JSON Converters
void to_json(Json& jsonData, const SkillData& obj);
void from_json(const Json& jsonData, SkillData& obj);

};

#endif
