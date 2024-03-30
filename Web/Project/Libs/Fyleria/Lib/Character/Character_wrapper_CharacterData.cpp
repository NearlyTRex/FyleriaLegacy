// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#include "Character/CharacterProgressItem.h"
#include "Character/CharacterProgressData.h"
#include "Character/CharacterBattleData.h"
#include "Utility/Macros.h"
#include "Utility/TypesPython.h"

PYBIND11_MAKE_OPAQUE(Gecko::CharacterProgressDataList);
PYBIND11_MAKE_OPAQUE(Gecko::CharacterBattleDataList);
PYBIND11_MAKE_OPAQUE(Gecko::CharacterProgressItemList);

PYBIND11_EMBEDDED_MODULE(GeckoCharacterData, m)
{
    // CharacterProgressData.h
    PyBindClass<Gecko::CharacterProgressData, STDSharedPtr<Gecko::CharacterProgressData>>(m, "CharacterProgressData")
        WRAPPING_ADD_CONSTRUCTOR_SIMPLE()
        WRAPPING_ADD_METHOD_SIMPLE(Clear, Gecko::CharacterProgressData)
        WRAPPING_ADD_METHOD_SIMPLE(ApplyTakenDamage, Gecko::CharacterProgressData)
        WRAPPING_ADD_METHOD_SIMPLE(ApplyRegeneration, Gecko::CharacterProgressData)
        WRAPPING_ADD_METHOD_SIMPLE(ApplyActionCost, Gecko::CharacterProgressData)
        WRAPPING_ADD_METHOD_SIMPLE(UpdateAvailableAP, Gecko::CharacterProgressData)
        WRAPPING_ADD_METHOD_SIMPLE(GetIntStatValue, Gecko::CharacterProgressData)
        WRAPPING_ADD_METHOD_SIMPLE(SetIntStatValue, Gecko::CharacterProgressData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(HealthPointsCurrent, Gecko::CharacterProgressData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(MagicPointsCurrent, Gecko::CharacterProgressData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(EnergyPointsCurrent, Gecko::CharacterProgressData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(HealthPointsMax, Gecko::CharacterProgressData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(MagicPointsMax, Gecko::CharacterProgressData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(EnergyPointsMax, Gecko::CharacterProgressData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(HealthRegen, Gecko::CharacterProgressData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(MagicRegen, Gecko::CharacterProgressData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(EnergyRegen, Gecko::CharacterProgressData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(HealthCostDelta, Gecko::CharacterProgressData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(MagicCostDelta, Gecko::CharacterProgressData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(EnergyCostDelta, Gecko::CharacterProgressData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(Speed, Gecko::CharacterProgressData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(AmberValueDelta, Gecko::CharacterProgressData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(RubyValueDelta, Gecko::CharacterProgressData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(DiamondValueDelta, Gecko::CharacterProgressData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(CitrineValueDelta, Gecko::CharacterProgressData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(OnyxValueDelta, Gecko::CharacterProgressData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(QuartzValueDelta, Gecko::CharacterProgressData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(SapphireValueDelta, Gecko::CharacterProgressData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(AmethystValueDelta, Gecko::CharacterProgressData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(EmeraldValueDelta, Gecko::CharacterProgressData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(GarnetValueDelta, Gecko::CharacterProgressData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(IvoryValueDelta, Gecko::CharacterProgressData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(OpalValueDelta, Gecko::CharacterProgressData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(BluntAttack, Gecko::CharacterProgressData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(BluntDefense, Gecko::CharacterProgressData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(MagicAttack, Gecko::CharacterProgressData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(MagicDefense, Gecko::CharacterProgressData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(PierceAttack, Gecko::CharacterProgressData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(PierceDefense, Gecko::CharacterProgressData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(SlashAttack, Gecko::CharacterProgressData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(SlashDefense, Gecko::CharacterProgressData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(EnergyAttack, Gecko::CharacterProgressData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(EnergyDefense, Gecko::CharacterProgressData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(SlashPoints, Gecko::CharacterProgressData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(SeverPoints, Gecko::CharacterProgressData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(SlicePoints, Gecko::CharacterProgressData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(SlitPoints, Gecko::CharacterProgressData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(CleavePoints, Gecko::CharacterProgressData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(DecapitatePoints, Gecko::CharacterProgressData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(ParryPoints, Gecko::CharacterProgressData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(RipostePoints, Gecko::CharacterProgressData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(BashPoints, Gecko::CharacterProgressData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(SmashPoints, Gecko::CharacterProgressData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(ImpactPoints, Gecko::CharacterProgressData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(CrushPoints, Gecko::CharacterProgressData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(BreakPoints, Gecko::CharacterProgressData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(CrackPoints, Gecko::CharacterProgressData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(BlockPoints, Gecko::CharacterProgressData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(RushPoints, Gecko::CharacterProgressData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(PiercePoints, Gecko::CharacterProgressData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(DrillPoints, Gecko::CharacterProgressData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(ShootPoints, Gecko::CharacterProgressData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(ImpalePoints, Gecko::CharacterProgressData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(StealthStrikePoints, Gecko::CharacterProgressData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(CriticalShotPoints, Gecko::CharacterProgressData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(DodgePoints, Gecko::CharacterProgressData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(CounterPoints, Gecko::CharacterProgressData)
    ;
    PyBindVector<Gecko::CharacterProgressDataList>(m, "CharacterProgressDataList");
    WRAPPING_STANDALONE_METHOD_SIMPLE(ConvertCharacterProgressDataToJsonString, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(ConvertCharacterProgressDataListToJsonString, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetCharacterProgressDataFromJsonString, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetCharacterProgressDataListFromJsonString, Gecko);

    // CharacterBattleData.h
    PyBindClass<Gecko::CharacterBattleData, STDSharedPtr<Gecko::CharacterBattleData>>(m, "CharacterBattleData")
        WRAPPING_ADD_CONSTRUCTOR_SIMPLE()
        WRAPPING_ADD_METHOD_SIMPLE(Clear, Gecko::CharacterBattleData)
        WRAPPING_ADD_METHOD_SIMPLE(ApplyNewStatus, Gecko::CharacterBattleData)
        WRAPPING_ADD_METHOD_SIMPLE(ApplyGivenDamage, Gecko::CharacterBattleData)
        WRAPPING_ADD_METHOD_SIMPLE(ApplyTakenDamage, Gecko::CharacterBattleData)
        WRAPPING_ADD_METHOD_SIMPLE(AdvanceRound, Gecko::CharacterBattleData)
        WRAPPING_ADD_METHOD_SIMPLE(FinishBattle, Gecko::CharacterBattleData)
        WRAPPING_ADD_METHOD_SIMPLE(CanRegenerateFromStat, Gecko::CharacterBattleData)
        WRAPPING_ADD_METHOD_SIMPLE(UpdateEquipmentRatings, Gecko::CharacterBattleData)
        WRAPPING_ADD_METHOD_SIMPLE(GetPrimaryWeaponRatings, Gecko::CharacterBattleData)
        WRAPPING_ADD_METHOD_SIMPLE(GetSecondaryWeaponRatings, Gecko::CharacterBattleData)
        WRAPPING_ADD_METHOD_SIMPLE(GetPrimaryShieldRatings, Gecko::CharacterBattleData)
        WRAPPING_ADD_METHOD_SIMPLE(GetSecondaryShieldRatings, Gecko::CharacterBattleData)
        WRAPPING_ADD_METHOD_SIMPLE(GetBoolStatValue, Gecko::CharacterBattleData)
        WRAPPING_ADD_METHOD_SIMPLE(GetIntStatValue, Gecko::CharacterBattleData)
        WRAPPING_ADD_METHOD_SIMPLE(GetFloatStatValue, Gecko::CharacterBattleData)
        WRAPPING_ADD_METHOD_SIMPLE(GetStringStatValue, Gecko::CharacterBattleData)
        WRAPPING_ADD_METHOD_SIMPLE(GetStringListStatValue, Gecko::CharacterBattleData)
        WRAPPING_ADD_METHOD_SIMPLE(SetBoolStatValue, Gecko::CharacterBattleData)
        WRAPPING_ADD_METHOD_SIMPLE(SetIntStatValue, Gecko::CharacterBattleData)
        WRAPPING_ADD_METHOD_SIMPLE(SetFloatStatValue, Gecko::CharacterBattleData)
        WRAPPING_ADD_METHOD_SIMPLE(SetStringStatValue, Gecko::CharacterBattleData)
        WRAPPING_ADD_METHOD_SIMPLE(SetStringListStatValue, Gecko::CharacterBattleData)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(AttackTargetsThisAction, Gecko::CharacterBattleData)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(AttackTargetsThisRound, Gecko::CharacterBattleData)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(AttackTargetsLastRound, Gecko::CharacterBattleData)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(DefendTargetThisAction, Gecko::CharacterBattleData)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(DefendTargetsThisRound, Gecko::CharacterBattleData)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(DefendTargetsLastRound, Gecko::CharacterBattleData)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(MostRecentAttackTargets, Gecko::CharacterBattleData)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(MostRecentDefendTarget, Gecko::CharacterBattleData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(AllowedTargetAmount, Gecko::CharacterBattleData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(IsDead, Gecko::CharacterBattleData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(IsUnconscious, Gecko::CharacterBattleData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(EquippedWeaponLeftBluntRating, Gecko::CharacterBattleData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(EquippedWeaponLeftPierceRating, Gecko::CharacterBattleData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(EquippedWeaponLeftSlashRating, Gecko::CharacterBattleData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(EquippedWeaponRightBluntRating, Gecko::CharacterBattleData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(EquippedWeaponRightPierceRating, Gecko::CharacterBattleData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(EquippedWeaponRightSlashRating, Gecko::CharacterBattleData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(EquippedShieldLeftBluntRating, Gecko::CharacterBattleData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(EquippedShieldLeftPierceRating, Gecko::CharacterBattleData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(EquippedShieldLeftSlashRating, Gecko::CharacterBattleData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(EquippedShieldLeftMagicRating, Gecko::CharacterBattleData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(EquippedShieldRightBluntRating, Gecko::CharacterBattleData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(EquippedShieldRightPierceRating, Gecko::CharacterBattleData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(EquippedShieldRightSlashRating, Gecko::CharacterBattleData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(EquippedShieldRightMagicRating, Gecko::CharacterBattleData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(EquippedArmorBluntRating, Gecko::CharacterBattleData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(EquippedArmorPierceRating, Gecko::CharacterBattleData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(EquippedArmorSlashRating, Gecko::CharacterBattleData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(EquippedArmorMagicRating, Gecko::CharacterBattleData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(ChanceToCauseCriticalHit, Gecko::CharacterBattleData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(ChanceToBlockCriticalHit, Gecko::CharacterBattleData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(CriticalHitMultiplier, Gecko::CharacterBattleData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(ChanceToApplyMultipleAttacks, Gecko::CharacterBattleData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(AttacksMultiplier, Gecko::CharacterBattleData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(DamageTakenThisRound, Gecko::CharacterBattleData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(DamageTakenThisBattle, Gecko::CharacterBattleData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(DamageGivenThisRound, Gecko::CharacterBattleData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(DamageGivenThisBattle, Gecko::CharacterBattleData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(WeaponPrimaryDamageBonusValue, Gecko::CharacterBattleData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(WeaponPrimaryDamageBonusPercent, Gecko::CharacterBattleData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(WeaponSecondaryDamageBonusValue, Gecko::CharacterBattleData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(WeaponSecondaryDamageBonusPercent, Gecko::CharacterBattleData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(GeneralDamageBonusPercent, Gecko::CharacterBattleData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(GeneralDamageBonusValue, Gecko::CharacterBattleData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(DefensivePowerEffectsBonusValue, Gecko::CharacterBattleData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(DefensivePowerEffectsBonusPercent, Gecko::CharacterBattleData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(OffensivePowerEffectsBonusValue, Gecko::CharacterBattleData)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(OffensivePowerEffectsBonusPercent, Gecko::CharacterBattleData)
    ;
    PyBindVector<Gecko::CharacterBattleDataList>(m, "CharacterBattleDataList");
    WRAPPING_STANDALONE_METHOD_SIMPLE(ConvertCharacterBattleDataToJsonString, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(ConvertCharacterBattleDataListToJsonString, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetCharacterBattleDataFromJsonString, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetCharacterBattleDataListFromJsonString, Gecko);

    // CharacterProgressItem.h
    PyBindClass<Gecko::CharacterProgressItem>(m, "CharacterProgressItem")
        WRAPPING_ADD_CONSTRUCTOR_SIMPLE()
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(TreeIndex, Gecko::CharacterProgressItem)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(ItemSlot, Gecko::CharacterProgressItem)
    ;
    PyBindVector<Gecko::CharacterProgressItemList>(m, "CharacterProgressItemList");
    WRAPPING_STANDALONE_METHOD_SIMPLE(ConvertCharacterProgressItemToJsonString, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(ConvertCharacterProgressItemListToJsonString, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetCharacterProgressItemFromJsonString, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetCharacterProgressItemListFromJsonString, Gecko);
}
