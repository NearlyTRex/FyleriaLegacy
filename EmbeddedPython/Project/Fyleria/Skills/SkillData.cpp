// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

// Internal includes
#include "Skills/SkillData.h"
#include "CharacterAction/CharacterAction.h"
#include "Character/CharacterManager.h"
#include "CharacterParty/CharacterPartyManager.h"
#include "Utility/Templates.h"

namespace Gecko
{

SkillData::SkillData()
{
}

SkillData::SkillData(const Json& jsonData)
{
    from_json(jsonData, *this);
}

SkillData::~SkillData()
{
}

void SkillData::Clear()
{
    // Run types
    SetRunTypes({});

    // Data class
    SetDataClass("");

    // Skill rank
    SetSkillRank(0);

    // Skill name
    SetSkillName("");

    // Skill description
    SetSkillDescription("");

    // Skill type
    SetSkillType("");

    // Skill costs
    SetSkillCostAP(0);
    SetSkillCostHP(0);

    // Skill index
    SetSkillTreeIndex({});

    // Stat changes
    SetStatChanges({});
}

Bool SkillData::IsActionable() const
{
    // First check that all the necessary information is filled out
    if(GetRunTypes().empty() ||
       GetDataClass().empty() ||
       GetSkillName().empty() ||
       GetSkillDescription().empty() ||
       GetSkillType().empty())
    {
        return false;
    }

    // Check special case for base attacks
    if(GetSkillRank() == 0)
    {
        return true;
    }

    // Check costs
    if(GetSkillCostAP() > 0 ||
       GetSkillCostHP() > 0)
    {
        return true;
    }
    return false;
}

void SkillData::GetNumberOfAttackAndDefendRequirements(Int& iAttacks, Int& iDefends) const
{
    for(const StatChange& change : GetStatChanges())
    {
        iAttacks += (change.DoesHaveAttackRequirements()) ? 1 : 0;
        iDefends += (change.DoesHaveDefendRequirements()) ? 1 : 0;
    }
}

Bool SkillData::DoesHaveOnlyAttackRequirements() const
{
    Int iAttacks = 0;
    Int iDefends = 0;
    GetNumberOfAttackAndDefendRequirements(iAttacks, iDefends);
    return (iAttacks > 0 && iDefends == 0);
}

Bool SkillData::DoesHaveOnlyDefendRequirements() const
{
    Int iAttacks = 0;
    Int iDefends = 0;
    GetNumberOfAttackAndDefendRequirements(iAttacks, iDefends);
    return (iAttacks == 0 && iDefends > 0);
}

Bool SkillData::GetIntersectingRequirementTypes(
    const StringArray& vPrimaryActionTypes,
    const StringArray& vSecondaryActionTypes,
    StringArray& vPrimaryAttackIntersections,
    StringArray& vPrimaryDefendIntersections,
    StringArray& vSecondaryAttackIntersections,
    StringArray& vSecondaryDefendIntersections) const
{
    // Get intersections
    for(const StatChange& change : GetStatChanges())
    {
        if(change.DoesHaveAttackRequirements() && !vPrimaryActionTypes.empty())
        {
            StringArray vIntersect = change.GetIntersectingAttackRequirements(vPrimaryActionTypes);
            vPrimaryAttackIntersections.insert(vPrimaryAttackIntersections.end(), vIntersect.begin(), vIntersect.end());
        }
        if(change.DoesHaveAttackRequirements() && !vSecondaryActionTypes.empty())
        {
            StringArray vIntersect = change.GetIntersectingAttackRequirements(vSecondaryActionTypes);
            vSecondaryAttackIntersections.insert(vSecondaryAttackIntersections.end(), vIntersect.begin(), vIntersect.end());
        }
        if(change.DoesHaveDefendRequirements() && !vPrimaryActionTypes.empty())
        {
            StringArray vIntersect = change.GetIntersectingDefendRequirements(vPrimaryActionTypes);
            vPrimaryDefendIntersections.insert(vPrimaryDefendIntersections.end(), vIntersect.begin(), vIntersect.end());
        }
        if(change.DoesHaveDefendRequirements() && !vSecondaryActionTypes.empty())
        {
            StringArray vIntersect = change.GetIntersectingDefendRequirements(vSecondaryActionTypes);
            vSecondaryDefendIntersections.insert(vSecondaryDefendIntersections.end(), vIntersect.begin(), vIntersect.end());
        }
    }

    // Remove duplicates
    RemoveVectorDuplicates<String>(vPrimaryAttackIntersections);
    RemoveVectorDuplicates<String>(vPrimaryDefendIntersections);
    RemoveVectorDuplicates<String>(vSecondaryAttackIntersections);
    RemoveVectorDuplicates<String>(vSecondaryDefendIntersections);

    // Return true if at least one of them is not empty
    return (
        !vPrimaryAttackIntersections.empty() ||
        !vPrimaryDefendIntersections.empty() ||
        !vSecondaryAttackIntersections.empty() ||
        !vSecondaryDefendIntersections.empty()
    );
}

Bool SkillData::DoesMeetActionRequirements(const String& sCharacterID, const String& sWeaponSet) const
{
    // Check character
    if(!CharacterManager::GetInstance()->DoesCharacterExist(sCharacterID))
    {
        return false;
    }

    // Get character
    const Character& character = CharacterManager::GetInstance()->GetCharacter(sCharacterID);
    if(character.GetPartyID().empty())
    {
        return false;
    }

    // Get party
    const CharacterParty& party = CharacterPartyManager::GetInstance()->GetPartyByID(character.GetPartyID());
    const CharacterPartyMember& partyMember = party.GetMemberByID(sCharacterID);

    // Get action types
    TreeIndex primaryItemIndex;
    TreeIndex secondaryItemIndex;
    StringArray vPrimaryActionTypes;
    StringArray vSecondaryActionTypes;
    if(!partyMember.GetHandInfoByWeaponSet(sWeaponSet,
        primaryItemIndex,
        secondaryItemIndex,
        vPrimaryActionTypes,
        vSecondaryActionTypes))
    {
        return false;
    }

    // Check each of the stat changes against the equipped items and their action types
    for(const StatChange& change : GetStatChanges())
    {
        if(change.DoesHaveItemEquippedRequirements())
        {
            return change.DoesMeetItemEquippedRequirements(sCharacterID, sWeaponSet);
        }
        else if(change.DoesHaveAttackRequirements() && !vPrimaryActionTypes.empty())
        {
            return change.DoesMeetAttackRequirements(vPrimaryActionTypes);
        }
        else if(change.DoesHaveAttackRequirements() && !vSecondaryActionTypes.empty())
        {
            return change.DoesMeetAttackRequirements(vSecondaryActionTypes);
        }
    }
    return false;
}

CharacterActionArray SkillData::CreateBaseActions(const String& sCharacterID, const String& sWeaponSet) const
{
    // Check character
    CharacterActionArray vNewActions;
    if(!CharacterManager::GetInstance()->DoesCharacterExist(sCharacterID))
    {
        return vNewActions;
    }

    // Get character
    const Character& character = CharacterManager::GetInstance()->GetCharacter(sCharacterID);

    // Create actions
    for(auto& sType : GetRunTypes())
    {
        CharacterAction newAction;
        newAction.SetRunType(sType);
        newAction.SetCostAP(GetSkillCostAP());
        newAction.SetCostHP(GetSkillCostHP());
        newAction.SetWeaponSet(sWeaponSet);
        newAction.SetSkillTreeIndex(GetSkillTreeIndex());
        newAction.SetSourceTargetType(character.GetCharacterTargetType());
        newAction.SetSourceCharacterID(sCharacterID);
        vNewActions.push_back(newAction);
    }
    return vNewActions;
}

void to_json(Json& jsonData, const SkillData& obj)
{
    // Run types
    SET_JSON_DATA(RunTypes);

    // Data class
    SET_JSON_DATA(DataClass);

    // Skill rank
    SET_JSON_DATA(SkillRank);

    // Skill name
    SET_JSON_DATA(SkillName);

    // Skill description
    SET_JSON_DATA(SkillDescription);

    // Skill type
    SET_JSON_DATA(SkillType);

    // Skill costs
    SET_JSON_DATA(SkillCostAP);
    SET_JSON_DATA(SkillCostHP);

    // Skill index
    SET_JSON_DATA(SkillTreeIndex);

    // Stat changes
    SET_JSON_DATA(StatChanges);
}

void from_json(const Json& jsonData, SkillData& obj)
{
    // Run types
    SET_OBJ_DATA(RunTypes, StringArray);

    // Data class
    SET_OBJ_DATA(DataClass, String);

    // Skill rank
    SET_OBJ_DATA(SkillRank, Int);

    // Skill name
    SET_OBJ_DATA(SkillName, String);

    // Skill description
    SET_OBJ_DATA(SkillDescription, String);

    // Skill type
    SET_OBJ_DATA(SkillType, String);

    // Skill costs
    SET_OBJ_DATA(SkillCostAP, Int);
    SET_OBJ_DATA(SkillCostHP, Int);

    // Skill index
    SET_OBJ_DATA(SkillTreeIndex, TreeIndex);

    // Stat changes
    SET_OBJ_DATA(StatChanges, StatChangeArray);
}

};
