// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#ifndef _GECKO_CHARACTER_GENERATOR_H_
#define _GECKO_CHARACTER_GENERATOR_H_

#include "Character/CharacterProgressData.h"
#include "Character/CharacterBattleData.h"
#include "Utility/IndexedString.h"
#include "Utility/Macros.h"
#include "Utility/TypesJson.h"
#include "Utility/Serializable.h"

namespace Gecko
{

class CharacterGenerator : public SerializableToJson
{
public:

    // Constructors
    CharacterGenerator();
    CharacterGenerator(const Json& jsonData);

    // Create empty data
    static STDSharedPtr<CharacterProgressData> CreateEmptyProgressData();
    static STDSharedPtr<CharacterBattleData> CreateEmptyBattleData();

    // Generate character data
    STDSharedPtr<CharacterProgressData> GenerateProgressData() const;
    IndexedString GenerateFirstName() const;
    IndexedString GenerateLastName() const;
    Int GenerateAge() const;
    IndexedString GenerateGender() const;
    IndexedString GenerateHair() const;
    IndexedString GenerateEyes() const;
    IndexedString GenerateHandedness() const;
    IndexedString GenerateBaseRace() const;
    IndexedString GenerateTransformedRace() const;
    IndexedString GeneratePowerSet() const;

    // -- Basics --
    MAKE_JSON_BASIC_TYPE_ACCESSORS(FirstName, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(LastName, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(FirstNamePattern, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(LastNamePattern, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(AgeStart, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(AgeEnd, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(Gender, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(Hair, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(Eyes, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(Handedness, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(BaseRace, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(TransformedRace, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(PowerSet, String);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(UseRandomName, Bool);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(UseRandomGender, Bool);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(UseRandomHair, Bool);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(UseRandomEyes, Bool);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(UseRandomHandedness, Bool);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(UseRandomBaseRace, Bool);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(UseRandomTransformedRace, Bool);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(UseRandomPowerSet, Bool);

    // -- Meters --
    MAKE_JSON_BASIC_TYPE_ACCESSORS(HPStart, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(HPEnd, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(MPStart, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(MPEnd, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(EPStart, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(EPEnd, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(HPRegenStart, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(HPRegenEnd, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(MPRegenStart, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(MPRegenEnd, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(EPRegenStart, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(EPRegenEnd, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SpeedStart, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SpeedEnd, Int);

    // -- Attack and Defense Scoring --
    MAKE_JSON_BASIC_TYPE_ACCESSORS(BluntATKStart, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(BluntATKEnd, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(BluntDEFStart, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(BluntDEFEnd, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(PierceATKStart, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(PierceATKEnd, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(PierceDEFStart, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(PierceDEFEnd, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SlashATKStart, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SlashATKEnd, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SlashDEFStart, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(SlashDEFEnd, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(EnergyATKStart, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(EnergyATKEnd, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(EnergyDEFStart, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(EnergyDEFEnd, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(MagicATKStart, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(MagicATKEnd, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(MagicDEFStart, Int);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(MagicDEFEnd, Int);
};

// Typedef
MAKE_TYPE_TYPEDEFS(CharacterGenerator);

// JSON Converters
MAKE_JSON_BASIC_TYPE_CONVERTERS_DECL(CharacterGenerator);
MAKE_JSON_GENERIC_TYPE_CONVERTERS_DECL(CharacterGenerator, CharacterGenerator);

};

#endif
