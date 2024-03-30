// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

#ifndef _GECKO_CHARACTER_SKILL_DATA_H_
#define _GECKO_CHARACTER_SKILL_DATA_H_

// Internal includes
#include "Stats/StatTypeHolder.h"

namespace Gecko
{

class CharacterSkillData : public StatTypeHolder
{
public:

    // Constructors
    CharacterSkillData();
    CharacterSkillData(const Json& jsonData);

    // Destructor
    virtual ~CharacterSkillData();

    // Get skill current value
    Short GetSkillCurrentValue(const String& sSkillType) const;

    // Get skill rank value
    Short GetSkillRankValue(const String& sSkillType) const;

    // Update skill value
    void UpdateSkillValue(const String& sSkillType, Short iDelta);

    // Stat names
    static void InitAllStatNames();

    // Short stats
    MAKE_STAT_TYPE_ACCESSORS(Barbarian, Short);
    MAKE_STAT_TYPE_ACCESSORS(Mage, Short);
    MAKE_STAT_TYPE_ACCESSORS(Rogue, Short);
    MAKE_STAT_TYPE_ACCESSORS(Blademaster, Short);
    MAKE_STAT_TYPE_ACCESSORS(Avatar, Short);
    MAKE_STAT_TYPE_ACCESSORS(Ambidextrous, Short);
    MAKE_STAT_TYPE_ACCESSORS(Focused, Short);
    MAKE_STAT_TYPE_ACCESSORS(Stalwart, Short);
    MAKE_STAT_TYPE_ACCESSORS(Slash, Short);
    MAKE_STAT_TYPE_ACCESSORS(Sever, Short);
    MAKE_STAT_TYPE_ACCESSORS(Slice, Short);
    MAKE_STAT_TYPE_ACCESSORS(Slit, Short);
    MAKE_STAT_TYPE_ACCESSORS(Cleave, Short);
    MAKE_STAT_TYPE_ACCESSORS(Decapitate, Short);
    MAKE_STAT_TYPE_ACCESSORS(Parry, Short);
    MAKE_STAT_TYPE_ACCESSORS(Riposte, Short);
    MAKE_STAT_TYPE_ACCESSORS(Bash, Short);
    MAKE_STAT_TYPE_ACCESSORS(Smash, Short);
    MAKE_STAT_TYPE_ACCESSORS(Crush, Short);
    MAKE_STAT_TYPE_ACCESSORS(Impact, Short);
    MAKE_STAT_TYPE_ACCESSORS(Break, Short);
    MAKE_STAT_TYPE_ACCESSORS(Crack, Short);
    MAKE_STAT_TYPE_ACCESSORS(Block, Short);
    MAKE_STAT_TYPE_ACCESSORS(Rush, Short);
    MAKE_STAT_TYPE_ACCESSORS(Pierce, Short);
    MAKE_STAT_TYPE_ACCESSORS(Drill, Short);
    MAKE_STAT_TYPE_ACCESSORS(Shoot, Short);
    MAKE_STAT_TYPE_ACCESSORS(Impale, Short);
    MAKE_STAT_TYPE_ACCESSORS(StealthStrike, Short);
    MAKE_STAT_TYPE_ACCESSORS(CriticalShot, Short);
    MAKE_STAT_TYPE_ACCESSORS(Dodge, Short);
    MAKE_STAT_TYPE_ACCESSORS(Counter, Short);
    MAKE_STAT_TYPE_ACCESSORS(Healer, Short);
    MAKE_STAT_TYPE_ACCESSORS(Alchemist, Short);
    MAKE_STAT_TYPE_ACCESSORS(Energist, Short);
    MAKE_STAT_TYPE_ACCESSORS(Chemist, Short);
    MAKE_STAT_TYPE_ACCESSORS(Hammersmith, Short);
    MAKE_STAT_TYPE_ACCESSORS(Spellsmith, Short);
    MAKE_STAT_TYPE_ACCESSORS(Bowsmith, Short);
    MAKE_STAT_TYPE_ACCESSORS(Swordsmith, Short);
    MAKE_STAT_TYPE_ACCESSORS(Weaver, Short);
    MAKE_STAT_TYPE_ACCESSORS(Tanner, Short);
    MAKE_STAT_TYPE_ACCESSORS(Scalesmith, Short);
    MAKE_STAT_TYPE_ACCESSORS(Platesmith, Short);
    MAKE_STAT_TYPE_ACCESSORS(Goldsmith, Short);
    MAKE_STAT_TYPE_ACCESSORS(Shieldsmith, Short);
    MAKE_STAT_TYPE_ACCESSORS(Hammerbane, Short);
    MAKE_STAT_TYPE_ACCESSORS(Spellbane, Short);
    MAKE_STAT_TYPE_ACCESSORS(Bowbane, Short);
    MAKE_STAT_TYPE_ACCESSORS(Swordbane, Short);
    MAKE_STAT_TYPE_ACCESSORS(Threadbare, Short);
    MAKE_STAT_TYPE_ACCESSORS(StudRemover, Short);
    MAKE_STAT_TYPE_ACCESSORS(Scalebane, Short);
    MAKE_STAT_TYPE_ACCESSORS(Platebane, Short);
    MAKE_STAT_TYPE_ACCESSORS(Goldbane, Short);
    MAKE_STAT_TYPE_ACCESSORS(Shieldbane, Short);
    MAKE_STAT_TYPE_ACCESSORS(Holy, Short);
    MAKE_STAT_TYPE_ACCESSORS(Fire, Short);
    MAKE_STAT_TYPE_ACCESSORS(Ice, Short);
    MAKE_STAT_TYPE_ACCESSORS(Shock, Short);
    MAKE_STAT_TYPE_ACCESSORS(Dark, Short);
    MAKE_STAT_TYPE_ACCESSORS(Light, Short);
    MAKE_STAT_TYPE_ACCESSORS(Force, Short);
    MAKE_STAT_TYPE_ACCESSORS(Mind, Short);
    MAKE_STAT_TYPE_ACCESSORS(Earth, Short);
    MAKE_STAT_TYPE_ACCESSORS(Blood, Short);
    MAKE_STAT_TYPE_ACCESSORS(Flesh, Short);
    MAKE_STAT_TYPE_ACCESSORS(Wind, Short);

    // Comparisons
    Bool operator==(const CharacterSkillData& other) const;
    Bool operator!=(const CharacterSkillData& other) const;
};

// Typedef
MAKE_COMMON_TYPEDEFS(CharacterSkillData);

// JSON Converters
void to_json(Json& jsonData, const CharacterSkillData& obj);
void from_json(const Json& jsonData, CharacterSkillData& obj);

};

#endif
