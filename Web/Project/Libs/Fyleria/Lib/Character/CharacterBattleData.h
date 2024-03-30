// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#ifndef _GECKO_CHARACTER_BATTLE_DATA_H_
#define _GECKO_CHARACTER_BATTLE_DATA_H_

#include "Character/CharacterProgressData.h"
#include "Utility/IndexedString.h"
#include "Utility/Macros.h"
#include "Utility/TypesEnum.h"
#include "Utility/TypesJson.h"

namespace Gecko
{

// POD class for character battle-only data
class CharacterBattleData
{
public:

    // Constructors
    CharacterBattleData();
    CharacterBattleData(const Json& jsonData);

    // Clear all data
    void Clear();

    // Apply status
    void ApplyNewStatus(const CharacterProgressData& progressData);

    // Apply damage
    void ApplyGivenDamage(Int iDamage);
    void ApplyTakenDamage(Int iDamage);

    // Advance round
    void AdvanceRound(CharacterProgressData& progressData);

    // Finish battle
    void FinishBattle(CharacterProgressData& progressData);

    // Can regenerate from stat
    Bool CanRegenerateFromStat(const IndexedString& sRegenStat) const;

    // Update equipment ratings
    void UpdateEquipmentRatings(const IndexedString& sWeaponSet, const CharacterProgressItemList& vEquippedItems, const CharacterProgressData& progressData);

    // Weapon ratings based on handedness
    Bool GetPrimaryWeaponRatings(const IndexedString& sHandedness,
        Float& fPrimaryBlunt,
        Float& fPrimaryPierce,
        Float& fPrimarySlash) const;
    Bool GetSecondaryWeaponRatings(const IndexedString& sHandedness,
        Float& fSecondaryBlunt,
        Float& fSecondaryPierce,
        Float& fSecondarySlash) const;

    // Shield ratings based on handedness
    Bool GetPrimaryShieldRatings(const IndexedString& sHandedness,
        Float& fPrimaryBlunt,
        Float& fPrimaryPierce,
        Float& fPrimarySlash) const;
    Bool GetSecondaryShieldRatings(const IndexedString& sHandedness,
        Float& fSecondaryBlunt,
        Float& fSecondaryPierce,
        Float& fSecondarySlash) const;

    // Stat values
    Bool GetBoolStatValue(const IndexedString& sStat, Bool& bValue) const;
    Bool GetIntStatValue(const IndexedString& sStat, Int& iValue) const;
    Bool GetFloatStatValue(const IndexedString& sStat, Float& fValue) const;
    Bool GetStringStatValue(const IndexedString& sStat, IndexedString& sValue) const;
    Bool GetStringListStatValue(const IndexedString& sStat, IndexedStringList& vValues) const;
    Bool SetBoolStatValue(const IndexedString& sStat, const Bool& bValue);
    Bool SetIntStatValue(const IndexedString& sStat, const Int& iValue);
    Bool SetFloatStatValue(const IndexedString& sStat, const Float& fValue);
    Bool SetStringStatValue(const IndexedString& sStat, const IndexedString& sValue);
    Bool SetStringListStatValue(const IndexedString& sStat, const IndexedStringList& vValues);

    // Stat names
    static STDUnorderedSet<String>& GetBoolStatNames();
    static STDUnorderedSet<String>& GetUByteStatNames();
    static STDUnorderedSet<String>& GetIntStatNames();
    static STDUnorderedSet<String>& GetFloatStatNames();
    static STDUnorderedSet<String>& GetIndexedStringStatNames();
    static STDUnorderedSet<String>& GetIndexedStringListStatNames();
    static void InitAllStatNames();

    // -- Target Characters --
    MAKE_RAW_OBJECT_TYPE_ACCESSORS_WITH_STATIC(AttackTargetsThisAction, IndexedStringList);
    MAKE_RAW_OBJECT_TYPE_ACCESSORS_WITH_STATIC(AttackTargetsThisRound, IndexedStringList);
    MAKE_RAW_OBJECT_TYPE_ACCESSORS_WITH_STATIC(AttackTargetsLastRound, IndexedStringList);
    MAKE_RAW_OBJECT_TYPE_ACCESSORS_WITH_STATIC(DefendTargetThisAction, IndexedString);
    MAKE_RAW_OBJECT_TYPE_ACCESSORS_WITH_STATIC(DefendTargetsThisRound, IndexedStringList);
    MAKE_RAW_OBJECT_TYPE_ACCESSORS_WITH_STATIC(DefendTargetsLastRound, IndexedStringList);
    MAKE_RAW_OBJECT_TYPE_ACCESSORS_WITH_STATIC(MostRecentAttackTargets, IndexedStringList);
    MAKE_RAW_OBJECT_TYPE_ACCESSORS_WITH_STATIC(MostRecentDefendTarget, IndexedString);

    // -- Target Amounts --
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(AllowedTargetAmount, UByte);

    // -- Status --
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(IsDead, Bool);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(IsUnconscious, Bool);

    // -- Equipment Ratings --
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(EquippedWeaponLeftBluntRating, Float);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(EquippedWeaponLeftPierceRating, Float);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(EquippedWeaponLeftSlashRating, Float);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(EquippedWeaponRightBluntRating, Float);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(EquippedWeaponRightPierceRating, Float);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(EquippedWeaponRightSlashRating, Float);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(EquippedShieldLeftBluntRating, Float);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(EquippedShieldLeftPierceRating, Float);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(EquippedShieldLeftSlashRating, Float);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(EquippedShieldLeftMagicRating, Float);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(EquippedShieldRightBluntRating, Float);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(EquippedShieldRightPierceRating, Float);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(EquippedShieldRightSlashRating, Float);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(EquippedShieldRightMagicRating, Float);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(EquippedArmorBluntRating, Float);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(EquippedArmorPierceRating, Float);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(EquippedArmorSlashRating, Float);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(EquippedArmorMagicRating, Float);

    // -- Critical Hits --
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(ChanceToCauseCriticalHit, Float);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(ChanceToBlockCriticalHit, Float);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(CriticalHitMultiplier, Float);

    // -- Multiple Attacks --
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(ChanceToApplyMultipleAttacks, Float);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(AttacksMultiplier, Float);

    // -- Damage Counters --
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(DamageTakenThisRound, Int);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(DamageTakenThisBattle, Int);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(DamageGivenThisRound, Int);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(DamageGivenThisBattle, Int);

    // -- Damage Bonus --
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(WeaponPrimaryDamageBonusValue, Float);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(WeaponPrimaryDamageBonusPercent, Float);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(WeaponSecondaryDamageBonusValue, Float);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(WeaponSecondaryDamageBonusPercent, Float);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(GeneralDamageBonusValue, Float);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(GeneralDamageBonusPercent, Float);

    // -- Effects Bonus --
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(DefensivePowerEffectsBonusValue, Float);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(DefensivePowerEffectsBonusPercent, Float);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(OffensivePowerEffectsBonusValue, Float);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(OffensivePowerEffectsBonusPercent, Float);

    // Comparisons
    Bool operator==(const CharacterBattleData& other) const;
    Bool operator!=(const CharacterBattleData& other) const;
};

// Typedef
MAKE_TYPE_TYPEDEFS(CharacterBattleData);

// JSON Converters
void to_json(Json& jsonData, const CharacterBattleData& obj);
void from_json(const Json& jsonData, CharacterBattleData& obj);
MAKE_JSON_GENERIC_TYPE_CONVERTERS_DECL(CharacterBattleData, CharacterBattleData);

};

#endif
