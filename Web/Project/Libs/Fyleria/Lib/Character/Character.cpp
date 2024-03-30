// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#include "Character/Character.h"
#include "Character/CharacterManager.h"
#include "Character/CharacterPartyManager.h"
#include "Character/CharacterTypes.h"
#include "Config/ConfigManager.h"
#include "Battle/BattleManager.h"
#include "Items/ItemTypes.h"
#include "Utility/Constants.h"

namespace Gecko
{

const TreeIndexList Character::s_vEmptyChanges = {};

Character::Character()
{
    // Get current configuration
    const Config& config = ConfigManager::GetInstance()->GetCurrentConfig();

    // Basic character data
    SetFirstName(IndexedString(config.GetDefaultFirstName()));
    SetLastName(IndexedString(config.GetDefaultLastName()));
    SetAge(config.GetDefaultAge());
    SetGender(IndexedString(config.GetDefaultGender()));
    SetHair(IndexedString(config.GetDefaultHair()));
    SetEyes(IndexedString(config.GetDefaultEyes()));
    SetHandedness(IndexedString(config.GetDefaultHandedness()));
    SetBaseRace(IndexedString(config.GetDefaultBaseRace()));
    SetTransformedRace(IndexedString(config.GetDefaultTransformedRace()));
    SetPowerSet(IndexedString(config.GetDefaultPowerSet()));
    SetEquippedItems({});
    SetCurrentWeaponSet(IndexedString(config.GetDefaultCurrentWeaponSet()));

    // Combat Skills
    SetBarbarianCurrent(config.GetDefaultBarbarianCurrent());
    SetBarbarianRank(config.GetDefaultBarbarianRank());
    SetMageCurrent(config.GetDefaultMageCurrent());
    SetMageRank(config.GetDefaultMageRank());
    SetRogueCurrent(config.GetDefaultRogueCurrent());
    SetRogueRank(config.GetDefaultRogueRank());
    SetBlademasterCurrent(config.GetDefaultBlademasterCurrent());
    SetBlademasterRank(config.GetDefaultBlademasterRank());
    SetAvatarCurrent(config.GetDefaultAvatarCurrent());
    SetAvatarRank(config.GetDefaultAvatarRank());
    SetAmbidextrousCurrent(config.GetDefaultAmbidextrousCurrent());
    SetAmbidextrousRank(config.GetDefaultAmbidextrousRank());
    SetFocusedCurrent(config.GetDefaultFocusedCurrent());
    SetFocusedRank(config.GetDefaultFocusedRank());
    SetStalwartCurrent(config.GetDefaultStalwartCurrent());
    SetStalwartRank(config.GetDefaultStalwartRank());

    // Weapon Skills
    SetSlashCurrent(config.GetDefaultSlashCurrent());
    SetSlashRank(config.GetDefaultSlashRank());
    SetSeverCurrent(config.GetDefaultSeverCurrent());
    SetSeverRank(config.GetDefaultSeverRank());
    SetSliceCurrent(config.GetDefaultSliceCurrent());
    SetSliceRank(config.GetDefaultSliceRank());
    SetSlitCurrent(config.GetDefaultSlitCurrent());
    SetSlitRank(config.GetDefaultSlitRank());
    SetCleaveCurrent(config.GetDefaultCleaveCurrent());
    SetCleaveRank(config.GetDefaultCleaveRank());
    SetDecapitateCurrent(config.GetDefaultDecapitateCurrent());
    SetDecapitateRank(config.GetDefaultDecapitateRank());
    SetParryCurrent(config.GetDefaultParryCurrent());
    SetParryRank(config.GetDefaultParryRank());
    SetRiposteCurrent(config.GetDefaultRiposteCurrent());
    SetRiposteRank(config.GetDefaultRiposteRank());
    SetBashCurrent(config.GetDefaultBashCurrent());
    SetBashRank(config.GetDefaultBashRank());
    SetSmashCurrent(config.GetDefaultSmashCurrent());
    SetSmashRank(config.GetDefaultSmashRank());
    SetCrushCurrent(config.GetDefaultCrushCurrent());
    SetCrushRank(config.GetDefaultCrushRank());
    SetImpactCurrent(config.GetDefaultImpactCurrent());
    SetImpactRank(config.GetDefaultImpactRank());
    SetBreakCurrent(config.GetDefaultBreakCurrent());
    SetBreakRank(config.GetDefaultBreakRank());
    SetCrackCurrent(config.GetDefaultCrackCurrent());
    SetCrackRank(config.GetDefaultCrackRank());
    SetBlockCurrent(config.GetDefaultBlockCurrent());
    SetBlockRank(config.GetDefaultBlockRank());
    SetRushCurrent(config.GetDefaultRushCurrent());
    SetRushRank(config.GetDefaultRushRank());
    SetPierceCurrent(config.GetDefaultPierceCurrent());
    SetPierceRank(config.GetDefaultPierceRank());
    SetDrillCurrent(config.GetDefaultDrillCurrent());
    SetDrillRank(config.GetDefaultDrillRank());
    SetShootCurrent(config.GetDefaultShootCurrent());
    SetShootRank(config.GetDefaultShootRank());
    SetImpaleCurrent(config.GetDefaultImpaleCurrent());
    SetImpaleRank(config.GetDefaultImpaleRank());
    SetStealthStrikeCurrent(config.GetDefaultStealthStrikeCurrent());
    SetStealthStrikeRank(config.GetDefaultStealthStrikeRank());
    SetCriticalShotCurrent(config.GetDefaultCriticalShotCurrent());
    SetCriticalShotRank(config.GetDefaultCriticalShotRank());
    SetDodgeCurrent(config.GetDefaultDodgeCurrent());
    SetDodgeRank(config.GetDefaultDodgeRank());
    SetCounterCurrent(config.GetDefaultCounterCurrent());
    SetCounterRank(config.GetDefaultCounterRank());

    // Alchemy Skills
    SetHealerCurrent(config.GetDefaultHealerCurrent());
    SetHealerRank(config.GetDefaultHealerRank());
    SetAlchemistCurrent(config.GetDefaultAlchemistCurrent());
    SetAlchemistRank(config.GetDefaultAlchemistRank());
    SetEnergistCurrent(config.GetDefaultEnergistCurrent());
    SetEnergistRank(config.GetDefaultEnergistRank());
    SetChemistCurrent(config.GetDefaultChemistCurrent());
    SetChemistRank(config.GetDefaultChemistRank());

    // Crafting Skills
    SetHammersmithCurrent(config.GetDefaultHammersmithCurrent());
    SetHammersmithRank(config.GetDefaultHammersmithRank());
    SetSpellsmithCurrent(config.GetDefaultSpellsmithCurrent());
    SetSpellsmithRank(config.GetDefaultSpellsmithRank());
    SetBowsmithCurrent(config.GetDefaultBowsmithCurrent());
    SetBowsmithRank(config.GetDefaultBowsmithRank());
    SetSwordsmithCurrent(config.GetDefaultSwordsmithCurrent());
    SetSwordsmithRank(config.GetDefaultSwordsmithRank());
    SetWeaverCurrent(config.GetDefaultWeaverCurrent());
    SetWeaverRank(config.GetDefaultWeaverRank());
    SetTannerCurrent(config.GetDefaultTannerCurrent());
    SetTannerRank(config.GetDefaultTannerRank());
    SetScalesmithCurrent(config.GetDefaultScalesmithCurrent());
    SetScalesmithRank(config.GetDefaultScalesmithRank());
    SetPlatesmithCurrent(config.GetDefaultPlatesmithCurrent());
    SetPlatesmithRank(config.GetDefaultPlatesmithRank());
    SetGoldsmithCurrent(config.GetDefaultGoldsmithCurrent());
    SetGoldsmithRank(config.GetDefaultGoldsmithRank());
    SetShieldsmithCurrent(config.GetDefaultShieldsmithCurrent());
    SetShieldsmithRank(config.GetDefaultShieldsmithRank());

    // Breakdown Skills
    SetHammerbaneCurrent(config.GetDefaultHammerbaneCurrent());
    SetHammerbaneRank(config.GetDefaultHammerbaneRank());
    SetSpellbaneCurrent(config.GetDefaultSpellbaneCurrent());
    SetSpellbaneRank(config.GetDefaultSpellbaneRank());
    SetBowbaneCurrent(config.GetDefaultBowbaneCurrent());
    SetBowbaneRank(config.GetDefaultBowbaneRank());
    SetSwordbaneCurrent(config.GetDefaultSwordbaneCurrent());
    SetSwordbaneRank(config.GetDefaultSwordbaneRank());
    SetThreadbareCurrent(config.GetDefaultThreadbareCurrent());
    SetThreadbareRank(config.GetDefaultThreadbareRank());
    SetStudRemoverCurrent(config.GetDefaultStudRemoverCurrent());
    SetStudRemoverRank(config.GetDefaultStudRemoverRank());
    SetScalebaneCurrent(config.GetDefaultScalebaneCurrent());
    SetScalebaneRank(config.GetDefaultScalebaneRank());
    SetPlatebaneCurrent(config.GetDefaultPlatebaneCurrent());
    SetPlatebaneRank(config.GetDefaultPlatebaneRank());
    SetGoldbaneCurrent(config.GetDefaultGoldbaneCurrent());
    SetGoldbaneRank(config.GetDefaultGoldbaneRank());
    SetShieldbaneCurrent(config.GetDefaultShieldbaneCurrent());
    SetShieldbaneRank(config.GetDefaultShieldbaneRank());

    // Affinity Skills
    SetHolyCurrent(config.GetDefaultHolyCurrent());
    SetHolyRank(config.GetDefaultHolyRank());
    SetFireCurrent(config.GetDefaultFireCurrent());
    SetFireRank(config.GetDefaultFireRank());
    SetIceCurrent(config.GetDefaultIceCurrent());
    SetIceRank(config.GetDefaultIceRank());
    SetShockCurrent(config.GetDefaultShockCurrent());
    SetShockRank(config.GetDefaultShockRank());
    SetDarkCurrent(config.GetDefaultDarkCurrent());
    SetDarkRank(config.GetDefaultDarkRank());
    SetLightCurrent(config.GetDefaultLightCurrent());
    SetLightRank(config.GetDefaultLightRank());
    SetForceCurrent(config.GetDefaultForceCurrent());
    SetForceRank(config.GetDefaultForceRank());
    SetMindCurrent(config.GetDefaultMindCurrent());
    SetMindRank(config.GetDefaultMindRank());
    SetEarthCurrent(config.GetDefaultEarthCurrent());
    SetEarthRank(config.GetDefaultEarthRank());
    SetBloodCurrent(config.GetDefaultBloodCurrent());
    SetBloodRank(config.GetDefaultBloodRank());
    SetFleshCurrent(config.GetDefaultFleshCurrent());
    SetFleshRank(config.GetDefaultFleshRank());
    SetWindCurrent(config.GetDefaultWindCurrent());
    SetWindRank(config.GetDefaultWindRank());

    // Segmented progress data
    GetProgressDataBase().reset();
    GetProgressDataPassives().reset();
    GetProgressDataActives().reset();

    // Segmented battle data
    GetBattleDataBase().reset();
    GetBattleDataPassives().reset();
    GetBattleDataActives().reset();

    // List of passive/active/actionable data
    GetPassiveSkillDataList().clear();
    GetActiveSkillDataList().clear();
    GetActionableSkillDataList().clear();
    GetPassiveItemDataList().clear();
    GetActiveItemDataList().clear();
    GetActionableItemDataList().clear();

    // List of character actions
    GetAvailableActions().clear();

    // Prolonged stat changes
    SetProlongedStatChanges({});

    // Skill use tracking
    SetSkillUseTrackingMap({});

    // Attack/defend counters
    SetAttackCounter(0);
    SetDefendCounter(0);

    // Character ID
    SetCharacterID(IndexedString(""));

    // Character target type
    SetCharacterTargetType(IndexedString("None"));
}

Character::~Character()
{
}

//===============================================================================================

void Character::RegenerateCharacterData(
    Bool bUpdateSkillRankings /*= true*/,
    Bool bUpdateEquipmentRatings /*= true*/,
    Bool bUpdateAvailableChanges /*= true*/,
    Bool bUpdateAvailableActions /*= true*/,
    Bool bUpdateAvailableAP /*= true*/
)
{
    // Reset all non-base data
    GetProgressDataPassives().reset();
    GetBattleDataPassives().reset();
    GetProgressDataActives().reset();
    GetBattleDataActives().reset();

    // Update character data
    if(bUpdateSkillRankings) { UpdateSkillRankings(IndexedString("Base")); }
    if(bUpdateEquipmentRatings) { UpdateEquipmentRatings(IndexedString("Base")); }
    if(bUpdateAvailableChanges) { UpdateAvailableChanges(IndexedString("Base")); }
    if(bUpdateAvailableActions) { UpdateAvailableActions(IndexedString("Base")); }
    if(bUpdateAvailableAP) { UpdateAvailableAP(IndexedString("Base")); }

    // Apply passives
    ApplyPassiveChanges();

    // Display the new data
#ifdef DEBUG
    Json jsonData = *this;
    LOG_FORMAT_STATEMENT("Completed regenerating character data (CharacterID = '%s'):\n%s\n",
        GetCharacterID().c_str(),
        jsonData.dump(4).c_str());
#endif
}

//===============================================================================================

void Character::OnBattleStarted()
{
    // Clear active changes
    ClearActiveChanges();

    // Reset prolonged stat changes
    SetProlongedStatChanges({});

    // Reset skill tracking
    SetSkillUseTrackingMap({});

    // Reset attack/defend counters
    SetAttackCounter(0);
    SetDefendCounter(0);
}

void Character::OnBattleEnded()
{
    // Clear active changes
    ClearActiveChanges();

    // Reset prolonged stat changes
    SetProlongedStatChanges({});

    // Reset attack/defend counters
    SetAttackCounter(0);
    SetDefendCounter(0);
}

void Character::OnBattleTally()
{
    // Regenerate character data on the tally screen
    // The calling code should capture the state before and after this
    // then see the difference as something to display to the player
    // We DO
    // - Update skill rankings because they could have used skills
    // - Update available changes because skills could have changed
    // - Update available actions because skills could have changed
    // We DO NOT
    // - Update equipment ratings, because equipment does not change
    // - Update available AP, because you only refill AP when resting
    RegenerateCharacterData(
        true, /* bUpdateSkillRankings */
        false, /* bUpdateEquipmentRatings */
        true, /* bUpdateAvailableChanges */
        true, /* bUpdateAvailableActions */
        false /* bUpdateAvailableAP */
    );
}

void Character::OnBattleFullyCompleted()
{
    // Update character data across non-active segments
    const IndexedStringList vSegments = {IndexedString("Base"), IndexedString("Passive")};
    for(const IndexedString& sSegment : vSegments)
    {
        // Get appropriate segments
        STDSharedPtr<CharacterProgressData> pProgressData = GetProgressSegment(sSegment);
        STDSharedPtr<CharacterBattleData> pBattleData = GetBattleSegment(sSegment);
        if(!pProgressData || !pBattleData)
        {
            continue;
        }

        // Finish battle
        pBattleData->FinishBattle(*pProgressData);
    }

    // Reset skill tracking
    SetSkillUseTrackingMap({});
}

void Character::OnBattleRoundAdvanced()
{
    // Update character data across non-active segments
    const IndexedStringList vSegments = {IndexedString("Base"), IndexedString("Passive")};
    for(const IndexedString& sSegment : vSegments)
    {
        // Get appropriate segments
        STDSharedPtr<CharacterProgressData> pProgressData = GetProgressSegment(sSegment);
        STDSharedPtr<CharacterBattleData> pBattleData = GetBattleSegment(sSegment);
        if(!pProgressData || !pBattleData)
        {
            continue;
        }

        // Advance round
        pBattleData->AdvanceRound(*pProgressData);
    }

    // Remove expired prolonged stat changes
    RemoveAllExpiredProlongedStatChanges();
}

void Character::OnBattleGivingDamage(Int iAmount)
{
    // Skip invalid damage
    if(iAmount <= 0)
    {
        return;
    }

    // Update character data across non-active segments
    const IndexedStringList vSegments = {IndexedString("Base"), IndexedString("Passive")};
    for(const IndexedString& sSegment : vSegments)
    {
        // Get appropriate segments
        STDSharedPtr<CharacterBattleData> pBattleData = GetBattleSegment(sSegment);
        if(!pBattleData)
        {
            continue;
        }

        // Update damage given
        pBattleData->ApplyGivenDamage(iAmount);
    }

    // Update attack counter
    SetAttackCounter(GetAttackCounter() + 1);

    // Remove expired prolonged stat changes
    RemoveAllExpiredProlongedStatChanges();
}

void Character::OnBattleTakingDamage(Int iAmount)
{
    // Skip invalid damage
    if(iAmount <= 0)
    {
        return;
    }

    // Update character data across non-active segments
    const IndexedStringList vSegments = {IndexedString("Base"), IndexedString("Passive")};
    for(const IndexedString& sSegment : vSegments)
    {
        // Get appropriate segments
        STDSharedPtr<CharacterProgressData> pProgressData = GetProgressSegment(sSegment);
        STDSharedPtr<CharacterBattleData> pBattleData = GetBattleSegment(sSegment);
        if(!pProgressData || !pBattleData)
        {
            continue;
        }

        // Update damage taken
        pProgressData->ApplyTakenDamage(iAmount);
        pBattleData->ApplyTakenDamage(iAmount);

        // Apply new status
        pBattleData->ApplyNewStatus(*pProgressData);
    }

    // Update defend counter
    SetDefendCounter(GetDefendCounter() + 1);

    // Remove expired prolonged stat changes
    RemoveAllExpiredProlongedStatChanges();
}

void Character::OnBattleChoosingTargets(const IndexedStringList& vDestTargets)
{
    // Update character data across non-active segments
    const IndexedStringList vSegments = {IndexedString("Base"), IndexedString("Passive")};
    for(const IndexedString& sSegment : vSegments)
    {
        // Get appropriate segments
        STDSharedPtr<CharacterBattleData> pBattleData = GetBattleSegment(sSegment);
        if(!pBattleData)
        {
            continue;
        }

        // Update most recent attack targets
        pBattleData->SetMostRecentAttackTargets(vDestTargets);

        // Update attack targets this round
        IndexedStringList vTargetsThisRound = pBattleData->GetAttackTargetsThisRound();
        vTargetsThisRound.insert(vTargetsThisRound.end(), vDestTargets.begin(), vDestTargets.end());
        pBattleData->SetAttackTargetsThisRound(vTargetsThisRound);
    }
}

void Character::OnBattleBecomingTarget(const IndexedString& sSourceTarget)
{
    // Update character data across non-active segments
    const IndexedStringList vSegments = {IndexedString("Base"), IndexedString("Passive")};
    for(const IndexedString& sSegment : vSegments)
    {
        // Get appropriate segments
        STDSharedPtr<CharacterBattleData> pBattleData = GetBattleSegment(sSegment);
        if(!pBattleData)
        {
            continue;
        }

        // Update most recent defend target
        pBattleData->SetMostRecentDefendTarget(sSourceTarget);

        // Update defend targets this round
        pBattleData->GetDefendTargetsThisRound().push_back(sSourceTarget);
    }
}

void Character::OnBattleActionAttackSetup(const CharacterActionSharedPtr& pAction)
{
    // Update character data across non-active segments
    const IndexedStringList vSegments = {IndexedString("Base"), IndexedString("Passive")};
    for(const IndexedString& sSegment : vSegments)
    {
        // Get appropriate segments
        STDSharedPtr<CharacterBattleData> pBattleData = GetBattleSegment(sSegment);
        if(!pBattleData)
        {
            continue;
        }

        // Set targets for this action
        pBattleData->SetAttackTargetsThisAction(pBattleData->GetMostRecentAttackTargets());
        pBattleData->SetDefendTargetThisAction(IndexedString(""));
    }

    // Apply active changes
    ApplyActiveChanges(pAction);
}

void Character::OnBattleActionDefendSetup(const CharacterActionSharedPtr& pAction)
{
    // Update character data across non-active segments
    const IndexedStringList vSegments = {IndexedString("Base"), IndexedString("Passive")};
    for(const IndexedString& sSegment : vSegments)
    {
        // Get appropriate segments
        STDSharedPtr<CharacterBattleData> pBattleData = GetBattleSegment(sSegment);
        if(!pBattleData)
        {
            continue;
        }

        // Set targets for this action
        pBattleData->SetAttackTargetsThisAction({});
        pBattleData->SetDefendTargetThisAction(pBattleData->GetMostRecentDefendTarget());
    }

    // Apply active changes
    ApplyActiveChanges(pAction);
}

void Character::OnBattleActionApplied(const CharacterActionSharedPtr& pAction)
{
    // Store previous action types
    if(pAction)
    {
        SetPreviousActionTypes(pAction->GetAllActionTypes());
    }
}

void Character::OnBattleActionFinished(const CharacterActionSharedPtr& pAction)
{
    // Update character data across non-active segments
    const IndexedStringList vSegments = {IndexedString("Base"), IndexedString("Passive")};
    for(const IndexedString& sSegment : vSegments)
    {
        // Get appropriate segments
        STDSharedPtr<CharacterProgressData> pProgressData = GetProgressSegment(sSegment);
        STDSharedPtr<CharacterBattleData> pBattleData = GetBattleSegment(sSegment);
        if(!pProgressData || !pBattleData)
        {
            continue;
        }

        // Apply costs
        pProgressData->ApplyActionCost(pAction);

        // If this was a skill action, we should track it
        if(pAction && !pAction->GetSkillTreeIndex().empty())
        {
            AddSkillUse(GetSkillType(pAction->GetSkillTreeIndex()), 1);
        }

        // Apply new status
        pBattleData->ApplyNewStatus(*pProgressData);

        // Clear action targets
        pBattleData->SetAttackTargetsThisAction({});
        pBattleData->SetDefendTargetThisAction(IndexedString(""));
    }

    // Clear active changes
    ClearActiveChanges();
}

//===============================================================================================

STDSharedPtr<CharacterProgressData> Character::GetProgressSegment(const IndexedString& sSegment)
{
    CharacterSegmentType eSegmentType = StringToCharacterSegmentType(sSegment);
    switch(eSegmentType)
    {
        case CharacterSegmentType::Base: return GetProgressDataBase();
        case CharacterSegmentType::Passive: return GetProgressDataPassives();
        case CharacterSegmentType::Active: return GetProgressDataActives();
        default: return nullptr;
    }
}

STDSharedPtr<const CharacterProgressData> Character::GetProgressSegment(const IndexedString& sSegment) const
{
    CharacterSegmentType eSegmentType = StringToCharacterSegmentType(sSegment);
    switch(eSegmentType)
    {
        case CharacterSegmentType::Base: return GetProgressDataBase();
        case CharacterSegmentType::Passive: return GetProgressDataPassives();
        case CharacterSegmentType::Active: return GetProgressDataActives();
        default: return nullptr;
    }
}

STDSharedPtr<CharacterBattleData> Character::GetBattleSegment(const IndexedString& sSegment)
{
    CharacterSegmentType eSegmentType = StringToCharacterSegmentType(sSegment);
    switch(eSegmentType)
    {
        case CharacterSegmentType::Base: return GetBattleDataBase();
        case CharacterSegmentType::Passive: return GetBattleDataPassives();
        case CharacterSegmentType::Active: return GetBattleDataActives();
        default: return nullptr;
    }
}

STDSharedPtr<const CharacterBattleData> Character::GetBattleSegment(const IndexedString& sSegment) const
{
    CharacterSegmentType eSegmentType = StringToCharacterSegmentType(sSegment);
    switch(eSegmentType)
    {
        case CharacterSegmentType::Base: return GetBattleDataBase();
        case CharacterSegmentType::Passive: return GetBattleDataPassives();
        case CharacterSegmentType::Active: return GetBattleDataActives();
        default: return nullptr;
    }
}

//===============================================================================================

Bool Character::GetBoolStatValue(const IndexedString& sSegment, const IndexedString& sStat, Bool& bValue) const
{
    STDSharedPtr<const CharacterBattleData> pBattleData = GetBattleSegment(sSegment);
    return (pBattleData) ? pBattleData->GetBoolStatValue(sStat, bValue) : false;
}

Bool Character::GetIntStatValue(const IndexedString& sSegment, const IndexedString& sStat, Int& iValue) const
{
    STDSharedPtr<const CharacterProgressData> pProgressData = GetProgressSegment(sSegment);
    STDSharedPtr<const CharacterBattleData> pBattleData = GetBattleSegment(sSegment);
    return (pProgressData && pBattleData) ? (pProgressData->GetIntStatValue(sStat, iValue) || pBattleData->GetIntStatValue(sStat, iValue)) : false;
}

Bool Character::GetFloatStatValue(const IndexedString& sSegment, const IndexedString& sStat, Float& fValue) const
{
    STDSharedPtr<const CharacterBattleData> pBattleData = GetBattleSegment(sSegment);
    return (pBattleData) ? pBattleData->GetFloatStatValue(sStat, fValue) : false;
}

Bool Character::GetStringStatValue(const IndexedString& sSegment, const IndexedString& sStat, IndexedString& sValue) const
{
    STDSharedPtr<const CharacterBattleData> pBattleData = GetBattleSegment(sSegment);
    return (pBattleData) ? pBattleData->GetStringStatValue(sStat, sValue) : false;
}

Bool Character::GetStringListStatValue(const IndexedString& sSegment, const IndexedString& sStat, IndexedStringList& vValues) const
{
    STDSharedPtr<const CharacterBattleData> pBattleData = GetBattleSegment(sSegment);
    return (pBattleData) ? pBattleData->GetStringListStatValue(sStat, vValues) : false;
}

Bool Character::SetBoolStatValue(const IndexedString& sSegment, const IndexedString& sStat, const Bool& bValue)
{
    STDSharedPtr<CharacterBattleData> pBattleData = GetBattleSegment(sSegment);
    return (pBattleData) ? pBattleData->SetBoolStatValue(sStat, bValue) : false;
}

Bool Character::SetIntStatValue(const IndexedString& sSegment, const IndexedString& sStat, const Int& iValue)
{
    STDSharedPtr<CharacterProgressData> pProgressData = GetProgressSegment(sSegment);
    STDSharedPtr<CharacterBattleData> pBattleData = GetBattleSegment(sSegment);
    return (pProgressData && pBattleData) ? (pProgressData->SetIntStatValue(sStat, iValue) || pBattleData->SetIntStatValue(sStat, iValue)) : false;
}

Bool Character::SetFloatStatValue(const IndexedString& sSegment, const IndexedString& sStat, const Float& fValue)
{
    STDSharedPtr<CharacterBattleData> pBattleData = GetBattleSegment(sSegment);
    return (pBattleData) ? pBattleData->SetFloatStatValue(sStat, fValue) : false;
}

Bool Character::SetStringStatValue(const IndexedString& sSegment, const IndexedString& sStat, const IndexedString& sValue)
{
    STDSharedPtr<CharacterBattleData> pBattleData = GetBattleSegment(sSegment);
    return (pBattleData) ? pBattleData->SetStringStatValue(sStat, sValue) : false;
}

Bool Character::SetStringListStatValue(const IndexedString& sSegment, const IndexedString& sStat, const IndexedStringList& vValues)
{
    STDSharedPtr<CharacterBattleData> pBattleData = GetBattleSegment(sSegment);
    return (pBattleData) ? pBattleData->SetStringListStatValue(sStat, vValues) : false;
}

IndexedStringList Character::ResolveTargetPlaceholder(const IndexedString& sSegment, const IndexedString& sPlaceholderTargetType) const
{
    IndexedStringList vTargets;
    STDSharedPtr<const CharacterBattleData> pBattleData = GetBattleSegment(sSegment);
    if(!pBattleData)
    {
        return vTargets;
    }

    const CharacterTargetType eTargetType = StringToCharacterTargetType(sPlaceholderTargetType);
    switch(eTargetType)
    {
        case CharacterTargetType::Self:
            vTargets.push_back(GetCharacterTargetType());
            break;
        case CharacterTargetType::AttackTargetsThisAction:
            vTargets = pBattleData->GetAttackTargetsThisAction();
            break;
        case CharacterTargetType::DefendTargetThisAction:
            vTargets.push_back(pBattleData->GetDefendTargetThisAction());
            break;
        case CharacterTargetType::AttackTargetsThisRound:
            vTargets = pBattleData->GetAttackTargetsThisRound();
            break;
        case CharacterTargetType::DefendTargetsThisRound:
            vTargets = pBattleData->GetDefendTargetsThisRound();
            break;
        case CharacterTargetType::AttackTargetsLastRound:
            vTargets = pBattleData->GetAttackTargetsLastRound();
            break;
        case CharacterTargetType::DefendTargetsLastRound:
            vTargets = pBattleData->GetDefendTargetsLastRound();
            break;
        case CharacterTargetType::MostRecentAttackTargets:
            vTargets = pBattleData->GetMostRecentAttackTargets();
            break;
        case CharacterTargetType::MostRecentDefendTarget:
            vTargets.push_back(pBattleData->GetMostRecentDefendTarget());
            break;
        default:
            break;
    }
    return vTargets;
}

void Character::ResolveTargetPlaceholders(const IndexedString& sSegment, StatChange& change)
{
    IndexedStringList vSourceTargetTypes = ResolveTargetPlaceholder(sSegment, change.GetSourceTargetType());
    IndexedStringList vDestTargetTypes = ResolveTargetPlaceholder(sSegment, change.GetDestinationTargetType());
    if(!vSourceTargetTypes.empty())
    {
        change.SetSourceTargetType(vSourceTargetTypes.front());
    }
    if(!vDestTargetTypes.empty())
    {
        change.SetDestinationTargetType(vDestTargetTypes.front());
    }
}

UInt Character::GetEquippedItemTypeCount(const TreeIndex& index) const
{
    TreeIndexList vEquippedItemIndices;
    for(auto&& progressItem : GetEquippedItems())
    {
        vEquippedItemIndices.push_back(progressItem.GetTreeIndex());
    }
    return STDCountData(vEquippedItemIndices.begin(), vEquippedItemIndices.end(), index);
}

UInt Character::GetEquippedWeaponCount(const IndexedString& sWeaponSet) const
{
    UInt uWeapon1Count = 0;
    UInt uWeapon2Count = 0;
    for(auto&& progressItem : GetEquippedItems())
    {
        if(!IsItemWeapon(progressItem.GetTreeIndex()))
        {
            continue;
        }

        const CharacterEquipmentType eEquipType = StringToCharacterEquipmentType(progressItem.GetItemSlot());
        uWeapon1Count += (eEquipType == +CharacterEquipmentType::Weapon1Left) ? 1 : 0;
        uWeapon1Count += (eEquipType == +CharacterEquipmentType::Weapon1Right) ? 1 : 0;
        uWeapon2Count += (eEquipType == +CharacterEquipmentType::Weapon2Left) ? 1 : 0;
        uWeapon2Count += (eEquipType == +CharacterEquipmentType::Weapon2Right) ? 1 : 0;
    }

    const CharacterWeaponSetType eWeaponSetType = StringToCharacterWeaponSetType(sWeaponSet);
    if(eWeaponSetType == +CharacterWeaponSetType::WeaponSet1)
    {
        return uWeapon1Count;
    }
    else if(eWeaponSetType == +CharacterWeaponSetType::WeaponSet2)
    {
        return uWeapon2Count;
    }
    return 0;
}

UInt Character::GetEquippedShieldCount(const IndexedString& sWeaponSet) const
{
    UInt uShield1Count = 0;
    UInt uShield2Count = 0;
    for(auto&& progressItem : GetEquippedItems())
    {
        if(!IsItemShield(progressItem.GetTreeIndex()))
        {
            continue;
        }

        const CharacterEquipmentType eEquipType = StringToCharacterEquipmentType(progressItem.GetItemSlot());
        uShield1Count += (eEquipType == +CharacterEquipmentType::Weapon1Left) ? 1 : 0;
        uShield1Count += (eEquipType == +CharacterEquipmentType::Weapon1Right) ? 1 : 0;
        uShield2Count += (eEquipType == +CharacterEquipmentType::Weapon2Left) ? 1 : 0;
        uShield2Count += (eEquipType == +CharacterEquipmentType::Weapon2Right) ? 1 : 0;
    }

    const CharacterWeaponSetType eWeaponSetType = StringToCharacterWeaponSetType(sWeaponSet);
    if(eWeaponSetType == +CharacterWeaponSetType::WeaponSet1)
    {
        return uShield1Count;
    }
    else if(eWeaponSetType == +CharacterWeaponSetType::WeaponSet2)
    {
        return uShield2Count;
    }
    return 0;
}

Bool Character::CanAddEquippedItem(const TreeIndex& index) const
{
    const UInt uItemCount = GetEquippedItemTypeCount(index);
    const ItemType eItemType = StringToItemType(RetrieveItemType(index));
    switch(eItemType)
    {
        case ItemType::WeaponPierce:
        case ItemType::WeaponBlunt:
        case ItemType::WeaponSlash:
        case ItemType::WeaponMage:
        case ItemType::ArmorShieldPierce:
        case ItemType::ArmorShieldBlunt:
        case ItemType::ArmorShieldSlash:
            return (uItemCount < s_kuHandSizeLimit);
        case ItemType::ArmorChest:
        case ItemType::ArmorFeet:
        case ItemType::ArmorFinger:
        case ItemType::ArmorHands:
        case ItemType::ArmorHead:
        case ItemType::ArmorLegs:
        case ItemType::ArmorNeck:
            return (uItemCount < s_kuBodySizeLimit);
        default:
            return false;
    }
}

Bool Character::CanRemoveEquippedItem(const TreeIndex& index) const
{
    const UInt uItemCount = GetEquippedItemTypeCount(index);
    const ItemType eItemType = StringToItemType(RetrieveItemType(index));
    switch(eItemType)
    {
        case ItemType::WeaponPierce:
        case ItemType::WeaponBlunt:
        case ItemType::WeaponSlash:
        case ItemType::WeaponMage:
        case ItemType::ArmorShieldPierce:
        case ItemType::ArmorShieldBlunt:
        case ItemType::ArmorShieldSlash:
        case ItemType::ArmorChest:
        case ItemType::ArmorFeet:
        case ItemType::ArmorFinger:
        case ItemType::ArmorHands:
        case ItemType::ArmorHead:
        case ItemType::ArmorLegs:
        case ItemType::ArmorNeck:
            return (uItemCount > 0);
        default:
            return false;
    }
}

Bool Character::AddEquippedItem(const TreeIndex& index, const IndexedString& sEquipSlot)
{
    // Check if it can be added
    if(!CanAddEquippedItem(index))
    {
        return false;
    }

    // Add item
    CharacterProgressItem equipItem;
    equipItem.SetTreeIndex(index);
    equipItem.SetItemSlot(sEquipSlot);
    GetEquippedItems().push_back(equipItem);
    return true;
}

Bool Character::RemoveEquippedItem(const TreeIndex& index, const IndexedString& sEquipSlot)
{
    // Check if it can be removed
    if(!CanRemoveEquippedItem(index))
    {
        return false;
    }

    // Remove item
    CharacterProgressItem equipItem;
    equipItem.SetTreeIndex(index);
    equipItem.SetItemSlot(sEquipSlot);
    STDVectorRemoveElement<CharacterProgressItem>(GetEquippedItems(), equipItem);
    return true;
}

Bool Character::GetHandInfoByWeaponSet(const IndexedString& sWeaponSet,
    TreeIndex& primaryItemIndex,
    TreeIndex& secondaryItemIndex,
    IndexedStringList& vPrimaryActionTypes,
    IndexedStringList& vSecondaryActionTypes) const
{
    // Get weapon set
    const CharacterWeaponSetType eWeaponSetType = StringToCharacterWeaponSetType(sWeaponSet);
    const Bool bIsWeaponSetSelected1 = (eWeaponSetType == +CharacterWeaponSetType::WeaponSet1);
    const Bool bIsWeaponSetSelected2 = (eWeaponSetType == +CharacterWeaponSetType::WeaponSet2);

    // Get the left/right items
    TreeIndex itemIndexLeft;
    TreeIndex itemIndexRight;
    for(auto&& progressItem : GetEquippedItems())
    {
        const ItemTreeType eItemTreeType = StringToItemTreeType(progressItem.GetTreeIndex().GetTree());
        const CharacterEquipmentType eEquipType = StringToCharacterEquipmentType(progressItem.GetItemSlot());
        const Bool bValidEquipLeft =
            (bIsWeaponSetSelected1 && (eEquipType == +CharacterEquipmentType::Weapon1Left)) ||
            (bIsWeaponSetSelected2 && (eEquipType == +CharacterEquipmentType::Weapon2Left));
        const Bool bValidEquipRight =
            (bIsWeaponSetSelected1 && (eEquipType == +CharacterEquipmentType::Weapon1Right)) ||
            (bIsWeaponSetSelected2 && (eEquipType == +CharacterEquipmentType::Weapon2Right));
        switch(eItemTreeType)
        {
            case ItemTreeType::Armor:
            {
                const Bool bIsShield = IsItemShield(progressItem.GetTreeIndex());
                if(bIsShield && bValidEquipLeft)
                {
                    itemIndexLeft = progressItem.GetTreeIndex();
                }
                else if(bIsShield && bValidEquipRight)
                {
                    itemIndexRight = progressItem.GetTreeIndex();
                }
                break;
            }
            case ItemTreeType::Weapon:
            {
                if(bValidEquipLeft)
                {
                    itemIndexLeft = progressItem.GetTreeIndex();
                }
                else if(bValidEquipRight)
                {
                    itemIndexRight = progressItem.GetTreeIndex();
                }
                break;
            }
            default:
                break;
        }
    }

    // Translate left/right to primary/secondary
    const CharacterHandednessType eHandedness = StringToCharacterHandednessType(GetHandedness());
    switch(eHandedness)
    {
        case CharacterHandednessType::LeftHanded:
            primaryItemIndex = itemIndexLeft;
            secondaryItemIndex = itemIndexRight;
            break;
        case CharacterHandednessType::RightHanded:
            primaryItemIndex = itemIndexRight;
            secondaryItemIndex = itemIndexLeft;
            break;
        default:
            break;
    }

    // Fill action types
    vPrimaryActionTypes = GetActionTypes(primaryItemIndex);
    vSecondaryActionTypes = GetActionTypes(secondaryItemIndex);
    return (!primaryItemIndex.empty() || !secondaryItemIndex.empty());
}

void Character::AddProlongedStatChange(const IndexedString& sKey, const ProlongedStatChange& change)
{
    GetProlongedStatChanges()[sKey] = change;
}

Bool Character::RemoveProlongedStatChange(const IndexedString& sKey)
{
    return (GetProlongedStatChanges().erase(sKey) > 0);
}

ProlongedStatChange& Character::GetProlongedStatChange(const IndexedString& sKey)
{
    return (GetProlongedStatChanges().at(sKey));
}

const ProlongedStatChange& Character::GetProlongedStatChange(const IndexedString& sKey) const
{
    return (GetProlongedStatChanges().at(sKey));
}

StatChangeEntryList Character::GetProlongedStatChangeEntries() const
{
    // Find all prolonged stat change entries that match current conditions
    StatChangeEntryList vEntries;
    for(auto it = GetProlongedStatChanges().begin(); it != GetProlongedStatChanges().end(); it++)
    {
        // Ignore expired entries
        const IndexedString& sKey = IndexedString(it->first);
        if(HasProlongedStatChangeExpired(sKey))
        {
            continue;
        }

        // Find the only valid round/attack/defend and check if it matches
        const ProlongedStatChange& change = it->second;
        const StatChangeEntry& entry = change.GetStatChangeEntry();
        if(
            (change.IsValidRound() && change.GetRound() == BattleManager::GetInstance()->GetCurrentBattle().GetCurrentRoundIndex()) ||
            (change.IsValidAttack() && change.GetAttack() == GetAttackCounter()) ||
            (change.IsValidDefend() && change.GetDefend() == GetDefendCounter()))
        {
            vEntries.push_back(entry);
        }
    }
    return vEntries;
}

Bool Character::DoesProlongedStatChangeExist(const IndexedString& sKey) const
{
    return (GetProlongedStatChanges().find(sKey) != GetProlongedStatChanges().end());
}

Bool Character::HasProlongedStatChangeExpired(const IndexedString& sKey) const
{
    const ProlongedStatChange& change = GetProlongedStatChange(sKey);
    return (
        (change.IsValidRound() && change.GetRound() < BattleManager::GetInstance()->GetCurrentBattle().GetCurrentRoundIndex()) ||
        (change.IsValidAttack() && change.GetAttack() < GetAttackCounter()) ||
        (change.IsValidDefend() && change.GetDefend() < GetDefendCounter())
    );
}

void Character::RemoveAllExpiredProlongedStatChanges()
{
    IndexedStringList vKeys;
    for(auto it = GetProlongedStatChanges().begin(); it != GetProlongedStatChanges().end(); it++)
    {
        if(HasProlongedStatChangeExpired(IndexedString(it->first)))
        {
            vKeys.push_back(IndexedString(it->first));
        }
    }

    for(const IndexedString& sKey : vKeys)
    {
        RemoveProlongedStatChange(sKey);
    }
}

void Character::AddSkillUse(const IndexedString& sSkillType, UInt uNum)
{
    SkillUseTrackingMapType& tTrackingMap = GetSkillUseTrackingMap();
    if(tTrackingMap.count(sSkillType))
    {
        tTrackingMap[sSkillType] = tTrackingMap[sSkillType] + uNum;
    }
    else
    {
        tTrackingMap[sSkillType] = uNum;
    }
}

UInt Character::GetSkillUseCount(const IndexedString& sSkillType) const
{
    const SkillUseTrackingMapType& tTrackingMap = GetSkillUseTrackingMap();
    auto iSearch = tTrackingMap.find(sSkillType);
    if(iSearch != tTrackingMap.end())
    {
        return iSearch->second;
    }
    return 0;
}

#define CHARACTER_SET_SKILL_VALUE(type, method, value)                      \
{                                                                           \
    for(auto&& sSkillType : type::_names())                                 \
    {                                                                       \
        CharacterSkillFunctionNode node = GetSkillFunctions(sSkillType);    \
        if(node.IsValid()) { node.method(*this, value); }                   \
    }                                                                       \
}

void Character::SetAllSkillCurrentValues(UByte uValue)
{
    CHARACTER_SET_SKILL_VALUE(SkillWeaponType, SetCurrent, uValue);
    CHARACTER_SET_SKILL_VALUE(SkillAlchemyType, SetCurrent, uValue);
    CHARACTER_SET_SKILL_VALUE(SkillBreakdownType, SetCurrent, uValue);
    CHARACTER_SET_SKILL_VALUE(SkillCombatType, SetCurrent, uValue);
    CHARACTER_SET_SKILL_VALUE(SkillCraftingType, SetCurrent, uValue);
    CHARACTER_SET_SKILL_VALUE(SkillAffinityType, SetCurrent, uValue);
}

void Character::SetAllSkillRankingValues(UByte uValue)
{
    CHARACTER_SET_SKILL_VALUE(SkillWeaponType, SetRank, uValue);
    CHARACTER_SET_SKILL_VALUE(SkillAlchemyType, SetRank, uValue);
    CHARACTER_SET_SKILL_VALUE(SkillBreakdownType, SetRank, uValue);
    CHARACTER_SET_SKILL_VALUE(SkillCombatType, SetRank, uValue);
    CHARACTER_SET_SKILL_VALUE(SkillCraftingType, SetRank, uValue);
    CHARACTER_SET_SKILL_VALUE(SkillAffinityType, SetRank, uValue);
}

const TreeIndexList& Character::GetPassiveChanges(const IndexedString& sTreeIndexType) const
{
    const CharacterTreeIndexType eTreeIndexType = StringToCharacterTreeIndexType(sTreeIndexType);
    switch(eTreeIndexType)
    {
        case CharacterTreeIndexType::Skill:
            return GetPassiveSkillDataList();
        case CharacterTreeIndexType::Item:
            return GetPassiveItemDataList();
        default:
            break;
    }
    return s_vEmptyChanges;
}

const TreeIndexList& Character::GetActiveChanges(const IndexedString& sTreeIndexType) const
{
    const CharacterTreeIndexType eTreeIndexType = StringToCharacterTreeIndexType(sTreeIndexType);
    switch(eTreeIndexType)
    {
        case CharacterTreeIndexType::Skill:
            return GetActiveSkillDataList();
        case CharacterTreeIndexType::Item:
            return GetActiveItemDataList();
        default:
            break;
    }
    return s_vEmptyChanges;
}

const TreeIndexList& Character::GetActionableChanges(const IndexedString& sTreeIndexType) const
{
    const CharacterTreeIndexType eTreeIndexType = StringToCharacterTreeIndexType(sTreeIndexType);
    switch(eTreeIndexType)
    {
        case CharacterTreeIndexType::Skill:
            return GetActionableSkillDataList();
        case CharacterTreeIndexType::Item:
            return GetActionableItemDataList();
        default:
            break;
    }
    return s_vEmptyChanges;
}

Bool Character::operator==(const Character& other) const
{
    return (Json(*this) == Json(other));
}

Bool Character::operator!=(const Character& other) const
{
    return not operator==(other);
}

void Character::UpdateEquipmentRatings(const IndexedString& sSegment)
{
    // Get character data
    STDSharedPtr<const CharacterProgressData> pProgressData = GetProgressSegment(sSegment);
    STDSharedPtr<CharacterBattleData> pBattleData = GetBattleSegment(sSegment);
    if(!pProgressData || !pBattleData)
    {
        return;
    }

    // Update ratings
    pBattleData->UpdateEquipmentRatings(GetCurrentWeaponSet(), GetEquippedItems(), *pProgressData);
}

void Character::UpdateAvailableChanges(const IndexedString& sSegment)
{
    // Fill skill indices
    TreeIndexList vSkillPassives;
    TreeIndexList vSkillActives;
    TreeIndexList vSkillActionables;
    FillSkillStatChangeLists(GetCharacterID(), vSkillPassives, vSkillActives, vSkillActionables, true);

    // Fill item indices
    TreeIndexList vItemPassives;
    TreeIndexList vItemActives;
    TreeIndexList vItemActionables;
    FillItemStatChangeLists(GetAllEquippedItems(GetCharacterID()), vItemPassives, vItemActives, vItemActionables);

    // Add to stored changes
    SetPassiveSkillDataList(vSkillPassives);
    SetActiveSkillDataList(vSkillActives);
    SetActionableSkillDataList(vSkillActionables);
    SetPassiveItemDataList(vItemPassives);
    SetActiveItemDataList(vItemActives);
    SetActionableItemDataList(vItemActionables);
}

void Character::UpdateAvailableActions(const IndexedString& sSegment)
{
    // Clear stored actions
    CharacterActionSharedPtrList& vAvailableActions = GetAvailableActions();
    vAvailableActions.clear();

    // Look at each type of tree index
    for(const IndexedString& sIndexTreeType : CharacterTreeIndexType::_names())
    {
        // Skip invalid tree types
        if(sIndexTreeType.IsNone())
        {
            continue;
        }

        // Get actionable data
        Bool bIsSkillAction = sIndexTreeType == IndexedString("Skill");

        // Look at each active change index of that type
        for(const TreeIndex& index : GetActionableChanges(sIndexTreeType))
        {
            // Look at each weapon set
            for(const IndexedString& sWeaponSet : CharacterWeaponSetType::_names())
            {
                // Skip invalid weapon sets
                if(sWeaponSet.IsNone())
                {
                    continue;
                }

                // Add skill actions
                CharacterActionSharedPtrList vSkillActions;
                if(bIsSkillAction && GenerateSkillCharacterActions(index, GetCharacterID(), sWeaponSet, vSkillActions))
                {
                   vAvailableActions.insert(vAvailableActions.end(), vSkillActions.begin(), vSkillActions.end());
                }

                // Add item actions
                CharacterActionSharedPtrList vItemActions;
                if(bIsSkillAction && GenerateItemCharacterActions(index, GetCharacterID(), sWeaponSet, vItemActions))
                {
                   vAvailableActions.insert(vAvailableActions.end(), vItemActions.begin(), vItemActions.end());
                }
            }
        }
    }
}

void Character::UpdateAvailableAP(const IndexedString& sSegment)
{
    // Get character data
    STDSharedPtr<CharacterProgressData> pProgressData = GetProgressSegment(sSegment);
    if(!pProgressData)
    {
        return;
    }

    // Get weapon skills
    TreeIndexList vWeaponSkills = GetWeaponSkills(GetCharacterID(), true);
    if(vWeaponSkills.empty())
    {
        return;
    }

    // Update available AP
    pProgressData->UpdateAvailableAP(vWeaponSkills);
}

void Character::UpdateSkillRankings(const IndexedString& sSegment)
{
    const SkillUseTrackingMapType& tSkillTracking = GetSkillUseTrackingMap();
    for(auto it = tSkillTracking.begin(); it != tSkillTracking.end(); it++)
    {
        const IndexedString& sSkillType = it->first;
        UInt uUseCount = it->second;
        if(sSkillType.IsNone() || uUseCount == 0)
        {
            continue;
        }

        Character::CharacterSkillFunctionNode node = GetSkillFunctions(sSkillType);
        if(node.IsValid())
        {
            UByte uRank = node.GetRank(*this);
            if(uRank >= s_kuMaxSkillRank)
            {
                continue;
            }

            UByte uCurrent = node.GetCurrent(*this);
            node.SetCurrent(*this, uCurrent + 1);
            if(static_cast<UInt>(uCurrent + 1) >= s_kuSkillRankUpgradeAmount)
            {
                node.SetCurrent(*this, 0);
                node.SetRank(*this, uRank + 1);
            }
        }
    }
}

#define RETURN_SKILL_FUNCTION_NODE(name)                    \
{                                                           \
    CharacterSkillFunctionNode node;                        \
    node.fnGetCurrent = &Character::Get##name##Current;     \
    node.fnGetRank = &Character::Get##name##Rank;           \
    node.fnSetCurrent = &Character::Set##name##Current;     \
    node.fnSetRank = &Character::Set##name##Rank;           \
    return node;                                            \
}

Character::CharacterSkillFunctionNode Character::GetSkillFunctions(const IndexedString& sSkillType) const
{
    SkillWeaponType eSkillWeaponType = IsValidSkillWeaponType(sSkillType) ? StringToSkillWeaponType(sSkillType) : +SkillWeaponType::None;
    switch(eSkillWeaponType)
    {
        case SkillWeaponType::Slash: RETURN_SKILL_FUNCTION_NODE(Slash);
        case SkillWeaponType::Sever: RETURN_SKILL_FUNCTION_NODE(Sever);
        case SkillWeaponType::Slice: RETURN_SKILL_FUNCTION_NODE(Slice);
        case SkillWeaponType::Slit: RETURN_SKILL_FUNCTION_NODE(Slit);
        case SkillWeaponType::Cleave: RETURN_SKILL_FUNCTION_NODE(Cleave);
        case SkillWeaponType::Decapitate: RETURN_SKILL_FUNCTION_NODE(Decapitate);
        case SkillWeaponType::Parry: RETURN_SKILL_FUNCTION_NODE(Parry);
        case SkillWeaponType::Riposte: RETURN_SKILL_FUNCTION_NODE(Riposte);
        case SkillWeaponType::Bash: RETURN_SKILL_FUNCTION_NODE(Bash);
        case SkillWeaponType::Smash: RETURN_SKILL_FUNCTION_NODE(Smash);
        case SkillWeaponType::Impact: RETURN_SKILL_FUNCTION_NODE(Impact);
        case SkillWeaponType::Crush: RETURN_SKILL_FUNCTION_NODE(Crush);
        case SkillWeaponType::Break: RETURN_SKILL_FUNCTION_NODE(Break);
        case SkillWeaponType::Crack: RETURN_SKILL_FUNCTION_NODE(Crack);
        case SkillWeaponType::Block: RETURN_SKILL_FUNCTION_NODE(Block);
        case SkillWeaponType::Rush: RETURN_SKILL_FUNCTION_NODE(Rush);
        case SkillWeaponType::Pierce: RETURN_SKILL_FUNCTION_NODE(Pierce);
        case SkillWeaponType::Drill: RETURN_SKILL_FUNCTION_NODE(Drill);
        case SkillWeaponType::Shoot: RETURN_SKILL_FUNCTION_NODE(Shoot);
        case SkillWeaponType::Impale: RETURN_SKILL_FUNCTION_NODE(Impale);
        case SkillWeaponType::StealthStrike: RETURN_SKILL_FUNCTION_NODE(StealthStrike);
        case SkillWeaponType::CriticalShot: RETURN_SKILL_FUNCTION_NODE(CriticalShot);
        case SkillWeaponType::Dodge: RETURN_SKILL_FUNCTION_NODE(Dodge);
        case SkillWeaponType::Counter: RETURN_SKILL_FUNCTION_NODE(Counter);
        default:
            break;
    }

    SkillAlchemyType eSkillAlchemyType = IsValidSkillAlchemyType(sSkillType) ? StringToSkillAlchemyType(sSkillType) : +SkillAlchemyType::None;
    switch(eSkillAlchemyType)
    {
        case SkillAlchemyType::Healer: RETURN_SKILL_FUNCTION_NODE(Healer);
        case SkillAlchemyType::Alchemist: RETURN_SKILL_FUNCTION_NODE(Alchemist);
        case SkillAlchemyType::Energist: RETURN_SKILL_FUNCTION_NODE(Energist);
        case SkillAlchemyType::Chemist: RETURN_SKILL_FUNCTION_NODE(Chemist);
        default:
            break;
    }

    SkillBreakdownType eSkillBreakdownType = IsValidSkillBreakdownType(sSkillType) ? StringToSkillBreakdownType(sSkillType) : +SkillBreakdownType::None;
    switch(eSkillBreakdownType)
    {
        case SkillBreakdownType::Hammerbane: RETURN_SKILL_FUNCTION_NODE(Hammerbane);
        case SkillBreakdownType::Spellbane: RETURN_SKILL_FUNCTION_NODE(Spellbane);
        case SkillBreakdownType::Bowbane: RETURN_SKILL_FUNCTION_NODE(Bowbane);
        case SkillBreakdownType::Swordbane: RETURN_SKILL_FUNCTION_NODE(Swordbane);
        case SkillBreakdownType::Threadbare: RETURN_SKILL_FUNCTION_NODE(Threadbare);
        case SkillBreakdownType::StudRemover: RETURN_SKILL_FUNCTION_NODE(StudRemover);
        case SkillBreakdownType::Scalebane: RETURN_SKILL_FUNCTION_NODE(Scalebane);
        case SkillBreakdownType::Platebane: RETURN_SKILL_FUNCTION_NODE(Platebane);
        case SkillBreakdownType::Goldbane: RETURN_SKILL_FUNCTION_NODE(Goldbane);
        case SkillBreakdownType::Shieldbane: RETURN_SKILL_FUNCTION_NODE(Shieldbane);
        default:
            break;
    }

    SkillCombatType eSkillCombatType = IsValidSkillCombatType(sSkillType) ? StringToSkillCombatType(sSkillType) : +SkillCombatType::None;
    switch(eSkillCombatType)
    {
        case SkillCombatType::Barbarian: RETURN_SKILL_FUNCTION_NODE(Barbarian);
        case SkillCombatType::Mage: RETURN_SKILL_FUNCTION_NODE(Mage);
        case SkillCombatType::Rogue: RETURN_SKILL_FUNCTION_NODE(Rogue);
        case SkillCombatType::Blademaster: RETURN_SKILL_FUNCTION_NODE(Blademaster);
        case SkillCombatType::Avatar: RETURN_SKILL_FUNCTION_NODE(Avatar);
        case SkillCombatType::Ambidextrous: RETURN_SKILL_FUNCTION_NODE(Ambidextrous);
        case SkillCombatType::Focused: RETURN_SKILL_FUNCTION_NODE(Focused);
        case SkillCombatType::Stalwart: RETURN_SKILL_FUNCTION_NODE(Stalwart);
        default:
            break;
    }

    SkillCraftingType eSkillCraftingType = IsValidSkillCraftingType(sSkillType) ? StringToSkillCraftingType(sSkillType) : +SkillCraftingType::None;
    switch(eSkillCraftingType)
    {
        case SkillCraftingType::Hammersmith: RETURN_SKILL_FUNCTION_NODE(Hammersmith);
        case SkillCraftingType::Spellsmith: RETURN_SKILL_FUNCTION_NODE(Spellsmith);
        case SkillCraftingType::Bowsmith: RETURN_SKILL_FUNCTION_NODE(Bowsmith);
        case SkillCraftingType::Swordsmith: RETURN_SKILL_FUNCTION_NODE(Swordsmith);
        case SkillCraftingType::Weaver: RETURN_SKILL_FUNCTION_NODE(Weaver);
        case SkillCraftingType::Tanner: RETURN_SKILL_FUNCTION_NODE(Tanner);
        case SkillCraftingType::Scalesmith: RETURN_SKILL_FUNCTION_NODE(Scalesmith);
        case SkillCraftingType::Platesmith: RETURN_SKILL_FUNCTION_NODE(Platesmith);
        case SkillCraftingType::Goldsmith: RETURN_SKILL_FUNCTION_NODE(Goldsmith);
        case SkillCraftingType::Shieldsmith: RETURN_SKILL_FUNCTION_NODE(Shieldsmith);
        default:
            break;
    }

    SkillAffinityType eSkillAffinityType = IsValidSkillAffinityType(sSkillType) ? StringToSkillAffinityType(sSkillType) : +SkillAffinityType::None;
    switch(eSkillAffinityType)
    {
        case SkillAffinityType::Holy: RETURN_SKILL_FUNCTION_NODE(Holy);
        case SkillAffinityType::Fire: RETURN_SKILL_FUNCTION_NODE(Fire);
        case SkillAffinityType::Ice: RETURN_SKILL_FUNCTION_NODE(Ice);
        case SkillAffinityType::Shock: RETURN_SKILL_FUNCTION_NODE(Shock);
        case SkillAffinityType::Dark: RETURN_SKILL_FUNCTION_NODE(Dark);
        case SkillAffinityType::Light: RETURN_SKILL_FUNCTION_NODE(Light);
        case SkillAffinityType::Force: RETURN_SKILL_FUNCTION_NODE(Force);
        case SkillAffinityType::Mind: RETURN_SKILL_FUNCTION_NODE(Mind);
        case SkillAffinityType::Earth: RETURN_SKILL_FUNCTION_NODE(Earth);
        case SkillAffinityType::Blood: RETURN_SKILL_FUNCTION_NODE(Blood);
        case SkillAffinityType::Flesh: RETURN_SKILL_FUNCTION_NODE(Flesh);
        case SkillAffinityType::Wind: RETURN_SKILL_FUNCTION_NODE(Wind);
        default:
            break;
    }
    return CharacterSkillFunctionNode();
}

Bool Character::DoesChangeMeetActiveRequirements(const StatChange& change) const
{
    // Check change requirements
    if(change.DoesHaveItemEquippedRequirements() && change.DoesMeetItemEquippedRequirements(GetCharacterID(), GetCurrentWeaponSet()))
    {
        return true;
    }
    return false;
}

Bool Character::DoesChangeMeetActiveRequirements(const StatChange& change, const CharacterActionSharedPtr& pAction) const
{
    // Make sure there are some entries first
    if(!pAction || pAction->GetActionEntries().empty())
    {
        return false;
    }

    // Find out target information for action
    Bool bSelfIsActionSender = (GetCharacterTargetType() == pAction->GetSourceTargetType());
    Bool bSelfIsActionRecipient = STDVectorDoesIntersectElement<IndexedString>(pAction->GetAllDestinationTargetTypes(), GetCharacterTargetType());

    // Check change requirements
    // Only check attack/defend if they are the attacker/defender referenced by the action
    if(change.DoesHaveItemEquippedRequirements())
    {
        return change.DoesMeetItemEquippedRequirements(GetCharacterID(), GetCurrentWeaponSet());
    }
    else if(change.DoesHaveItemUsedRequirements())
    {
        return change.DoesMeetItemUsedRequirements(GetActionTypes(change.GetItemTreeIndex()));
    }
    else if(change.DoesHaveAttackRequirements() && bSelfIsActionSender)
    {
        return change.DoesMeetAttackRequirements(pAction->GetAllActionTypes(), pAction->GetPreviousActionTypes());
    }
    else if(change.DoesHaveDefendRequirements() && bSelfIsActionRecipient)
    {
        return change.DoesMeetDefendRequirements(pAction->GetAllActionTypes(), pAction->GetPreviousActionTypes());
    }
    return false;
}

void Character::ApplyPassiveChanges()
{
    // Data sources should come from base but apply to passive
    const IndexedString sSourceSegment("Base");
    const IndexedString sDestSegment("Passive");

    // Get character base data
    STDSharedPtr<CharacterProgressData> pProgressData = GetProgressDataBase();
    STDSharedPtr<CharacterBattleData> pBattleData = GetBattleDataBase();
    if(!pProgressData || !pBattleData)
    {
        return;
    }

    // Copy passive data into active to start with
    SetProgressDataPassives(STDMakeSharedPtr<CharacterProgressData>(*pProgressData));
    SetBattleDataPassives(STDMakeSharedPtr<CharacterBattleData>(*pBattleData));

    // Apply passives
    for(const IndexedString& sTreeIndexType : CharacterTreeIndexType::_names())
    {
        for(const TreeIndex& index : GetPassiveChanges(sTreeIndexType))
        {
            for(StatChange change : GetStatChangesFromTreeIndex(sTreeIndexType, index))
            {
                // Resolve target placeholders
                ResolveTargetPlaceholders(sSourceSegment, change);

                // Apply change
                Bool bAllChangesApplied = false;
                Bool bAtLeastOneChange = false;
                CharacterManager::GetInstance()->ApplyStatChange(sDestSegment, change, bAllChangesApplied, bAtLeastOneChange);
            }
        }
    }
}

void Character::ApplyActiveChanges(const CharacterActionSharedPtr& pAction)
{
    // Data sources should come from passive but apply to active
    const IndexedString sSourceSegment("Passive");
    const IndexedString sDestSegment("Active");

    // Get character passive data
    STDSharedPtr<CharacterProgressData> pProgressData = GetProgressDataPassives();
    STDSharedPtr<CharacterBattleData> pBattleData = GetBattleDataPassives();
    if(!pProgressData || !pBattleData)
    {
        return;
    }

    // Copy passive data into active to start with
    SetProgressDataActives(STDMakeSharedPtr<CharacterProgressData>(*pProgressData));
    SetBattleDataActives(STDMakeSharedPtr<CharacterBattleData>(*pBattleData));

    // Apply actives
    for(const IndexedString& sTreeIndexType : CharacterTreeIndexType::_names())
    {
        for(const TreeIndex& index : GetActiveChanges(sTreeIndexType))
        {
            for(const StatChange& change : GetStatChangesFromTreeIndex(sTreeIndexType, index))
            {
                // Ignore active changes that do not meet requirements
                if(!DoesChangeMeetActiveRequirements(change, pAction))
                {
                    continue;
                }

                // Make a local copy now that we have passed the check
                StatChange localStatChange(change);

                // Resolve target placeholders
                ResolveTargetPlaceholders(sSourceSegment, localStatChange);

                // Apply change
                Bool bAllChangesApplied = false;
                Bool bAtLeastOneChange = false;
                CharacterManager::GetInstance()->ApplyStatChange(sDestSegment, localStatChange, bAllChangesApplied, bAtLeastOneChange);
            }
        }
    }

    // Apply prolonged stat changes
    for(const StatChangeEntry& entry : GetProlongedStatChangeEntries())
    {
        CharacterManager::GetInstance()->ApplyStatChangeEntry(sDestSegment, entry);
    }
}

void Character::ClearActiveChanges()
{
    GetProgressDataActives().reset();
    GetBattleDataActives().reset();
}

void to_json(Json& jsonData, const Character& obj)
{
    // Get current configuration
    const Config& config = ConfigManager::GetInstance()->GetCurrentConfig();

    // Basic character data
    SET_JSON_DATA_IF_NOT_DEFAULT(FirstName, IndexedString(config.GetDefaultFirstName()));
    SET_JSON_DATA_IF_NOT_DEFAULT(LastName, IndexedString(config.GetDefaultLastName()));
    SET_JSON_DATA_IF_NOT_DEFAULT(Age, config.GetDefaultAge());
    SET_JSON_DATA_IF_NOT_DEFAULT(Gender, IndexedString(config.GetDefaultGender()));
    SET_JSON_DATA_IF_NOT_DEFAULT(Hair, IndexedString(config.GetDefaultHair()));
    SET_JSON_DATA_IF_NOT_DEFAULT(Eyes, IndexedString(config.GetDefaultEyes()));
    SET_JSON_DATA_IF_NOT_DEFAULT(Handedness, IndexedString(config.GetDefaultHandedness()));
    SET_JSON_DATA_IF_NOT_DEFAULT(BaseRace, IndexedString(config.GetDefaultBaseRace()));
    SET_JSON_DATA_IF_NOT_DEFAULT(TransformedRace, IndexedString(config.GetDefaultTransformedRace()));
    SET_JSON_DATA_IF_NOT_DEFAULT(PowerSet, IndexedString(config.GetDefaultPowerSet()));
    SET_JSON_DATA_IF_NOT_EMPTY(EquippedItems);
    SET_JSON_DATA_IF_NOT_DEFAULT(CurrentWeaponSet, IndexedString(config.GetDefaultCurrentWeaponSet()));

    // Combat Skills
    SET_JSON_DATA_IF_NOT_DEFAULT(BarbarianCurrent, config.GetDefaultBarbarianCurrent());
    SET_JSON_DATA_IF_NOT_DEFAULT(BarbarianRank, config.GetDefaultBarbarianRank());
    SET_JSON_DATA_IF_NOT_DEFAULT(MageCurrent, config.GetDefaultMageCurrent());
    SET_JSON_DATA_IF_NOT_DEFAULT(MageRank, config.GetDefaultMageRank());
    SET_JSON_DATA_IF_NOT_DEFAULT(RogueCurrent, config.GetDefaultRogueCurrent());
    SET_JSON_DATA_IF_NOT_DEFAULT(RogueRank, config.GetDefaultRogueRank());
    SET_JSON_DATA_IF_NOT_DEFAULT(BlademasterCurrent, config.GetDefaultBlademasterCurrent());
    SET_JSON_DATA_IF_NOT_DEFAULT(BlademasterRank, config.GetDefaultBlademasterRank());
    SET_JSON_DATA_IF_NOT_DEFAULT(AvatarCurrent, config.GetDefaultAvatarCurrent());
    SET_JSON_DATA_IF_NOT_DEFAULT(AvatarRank, config.GetDefaultAvatarRank());
    SET_JSON_DATA_IF_NOT_DEFAULT(AmbidextrousCurrent, config.GetDefaultAmbidextrousCurrent());
    SET_JSON_DATA_IF_NOT_DEFAULT(AmbidextrousRank, config.GetDefaultAmbidextrousRank());
    SET_JSON_DATA_IF_NOT_DEFAULT(FocusedCurrent, config.GetDefaultFocusedCurrent());
    SET_JSON_DATA_IF_NOT_DEFAULT(FocusedRank, config.GetDefaultFocusedRank());
    SET_JSON_DATA_IF_NOT_DEFAULT(StalwartCurrent, config.GetDefaultStalwartCurrent());
    SET_JSON_DATA_IF_NOT_DEFAULT(StalwartRank, config.GetDefaultStalwartRank());

    // Weapon Skills
    SET_JSON_DATA_IF_NOT_DEFAULT(SlashCurrent, config.GetDefaultSlashCurrent());
    SET_JSON_DATA_IF_NOT_DEFAULT(SlashRank, config.GetDefaultSlashRank());
    SET_JSON_DATA_IF_NOT_DEFAULT(SeverCurrent, config.GetDefaultSeverCurrent());
    SET_JSON_DATA_IF_NOT_DEFAULT(SeverRank, config.GetDefaultSeverRank());
    SET_JSON_DATA_IF_NOT_DEFAULT(SliceCurrent, config.GetDefaultSliceCurrent());
    SET_JSON_DATA_IF_NOT_DEFAULT(SliceRank, config.GetDefaultSliceRank());
    SET_JSON_DATA_IF_NOT_DEFAULT(SlitCurrent, config.GetDefaultSlitCurrent());
    SET_JSON_DATA_IF_NOT_DEFAULT(SlitRank, config.GetDefaultSlitRank());
    SET_JSON_DATA_IF_NOT_DEFAULT(CleaveCurrent, config.GetDefaultCleaveCurrent());
    SET_JSON_DATA_IF_NOT_DEFAULT(CleaveRank, config.GetDefaultCleaveRank());
    SET_JSON_DATA_IF_NOT_DEFAULT(DecapitateCurrent, config.GetDefaultDecapitateCurrent());
    SET_JSON_DATA_IF_NOT_DEFAULT(DecapitateRank, config.GetDefaultDecapitateRank());
    SET_JSON_DATA_IF_NOT_DEFAULT(ParryCurrent, config.GetDefaultParryCurrent());
    SET_JSON_DATA_IF_NOT_DEFAULT(ParryRank, config.GetDefaultParryRank());
    SET_JSON_DATA_IF_NOT_DEFAULT(RiposteCurrent, config.GetDefaultRiposteCurrent());
    SET_JSON_DATA_IF_NOT_DEFAULT(RiposteRank, config.GetDefaultRiposteRank());
    SET_JSON_DATA_IF_NOT_DEFAULT(BashCurrent, config.GetDefaultBashCurrent());
    SET_JSON_DATA_IF_NOT_DEFAULT(BashRank, config.GetDefaultBashRank());
    SET_JSON_DATA_IF_NOT_DEFAULT(SmashCurrent, config.GetDefaultSmashCurrent());
    SET_JSON_DATA_IF_NOT_DEFAULT(SmashRank, config.GetDefaultSmashRank());
    SET_JSON_DATA_IF_NOT_DEFAULT(CrushCurrent, config.GetDefaultCrushCurrent());
    SET_JSON_DATA_IF_NOT_DEFAULT(CrushRank, config.GetDefaultCrushRank());
    SET_JSON_DATA_IF_NOT_DEFAULT(ImpactCurrent, config.GetDefaultImpactCurrent());
    SET_JSON_DATA_IF_NOT_DEFAULT(ImpactRank, config.GetDefaultImpactRank());
    SET_JSON_DATA_IF_NOT_DEFAULT(BreakCurrent, config.GetDefaultBreakCurrent());
    SET_JSON_DATA_IF_NOT_DEFAULT(BreakRank, config.GetDefaultBreakRank());
    SET_JSON_DATA_IF_NOT_DEFAULT(CrackCurrent, config.GetDefaultCrackCurrent());
    SET_JSON_DATA_IF_NOT_DEFAULT(CrackRank, config.GetDefaultCrackRank());
    SET_JSON_DATA_IF_NOT_DEFAULT(BlockCurrent, config.GetDefaultBlockCurrent());
    SET_JSON_DATA_IF_NOT_DEFAULT(BlockRank, config.GetDefaultBlockRank());
    SET_JSON_DATA_IF_NOT_DEFAULT(RushCurrent, config.GetDefaultRushCurrent());
    SET_JSON_DATA_IF_NOT_DEFAULT(RushRank, config.GetDefaultRushRank());
    SET_JSON_DATA_IF_NOT_DEFAULT(PierceCurrent, config.GetDefaultPierceCurrent());
    SET_JSON_DATA_IF_NOT_DEFAULT(PierceRank, config.GetDefaultPierceRank());
    SET_JSON_DATA_IF_NOT_DEFAULT(DrillCurrent, config.GetDefaultDrillCurrent());
    SET_JSON_DATA_IF_NOT_DEFAULT(DrillRank, config.GetDefaultDrillRank());
    SET_JSON_DATA_IF_NOT_DEFAULT(ShootCurrent, config.GetDefaultShootCurrent());
    SET_JSON_DATA_IF_NOT_DEFAULT(ShootRank, config.GetDefaultShootRank());
    SET_JSON_DATA_IF_NOT_DEFAULT(ImpaleCurrent, config.GetDefaultImpaleCurrent());
    SET_JSON_DATA_IF_NOT_DEFAULT(ImpaleRank, config.GetDefaultImpaleRank());
    SET_JSON_DATA_IF_NOT_DEFAULT(StealthStrikeCurrent, config.GetDefaultStealthStrikeCurrent());
    SET_JSON_DATA_IF_NOT_DEFAULT(StealthStrikeRank, config.GetDefaultStealthStrikeRank());
    SET_JSON_DATA_IF_NOT_DEFAULT(CriticalShotCurrent, config.GetDefaultCriticalShotCurrent());
    SET_JSON_DATA_IF_NOT_DEFAULT(CriticalShotRank, config.GetDefaultCriticalShotRank());
    SET_JSON_DATA_IF_NOT_DEFAULT(DodgeCurrent, config.GetDefaultDodgeCurrent());
    SET_JSON_DATA_IF_NOT_DEFAULT(DodgeRank, config.GetDefaultDodgeRank());
    SET_JSON_DATA_IF_NOT_DEFAULT(CounterCurrent, config.GetDefaultCounterCurrent());
    SET_JSON_DATA_IF_NOT_DEFAULT(CounterRank, config.GetDefaultCounterRank());

    // Alchemy Skills
    SET_JSON_DATA_IF_NOT_DEFAULT(HealerCurrent, config.GetDefaultHealerCurrent());
    SET_JSON_DATA_IF_NOT_DEFAULT(HealerRank, config.GetDefaultHealerRank());
    SET_JSON_DATA_IF_NOT_DEFAULT(AlchemistCurrent, config.GetDefaultAlchemistCurrent());
    SET_JSON_DATA_IF_NOT_DEFAULT(AlchemistRank, config.GetDefaultAlchemistRank());
    SET_JSON_DATA_IF_NOT_DEFAULT(EnergistCurrent, config.GetDefaultEnergistCurrent());
    SET_JSON_DATA_IF_NOT_DEFAULT(EnergistRank, config.GetDefaultEnergistRank());
    SET_JSON_DATA_IF_NOT_DEFAULT(ChemistCurrent, config.GetDefaultChemistCurrent());
    SET_JSON_DATA_IF_NOT_DEFAULT(ChemistRank, config.GetDefaultChemistRank());

    // Crafting Skills
    SET_JSON_DATA_IF_NOT_DEFAULT(HammersmithCurrent, config.GetDefaultHammersmithCurrent());
    SET_JSON_DATA_IF_NOT_DEFAULT(HammersmithRank, config.GetDefaultHammersmithRank());
    SET_JSON_DATA_IF_NOT_DEFAULT(SpellsmithCurrent, config.GetDefaultSpellsmithCurrent());
    SET_JSON_DATA_IF_NOT_DEFAULT(SpellsmithRank, config.GetDefaultSpellsmithRank());
    SET_JSON_DATA_IF_NOT_DEFAULT(BowsmithCurrent, config.GetDefaultBowsmithCurrent());
    SET_JSON_DATA_IF_NOT_DEFAULT(BowsmithRank, config.GetDefaultBowsmithRank());
    SET_JSON_DATA_IF_NOT_DEFAULT(SwordsmithCurrent, config.GetDefaultSwordsmithCurrent());
    SET_JSON_DATA_IF_NOT_DEFAULT(SwordsmithRank, config.GetDefaultSwordsmithRank());
    SET_JSON_DATA_IF_NOT_DEFAULT(WeaverCurrent, config.GetDefaultWeaverCurrent());
    SET_JSON_DATA_IF_NOT_DEFAULT(WeaverRank, config.GetDefaultWeaverRank());
    SET_JSON_DATA_IF_NOT_DEFAULT(TannerCurrent, config.GetDefaultTannerCurrent());
    SET_JSON_DATA_IF_NOT_DEFAULT(TannerRank, config.GetDefaultTannerRank());
    SET_JSON_DATA_IF_NOT_DEFAULT(ScalesmithCurrent, config.GetDefaultScalesmithCurrent());
    SET_JSON_DATA_IF_NOT_DEFAULT(ScalesmithRank, config.GetDefaultScalesmithRank());
    SET_JSON_DATA_IF_NOT_DEFAULT(PlatesmithCurrent, config.GetDefaultPlatesmithCurrent());
    SET_JSON_DATA_IF_NOT_DEFAULT(PlatesmithRank, config.GetDefaultPlatesmithRank());
    SET_JSON_DATA_IF_NOT_DEFAULT(GoldsmithCurrent, config.GetDefaultGoldsmithCurrent());
    SET_JSON_DATA_IF_NOT_DEFAULT(GoldsmithRank, config.GetDefaultGoldsmithRank());
    SET_JSON_DATA_IF_NOT_DEFAULT(ShieldsmithCurrent, config.GetDefaultShieldsmithCurrent());
    SET_JSON_DATA_IF_NOT_DEFAULT(ShieldsmithRank, config.GetDefaultShieldsmithRank());

    // Breakdown Skills
    SET_JSON_DATA_IF_NOT_DEFAULT(HammerbaneCurrent, config.GetDefaultHammerbaneCurrent());
    SET_JSON_DATA_IF_NOT_DEFAULT(HammerbaneRank, config.GetDefaultHammerbaneRank());
    SET_JSON_DATA_IF_NOT_DEFAULT(SpellbaneCurrent, config.GetDefaultSpellbaneCurrent());
    SET_JSON_DATA_IF_NOT_DEFAULT(SpellbaneRank, config.GetDefaultSpellbaneRank());
    SET_JSON_DATA_IF_NOT_DEFAULT(BowbaneCurrent, config.GetDefaultBowbaneCurrent());
    SET_JSON_DATA_IF_NOT_DEFAULT(BowbaneRank, config.GetDefaultBowbaneRank());
    SET_JSON_DATA_IF_NOT_DEFAULT(SwordbaneCurrent, config.GetDefaultSwordbaneCurrent());
    SET_JSON_DATA_IF_NOT_DEFAULT(SwordbaneRank, config.GetDefaultSwordbaneRank());
    SET_JSON_DATA_IF_NOT_DEFAULT(ThreadbareCurrent, config.GetDefaultThreadbareCurrent());
    SET_JSON_DATA_IF_NOT_DEFAULT(ThreadbareRank, config.GetDefaultThreadbareRank());
    SET_JSON_DATA_IF_NOT_DEFAULT(StudRemoverCurrent, config.GetDefaultStudRemoverCurrent());
    SET_JSON_DATA_IF_NOT_DEFAULT(StudRemoverRank, config.GetDefaultStudRemoverRank());
    SET_JSON_DATA_IF_NOT_DEFAULT(ScalebaneCurrent, config.GetDefaultScalebaneCurrent());
    SET_JSON_DATA_IF_NOT_DEFAULT(ScalebaneRank, config.GetDefaultScalebaneRank());
    SET_JSON_DATA_IF_NOT_DEFAULT(PlatebaneCurrent, config.GetDefaultPlatebaneCurrent());
    SET_JSON_DATA_IF_NOT_DEFAULT(PlatebaneRank, config.GetDefaultPlatebaneRank());
    SET_JSON_DATA_IF_NOT_DEFAULT(GoldbaneCurrent, config.GetDefaultGoldbaneCurrent());
    SET_JSON_DATA_IF_NOT_DEFAULT(GoldbaneRank, config.GetDefaultGoldbaneRank());
    SET_JSON_DATA_IF_NOT_DEFAULT(ShieldbaneCurrent, config.GetDefaultShieldbaneCurrent());
    SET_JSON_DATA_IF_NOT_DEFAULT(ShieldbaneRank, config.GetDefaultShieldbaneRank());

    // Affinity Skills
    SET_JSON_DATA_IF_NOT_DEFAULT(HolyCurrent, config.GetDefaultHolyCurrent());
    SET_JSON_DATA_IF_NOT_DEFAULT(HolyRank, config.GetDefaultHolyRank());
    SET_JSON_DATA_IF_NOT_DEFAULT(FireCurrent, config.GetDefaultFireCurrent());
    SET_JSON_DATA_IF_NOT_DEFAULT(FireRank, config.GetDefaultFireRank());
    SET_JSON_DATA_IF_NOT_DEFAULT(IceCurrent, config.GetDefaultIceCurrent());
    SET_JSON_DATA_IF_NOT_DEFAULT(IceRank, config.GetDefaultIceRank());
    SET_JSON_DATA_IF_NOT_DEFAULT(ShockCurrent, config.GetDefaultShockCurrent());
    SET_JSON_DATA_IF_NOT_DEFAULT(ShockRank, config.GetDefaultShockRank());
    SET_JSON_DATA_IF_NOT_DEFAULT(DarkCurrent, config.GetDefaultDarkCurrent());
    SET_JSON_DATA_IF_NOT_DEFAULT(DarkRank, config.GetDefaultDarkRank());
    SET_JSON_DATA_IF_NOT_DEFAULT(LightCurrent, config.GetDefaultLightCurrent());
    SET_JSON_DATA_IF_NOT_DEFAULT(LightRank, config.GetDefaultLightRank());
    SET_JSON_DATA_IF_NOT_DEFAULT(ForceCurrent, config.GetDefaultForceCurrent());
    SET_JSON_DATA_IF_NOT_DEFAULT(ForceRank, config.GetDefaultForceRank());
    SET_JSON_DATA_IF_NOT_DEFAULT(MindCurrent, config.GetDefaultMindCurrent());
    SET_JSON_DATA_IF_NOT_DEFAULT(MindRank, config.GetDefaultMindRank());
    SET_JSON_DATA_IF_NOT_DEFAULT(EarthCurrent, config.GetDefaultEarthCurrent());
    SET_JSON_DATA_IF_NOT_DEFAULT(EarthRank, config.GetDefaultEarthRank());
    SET_JSON_DATA_IF_NOT_DEFAULT(BloodCurrent, config.GetDefaultBloodCurrent());
    SET_JSON_DATA_IF_NOT_DEFAULT(BloodRank, config.GetDefaultBloodRank());
    SET_JSON_DATA_IF_NOT_DEFAULT(FleshCurrent, config.GetDefaultFleshCurrent());
    SET_JSON_DATA_IF_NOT_DEFAULT(FleshRank, config.GetDefaultFleshRank());
    SET_JSON_DATA_IF_NOT_DEFAULT(WindCurrent, config.GetDefaultWindCurrent());
    SET_JSON_DATA_IF_NOT_DEFAULT(WindRank, config.GetDefaultWindRank());

    // Segmented progress data
    SET_JSON_DATA_IF_NOT_DEFAULT_FROM_PTR(ProgressDataBase, CharacterProgressData());
    SET_JSON_DATA_IF_NOT_DEFAULT_FROM_PTR(ProgressDataPassives, CharacterProgressData());

    // Segmented battle data
    SET_JSON_DATA_IF_NOT_DEFAULT_FROM_PTR(BattleDataBase, CharacterBattleData());
    SET_JSON_DATA_IF_NOT_DEFAULT_FROM_PTR(BattleDataPassives, CharacterBattleData());

    // List of passive/active/actionable data
    SET_JSON_DATA_IF_NOT_EMPTY(PassiveSkillDataList);
    SET_JSON_DATA_IF_NOT_EMPTY(ActiveSkillDataList);
    SET_JSON_DATA_IF_NOT_EMPTY(ActionableSkillDataList);
    SET_JSON_DATA_IF_NOT_EMPTY(PassiveItemDataList);
    SET_JSON_DATA_IF_NOT_EMPTY(ActiveItemDataList);
    SET_JSON_DATA_IF_NOT_EMPTY(ActionableItemDataList);

    // List of character actions
    SET_JSON_DATA_FROM_PTR_ARRAY_IF_NOT_EMPTY(AvailableActions);

    // Character ID
    SET_JSON_DATA_IF_NOT_DEFAULT(CharacterID, IndexedString(""));

    // Character target type
    SET_JSON_DATA_IF_NOT_DEFAULT(CharacterTargetType, IndexedString("None"));
}

void from_json(const Json& jsonData, Character& obj)
{
    // Get current configuration
    const Config& config = ConfigManager::GetInstance()->GetCurrentConfig();

    // Basic character data
    obj.SetFirstName(GET_JSON_DATA_OR_DEFAULT(FirstName, IndexedString, IndexedString(config.GetDefaultFirstName())));
    obj.SetLastName(GET_JSON_DATA_OR_DEFAULT(LastName, IndexedString, IndexedString(config.GetDefaultLastName())));
    obj.SetAge(GET_JSON_DATA_OR_DEFAULT(Age, Int, config.GetDefaultAge()));
    obj.SetGender(GET_JSON_DATA_OR_DEFAULT(Gender, IndexedString, IndexedString(config.GetDefaultGender())));
    obj.SetHair(GET_JSON_DATA_OR_DEFAULT(Hair, IndexedString, IndexedString(config.GetDefaultHair())));
    obj.SetEyes(GET_JSON_DATA_OR_DEFAULT(Eyes, IndexedString, IndexedString(config.GetDefaultEyes())));
    obj.SetHandedness(GET_JSON_DATA_OR_DEFAULT(Handedness, IndexedString, IndexedString(config.GetDefaultHandedness())));
    obj.SetBaseRace(GET_JSON_DATA_OR_DEFAULT(BaseRace, IndexedString, IndexedString(config.GetDefaultBaseRace())));
    obj.SetTransformedRace(GET_JSON_DATA_OR_DEFAULT(TransformedRace, IndexedString, IndexedString(config.GetDefaultTransformedRace())));
    obj.SetPowerSet(GET_JSON_DATA_OR_DEFAULT(PowerSet, IndexedString, IndexedString(config.GetDefaultPowerSet())));
    obj.SetEquippedItems(GET_JSON_DATA_OR_DEFAULT(EquippedItems, CharacterProgressItemList, CharacterProgressItemList()));
    obj.SetCurrentWeaponSet(GET_JSON_DATA_OR_DEFAULT(CurrentWeaponSet, IndexedString, IndexedString(config.GetDefaultCurrentWeaponSet())));

    // Combat Skills
    obj.SetBarbarianCurrent(GET_JSON_DATA_OR_DEFAULT(BarbarianCurrent, Int, config.GetDefaultBarbarianCurrent()));
    obj.SetBarbarianRank(GET_JSON_DATA_OR_DEFAULT(BarbarianRank, Int, config.GetDefaultBarbarianRank()));
    obj.SetMageCurrent(GET_JSON_DATA_OR_DEFAULT(MageCurrent, Int, config.GetDefaultMageCurrent()));
    obj.SetMageRank(GET_JSON_DATA_OR_DEFAULT(MageRank, Int, config.GetDefaultMageRank()));
    obj.SetRogueCurrent(GET_JSON_DATA_OR_DEFAULT(RogueCurrent, Int, config.GetDefaultRogueCurrent()));
    obj.SetRogueRank(GET_JSON_DATA_OR_DEFAULT(RogueRank, Int, config.GetDefaultRogueRank()));
    obj.SetBlademasterCurrent(GET_JSON_DATA_OR_DEFAULT(BlademasterCurrent, Int, config.GetDefaultBlademasterCurrent()));
    obj.SetBlademasterRank(GET_JSON_DATA_OR_DEFAULT(BlademasterRank, Int, config.GetDefaultBlademasterRank()));
    obj.SetAvatarCurrent(GET_JSON_DATA_OR_DEFAULT(AvatarCurrent, Int, config.GetDefaultAvatarCurrent()));
    obj.SetAvatarRank(GET_JSON_DATA_OR_DEFAULT(AvatarRank, Int, config.GetDefaultAvatarRank()));
    obj.SetAmbidextrousCurrent(GET_JSON_DATA_OR_DEFAULT(AmbidextrousCurrent, Int, config.GetDefaultAmbidextrousCurrent()));
    obj.SetAmbidextrousRank(GET_JSON_DATA_OR_DEFAULT(AmbidextrousRank, Int, config.GetDefaultAmbidextrousRank()));
    obj.SetFocusedCurrent(GET_JSON_DATA_OR_DEFAULT(FocusedCurrent, Int, config.GetDefaultFocusedCurrent()));
    obj.SetFocusedRank(GET_JSON_DATA_OR_DEFAULT(FocusedRank, Int, config.GetDefaultFocusedRank()));
    obj.SetStalwartCurrent(GET_JSON_DATA_OR_DEFAULT(StalwartCurrent, Int, config.GetDefaultStalwartCurrent()));
    obj.SetStalwartRank(GET_JSON_DATA_OR_DEFAULT(StalwartRank, Int, config.GetDefaultStalwartRank()));

    // Weapon Skills
    obj.SetSlashCurrent(GET_JSON_DATA_OR_DEFAULT(SlashCurrent, Int, config.GetDefaultSlashCurrent()));
    obj.SetSlashRank(GET_JSON_DATA_OR_DEFAULT(SlashRank, Int, config.GetDefaultSlashRank()));
    obj.SetSeverCurrent(GET_JSON_DATA_OR_DEFAULT(SeverCurrent, Int, config.GetDefaultSeverCurrent()));
    obj.SetSeverRank(GET_JSON_DATA_OR_DEFAULT(SeverRank, Int, config.GetDefaultSeverRank()));
    obj.SetSliceCurrent(GET_JSON_DATA_OR_DEFAULT(SliceCurrent, Int, config.GetDefaultSliceCurrent()));
    obj.SetSliceRank(GET_JSON_DATA_OR_DEFAULT(SliceRank, Int, config.GetDefaultSliceRank()));
    obj.SetSlitCurrent(GET_JSON_DATA_OR_DEFAULT(SlitCurrent, Int, config.GetDefaultSlitCurrent()));
    obj.SetSlitRank(GET_JSON_DATA_OR_DEFAULT(SlitRank, Int, config.GetDefaultSlitRank()));
    obj.SetCleaveCurrent(GET_JSON_DATA_OR_DEFAULT(CleaveCurrent, Int, config.GetDefaultCleaveCurrent()));
    obj.SetCleaveRank(GET_JSON_DATA_OR_DEFAULT(CleaveRank, Int, config.GetDefaultCleaveRank()));
    obj.SetDecapitateCurrent(GET_JSON_DATA_OR_DEFAULT(DecapitateCurrent, Int, config.GetDefaultDecapitateCurrent()));
    obj.SetDecapitateRank(GET_JSON_DATA_OR_DEFAULT(DecapitateRank, Int, config.GetDefaultDecapitateRank()));
    obj.SetParryCurrent(GET_JSON_DATA_OR_DEFAULT(ParryCurrent, Int, config.GetDefaultParryCurrent()));
    obj.SetParryRank(GET_JSON_DATA_OR_DEFAULT(ParryRank, Int, config.GetDefaultParryRank()));
    obj.SetRiposteCurrent(GET_JSON_DATA_OR_DEFAULT(RiposteCurrent, Int, config.GetDefaultRiposteCurrent()));
    obj.SetRiposteRank(GET_JSON_DATA_OR_DEFAULT(RiposteRank, Int, config.GetDefaultRiposteRank()));
    obj.SetBashCurrent(GET_JSON_DATA_OR_DEFAULT(BashCurrent, Int, config.GetDefaultBashCurrent()));
    obj.SetBashRank(GET_JSON_DATA_OR_DEFAULT(BashRank, Int, config.GetDefaultBashRank()));
    obj.SetSmashCurrent(GET_JSON_DATA_OR_DEFAULT(SmashCurrent, Int, config.GetDefaultSmashCurrent()));
    obj.SetSmashRank(GET_JSON_DATA_OR_DEFAULT(SmashRank, Int, config.GetDefaultSmashRank()));
    obj.SetCrushCurrent(GET_JSON_DATA_OR_DEFAULT(CrushCurrent, Int, config.GetDefaultCrushCurrent()));
    obj.SetCrushRank(GET_JSON_DATA_OR_DEFAULT(CrushRank, Int, config.GetDefaultCrushRank()));
    obj.SetImpactCurrent(GET_JSON_DATA_OR_DEFAULT(ImpactCurrent, Int, config.GetDefaultImpactCurrent()));
    obj.SetImpactRank(GET_JSON_DATA_OR_DEFAULT(ImpactRank, Int, config.GetDefaultImpactRank()));
    obj.SetBreakCurrent(GET_JSON_DATA_OR_DEFAULT(BreakCurrent, Int, config.GetDefaultBreakCurrent()));
    obj.SetBreakRank(GET_JSON_DATA_OR_DEFAULT(BreakRank, Int, config.GetDefaultBreakRank()));
    obj.SetCrackCurrent(GET_JSON_DATA_OR_DEFAULT(CrackCurrent, Int, config.GetDefaultCrackCurrent()));
    obj.SetCrackRank(GET_JSON_DATA_OR_DEFAULT(CrackRank, Int, config.GetDefaultCrackRank()));
    obj.SetBlockCurrent(GET_JSON_DATA_OR_DEFAULT(BlockCurrent, Int, config.GetDefaultBlockCurrent()));
    obj.SetBlockRank(GET_JSON_DATA_OR_DEFAULT(BlockRank, Int, config.GetDefaultBlockRank()));
    obj.SetRushCurrent(GET_JSON_DATA_OR_DEFAULT(RushCurrent, Int, config.GetDefaultRushCurrent()));
    obj.SetRushRank(GET_JSON_DATA_OR_DEFAULT(RushRank, Int, config.GetDefaultRushRank()));
    obj.SetPierceCurrent(GET_JSON_DATA_OR_DEFAULT(PierceCurrent, Int, config.GetDefaultPierceCurrent()));
    obj.SetPierceRank(GET_JSON_DATA_OR_DEFAULT(PierceRank, Int, config.GetDefaultPierceRank()));
    obj.SetDrillCurrent(GET_JSON_DATA_OR_DEFAULT(DrillCurrent, Int, config.GetDefaultDrillCurrent()));
    obj.SetDrillRank(GET_JSON_DATA_OR_DEFAULT(DrillRank, Int, config.GetDefaultDrillRank()));
    obj.SetShootCurrent(GET_JSON_DATA_OR_DEFAULT(ShootCurrent, Int, config.GetDefaultShootCurrent()));
    obj.SetShootRank(GET_JSON_DATA_OR_DEFAULT(ShootRank, Int, config.GetDefaultShootRank()));
    obj.SetImpaleCurrent(GET_JSON_DATA_OR_DEFAULT(ImpaleCurrent, Int, config.GetDefaultImpaleCurrent()));
    obj.SetImpaleRank(GET_JSON_DATA_OR_DEFAULT(ImpaleRank, Int, config.GetDefaultImpaleRank()));
    obj.SetStealthStrikeCurrent(GET_JSON_DATA_OR_DEFAULT(StealthStrikeCurrent, Int, config.GetDefaultStealthStrikeCurrent()));
    obj.SetStealthStrikeRank(GET_JSON_DATA_OR_DEFAULT(StealthStrikeRank, Int, config.GetDefaultStealthStrikeRank()));
    obj.SetCriticalShotCurrent(GET_JSON_DATA_OR_DEFAULT(CriticalShotCurrent, Int, config.GetDefaultCriticalShotCurrent()));
    obj.SetCriticalShotRank(GET_JSON_DATA_OR_DEFAULT(CriticalShotRank, Int, config.GetDefaultCriticalShotRank()));
    obj.SetDodgeCurrent(GET_JSON_DATA_OR_DEFAULT(DodgeCurrent, Int, config.GetDefaultDodgeCurrent()));
    obj.SetDodgeRank(GET_JSON_DATA_OR_DEFAULT(DodgeRank, Int, config.GetDefaultDodgeRank()));
    obj.SetCounterCurrent(GET_JSON_DATA_OR_DEFAULT(CounterCurrent, Int, config.GetDefaultCounterCurrent()));
    obj.SetCounterRank(GET_JSON_DATA_OR_DEFAULT(CounterRank, Int, config.GetDefaultCounterRank()));

    // Alchemy Skills
    obj.SetHealerCurrent(GET_JSON_DATA_OR_DEFAULT(HealerCurrent, Int, config.GetDefaultHealerCurrent()));
    obj.SetHealerRank(GET_JSON_DATA_OR_DEFAULT(HealerRank, Int, config.GetDefaultHealerRank()));
    obj.SetAlchemistCurrent(GET_JSON_DATA_OR_DEFAULT(AlchemistCurrent, Int, config.GetDefaultAlchemistCurrent()));
    obj.SetAlchemistRank(GET_JSON_DATA_OR_DEFAULT(AlchemistRank, Int, config.GetDefaultAlchemistRank()));
    obj.SetEnergistCurrent(GET_JSON_DATA_OR_DEFAULT(EnergistCurrent, Int, config.GetDefaultEnergistCurrent()));
    obj.SetEnergistRank(GET_JSON_DATA_OR_DEFAULT(EnergistRank, Int, config.GetDefaultEnergistRank()));
    obj.SetChemistCurrent(GET_JSON_DATA_OR_DEFAULT(ChemistCurrent, Int, config.GetDefaultChemistCurrent()));
    obj.SetChemistRank(GET_JSON_DATA_OR_DEFAULT(ChemistRank, Int, config.GetDefaultChemistRank()));

    // Crafting Skills
    obj.SetHammersmithCurrent(GET_JSON_DATA_OR_DEFAULT(HammersmithCurrent, Int, config.GetDefaultHammersmithCurrent()));
    obj.SetHammersmithRank(GET_JSON_DATA_OR_DEFAULT(HammersmithRank, Int, config.GetDefaultHammersmithRank()));
    obj.SetSpellsmithCurrent(GET_JSON_DATA_OR_DEFAULT(SpellsmithCurrent, Int, config.GetDefaultSpellsmithCurrent()));
    obj.SetSpellsmithRank(GET_JSON_DATA_OR_DEFAULT(SpellsmithRank, Int, config.GetDefaultSpellsmithRank()));
    obj.SetBowsmithCurrent(GET_JSON_DATA_OR_DEFAULT(BowsmithCurrent, Int, config.GetDefaultBowsmithCurrent()));
    obj.SetBowsmithRank(GET_JSON_DATA_OR_DEFAULT(BowsmithRank, Int, config.GetDefaultBowsmithRank()));
    obj.SetSwordsmithCurrent(GET_JSON_DATA_OR_DEFAULT(SwordsmithCurrent, Int, config.GetDefaultSwordsmithCurrent()));
    obj.SetSwordsmithRank(GET_JSON_DATA_OR_DEFAULT(SwordsmithRank, Int, config.GetDefaultSwordsmithRank()));
    obj.SetWeaverCurrent(GET_JSON_DATA_OR_DEFAULT(WeaverCurrent, Int, config.GetDefaultWeaverCurrent()));
    obj.SetWeaverRank(GET_JSON_DATA_OR_DEFAULT(WeaverRank, Int, config.GetDefaultWeaverRank()));
    obj.SetTannerCurrent(GET_JSON_DATA_OR_DEFAULT(TannerCurrent, Int, config.GetDefaultTannerCurrent()));
    obj.SetTannerRank(GET_JSON_DATA_OR_DEFAULT(TannerRank, Int, config.GetDefaultTannerRank()));
    obj.SetScalesmithCurrent(GET_JSON_DATA_OR_DEFAULT(ScalesmithCurrent, Int, config.GetDefaultScalesmithCurrent()));
    obj.SetScalesmithRank(GET_JSON_DATA_OR_DEFAULT(ScalesmithRank, Int, config.GetDefaultScalesmithRank()));
    obj.SetPlatesmithCurrent(GET_JSON_DATA_OR_DEFAULT(PlatesmithCurrent, Int, config.GetDefaultPlatesmithCurrent()));
    obj.SetPlatesmithRank(GET_JSON_DATA_OR_DEFAULT(PlatesmithRank, Int, config.GetDefaultPlatesmithRank()));
    obj.SetGoldsmithCurrent(GET_JSON_DATA_OR_DEFAULT(GoldsmithCurrent, Int, config.GetDefaultGoldsmithCurrent()));
    obj.SetGoldsmithRank(GET_JSON_DATA_OR_DEFAULT(GoldsmithRank, Int, config.GetDefaultGoldsmithRank()));
    obj.SetShieldsmithCurrent(GET_JSON_DATA_OR_DEFAULT(ShieldsmithCurrent, Int, config.GetDefaultShieldsmithCurrent()));
    obj.SetShieldsmithRank(GET_JSON_DATA_OR_DEFAULT(ShieldsmithRank, Int, config.GetDefaultShieldsmithRank()));

    // Breakdown Skills
    obj.SetHammerbaneCurrent(GET_JSON_DATA_OR_DEFAULT(HammerbaneCurrent, Int, config.GetDefaultHammerbaneCurrent()));
    obj.SetHammerbaneRank(GET_JSON_DATA_OR_DEFAULT(HammerbaneRank, Int, config.GetDefaultHammerbaneRank()));
    obj.SetSpellbaneCurrent(GET_JSON_DATA_OR_DEFAULT(SpellbaneCurrent, Int, config.GetDefaultSpellbaneCurrent()));
    obj.SetSpellbaneRank(GET_JSON_DATA_OR_DEFAULT(SpellbaneRank, Int, config.GetDefaultSpellbaneRank()));
    obj.SetBowbaneCurrent(GET_JSON_DATA_OR_DEFAULT(BowbaneCurrent, Int, config.GetDefaultBowbaneCurrent()));
    obj.SetBowbaneRank(GET_JSON_DATA_OR_DEFAULT(BowbaneRank, Int, config.GetDefaultBowbaneRank()));
    obj.SetSwordbaneCurrent(GET_JSON_DATA_OR_DEFAULT(SwordbaneCurrent, Int, config.GetDefaultSwordbaneCurrent()));
    obj.SetSwordbaneRank(GET_JSON_DATA_OR_DEFAULT(SwordbaneRank, Int, config.GetDefaultSwordbaneRank()));
    obj.SetThreadbareCurrent(GET_JSON_DATA_OR_DEFAULT(ThreadbareCurrent, Int, config.GetDefaultThreadbareCurrent()));
    obj.SetThreadbareRank(GET_JSON_DATA_OR_DEFAULT(ThreadbareRank, Int, config.GetDefaultThreadbareRank()));
    obj.SetStudRemoverCurrent(GET_JSON_DATA_OR_DEFAULT(StudRemoverCurrent, Int, config.GetDefaultStudRemoverCurrent()));
    obj.SetStudRemoverRank(GET_JSON_DATA_OR_DEFAULT(StudRemoverRank, Int, config.GetDefaultStudRemoverRank()));
    obj.SetScalebaneCurrent(GET_JSON_DATA_OR_DEFAULT(ScalebaneCurrent, Int, config.GetDefaultScalebaneCurrent()));
    obj.SetScalebaneRank(GET_JSON_DATA_OR_DEFAULT(ScalebaneRank, Int, config.GetDefaultScalebaneRank()));
    obj.SetPlatebaneCurrent(GET_JSON_DATA_OR_DEFAULT(PlatebaneCurrent, Int, config.GetDefaultPlatebaneCurrent()));
    obj.SetPlatebaneRank(GET_JSON_DATA_OR_DEFAULT(PlatebaneRank, Int, config.GetDefaultPlatebaneRank()));
    obj.SetGoldbaneCurrent(GET_JSON_DATA_OR_DEFAULT(GoldbaneCurrent, Int, config.GetDefaultGoldbaneCurrent()));
    obj.SetGoldbaneRank(GET_JSON_DATA_OR_DEFAULT(GoldbaneRank, Int, config.GetDefaultGoldbaneRank()));
    obj.SetShieldbaneCurrent(GET_JSON_DATA_OR_DEFAULT(ShieldbaneCurrent, Int, config.GetDefaultShieldbaneCurrent()));
    obj.SetShieldbaneRank(GET_JSON_DATA_OR_DEFAULT(ShieldbaneRank, Int, config.GetDefaultShieldbaneRank()));

    // Affinity Skills
    obj.SetHolyCurrent(GET_JSON_DATA_OR_DEFAULT(HolyCurrent, Int, config.GetDefaultHolyCurrent()));
    obj.SetHolyRank(GET_JSON_DATA_OR_DEFAULT(HolyRank, Int, config.GetDefaultHolyRank()));
    obj.SetFireCurrent(GET_JSON_DATA_OR_DEFAULT(FireCurrent, Int, config.GetDefaultFireCurrent()));
    obj.SetFireRank(GET_JSON_DATA_OR_DEFAULT(FireRank, Int, config.GetDefaultFireRank()));
    obj.SetIceCurrent(GET_JSON_DATA_OR_DEFAULT(IceCurrent, Int, config.GetDefaultIceCurrent()));
    obj.SetIceRank(GET_JSON_DATA_OR_DEFAULT(IceRank, Int, config.GetDefaultIceRank()));
    obj.SetShockCurrent(GET_JSON_DATA_OR_DEFAULT(ShockCurrent, Int, config.GetDefaultShockCurrent()));
    obj.SetShockRank(GET_JSON_DATA_OR_DEFAULT(ShockRank, Int, config.GetDefaultShockRank()));
    obj.SetDarkCurrent(GET_JSON_DATA_OR_DEFAULT(DarkCurrent, Int, config.GetDefaultDarkCurrent()));
    obj.SetDarkRank(GET_JSON_DATA_OR_DEFAULT(DarkRank, Int, config.GetDefaultDarkRank()));
    obj.SetLightCurrent(GET_JSON_DATA_OR_DEFAULT(LightCurrent, Int, config.GetDefaultLightCurrent()));
    obj.SetLightRank(GET_JSON_DATA_OR_DEFAULT(LightRank, Int, config.GetDefaultLightRank()));
    obj.SetForceCurrent(GET_JSON_DATA_OR_DEFAULT(ForceCurrent, Int, config.GetDefaultForceCurrent()));
    obj.SetForceRank(GET_JSON_DATA_OR_DEFAULT(ForceRank, Int, config.GetDefaultForceRank()));
    obj.SetMindCurrent(GET_JSON_DATA_OR_DEFAULT(MindCurrent, Int, config.GetDefaultMindCurrent()));
    obj.SetMindRank(GET_JSON_DATA_OR_DEFAULT(MindRank, Int, config.GetDefaultMindRank()));
    obj.SetEarthCurrent(GET_JSON_DATA_OR_DEFAULT(EarthCurrent, Int, config.GetDefaultEarthCurrent()));
    obj.SetEarthRank(GET_JSON_DATA_OR_DEFAULT(EarthRank, Int, config.GetDefaultEarthRank()));
    obj.SetBloodCurrent(GET_JSON_DATA_OR_DEFAULT(BloodCurrent, Int, config.GetDefaultBloodCurrent()));
    obj.SetBloodRank(GET_JSON_DATA_OR_DEFAULT(BloodRank, Int, config.GetDefaultBloodRank()));
    obj.SetFleshCurrent(GET_JSON_DATA_OR_DEFAULT(FleshCurrent, Int, config.GetDefaultFleshCurrent()));
    obj.SetFleshRank(GET_JSON_DATA_OR_DEFAULT(FleshRank, Int, config.GetDefaultFleshRank()));
    obj.SetWindCurrent(GET_JSON_DATA_OR_DEFAULT(WindCurrent, Int, config.GetDefaultWindCurrent()));
    obj.SetWindRank(GET_JSON_DATA_OR_DEFAULT(WindRank, Int, config.GetDefaultWindRank()));

    // Segmented progress data
    obj.SetProgressDataBase(GET_JSON_SHAREDPTR_DATA_OR_DEFAULT(ProgressDataBase, CharacterProgressData));
    obj.SetProgressDataPassives(GET_JSON_SHAREDPTR_DATA_OR_DEFAULT(ProgressDataPassives, CharacterProgressData));

    // Segmented battle data
    obj.SetBattleDataBase(GET_JSON_SHAREDPTR_DATA_OR_DEFAULT(BattleDataBase, CharacterBattleData));
    obj.SetBattleDataPassives(GET_JSON_SHAREDPTR_DATA_OR_DEFAULT(BattleDataPassives, CharacterBattleData));

    // List of passive/active/actionable data
    obj.SetPassiveSkillDataList(GET_JSON_DATA_OR_DEFAULT(PassiveSkillDataList, TreeIndexList, TreeIndexList()));
    obj.SetActiveSkillDataList(GET_JSON_DATA_OR_DEFAULT(ActiveSkillDataList, TreeIndexList, TreeIndexList()));
    obj.SetActionableSkillDataList(GET_JSON_DATA_OR_DEFAULT(ActionableSkillDataList, TreeIndexList, TreeIndexList()));
    obj.SetPassiveItemDataList(GET_JSON_DATA_OR_DEFAULT(PassiveItemDataList, TreeIndexList, TreeIndexList()));
    obj.SetActiveItemDataList(GET_JSON_DATA_OR_DEFAULT(ActiveItemDataList, TreeIndexList, TreeIndexList()));
    obj.SetActionableItemDataList(GET_JSON_DATA_OR_DEFAULT(ActionableItemDataList, TreeIndexList, TreeIndexList()));

    // List of character actions
    obj.SetAvailableActions(GET_JSON_DATA_OR_DEFAULT(AvailableActions, CharacterActionSharedPtrList, CharacterActionSharedPtrList()));

    // Character ID
    obj.SetCharacterID(GET_JSON_DATA_OR_DEFAULT(CharacterID, IndexedString, IndexedString("")));

    // Character target type
    obj.SetCharacterTargetType(GET_JSON_DATA_OR_DEFAULT(CharacterTargetType, IndexedString, IndexedString("None")));
}

MAKE_JSON_GENERIC_TYPE_CONVERTERS_IMPL(Character, Character);

Bool operator==(const Character& a, const Character& b)
{
    return (a.GetCharacterID() == b.GetCharacterID());
}

};
