// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

// Internal includes
#include "CharacterData/CharacterProgressData.h"
#include "Character/CharacterTypes.h"
#include "Utility/Templates.h"

namespace Gecko
{

CharacterProgressData::CharacterProgressData()
{
}

CharacterProgressData::CharacterProgressData(const Json& jsonData)
{
    from_json(jsonData, *this);
}

CharacterProgressData::~CharacterProgressData()
{
}

void CharacterProgressData::ApplyTakenDamage(Int iDamage)
{
    Int iNewHealthPoints = ClipValue<Int>(GetHealthPointsCurrent() - iDamage, 0, GetHealthPointsMax());
    SetHealthPointsCurrent(iNewHealthPoints);
}

void CharacterProgressData::ApplyRegeneration(Bool bCanRegenHP, Bool bCanRegenMP, Bool bCanRegenEP)
{
    // Get new values
    Int iNewHP = ClipValue<Int>(GetHealthPointsCurrent() + GetHealthRegen(), 0, GetHealthPointsMax());
    Int iNewMP = ClipValue<Int>(GetMagicPointsCurrent() + GetMagicRegen(), -GetMagicPointsMax(), GetMagicPointsMax());
    Int iNewEP = ClipValue<Int>(GetEnergyPointsCurrent() + GetEnergyRegen(), -GetEnergyPointsMax(), GetEnergyPointsMax());

    // Apply new values
    if(bCanRegenHP) { SetHealthPointsCurrent(iNewHP); }
    if(bCanRegenMP) { SetMagicPointsCurrent(iNewMP); }
    if(bCanRegenEP) { SetEnergyPointsCurrent(iNewEP); }
}

void CharacterProgressData::InitAllStatNames()
{
    // Initialize stat type names
    InitializeStatTypeNames<CharacterProgressStatType_Int>(GetIntStatNames());
}

Bool CharacterProgressData::operator==(const CharacterProgressData& other) const
{
    return (Json(*this) == Json(other));
}

Bool CharacterProgressData::operator!=(const CharacterProgressData& other) const
{
    return not operator==(other);
}

void to_json(Json& jsonData, const CharacterProgressData& obj)
{
    // Stat values
    SetJsonValuesFromStatTypeValues<CharacterProgressStatType_Int, Int>(jsonData, obj.GetIntStats());
}

void from_json(const Json& jsonData, CharacterProgressData& obj)
{
    // Stat values
    SetStatTypeValuesFromJsonValues<CharacterProgressStatType_Int, Int>(jsonData, obj.GetIntStats());
}

};
