// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#include "Character/CharacterGenerator.h"
#include "Character/CharacterTypes.h"
#include "Utility/TypesFantasyName.h"

namespace Gecko
{

CharacterGenerator::CharacterGenerator()
    : SerializableToJson()
{
}

CharacterGenerator::CharacterGenerator(const Json& jsonData)
    : SerializableToJson(jsonData)
{
}

STDSharedPtr<CharacterProgressData> CharacterGenerator::CreateEmptyProgressData()
{
    STDSharedPtr<CharacterProgressData> pProgressData = STDMakeSharedPtr<CharacterProgressData>();
    return pProgressData;
}

STDSharedPtr<CharacterBattleData> CharacterGenerator::CreateEmptyBattleData()
{
    STDSharedPtr<CharacterBattleData> pBattleData = STDMakeSharedPtr<CharacterBattleData>();
    return pBattleData;
}

STDSharedPtr<CharacterProgressData> CharacterGenerator::GenerateProgressData() const
{
    // Create progress data
    STDSharedPtr<CharacterProgressData> pProgressData = STDMakeSharedPtr<CharacterProgressData>();
    if(!pProgressData)
    {
        return pProgressData;
    }

    // -- Meters --
    pProgressData->SetHealthPointsMax(STDRandomIntValue<Int>(GetHPStart(), GetHPEnd()));
    pProgressData->SetMagicPointsMax(STDRandomIntValue<Int>(GetMPStart(), GetMPEnd()));
    pProgressData->SetEnergyPointsMax(STDRandomIntValue<Int>(GetEPStart(), GetEPEnd()));
    pProgressData->SetHealthPointsCurrent(pProgressData->GetHealthPointsMax());
    pProgressData->SetMagicPointsCurrent(pProgressData->GetMagicPointsMax());
    pProgressData->SetEnergyPointsCurrent(pProgressData->GetEnergyPointsMax());
    pProgressData->SetHealthRegen(STDRandomIntValue<Int>(GetHPRegenStart(), GetHPRegenEnd()));
    pProgressData->SetMagicRegen(STDRandomIntValue<Int>(GetMPRegenStart(), GetMPRegenEnd()));
    pProgressData->SetEnergyRegen(STDRandomIntValue<Int>(GetEPRegenStart(), GetEPRegenEnd()));
    pProgressData->SetSpeed(STDRandomIntValue<Int>(GetSpeedStart(), GetSpeedEnd()));

    // -- Attack and Defense Scoring --
    pProgressData->SetBluntAttack(STDRandomIntValue<Int>(GetBluntATKStart(), GetBluntATKEnd()));
    pProgressData->SetBluntDefense(STDRandomIntValue<Int>(GetBluntDEFStart(), GetBluntDEFEnd()));
    pProgressData->SetPierceAttack(STDRandomIntValue<Int>(GetPierceATKStart(), GetPierceATKEnd()));
    pProgressData->SetPierceDefense(STDRandomIntValue<Int>(GetPierceDEFStart(), GetPierceDEFEnd()));
    pProgressData->SetSlashAttack(STDRandomIntValue<Int>(GetSlashATKStart(), GetSlashATKEnd()));
    pProgressData->SetSlashDefense(STDRandomIntValue<Int>(GetSlashDEFStart(), GetSlashDEFEnd()));
    pProgressData->SetEnergyAttack(STDRandomIntValue<Int>(GetEnergyATKStart(), GetEnergyATKEnd()));
    pProgressData->SetEnergyDefense(STDRandomIntValue<Int>(GetEnergyDEFStart(), GetEnergyDEFEnd()));
    pProgressData->SetMagicAttack(STDRandomIntValue<Int>(GetMagicATKStart(), GetMagicATKEnd()));
    pProgressData->SetMagicDefense(STDRandomIntValue<Int>(GetMagicDEFStart(), GetMagicDEFEnd()));
    return pProgressData;
}

IndexedString CharacterGenerator::GenerateFirstName() const
{
    return IndexedString(GetUseRandomName() ? GenerateRandomFantasyName(GetFirstNamePattern()) : GetFirstName());
}

IndexedString CharacterGenerator::GenerateLastName() const
{
    return IndexedString(GetUseRandomName() ? GenerateRandomFantasyName(GetLastNamePattern()) : GetLastName());
}

Int CharacterGenerator::GenerateAge() const
{
    return STDRandomIntValue<Int>(GetAgeStart(), GetAgeEnd());
}

IndexedString CharacterGenerator::GenerateGender() const
{
    return IndexedString(GetUseRandomGender() ? STDRandomEnumValue<CharacterGenderType>() : GetGender());
}

IndexedString CharacterGenerator::GenerateHair() const
{
    return IndexedString(GetUseRandomHair() ? STDRandomEnumValue<CharacterHairType>() : GetHair());
}

IndexedString CharacterGenerator::GenerateEyes() const
{
    return IndexedString(GetUseRandomEyes() ? STDRandomEnumValue<CharacterEyeType>() : GetEyes());
}

IndexedString CharacterGenerator::GenerateHandedness() const
{
    return IndexedString(GetUseRandomHandedness() ? STDRandomEnumValue<CharacterHandednessType>() : GetHandedness());
}

IndexedString CharacterGenerator::GenerateBaseRace() const
{
    return IndexedString(GetUseRandomBaseRace() ? STDRandomEnumValue<CharacterBaseRaceType>() : GetBaseRace());
}

IndexedString CharacterGenerator::GenerateTransformedRace() const
{
    return IndexedString(GetUseRandomTransformedRace() ? STDRandomEnumValue<CharacterTransformedRaceType>() : GetTransformedRace());
}

IndexedString CharacterGenerator::GeneratePowerSet() const
{
    return IndexedString(GetUseRandomPowerSet() ? STDRandomEnumValue<CharacterPowerSetType>() : GetPowerSet());
}

MAKE_JSON_BASIC_TYPE_CONVERTERS_IMPL(CharacterGenerator);
MAKE_JSON_GENERIC_TYPE_CONVERTERS_IMPL(CharacterGenerator, CharacterGenerator);

};
