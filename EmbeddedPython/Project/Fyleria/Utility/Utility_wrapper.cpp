// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

// Internal includes
#include "Character/CharacterTypes.h"
#include "Items/ItemTypes.h"
#include "Skills/SkillTypes.h"
#include "Saves/SaveTypes.h"
#include "Utility/IndexedString.h"
#include "Utility/Tree.h"
#include "Utility/Enum.h"
#include "Utility/FantasyName.h"
#include "Utility/Python.h"
#include "Utility/Templates.h"
#include "Utility/ResultManager.h"

namespace Gecko
{
    // Manager lambdas
    auto fnStoreResult = MAKE_MANAGER_VOID_LAMBDA_A2(ResultManager, StoreResult, const String&, const String&);
    auto fnStoreCurrentResult = MAKE_MANAGER_VOID_LAMBDA_A1(ResultManager, StoreCurrentResult, const String&);
    auto fnGetResult = MAKE_MANAGER_RETURN_LAMBDA_A1(ResultManager, GetResult, String, const String&);
    auto fnDoesResultExist = MAKE_MANAGER_RETURN_LAMBDA_A1(ResultManager, DoesResultExist, Bool, const String&);
    auto fnClearResult = MAKE_MANAGER_VOID_LAMBDA_A1(ResultManager, ClearResult, const String&);
    auto fnClearAllResults = MAKE_MANAGER_VOID_LAMBDA(ResultManager, ClearAllResults);
    auto fnGetCurrentResultID = MAKE_MANAGER_RETURN_LAMBDA(ResultManager, GetCurrentResultID, const String&);
    auto fnSetCurrentResultID = MAKE_MANAGER_VOID_LAMBDA_A1(ResultManager, SetCurrentResultID, const String&);

    // Get all type names as a json string
    String GetAllTypeNames()
    {
        // CharacterTypes.h
        Json jsonData;
        jsonData["CharacterTreeIndexType"] = GetEnumNames<CharacterTreeIndexType>();
        jsonData["CharacterSegmentType"] = GetEnumNames<CharacterSegmentType>();
        jsonData["CharacterActionStatType_Int"] = GetEnumNames<CharacterActionStatType_Int>();
        jsonData["CharacterBasicStatType_String"] = GetEnumNames<CharacterBasicStatType_String>();
        jsonData["CharacterBasicStatType_Int"] = GetEnumNames<CharacterBasicStatType_Int>();
        jsonData["CharacterMediaStatType_String"] = GetEnumNames<CharacterMediaStatType_String>();
        jsonData["CharacterProgressStatType_Int"] = GetEnumNames<CharacterProgressStatType_Int>();
        jsonData["CharacterBattleStatType_String"] = GetEnumNames<CharacterBattleStatType_String>();
        jsonData["CharacterBattleStatType_StringArray"] = GetEnumNames<CharacterBattleStatType_StringArray>();
        jsonData["CharacterBattleStatType_Bool"] = GetEnumNames<CharacterBattleStatType_Bool>();
        jsonData["CharacterBattleStatType_Int"] = GetEnumNames<CharacterBattleStatType_Int>();
        jsonData["CharacterBattleStatType_Float"] = GetEnumNames<CharacterBattleStatType_Float>();
        jsonData["CharacterSkillStatType_Short"] = GetEnumNames<CharacterSkillStatType_Short>();
        jsonData["CharacterStatusType"] = GetEnumNames<CharacterStatusType>();
        jsonData["CharacterBaseRaceType"] = GetEnumNames<CharacterBaseRaceType>();
        jsonData["CharacterTransformedRaceType"] = GetEnumNames<CharacterTransformedRaceType>();
        jsonData["CharacterPowerSetType"] = GetEnumNames<CharacterPowerSetType>();
        jsonData["CharacterWeaponSetType"] = GetEnumNames<CharacterWeaponSetType>();
        jsonData["CharacterGenderType"] = GetEnumNames<CharacterGenderType>();
        jsonData["CharacterHairType"] = GetEnumNames<CharacterHairType>();
        jsonData["CharacterEyeType"] = GetEnumNames<CharacterEyeType>();
        jsonData["CharacterHandednessType"] = GetEnumNames<CharacterHandednessType>();
        jsonData["CharacterHandType"] = GetEnumNames<CharacterHandType>();
        jsonData["CharacterEquipmentType"] = GetEnumNames<CharacterEquipmentType>();
        jsonData["CharacterTargetType"] = GetEnumNames<CharacterTargetType>();
        jsonData["CharacterResolvedTargetType"] = GetEnumNames<CharacterResolvedTargetType>();
        jsonData["CharacterPartyType"] = GetEnumNames<CharacterPartyType>();
        jsonData["CharacterActionType"] = GetEnumNames<CharacterActionType>();

        // SaveTypes.h
        jsonData["SaveSlotType"] = GetEnumNames<SaveSlotType>();

        // SkillTypes.h
        jsonData["SkillTreeType"] = GetEnumNames<SkillTreeType>();
        jsonData["SkillWeaponBaseType"] = GetEnumNames<SkillWeaponBaseType>();
        jsonData["SkillWeaponType"] = GetEnumNames<SkillWeaponType>();
        jsonData["SkillAlchemyType"] = GetEnumNames<SkillAlchemyType>();
        jsonData["SkillBreakdownType"] = GetEnumNames<SkillBreakdownType>();
        jsonData["SkillCombatType"] = GetEnumNames<SkillCombatType>();
        jsonData["SkillCraftingType"] = GetEnumNames<SkillCraftingType>();
        jsonData["SkillAffinityType"] = GetEnumNames<SkillAffinityType>();

        // ItemTypes.h
        jsonData["ItemTreeType"] = GetEnumNames<ItemTreeType>();
        jsonData["ItemType"] = GetEnumNames<ItemType>();

        // TypesEnum.h
        jsonData["OperationType"] = GetEnumNames<OperationType>();
        jsonData["ComparisonType"] = GetEnumNames<ComparisonType>();
        jsonData["FileType"] = GetEnumNames<FileType>();
        return jsonData.dump();
    }
    MAKE_MODULE_RESULT_VARIANT(GetAllTypeNames);

};

PYBIND11_MAKE_OPAQUE(Gecko::TreeIndexArray);
PYBIND11_MAKE_OPAQUE(Gecko::IndexedStringArray);

PYBIND11_EMBEDDED_MODULE(GeckoUtility, m)
{
    // IndexedString.h
    PyBindClass<Gecko::IndexedString>(m, "IndexedString")
        WRAPPING_ADD_CONSTRUCTOR_SIMPLE()
        WRAPPING_ADD_CONSTRUCTOR_ARGS(const Gecko::String&)
        WRAPPING_ADD_METHOD_SIMPLE(Set, Gecko::IndexedString)
        WRAPPING_ADD_METHOD_SIMPLE(Get, Gecko::IndexedString)
        WRAPPING_ADD_METHOD_FUNC(Empty, empty, Gecko::IndexedString)
        WRAPPING_ADD_METHOD_FUNC(Length, length, Gecko::IndexedString)
        WRAPPING_ADD_METHOD_SIMPLE(IsNone, Gecko::IndexedString)
        WRAPPING_ADD_METHOD_SIMPLE(IsValid, Gecko::IndexedString)
        WRAPPING_ADD_METHOD_SIMPLE(GetIndex, Gecko::IndexedString)
    ;
    PyBindVector<Gecko::IndexedStringArray>(m, "IndexedStringArray");
    PyBindMakeImplicitlyConvertible<Gecko::String, Gecko::IndexedString>();
    PyBindMakeImplicitlyConvertible<Gecko::StringArray, Gecko::IndexedStringArray>();

    // TreeIndex.h
    PyBindClass<Gecko::TreeIndex>(m, "TreeIndex")
        WRAPPING_ADD_CONSTRUCTOR_SIMPLE()
        WRAPPING_ADD_CONSTRUCTOR_ARGS(const Gecko::String&, const Gecko::String&, const Gecko::String&)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(Tree, Gecko::TreeIndex)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(Branch, Gecko::TreeIndex)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(Leaf, Gecko::TreeIndex)
        WRAPPING_ADD_METHOD_SIMPLE(GetTreeBranchType, Gecko::TreeIndex)
        WRAPPING_ADD_METHOD_SIMPLE(GetTreeBranchLeafType, Gecko::TreeIndex)
        WRAPPING_ADD_METHOD_SIMPLE(GetTypes, Gecko::TreeIndex)
    ;
    PyBindVector<Gecko::TreeIndexArray>(m, "TreeIndexArray");

    // Serialization.h
    WRAPPING_STANDALONE_METHOD_SIMPLE(ReadBinaryFile, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(WriteBinaryFile, Gecko);

    // Enum.h
    WRAPPING_STANDALONE_METHOD_FUNC(GetOperationTypeNames, GetEnumNames<Gecko::OperationType>, Gecko);
    WRAPPING_STANDALONE_METHOD_FUNC(GetComparisonTypeNames, GetEnumNames<Gecko::ComparisonType>, Gecko);
    WRAPPING_STANDALONE_METHOD_FUNC(GetFileTypeNames, GetEnumNames<Gecko::FileType>, Gecko);

    // Templates.h
    WRAPPING_STANDALONE_METHOD_FUNC(PrintStringVector, PrintStringVector<Gecko::String>, Gecko);
    WRAPPING_STANDALONE_METHOD_FUNC(PrintIndexedStringVector, PrintStringVector<Gecko::IndexedString>, Gecko);
    WRAPPING_STANDALONE_METHOD_FUNC(ConcatStringVector, ConcatStringVector<Gecko::String>, Gecko);
    WRAPPING_STANDALONE_METHOD_FUNC(ConcatIndexedStringVector, ConcatStringVector<Gecko::IndexedString>, Gecko);

    // FantasyName.h
    WRAPPING_STANDALONE_METHOD_SIMPLE(GenerateRandomFantasyName, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetRandomNamePattern, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetCapitalizationToken, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetReverseToken, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetMiddleEarthNamePattern, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetJapaneseNameConstrainedPattern, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetJapaneseNameDiversePattern, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetChineseNamePattern, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetGreekNamePattern, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetHawaiianName1Pattern, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetHawaiianName2Pattern, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetOldLatinPlaceNamePattern, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetDragonPernNamePattern, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetDragonRiderNamePattern, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetPokemonNamePattern, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetFantasyVowelsRNamePattern, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetFantasySANamePattern, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetFantasyHLNamePattern, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetFantasyNLNamePattern, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetFantasyKNNamePattern, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetFantasyJGZNamePattern, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetFantasyKJYNamePattern, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetFantasySENamePattern, Gecko);

    // ResultManager.h
    WRAPPING_STANDALONE_LAMBDA(StoreResult, Gecko::fnStoreResult);
    WRAPPING_STANDALONE_LAMBDA(StoreCurrentResult, Gecko::fnStoreCurrentResult);
    WRAPPING_STANDALONE_LAMBDA_POLICY(GetResult, Gecko::fnGetResult, PyBindReturnCopy);
    WRAPPING_STANDALONE_LAMBDA(DoesResultExist, Gecko::fnDoesResultExist);
    WRAPPING_STANDALONE_LAMBDA(ClearResult, Gecko::fnClearResult);
    WRAPPING_STANDALONE_LAMBDA(ClearAllResults, Gecko::fnClearAllResults);
    WRAPPING_STANDALONE_LAMBDA_POLICY(GetCurrentResultID, Gecko::fnGetCurrentResultID, PyBindReturnCopy);
    WRAPPING_STANDALONE_LAMBDA(SetCurrentResultID, Gecko::fnSetCurrentResultID);

    // Local
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetAllTypeNames, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetAllTypeNames_StoreResult, Gecko);
}
