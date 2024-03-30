// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

// Internal includes
#include "Items/ItemDataArmor.h"
#include "Items/ItemDataIngredient.h"
#include "Items/ItemDataPotion.h"
#include "Items/ItemDataWeapon.h"
#include "Items/ItemTree.h"
#include "Utility/Python.h"

PYBIND11_EMBEDDED_MODULE(GeckoItems, m)
{
    // ItemData.h
    PyBindClass<Gecko::ItemData>(m, "ItemData")
        WRAPPING_ADD_CONSTRUCTOR_SIMPLE()
        WRAPPING_ADD_METHOD_SIMPLE(Clear, Gecko::ItemData)
        WRAPPING_ADD_BASIC_PROPERTY_READONLY_MULTIGET(DataClass, Gecko::ItemData)
        WRAPPING_ADD_BASIC_PROPERTY_READONLY_MULTIGET(ItemName, Gecko::ItemData)
        WRAPPING_ADD_BASIC_PROPERTY_READONLY_MULTIGET(ItemDescription, Gecko::ItemData)
        WRAPPING_ADD_BASIC_PROPERTY_READONLY_MULTIGET(ItemType, Gecko::ItemData)
    ;

    // ItemDataArmor.h
    PyBindClass<Gecko::ItemDataArmor, Gecko::ItemData>(m, "ItemDataArmor")
        WRAPPING_ADD_CONSTRUCTOR_SIMPLE()
        WRAPPING_ADD_METHOD_SIMPLE(Clear, Gecko::ItemDataArmor)
        WRAPPING_ADD_BASIC_PROPERTY_READONLY_SIMPLE(TreeType, Gecko::ItemDataArmor)
        WRAPPING_ADD_BASIC_PROPERTY_READONLY_MULTIGET(BluntDefendPercent, Gecko::ItemDataArmor)
        WRAPPING_ADD_BASIC_PROPERTY_READONLY_MULTIGET(PierceDefendPercent, Gecko::ItemDataArmor)
        WRAPPING_ADD_BASIC_PROPERTY_READONLY_MULTIGET(SlashDefendPercent, Gecko::ItemDataArmor)
        WRAPPING_ADD_BASIC_PROPERTY_READONLY_MULTIGET(MagicDefendPercent, Gecko::ItemDataArmor)
        WRAPPING_ADD_BASIC_PROPERTY_READONLY_MULTIGET(StatChanges, Gecko::ItemDataArmor)
    ;
    PyBindVector<Gecko::ItemDataArmorArray>(m, "ItemDataArmorArray");

    // ItemDataIngredient.h
    PyBindClass<Gecko::ItemDataIngredient, Gecko::ItemData>(m, "ItemDataIngredient")
        WRAPPING_ADD_CONSTRUCTOR_SIMPLE()
        WRAPPING_ADD_METHOD_SIMPLE(Clear, Gecko::ItemDataIngredient)
        WRAPPING_ADD_BASIC_PROPERTY_READONLY_SIMPLE(TreeType, Gecko::ItemDataIngredient)
        WRAPPING_ADD_BASIC_PROPERTY_READONLY_MULTIGET(StatChanges, Gecko::ItemDataIngredient)
    ;
    PyBindVector<Gecko::ItemDataIngredientArray>(m, "ItemDataIngredientArray");

    // ItemDataPotion.h
    PyBindClass<Gecko::ItemDataPotion, Gecko::ItemData>(m, "ItemDataPotion")
        WRAPPING_ADD_CONSTRUCTOR_SIMPLE()
        WRAPPING_ADD_METHOD_SIMPLE(Clear, Gecko::ItemDataPotion)
        WRAPPING_ADD_BASIC_PROPERTY_READONLY_SIMPLE(TreeType, Gecko::ItemDataPotion)
        WRAPPING_ADD_BASIC_PROPERTY_READONLY_MULTIGET(StatChanges, Gecko::ItemDataPotion)
    ;
    PyBindVector<Gecko::ItemDataPotionArray>(m, "ItemDataPotionArray");

    // ItemDataWeapon.h
    PyBindClass<Gecko::ItemDataWeapon, Gecko::ItemData>(m, "ItemDataWeapon")
        WRAPPING_ADD_CONSTRUCTOR_SIMPLE()
        WRAPPING_ADD_METHOD_SIMPLE(Clear, Gecko::ItemDataWeapon)
        WRAPPING_ADD_BASIC_PROPERTY_READONLY_SIMPLE(TreeType, Gecko::ItemDataWeapon)
        WRAPPING_ADD_BASIC_PROPERTY_READONLY_MULTIGET(BluntAttackPercent, Gecko::ItemDataWeapon)
        WRAPPING_ADD_BASIC_PROPERTY_READONLY_MULTIGET(PierceAttackPercent, Gecko::ItemDataWeapon)
        WRAPPING_ADD_BASIC_PROPERTY_READONLY_MULTIGET(SlashAttackPercent, Gecko::ItemDataWeapon)
        WRAPPING_ADD_BASIC_PROPERTY_READONLY_MULTIGET(StatChanges, Gecko::ItemDataWeapon)
    ;
    PyBindVector<Gecko::ItemDataWeaponArray>(m, "ItemDataWeaponArray");

    // ItemTree.h
    PyBindClass<Gecko::ItemTree>(m, "ItemTree")
        WRAPPING_ADD_CONSTRUCTOR_SIMPLE()
        WRAPPING_ADD_METHOD_STATIC_SIMPLE(LoadItemTreesIntoMemory, Gecko::ItemTree)
        WRAPPING_ADD_METHOD_STATIC_SIMPLE(UnloadItemTreesFromMemory, Gecko::ItemTree)
        WRAPPING_ADD_METHOD_STATIC_SIMPLE(VerifyItemTrees, Gecko::ItemTree)
        WRAPPING_ADD_METHOD_STATIC_SIMPLE(DoesItemDataExist, Gecko::ItemTree)
        WRAPPING_ADD_METHOD_STATIC_SIMPLE(DoesItemDataArmorExist, Gecko::ItemTree)
        WRAPPING_ADD_METHOD_STATIC_SIMPLE(DoesItemDataIngredientExist, Gecko::ItemTree)
        WRAPPING_ADD_METHOD_STATIC_SIMPLE(DoesItemDataPotionExist, Gecko::ItemTree)
        WRAPPING_ADD_METHOD_STATIC_SIMPLE(DoesItemDataWeaponExist, Gecko::ItemTree)
        WRAPPING_ADD_METHOD_STATIC_POLICY(RetrieveItemDataArmor, Gecko::ItemTree, PyBindReturnCopy)
        WRAPPING_ADD_METHOD_STATIC_POLICY(RetrieveItemDataIngredient, Gecko::ItemTree, PyBindReturnCopy)
        WRAPPING_ADD_METHOD_STATIC_POLICY(RetrieveItemDataPotion, Gecko::ItemTree, PyBindReturnCopy)
        WRAPPING_ADD_METHOD_STATIC_POLICY(RetrieveItemDataWeapon, Gecko::ItemTree, PyBindReturnCopy)
        WRAPPING_ADD_METHOD_STATIC_SIMPLE(RetrieveItemType, Gecko::ItemTree)
        WRAPPING_ADD_METHOD_STATIC_SIMPLE(GetAllArmorItems, Gecko::ItemTree)
        WRAPPING_ADD_METHOD_STATIC_SIMPLE(GetAllIngredientItems, Gecko::ItemTree)
        WRAPPING_ADD_METHOD_STATIC_SIMPLE(GetAllPotionItems, Gecko::ItemTree)
        WRAPPING_ADD_METHOD_STATIC_SIMPLE(GetAllWeaponItems, Gecko::ItemTree)
        WRAPPING_ADD_METHOD_STATIC_SIMPLE(GetAllEquippedItems, Gecko::ItemTree)
        WRAPPING_ADD_METHOD_STATIC_SIMPLE(ResolveItemLeafIntoIndex, Gecko::ItemTree)
        WRAPPING_ADD_METHOD_STATIC_SIMPLE(IsItemActionable, Gecko::ItemTree)
        WRAPPING_ADD_METHOD_STATIC_SIMPLE(GenerateItemCharacterActions, Gecko::ItemTree)
        WRAPPING_ADD_METHOD_STATIC_SIMPLE(IsArmorBetter, Gecko::ItemTree)
        WRAPPING_ADD_METHOD_STATIC_SIMPLE(IsWeaponBetter, Gecko::ItemTree)
        WRAPPING_ADD_METHOD_STATIC_SIMPLE(IsItemWeapon, Gecko::ItemTree)
        WRAPPING_ADD_METHOD_STATIC_SIMPLE(IsItemShield, Gecko::ItemTree)
        WRAPPING_ADD_METHOD_STATIC_SIMPLE(GetActionTypes, Gecko::ItemTree)
        WRAPPING_ADD_METHOD_STATIC_SIMPLE(FillItemStatChangeArrays, Gecko::ItemTree)
    ;

    // ItemTypes.h
    WRAPPING_STANDALONE_METHOD_FUNC(GetItemTreeTypeNames, GetEnumNames<Gecko::ItemTreeType>, Gecko);
    WRAPPING_STANDALONE_METHOD_FUNC(GetItemTypeNames, GetEnumNames<Gecko::ItemType>, Gecko);
}
