// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#ifndef _GECKO_CONFIG_H_
#define _GECKO_CONFIG_H_

#include "Utility/Macros.h"
#include "Utility/TypesEnum.h"
#include "Utility/Serializable.h"

namespace Gecko
{

class Config : public SerializableToJson
{
public:

    // Constructors
    Config();
    explicit Config(const Json& jsonData);
    explicit Config(const String& jsonString);

    // Python library
    MAKE_JSON_BASIC_TYPE_ACCESSORS(PythonLib, String);

    // Character generator file locations
    MAKE_JSON_BASIC_TYPE_ACCESSORS(CharacterGeneratorRandomFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(CharacterGeneratorStaticFile, String);

    // Item file locations
    MAKE_JSON_BASIC_TYPE_ACCESSORS(ItemArmorChestFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(ItemArmorFeetFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(ItemArmorFingerFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(ItemArmorHandsFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(ItemArmorHeadFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(ItemArmorNeckFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(ItemArmorLegsFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(ItemArmorShieldFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(ItemIngredientBarFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(ItemIngredientClothFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(ItemIngredientCrystalFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(ItemIngredientLeatherFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(ItemIngredientMailFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(ItemIngredientPlateFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(ItemIngredientScaleFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(ItemIngredientScrewFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(ItemIngredientSheetFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(ItemIngredientStudFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(ItemIngredientThreadFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(ItemPotionEnergyFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(ItemPotionHealFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(ItemPotionMagicFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(ItemPotionSpeedFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(ItemWeaponBluntFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(ItemWeaponMageFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(ItemWeaponPierceFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(ItemWeaponSlashFile, String);

    // Skill file locations
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SkillAffinityBloodFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SkillAffinityDarkFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SkillAffinityEarthFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SkillAffinityFireFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SkillAffinityFleshFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SkillAffinityForceFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SkillAffinityHolyFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SkillAffinityIceFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SkillAffinityLightFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SkillAffinityMindFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SkillAffinityShockFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SkillAffinityWindFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SkillAlchemyAlchemistFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SkillAlchemyChemistFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SkillAlchemyEnergistFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SkillAlchemyHealerFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SkillBreakdownBowbaneFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SkillBreakdownGoldbaneFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SkillBreakdownHammerbaneFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SkillBreakdownPlatebaneFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SkillBreakdownScalebaneFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SkillBreakdownShieldbaneFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SkillBreakdownSpellbaneFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SkillBreakdownStudRemoverFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SkillBreakdownSwordbaneFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SkillBreakdownThreadbareFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SkillCombatAmbidextrousFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SkillCombatAvatarFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SkillCombatBarbarianFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SkillCombatBlademasterFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SkillCombatFocusedFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SkillCombatMageFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SkillCombatRogueFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SkillCombatStalwartFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SkillCraftingBowsmithFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SkillCraftingGoldsmithFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SkillCraftingHammersmithFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SkillCraftingPlatesmithFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SkillCraftingScalesmithFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SkillCraftingShieldsmithFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SkillCraftingSpellsmithFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SkillCraftingSwordsmithFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SkillCraftingTannerFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SkillCraftingWeaverFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SkillWeaponBashFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SkillWeaponBlockFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SkillWeaponBreakFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SkillWeaponCleaveFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SkillWeaponCounterFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SkillWeaponCrackFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SkillWeaponCriticalShotFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SkillWeaponCrushFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SkillWeaponDecapitateFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SkillWeaponDodgeFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SkillWeaponDrillFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SkillWeaponImpactFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SkillWeaponImpaleFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SkillWeaponParryFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SkillWeaponPierceFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SkillWeaponRiposteFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SkillWeaponRushFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SkillWeaponSeverFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SkillWeaponShootFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SkillWeaponSlashFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SkillWeaponSliceFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SkillWeaponSlitFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SkillWeaponSmashFile, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SkillWeaponStealthStrikeFile, String);

    // Default basic character data
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultFirstName, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultLastName, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultAge, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultGender, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultHair, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultEyes, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultHandedness, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultBaseRace, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultTransformedRace, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultPowerSet, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultCurrentWeaponSet, String);

    // Default combat Skills
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultBarbarianCurrent, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultBarbarianRank, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultMageCurrent, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultMageRank, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultRogueCurrent, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultRogueRank, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultBlademasterCurrent, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultBlademasterRank, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultAvatarCurrent, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultAvatarRank, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultAmbidextrousCurrent, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultAmbidextrousRank, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultFocusedCurrent, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultFocusedRank, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultStalwartCurrent, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultStalwartRank, Int);

    // Default weapon Skills
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultSlashCurrent, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultSlashRank, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultSeverCurrent, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultSeverRank, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultSliceCurrent, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultSliceRank, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultSlitCurrent, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultSlitRank, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultCleaveCurrent, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultCleaveRank, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultDecapitateCurrent, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultDecapitateRank, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultParryCurrent, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultParryRank, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultRiposteCurrent, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultRiposteRank, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultBashCurrent, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultBashRank, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultSmashCurrent, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultSmashRank, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultCrushCurrent, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultCrushRank, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultImpactCurrent, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultImpactRank, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultBreakCurrent, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultBreakRank, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultCrackCurrent, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultCrackRank, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultBlockCurrent, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultBlockRank, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultRushCurrent, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultRushRank, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultPierceCurrent, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultPierceRank, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultDrillCurrent, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultDrillRank, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultShootCurrent, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultShootRank, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultImpaleCurrent, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultImpaleRank, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultStealthStrikeCurrent, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultStealthStrikeRank, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultCriticalShotCurrent, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultCriticalShotRank, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultDodgeCurrent, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultDodgeRank, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultCounterCurrent, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultCounterRank, Int);

    // Default alchemy Skills
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultHealerCurrent, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultHealerRank, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultAlchemistCurrent, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultAlchemistRank, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultEnergistCurrent, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultEnergistRank, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultChemistCurrent, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultChemistRank, Int);

    // Default crafting Skills
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultHammersmithCurrent, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultHammersmithRank, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultSpellsmithCurrent, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultSpellsmithRank, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultBowsmithCurrent, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultBowsmithRank, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultSwordsmithCurrent, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultSwordsmithRank, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultWeaverCurrent, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultWeaverRank, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultTannerCurrent, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultTannerRank, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultScalesmithCurrent, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultScalesmithRank, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultPlatesmithCurrent, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultPlatesmithRank, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultGoldsmithCurrent, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultGoldsmithRank, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultShieldsmithCurrent, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultShieldsmithRank, Int);

    // Default breakdown Skills
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultHammerbaneCurrent, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultHammerbaneRank, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultSpellbaneCurrent, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultSpellbaneRank, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultBowbaneCurrent, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultBowbaneRank, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultSwordbaneCurrent, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultSwordbaneRank, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultThreadbareCurrent, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultThreadbareRank, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultStudRemoverCurrent, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultStudRemoverRank, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultScalebaneCurrent, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultScalebaneRank, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultPlatebaneCurrent, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultPlatebaneRank, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultGoldbaneCurrent, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultGoldbaneRank, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultShieldbaneCurrent, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultShieldbaneRank, Int);

    // Default affinity Skills
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultHolyCurrent, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultHolyRank, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultFireCurrent, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultFireRank, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultIceCurrent, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultIceRank, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultShockCurrent, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultShockRank, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultDarkCurrent, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultDarkRank, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultLightCurrent, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultLightRank, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultForceCurrent, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultForceRank, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultMindCurrent, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultMindRank, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultEarthCurrent, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultEarthRank, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultBloodCurrent, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultBloodRank, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultFleshCurrent, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultFleshRank, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultWindCurrent, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultWindRank, Int);

    // Default target amount
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultAllowedTargetAmount, Int);

    // Default status
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultIsDead, Bool);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultIsUnconscious, Bool);

    // Default equipment ratings
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultEquippedWeaponLeftBluntRating, Float);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultEquippedWeaponLeftPierceRating, Float);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultEquippedWeaponLeftSlashRating, Float);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultEquippedWeaponRightBluntRating, Float);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultEquippedWeaponRightPierceRating, Float);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultEquippedWeaponRightSlashRating, Float);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultEquippedShieldLeftBluntRating, Float);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultEquippedShieldLeftPierceRating, Float);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultEquippedShieldLeftSlashRating, Float);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultEquippedShieldLeftMagicRating, Float);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultEquippedShieldRightBluntRating, Float);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultEquippedShieldRightPierceRating, Float);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultEquippedShieldRightSlashRating, Float);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultEquippedShieldRightMagicRating, Float);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultEquippedArmorBluntRating, Float);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultEquippedArmorPierceRating, Float);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultEquippedArmorSlashRating, Float);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultEquippedArmorMagicRating, Float);

    // Default critical hits
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultChanceToCauseCriticalHit, Float);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultChanceToBlockCriticalHit, Float);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultCriticalHitMultiplier, Float);

    // Default multiple attacks
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultChanceToApplyMultipleAttacks, Float);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultAttacksMultiplier, Float);

    // Default damage counters
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultDamageTakenThisRound, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultDamageTakenThisBattle, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultDamageGivenThisRound, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultDamageGivenThisBattle, Int);

    // Default damage bonus
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultWeaponPrimaryDamageBonusValue, Float);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultWeaponPrimaryDamageBonusPercent, Float);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultWeaponSecondaryDamageBonusValue, Float);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultWeaponSecondaryDamageBonusPercent, Float);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultGeneralDamageBonusValue, Float);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultGeneralDamageBonusPercent, Float);

    // Default effects bonus
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultDefensivePowerEffectsBonusValue, Float);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultDefensivePowerEffectsBonusPercent, Float);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultOffensivePowerEffectsBonusValue, Float);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(DefaultOffensivePowerEffectsBonusPercent, Float);
};

// Typedef
MAKE_TYPE_TYPEDEFS(Config);

// JSON Converters
MAKE_JSON_BASIC_TYPE_CONVERTERS_DECL(Config);
MAKE_JSON_GENERIC_TYPE_CONVERTERS_DECL(Config, Config);

};

#endif
