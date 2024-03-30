// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

#ifndef _GECKO_CHARACTER_TYPES_H_
#define _GECKO_CHARACTER_TYPES_H_

// Internal includes
#include "Utility/Constants.h"
#include "Utility/Macros.h"
#include "Utility/Enum.h"

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

BETTER_ENUM(CharacterActionStatType_Int, Int,
    None,
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

BETTER_ENUM(CharacterBasicStatType_String, Int,
    None,
    CharacterID,
    PartyID,
    FirstName,
    LastName,
    Gender,
    Hair,
    Eyes,
    Handedness,
    BaseRace,
    TransformedRace,
    PowerSet,
    WeaponSet
);

BETTER_ENUM(CharacterBasicStatType_Int, Int,
    None,
    Age
);

BETTER_ENUM(CharacterMediaStatType_String, Int,
    None,
    PortraitImage
);

BETTER_ENUM(CharacterProgressStatType_Int, Int,
    None,
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
    BluntAttack,
    BluntDefense,
    PierceAttack,
    PierceDefense,
    SlashAttack,
    SlashDefense,
    MagicAttack,
    MagicDefense,
    EnergyAttack,
    EnergyDefense
);

BETTER_ENUM(CharacterBattleStatType_String, Int,
    None,
    ActionSourceThisAction,
    MostRecentActionSource
);

BETTER_ENUM(CharacterBattleStatType_StringArray, Int,
    None,
    PreviousActionTypes,
    ActionTargetsThisAction,
    ActionTargetsThisRound,
    ActionSourcesThisRound,
    ActionTargetsLastRound,
    ActionSourcesLastRound,
    MostRecentActionTargets
);

BETTER_ENUM(CharacterBattleStatType_Bool, Int,
    None,
    TargetsMustBeIdentical,
    IsDead,
    IsUnconscious
);

BETTER_ENUM(CharacterBattleStatType_Int, Int,
    None,
    AttackCounter,
    DefendCounter,
    AllowedTargetAmount,
    DamageTakenThisRound,
    DamageTakenThisBattle,
    DamageGivenThisRound,
    DamageGivenThisBattle
);

BETTER_ENUM(CharacterBattleStatType_Float, Int,
    None,
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
    ChanceToCauseCriticalHit,
    ChanceToBlockCriticalHit,
    CriticalHitMultiplier,
    ChanceToApplyMultipleAttacks,
    AttacksMultiplier,
    WeaponPrimaryDamageBonusValue,
    WeaponPrimaryDamageBonusPercent,
    WeaponSecondaryDamageBonusValue,
    WeaponSecondaryDamageBonusPercent,
    GeneralDamageBonusPercent,
    GeneralDamageBonusValue,
    DefensivePowerEffectsBonusValue,
    DefensivePowerEffectsBonusPercent,
    OffensivePowerEffectsBonusValue,
    OffensivePowerEffectsBonusPercent
);

BETTER_ENUM(CharacterSkillStatType_Short, Int,
    None,
    Healer,
    Alchemist,
    Energist,
    Chemist,
    Hammerbane,
    Spellbane,
    Bowbane,
    Swordbane,
    Threadbare,
    StudRemover,
    Scalebane,
    Platebane,
    Goldbane,
    Shieldbane,
    Barbarian,
    Mage,
    Rogue,
    Blademaster,
    Avatar,
    Ambidextrous,
    Focused,
    Stalwart,
    Hammersmith,
    Spellsmith,
    Bowsmith,
    Swordsmith,
    Weaver,
    Tanner,
    Scalesmith,
    Platesmith,
    Goldsmith,
    Shieldsmith,
    Holy,
    Fire,
    Ice,
    Shock,
    Dark,
    Light,
    Force,
    Mind,
    Earth,
    Blood,
    Flesh,
    Wind
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
    ActionTargetsThisAction,
    ActionSourceThisAction,
    ActionTargetsThisRound,
    ActionSourcesThisRound,
    ActionTargetsLastRound,
    ActionSourcesLastRound,
    MostRecentActionTargets,
    MostRecentActionSource,
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

BETTER_ENUM(CharacterResolvedTargetType, Int,
    None,
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

String ConvertCharacterEquipmentTypeToCharacterWeaponSetType(const String& sCharacterEquipmentType);
String ConvertCharacterTargetTypeToCharacterPartyType(const String& sCharacterTargetType);
String ConvertItemTypeToCharacterActionType(const String& sItemType);
StringArray ConvertItemTypeToCharacterEquipTypes(const String& sItemType);
String ConvertSkillWeaponBaseTypeToCharacterActionType(const String& sSkillWeaponBaseType);
String ConvertSkillWeaponTypeToCharacterActionType(const String& sSkillWeaponType);
String ConvertSkillWeaponTypeToCharacterActionStatType(const String& sSkillWeaponType);

};

#endif
