// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

#ifndef _GECKO_CHARACTER_PROGRESS_DATA_H_
#define _GECKO_CHARACTER_PROGRESS_DATA_H_

// Internal includes
#include "Stats/StatTypeHolder.h"

namespace Gecko
{

// Character progress data
class CharacterProgressData : public StatTypeHolder
{
public:

    // Constructors
    CharacterProgressData();
    CharacterProgressData(const Json& jsonData);

    // Destructor
    virtual ~CharacterProgressData();

    // Apply damage
    void ApplyTakenDamage(Int iDamage);

    // Apply regeneration
    void ApplyRegeneration(Bool bCanRegenHP, Bool bCanRegenMP, Bool bCanRegenEP);

    // Stat names
    static void InitAllStatNames();

    // Int stats
    MAKE_STAT_TYPE_ACCESSORS(HealthPointsCurrent, Int);
    MAKE_STAT_TYPE_ACCESSORS(MagicPointsCurrent, Int);
    MAKE_STAT_TYPE_ACCESSORS(EnergyPointsCurrent, Int);
    MAKE_STAT_TYPE_ACCESSORS(HealthPointsMax, Int);
    MAKE_STAT_TYPE_ACCESSORS(MagicPointsMax, Int);
    MAKE_STAT_TYPE_ACCESSORS(EnergyPointsMax, Int);
    MAKE_STAT_TYPE_ACCESSORS(HealthRegen, Int);
    MAKE_STAT_TYPE_ACCESSORS(MagicRegen, Int);
    MAKE_STAT_TYPE_ACCESSORS(EnergyRegen, Int);
    MAKE_STAT_TYPE_ACCESSORS(HealthCostDelta, Int);
    MAKE_STAT_TYPE_ACCESSORS(MagicCostDelta, Int);
    MAKE_STAT_TYPE_ACCESSORS(EnergyCostDelta, Int);
    MAKE_STAT_TYPE_ACCESSORS(Speed, Int);
    MAKE_STAT_TYPE_ACCESSORS(AmberValueDelta, Int);
    MAKE_STAT_TYPE_ACCESSORS(RubyValueDelta, Int);
    MAKE_STAT_TYPE_ACCESSORS(DiamondValueDelta, Int);
    MAKE_STAT_TYPE_ACCESSORS(CitrineValueDelta, Int);
    MAKE_STAT_TYPE_ACCESSORS(OnyxValueDelta, Int);
    MAKE_STAT_TYPE_ACCESSORS(QuartzValueDelta, Int);
    MAKE_STAT_TYPE_ACCESSORS(SapphireValueDelta, Int);
    MAKE_STAT_TYPE_ACCESSORS(AmethystValueDelta, Int);
    MAKE_STAT_TYPE_ACCESSORS(EmeraldValueDelta, Int);
    MAKE_STAT_TYPE_ACCESSORS(GarnetValueDelta, Int);
    MAKE_STAT_TYPE_ACCESSORS(IvoryValueDelta, Int);
    MAKE_STAT_TYPE_ACCESSORS(OpalValueDelta, Int);
    MAKE_STAT_TYPE_ACCESSORS(BluntAttack, Int);
    MAKE_STAT_TYPE_ACCESSORS(BluntDefense, Int);
    MAKE_STAT_TYPE_ACCESSORS(MagicAttack, Int);
    MAKE_STAT_TYPE_ACCESSORS(MagicDefense, Int);
    MAKE_STAT_TYPE_ACCESSORS(PierceAttack, Int);
    MAKE_STAT_TYPE_ACCESSORS(PierceDefense, Int);
    MAKE_STAT_TYPE_ACCESSORS(SlashAttack, Int);
    MAKE_STAT_TYPE_ACCESSORS(SlashDefense, Int);
    MAKE_STAT_TYPE_ACCESSORS(EnergyAttack, Int);
    MAKE_STAT_TYPE_ACCESSORS(EnergyDefense, Int);

    // Comparisons
    Bool operator==(const CharacterProgressData& other) const;
    Bool operator!=(const CharacterProgressData& other) const;
};

// Typedef
MAKE_COMMON_TYPEDEFS(CharacterProgressData);

// JSON Converters
void to_json(Json& jsonData, const CharacterProgressData& obj);
void from_json(const Json& jsonData, CharacterProgressData& obj);

};

#endif
