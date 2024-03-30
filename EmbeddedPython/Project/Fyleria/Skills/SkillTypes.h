// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

#ifndef _GECKO_SKILL_TYPES_H_
#define _GECKO_SKILL_TYPES_H_

// Internal includes
#include "Utility/Assert.h"
#include "Utility/Macros.h"
#include "Utility/Enum.h"

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

};

#endif
