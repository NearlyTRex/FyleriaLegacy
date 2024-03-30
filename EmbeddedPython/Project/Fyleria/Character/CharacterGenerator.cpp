// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

// Internal includes
#include "Character/CharacterGenerator.h"
#include "Character/CharacterTypes.h"
#include "Utility/FantasyName.h"
#include "Utility/Templates.h"

namespace Gecko
{

CharacterGenerator::CharacterGenerator()
{
}

CharacterGenerator::CharacterGenerator(const Json& jsonData)
{
    from_json(jsonData, *this);
}

CharacterGenerator::CharacterGenerator(const String& jsonString)
{
    from_json(JsonParse(jsonString), *this);
}

CharacterGenerator::~CharacterGenerator()
{
}

CharacterBasicData CharacterGenerator::GenerateBasicData(const String& sCharacterID) const
{
    // Create basic data
    CharacterBasicData basicData;
    basicData.Clear();

    // Character ID
    basicData.SetCharacterID(sCharacterID);

    // Basic character data
    basicData.SetFirstName(GenerateFirstName());
    basicData.SetLastName(GenerateLastName());
    basicData.SetAge(GenerateAge());
    basicData.SetGender(GenerateGender());
    basicData.SetHair(GenerateHair());
    basicData.SetEyes(GenerateEyes());
    basicData.SetHandedness(GenerateHandedness());
    basicData.SetBaseRace(GenerateBaseRace());
    basicData.SetTransformedRace(GenerateTransformedRace());
    basicData.SetPowerSet(GeneratePowerSet());
    basicData.SetWeaponSet(GenerateWeaponSet());
    return basicData;
}

CharacterProgressData CharacterGenerator::GenerateProgressData() const
{
    // Create progress data
    CharacterProgressData progressData;
    progressData.Clear();

    // Meters
    progressData.SetHealthPointsMax(GetRandomIntValue<Int>(GetHPStart(), GetHPEnd()));
    progressData.SetMagicPointsMax(GetRandomIntValue<Int>(GetMPStart(), GetMPEnd()));
    progressData.SetEnergyPointsMax(GetRandomIntValue<Int>(GetEPStart(), GetEPEnd()));
    progressData.SetHealthPointsCurrent(progressData.GetHealthPointsMax());
    progressData.SetMagicPointsCurrent(progressData.GetMagicPointsMax());
    progressData.SetEnergyPointsCurrent(progressData.GetEnergyPointsMax());
    progressData.SetHealthRegen(GetRandomIntValue<Int>(GetHPRegenStart(), GetHPRegenEnd()));
    progressData.SetMagicRegen(GetRandomIntValue<Int>(GetMPRegenStart(), GetMPRegenEnd()));
    progressData.SetEnergyRegen(GetRandomIntValue<Int>(GetEPRegenStart(), GetEPRegenEnd()));
    progressData.SetSpeed(GetRandomIntValue<Int>(GetSpeedStart(), GetSpeedEnd()));

    // Attack and Defense Scoring
    progressData.SetBluntAttack(GetRandomIntValue<Int>(GetBluntATKStart(), GetBluntATKEnd()));
    progressData.SetBluntDefense(GetRandomIntValue<Int>(GetBluntDEFStart(), GetBluntDEFEnd()));
    progressData.SetPierceAttack(GetRandomIntValue<Int>(GetPierceATKStart(), GetPierceATKEnd()));
    progressData.SetPierceDefense(GetRandomIntValue<Int>(GetPierceDEFStart(), GetPierceDEFEnd()));
    progressData.SetSlashAttack(GetRandomIntValue<Int>(GetSlashATKStart(), GetSlashATKEnd()));
    progressData.SetSlashDefense(GetRandomIntValue<Int>(GetSlashDEFStart(), GetSlashDEFEnd()));
    progressData.SetEnergyAttack(GetRandomIntValue<Int>(GetEnergyATKStart(), GetEnergyATKEnd()));
    progressData.SetEnergyDefense(GetRandomIntValue<Int>(GetEnergyDEFStart(), GetEnergyDEFEnd()));
    progressData.SetMagicAttack(GetRandomIntValue<Int>(GetMagicATKStart(), GetMagicATKEnd()));
    progressData.SetMagicDefense(GetRandomIntValue<Int>(GetMagicDEFStart(), GetMagicDEFEnd()));
    return progressData;
}

CharacterSkillData CharacterGenerator::GenerateSkillData() const
{
    // Create skill data
    CharacterSkillData skillData;
    skillData.Clear();

    // Combat Skills
    skillData.SetBarbarian(GetRandomIntValue<Short>(GetBarbarianStart(), GetBarbarianEnd()));
    skillData.SetMage(GetRandomIntValue<Short>(GetMageStart(), GetMageEnd()));
    skillData.SetRogue(GetRandomIntValue<Short>(GetRogueStart(), GetRogueEnd()));
    skillData.SetBlademaster(GetRandomIntValue<Short>(GetBlademasterStart(), GetBlademasterEnd()));
    skillData.SetAvatar(GetRandomIntValue<Short>(GetAvatarStart(), GetAvatarEnd()));
    skillData.SetAmbidextrous(GetRandomIntValue<Short>(GetAmbidextrousStart(), GetAmbidextrousEnd()));
    skillData.SetFocused(GetRandomIntValue<Short>(GetFocusedStart(), GetFocusedEnd()));
    skillData.SetStalwart(GetRandomIntValue<Short>(GetStalwartStart(), GetStalwartEnd()));

    // Weapon Skills
    skillData.SetSlash(GetRandomIntValue<Short>(GetSlashStart(), GetSlashEnd()));
    skillData.SetSever(GetRandomIntValue<Short>(GetSeverStart(), GetSeverEnd()));
    skillData.SetSlice(GetRandomIntValue<Short>(GetSliceStart(), GetSliceEnd()));
    skillData.SetSlit(GetRandomIntValue<Short>(GetSlitStart(), GetSlitEnd()));
    skillData.SetCleave(GetRandomIntValue<Short>(GetCleaveStart(), GetCleaveEnd()));
    skillData.SetDecapitate(GetRandomIntValue<Short>(GetDecapitateStart(), GetDecapitateEnd()));
    skillData.SetParry(GetRandomIntValue<Short>(GetParryStart(), GetParryEnd()));
    skillData.SetRiposte(GetRandomIntValue<Short>(GetRiposteStart(), GetRiposteEnd()));
    skillData.SetBash(GetRandomIntValue<Short>(GetBashStart(), GetBashEnd()));
    skillData.SetSmash(GetRandomIntValue<Short>(GetSmashStart(), GetSmashEnd()));
    skillData.SetCrush(GetRandomIntValue<Short>(GetCrushStart(), GetCrushEnd()));
    skillData.SetImpact(GetRandomIntValue<Short>(GetImpactStart(), GetImpactEnd()));
    skillData.SetBreak(GetRandomIntValue<Short>(GetBreakStart(), GetBreakEnd()));
    skillData.SetCrack(GetRandomIntValue<Short>(GetCrackStart(), GetCrackEnd()));
    skillData.SetBlock(GetRandomIntValue<Short>(GetBlockStart(), GetBlockEnd()));
    skillData.SetRush(GetRandomIntValue<Short>(GetRushStart(), GetRushEnd()));
    skillData.SetPierce(GetRandomIntValue<Short>(GetPierceStart(), GetPierceEnd()));
    skillData.SetDrill(GetRandomIntValue<Short>(GetDrillStart(), GetDrillEnd()));
    skillData.SetShoot(GetRandomIntValue<Short>(GetShootStart(), GetShootEnd()));
    skillData.SetImpale(GetRandomIntValue<Short>(GetImpaleStart(), GetImpaleEnd()));
    skillData.SetStealthStrike(GetRandomIntValue<Short>(GetStealthStrikeStart(), GetStealthStrikeEnd()));
    skillData.SetCriticalShot(GetRandomIntValue<Short>(GetCriticalShotStart(), GetCriticalShotEnd()));
    skillData.SetDodge(GetRandomIntValue<Short>(GetDodgeStart(), GetDodgeEnd()));
    skillData.SetCounter(GetRandomIntValue<Short>(GetCounterStart(), GetCounterEnd()));

    // Alchemy Skills
    skillData.SetHealer(GetRandomIntValue<Short>(GetHealerStart(), GetHealerEnd()));
    skillData.SetAlchemist(GetRandomIntValue<Short>(GetAlchemistStart(), GetAlchemistEnd()));
    skillData.SetEnergist(GetRandomIntValue<Short>(GetEnergistStart(), GetEnergistEnd()));
    skillData.SetChemist(GetRandomIntValue<Short>(GetChemistStart(), GetChemistEnd()));

    // Crafting Skills
    skillData.SetHammersmith(GetRandomIntValue<Short>(GetHammersmithStart(), GetHammersmithEnd()));
    skillData.SetSpellsmith(GetRandomIntValue<Short>(GetSpellsmithStart(), GetSpellsmithEnd()));
    skillData.SetBowsmith(GetRandomIntValue<Short>(GetBowsmithStart(), GetBowsmithEnd()));
    skillData.SetSwordsmith(GetRandomIntValue<Short>(GetSwordsmithStart(), GetSwordsmithEnd()));
    skillData.SetWeaver(GetRandomIntValue<Short>(GetWeaverStart(), GetWeaverEnd()));
    skillData.SetTanner(GetRandomIntValue<Short>(GetTannerStart(), GetTannerEnd()));
    skillData.SetScalesmith(GetRandomIntValue<Short>(GetScalesmithStart(), GetScalesmithEnd()));
    skillData.SetPlatesmith(GetRandomIntValue<Short>(GetPlatesmithStart(), GetPlatesmithEnd()));
    skillData.SetGoldsmith(GetRandomIntValue<Short>(GetGoldsmithStart(), GetGoldsmithEnd()));
    skillData.SetShieldsmith(GetRandomIntValue<Short>(GetShieldsmithStart(), GetShieldsmithEnd()));

    // Breakdown Skills
    skillData.SetHammerbane(GetRandomIntValue<Short>(GetHammerbaneStart(), GetHammerbaneEnd()));
    skillData.SetSpellbane(GetRandomIntValue<Short>(GetSpellbaneStart(), GetSpellbaneEnd()));
    skillData.SetBowbane(GetRandomIntValue<Short>(GetBowbaneStart(), GetBowbaneEnd()));
    skillData.SetSwordbane(GetRandomIntValue<Short>(GetSwordbaneStart(), GetSwordbaneEnd()));
    skillData.SetThreadbare(GetRandomIntValue<Short>(GetThreadbareStart(), GetThreadbareEnd()));
    skillData.SetStudRemover(GetRandomIntValue<Short>(GetStudRemoverStart(), GetStudRemoverEnd()));
    skillData.SetScalebane(GetRandomIntValue<Short>(GetScalebaneStart(), GetScalebaneEnd()));
    skillData.SetPlatebane(GetRandomIntValue<Short>(GetPlatebaneStart(), GetPlatebaneEnd()));
    skillData.SetGoldbane(GetRandomIntValue<Short>(GetGoldbaneStart(), GetGoldbaneEnd()));
    skillData.SetShieldbane(GetRandomIntValue<Short>(GetShieldbaneStart(), GetShieldbaneEnd()));

    // Affinity Skills
    skillData.SetHoly(GetRandomIntValue<Short>(GetHolyStart(), GetHolyEnd()));
    skillData.SetFire(GetRandomIntValue<Short>(GetFireStart(), GetFireEnd()));
    skillData.SetIce(GetRandomIntValue<Short>(GetIceStart(), GetIceEnd()));
    skillData.SetShock(GetRandomIntValue<Short>(GetShockStart(), GetShockEnd()));
    skillData.SetDark(GetRandomIntValue<Short>(GetDarkStart(), GetDarkEnd()));
    skillData.SetLight(GetRandomIntValue<Short>(GetLightStart(), GetLightEnd()));
    skillData.SetForce(GetRandomIntValue<Short>(GetForceStart(), GetForceEnd()));
    skillData.SetMind(GetRandomIntValue<Short>(GetMindStart(), GetMindEnd()));
    skillData.SetEarth(GetRandomIntValue<Short>(GetEarthStart(), GetEarthEnd()));
    skillData.SetBlood(GetRandomIntValue<Short>(GetBloodStart(), GetBloodEnd()));
    skillData.SetFlesh(GetRandomIntValue<Short>(GetFleshStart(), GetFleshEnd()));
    skillData.SetWind(GetRandomIntValue<Short>(GetWindStart(), GetWindEnd()));
    return skillData;
}

String CharacterGenerator::GenerateFirstName() const
{
    return String(GetUseRandomName() ? GenerateRandomFantasyName(GetCapitalizationToken() + GetFirstNamePattern()) : GetFirstName());
}

String CharacterGenerator::GenerateLastName() const
{
    return String(GetUseRandomName() ? GenerateRandomFantasyName(GetCapitalizationToken() + GetLastNamePattern()) : GetLastName());
}

Int CharacterGenerator::GenerateAge() const
{
    return (GetUseRandomAge() ? GetRandomIntValue<Int>(GetAgeStart(), GetAgeEnd()) : GetAge());
}

String CharacterGenerator::GenerateGender() const
{
    return String(GetUseRandomGender() ? GetRandomEnumValue<CharacterGenderType>() : GetGender());
}

String CharacterGenerator::GenerateHair() const
{
    return String(GetUseRandomHair() ? GetRandomEnumValue<CharacterHairType>() : GetHair());
}

String CharacterGenerator::GenerateEyes() const
{
    return String(GetUseRandomEyes() ? GetRandomEnumValue<CharacterEyeType>() : GetEyes());
}

String CharacterGenerator::GenerateHandedness() const
{
    return String(GetUseRandomHandedness() ? GetRandomEnumValue<CharacterHandednessType>() : GetHandedness());
}

String CharacterGenerator::GenerateBaseRace() const
{
    return String(GetUseRandomBaseRace() ? GetRandomEnumValue<CharacterBaseRaceType>() : GetBaseRace());
}

String CharacterGenerator::GenerateTransformedRace() const
{
    return String(GetUseRandomTransformedRace() ? GetRandomEnumValue<CharacterTransformedRaceType>() : GetTransformedRace());
}

String CharacterGenerator::GeneratePowerSet() const
{
    return String(GetUseRandomPowerSet() ? GetRandomEnumValue<CharacterPowerSetType>() : GetPowerSet());
}

String CharacterGenerator::GenerateWeaponSet() const
{
    return String(GetUseRandomWeaponSet() ? GetRandomEnumValue<CharacterWeaponSetType>() : GetWeaponSet());
}

void CharacterGenerator::RandomizeBasics()
{
    // Basics
    String sRandomNamePattern = GetRandomNamePattern();
    SetFirstNamePattern(sRandomNamePattern);
    SetLastNamePattern(sRandomNamePattern);
    SetAgeStart(GetRandomIntValue<Int>(1, DEFAULT_MAX_AGE));
    SetAgeEnd(GetRandomIntValue<Int>(GetAgeStart() + 1, DEFAULT_MAX_AGE));
    SetUseRandomName(true);
    SetUseRandomAge(true);
    SetUseRandomGender(true);
    SetUseRandomHair(true);
    SetUseRandomEyes(true);
    SetUseRandomHandedness(true);
    SetUseRandomBaseRace(true);
    SetUseRandomTransformedRace(true);
    SetUseRandomPowerSet(true);
    SetUseRandomWeaponSet(true);
}

void CharacterGenerator::RandomizeMeters()
{
    // Meters
    SetHPStart(GetRandomIntValue<Int>(1, DEFAULT_MAX_METER));
    SetHPEnd(GetRandomIntValue<Int>(GetHPStart() + 1, DEFAULT_MAX_METER));
    SetMPStart(GetRandomIntValue<Int>(1, DEFAULT_MAX_METER));
    SetMPEnd(GetRandomIntValue<Int>(GetMPStart() + 1, DEFAULT_MAX_METER));
    SetEPStart(GetRandomIntValue<Int>(1, DEFAULT_MAX_METER));
    SetEPEnd(GetRandomIntValue<Int>(GetEPStart() + 1, DEFAULT_MAX_METER));
    SetHPRegenStart(GetRandomIntValue<Int>(1, DEFAULT_MAX_METER));
    SetHPRegenEnd(GetRandomIntValue<Int>(GetHPRegenStart() + 1, DEFAULT_MAX_METER));
    SetMPRegenStart(GetRandomIntValue<Int>(1, DEFAULT_MAX_METER));
    SetMPRegenEnd(GetRandomIntValue<Int>(GetMPRegenStart() + 1, DEFAULT_MAX_METER));
    SetEPRegenStart(GetRandomIntValue<Int>(1, DEFAULT_MAX_METER));
    SetEPRegenEnd(GetRandomIntValue<Int>(GetEPRegenStart() + 1, DEFAULT_MAX_METER));
    SetSpeedStart(GetRandomIntValue<Int>(1, DEFAULT_MAX_METER));
    SetSpeedEnd(GetRandomIntValue<Int>(GetSpeedStart() + 1, DEFAULT_MAX_METER));
}

void CharacterGenerator::RandomizeScoring()
{
    // Attack and Defense Scoring
    SetBluntATKStart(GetRandomIntValue<Int>(1, DEFAULT_MAX_SCORING));
    SetBluntATKEnd(GetRandomIntValue<Int>(GetBluntATKStart() + 1, DEFAULT_MAX_SCORING));
    SetBluntDEFStart(GetRandomIntValue<Int>(1, DEFAULT_MAX_SCORING));
    SetBluntDEFEnd(GetRandomIntValue<Int>(GetBluntDEFStart() + 1, DEFAULT_MAX_SCORING));
    SetPierceATKStart(GetRandomIntValue<Int>(1, DEFAULT_MAX_SCORING));
    SetPierceATKEnd(GetRandomIntValue<Int>(GetPierceATKStart() + 1, DEFAULT_MAX_SCORING));
    SetPierceDEFStart(GetRandomIntValue<Int>(1, DEFAULT_MAX_SCORING));
    SetPierceDEFEnd(GetRandomIntValue<Int>(GetPierceDEFStart() + 1, DEFAULT_MAX_SCORING));
    SetSlashATKStart(GetRandomIntValue<Int>(1, DEFAULT_MAX_SCORING));
    SetSlashATKEnd(GetRandomIntValue<Int>(GetSlashATKStart() + 1, DEFAULT_MAX_SCORING));
    SetSlashDEFStart(GetRandomIntValue<Int>(1, DEFAULT_MAX_SCORING));
    SetSlashDEFEnd(GetRandomIntValue<Int>(GetSlashDEFStart() + 1, DEFAULT_MAX_SCORING));
    SetEnergyATKStart(GetRandomIntValue<Int>(1, DEFAULT_MAX_SCORING));
    SetEnergyATKEnd(GetRandomIntValue<Int>(GetEnergyATKStart() + 1, DEFAULT_MAX_SCORING));
    SetEnergyDEFStart(GetRandomIntValue<Int>(1, DEFAULT_MAX_SCORING));
    SetEnergyDEFEnd(GetRandomIntValue<Int>(GetEnergyDEFStart() + 1, DEFAULT_MAX_SCORING));
    SetMagicATKStart(GetRandomIntValue<Int>(1, DEFAULT_MAX_SCORING));
    SetMagicATKEnd(GetRandomIntValue<Int>(GetMagicATKStart() + 1, DEFAULT_MAX_SCORING));
    SetMagicDEFStart(GetRandomIntValue<Int>(1, DEFAULT_MAX_SCORING));
    SetMagicDEFEnd(GetRandomIntValue<Int>(GetMagicDEFStart() + 1, DEFAULT_MAX_SCORING));
}

void CharacterGenerator::RandomizeSkills()
{
    // Combat Skills
    SetBarbarianStart(GetRandomIntValue<Short>(1, DEFAULT_MAX_SKILL));
    SetBarbarianEnd(GetRandomIntValue<Short>(GetBarbarianStart() + 1, DEFAULT_MAX_SKILL));
    SetMageStart(GetRandomIntValue<Short>(1, DEFAULT_MAX_SKILL));
    SetMageEnd(GetRandomIntValue<Short>(GetMageStart() + 1, DEFAULT_MAX_SKILL));
    SetRogueStart(GetRandomIntValue<Short>(1, DEFAULT_MAX_SKILL));
    SetRogueEnd(GetRandomIntValue<Short>(GetRogueStart() + 1, DEFAULT_MAX_SKILL));
    SetBlademasterStart(GetRandomIntValue<Short>(1, DEFAULT_MAX_SKILL));
    SetBlademasterEnd(GetRandomIntValue<Short>(GetBlademasterStart() + 1, DEFAULT_MAX_SKILL));
    SetAvatarStart(GetRandomIntValue<Short>(1, DEFAULT_MAX_SKILL));
    SetAvatarEnd(GetRandomIntValue<Short>(GetAvatarStart() + 1, DEFAULT_MAX_SKILL));
    SetAmbidextrousStart(GetRandomIntValue<Short>(1, DEFAULT_MAX_SKILL));
    SetAmbidextrousEnd(GetRandomIntValue<Short>(GetAmbidextrousStart() + 1, DEFAULT_MAX_SKILL));
    SetFocusedStart(GetRandomIntValue<Short>(1, DEFAULT_MAX_SKILL));
    SetFocusedEnd(GetRandomIntValue<Short>(GetFocusedStart() + 1, DEFAULT_MAX_SKILL));
    SetStalwartStart(GetRandomIntValue<Short>(1, DEFAULT_MAX_SKILL));
    SetStalwartEnd(GetRandomIntValue<Short>(GetStalwartStart() + 1, DEFAULT_MAX_SKILL));

    // Weapon Skills
    SetSlashStart(GetRandomIntValue<Short>(1, DEFAULT_MAX_SKILL));
    SetSlashEnd(GetRandomIntValue<Short>(GetSlashStart() + 1, DEFAULT_MAX_SKILL));
    SetSeverStart(GetRandomIntValue<Short>(1, DEFAULT_MAX_SKILL));
    SetSeverEnd(GetRandomIntValue<Short>(GetSeverStart() + 1, DEFAULT_MAX_SKILL));
    SetSliceStart(GetRandomIntValue<Short>(1, DEFAULT_MAX_SKILL));
    SetSliceEnd(GetRandomIntValue<Short>(GetSliceStart() + 1, DEFAULT_MAX_SKILL));
    SetSlitStart(GetRandomIntValue<Short>(1, DEFAULT_MAX_SKILL));
    SetSlitEnd(GetRandomIntValue<Short>(GetSlitStart() + 1, DEFAULT_MAX_SKILL));
    SetCleaveStart(GetRandomIntValue<Short>(1, DEFAULT_MAX_SKILL));
    SetCleaveEnd(GetRandomIntValue<Short>(GetCleaveStart() + 1, DEFAULT_MAX_SKILL));
    SetDecapitateStart(GetRandomIntValue<Short>(1, DEFAULT_MAX_SKILL));
    SetDecapitateEnd(GetRandomIntValue<Short>(GetDecapitateStart() + 1, DEFAULT_MAX_SKILL));
    SetParryStart(GetRandomIntValue<Short>(1, DEFAULT_MAX_SKILL));
    SetParryEnd(GetRandomIntValue<Short>(GetParryStart() + 1, DEFAULT_MAX_SKILL));
    SetRiposteStart(GetRandomIntValue<Short>(1, DEFAULT_MAX_SKILL));
    SetRiposteEnd(GetRandomIntValue<Short>(GetRiposteStart() + 1, DEFAULT_MAX_SKILL));
    SetBashStart(GetRandomIntValue<Short>(1, DEFAULT_MAX_SKILL));
    SetBashEnd(GetRandomIntValue<Short>(GetBashStart() + 1, DEFAULT_MAX_SKILL));
    SetSmashStart(GetRandomIntValue<Short>(1, DEFAULT_MAX_SKILL));
    SetSmashEnd(GetRandomIntValue<Short>(GetSmashStart() + 1, DEFAULT_MAX_SKILL));
    SetCrushStart(GetRandomIntValue<Short>(1, DEFAULT_MAX_SKILL));
    SetCrushEnd(GetRandomIntValue<Short>(GetCrushStart() + 1, DEFAULT_MAX_SKILL));
    SetImpactStart(GetRandomIntValue<Short>(1, DEFAULT_MAX_SKILL));
    SetImpactEnd(GetRandomIntValue<Short>(GetImpactStart() + 1, DEFAULT_MAX_SKILL));
    SetBreakStart(GetRandomIntValue<Short>(1, DEFAULT_MAX_SKILL));
    SetBreakEnd(GetRandomIntValue<Short>(GetBreakStart() + 1, DEFAULT_MAX_SKILL));
    SetCrackStart(GetRandomIntValue<Short>(1, DEFAULT_MAX_SKILL));
    SetCrackEnd(GetRandomIntValue<Short>(GetCrackStart() + 1, DEFAULT_MAX_SKILL));
    SetBlockStart(GetRandomIntValue<Short>(1, DEFAULT_MAX_SKILL));
    SetBlockEnd(GetRandomIntValue<Short>(GetBlockStart() + 1, DEFAULT_MAX_SKILL));
    SetRushStart(GetRandomIntValue<Short>(1, DEFAULT_MAX_SKILL));
    SetRushEnd(GetRandomIntValue<Short>(GetRushStart() + 1, DEFAULT_MAX_SKILL));
    SetPierceStart(GetRandomIntValue<Short>(1, DEFAULT_MAX_SKILL));
    SetPierceEnd(GetRandomIntValue<Short>(GetPierceStart() + 1, DEFAULT_MAX_SKILL));
    SetDrillStart(GetRandomIntValue<Short>(1, DEFAULT_MAX_SKILL));
    SetDrillEnd(GetRandomIntValue<Short>(GetDrillStart() + 1, DEFAULT_MAX_SKILL));
    SetShootStart(GetRandomIntValue<Short>(1, DEFAULT_MAX_SKILL));
    SetShootEnd(GetRandomIntValue<Short>(GetShootStart() + 1, DEFAULT_MAX_SKILL));
    SetImpaleStart(GetRandomIntValue<Short>(1, DEFAULT_MAX_SKILL));
    SetImpaleEnd(GetRandomIntValue<Short>(GetImpaleStart() + 1, DEFAULT_MAX_SKILL));
    SetStealthStrikeStart(GetRandomIntValue<Short>(1, DEFAULT_MAX_SKILL));
    SetStealthStrikeEnd(GetRandomIntValue<Short>(GetStealthStrikeStart() + 1, DEFAULT_MAX_SKILL));
    SetCriticalShotStart(GetRandomIntValue<Short>(1, DEFAULT_MAX_SKILL));
    SetCriticalShotEnd(GetRandomIntValue<Short>(GetCriticalShotStart() + 1, DEFAULT_MAX_SKILL));
    SetDodgeStart(GetRandomIntValue<Short>(1, DEFAULT_MAX_SKILL));
    SetDodgeEnd(GetRandomIntValue<Short>(GetDodgeStart() + 1, DEFAULT_MAX_SKILL));
    SetCounterStart(GetRandomIntValue<Short>(1, DEFAULT_MAX_SKILL));
    SetCounterEnd(GetRandomIntValue<Short>(GetCounterStart() + 1, DEFAULT_MAX_SKILL));

    // Alchemy Skills
    SetHealerStart(GetRandomIntValue<Short>(1, DEFAULT_MAX_SKILL));
    SetHealerEnd(GetRandomIntValue<Short>(GetHealerStart() + 1, DEFAULT_MAX_SKILL));
    SetAlchemistStart(GetRandomIntValue<Short>(1, DEFAULT_MAX_SKILL));
    SetAlchemistEnd(GetRandomIntValue<Short>(GetAlchemistStart() + 1, DEFAULT_MAX_SKILL));
    SetEnergistStart(GetRandomIntValue<Short>(1, DEFAULT_MAX_SKILL));
    SetEnergistEnd(GetRandomIntValue<Short>(GetEnergistStart() + 1, DEFAULT_MAX_SKILL));
    SetChemistStart(GetRandomIntValue<Short>(1, DEFAULT_MAX_SKILL));
    SetChemistEnd(GetRandomIntValue<Short>(GetChemistStart() + 1, DEFAULT_MAX_SKILL));

    // Crafting Skills
    SetHammersmithStart(GetRandomIntValue<Short>(1, DEFAULT_MAX_SKILL));
    SetHammersmithEnd(GetRandomIntValue<Short>(GetHammersmithStart() + 1, DEFAULT_MAX_SKILL));
    SetSpellsmithStart(GetRandomIntValue<Short>(1, DEFAULT_MAX_SKILL));
    SetSpellsmithEnd(GetRandomIntValue<Short>(GetSpellsmithStart() + 1, DEFAULT_MAX_SKILL));
    SetBowsmithStart(GetRandomIntValue<Short>(1, DEFAULT_MAX_SKILL));
    SetBowsmithEnd(GetRandomIntValue<Short>(GetBowsmithStart() + 1, DEFAULT_MAX_SKILL));
    SetSwordsmithStart(GetRandomIntValue<Short>(1, DEFAULT_MAX_SKILL));
    SetSwordsmithEnd(GetRandomIntValue<Short>(GetSwordsmithStart() + 1, DEFAULT_MAX_SKILL));
    SetWeaverStart(GetRandomIntValue<Short>(1, DEFAULT_MAX_SKILL));
    SetWeaverEnd(GetRandomIntValue<Short>(GetWeaverStart() + 1, DEFAULT_MAX_SKILL));
    SetTannerStart(GetRandomIntValue<Short>(1, DEFAULT_MAX_SKILL));
    SetTannerEnd(GetRandomIntValue<Short>(GetTannerStart() + 1, DEFAULT_MAX_SKILL));
    SetScalesmithStart(GetRandomIntValue<Short>(1, DEFAULT_MAX_SKILL));
    SetScalesmithEnd(GetRandomIntValue<Short>(GetScalesmithStart() + 1, DEFAULT_MAX_SKILL));
    SetPlatesmithStart(GetRandomIntValue<Short>(1, DEFAULT_MAX_SKILL));
    SetPlatesmithEnd(GetRandomIntValue<Short>(GetPlatesmithStart() + 1, DEFAULT_MAX_SKILL));
    SetGoldsmithStart(GetRandomIntValue<Short>(1, DEFAULT_MAX_SKILL));
    SetGoldsmithEnd(GetRandomIntValue<Short>(GetGoldsmithStart() + 1, DEFAULT_MAX_SKILL));
    SetShieldsmithStart(GetRandomIntValue<Short>(1, DEFAULT_MAX_SKILL));
    SetShieldsmithEnd(GetRandomIntValue<Short>(GetShieldsmithStart() + 1, DEFAULT_MAX_SKILL));

    // Breakdown Skills
    SetHammerbaneStart(GetRandomIntValue<Short>(1, DEFAULT_MAX_SKILL));
    SetHammerbaneEnd(GetRandomIntValue<Short>(GetHammerbaneStart() + 1, DEFAULT_MAX_SKILL));
    SetSpellbaneStart(GetRandomIntValue<Short>(1, DEFAULT_MAX_SKILL));
    SetSpellbaneEnd(GetRandomIntValue<Short>(GetSpellbaneStart() + 1, DEFAULT_MAX_SKILL));
    SetBowbaneStart(GetRandomIntValue<Short>(1, DEFAULT_MAX_SKILL));
    SetBowbaneEnd(GetRandomIntValue<Short>(GetBowbaneStart() + 1, DEFAULT_MAX_SKILL));
    SetSwordbaneStart(GetRandomIntValue<Short>(1, DEFAULT_MAX_SKILL));
    SetSwordbaneEnd(GetRandomIntValue<Short>(GetSwordbaneStart() + 1, DEFAULT_MAX_SKILL));
    SetThreadbareStart(GetRandomIntValue<Short>(1, DEFAULT_MAX_SKILL));
    SetThreadbareEnd(GetRandomIntValue<Short>(GetThreadbareStart() + 1, DEFAULT_MAX_SKILL));
    SetStudRemoverStart(GetRandomIntValue<Short>(1, DEFAULT_MAX_SKILL));
    SetStudRemoverEnd(GetRandomIntValue<Short>(GetStudRemoverStart() + 1, DEFAULT_MAX_SKILL));
    SetScalebaneStart(GetRandomIntValue<Short>(1, DEFAULT_MAX_SKILL));
    SetScalebaneEnd(GetRandomIntValue<Short>(GetScalebaneStart() + 1, DEFAULT_MAX_SKILL));
    SetPlatebaneStart(GetRandomIntValue<Short>(1, DEFAULT_MAX_SKILL));
    SetPlatebaneEnd(GetRandomIntValue<Short>(GetPlatebaneStart() + 1, DEFAULT_MAX_SKILL));
    SetGoldbaneStart(GetRandomIntValue<Short>(1, DEFAULT_MAX_SKILL));
    SetGoldbaneEnd(GetRandomIntValue<Short>(GetGoldbaneStart() + 1, DEFAULT_MAX_SKILL));
    SetShieldbaneStart(GetRandomIntValue<Short>(1, DEFAULT_MAX_SKILL));
    SetShieldbaneEnd(GetRandomIntValue<Short>(GetShieldbaneStart() + 1, DEFAULT_MAX_SKILL));

    // Affinity Skills
    SetHolyStart(GetRandomIntValue<Short>(1, DEFAULT_MAX_SKILL));
    SetHolyEnd(GetRandomIntValue<Short>(GetHolyStart() + 1, DEFAULT_MAX_SKILL));
    SetFireStart(GetRandomIntValue<Short>(1, DEFAULT_MAX_SKILL));
    SetFireEnd(GetRandomIntValue<Short>(GetFireStart() + 1, DEFAULT_MAX_SKILL));
    SetIceStart(GetRandomIntValue<Short>(1, DEFAULT_MAX_SKILL));
    SetIceEnd(GetRandomIntValue<Short>(GetIceStart() + 1, DEFAULT_MAX_SKILL));
    SetShockStart(GetRandomIntValue<Short>(1, DEFAULT_MAX_SKILL));
    SetShockEnd(GetRandomIntValue<Short>(GetShockStart() + 1, DEFAULT_MAX_SKILL));
    SetDarkStart(GetRandomIntValue<Short>(1, DEFAULT_MAX_SKILL));
    SetDarkEnd(GetRandomIntValue<Short>(GetDarkStart() + 1, DEFAULT_MAX_SKILL));
    SetLightStart(GetRandomIntValue<Short>(1, DEFAULT_MAX_SKILL));
    SetLightEnd(GetRandomIntValue<Short>(GetLightStart() + 1, DEFAULT_MAX_SKILL));
    SetForceStart(GetRandomIntValue<Short>(1, DEFAULT_MAX_SKILL));
    SetForceEnd(GetRandomIntValue<Short>(GetForceStart() + 1, DEFAULT_MAX_SKILL));
    SetMindStart(GetRandomIntValue<Short>(1, DEFAULT_MAX_SKILL));
    SetMindEnd(GetRandomIntValue<Short>(GetMindStart() + 1, DEFAULT_MAX_SKILL));
    SetEarthStart(GetRandomIntValue<Short>(1, DEFAULT_MAX_SKILL));
    SetEarthEnd(GetRandomIntValue<Short>(GetEarthStart() + 1, DEFAULT_MAX_SKILL));
    SetBloodStart(GetRandomIntValue<Short>(1, DEFAULT_MAX_SKILL));
    SetBloodEnd(GetRandomIntValue<Short>(GetBloodStart() + 1, DEFAULT_MAX_SKILL));
    SetFleshStart(GetRandomIntValue<Short>(1, DEFAULT_MAX_SKILL));
    SetFleshEnd(GetRandomIntValue<Short>(GetFleshStart() + 1, DEFAULT_MAX_SKILL));
    SetWindStart(GetRandomIntValue<Short>(1, DEFAULT_MAX_SKILL));
    SetWindEnd(GetRandomIntValue<Short>(GetWindStart() + 1, DEFAULT_MAX_SKILL));
}

void CharacterGenerator::RandomizeAll()
{
    RandomizeBasics();
    RandomizeMeters();
    RandomizeScoring();
    RandomizeSkills();
}

void to_json(Json& jsonData, const CharacterGenerator& obj)
{
    // Basics
    SET_JSON_DATA(FirstName);
    SET_JSON_DATA(LastName);
    SET_JSON_DATA(FirstNamePattern);
    SET_JSON_DATA(LastNamePattern);
    SET_JSON_DATA(Age);
    SET_JSON_DATA(AgeStart);
    SET_JSON_DATA(AgeEnd);
    SET_JSON_DATA(Gender);
    SET_JSON_DATA(Hair);
    SET_JSON_DATA(Eyes);
    SET_JSON_DATA(Handedness);
    SET_JSON_DATA(BaseRace);
    SET_JSON_DATA(TransformedRace);
    SET_JSON_DATA(PowerSet);
    SET_JSON_DATA(WeaponSet);
    SET_JSON_DATA(UseRandomName);
    SET_JSON_DATA(UseRandomAge);
    SET_JSON_DATA(UseRandomGender);
    SET_JSON_DATA(UseRandomHair);
    SET_JSON_DATA(UseRandomEyes);
    SET_JSON_DATA(UseRandomHandedness);
    SET_JSON_DATA(UseRandomBaseRace);
    SET_JSON_DATA(UseRandomTransformedRace);
    SET_JSON_DATA(UseRandomPowerSet);
    SET_JSON_DATA(UseRandomWeaponSet);

    // Meters
    SET_JSON_DATA(HPStart);
    SET_JSON_DATA(HPEnd);
    SET_JSON_DATA(MPStart);
    SET_JSON_DATA(MPEnd);
    SET_JSON_DATA(EPStart);
    SET_JSON_DATA(EPEnd);
    SET_JSON_DATA(HPRegenStart);
    SET_JSON_DATA(HPRegenEnd);
    SET_JSON_DATA(MPRegenStart);
    SET_JSON_DATA(MPRegenEnd);
    SET_JSON_DATA(EPRegenStart);
    SET_JSON_DATA(EPRegenEnd);
    SET_JSON_DATA(SpeedStart);
    SET_JSON_DATA(SpeedEnd);

    // Attack and Defense Scoring
    SET_JSON_DATA(BluntATKStart);
    SET_JSON_DATA(BluntATKEnd);
    SET_JSON_DATA(BluntDEFStart);
    SET_JSON_DATA(BluntDEFEnd);
    SET_JSON_DATA(PierceATKStart);
    SET_JSON_DATA(PierceATKEnd);
    SET_JSON_DATA(PierceDEFStart);
    SET_JSON_DATA(PierceDEFEnd);
    SET_JSON_DATA(SlashATKStart);
    SET_JSON_DATA(SlashATKEnd);
    SET_JSON_DATA(SlashDEFStart);
    SET_JSON_DATA(SlashDEFEnd);
    SET_JSON_DATA(EnergyATKStart);
    SET_JSON_DATA(EnergyATKEnd);
    SET_JSON_DATA(EnergyDEFStart);
    SET_JSON_DATA(EnergyDEFEnd);
    SET_JSON_DATA(MagicATKStart);
    SET_JSON_DATA(MagicATKEnd);
    SET_JSON_DATA(MagicDEFStart);
    SET_JSON_DATA(MagicDEFEnd);

    // Combat Skills
    SET_JSON_DATA(BarbarianStart);
    SET_JSON_DATA(BarbarianEnd);
    SET_JSON_DATA(MageStart);
    SET_JSON_DATA(MageEnd);
    SET_JSON_DATA(RogueStart);
    SET_JSON_DATA(RogueEnd);
    SET_JSON_DATA(BlademasterStart);
    SET_JSON_DATA(BlademasterEnd);
    SET_JSON_DATA(AvatarStart);
    SET_JSON_DATA(AvatarEnd);
    SET_JSON_DATA(AmbidextrousStart);
    SET_JSON_DATA(AmbidextrousEnd);
    SET_JSON_DATA(FocusedStart);
    SET_JSON_DATA(FocusedEnd);
    SET_JSON_DATA(StalwartStart);
    SET_JSON_DATA(StalwartEnd);

    // Weapon Skills
    SET_JSON_DATA(SlashStart);
    SET_JSON_DATA(SlashEnd);
    SET_JSON_DATA(SeverStart);
    SET_JSON_DATA(SeverEnd);
    SET_JSON_DATA(SliceStart);
    SET_JSON_DATA(SliceEnd);
    SET_JSON_DATA(SlitStart);
    SET_JSON_DATA(SlitEnd);
    SET_JSON_DATA(CleaveStart);
    SET_JSON_DATA(CleaveEnd);
    SET_JSON_DATA(DecapitateStart);
    SET_JSON_DATA(DecapitateEnd);
    SET_JSON_DATA(ParryStart);
    SET_JSON_DATA(ParryEnd);
    SET_JSON_DATA(RiposteStart);
    SET_JSON_DATA(RiposteEnd);
    SET_JSON_DATA(BashStart);
    SET_JSON_DATA(BashEnd);
    SET_JSON_DATA(SmashStart);
    SET_JSON_DATA(SmashEnd);
    SET_JSON_DATA(CrushStart);
    SET_JSON_DATA(CrushEnd);
    SET_JSON_DATA(ImpactStart);
    SET_JSON_DATA(ImpactEnd);
    SET_JSON_DATA(BreakStart);
    SET_JSON_DATA(BreakEnd);
    SET_JSON_DATA(CrackStart);
    SET_JSON_DATA(CrackEnd);
    SET_JSON_DATA(BlockStart);
    SET_JSON_DATA(BlockEnd);
    SET_JSON_DATA(RushStart);
    SET_JSON_DATA(RushEnd);
    SET_JSON_DATA(PierceStart);
    SET_JSON_DATA(PierceEnd);
    SET_JSON_DATA(DrillStart);
    SET_JSON_DATA(DrillEnd);
    SET_JSON_DATA(ShootStart);
    SET_JSON_DATA(ShootEnd);
    SET_JSON_DATA(ImpaleStart);
    SET_JSON_DATA(ImpaleEnd);
    SET_JSON_DATA(StealthStrikeStart);
    SET_JSON_DATA(StealthStrikeEnd);
    SET_JSON_DATA(CriticalShotStart);
    SET_JSON_DATA(CriticalShotEnd);
    SET_JSON_DATA(DodgeStart);
    SET_JSON_DATA(DodgeEnd);
    SET_JSON_DATA(CounterStart);
    SET_JSON_DATA(CounterEnd);

    // Alchemy Skills
    SET_JSON_DATA(HealerStart);
    SET_JSON_DATA(HealerEnd);
    SET_JSON_DATA(AlchemistStart);
    SET_JSON_DATA(AlchemistEnd);
    SET_JSON_DATA(EnergistStart);
    SET_JSON_DATA(EnergistEnd);
    SET_JSON_DATA(ChemistStart);
    SET_JSON_DATA(ChemistEnd);

    // Crafting Skills
    SET_JSON_DATA(HammersmithStart);
    SET_JSON_DATA(HammersmithEnd);
    SET_JSON_DATA(SpellsmithStart);
    SET_JSON_DATA(SpellsmithEnd);
    SET_JSON_DATA(BowsmithStart);
    SET_JSON_DATA(BowsmithEnd);
    SET_JSON_DATA(SwordsmithStart);
    SET_JSON_DATA(SwordsmithEnd);
    SET_JSON_DATA(WeaverStart);
    SET_JSON_DATA(WeaverEnd);
    SET_JSON_DATA(TannerStart);
    SET_JSON_DATA(TannerEnd);
    SET_JSON_DATA(ScalesmithStart);
    SET_JSON_DATA(ScalesmithEnd);
    SET_JSON_DATA(PlatesmithStart);
    SET_JSON_DATA(PlatesmithEnd);
    SET_JSON_DATA(GoldsmithStart);
    SET_JSON_DATA(GoldsmithEnd);
    SET_JSON_DATA(ShieldsmithStart);
    SET_JSON_DATA(ShieldsmithEnd);

    // Breakdown Skills
    SET_JSON_DATA(HammerbaneStart);
    SET_JSON_DATA(HammerbaneEnd);
    SET_JSON_DATA(SpellbaneStart);
    SET_JSON_DATA(SpellbaneEnd);
    SET_JSON_DATA(BowbaneStart);
    SET_JSON_DATA(BowbaneEnd);
    SET_JSON_DATA(SwordbaneStart);
    SET_JSON_DATA(SwordbaneEnd);
    SET_JSON_DATA(ThreadbareStart);
    SET_JSON_DATA(ThreadbareEnd);
    SET_JSON_DATA(StudRemoverStart);
    SET_JSON_DATA(StudRemoverEnd);
    SET_JSON_DATA(ScalebaneStart);
    SET_JSON_DATA(ScalebaneEnd);
    SET_JSON_DATA(PlatebaneStart);
    SET_JSON_DATA(PlatebaneEnd);
    SET_JSON_DATA(GoldbaneStart);
    SET_JSON_DATA(GoldbaneEnd);
    SET_JSON_DATA(ShieldbaneStart);
    SET_JSON_DATA(ShieldbaneEnd);

    // Affinity Skills
    SET_JSON_DATA(HolyStart);
    SET_JSON_DATA(HolyEnd);
    SET_JSON_DATA(FireStart);
    SET_JSON_DATA(FireEnd);
    SET_JSON_DATA(IceStart);
    SET_JSON_DATA(IceEnd);
    SET_JSON_DATA(ShockStart);
    SET_JSON_DATA(ShockEnd);
    SET_JSON_DATA(DarkStart);
    SET_JSON_DATA(DarkEnd);
    SET_JSON_DATA(LightStart);
    SET_JSON_DATA(LightEnd);
    SET_JSON_DATA(ForceStart);
    SET_JSON_DATA(ForceEnd);
    SET_JSON_DATA(MindStart);
    SET_JSON_DATA(MindEnd);
    SET_JSON_DATA(EarthStart);
    SET_JSON_DATA(EarthEnd);
    SET_JSON_DATA(BloodStart);
    SET_JSON_DATA(BloodEnd);
    SET_JSON_DATA(FleshStart);
    SET_JSON_DATA(FleshEnd);
    SET_JSON_DATA(WindStart);
    SET_JSON_DATA(WindEnd);
}

void from_json(const Json& jsonData, CharacterGenerator& obj)
{
    // Basics
    SET_OBJ_DATA(FirstName, String);
    SET_OBJ_DATA(LastName, String);
    SET_OBJ_DATA(FirstNamePattern, String);
    SET_OBJ_DATA(LastNamePattern, String);
    SET_OBJ_DATA(Age, Int);
    SET_OBJ_DATA(AgeStart, Int);
    SET_OBJ_DATA(AgeEnd, Int);
    SET_OBJ_DATA(Gender, String);
    SET_OBJ_DATA(Hair, String);
    SET_OBJ_DATA(Eyes, String);
    SET_OBJ_DATA(Handedness, String);
    SET_OBJ_DATA(BaseRace, String);
    SET_OBJ_DATA(TransformedRace, String);
    SET_OBJ_DATA(PowerSet, String);
    SET_OBJ_DATA(WeaponSet, String);
    SET_OBJ_DATA(UseRandomName, Bool);
    SET_OBJ_DATA(UseRandomAge, Bool);
    SET_OBJ_DATA(UseRandomGender, Bool);
    SET_OBJ_DATA(UseRandomHair, Bool);
    SET_OBJ_DATA(UseRandomEyes, Bool);
    SET_OBJ_DATA(UseRandomHandedness, Bool);
    SET_OBJ_DATA(UseRandomBaseRace, Bool);
    SET_OBJ_DATA(UseRandomTransformedRace, Bool);
    SET_OBJ_DATA(UseRandomPowerSet, Bool);
    SET_OBJ_DATA(UseRandomWeaponSet, Bool);

    // Meters
    SET_OBJ_DATA(HPStart, Int);
    SET_OBJ_DATA(HPEnd, Int);
    SET_OBJ_DATA(MPStart, Int);
    SET_OBJ_DATA(MPEnd, Int);
    SET_OBJ_DATA(EPStart, Int);
    SET_OBJ_DATA(EPEnd, Int);
    SET_OBJ_DATA(HPRegenStart, Int);
    SET_OBJ_DATA(HPRegenEnd, Int);
    SET_OBJ_DATA(MPRegenStart, Int);
    SET_OBJ_DATA(MPRegenEnd, Int);
    SET_OBJ_DATA(EPRegenStart, Int);
    SET_OBJ_DATA(EPRegenEnd, Int);
    SET_OBJ_DATA(SpeedStart, Int);
    SET_OBJ_DATA(SpeedEnd, Int);

    // Attack and Defense Scoring
    SET_OBJ_DATA(BluntATKStart, Int);
    SET_OBJ_DATA(BluntATKEnd, Int);
    SET_OBJ_DATA(BluntDEFStart, Int);
    SET_OBJ_DATA(BluntDEFEnd, Int);
    SET_OBJ_DATA(PierceATKStart, Int);
    SET_OBJ_DATA(PierceATKEnd, Int);
    SET_OBJ_DATA(PierceDEFStart, Int);
    SET_OBJ_DATA(PierceDEFEnd, Int);
    SET_OBJ_DATA(SlashATKStart, Int);
    SET_OBJ_DATA(SlashATKEnd, Int);
    SET_OBJ_DATA(SlashDEFStart, Int);
    SET_OBJ_DATA(SlashDEFEnd, Int);
    SET_OBJ_DATA(EnergyATKStart, Int);
    SET_OBJ_DATA(EnergyATKEnd, Int);
    SET_OBJ_DATA(EnergyDEFStart, Int);
    SET_OBJ_DATA(EnergyDEFEnd, Int);
    SET_OBJ_DATA(MagicATKStart, Int);
    SET_OBJ_DATA(MagicATKEnd, Int);
    SET_OBJ_DATA(MagicDEFStart, Int);
    SET_OBJ_DATA(MagicDEFEnd, Int);

    // Combat Skills
    SET_OBJ_DATA(BarbarianStart, Short);
    SET_OBJ_DATA(BarbarianEnd, Short);
    SET_OBJ_DATA(MageStart, Short);
    SET_OBJ_DATA(MageEnd, Short);
    SET_OBJ_DATA(RogueStart, Short);
    SET_OBJ_DATA(RogueEnd, Short);
    SET_OBJ_DATA(BlademasterStart, Short);
    SET_OBJ_DATA(BlademasterEnd, Short);
    SET_OBJ_DATA(AvatarStart, Short);
    SET_OBJ_DATA(AvatarEnd, Short);
    SET_OBJ_DATA(AmbidextrousStart, Short);
    SET_OBJ_DATA(AmbidextrousEnd, Short);
    SET_OBJ_DATA(FocusedStart, Short);
    SET_OBJ_DATA(FocusedEnd, Short);
    SET_OBJ_DATA(StalwartStart, Short);
    SET_OBJ_DATA(StalwartEnd, Short);

    // Weapon Skills
    SET_OBJ_DATA(SlashStart, Short);
    SET_OBJ_DATA(SlashEnd, Short);
    SET_OBJ_DATA(SeverStart, Short);
    SET_OBJ_DATA(SeverEnd, Short);
    SET_OBJ_DATA(SliceStart, Short);
    SET_OBJ_DATA(SliceEnd, Short);
    SET_OBJ_DATA(SlitStart, Short);
    SET_OBJ_DATA(SlitEnd, Short);
    SET_OBJ_DATA(CleaveStart, Short);
    SET_OBJ_DATA(CleaveEnd, Short);
    SET_OBJ_DATA(DecapitateStart, Short);
    SET_OBJ_DATA(DecapitateEnd, Short);
    SET_OBJ_DATA(ParryStart, Short);
    SET_OBJ_DATA(ParryEnd, Short);
    SET_OBJ_DATA(RiposteStart, Short);
    SET_OBJ_DATA(RiposteEnd, Short);
    SET_OBJ_DATA(BashStart, Short);
    SET_OBJ_DATA(BashEnd, Short);
    SET_OBJ_DATA(SmashStart, Short);
    SET_OBJ_DATA(SmashEnd, Short);
    SET_OBJ_DATA(CrushStart, Short);
    SET_OBJ_DATA(CrushEnd, Short);
    SET_OBJ_DATA(ImpactStart, Short);
    SET_OBJ_DATA(ImpactEnd, Short);
    SET_OBJ_DATA(BreakStart, Short);
    SET_OBJ_DATA(BreakEnd, Short);
    SET_OBJ_DATA(CrackStart, Short);
    SET_OBJ_DATA(CrackEnd, Short);
    SET_OBJ_DATA(BlockStart, Short);
    SET_OBJ_DATA(BlockEnd, Short);
    SET_OBJ_DATA(RushStart, Short);
    SET_OBJ_DATA(RushEnd, Short);
    SET_OBJ_DATA(PierceStart, Short);
    SET_OBJ_DATA(PierceEnd, Short);
    SET_OBJ_DATA(DrillStart, Short);
    SET_OBJ_DATA(DrillEnd, Short);
    SET_OBJ_DATA(ShootStart, Short);
    SET_OBJ_DATA(ShootEnd, Short);
    SET_OBJ_DATA(ImpaleStart, Short);
    SET_OBJ_DATA(ImpaleEnd, Short);
    SET_OBJ_DATA(StealthStrikeStart, Short);
    SET_OBJ_DATA(StealthStrikeEnd, Short);
    SET_OBJ_DATA(CriticalShotStart, Short);
    SET_OBJ_DATA(CriticalShotEnd, Short);
    SET_OBJ_DATA(DodgeStart, Short);
    SET_OBJ_DATA(DodgeEnd, Short);
    SET_OBJ_DATA(CounterStart, Short);
    SET_OBJ_DATA(CounterEnd, Short);

    // Alchemy Skills
    SET_OBJ_DATA(HealerStart, Short);
    SET_OBJ_DATA(HealerEnd, Short);
    SET_OBJ_DATA(AlchemistStart, Short);
    SET_OBJ_DATA(AlchemistEnd, Short);
    SET_OBJ_DATA(EnergistStart, Short);
    SET_OBJ_DATA(EnergistEnd, Short);
    SET_OBJ_DATA(ChemistStart, Short);
    SET_OBJ_DATA(ChemistEnd, Short);

    // Crafting Skills
    SET_OBJ_DATA(HammersmithStart, Short);
    SET_OBJ_DATA(HammersmithEnd, Short);
    SET_OBJ_DATA(SpellsmithStart, Short);
    SET_OBJ_DATA(SpellsmithEnd, Short);
    SET_OBJ_DATA(BowsmithStart, Short);
    SET_OBJ_DATA(BowsmithEnd, Short);
    SET_OBJ_DATA(SwordsmithStart, Short);
    SET_OBJ_DATA(SwordsmithEnd, Short);
    SET_OBJ_DATA(WeaverStart, Short);
    SET_OBJ_DATA(WeaverEnd, Short);
    SET_OBJ_DATA(TannerStart, Short);
    SET_OBJ_DATA(TannerEnd, Short);
    SET_OBJ_DATA(ScalesmithStart, Short);
    SET_OBJ_DATA(ScalesmithEnd, Short);
    SET_OBJ_DATA(PlatesmithStart, Short);
    SET_OBJ_DATA(PlatesmithEnd, Short);
    SET_OBJ_DATA(GoldsmithStart, Short);
    SET_OBJ_DATA(GoldsmithEnd, Short);
    SET_OBJ_DATA(ShieldsmithStart, Short);
    SET_OBJ_DATA(ShieldsmithEnd, Short);

    // Breakdown Skills
    SET_OBJ_DATA(HammerbaneStart, Short);
    SET_OBJ_DATA(HammerbaneEnd, Short);
    SET_OBJ_DATA(SpellbaneStart, Short);
    SET_OBJ_DATA(SpellbaneEnd, Short);
    SET_OBJ_DATA(BowbaneStart, Short);
    SET_OBJ_DATA(BowbaneEnd, Short);
    SET_OBJ_DATA(SwordbaneStart, Short);
    SET_OBJ_DATA(SwordbaneEnd, Short);
    SET_OBJ_DATA(ThreadbareStart, Short);
    SET_OBJ_DATA(ThreadbareEnd, Short);
    SET_OBJ_DATA(StudRemoverStart, Short);
    SET_OBJ_DATA(StudRemoverEnd, Short);
    SET_OBJ_DATA(ScalebaneStart, Short);
    SET_OBJ_DATA(ScalebaneEnd, Short);
    SET_OBJ_DATA(PlatebaneStart, Short);
    SET_OBJ_DATA(PlatebaneEnd, Short);
    SET_OBJ_DATA(GoldbaneStart, Short);
    SET_OBJ_DATA(GoldbaneEnd, Short);
    SET_OBJ_DATA(ShieldbaneStart, Short);
    SET_OBJ_DATA(ShieldbaneEnd, Short);

    // Affinity Skills
    SET_OBJ_DATA(HolyStart, Short);
    SET_OBJ_DATA(HolyEnd, Short);
    SET_OBJ_DATA(FireStart, Short);
    SET_OBJ_DATA(FireEnd, Short);
    SET_OBJ_DATA(IceStart, Short);
    SET_OBJ_DATA(IceEnd, Short);
    SET_OBJ_DATA(ShockStart, Short);
    SET_OBJ_DATA(ShockEnd, Short);
    SET_OBJ_DATA(DarkStart, Short);
    SET_OBJ_DATA(DarkEnd, Short);
    SET_OBJ_DATA(LightStart, Short);
    SET_OBJ_DATA(LightEnd, Short);
    SET_OBJ_DATA(ForceStart, Short);
    SET_OBJ_DATA(ForceEnd, Short);
    SET_OBJ_DATA(MindStart, Short);
    SET_OBJ_DATA(MindEnd, Short);
    SET_OBJ_DATA(EarthStart, Short);
    SET_OBJ_DATA(EarthEnd, Short);
    SET_OBJ_DATA(BloodStart, Short);
    SET_OBJ_DATA(BloodEnd, Short);
    SET_OBJ_DATA(FleshStart, Short);
    SET_OBJ_DATA(FleshEnd, Short);
    SET_OBJ_DATA(WindStart, Short);
    SET_OBJ_DATA(WindEnd, Short);
}

};
