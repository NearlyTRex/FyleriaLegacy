// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#ifndef _GECKO_CHARACTER_TYPES_H_
#define _GECKO_CHARACTER_TYPES_H_

// Internal includes
#include "Utility/IndexedString.h"
#include "Utility/Macros.h"
#include "Utility/TypesEnum.h"

namespace Gecko
{

BETTER_ENUM(CharacterTreeIndexType, Int,
    None,
    Skill,
    Item
);

BETTER_ENUM(CharacterSegmentType, Int,
    None,
    Base,
    Passive,
    Active
);

BETTER_ENUM(CharacterProgressStatType, Int,
    None,

    // -- Basics --
    FirstName,
    LastName,
    Age,
    Gender,
    Hair,
    Eyes,
    Handedness,
    BaseRace,
    TransformedRace,
    PowerSet,

    // -- Meters --
    HealthPointsCurrent,
    MagicPointsCurrent,
    EnergyPointsCurrent,
    HealthPointsMax,
    MagicPointsMax,
    EnergyPointsMax,
    HealthRegen,
    MagicRegen,
    EnergyRegen,
    HealthCostDelta,
    MagicCostDelta,
    EnergyCostDelta,
    Speed,

    // -- Gemstones --
    AmberValueDelta,
    RubyValueDelta,
    DiamondValueDelta,
    CitrineValueDelta,
    OnyxValueDelta,
    QuartzValueDelta,
    SapphireValueDelta,
    AmethystValueDelta,
    EmeraldValueDelta,
    GarnetValueDelta,
    IvoryValueDelta,
    OpalValueDelta,

    // -- Attack and Defense Scoring --
    BluntAttack,
    BluntDefense,
    PierceAttack,
    PierceDefense,
    SlashAttack,
    SlashDefense,
    MagicAttack,
    MagicDefense,
    EnergyAttack,
    EnergyDefense,

    // -- Action Points --
    SlashPoints,
    SeverPoints,
    SlicePoints,
    SlitPoints,
    CleavePoints,
    DecapitatePoints,
    ParryPoints,
    RipostePoints,
    BashPoints,
    SmashPoints,
    ImpactPoints,
    CrushPoints,
    BreakPoints,
    CrackPoints,
    BlockPoints,
    RushPoints,
    PiercePoints,
    DrillPoints,
    ShootPoints,
    ImpalePoints,
    StealthStrikePoints,
    CriticalShotPoints,
    DodgePoints,
    CounterPoints
);

BETTER_ENUM(CharacterBattleStatType, Int,
    None,

    // -- Target Characters --
    AttackTargetsThisAction,
    DefendTargetThisAction,
    AttackTargetsThisRound,
    DefendTargetsThisRound,
    AttackTargetsLastRound,
    DefendTargetsLastRound,
    MostRecentAttackTargets,
    MostRecentDefendTarget,

    // -- Target Amounts --
    AllowedTargetAmount,

    // -- Status --
    IsDead,
    IsUnconscious,

    // -- Equipment Ratings --
    EquippedWeaponLeftBluntRating,
    EquippedWeaponLeftPierceRating,
    EquippedWeaponLeftSlashRating,
    EquippedWeaponRightBluntRating,
    EquippedWeaponRightPierceRating,
    EquippedWeaponRightSlashRating,
    EquippedShieldLeftBluntRating,
    EquippedShieldLeftPierceRating,
    EquippedShieldLeftSlashRating,
    EquippedShieldLeftMagicRating,
    EquippedShieldRightBluntRating,
    EquippedShieldRightPierceRating,
    EquippedShieldRightSlashRating,
    EquippedShieldRightMagicRating,
    EquippedArmorBluntRating,
    EquippedArmorPierceRating,
    EquippedArmorSlashRating,
    EquippedArmorMagicRating,

    // -- Critical Hits --
    ChanceToCauseCriticalHit,
    ChanceToBlockCriticalHit,
    CriticalHitMultiplier,

    // -- Multiple Attacks --
    ChanceToApplyMultipleAttacks,
    AttacksMultiplier,

    // -- Damage Counters --
    DamageTakenThisRound,
    DamageTakenThisBattle,
    DamageGivenThisRound,
    DamageGivenThisBattle,

    // -- Damage Bonus --
    WeaponPrimaryDamageBonusValue,
    WeaponPrimaryDamageBonusPercent,
    WeaponSecondaryDamageBonusValue,
    WeaponSecondaryDamageBonusPercent,
    GeneralDamageBonusPercent,
    GeneralDamageBonusValue,

    // -- Effects Bonus --
    DefensivePowerEffectsBonusValue,
    DefensivePowerEffectsBonusPercent,
    OffensivePowerEffectsBonusValue,
    OffensivePowerEffectsBonusPercent
);

BETTER_ENUM(CharacterStatusType, Int,
    None,
    Dead,
    Unconscious
);

BETTER_ENUM(CharacterBaseRaceType, Int,
    None,
    Human,
    Dwarf,
    Drow,
    Elf,
    Halfling,
    Caetian,
    Geikan,
    Faerie,
    Goblin
);

BETTER_ENUM(CharacterTransformedRaceType, Int,
    None,
    Untransformed,
    Skeleton,
    Zombie,
    Vampire,
    Ghost,
    Wraith,
    Revenant,
    Ghoul
);

BETTER_ENUM(CharacterPowerSetType, Int,
    None,
    Oracle,
    Reaper,
    Dragon,
    Trickster,
    Sidhe,
    Vampire
);

BETTER_ENUM(CharacterWeaponSetType, Int,
    None,
    WeaponSet1,
    WeaponSet2
);

BETTER_ENUM(CharacterGenderType, Int,
    None,
    Male,
    Female
);

BETTER_ENUM(CharacterHairType, Int,
    None,
    Hair1,
    Hair2
);

BETTER_ENUM(CharacterEyeType, Int,
    None,
    Eyes1,
    Eyes2
);

BETTER_ENUM(CharacterHandednessType, Int,
    None,
    LeftHanded,
    RightHanded
);

BETTER_ENUM(CharacterHandType, Int,
    None,
    Primary,
    Secondary
);

BETTER_ENUM(CharacterEquipmentType, Int,
    None,
    Weapon1Left,
    Weapon1Right,
    Weapon2Left,
    Weapon2Right,
    LeftFingers,
    RightFingers,
    Neck,
    Head,
    Hands,
    Feet,
    Legs,
    Chest
);

BETTER_ENUM(CharacterTargetType, Int,
    None,
    Self,
    AttackTargetsThisAction,
    DefendTargetThisAction,
    AttackTargetsThisRound,
    DefendTargetsThisRound,
    AttackTargetsLastRound,
    DefendTargetsLastRound,
    MostRecentAttackTargets,
    MostRecentDefendTarget,
    AllEnemies,
    AllAllies,
    Enemy1,
    Enemy2,
    Enemy3,
    Enemy4,
    Enemy5,
    Enemy6,
    Ally1,
    Ally2,
    Ally3,
    Ally4,
    Ally5,
    Ally6
);

BETTER_ENUM(CharacterPartyType, Int,
    None,
    Ally,
    Enemy
);

BETTER_ENUM(CharacterActionType, Int,
    None,
    ItemPotionEnergy,
    ItemPotionHeal,
    ItemPotionMagic,
    ItemPotionSpeed,
    WeaponBasePierce,
    WeaponBaseBlunt,
    WeaponBaseSlash,
    WeaponSlash,
    WeaponSever,
    WeaponSlice,
    WeaponSlit,
    WeaponCleave,
    WeaponDecapitate,
    WeaponParry,
    WeaponRiposte,
    WeaponBash,
    WeaponSmash,
    WeaponImpact,
    WeaponCrush,
    WeaponBreak,
    WeaponCrack,
    WeaponBlock,
    WeaponRush,
    WeaponPierce,
    WeaponDrill,
    WeaponShoot,
    WeaponImpale,
    WeaponStealthStrike,
    WeaponCriticalShot,
    WeaponDodge,
    WeaponCounter,
    SpellHoly,
    SpellFire,
    SpellIce,
    SpellShock,
    SpellDark,
    SpellLight,
    SpellForce,
    SpellMind,
    SpellEarth,
    SpellBlood,
    SpellFlesh,
    SpellWind,
    PowerHoly,
    PowerFire,
    PowerIce,
    PowerShock,
    PowerDark,
    PowerLight,
    PowerForce,
    PowerMind,
    PowerEarth,
    PowerBlood,
    PowerFlesh,
    PowerWind
);

BETTER_ENUM(CharacterActionRunType, Int,
    None,
    Battle,
    Field
);

IndexedString ConvertCharacterEquipmentTypeToCharacterWeaponSetType(const IndexedString& sCharacterEquipmentType);
IndexedString ConvertCharacterTargetTypeToCharacterPartyType(const IndexedString& sCharacterTargetType);
IndexedString ConvertItemTypeToCharacterActionType(const IndexedString& sItemType);
IndexedStringList ConvertItemTypeToCharacterEquipTypes(const IndexedString& sItemType);
IndexedString ConvertSkillWeaponBaseTypeToCharacterActionType(const IndexedString& sSkillWeaponBaseType);
IndexedString ConvertSkillWeaponTypeToCharacterActionType(const IndexedString& sSkillWeaponType);

MAKE_ENUM_GETSTRINGLIST_DECL(CharacterTreeIndexType);
MAKE_ENUM_GETSTRINGLIST_DECL(CharacterSegmentType);
MAKE_ENUM_GETSTRINGLIST_DECL(CharacterProgressStatType);
MAKE_ENUM_GETSTRINGLIST_DECL(CharacterBattleStatType);
MAKE_ENUM_GETSTRINGLIST_DECL(CharacterStatusType);
MAKE_ENUM_GETSTRINGLIST_DECL(CharacterBaseRaceType);
MAKE_ENUM_GETSTRINGLIST_DECL(CharacterTransformedRaceType);
MAKE_ENUM_GETSTRINGLIST_DECL(CharacterPowerSetType);
MAKE_ENUM_GETSTRINGLIST_DECL(CharacterWeaponSetType);
MAKE_ENUM_GETSTRINGLIST_DECL(CharacterGenderType);
MAKE_ENUM_GETSTRINGLIST_DECL(CharacterHairType);
MAKE_ENUM_GETSTRINGLIST_DECL(CharacterEyeType);
MAKE_ENUM_GETSTRINGLIST_DECL(CharacterHandednessType);
MAKE_ENUM_GETSTRINGLIST_DECL(CharacterHandType);
MAKE_ENUM_GETSTRINGLIST_DECL(CharacterEquipmentType);
MAKE_ENUM_GETSTRINGLIST_DECL(CharacterTargetType);
MAKE_ENUM_GETSTRINGLIST_DECL(CharacterPartyType);
MAKE_ENUM_GETSTRINGLIST_DECL(CharacterActionType);
MAKE_ENUM_GETSTRINGLIST_DECL(CharacterActionRunType);

MAKE_ENUM_CONVERTERS_DECL(CharacterTreeIndexType);
MAKE_ENUM_CONVERTERS_DECL(CharacterSegmentType);
MAKE_ENUM_CONVERTERS_DECL(CharacterProgressStatType);
MAKE_ENUM_CONVERTERS_DECL(CharacterBattleStatType);
MAKE_ENUM_CONVERTERS_DECL(CharacterStatusType);
MAKE_ENUM_CONVERTERS_DECL(CharacterBaseRaceType);
MAKE_ENUM_CONVERTERS_DECL(CharacterTransformedRaceType);
MAKE_ENUM_CONVERTERS_DECL(CharacterPowerSetType);
MAKE_ENUM_CONVERTERS_DECL(CharacterWeaponSetType);
MAKE_ENUM_CONVERTERS_DECL(CharacterGenderType);
MAKE_ENUM_CONVERTERS_DECL(CharacterHairType);
MAKE_ENUM_CONVERTERS_DECL(CharacterEyeType);
MAKE_ENUM_CONVERTERS_DECL(CharacterHandednessType);
MAKE_ENUM_CONVERTERS_DECL(CharacterHandType);
MAKE_ENUM_CONVERTERS_DECL(CharacterEquipmentType);
MAKE_ENUM_CONVERTERS_DECL(CharacterTargetType);
MAKE_ENUM_CONVERTERS_DECL(CharacterPartyType);
MAKE_ENUM_CONVERTERS_DECL(CharacterActionType);
MAKE_ENUM_CONVERTERS_DECL(CharacterActionRunType);

};

#endif
