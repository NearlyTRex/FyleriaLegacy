// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#include "Character/CharacterTypes.h"
#include "Items/ItemTypes.h"
#include "Skills/SkillTypes.h"
#include "Saves/SaveTypes.h"
#include "Utility/Serializable.h"
#include "Utility/Tree.h"
#include "Utility/TypesEnum.h"
#include "Utility/TypesFantasyName.h"
#include "Utility/TypesPython.h"

namespace Gecko
{

String GetAllTypeNames()
{
    Json jsonData;

    // CharacterTypes.h
    jsonData["CharacterTreeIndexType"] = GetCharacterTreeIndexTypeNames();
    jsonData["CharacterSegmentType"] = GetCharacterSegmentTypeNames();
    jsonData["CharacterProgressStatType"] = GetCharacterProgressStatTypeNames();
    jsonData["CharacterBattleStatType"] = GetCharacterBattleStatTypeNames();
    jsonData["CharacterStatusType"] = GetCharacterStatusTypeNames();
    jsonData["CharacterBaseRaceType"] = GetCharacterBaseRaceTypeNames();
    jsonData["CharacterTransformedRaceType"] = GetCharacterTransformedRaceTypeNames();
    jsonData["CharacterPowerSetType"] = GetCharacterPowerSetTypeNames();
    jsonData["CharacterWeaponSetType"] = GetCharacterWeaponSetTypeNames();
    jsonData["CharacterGenderType"] = GetCharacterGenderTypeNames();
    jsonData["CharacterHairType"] = GetCharacterHairTypeNames();
    jsonData["CharacterEyeType"] = GetCharacterEyeTypeNames();
    jsonData["CharacterHandednessType"] = GetCharacterHandednessTypeNames();
    jsonData["CharacterHandType"] = GetCharacterHandTypeNames();
    jsonData["CharacterEquipmentType"] = GetCharacterEquipmentTypeNames();
    jsonData["CharacterTargetType"] = GetCharacterTargetTypeNames();
    jsonData["CharacterPartyType"] = GetCharacterPartyTypeNames();
    jsonData["CharacterActionType"] = GetCharacterActionTypeNames();

    // SkillTypes.h
    jsonData["SkillTreeType"] = GetSkillTreeTypeNames();
    jsonData["SkillWeaponBaseType"] = GetSkillWeaponBaseTypeNames();
    jsonData["SkillWeaponType"] = GetSkillWeaponTypeNames();
    jsonData["SkillAlchemyType"] = GetSkillAlchemyTypeNames();
    jsonData["SkillBreakdownType"] = GetSkillBreakdownTypeNames();
    jsonData["SkillCombatType"] = GetSkillCombatTypeNames();
    jsonData["SkillCraftingType"] = GetSkillCraftingTypeNames();
    jsonData["SkillAffinityType"] = GetSkillAffinityTypeNames();

    // ItemTypes.h
    jsonData["ItemTreeType"] = GetItemTreeTypeNames();
    jsonData["ItemType"] = GetItemTypeNames();

    // TypesEnum.h
    jsonData["OperationType"] = GetOperationTypeNames();
    jsonData["ComparisonType"] = GetComparisonTypeNames();
    jsonData["FileType"] = GetFileTypeNames();
    return jsonData.dump();
}

};

PYBIND11_MAKE_OPAQUE(Gecko::TreeIndexList);
PYBIND11_MAKE_OPAQUE(Gecko::IndexedStringList);

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
    PyBindVector<Gecko::IndexedStringList>(m, "IndexedStringList");
    PyBindMakeImplicitlyConvertible<Gecko::String, Gecko::IndexedString>();
    PyBindMakeImplicitlyConvertible<Gecko::StringList, Gecko::IndexedStringList>();

    // Serializable.h
    PyBindClass<Gecko::SerializableToJson>(m, "SerializableToJson")
        WRAPPING_ADD_METHOD_SIMPLE(FromJsonString, Gecko::SerializableToJson)
        WRAPPING_ADD_METHOD_ARGS(ToJsonString, Gecko::SerializableToJson, PyBindArg("iIndent") = -1)
        WRAPPING_ADD_METHOD_SIMPLE(FromCBOR, Gecko::SerializableToJson)
        WRAPPING_ADD_METHOD_SIMPLE(FromMsgPack, Gecko::SerializableToJson)
        WRAPPING_ADD_METHOD_SIMPLE(ToCBOR, Gecko::SerializableToJson)
        WRAPPING_ADD_METHOD_SIMPLE(ToMsgPack, Gecko::SerializableToJson)
        WRAPPING_ADD_METHOD_SIMPLE(FromFile, Gecko::SerializableToJson)
        WRAPPING_ADD_METHOD_SIMPLE(FromCBORFile, Gecko::SerializableToJson)
        WRAPPING_ADD_METHOD_SIMPLE(FromMsgPackFile, Gecko::SerializableToJson)
        WRAPPING_ADD_METHOD_SIMPLE(ToFile, Gecko::SerializableToJson)
        WRAPPING_ADD_METHOD_SIMPLE(ToCBORFile, Gecko::SerializableToJson)
        WRAPPING_ADD_METHOD_SIMPLE(ToMsgPackFile, Gecko::SerializableToJson)
        WRAPPING_ADD_METHOD_SIMPLE(Reset, Gecko::SerializableToJson)
        WRAPPING_ADD_METHOD_SIMPLE(Clear, Gecko::SerializableToJson)
        WRAPPING_ADD_METHOD_SIMPLE(IsEmpty, Gecko::SerializableToJson)
        WRAPPING_ADD_BASIC_PROPERTY_READONLY_SIMPLE(Size, Gecko::SerializableToJson)
    ;

    // TreeIndex.h
    PyBindClass<Gecko::TreeIndex, Gecko::SerializableToJson>(m, "TreeIndex")
        WRAPPING_ADD_CONSTRUCTOR_SIMPLE()
        WRAPPING_ADD_CONSTRUCTOR_ARGS(const Gecko::IndexedString&, const Gecko::IndexedString&, const Gecko::IndexedString&)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(Tree, Gecko::TreeIndex)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(Branch, Gecko::TreeIndex)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(Leaf, Gecko::TreeIndex)
        WRAPPING_ADD_METHOD_SIMPLE(GetTreeBranchType, Gecko::TreeIndex)
        WRAPPING_ADD_METHOD_SIMPLE(GetTreeBranchLeafType, Gecko::TreeIndex)
        WRAPPING_ADD_METHOD_SIMPLE(GetTypes, Gecko::TreeIndex)
    ;
    PyBindVector<Gecko::TreeIndexList>(m, "TreeIndexList");
    WRAPPING_STANDALONE_METHOD_SIMPLE(ConvertTreeIndexToJsonString, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(ConvertTreeIndexListToJsonString, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetTreeIndexFromJsonString, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetTreeIndexListFromJsonString, Gecko);

    // Serialization.h
    WRAPPING_STANDALONE_METHOD_SIMPLE(ReadBinaryFile, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(WriteBinaryFile, Gecko);

    // TypesEnum.h
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetOperationTypeNames, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetComparisonTypeNames, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetFileTypeNames, Gecko);

    // TypesSimple.h
    WRAPPING_STANDALONE_METHOD_FUNC(PrintStringVector, STDVectorPrintStrings<Gecko::String>, Gecko);
    WRAPPING_STANDALONE_METHOD_FUNC(PrintIndexedStringVector, STDVectorPrintStrings<Gecko::IndexedString>, Gecko);
    WRAPPING_STANDALONE_METHOD_FUNC(ConvertStringVector, STDVectorConvertStrings<Gecko::String>, Gecko);
    WRAPPING_STANDALONE_METHOD_FUNC(ConvertIndexedStringVector, STDVectorConvertStrings<Gecko::IndexedString>, Gecko);

    // TypesFantasyName.h
    WRAPPING_STANDALONE_METHOD_SIMPLE(GenerateRandomFantasyName, Gecko);
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

    // Local
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetAllTypeNames, Gecko);
}
