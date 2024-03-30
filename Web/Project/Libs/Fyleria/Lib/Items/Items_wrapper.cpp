// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#include "Items/ItemDataArmor.h"
#include "Items/ItemDataIngredient.h"
#include "Items/ItemDataPotion.h"
#include "Items/ItemDataWeapon.h"
#include "Items/ItemTree.h"
#include "Utility/TypesPython.h"

PYBIND11_EMBEDDED_MODULE(GeckoItems, m)
{
    // ItemData.h
    PyBindClass<Gecko::ItemData>(m, "ItemData")
        WRAPPING_ADD_CONSTRUCTOR_SIMPLE()
        WRAPPING_ADD_BASIC_PROPERTY_READONLY_MULTIGET(DataClass, Gecko::ItemData)
        WRAPPING_ADD_BASIC_PROPERTY_READONLY_MULTIGET(ItemName, Gecko::ItemData)
        WRAPPING_ADD_BASIC_PROPERTY_READONLY_MULTIGET(ItemDescription, Gecko::ItemData)
        WRAPPING_ADD_BASIC_PROPERTY_READONLY_MULTIGET(ItemType, Gecko::ItemData)
    ;

    // ItemDataArmor.h
    PyBindClass<Gecko::ItemDataArmor, Gecko::ItemData>(m, "ItemDataArmor")
        WRAPPING_ADD_CONSTRUCTOR_SIMPLE()
        WRAPPING_ADD_BASIC_PROPERTY_READONLY_SIMPLE(TreeType, Gecko::ItemDataArmor)
        WRAPPING_ADD_BASIC_PROPERTY_READONLY_SIMPLE(BluntDefendPercent, Gecko::ItemDataArmor)
        WRAPPING_ADD_BASIC_PROPERTY_READONLY_SIMPLE(PierceDefendPercent, Gecko::ItemDataArmor)
        WRAPPING_ADD_BASIC_PROPERTY_READONLY_SIMPLE(SlashDefendPercent, Gecko::ItemDataArmor)
        WRAPPING_ADD_BASIC_PROPERTY_READONLY_SIMPLE(MagicDefendPercent, Gecko::ItemDataArmor)
        WRAPPING_ADD_BASIC_PROPERTY_READONLY_MULTIGET(StatChanges, Gecko::ItemDataArmor)
    ;
    PyBindVector<Gecko::ItemDataArmorList>(m, "ItemDataArmorList");
    WRAPPING_STANDALONE_METHOD_SIMPLE(ConvertItemDataArmorToJsonString, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(ConvertItemDataArmorListToJsonString, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetItemDataArmorFromJsonString, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetItemDataArmorListFromJsonString, Gecko);

    // ItemDataIngredient.h
    PyBindClass<Gecko::ItemDataIngredient, Gecko::ItemData>(m, "ItemDataIngredient")
        WRAPPING_ADD_CONSTRUCTOR_SIMPLE()
        WRAPPING_ADD_BASIC_PROPERTY_READONLY_SIMPLE(TreeType, Gecko::ItemDataIngredient)
        WRAPPING_ADD_BASIC_PROPERTY_READONLY_MULTIGET(StatChanges, Gecko::ItemDataIngredient)
    ;
    PyBindVector<Gecko::ItemDataIngredientList>(m, "ItemDataIngredientList");
    WRAPPING_STANDALONE_METHOD_SIMPLE(ConvertItemDataIngredientToJsonString, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(ConvertItemDataIngredientListToJsonString, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetItemDataIngredientFromJsonString, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetItemDataIngredientListFromJsonString, Gecko);

    // ItemDataPotion.h
    PyBindClass<Gecko::ItemDataPotion, Gecko::ItemData>(m, "ItemDataPotion")
        WRAPPING_ADD_CONSTRUCTOR_SIMPLE()
        WRAPPING_ADD_BASIC_PROPERTY_READONLY_SIMPLE(TreeType, Gecko::ItemDataPotion)
        WRAPPING_ADD_BASIC_PROPERTY_READONLY_MULTIGET(StatChanges, Gecko::ItemDataPotion)
    ;
    PyBindVector<Gecko::ItemDataPotionList>(m, "ItemDataPotionList");
    WRAPPING_STANDALONE_METHOD_SIMPLE(ConvertItemDataPotionToJsonString, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(ConvertItemDataPotionListToJsonString, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetItemDataPotionFromJsonString, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetItemDataPotionListFromJsonString, Gecko);

    // ItemDataWeapon.h
    PyBindClass<Gecko::ItemDataWeapon, Gecko::ItemData>(m, "ItemDataWeapon")
        WRAPPING_ADD_CONSTRUCTOR_SIMPLE()
        WRAPPING_ADD_BASIC_PROPERTY_READONLY_SIMPLE(TreeType, Gecko::ItemDataWeapon)
        WRAPPING_ADD_BASIC_PROPERTY_READONLY_SIMPLE(BluntAttackPercent, Gecko::ItemDataWeapon)
        WRAPPING_ADD_BASIC_PROPERTY_READONLY_SIMPLE(PierceAttackPercent, Gecko::ItemDataWeapon)
        WRAPPING_ADD_BASIC_PROPERTY_READONLY_SIMPLE(SlashAttackPercent, Gecko::ItemDataWeapon)
        WRAPPING_ADD_BASIC_PROPERTY_READONLY_MULTIGET(StatChanges, Gecko::ItemDataWeapon)
    ;
    PyBindVector<Gecko::ItemDataWeaponList>(m, "ItemDataWeaponList");
    WRAPPING_STANDALONE_METHOD_SIMPLE(ConvertItemDataWeaponToJsonString, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(ConvertItemDataWeaponListToJsonString, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetItemDataWeaponFromJsonString, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetItemDataWeaponListFromJsonString, Gecko);

    // ItemTree.h
    WRAPPING_STANDALONE_METHOD_SIMPLE(LoadItemTreesIntoMemory, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(UnloadItemTreesFromMemory, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(VerifyItemTrees, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(DoesItemDataExist, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(DoesItemDataArmorExist, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(DoesItemDataIngredientExist, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(DoesItemDataPotionExist, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(DoesItemDataWeaponExist, Gecko);
    WRAPPING_STANDALONE_METHOD_POLICY(RetrieveItemDataArmor, Gecko, PyBindReturnCopy);
    WRAPPING_STANDALONE_METHOD_POLICY(RetrieveItemDataIngredient, Gecko, PyBindReturnCopy);
    WRAPPING_STANDALONE_METHOD_POLICY(RetrieveItemDataPotion, Gecko, PyBindReturnCopy);
    WRAPPING_STANDALONE_METHOD_POLICY(RetrieveItemDataWeapon, Gecko, PyBindReturnCopy);
    WRAPPING_STANDALONE_METHOD_SIMPLE(RetrieveItemType, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetAllArmorItems, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetAllIngredientItems, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetAllPotionItems, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetAllWeaponItems, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetAllEquippedItems, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(ResolveItemLeafIntoIndex, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(IsItemActionable, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GenerateItemCharacterActions, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(IsArmorBetter, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(IsWeaponBetter, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(IsItemWeapon, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(IsItemShield, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetActionTypes, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(FillItemStatChangeLists, Gecko);

    // ItemTypes.h
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetItemTreeTypeNames, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetItemTypeNames, Gecko);
}
