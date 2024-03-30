// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#include "Skills/SkillData.h"
#include "Character/CharacterActionBattleSkill.h"
#include "Character/CharacterActionFieldSkill.h"
#include "Character/CharacterManager.h"

namespace Gecko
{

SkillData::SkillData()
{
    // Run types
    SetRunTypes({});

    // Data class
    SetDataClass(IndexedString(""));

    // Skill rank
    SetSkillRank(0);

    // Skill name
    SetSkillName(IndexedString(""));

    // Skill description
    SetSkillDescription(IndexedString(""));

    // Skill type
    SetSkillType(IndexedString("None"));

    // Skill costs
    SetSkillCostAP(0);
    SetSkillCostHP(0);

    // Skill index
    SetSkillTreeIndex({});

    // Stat changes
    SetStatChanges({});
}

SkillData::SkillData(const Json& jsonData)
{
    from_json(jsonData, *this);
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
    const IndexedStringList& vPrimaryActionTypes,
    const IndexedStringList& vSecondaryActionTypes,
    IndexedStringList& vPrimaryAttackIntersections,
    IndexedStringList& vPrimaryDefendIntersections,
    IndexedStringList& vSecondaryAttackIntersections,
    IndexedStringList& vSecondaryDefendIntersections) const
{
    // Get intersections
    for(const StatChange& change : GetStatChanges())
    {
        if(change.DoesHaveAttackRequirements() && !vPrimaryActionTypes.empty())
        {
            IndexedStringList vIntersect = change.GetIntersectingAttackRequirements(vPrimaryActionTypes);
            vPrimaryAttackIntersections.insert(vPrimaryAttackIntersections.end(), vIntersect.begin(), vIntersect.end());
        }
        if(change.DoesHaveAttackRequirements() && !vSecondaryActionTypes.empty())
        {
            IndexedStringList vIntersect = change.GetIntersectingAttackRequirements(vSecondaryActionTypes);
            vSecondaryAttackIntersections.insert(vSecondaryAttackIntersections.end(), vIntersect.begin(), vIntersect.end());
        }
        if(change.DoesHaveDefendRequirements() && !vPrimaryActionTypes.empty())
        {
            IndexedStringList vIntersect = change.GetIntersectingDefendRequirements(vPrimaryActionTypes);
            vPrimaryDefendIntersections.insert(vPrimaryDefendIntersections.end(), vIntersect.begin(), vIntersect.end());
        }
        if(change.DoesHaveDefendRequirements() && !vSecondaryActionTypes.empty())
        {
            IndexedStringList vIntersect = change.GetIntersectingDefendRequirements(vSecondaryActionTypes);
            vSecondaryDefendIntersections.insert(vSecondaryDefendIntersections.end(), vIntersect.begin(), vIntersect.end());
        }
    }

    // Remove duplicates
    STDVectorRemoveDuplicates<IndexedString>(vPrimaryAttackIntersections);
    STDVectorRemoveDuplicates<IndexedString>(vPrimaryDefendIntersections);
    STDVectorRemoveDuplicates<IndexedString>(vSecondaryAttackIntersections);
    STDVectorRemoveDuplicates<IndexedString>(vSecondaryDefendIntersections);

    // Return true if at least one of them is not empty
    return (
        !vPrimaryAttackIntersections.empty() ||
        !vPrimaryDefendIntersections.empty() ||
        !vSecondaryAttackIntersections.empty() ||
        !vSecondaryDefendIntersections.empty()
    );
}

Bool SkillData::DoesMeetActionRequirements(const IndexedString& sCharacterID, const IndexedString& sWeaponSet) const
{
    // Check character
    if(!CharacterManager::GetInstance()->DoesCharacterExist(sCharacterID))
    {
        return false;
    }

    // Get character
    const Character& character = CharacterManager::GetInstance()->GetCharacter(sCharacterID);

    // Get action types
    TreeIndex primaryItemIndex;
    TreeIndex secondaryItemIndex;
    IndexedStringList vPrimaryActionTypes;
    IndexedStringList vSecondaryActionTypes;
    if(!character.GetHandInfoByWeaponSet(sWeaponSet,
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

CharacterActionSharedPtrList SkillData::CreateBaseActions(const IndexedString& sCharacterID, const IndexedString& sWeaponSet) const
{
    // Check character
    CharacterActionSharedPtrList vNewActions;
    if(!CharacterManager::GetInstance()->DoesCharacterExist(sCharacterID))
    {
        return vNewActions;
    }

    // Get character
    const Character& character = CharacterManager::GetInstance()->GetCharacter(sCharacterID);

    // Create actions
    for(auto& sType : GetRunTypes())
    {
        CharacterActionSharedPtr pNewAction;
        const CharacterActionRunType eRunType = StringToCharacterActionRunType(sType);
        switch(eRunType)
        {
            case CharacterActionRunType::Battle:
                pNewAction = STDMakeSharedPtr<CharacterActionBattleSkill>();
                break;
            case CharacterActionRunType::Field:
                pNewAction = STDMakeSharedPtr<CharacterActionFieldSkill>();
                break;
            default:
                break;
        }
        if(pNewAction)
        {
            pNewAction->SetCostAP(GetSkillCostAP());
            pNewAction->SetCostHP(GetSkillCostHP());
            pNewAction->SetWeaponSet(sWeaponSet);
            pNewAction->SetSkillTreeIndex(GetSkillTreeIndex());
            pNewAction->SetSourceTargetType(character.GetCharacterTargetType());
            pNewAction->SetSourceCharacterID(sCharacterID);
            vNewActions.push_back(pNewAction);
        }
    }
    return vNewActions;
}

void to_json(Json& jsonData, const SkillData& obj)
{
    // Run types
    SET_JSON_DATA_IF_NOT_EMPTY(RunTypes);

    // Data class
    SET_JSON_DATA_IF_NOT_DEFAULT(DataClass, IndexedString(""));

    // Skill rank
    SET_JSON_DATA_IF_NOT_DEFAULT(SkillRank, 0);

    // Skill name
    SET_JSON_DATA_IF_NOT_DEFAULT(SkillName, IndexedString(""));

    // Skill description
    SET_JSON_DATA_IF_NOT_DEFAULT(SkillDescription, IndexedString(""));

    // Skill type
    SET_JSON_DATA_IF_NOT_DEFAULT(SkillType, IndexedString("None"));

    // Skill costs
    SET_JSON_DATA_IF_NOT_DEFAULT(SkillCostAP, 0);
    SET_JSON_DATA_IF_NOT_DEFAULT(SkillCostHP, 0);

    // Skill index
    SET_JSON_DATA_IF_NOT_DEFAULT(SkillTreeIndex, TreeIndex());

    // Stat changes
    SET_JSON_DATA_IF_NOT_EMPTY(StatChanges);
}

void from_json(const Json& jsonData, SkillData& obj)
{
    // Run types
    obj.SetRunTypes(GET_JSON_DATA_OR_DEFAULT(RunTypes, IndexedStringList, IndexedStringList()));

    // Data class
    obj.SetDataClass(GET_JSON_DATA_OR_DEFAULT(DataClass, IndexedString, IndexedString("")));

    // Skill rank
    obj.SetSkillRank(GET_JSON_DATA_OR_DEFAULT(SkillRank, Int, 0));

    // Skill name
    obj.SetSkillName(GET_JSON_DATA_OR_DEFAULT(SkillName, IndexedString, IndexedString("")));

    // Skill description
    obj.SetSkillDescription(GET_JSON_DATA_OR_DEFAULT(SkillDescription, IndexedString, IndexedString("")));

    // Skill type
    obj.SetSkillType(GET_JSON_DATA_OR_DEFAULT(SkillType, IndexedString, IndexedString("None")));

    // Skill costs
    obj.SetSkillCostAP(GET_JSON_DATA_OR_DEFAULT(SkillCostAP, Int, 0));
    obj.SetSkillCostHP(GET_JSON_DATA_OR_DEFAULT(SkillCostHP, Int, 0));

    // Skill index
    obj.SetSkillTreeIndex(GET_JSON_DATA_OR_DEFAULT(SkillTreeIndex, TreeIndex, TreeIndex()));

    // Stat changes
    obj.SetStatChanges(GET_JSON_DATA_OR_DEFAULT(StatChanges, StatChangeList, StatChangeList()));
}

};
