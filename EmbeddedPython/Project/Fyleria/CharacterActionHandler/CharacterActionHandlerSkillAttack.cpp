// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

// Internal includes
#include "CharacterActionHandler/CharacterActionHandlerSkillAttack.h"
#include "Character/CharacterManager.h"
#include "Battle/BattleEvents.h"
#include "Utility/Constants.h"
#include "Utility/Templates.h"

namespace Gecko
{

CharacterActionHandlerSkillAttack::CharacterActionHandlerSkillAttack()
{
}

CharacterActionHandlerSkillAttack::~CharacterActionHandlerSkillAttack()
{
}

CharacterActionResult CharacterActionHandlerSkillAttack::GetSkillAttackResult(
    const CharacterAction& action,
    const CharacterActionEntry& entry,
    const String& sDestCharID) const
{
    // Action result
    CharacterActionResult result;

    // Get character data
    const String& sSourceCharID = action.GetSourceCharacterID();
    const Character& sourceCharacter = CharacterManager::GetInstance()->GetCharacter(sSourceCharID);
    const Character& destCharacter = CharacterManager::GetInstance()->GetCharacter(sDestCharID);
    const CharacterBattleData& sourceBattleData = sourceCharacter.GetBattleDataActives();
    const CharacterBattleData& destBattleData = destCharacter.GetBattleDataActives();

    // Gather critical/multiple hit info
    const Float fSourceChanceToCauseCriticalHit = sourceBattleData.GetChanceToCauseCriticalHit();
    const Float fSourceChanceToApplyMultipleAttacks = sourceBattleData.GetChanceToApplyMultipleAttacks();
    //const Float fSourceCriticalHitMultiplier = sourceBattleData.GetCriticalHitMultiplier();
    const Float fSourceAttacksMultiplier = sourceBattleData.GetAttacksMultiplier();
    const Float fDestChanceToBlockCriticalHit = destBattleData.GetChanceToBlockCriticalHit();

    // Get hand info
    const CharacterHandType eHandType = GetEnumFromStringOrNone<CharacterHandType>(entry.GetHandType());
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
    const String& sHandedness = sourceCharacter.GetBasicData().GetHandedness();
    if(bIsPrimaryHandAction && !bIsShield) { sourceBattleData.GetPrimaryWeaponRatings(sHandedness, fPrimaryBlunt, fPrimaryPierce, fPrimarySlash); }
    if(bIsPrimaryHandAction && bIsShield) { sourceBattleData.GetPrimaryShieldRatings(sHandedness, fPrimaryBlunt, fPrimaryPierce, fPrimarySlash); }
    if(bIsSecondaryHandAction && !bIsShield) { sourceBattleData.GetSecondaryWeaponRatings(sHandedness, fSecondaryBlunt, fSecondaryPierce, fSecondarySlash); }
    if(bIsSecondaryHandAction && bIsShield) { sourceBattleData.GetSecondaryShieldRatings(sHandedness, fSecondaryBlunt, fSecondaryPierce, fSecondarySlash); }

    // Gather damage bonus values
    const Float fSourcePrimaryDamageBonusValue = (bIsPrimaryHandAction) ? sourceBattleData.GetWeaponPrimaryDamageBonusValue() : 0;
    const Float fSourcePrimaryDamageBonusPercent = (bIsPrimaryHandAction) ? sourceBattleData.GetWeaponPrimaryDamageBonusPercent() : 1;
    const Float fSourceSecondaryDamageBonusValue = (bIsSecondaryHandAction) ? sourceBattleData.GetWeaponSecondaryDamageBonusValue() : 0;
    const Float fSourceSecondaryDamageBonusPercent = (bIsSecondaryHandAction) ? sourceBattleData.GetWeaponSecondaryDamageBonusPercent() : 1;
    const Float fGeneralDamageBonusValue = sourceBattleData.GetGeneralDamageBonusValue();
    const Float fGeneralDamageBonusPercent = sourceBattleData.GetGeneralDamageBonusPercent();

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
    const Float fDestBlunt = destBattleData.GetEquippedArmorBluntRating() +
        destBattleData.GetEquippedShieldLeftBluntRating() +
        destBattleData.GetEquippedShieldRightBluntRating();
    const Float fDestPierce = destBattleData.GetEquippedArmorPierceRating() +
        destBattleData.GetEquippedShieldLeftPierceRating() +
        destBattleData.GetEquippedShieldRightPierceRating();
    const Float fDestSlash = destBattleData.GetEquippedArmorSlashRating() +
        destBattleData.GetEquippedShieldLeftSlashRating() +
        destBattleData.GetEquippedShieldRightSlashRating();

    // Gather information about the actions requested
    Float fSourceAttackRating = 0;
    Float fDestDefendRating = 0;
    for(const String& sActionType : entry.GetActionTypes())
    {
        const CharacterActionType eActionType = GetEnumFromStringOrNone<CharacterActionType>(sActionType);
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
        if(fSourceAttackRating <= (fDestDefendRating * SKILL_DAMAGE_BOUNDARY_PERCENT))
        {
            // No damage at all
            result.SetHasTargetDefendedSuccessfully(true);
            return result;
        }
        else
        {
            // Default damage
            fSkillRatingDiff = SKILL_DAMAGE_BOUNDARY_DEFAULT_VALUE;
        }
    }

    // Determine number of attacks
    Bool bShouldApplyMultipleAttacks = DoesChanceSucceed<Float>(fSourceChanceToApplyMultipleAttacks);
    Int iNumAttacks = static_cast<Int>((bShouldApplyMultipleAttacks) ? (BASE_NUMBER_OF_SKILL_ATTACKS * fSourceAttacksMultiplier) : BASE_NUMBER_OF_SKILL_ATTACKS);
    result.SetHaveMultipleAttacksSucceeded(bShouldApplyMultipleAttacks);
    result.SetNumAttacksOnTarget(iNumAttacks);

    // In each attack, calculate the damage
    // This includes critical hits, which can be blocked
    Float fSkillAttackDamage = 0;
    BoolArray vCriticalHitOnTarget = result.GetIndividualAttackIsCriticalCausedArray();
    BoolArray vTargetBlockedCriticalHit = result.GetIndividualAttackIsCriticalBlockedArray();
    FloatArray vIndividualAttackTargetDamage = result.GetIndividualAttackTargetDamageArray();
    for(Int i = 0; i < iNumAttacks; i++)
    {
        // Determine if critical hits will happen
        Bool bCauseCriticalHit = DoesChanceSucceed<Float>(fSourceChanceToCauseCriticalHit);
        Bool bBlockCriticalHit = DoesChanceSucceed<Float>(fDestChanceToBlockCriticalHit);
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
    SizeType uNumCriticalHitOnTarget = vCriticalHitOnTarget.size();
    SizeType uNumTargetBlockedCriticalHit = vTargetBlockedCriticalHit.size();
    SizeType uNumIndividualAttackTargetDamage = vIndividualAttackTargetDamage.size();
    if(uNumCriticalHitOnTarget != uNumTargetBlockedCriticalHit ||
       uNumCriticalHitOnTarget != uNumIndividualAttackTargetDamage ||
       uNumTargetBlockedCriticalHit != uNumIndividualAttackTargetDamage)
    {
        THROW_RUNTIME_ERROR("Mismatch on size of attack/block lists");
    }
    result.SetIndividualAttackIsCriticalCausedArray(vCriticalHitOnTarget);
    result.SetIndividualAttackIsCriticalBlockedArray(vTargetBlockedCriticalHit);
    result.SetIndividualAttackTargetDamageArray(vIndividualAttackTargetDamage);

    // Calculate result damage now
    Int iDamage = static_cast<Int>(STDRound((fSkillAttackDamage * fGeneralDamageBonusPercent) + fGeneralDamageBonusValue));
    result.SetFinalDamage(iDamage);
    return result;
}

Bool CharacterActionHandlerSkillAttack::Setup(CharacterAction& action)
{
    // Prepare character IDs
    action.PrepareCharacterIDs();

    // Setup destination characters
    for(const CharacterActionEntry& entry : action.GetActionEntries())
    {
        for(const String& sDestCharID : entry.GetDestinationCharacterIDs())
        {
            HandleBattleActionDefendSetup(sDestCharID, action);
        }
    }

    // Setup source character
    HandleBattleActionAttackSetup(action.GetSourceCharacterID(), action);
    return true;
}

Bool CharacterActionHandlerSkillAttack::Finish(CharacterAction& action)
{
    // Check characters
    if(!action.AreAllCharacterIDsValid())
    {
        return false;
    }

    // Finish destination character actions
    for(const CharacterActionEntry& entry : action.GetActionEntries())
    {
        for(const String& sDestCharID : entry.GetDestinationCharacterIDs())
        {
            HandleBattleActionFinished(sDestCharID, action);
        }
    }

    // Finish source character action
    HandleBattleActionFinished(action.GetSourceCharacterID(), action);
    return true;
}

Bool CharacterActionHandlerSkillAttack::GenerateResult(CharacterAction& action)
{
    // Check characters
    if(!action.AreAllCharacterIDsValid())
    {
        return false;
    }

    // Search action types
    for(CharacterActionEntry& entry : action.GetActionEntries())
    {
        // Generate result
        if(entry.DoesMatchActionType((+CharacterActionType::WeaponBasePierce)._to_string()) ||
           entry.DoesMatchActionType((+CharacterActionType::WeaponBaseBlunt)._to_string()) ||
           entry.DoesMatchActionType((+CharacterActionType::WeaponBaseSlash)._to_string()))
        {
            for(const String& sDestCharID : entry.GetDestinationCharacterIDs())
            {
                CharacterActionResult result = GetSkillAttackResult(action, entry, sDestCharID);
                entry.GetResults().insert({sDestCharID, result});
            }
        }
    }
    return true;
}

Bool CharacterActionHandlerSkillAttack::ApplyResult(CharacterAction& action)
{
    // Check characters
    if(!action.AreAllCharacterIDsValid())
    {
        return false;
    }

    // Look at each entry
    Int iFinalDamage = 0;
    for(const CharacterActionEntry& entry : action.GetActionEntries())
    {
        // Look at each result
        Int iEntryDamage = 0;
        for(auto it = entry.GetResults().cbegin(); it != entry.GetResults().cend(); it++)
        {
            // Send entry damage to character
            iEntryDamage = it->second.GetFinalDamage();
            HandleBattleTakingDamage(it->first, iEntryDamage);
        }

        // Add to final damage that the source character applied
        iFinalDamage += iEntryDamage;
    }

    // Send final damage to source character so they can record how much they gave
    HandleBattleGivingDamage(action.GetSourceCharacterID(), iFinalDamage);

    // Notify source character that their action was applied
    HandleBattleActionApplied(action.GetSourceCharacterID(), action);
    return true;
}

};
