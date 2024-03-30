// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

#ifndef _GECKO_CHARACTER_BATTLE_DATA_H_
#define _GECKO_CHARACTER_BATTLE_DATA_H_

// Internal includes
#include "Stats/StatTypeHolder.h"

namespace Gecko
{

// Character battle data
class CharacterBattleData : public StatTypeHolder
{
public:

    // Constructors
    CharacterBattleData();
    CharacterBattleData(const Json& jsonData);

    // Destructor
    virtual ~CharacterBattleData();

    // Apply status
    void ApplyNewStatus(const String& sCharacterID, const String& sProgressSegment);

    // Apply damage
    void ApplyGivenDamage(Int iDamage);
    void ApplyTakenDamage(Int iDamage);

    // Advance round
    void AdvanceRound(const String& sCharacterID, const String& sProgressSegment);

    // Finish battle
    void FinishBattle(const String& sCharacterID, const String& sProgressSegment);

    // Can regenerate from stat
    Bool CanRegenerateFromStat(const String& sRegenStat) const;

    // Update equipment ratings
    void UpdateEquipmentRatings(const String& sCharacterID, const String& sProgressSegment);

    // Resolve target placeholders
    StringArray ResolveTargetPlaceholder(const String& sSelfTargetType,
        const String& sPlaceholderTargetType) const;

    // Weapon ratings based on handedness
    Bool GetPrimaryWeaponRatings(const String& sHandedness,
        Float& fPrimaryBlunt,
        Float& fPrimaryPierce,
        Float& fPrimarySlash) const;
    Bool GetSecondaryWeaponRatings(const String& sHandedness,
        Float& fSecondaryBlunt,
        Float& fSecondaryPierce,
        Float& fSecondarySlash) const;

    // Shield ratings based on handedness
    Bool GetPrimaryShieldRatings(const String& sHandedness,
        Float& fPrimaryBlunt,
        Float& fPrimaryPierce,
        Float& fPrimarySlash) const;
    Bool GetSecondaryShieldRatings(const String& sHandedness,
        Float& fSecondaryBlunt,
        Float& fSecondaryPierce,
        Float& fSecondarySlash) const;

    // Stat names
    static void InitAllStatNames();

    // String stats
    MAKE_STAT_TYPE_ACCESSORS(ActionSourceThisAction, String);
    MAKE_STAT_TYPE_ACCESSORS(MostRecentActionSource, String);

    // StringArray stats
    MAKE_STAT_TYPE_ACCESSORS(PreviousActionTypes, StringArray);
    MAKE_STAT_TYPE_ACCESSORS(ActionTargetsThisAction, StringArray);
    MAKE_STAT_TYPE_ACCESSORS(ActionTargetsThisRound, StringArray);
    MAKE_STAT_TYPE_ACCESSORS(ActionTargetsLastRound, StringArray);
    MAKE_STAT_TYPE_ACCESSORS(ActionSourcesThisRound, StringArray);
    MAKE_STAT_TYPE_ACCESSORS(ActionSourcesLastRound, StringArray);
    MAKE_STAT_TYPE_ACCESSORS(MostRecentActionTargets, StringArray);

    // Bool stats
    MAKE_STAT_TYPE_ACCESSORS(TargetsMustBeIdentical, Bool);
    MAKE_STAT_TYPE_ACCESSORS(IsDead, Bool);
    MAKE_STAT_TYPE_ACCESSORS(IsUnconscious, Bool);

    // Int stats
    MAKE_STAT_TYPE_ACCESSORS(AttackCounter, Int);
    MAKE_STAT_TYPE_ACCESSORS(DefendCounter, Int);
    MAKE_STAT_TYPE_ACCESSORS(AllowedTargetAmount, Int);
    MAKE_STAT_TYPE_ACCESSORS(DamageTakenThisRound, Int);
    MAKE_STAT_TYPE_ACCESSORS(DamageTakenThisBattle, Int);
    MAKE_STAT_TYPE_ACCESSORS(DamageGivenThisRound, Int);
    MAKE_STAT_TYPE_ACCESSORS(DamageGivenThisBattle, Int);

    // Float stats
    MAKE_STAT_TYPE_ACCESSORS(EquippedWeaponLeftBluntRating, Float);
    MAKE_STAT_TYPE_ACCESSORS(EquippedWeaponLeftPierceRating, Float);
    MAKE_STAT_TYPE_ACCESSORS(EquippedWeaponLeftSlashRating, Float);
    MAKE_STAT_TYPE_ACCESSORS(EquippedWeaponRightBluntRating, Float);
    MAKE_STAT_TYPE_ACCESSORS(EquippedWeaponRightPierceRating, Float);
    MAKE_STAT_TYPE_ACCESSORS(EquippedWeaponRightSlashRating, Float);
    MAKE_STAT_TYPE_ACCESSORS(EquippedShieldLeftBluntRating, Float);
    MAKE_STAT_TYPE_ACCESSORS(EquippedShieldLeftPierceRating, Float);
    MAKE_STAT_TYPE_ACCESSORS(EquippedShieldLeftSlashRating, Float);
    MAKE_STAT_TYPE_ACCESSORS(EquippedShieldLeftMagicRating, Float);
    MAKE_STAT_TYPE_ACCESSORS(EquippedShieldRightBluntRating, Float);
    MAKE_STAT_TYPE_ACCESSORS(EquippedShieldRightPierceRating, Float);
    MAKE_STAT_TYPE_ACCESSORS(EquippedShieldRightSlashRating, Float);
    MAKE_STAT_TYPE_ACCESSORS(EquippedShieldRightMagicRating, Float);
    MAKE_STAT_TYPE_ACCESSORS(EquippedArmorBluntRating, Float);
    MAKE_STAT_TYPE_ACCESSORS(EquippedArmorPierceRating, Float);
    MAKE_STAT_TYPE_ACCESSORS(EquippedArmorSlashRating, Float);
    MAKE_STAT_TYPE_ACCESSORS(EquippedArmorMagicRating, Float);
    MAKE_STAT_TYPE_ACCESSORS(ChanceToCauseCriticalHit, Float);
    MAKE_STAT_TYPE_ACCESSORS(ChanceToBlockCriticalHit, Float);
    MAKE_STAT_TYPE_ACCESSORS(CriticalHitMultiplier, Float);
    MAKE_STAT_TYPE_ACCESSORS(ChanceToApplyMultipleAttacks, Float);
    MAKE_STAT_TYPE_ACCESSORS(AttacksMultiplier, Float);
    MAKE_STAT_TYPE_ACCESSORS(WeaponPrimaryDamageBonusValue, Float);
    MAKE_STAT_TYPE_ACCESSORS(WeaponPrimaryDamageBonusPercent, Float);
    MAKE_STAT_TYPE_ACCESSORS(WeaponSecondaryDamageBonusValue, Float);
    MAKE_STAT_TYPE_ACCESSORS(WeaponSecondaryDamageBonusPercent, Float);
    MAKE_STAT_TYPE_ACCESSORS(GeneralDamageBonusValue, Float);
    MAKE_STAT_TYPE_ACCESSORS(GeneralDamageBonusPercent, Float);
    MAKE_STAT_TYPE_ACCESSORS(DefensivePowerEffectsBonusValue, Float);
    MAKE_STAT_TYPE_ACCESSORS(DefensivePowerEffectsBonusPercent, Float);
    MAKE_STAT_TYPE_ACCESSORS(OffensivePowerEffectsBonusValue, Float);
    MAKE_STAT_TYPE_ACCESSORS(OffensivePowerEffectsBonusPercent, Float);

    // Comparisons
    Bool operator==(const CharacterBattleData& other) const;
    Bool operator!=(const CharacterBattleData& other) const;
};

// Typedef
MAKE_COMMON_TYPEDEFS(CharacterBattleData);

// JSON Converters
void to_json(Json& jsonData, const CharacterBattleData& obj);
void from_json(const Json& jsonData, CharacterBattleData& obj);

};

#endif
