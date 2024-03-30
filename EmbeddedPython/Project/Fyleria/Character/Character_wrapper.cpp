// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

// Internal includes
#include "Character/Character.h"
#include "Character/CharacterGenerator.h"
#include "Character/CharacterManager.h"
#include "Character/CharacterTypes.h"
#include "Utility/Macros.h"
#include "Utility/Python.h"

namespace Gecko
{
    // Manager lambdas
    auto fnLoadCharacter = MAKE_MANAGER_RETURN_LAMBDA_A2(CharacterManager, LoadCharacter, String, const Character&, Bool);
    auto fnLoadCharacterFromFile = MAKE_MANAGER_RETURN_LAMBDA_A3(CharacterManager, LoadCharacterFromFile, String, const String&, const String&, Bool);
    auto fnSaveCharacterToFile = MAKE_MANAGER_VOID_LAMBDA_A3(CharacterManager, SaveCharacterToFile, const String&, const String&, const String&);
    auto fnCreateCharacter = MAKE_MANAGER_VOID_LAMBDA_A1(CharacterManager, CreateCharacter, const String&);
    auto fnUnloadCharacter = MAKE_MANAGER_VOID_LAMBDA_A1(CharacterManager, UnloadCharacter, const String&);
    auto fnDoesCharacterExist = MAKE_MANAGER_RETURN_LAMBDA_A1(CharacterManager, DoesCharacterExist, Bool, const String&);
    auto fnDoesCharacterExist_StoreResult = MAKE_MANAGER_VOID_LAMBDA_A2(CharacterManager, DoesCharacterExist_StoreResult, const String&, const String&);
    auto fnGenerateCharacter = MAKE_MANAGER_VOID_LAMBDA_A2(CharacterManager, GenerateCharacter, const String&, const CharacterGenerator&);
    auto fnIsValidCharacterID = MAKE_MANAGER_RETURN_LAMBDA_A1(CharacterManager, IsValidCharacterID, Bool, const String&);
    auto fnIsValidCharacterID_StoreResult = MAKE_MANAGER_VOID_LAMBDA_A2(CharacterManager, IsValidCharacterID_StoreResult, const String&, const String&);
    auto fnGetCharacter1 = MAKE_MANAGER_RETURN_LAMBDA_A1(CharacterManager, GetCharacter, const Character&, const String&);
    auto fnGetCharacter2 = MAKE_MANAGER_RETURN_LAMBDA_A1(CharacterManager, GetCharacter, Character&, const String&);
    auto fnGetCharacter_StoreResult = MAKE_MANAGER_VOID_LAMBDA_A2(CharacterManager, GetCharacter_StoreResult, const String&, const String&);
    auto fnGetAllCharacterIDs = MAKE_MANAGER_RETURN_LAMBDA(CharacterManager, GetAllCharacterIDs, StringArray);
    auto fnGetAllCharacterIDs_StoreResult = MAKE_MANAGER_VOID_LAMBDA_A1(CharacterManager, GetAllCharacterIDs_StoreResult, const String&);
    auto fnApplyStatChangeEntry = MAKE_MANAGER_RETURN_LAMBDA_A2(CharacterManager, ApplyStatChangeEntry, Bool, const String&, const StatChangeEntry&);
    auto fnDoesStatChangeEntryUseDelta = MAKE_MANAGER_RETURN_LAMBDA_A1(CharacterManager, DoesStatChangeEntryUseDelta, Bool, const StatChangeEntry&);
};

PYBIND11_MAKE_OPAQUE(Gecko::CharacterGeneratorArray);
PYBIND11_MAKE_OPAQUE(Gecko::CharacterArray);

PYBIND11_EMBEDDED_MODULE(GeckoCharacter, m)
{
    // CharacterGenerator.h
    PyBindClass<Gecko::CharacterGenerator>(m, "CharacterGenerator")
        WRAPPING_ADD_CONSTRUCTOR_SIMPLE()
        WRAPPING_ADD_METHOD_SIMPLE(GenerateBasicData, Gecko::CharacterGenerator)
        WRAPPING_ADD_METHOD_SIMPLE(GenerateProgressData, Gecko::CharacterGenerator)
        WRAPPING_ADD_METHOD_SIMPLE(GenerateFirstName, Gecko::CharacterGenerator)
        WRAPPING_ADD_METHOD_SIMPLE(GenerateLastName, Gecko::CharacterGenerator)
        WRAPPING_ADD_METHOD_SIMPLE(GenerateAge, Gecko::CharacterGenerator)
        WRAPPING_ADD_METHOD_SIMPLE(GenerateGender, Gecko::CharacterGenerator)
        WRAPPING_ADD_METHOD_SIMPLE(GenerateHair, Gecko::CharacterGenerator)
        WRAPPING_ADD_METHOD_SIMPLE(GenerateEyes, Gecko::CharacterGenerator)
        WRAPPING_ADD_METHOD_SIMPLE(GenerateHandedness, Gecko::CharacterGenerator)
        WRAPPING_ADD_METHOD_SIMPLE(GenerateBaseRace, Gecko::CharacterGenerator)
        WRAPPING_ADD_METHOD_SIMPLE(GenerateTransformedRace, Gecko::CharacterGenerator)
        WRAPPING_ADD_METHOD_SIMPLE(GeneratePowerSet, Gecko::CharacterGenerator)
        WRAPPING_ADD_METHOD_SIMPLE(RandomizeBasics, Gecko::CharacterGenerator)
        WRAPPING_ADD_METHOD_SIMPLE(RandomizeMeters, Gecko::CharacterGenerator)
        WRAPPING_ADD_METHOD_SIMPLE(RandomizeScoring, Gecko::CharacterGenerator)
        WRAPPING_ADD_METHOD_SIMPLE(RandomizeAll, Gecko::CharacterGenerator)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(FirstName, Gecko::CharacterGenerator)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(LastName, Gecko::CharacterGenerator)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(FirstNamePattern, Gecko::CharacterGenerator)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(LastNamePattern, Gecko::CharacterGenerator)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(Age, Gecko::CharacterGenerator)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(AgeStart, Gecko::CharacterGenerator)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(AgeEnd, Gecko::CharacterGenerator)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(Gender, Gecko::CharacterGenerator)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(Hair, Gecko::CharacterGenerator)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(Eyes, Gecko::CharacterGenerator)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(Handedness, Gecko::CharacterGenerator)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(BaseRace, Gecko::CharacterGenerator)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(TransformedRace, Gecko::CharacterGenerator)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(PowerSet, Gecko::CharacterGenerator)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(UseRandomName, Gecko::CharacterGenerator)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(UseRandomGender, Gecko::CharacterGenerator)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(UseRandomHair, Gecko::CharacterGenerator)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(UseRandomEyes, Gecko::CharacterGenerator)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(UseRandomHandedness, Gecko::CharacterGenerator)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(UseRandomBaseRace, Gecko::CharacterGenerator)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(UseRandomTransformedRace, Gecko::CharacterGenerator)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(UseRandomPowerSet, Gecko::CharacterGenerator)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(HPStart, Gecko::CharacterGenerator)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(HPEnd, Gecko::CharacterGenerator)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(MPStart, Gecko::CharacterGenerator)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(MPEnd, Gecko::CharacterGenerator)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(EPStart, Gecko::CharacterGenerator)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(EPEnd, Gecko::CharacterGenerator)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(HPRegenStart, Gecko::CharacterGenerator)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(HPRegenEnd, Gecko::CharacterGenerator)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(MPRegenStart, Gecko::CharacterGenerator)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(MPRegenEnd, Gecko::CharacterGenerator)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(EPRegenStart, Gecko::CharacterGenerator)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(EPRegenEnd, Gecko::CharacterGenerator)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(SpeedStart, Gecko::CharacterGenerator)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(SpeedEnd, Gecko::CharacterGenerator)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(BluntATKStart, Gecko::CharacterGenerator)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(BluntATKEnd, Gecko::CharacterGenerator)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(BluntDEFStart, Gecko::CharacterGenerator)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(BluntDEFEnd, Gecko::CharacterGenerator)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(PierceATKStart, Gecko::CharacterGenerator)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(PierceATKEnd, Gecko::CharacterGenerator)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(PierceDEFStart, Gecko::CharacterGenerator)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(PierceDEFEnd, Gecko::CharacterGenerator)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(SlashATKStart, Gecko::CharacterGenerator)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(SlashATKEnd, Gecko::CharacterGenerator)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(SlashDEFStart, Gecko::CharacterGenerator)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(SlashDEFEnd, Gecko::CharacterGenerator)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(EnergyATKStart, Gecko::CharacterGenerator)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(EnergyATKEnd, Gecko::CharacterGenerator)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(EnergyDEFStart, Gecko::CharacterGenerator)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(EnergyDEFEnd, Gecko::CharacterGenerator)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(MagicATKStart, Gecko::CharacterGenerator)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(MagicATKEnd, Gecko::CharacterGenerator)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(MagicDEFStart, Gecko::CharacterGenerator)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(MagicDEFEnd, Gecko::CharacterGenerator)
    ;
    PyBindVector<Gecko::CharacterGeneratorArray>(m, "CharacterGeneratorArray");

    // Character.h
    PyBindClass<Gecko::Character>(m, "Character")
        WRAPPING_ADD_CONSTRUCTOR_SIMPLE()
        WRAPPING_ADD_METHOD_SIMPLE(RegenerateCharacterData, Gecko::Character)
        WRAPPING_ADD_METHOD_SIMPLE(GetCharacterID, Gecko::Character)
        WRAPPING_ADD_METHOD_SIMPLE(GetPartyID, Gecko::Character)
        WRAPPING_ADD_METHOD_SIMPLE(GetCharacterTargetType, Gecko::Character)
        WRAPPING_ADD_METHOD_SIMPLE(GetWeaponSet, Gecko::Character)
        WRAPPING_ADD_METHOD_POLICY(GetEquippedItems, Gecko::Character, PyBindReturnCopy)
        WRAPPING_ADD_METHOD_POLICY(GetAvailableActions, Gecko::Character, PyBindReturnCopy)
        WRAPPING_ADD_METHOD_POLICY(GetPassiveChanges, Gecko::Character, PyBindReturnCopy)
        WRAPPING_ADD_METHOD_POLICY(GetActiveChanges, Gecko::Character, PyBindReturnCopy)
        WRAPPING_ADD_METHOD_POLICY(GetActionableChanges, Gecko::Character, PyBindReturnCopy)
        WRAPPING_ADD_METHOD_OVERLOADED_POLICY_CONST(GetProgressDataSegment, Gecko::Character, PyBindReturnCopy, const Gecko::String&)
        WRAPPING_ADD_METHOD_OVERLOADED_POLICY(GetProgressDataSegment, Gecko::Character, PyBindReturnRefInternal, const Gecko::String&)
        WRAPPING_ADD_METHOD_OVERLOADED_POLICY_CONST(GetBattleDataSegment, Gecko::Character, PyBindReturnCopy, const Gecko::String&)
        WRAPPING_ADD_METHOD_OVERLOADED_POLICY(GetBattleDataSegment, Gecko::Character, PyBindReturnRefInternal, const Gecko::String&)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(ProgressData, Gecko::Character)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(ProgressDataPassives, Gecko::Character)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(ProgressDataActives, Gecko::Character)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(BattleData, Gecko::Character)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(BattleDataPassives, Gecko::Character)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(BattleDataActives, Gecko::Character)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(BasicData, Gecko::Character)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(ActionData, Gecko::Character)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(SkillData, Gecko::Character)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(StatChangeData, Gecko::Character)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(MediaData, Gecko::Character)
        WRAPPING_ADD_METHOD_SIMPLE(GetCharacterID_StoreResult, Gecko::Character)
        WRAPPING_ADD_METHOD_SIMPLE(GetPartyID_StoreResult, Gecko::Character)
        WRAPPING_ADD_METHOD_SIMPLE(GetCharacterTargetType_StoreResult, Gecko::Character)
        WRAPPING_ADD_METHOD_SIMPLE(GetWeaponSet_StoreResult, Gecko::Character)
        WRAPPING_ADD_METHOD_SIMPLE(GetEquippedItems_StoreResult, Gecko::Character)
        WRAPPING_ADD_METHOD_SIMPLE(GetAvailableActions_StoreResult, Gecko::Character)
        WRAPPING_ADD_METHOD_SIMPLE(GetPassiveChanges_StoreResult, Gecko::Character)
        WRAPPING_ADD_METHOD_SIMPLE(GetActiveChanges_StoreResult, Gecko::Character)
        WRAPPING_ADD_METHOD_SIMPLE(GetActionableChanges_StoreResult, Gecko::Character)
        WRAPPING_ADD_METHOD_SIMPLE(GetProgressDataSegment_StoreResult, Gecko::Character)
        WRAPPING_ADD_METHOD_SIMPLE(GetBattleDataSegment_StoreResult, Gecko::Character)
        WRAPPING_ADD_METHOD_SIMPLE(GetProgressData_StoreResult, Gecko::Character)
        WRAPPING_ADD_METHOD_SIMPLE(GetProgressDataPassives_StoreResult, Gecko::Character)
        WRAPPING_ADD_METHOD_SIMPLE(GetProgressDataActives_StoreResult, Gecko::Character)
        WRAPPING_ADD_METHOD_SIMPLE(GetBattleData_StoreResult, Gecko::Character)
        WRAPPING_ADD_METHOD_SIMPLE(GetBattleDataPassives_StoreResult, Gecko::Character)
        WRAPPING_ADD_METHOD_SIMPLE(GetBattleDataActives_StoreResult, Gecko::Character)
        WRAPPING_ADD_METHOD_SIMPLE(GetBasicData_StoreResult, Gecko::Character)
        WRAPPING_ADD_METHOD_SIMPLE(GetActionData_StoreResult, Gecko::Character)
        WRAPPING_ADD_METHOD_SIMPLE(GetSkillData_StoreResult, Gecko::Character)
        WRAPPING_ADD_METHOD_SIMPLE(GetStatChangeData_StoreResult, Gecko::Character)
        WRAPPING_ADD_METHOD_SIMPLE(GetMediaData_StoreResult, Gecko::Character)
    ;
    PyBindVector<Gecko::CharacterArray>(m, "CharacterArray");

    // CharacterManager.h
    WRAPPING_STANDALONE_LAMBDA(LoadCharacter, Gecko::fnLoadCharacter);
    WRAPPING_STANDALONE_LAMBDA(LoadCharacterFromFile, Gecko::fnLoadCharacterFromFile);
    WRAPPING_STANDALONE_LAMBDA(SaveCharacterToFile, Gecko::fnSaveCharacterToFile);
    WRAPPING_STANDALONE_LAMBDA(CreateCharacter, Gecko::fnCreateCharacter);
    WRAPPING_STANDALONE_LAMBDA(UnloadCharacter, Gecko::fnUnloadCharacter);
    WRAPPING_STANDALONE_LAMBDA(DoesCharacterExist, Gecko::fnDoesCharacterExist);
    WRAPPING_STANDALONE_LAMBDA(DoesCharacterExist_StoreResult, Gecko::fnDoesCharacterExist_StoreResult);
    WRAPPING_STANDALONE_LAMBDA(GenerateCharacter, Gecko::fnGenerateCharacter);
    WRAPPING_STANDALONE_LAMBDA(IsValidCharacterID, Gecko::fnIsValidCharacterID);
    WRAPPING_STANDALONE_LAMBDA(IsValidCharacterID_StoreResult, Gecko::fnIsValidCharacterID_StoreResult);
    WRAPPING_STANDALONE_LAMBDA_POLICY(GetCharacter, Gecko::fnGetCharacter1, PyBindReturnCopy);
    WRAPPING_STANDALONE_LAMBDA_POLICY(GetCharacter, Gecko::fnGetCharacter2, PyBindReturnRefInternal);
    WRAPPING_STANDALONE_LAMBDA(GetCharacter_StoreResult, Gecko::fnGetCharacter_StoreResult);
    WRAPPING_STANDALONE_LAMBDA(GetAllCharacterIDs, Gecko::fnGetAllCharacterIDs);
    WRAPPING_STANDALONE_LAMBDA(GetAllCharacterIDs_StoreResult, Gecko::fnGetAllCharacterIDs_StoreResult);
    WRAPPING_STANDALONE_LAMBDA(ApplyStatChangeEntry, Gecko::fnApplyStatChangeEntry);
    WRAPPING_STANDALONE_LAMBDA(DoesStatChangeEntryUseDelta, Gecko::fnDoesStatChangeEntryUseDelta);

    // CharacterTypes.h
    WRAPPING_STANDALONE_METHOD_SIMPLE(ConvertCharacterEquipmentTypeToCharacterWeaponSetType, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(ConvertCharacterTargetTypeToCharacterPartyType, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(ConvertItemTypeToCharacterActionType, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(ConvertItemTypeToCharacterEquipTypes, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(ConvertSkillWeaponBaseTypeToCharacterActionType, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(ConvertSkillWeaponTypeToCharacterActionType, Gecko);
    WRAPPING_STANDALONE_METHOD_FUNC(GetCharacterTreeIndexTypeNames, GetEnumNames<Gecko::CharacterTreeIndexType>, Gecko);
    WRAPPING_STANDALONE_METHOD_FUNC(GetCharacterSegmentTypeNames, GetEnumNames<Gecko::CharacterSegmentType>, Gecko);
    WRAPPING_STANDALONE_METHOD_FUNC(GetCharacterBasicStatType_StringNames, GetEnumNames<Gecko::CharacterBasicStatType_String>, Gecko);
    WRAPPING_STANDALONE_METHOD_FUNC(GetCharacterBasicStatType_IntNames, GetEnumNames<Gecko::CharacterBasicStatType_Int>, Gecko);
    WRAPPING_STANDALONE_METHOD_FUNC(GetCharacterProgressStatType_IntNames, GetEnumNames<Gecko::CharacterProgressStatType_Int>, Gecko);
    WRAPPING_STANDALONE_METHOD_FUNC(GetCharacterBattleStatType_StringNames, GetEnumNames<Gecko::CharacterBattleStatType_String>, Gecko);
    WRAPPING_STANDALONE_METHOD_FUNC(GetCharacterBattleStatType_StringArrayNames, GetEnumNames<Gecko::CharacterBattleStatType_StringArray>, Gecko);
    WRAPPING_STANDALONE_METHOD_FUNC(GetCharacterBattleStatType_BoolNames, GetEnumNames<Gecko::CharacterBattleStatType_Bool>, Gecko);
    WRAPPING_STANDALONE_METHOD_FUNC(GetCharacterBattleStatType_IntNames, GetEnumNames<Gecko::CharacterBattleStatType_Int>, Gecko);
    WRAPPING_STANDALONE_METHOD_FUNC(GetCharacterBattleStatType_FloatNames, GetEnumNames<Gecko::CharacterBattleStatType_Float>, Gecko);
    WRAPPING_STANDALONE_METHOD_FUNC(GetCharacterSkillStatType_ByteNames, GetEnumNames<Gecko::CharacterSkillStatType_Short>, Gecko);
    WRAPPING_STANDALONE_METHOD_FUNC(GetCharacterStatusTypeNames, GetEnumNames<Gecko::CharacterStatusType>, Gecko);
    WRAPPING_STANDALONE_METHOD_FUNC(GetCharacterBaseRaceTypeNames, GetEnumNames<Gecko::CharacterBaseRaceType>, Gecko);
    WRAPPING_STANDALONE_METHOD_FUNC(GetCharacterTransformedRaceTypeNames, GetEnumNames<Gecko::CharacterTransformedRaceType>, Gecko);
    WRAPPING_STANDALONE_METHOD_FUNC(GetCharacterPowerSetTypeNames, GetEnumNames<Gecko::CharacterPowerSetType>, Gecko);
    WRAPPING_STANDALONE_METHOD_FUNC(GetCharacterWeaponSetTypeNames, GetEnumNames<Gecko::CharacterWeaponSetType>, Gecko);
    WRAPPING_STANDALONE_METHOD_FUNC(GetCharacterGenderTypeNames, GetEnumNames<Gecko::CharacterGenderType>, Gecko);
    WRAPPING_STANDALONE_METHOD_FUNC(GetCharacterHairTypeNames, GetEnumNames<Gecko::CharacterHairType>, Gecko);
    WRAPPING_STANDALONE_METHOD_FUNC(GetCharacterEyeTypeNames, GetEnumNames<Gecko::CharacterEyeType>, Gecko);
    WRAPPING_STANDALONE_METHOD_FUNC(GetCharacterHandednessTypeNames, GetEnumNames<Gecko::CharacterHandednessType>, Gecko);
    WRAPPING_STANDALONE_METHOD_FUNC(GetCharacterHandTypeNames, GetEnumNames<Gecko::CharacterHandType>, Gecko);
    WRAPPING_STANDALONE_METHOD_FUNC(GetCharacterEquipmentTypeNames, GetEnumNames<Gecko::CharacterEquipmentType>, Gecko);
    WRAPPING_STANDALONE_METHOD_FUNC(GetCharacterTargetTypeNames, GetEnumNames<Gecko::CharacterTargetType>, Gecko);
    WRAPPING_STANDALONE_METHOD_FUNC(GetCharacterPartyTypeNames, GetEnumNames<Gecko::CharacterPartyType>, Gecko);
    WRAPPING_STANDALONE_METHOD_FUNC(GetCharacterActionTypeNames, GetEnumNames<Gecko::CharacterActionType>, Gecko);
}
