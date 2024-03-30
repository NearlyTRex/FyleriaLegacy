// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

// Internal includes
#include "Skills/SkillData.h"
#include "Skills/SkillDataAffinity.h"
#include "Skills/SkillDataAlchemy.h"
#include "Skills/SkillDataBreakdown.h"
#include "Skills/SkillDataCombat.h"
#include "Skills/SkillDataCrafting.h"
#include "Skills/SkillDataWeapon.h"
#include "Skills/SkillTree.h"
#include "Utility/Macros.h"
#include "Utility/Python.h"

PYBIND11_EMBEDDED_MODULE(GeckoSkills, m)
{
    // SkillData.h
    PyBindClass<Gecko::SkillData>(m, "SkillData")
        WRAPPING_ADD_CONSTRUCTOR_SIMPLE()
        WRAPPING_ADD_METHOD_SIMPLE(Clear, Gecko::SkillData)
        WRAPPING_ADD_METHOD_SIMPLE(IsActionable, Gecko::SkillData)
        WRAPPING_ADD_METHOD_SIMPLE(DoesMeetActionRequirements, Gecko::SkillData)
        WRAPPING_ADD_BASIC_PROPERTY_READONLY_MULTIGET(DataClass, Gecko::SkillData)
        WRAPPING_ADD_BASIC_PROPERTY_READONLY_MULTIGET(SkillRank, Gecko::SkillData)
        WRAPPING_ADD_BASIC_PROPERTY_READONLY_MULTIGET(SkillName, Gecko::SkillData)
        WRAPPING_ADD_BASIC_PROPERTY_READONLY_MULTIGET(SkillDescription, Gecko::SkillData)
        WRAPPING_ADD_BASIC_PROPERTY_READONLY_MULTIGET(SkillType, Gecko::SkillData)
        WRAPPING_ADD_BASIC_PROPERTY_READONLY_MULTIGET(SkillCostAP, Gecko::SkillData)
        WRAPPING_ADD_BASIC_PROPERTY_READONLY_MULTIGET(SkillCostHP, Gecko::SkillData)
        WRAPPING_ADD_BASIC_PROPERTY_READONLY_MULTIGET(StatChanges, Gecko::SkillDataAffinity)
    ;

    // SkillDataAffinity.h
    PyBindClass<Gecko::SkillDataAffinity, Gecko::SkillData>(m, "SkillDataAffinity")
        WRAPPING_ADD_CONSTRUCTOR_SIMPLE()
        WRAPPING_ADD_METHOD_SIMPLE(Clear, Gecko::SkillDataAffinity)
        WRAPPING_ADD_BASIC_PROPERTY_READONLY_SIMPLE(TreeType, Gecko::SkillDataAffinity)
    ;
    PyBindVector<Gecko::SkillDataAffinityArray>(m, "SkillDataAffinityArray");

    // SkillDataAlchemy.h
    PyBindClass<Gecko::SkillDataAlchemy, Gecko::SkillData>(m, "SkillDataAlchemy")
        WRAPPING_ADD_CONSTRUCTOR_SIMPLE()
        WRAPPING_ADD_METHOD_SIMPLE(Clear, Gecko::SkillDataAlchemy)
        WRAPPING_ADD_BASIC_PROPERTY_READONLY_SIMPLE(TreeType, Gecko::SkillDataAlchemy)
        WRAPPING_ADD_BASIC_PROPERTY_READONLY_MULTIGET(Recipes, Gecko::SkillDataAlchemy)
    ;
    PyBindVector<Gecko::SkillDataAlchemyArray>(m, "SkillDataAlchemyArray");

    // SkillDataBreakdown.h
    PyBindClass<Gecko::SkillDataBreakdown, Gecko::SkillData>(m, "SkillDataBreakdown")
        WRAPPING_ADD_CONSTRUCTOR_SIMPLE()
        WRAPPING_ADD_METHOD_SIMPLE(Clear, Gecko::SkillDataBreakdown)
        WRAPPING_ADD_BASIC_PROPERTY_READONLY_SIMPLE(TreeType, Gecko::SkillDataBreakdown)
        WRAPPING_ADD_BASIC_PROPERTY_READONLY_MULTIGET(Recipes, Gecko::SkillDataBreakdown)
    ;
    PyBindVector<Gecko::SkillDataBreakdownArray>(m, "SkillDataBreakdownArray");

    // SkillDataCombat.h
    PyBindClass<Gecko::SkillDataCombat, Gecko::SkillData>(m, "SkillDataCombat")
        WRAPPING_ADD_CONSTRUCTOR_SIMPLE()
        WRAPPING_ADD_METHOD_SIMPLE(Clear, Gecko::SkillDataCombat)
        WRAPPING_ADD_BASIC_PROPERTY_READONLY_SIMPLE(TreeType, Gecko::SkillDataCombat)
        WRAPPING_ADD_METHOD_SIMPLE(CreateCombatActions, Gecko::SkillDataCombat)
    ;
    PyBindVector<Gecko::SkillDataCombatArray>(m, "SkillDataCombatArray");

    // SkillDataCrafting.h
    PyBindClass<Gecko::SkillDataCrafting, Gecko::SkillData>(m, "SkillDataCrafting")
        WRAPPING_ADD_CONSTRUCTOR_SIMPLE()
        WRAPPING_ADD_METHOD_SIMPLE(Clear, Gecko::SkillDataCrafting)
        WRAPPING_ADD_BASIC_PROPERTY_READONLY_SIMPLE(TreeType, Gecko::SkillDataCrafting)
        WRAPPING_ADD_BASIC_PROPERTY_READONLY_MULTIGET(Recipes, Gecko::SkillDataCrafting)
    ;
    PyBindVector<Gecko::SkillDataCraftingArray>(m, "SkillDataCraftingArray");

    // SkillDataWeapon.h
    PyBindClass<Gecko::SkillDataWeapon, Gecko::SkillData>(m, "SkillDataWeapon")
        WRAPPING_ADD_CONSTRUCTOR_SIMPLE()
        WRAPPING_ADD_METHOD_SIMPLE(Clear, Gecko::SkillDataWeapon)
        WRAPPING_ADD_METHOD_SIMPLE(CreateWeaponActions, Gecko::SkillDataWeapon)
        WRAPPING_ADD_BASIC_PROPERTY_READONLY_SIMPLE(TreeType, Gecko::SkillDataWeapon)
        WRAPPING_ADD_BASIC_PROPERTY_READONLY_MULTIGET(WeaponBaseType, Gecko::SkillDataWeapon)
        WRAPPING_ADD_BASIC_PROPERTY_READONLY_MULTIGET(ActionPoints, Gecko::SkillDataWeapon)
    ;
    PyBindVector<Gecko::SkillDataWeaponArray>(m, "SkillDataWeaponArray");

    // SkillTree.h
    PyBindClass<Gecko::SkillTree>(m, "SkillTree")
        WRAPPING_ADD_CONSTRUCTOR_SIMPLE()
        WRAPPING_ADD_METHOD_STATIC_SIMPLE(LoadSkillTreesIntoMemory, Gecko::SkillTree)
        WRAPPING_ADD_METHOD_STATIC_SIMPLE(UnloadSkillTreesFromMemory, Gecko::SkillTree)
        WRAPPING_ADD_METHOD_STATIC_SIMPLE(VerifySkillTrees, Gecko::SkillTree)
        WRAPPING_ADD_METHOD_STATIC_SIMPLE(DoesSkillDataAffinityExist, Gecko::SkillTree)
        WRAPPING_ADD_METHOD_STATIC_SIMPLE(DoesSkillDataAlchemyExist, Gecko::SkillTree)
        WRAPPING_ADD_METHOD_STATIC_SIMPLE(DoesSkillDataBreakdownExist, Gecko::SkillTree)
        WRAPPING_ADD_METHOD_STATIC_SIMPLE(DoesSkillDataCombatExist, Gecko::SkillTree)
        WRAPPING_ADD_METHOD_STATIC_SIMPLE(DoesSkillDataCraftingExist, Gecko::SkillTree)
        WRAPPING_ADD_METHOD_STATIC_SIMPLE(DoesSkillDataWeaponExist, Gecko::SkillTree)
        WRAPPING_ADD_METHOD_STATIC_POLICY(RetrieveSkillDataAffinity, Gecko::SkillTree, PyBindReturnCopy)
        WRAPPING_ADD_METHOD_STATIC_POLICY(RetrieveSkillDataAlchemy, Gecko::SkillTree, PyBindReturnCopy)
        WRAPPING_ADD_METHOD_STATIC_POLICY(RetrieveSkillDataBreakdown, Gecko::SkillTree, PyBindReturnCopy)
        WRAPPING_ADD_METHOD_STATIC_POLICY(RetrieveSkillDataCombat, Gecko::SkillTree, PyBindReturnCopy)
        WRAPPING_ADD_METHOD_STATIC_POLICY(RetrieveSkillDataCrafting, Gecko::SkillTree, PyBindReturnCopy)
        WRAPPING_ADD_METHOD_STATIC_POLICY(RetrieveSkillDataWeapon, Gecko::SkillTree, PyBindReturnCopy)
        WRAPPING_ADD_METHOD_STATIC_SIMPLE(GetAllAffinitySkills, Gecko::SkillTree)
        WRAPPING_ADD_METHOD_STATIC_SIMPLE(GetAllAlchemySkills, Gecko::SkillTree)
        WRAPPING_ADD_METHOD_STATIC_SIMPLE(GetAllBreakdownSkills, Gecko::SkillTree)
        WRAPPING_ADD_METHOD_STATIC_SIMPLE(GetAllCombatSkills, Gecko::SkillTree)
        WRAPPING_ADD_METHOD_STATIC_SIMPLE(GetAllCraftingSkills, Gecko::SkillTree)
        WRAPPING_ADD_METHOD_STATIC_SIMPLE(GetAllWeaponSkills, Gecko::SkillTree)
        WRAPPING_ADD_METHOD_STATIC_SIMPLE(GetAffinitySkills, Gecko::SkillTree)
        WRAPPING_ADD_METHOD_STATIC_SIMPLE(GetAlchemySkills, Gecko::SkillTree)
        WRAPPING_ADD_METHOD_STATIC_SIMPLE(GetBreakdownSkills, Gecko::SkillTree)
        WRAPPING_ADD_METHOD_STATIC_SIMPLE(GetCombatSkills, Gecko::SkillTree)
        WRAPPING_ADD_METHOD_STATIC_SIMPLE(GetCraftingSkills, Gecko::SkillTree)
        WRAPPING_ADD_METHOD_STATIC_SIMPLE(GetWeaponSkills, Gecko::SkillTree)
        WRAPPING_ADD_METHOD_STATIC_SIMPLE(GetSkillType, Gecko::SkillTree)
        WRAPPING_ADD_METHOD_STATIC_SIMPLE(IsBaseWeaponSkill, Gecko::SkillTree)
        WRAPPING_ADD_METHOD_STATIC_SIMPLE(IsSkillActionable, Gecko::SkillTree)
        WRAPPING_ADD_METHOD_STATIC_SIMPLE(GenerateSkillCharacterActions, Gecko::SkillTree)
        WRAPPING_ADD_METHOD_STATIC_SIMPLE(FillSkillStatChangeArrays, Gecko::SkillTree)
    ;

    // SkillTypes.h
    WRAPPING_STANDALONE_METHOD_FUNC(GetSkillTreeTypeNames, GetEnumNames<Gecko::SkillTreeType>, Gecko);
    WRAPPING_STANDALONE_METHOD_FUNC(GetSkillWeaponBaseTypeNames, GetEnumNames<Gecko::SkillWeaponBaseType>, Gecko);
    WRAPPING_STANDALONE_METHOD_FUNC(GetSkillWeaponTypeNames, GetEnumNames<Gecko::SkillWeaponType>, Gecko);
    WRAPPING_STANDALONE_METHOD_FUNC(GetSkillAlchemyTypeNames, GetEnumNames<Gecko::SkillAlchemyType>, Gecko);
    WRAPPING_STANDALONE_METHOD_FUNC(GetSkillBreakdownTypeNames, GetEnumNames<Gecko::SkillBreakdownType>, Gecko);
    WRAPPING_STANDALONE_METHOD_FUNC(GetSkillCombatTypeNames, GetEnumNames<Gecko::SkillCombatType>, Gecko);
    WRAPPING_STANDALONE_METHOD_FUNC(GetSkillCraftingTypeNames, GetEnumNames<Gecko::SkillCraftingType>, Gecko);
    WRAPPING_STANDALONE_METHOD_FUNC(GetSkillAffinityTypeNames, GetEnumNames<Gecko::SkillAffinityType>, Gecko);
}
