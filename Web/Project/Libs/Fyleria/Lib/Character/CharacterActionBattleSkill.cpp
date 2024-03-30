// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#include "Character/CharacterActionBattleSkill.h"
#include "Character/CharacterManager.h"
#include "Character/CharacterPartyManager.h"
#include "Utility/Constants.h"

namespace Gecko
{

CharacterActionBattleSkill::CharacterActionBattleSkill()
    : CharacterAction()
{
    SetTypeName("CharacterActionBattleSkill");
}

CharacterActionBattleSkill::CharacterActionBattleSkill(const Json& jsonData)
    : CharacterAction(jsonData)
{
    from_json(jsonData, *this);
}

CharacterActionResult CharacterActionBattleSkill::GetSkillAttackResult(const CharacterActionEntry& entry) const
{
    // Action result
    CharacterActionResult result;

    // Get character data
    const IndexedString& sSourceCharID = GetSourceCharacterID();
    const IndexedString& sDestCharID = entry.GetDestinationCharacterID();
    const Character& sourceCharacter = CharacterManager::GetInstance()->GetCharacter(sSourceCharID);
    const Character& destCharacter = CharacterManager::GetInstance()->GetCharacter(sDestCharID);
    STDSharedPtr<const CharacterBattleData> pSourceBattleData = sourceCharacter.GetBattleDataActives();
    STDSharedPtr<const CharacterBattleData> pDestBattleData = destCharacter.GetBattleDataActives();
    STDSharedPtr<const CharacterProgressData> pSourceProgressData = sourceCharacter.GetProgressDataActives();
    if(!pSourceBattleData || !pDestBattleData || !pSourceProgressData)
    {
        return result;
    }

    // Gather critical/multiple hit info
    const Float fSourceChanceToCauseCriticalHit = pSourceBattleData->GetChanceToCauseCriticalHit();
    const Float fSourceChanceToApplyMultipleAttacks = pSourceBattleData->GetChanceToApplyMultipleAttacks();
    //const Float fSourceCriticalHitMultiplier = pSourceBattleData->GetCriticalHitMultiplier();
    const Float fSourceAttacksMultiplier = pSourceBattleData->GetAttacksMultiplier();
    const Float fDestChanceToBlockCriticalHit = pDestBattleData->GetChanceToBlockCriticalHit();

    // Get hand info
    const CharacterHandType eHandType = StringToCharacterHandType(entry.GetHandType());
    Bool bIsPrimaryHandAction = (eHandType == +CharacterHandType::Primary);
    Bool bIsSecondaryHandAction = (eHandType == +CharacterHandType::Secondary);
    Bool bIsShield = entry.GetIsHandTypeShield();

    // Gather source ratings
    Float fPrimaryBlunt = 0;
    Float fPrimaryPierce = 0;
    Float fPrimarySlash = 0;
    Float fSecondaryBlunt = 0;
    Float fSecondaryPierce = 0;
    Float fSecondarySlash = 0;
    const IndexedString& sHandedness = sourceCharacter.GetHandedness();
    if(bIsPrimaryHandAction && !bIsShield) { pSourceBattleData->GetPrimaryWeaponRatings(sHandedness, fPrimaryBlunt, fPrimaryPierce, fPrimarySlash); }
    if(bIsPrimaryHandAction && bIsShield) { pSourceBattleData->GetPrimaryShieldRatings(sHandedness, fPrimaryBlunt, fPrimaryPierce, fPrimarySlash); }
    if(bIsSecondaryHandAction && !bIsShield) { pSourceBattleData->GetSecondaryWeaponRatings(sHandedness, fSecondaryBlunt, fSecondaryPierce, fSecondarySlash); }
    if(bIsSecondaryHandAction && bIsShield) { pSourceBattleData->GetSecondaryShieldRatings(sHandedness, fSecondaryBlunt, fSecondaryPierce, fSecondarySlash); }

    // Gather damage bonus values
    const Float fSourcePrimaryDamageBonusValue = (bIsPrimaryHandAction) ? pSourceBattleData->GetWeaponPrimaryDamageBonusValue() : 0;
    const Float fSourcePrimaryDamageBonusPercent = (bIsPrimaryHandAction) ? pSourceBattleData->GetWeaponPrimaryDamageBonusPercent() : 1;
    const Float fSourceSecondaryDamageBonusValue = (bIsSecondaryHandAction) ? pSourceBattleData->GetWeaponSecondaryDamageBonusValue() : 0;
    const Float fSourceSecondaryDamageBonusPercent = (bIsSecondaryHandAction) ? pSourceBattleData->GetWeaponSecondaryDamageBonusPercent() : 1;
    const Float fGeneralDamageBonusValue = pSourceBattleData->GetGeneralDamageBonusValue();
    const Float fGeneralDamageBonusPercent = pSourceBattleData->GetGeneralDamageBonusPercent();

    // Add in primary/secondary damage bonuses
    Float fSourceBlunt = 0;
    //Float fSourcePierce = 0;
    Float fSourceSlash = 0;
    if(bIsPrimaryHandAction)
    {
        fSourceBlunt = (fPrimaryBlunt * fSourcePrimaryDamageBonusPercent) + fSourcePrimaryDamageBonusValue;
        //fSourcePierce = (fPrimaryPierce * fSourcePrimaryDamageBonusPercent) + fSourcePrimaryDamageBonusValue;
        fSourceSlash = (fPrimarySlash * fSourcePrimaryDamageBonusPercent) + fSourcePrimaryDamageBonusValue;
    }
    else if(bIsSecondaryHandAction)
    {
        fSourceBlunt = (fSecondaryBlunt * fSourceSecondaryDamageBonusPercent) + fSourceSecondaryDamageBonusValue;
        //fSourcePierce = (fSecondaryPierce * fSourceSecondaryDamageBonusPercent) + fSourceSecondaryDamageBonusValue;
        fSourceSlash = (fSecondarySlash * fSourceSecondaryDamageBonusPercent) + fSourceSecondaryDamageBonusValue;
    }

    // Gather destination armor values
    const Float fDestBlunt = pDestBattleData->GetEquippedArmorBluntRating() +
        pDestBattleData->GetEquippedShieldLeftBluntRating() +
        pDestBattleData->GetEquippedShieldRightBluntRating();
    const Float fDestPierce = pDestBattleData->GetEquippedArmorPierceRating() +
        pDestBattleData->GetEquippedShieldLeftPierceRating() +
        pDestBattleData->GetEquippedShieldRightPierceRating();
    const Float fDestSlash = pDestBattleData->GetEquippedArmorSlashRating() +
        pDestBattleData->GetEquippedShieldLeftSlashRating() +
        pDestBattleData->GetEquippedShieldRightSlashRating();

    // Gather information about the actions requested
    Float fSourceAttackRating = 0;
    Float fDestDefendRating = 0;
    for(const IndexedString& sActionType : entry.GetActionTypes())
    {
        const CharacterActionType eActionType = StringToCharacterActionType(sActionType);
        switch(eActionType)
        {
            case CharacterActionType::WeaponBasePierce:
                fSourceAttackRating = fDestPierce;
                fDestDefendRating = fDestPierce;
                break;
            case CharacterActionType::WeaponBaseBlunt:
                fSourceAttackRating = fSourceBlunt;
                fDestDefendRating = fDestBlunt;
                break;
            case CharacterActionType::WeaponBaseSlash:
                fSourceAttackRating = fSourceSlash;
                fDestDefendRating = fDestSlash;
                break;
            default:
                break;
        }
    }

    // Check rating difference (positive means it was a successful damage)
    Float fSkillRatingDiff = fSourceAttackRating - fDestDefendRating;
    if(fSkillRatingDiff <= 0)
    {
        // If the attack is less than 10% lower than defense, apply 1 damage, otherwise none
        if(fSourceAttackRating <= (fDestDefendRating * s_kfSkillDamageBoundaryPercent))
        {
            // No damage at all
            result.SetHasTargetDefendedSuccessfully(true);
            return result;
        }
        else
        {
            // Default damage
            fSkillRatingDiff = s_kfSkillDamageBoundaryDefaultValue;
        }
    }

    // Determine number of attacks
    Bool bShouldApplyMultipleAttacks = STDDoesChanceSucceed<Float>(fSourceChanceToApplyMultipleAttacks);
    Int iNumAttacks = (bShouldApplyMultipleAttacks) ? (s_kuBaseNumberOfSkillAttacks * fSourceAttacksMultiplier) : s_kuBaseNumberOfSkillAttacks;
    result.SetHaveMultipleAttacksSucceeded(bShouldApplyMultipleAttacks);
    result.SetNumAttacksOnTarget(iNumAttacks);

    // In each attack, calculate the damage
    // This includes critical hits, which can be blocked
    Float fSkillAttackDamage = 0;
    BoolList vCriticalHitOnTarget = result.GetIndividualAttackIsCriticalCausedList();
    BoolList vTargetBlockedCriticalHit = result.GetIndividualAttackIsCriticalBlockedList();
    FloatList vIndividualAttackTargetDamage = result.GetIndividualAttackTargetDamageList();
    for(Int i = 0; i < iNumAttacks; i++)
    {
        // Determine if critical hits will happen
        Bool bCauseCriticalHit = STDDoesChanceSucceed<Float>(fSourceChanceToCauseCriticalHit);
        Bool bBlockCriticalHit = STDDoesChanceSucceed<Float>(fDestChanceToBlockCriticalHit);
        vCriticalHitOnTarget.push_back(bCauseCriticalHit);
        vTargetBlockedCriticalHit.push_back(bBlockCriticalHit);

        // Get damage for this attack
        if(!bCauseCriticalHit)
        {
            fSkillAttackDamage += fSkillRatingDiff;
            vIndividualAttackTargetDamage.push_back(fSkillRatingDiff);
        }
        else if(bCauseCriticalHit && !bBlockCriticalHit)
        {
            fSkillAttackDamage += (fSkillRatingDiff * fSourceAttacksMultiplier);
            vIndividualAttackTargetDamage.push_back(fSkillRatingDiff * fSourceAttacksMultiplier);
        }

    }
    ASSERT_ERROR((vCriticalHitOnTarget.size() == vTargetBlockedCriticalHit.size()) == vIndividualAttackTargetDamage.size());
    result.SetIndividualAttackIsCriticalCausedList(vCriticalHitOnTarget);
    result.SetIndividualAttackIsCriticalBlockedList(vTargetBlockedCriticalHit);
    result.SetIndividualAttackTargetDamageList(vIndividualAttackTargetDamage);

    // Calculate result damage now
    Int iDamage = STDRound((fSkillAttackDamage * fGeneralDamageBonusPercent) + fGeneralDamageBonusValue);
    result.SetFinalDamage(iDamage);
    return result;
}

Bool CharacterActionBattleSkill::Setup()
{
    // Prepare character IDs
    PrepareCharacterIDs();

    // Setup destination characters
    for(const CharacterActionEntry& entry : GetActionEntries())
    {
        Character& destCharacter = CharacterManager::GetInstance()->GetCharacter(entry.GetDestinationCharacterID());
        destCharacter.OnBattleActionDefendSetup(STDGetSharedThis());
    }

    // Setup source character
    Character& sourceCharacter = CharacterManager::GetInstance()->GetCharacter(GetSourceCharacterID());
    sourceCharacter.OnBattleActionAttackSetup(STDGetSharedThis());
    return true;
}

Bool CharacterActionBattleSkill::Finish()
{
    // Check characters
    if(!AreAllCharacterIDsValid())
    {
        return false;
    }

    // Finish destination character actions
    for(const CharacterActionEntry& entry : GetActionEntries())
    {
        Character& destCharacter = CharacterManager::GetInstance()->GetCharacter(entry.GetDestinationCharacterID());
        destCharacter.OnBattleActionFinished(STDGetSharedThis());
    }

    // Finish source character action
    Character& sourceCharacter = CharacterManager::GetInstance()->GetCharacter(GetSourceCharacterID());
    sourceCharacter.OnBattleActionFinished(STDGetSharedThis());
    return true;
}

Bool CharacterActionBattleSkill::GenerateResult()
{
    // Check characters
    if(!AreAllCharacterIDsValid())
    {
        return false;
    }

    // Search action types
    for(CharacterActionEntry& entry : GetActionEntries())
    {
        // Get entry action types
        const IndexedStringList& vActionTypes = entry.GetActionTypes();

        // Skill attack
        if(STDFindData(vActionTypes.begin(), vActionTypes.end(), IndexedString("WeaponBasePierce")) != vActionTypes.end() ||
           STDFindData(vActionTypes.begin(), vActionTypes.end(), IndexedString("WeaponBaseBlunt")) != vActionTypes.end() ||
           STDFindData(vActionTypes.begin(), vActionTypes.end(), IndexedString("WeaponBaseSlash")) != vActionTypes.end())
        {
            entry.SetResult(GetSkillAttackResult(entry));
        }
    }
    return true;
}

Bool CharacterActionBattleSkill::ApplyResult()
{
    // Check characters
    if(!AreAllCharacterIDsValid())
    {
        return false;
    }

    // Look at each entry
    Int iFinalDamage = 0;
    for(const CharacterActionEntry& entry : GetActionEntries())
    {
        // Send entry damage to character
        Int iEntryDamage = entry.GetResult().GetFinalDamage();
        Character& destCharacter = CharacterManager::GetInstance()->GetCharacter(entry.GetDestinationCharacterID());
        destCharacter.OnBattleTakingDamage(iEntryDamage);

        // Add to final damage that the source character applied
        iFinalDamage += iEntryDamage;
    }

    // Send final damage to source character so they can record how much they gave
    Character& sourceCharacter = CharacterManager::GetInstance()->GetCharacter(GetSourceCharacterID());
    sourceCharacter.OnBattleGivingDamage(iFinalDamage);

    // Notify source character that their action was applied
    sourceCharacter.OnBattleActionApplied(STDGetSharedThis());
    return true;
}

void to_json(Json& jsonData, const CharacterActionBattleSkill& obj)
{
}

void from_json(const Json& jsonData, CharacterActionBattleSkill& obj)
{
}

MAKE_JSON_GENERIC_TYPE_CONVERTERS_IMPL(CharacterActionBattleSkill, CharacterActionBattleSkill);

};
