// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#ifndef _GECKO_CHARACTER_PROGRESS_DATA_H_
#define _GECKO_CHARACTER_PROGRESS_DATA_H_

#include "Character/CharacterAction.h"
#include "Character/CharacterProgressItem.h"
#include "Utility/IndexedString.h"
#include "Utility/Macros.h"
#include "Utility/TypesEnum.h"
#include "Utility/TypesJson.h"

namespace Gecko
{

// POD class for character progress data
class CharacterProgressData
{
public:

    // Constructors
    CharacterProgressData();
    CharacterProgressData(const Json& jsonData);

    // Clear all data
    void Clear();

    // Apply damage
    void ApplyTakenDamage(Int iDamage);

    // Apply regeneration
    void ApplyRegeneration(Bool bCanRegenHP, Bool bCanRegenMP, Bool bCanRegenEP);

    // Apply cost of action
    void ApplyActionCost(const CharacterActionSharedPtr& pAction);

    // Update available AP
    void UpdateAvailableAP(const TreeIndexList& vIndices);

    // Stat values
    Bool GetIntStatValue(const IndexedString& sStat, Int& iValue) const;
    Bool SetIntStatValue(const IndexedString& sStat, const Int& iValue);

    // Stat names
    static STDUnorderedSet<String>& GetUByteStatNames();
    static STDUnorderedSet<String>& GetUShortStatNames();
    static STDUnorderedSet<String>& GetShortStatNames();
    static void InitAllStatNames();

    // -- Meters --
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(HealthPointsCurrent, Short);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(MagicPointsCurrent, Short);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(EnergyPointsCurrent, Short);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(HealthPointsMax, Short);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(MagicPointsMax, Short);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(EnergyPointsMax, Short);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(HealthRegen, Short);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(MagicRegen, Short);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(EnergyRegen, Short);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(HealthCostDelta, Short);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(MagicCostDelta, Short);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(EnergyCostDelta, Short);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(Speed, Short);

    // -- Gemstones --
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(AmberValueDelta, Short);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(RubyValueDelta, Short);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(DiamondValueDelta, Short);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(CitrineValueDelta, Short);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(OnyxValueDelta, Short);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(QuartzValueDelta, Short);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(SapphireValueDelta, Short);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(AmethystValueDelta, Short);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(EmeraldValueDelta, Short);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(GarnetValueDelta, Short);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(IvoryValueDelta, Short);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(OpalValueDelta, Short);

    // -- Attack and Defense Scoring --
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(BluntAttack, UShort);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(BluntDefense, UShort);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(MagicAttack, UShort);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(MagicDefense, UShort);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(PierceAttack, UShort);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(PierceDefense, UShort);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(SlashAttack, UShort);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(SlashDefense, UShort);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(EnergyAttack, UShort);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(EnergyDefense, UShort);

    // -- Action Points --
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(SlashPoints, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(SeverPoints, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(SlicePoints, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(SlitPoints, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(CleavePoints, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(DecapitatePoints, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(ParryPoints, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(RipostePoints, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(BashPoints, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(SmashPoints, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(ImpactPoints, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(CrushPoints, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(BreakPoints, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(CrackPoints, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(BlockPoints, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(RushPoints, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(PiercePoints, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(DrillPoints, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(ShootPoints, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(ImpalePoints, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(StealthStrikePoints, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(CriticalShotPoints, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(DodgePoints, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS_WITH_STATIC(CounterPoints, UByte);

    // Comparisons
    Bool operator==(const CharacterProgressData& other) const;
    Bool operator!=(const CharacterProgressData& other) const;
};

// Typedef
MAKE_TYPE_TYPEDEFS(CharacterProgressData);

// JSON Converters
void to_json(Json& jsonData, const CharacterProgressData& obj);
void from_json(const Json& jsonData, CharacterProgressData& obj);
MAKE_JSON_GENERIC_TYPE_CONVERTERS_DECL(CharacterProgressData, CharacterProgressData);

};

#endif
