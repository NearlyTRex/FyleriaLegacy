// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#include "Skills/SkillDataCombat.h"
#include "Character/CharacterManager.h"
#include "Character/CharacterTypes.h"

namespace Gecko
{

SkillDataCombat::SkillDataCombat()
    : SkillData()
{
}

SkillDataCombat::SkillDataCombat(const Json& jsonData)
    : SkillData(jsonData)
{
    from_json(jsonData, *this);
}

CharacterActionSharedPtrList SkillDataCombat::CreateCombatActions(const IndexedString& sCharacterID, const IndexedString& sWeaponSet) const
{
    // Check character
    CharacterActionSharedPtrList vNewActions;
    if(!CharacterManager::GetInstance()->DoesCharacterExist(sCharacterID))
    {
        return vNewActions;
    }

    // Get character
    const Character& character = CharacterManager::GetInstance()->GetCharacter(sCharacterID);

    // Get equipped item information
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
        return vNewActions;
    }

    // Get item types
    IndexedString sPrimaryItemType = RetrieveItemType(primaryItemIndex);
    IndexedString sSecondaryItemType = RetrieveItemType(secondaryItemIndex);
    IndexedString sPrimaryItemActionType = ConvertItemTypeToCharacterActionType(sPrimaryItemType);
    IndexedString sSecondaryItemActionType = ConvertItemTypeToCharacterActionType(sSecondaryItemType);
    if(sPrimaryItemActionType.IsNone() && sSecondaryItemActionType.IsNone())
    {
        return vNewActions;
    }

    // Setup new actions
    for(auto& pNewAction : CreateBaseActions(sCharacterID, sWeaponSet))
    {
        // Skip invalid base actions
        if(!pNewAction)
        {
            continue;
        }

        // For twin attack, we need to make sure to mark that the actual
        // destination targets are identical
        if(GetDataClass() == IndexedString("TwinAttack"))
        {
            pNewAction->SetAreDestinationTargetsIdentical(true);
        }

        // Ambidextrous - Twin Attack
        // Ambidextrous - Split Focus
        // Attack two targets with both primary and secondary weapons
        if(GetDataClass() == IndexedString("TwinAttack") ||
           GetDataClass() == IndexedString("SplitFocus"))
        {
            // Create primary entry
            CharacterActionEntry newEntryPrimary;
            newEntryPrimary.SetActionTypes({sPrimaryItemActionType});
            newEntryPrimary.SetHandType(IndexedString("Primary"));
            pNewAction->GetActionEntries().push_back(newEntryPrimary);

            // Create secondary entry
            CharacterActionEntry newEntrySecondary;
            newEntrySecondary.SetActionTypes({sSecondaryItemActionType});
            newEntrySecondary.SetHandType(IndexedString("Secondary"));
            pNewAction->GetActionEntries().push_back(newEntrySecondary);
        }

        // Focused - Focused Strike
        // Focused - Deadly Retribution
        // Attack a single target with primary or secondary weapon, whichever one is equipped
        else if(GetDataClass() == IndexedString("FocusedStrike") ||
                GetDataClass() == IndexedString("DeadlyRetribution"))
        {
            // Create entry
            CharacterActionEntry newEntry;
            Bool bUsePrimary = (!sPrimaryItemActionType.IsNone());
            IndexedString sActionTypeToUse = (bUsePrimary) ? sPrimaryItemActionType : sSecondaryItemActionType;
            IndexedString sHandTypeToUse = (bUsePrimary) ? IndexedString("Primary") : IndexedString("Secondary");
            newEntry.SetActionTypes({sActionTypeToUse});
            newEntry.SetHandType(sHandTypeToUse);
            pNewAction->GetActionEntries().push_back(newEntry);
        }

        // Stalwart - Shield Punch
        // Stalwart - Shield Charge
        // Attack a single target with primary or secondary shield, whichever one is the shield
        else if(GetDataClass() == IndexedString("ShieldPunch") ||
                GetDataClass() == IndexedString("ShieldCharge"))
        {
            // Create entry
            CharacterActionEntry newEntry;
            Bool bUsePrimary = (!sPrimaryItemActionType.IsNone() && IsItemShield(primaryItemIndex));
            IndexedString sActionTypeToUse = (bUsePrimary) ? sPrimaryItemActionType : sSecondaryItemActionType;
            IndexedString sHandTypeToUse = (bUsePrimary) ? IndexedString("Primary") : IndexedString("Secondary");
            newEntry.SetActionTypes({sActionTypeToUse});
            newEntry.SetHandType(sHandTypeToUse);
            newEntry.SetIsHandTypeShield(true);
            pNewAction->GetActionEntries().push_back(newEntry);
        }

        // Add new action
        if(!pNewAction->GetActionEntries().empty())
        {
            vNewActions.push_back(pNewAction);
        }
    }
    return vNewActions;
}

void to_json(Json& jsonData, const SkillDataCombat& obj)
{
}

void from_json(const Json& jsonData, SkillDataCombat& obj)
{
}

MAKE_JSON_GENERIC_TYPE_CONVERTERS_IMPL(SkillDataCombat, SkillDataCombat);

};
