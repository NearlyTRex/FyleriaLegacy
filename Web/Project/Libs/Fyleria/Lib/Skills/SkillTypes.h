// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#ifndef _GECKO_SKILL_TYPES_H_
#define _GECKO_SKILL_TYPES_H_

// Internal includes
#include "Utility/IndexedString.h"
#include "Utility/Macros.h"
#include "Utility/TypesEnum.h"

namespace Gecko
{

BETTER_ENUM(SkillTreeType, Int,
    None,
    Affinity,
    Alchemy,
    Crafting,
    Breakdown,
    Combat,
    Weapon
);

BETTER_ENUM(SkillWeaponBaseType, Int,
    None,
    Slash,
    Blunt,
    Pierce
);

BETTER_ENUM(SkillWeaponType, Int,
    None,

    // -- Slash --
    Slash,
    Sever,
    Slice,
    Slit,
    Cleave,
    Decapitate,
    Parry,
    Riposte,

    // -- Blunt --
    Bash,
    Smash,
    Impact,
    Crush,
    Break,
    Crack,
    Block,
    Rush,

    // -- Pierce --
    Pierce,
    Drill,
    Shoot,
    Impale,
    StealthStrike,
    CriticalShot,
    Dodge,
    Counter
);

BETTER_ENUM(SkillAlchemyType, Int,
    None,
    Healer,
    Alchemist,
    Energist,
    Chemist
);

BETTER_ENUM(SkillBreakdownType, Int,
    None,
    Hammerbane,
    Spellbane,
    Bowbane,
    Swordbane,
    Threadbare,
    StudRemover,
    Scalebane,
    Platebane,
    Goldbane,
    Shieldbane
);

BETTER_ENUM(SkillCombatType, Int,
    None,
    Barbarian,
    Mage,
    Rogue,
    Blademaster,
    Avatar,
    Ambidextrous,
    Focused,
    Stalwart
);

BETTER_ENUM(SkillCraftingType, Int,
    None,
    Hammersmith,
    Spellsmith,
    Bowsmith,
    Swordsmith,
    Weaver,
    Tanner,
    Scalesmith,
    Platesmith,
    Goldsmith,
    Shieldsmith
);

BETTER_ENUM(SkillAffinityType, Int,
    None,
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

MAKE_ENUM_GETSTRINGLIST_DECL(SkillTreeType);
MAKE_ENUM_GETSTRINGLIST_DECL(SkillWeaponBaseType);
MAKE_ENUM_GETSTRINGLIST_DECL(SkillWeaponType);
MAKE_ENUM_GETSTRINGLIST_DECL(SkillAlchemyType);
MAKE_ENUM_GETSTRINGLIST_DECL(SkillBreakdownType);
MAKE_ENUM_GETSTRINGLIST_DECL(SkillCombatType);
MAKE_ENUM_GETSTRINGLIST_DECL(SkillCraftingType);
MAKE_ENUM_GETSTRINGLIST_DECL(SkillAffinityType);

MAKE_ENUM_CONVERTERS_DECL(SkillTreeType);
MAKE_ENUM_CONVERTERS_DECL(SkillWeaponBaseType);
MAKE_ENUM_CONVERTERS_DECL(SkillWeaponType);
MAKE_ENUM_CONVERTERS_DECL(SkillAlchemyType);
MAKE_ENUM_CONVERTERS_DECL(SkillBreakdownType);
MAKE_ENUM_CONVERTERS_DECL(SkillCombatType);
MAKE_ENUM_CONVERTERS_DECL(SkillCraftingType);
MAKE_ENUM_CONVERTERS_DECL(SkillAffinityType);

};

#endif
