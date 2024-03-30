// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

#ifndef _GECKO_CHARACTER_GENERATOR_H_
#define _GECKO_CHARACTER_GENERATOR_H_

// Internal includes
#include "CharacterData/CharacterBasicData.h"
#include "CharacterData/CharacterProgressData.h"
#include "CharacterData/CharacterBattleData.h"
#include "CharacterData/CharacterSkillData.h"
#include "Utility/Macros.h"
#include "Utility/Json.h"

namespace Gecko
{

class CharacterGenerator
{
public:

    // Constructors
    CharacterGenerator();
    CharacterGenerator(const Json& jsonData);
    CharacterGenerator(const String& jsonString);

    // Destructor
    virtual ~CharacterGenerator();

    // Generate character data
    CharacterBasicData GenerateBasicData(const String& sCharacterID) const;
    CharacterProgressData GenerateProgressData() const;
    CharacterSkillData GenerateSkillData() const;
    String GenerateFirstName() const;
    String GenerateLastName() const;
    Int GenerateAge() const;
    String GenerateGender() const;
    String GenerateHair() const;
    String GenerateEyes() const;
    String GenerateHandedness() const;
    String GenerateBaseRace() const;
    String GenerateTransformedRace() const;
    String GeneratePowerSet() const;
    String GenerateWeaponSet() const;

    // Randomization
    void RandomizeBasics();
    void RandomizeMeters();
    void RandomizeScoring();
    void RandomizeSkills();
    void RandomizeAll();

    // Basics
    MAKE_RAW_TYPE_ACCESSORS(FirstName, String);
    MAKE_RAW_TYPE_ACCESSORS(LastName, String);
    MAKE_RAW_TYPE_ACCESSORS(FirstNamePattern, String);
    MAKE_RAW_TYPE_ACCESSORS(LastNamePattern, String);
    MAKE_RAW_TYPE_ACCESSORS(Age, Int);
    MAKE_RAW_TYPE_ACCESSORS(AgeStart, Int);
    MAKE_RAW_TYPE_ACCESSORS(AgeEnd, Int);
    MAKE_RAW_TYPE_ACCESSORS(Gender, String);
    MAKE_RAW_TYPE_ACCESSORS(Hair, String);
    MAKE_RAW_TYPE_ACCESSORS(Eyes, String);
    MAKE_RAW_TYPE_ACCESSORS(Handedness, String);
    MAKE_RAW_TYPE_ACCESSORS(BaseRace, String);
    MAKE_RAW_TYPE_ACCESSORS(TransformedRace, String);
    MAKE_RAW_TYPE_ACCESSORS(PowerSet, String);
    MAKE_RAW_TYPE_ACCESSORS(WeaponSet, String);
    MAKE_RAW_TYPE_ACCESSORS(UseRandomName, Bool);
    MAKE_RAW_TYPE_ACCESSORS(UseRandomAge, Bool);
    MAKE_RAW_TYPE_ACCESSORS(UseRandomGender, Bool);
    MAKE_RAW_TYPE_ACCESSORS(UseRandomHair, Bool);
    MAKE_RAW_TYPE_ACCESSORS(UseRandomEyes, Bool);
    MAKE_RAW_TYPE_ACCESSORS(UseRandomHandedness, Bool);
    MAKE_RAW_TYPE_ACCESSORS(UseRandomBaseRace, Bool);
    MAKE_RAW_TYPE_ACCESSORS(UseRandomTransformedRace, Bool);
    MAKE_RAW_TYPE_ACCESSORS(UseRandomPowerSet, Bool);
    MAKE_RAW_TYPE_ACCESSORS(UseRandomWeaponSet, Bool);

    // Meters
    MAKE_RAW_TYPE_ACCESSORS(HPStart, Int);
    MAKE_RAW_TYPE_ACCESSORS(HPEnd, Int);
    MAKE_RAW_TYPE_ACCESSORS(MPStart, Int);
    MAKE_RAW_TYPE_ACCESSORS(MPEnd, Int);
    MAKE_RAW_TYPE_ACCESSORS(EPStart, Int);
    MAKE_RAW_TYPE_ACCESSORS(EPEnd, Int);
    MAKE_RAW_TYPE_ACCESSORS(HPRegenStart, Int);
    MAKE_RAW_TYPE_ACCESSORS(HPRegenEnd, Int);
    MAKE_RAW_TYPE_ACCESSORS(MPRegenStart, Int);
    MAKE_RAW_TYPE_ACCESSORS(MPRegenEnd, Int);
    MAKE_RAW_TYPE_ACCESSORS(EPRegenStart, Int);
    MAKE_RAW_TYPE_ACCESSORS(EPRegenEnd, Int);
    MAKE_RAW_TYPE_ACCESSORS(SpeedStart, Int);
    MAKE_RAW_TYPE_ACCESSORS(SpeedEnd, Int);

    // Attack and Defense Scoring
    MAKE_RAW_TYPE_ACCESSORS(BluntATKStart, Int);
    MAKE_RAW_TYPE_ACCESSORS(BluntATKEnd, Int);
    MAKE_RAW_TYPE_ACCESSORS(BluntDEFStart, Int);
    MAKE_RAW_TYPE_ACCESSORS(BluntDEFEnd, Int);
    MAKE_RAW_TYPE_ACCESSORS(PierceATKStart, Int);
    MAKE_RAW_TYPE_ACCESSORS(PierceATKEnd, Int);
    MAKE_RAW_TYPE_ACCESSORS(PierceDEFStart, Int);
    MAKE_RAW_TYPE_ACCESSORS(PierceDEFEnd, Int);
    MAKE_RAW_TYPE_ACCESSORS(SlashATKStart, Int);
    MAKE_RAW_TYPE_ACCESSORS(SlashATKEnd, Int);
    MAKE_RAW_TYPE_ACCESSORS(SlashDEFStart, Int);
    MAKE_RAW_TYPE_ACCESSORS(SlashDEFEnd, Int);
    MAKE_RAW_TYPE_ACCESSORS(EnergyATKStart, Int);
    MAKE_RAW_TYPE_ACCESSORS(EnergyATKEnd, Int);
    MAKE_RAW_TYPE_ACCESSORS(EnergyDEFStart, Int);
    MAKE_RAW_TYPE_ACCESSORS(EnergyDEFEnd, Int);
    MAKE_RAW_TYPE_ACCESSORS(MagicATKStart, Int);
    MAKE_RAW_TYPE_ACCESSORS(MagicATKEnd, Int);
    MAKE_RAW_TYPE_ACCESSORS(MagicDEFStart, Int);
    MAKE_RAW_TYPE_ACCESSORS(MagicDEFEnd, Int);

    // Combat Skills
    MAKE_RAW_TYPE_ACCESSORS(BarbarianStart, Short);
    MAKE_RAW_TYPE_ACCESSORS(BarbarianEnd, Short);
    MAKE_RAW_TYPE_ACCESSORS(MageStart, Short);
    MAKE_RAW_TYPE_ACCESSORS(MageEnd, Short);
    MAKE_RAW_TYPE_ACCESSORS(RogueStart, Short);
    MAKE_RAW_TYPE_ACCESSORS(RogueEnd, Short);
    MAKE_RAW_TYPE_ACCESSORS(BlademasterStart, Short);
    MAKE_RAW_TYPE_ACCESSORS(BlademasterEnd, Short);
    MAKE_RAW_TYPE_ACCESSORS(AvatarStart, Short);
    MAKE_RAW_TYPE_ACCESSORS(AvatarEnd, Short);
    MAKE_RAW_TYPE_ACCESSORS(AmbidextrousStart, Short);
    MAKE_RAW_TYPE_ACCESSORS(AmbidextrousEnd, Short);
    MAKE_RAW_TYPE_ACCESSORS(FocusedStart, Short);
    MAKE_RAW_TYPE_ACCESSORS(FocusedEnd, Short);
    MAKE_RAW_TYPE_ACCESSORS(StalwartStart, Short);
    MAKE_RAW_TYPE_ACCESSORS(StalwartEnd, Short);

    // Weapon Skills
    MAKE_RAW_TYPE_ACCESSORS(SlashStart, Short);
    MAKE_RAW_TYPE_ACCESSORS(SlashEnd, Short);
    MAKE_RAW_TYPE_ACCESSORS(SeverStart, Short);
    MAKE_RAW_TYPE_ACCESSORS(SeverEnd, Short);
    MAKE_RAW_TYPE_ACCESSORS(SliceStart, Short);
    MAKE_RAW_TYPE_ACCESSORS(SliceEnd, Short);
    MAKE_RAW_TYPE_ACCESSORS(SlitStart, Short);
    MAKE_RAW_TYPE_ACCESSORS(SlitEnd, Short);
    MAKE_RAW_TYPE_ACCESSORS(CleaveStart, Short);
    MAKE_RAW_TYPE_ACCESSORS(CleaveEnd, Short);
    MAKE_RAW_TYPE_ACCESSORS(DecapitateStart, Short);
    MAKE_RAW_TYPE_ACCESSORS(DecapitateEnd, Short);
    MAKE_RAW_TYPE_ACCESSORS(ParryStart, Short);
    MAKE_RAW_TYPE_ACCESSORS(ParryEnd, Short);
    MAKE_RAW_TYPE_ACCESSORS(RiposteStart, Short);
    MAKE_RAW_TYPE_ACCESSORS(RiposteEnd, Short);
    MAKE_RAW_TYPE_ACCESSORS(BashStart, Short);
    MAKE_RAW_TYPE_ACCESSORS(BashEnd, Short);
    MAKE_RAW_TYPE_ACCESSORS(SmashStart, Short);
    MAKE_RAW_TYPE_ACCESSORS(SmashEnd, Short);
    MAKE_RAW_TYPE_ACCESSORS(CrushStart, Short);
    MAKE_RAW_TYPE_ACCESSORS(CrushEnd, Short);
    MAKE_RAW_TYPE_ACCESSORS(ImpactStart, Short);
    MAKE_RAW_TYPE_ACCESSORS(ImpactEnd, Short);
    MAKE_RAW_TYPE_ACCESSORS(BreakStart, Short);
    MAKE_RAW_TYPE_ACCESSORS(BreakEnd, Short);
    MAKE_RAW_TYPE_ACCESSORS(CrackStart, Short);
    MAKE_RAW_TYPE_ACCESSORS(CrackEnd, Short);
    MAKE_RAW_TYPE_ACCESSORS(BlockStart, Short);
    MAKE_RAW_TYPE_ACCESSORS(BlockEnd, Short);
    MAKE_RAW_TYPE_ACCESSORS(RushStart, Short);
    MAKE_RAW_TYPE_ACCESSORS(RushEnd, Short);
    MAKE_RAW_TYPE_ACCESSORS(PierceStart, Short);
    MAKE_RAW_TYPE_ACCESSORS(PierceEnd, Short);
    MAKE_RAW_TYPE_ACCESSORS(DrillStart, Short);
    MAKE_RAW_TYPE_ACCESSORS(DrillEnd, Short);
    MAKE_RAW_TYPE_ACCESSORS(ShootStart, Short);
    MAKE_RAW_TYPE_ACCESSORS(ShootEnd, Short);
    MAKE_RAW_TYPE_ACCESSORS(ImpaleStart, Short);
    MAKE_RAW_TYPE_ACCESSORS(ImpaleEnd, Short);
    MAKE_RAW_TYPE_ACCESSORS(StealthStrikeStart, Short);
    MAKE_RAW_TYPE_ACCESSORS(StealthStrikeEnd, Short);
    MAKE_RAW_TYPE_ACCESSORS(CriticalShotStart, Short);
    MAKE_RAW_TYPE_ACCESSORS(CriticalShotEnd, Short);
    MAKE_RAW_TYPE_ACCESSORS(DodgeStart, Short);
    MAKE_RAW_TYPE_ACCESSORS(DodgeEnd, Short);
    MAKE_RAW_TYPE_ACCESSORS(CounterStart, Short);
    MAKE_RAW_TYPE_ACCESSORS(CounterEnd, Short);

    // Alchemy Skills
    MAKE_RAW_TYPE_ACCESSORS(HealerStart, Short);
    MAKE_RAW_TYPE_ACCESSORS(HealerEnd, Short);
    MAKE_RAW_TYPE_ACCESSORS(AlchemistStart, Short);
    MAKE_RAW_TYPE_ACCESSORS(AlchemistEnd, Short);
    MAKE_RAW_TYPE_ACCESSORS(EnergistStart, Short);
    MAKE_RAW_TYPE_ACCESSORS(EnergistEnd, Short);
    MAKE_RAW_TYPE_ACCESSORS(ChemistStart, Short);
    MAKE_RAW_TYPE_ACCESSORS(ChemistEnd, Short);

    // Crafting Skills
    MAKE_RAW_TYPE_ACCESSORS(HammersmithStart, Short);
    MAKE_RAW_TYPE_ACCESSORS(HammersmithEnd, Short);
    MAKE_RAW_TYPE_ACCESSORS(SpellsmithStart, Short);
    MAKE_RAW_TYPE_ACCESSORS(SpellsmithEnd, Short);
    MAKE_RAW_TYPE_ACCESSORS(BowsmithStart, Short);
    MAKE_RAW_TYPE_ACCESSORS(BowsmithEnd, Short);
    MAKE_RAW_TYPE_ACCESSORS(SwordsmithStart, Short);
    MAKE_RAW_TYPE_ACCESSORS(SwordsmithEnd, Short);
    MAKE_RAW_TYPE_ACCESSORS(WeaverStart, Short);
    MAKE_RAW_TYPE_ACCESSORS(WeaverEnd, Short);
    MAKE_RAW_TYPE_ACCESSORS(TannerStart, Short);
    MAKE_RAW_TYPE_ACCESSORS(TannerEnd, Short);
    MAKE_RAW_TYPE_ACCESSORS(ScalesmithStart, Short);
    MAKE_RAW_TYPE_ACCESSORS(ScalesmithEnd, Short);
    MAKE_RAW_TYPE_ACCESSORS(PlatesmithStart, Short);
    MAKE_RAW_TYPE_ACCESSORS(PlatesmithEnd, Short);
    MAKE_RAW_TYPE_ACCESSORS(GoldsmithStart, Short);
    MAKE_RAW_TYPE_ACCESSORS(GoldsmithEnd, Short);
    MAKE_RAW_TYPE_ACCESSORS(ShieldsmithStart, Short);
    MAKE_RAW_TYPE_ACCESSORS(ShieldsmithEnd, Short);

    // Breakdown Skills
    MAKE_RAW_TYPE_ACCESSORS(HammerbaneStart, Short);
    MAKE_RAW_TYPE_ACCESSORS(HammerbaneEnd, Short);
    MAKE_RAW_TYPE_ACCESSORS(SpellbaneStart, Short);
    MAKE_RAW_TYPE_ACCESSORS(SpellbaneEnd, Short);
    MAKE_RAW_TYPE_ACCESSORS(BowbaneStart, Short);
    MAKE_RAW_TYPE_ACCESSORS(BowbaneEnd, Short);
    MAKE_RAW_TYPE_ACCESSORS(SwordbaneStart, Short);
    MAKE_RAW_TYPE_ACCESSORS(SwordbaneEnd, Short);
    MAKE_RAW_TYPE_ACCESSORS(ThreadbareStart, Short);
    MAKE_RAW_TYPE_ACCESSORS(ThreadbareEnd, Short);
    MAKE_RAW_TYPE_ACCESSORS(StudRemoverStart, Short);
    MAKE_RAW_TYPE_ACCESSORS(StudRemoverEnd, Short);
    MAKE_RAW_TYPE_ACCESSORS(ScalebaneStart, Short);
    MAKE_RAW_TYPE_ACCESSORS(ScalebaneEnd, Short);
    MAKE_RAW_TYPE_ACCESSORS(PlatebaneStart, Short);
    MAKE_RAW_TYPE_ACCESSORS(PlatebaneEnd, Short);
    MAKE_RAW_TYPE_ACCESSORS(GoldbaneStart, Short);
    MAKE_RAW_TYPE_ACCESSORS(GoldbaneEnd, Short);
    MAKE_RAW_TYPE_ACCESSORS(ShieldbaneStart, Short);
    MAKE_RAW_TYPE_ACCESSORS(ShieldbaneEnd, Short);

    // Affinity Skills
    MAKE_RAW_TYPE_ACCESSORS(HolyStart, Short);
    MAKE_RAW_TYPE_ACCESSORS(HolyEnd, Short);
    MAKE_RAW_TYPE_ACCESSORS(FireStart, Short);
    MAKE_RAW_TYPE_ACCESSORS(FireEnd, Short);
    MAKE_RAW_TYPE_ACCESSORS(IceStart, Short);
    MAKE_RAW_TYPE_ACCESSORS(IceEnd, Short);
    MAKE_RAW_TYPE_ACCESSORS(ShockStart, Short);
    MAKE_RAW_TYPE_ACCESSORS(ShockEnd, Short);
    MAKE_RAW_TYPE_ACCESSORS(DarkStart, Short);
    MAKE_RAW_TYPE_ACCESSORS(DarkEnd, Short);
    MAKE_RAW_TYPE_ACCESSORS(LightStart, Short);
    MAKE_RAW_TYPE_ACCESSORS(LightEnd, Short);
    MAKE_RAW_TYPE_ACCESSORS(ForceStart, Short);
    MAKE_RAW_TYPE_ACCESSORS(ForceEnd, Short);
    MAKE_RAW_TYPE_ACCESSORS(MindStart, Short);
    MAKE_RAW_TYPE_ACCESSORS(MindEnd, Short);
    MAKE_RAW_TYPE_ACCESSORS(EarthStart, Short);
    MAKE_RAW_TYPE_ACCESSORS(EarthEnd, Short);
    MAKE_RAW_TYPE_ACCESSORS(BloodStart, Short);
    MAKE_RAW_TYPE_ACCESSORS(BloodEnd, Short);
    MAKE_RAW_TYPE_ACCESSORS(FleshStart, Short);
    MAKE_RAW_TYPE_ACCESSORS(FleshEnd, Short);
    MAKE_RAW_TYPE_ACCESSORS(WindStart, Short);
    MAKE_RAW_TYPE_ACCESSORS(WindEnd, Short);
};

// Typedef
MAKE_COMMON_TYPEDEFS(CharacterGenerator);

// JSON Converters
void to_json(Json& jsonData, const CharacterGenerator& obj);
void from_json(const Json& jsonData, CharacterGenerator& obj);

};

#endif
