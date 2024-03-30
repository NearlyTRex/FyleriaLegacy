// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

// Internal includes
#include "CharacterParty/CharacterParty.h"
#include "CharacterParty/CharacterPartyItem.h"
#include "CharacterParty/CharacterPartyEquippedItem.h"
#include "CharacterParty/CharacterPartyMember.h"
#include "CharacterParty/CharacterPartyManager.h"
#include "Utility/Macros.h"
#include "Utility/Python.h"

namespace Gecko
{
    // Manager lambdas
    auto fnLoadParty = MAKE_MANAGER_RETURN_LAMBDA_A2(CharacterPartyManager, LoadParty, String, const CharacterParty&, Bool);
    auto fnLoadPartyFromFile = MAKE_MANAGER_RETURN_LAMBDA_A3(CharacterPartyManager, LoadPartyFromFile, String, const String&, const String&, Bool);
    auto fnSavePartyToFile = MAKE_MANAGER_VOID_LAMBDA_A3(CharacterPartyManager, SavePartyToFile, const String&, const String&, const String&);
    auto fnCreateParty = MAKE_MANAGER_VOID_LAMBDA_A3(CharacterPartyManager, CreateParty, const String&, const String&, Bool);
    auto fnUnloadParty = MAKE_MANAGER_VOID_LAMBDA_A1(CharacterPartyManager, UnloadParty, const String&);
    auto fnDoesPartyExistByID = MAKE_MANAGER_RETURN_LAMBDA_A1(CharacterPartyManager, DoesPartyExistByID, Bool, const String&);
    auto fnDoesPartyExistByType = MAKE_MANAGER_RETURN_LAMBDA_A1(CharacterPartyManager, DoesPartyExistByType, Bool, const String&);
    auto fnDoesPartyExistByID_StoreResult = MAKE_MANAGER_VOID_LAMBDA_A2(CharacterPartyManager, DoesPartyExistByID_StoreResult, const String&, const String&);
    auto fnDoesPartyExistByType_StoreResult = MAKE_MANAGER_VOID_LAMBDA_A2(CharacterPartyManager, DoesPartyExistByType_StoreResult, const String&, const String&);
    auto fnIsValidPartyID = MAKE_MANAGER_RETURN_LAMBDA_A1(CharacterPartyManager, IsValidPartyID, Bool, const String&);
    auto fnIsValidPartyID_StoreResult = MAKE_MANAGER_VOID_LAMBDA_A2(CharacterPartyManager, IsValidPartyID_StoreResult, const String&, const String&);
    auto fnGetPartyByID1 = MAKE_MANAGER_RETURN_LAMBDA_A1(CharacterPartyManager, GetPartyByID, const CharacterParty&, const String&);
    auto fnGetPartyByID2 = MAKE_MANAGER_RETURN_LAMBDA_A1(CharacterPartyManager, GetPartyByID, CharacterParty&, const String&);
    auto fnGetPartyByID_StoreResult = MAKE_MANAGER_VOID_LAMBDA_A2(CharacterPartyManager, GetPartyByID_StoreResult, const String&, const String&);
    auto fnGetPartyByType1 = MAKE_MANAGER_RETURN_LAMBDA_A1(CharacterPartyManager, GetPartyByType, const CharacterParty&, const String&);
    auto fnGetPartyByType2 = MAKE_MANAGER_RETURN_LAMBDA_A1(CharacterPartyManager, GetPartyByType, CharacterParty&, const String&);
    auto fnGetPartyByType_StoreResult = MAKE_MANAGER_VOID_LAMBDA_A2(CharacterPartyManager, GetPartyByType_StoreResult, const String&, const String&);
    auto fnGetCurrentAllyParty1 = MAKE_MANAGER_RETURN_LAMBDA(CharacterPartyManager, GetCurrentAllyParty, const CharacterParty&);
    auto fnGetCurrentAllyParty2 = MAKE_MANAGER_RETURN_LAMBDA(CharacterPartyManager, GetCurrentAllyParty, CharacterParty&);
    auto fnGetCurrentAllyParty_StoreResult = MAKE_MANAGER_VOID_LAMBDA_A1(CharacterPartyManager, GetCurrentAllyParty_StoreResult, const String&);
    auto fnGetCurrentEnemyParty1 = MAKE_MANAGER_RETURN_LAMBDA(CharacterPartyManager, GetCurrentEnemyParty, const CharacterParty&);
    auto fnGetCurrentEnemyParty2 = MAKE_MANAGER_RETURN_LAMBDA(CharacterPartyManager, GetCurrentEnemyParty, CharacterParty&);
    auto fnGetCurrentEnemyParty_StoreResult = MAKE_MANAGER_VOID_LAMBDA_A1(CharacterPartyManager, GetCurrentEnemyParty_StoreResult, const String&);
    auto fnGetAllPartyIDs = MAKE_MANAGER_RETURN_LAMBDA(CharacterPartyManager, GetAllPartyIDs, StringArray);
    auto fnGetAllPartyIDs_StoreResult = MAKE_MANAGER_VOID_LAMBDA_A1(CharacterPartyManager, GetAllPartyIDs_StoreResult, const String&);
    auto fnGetCurrentAllyPartyID = MAKE_MANAGER_RETURN_LAMBDA(CharacterPartyManager, GetCurrentAllyPartyID, String&);
    auto fnSetCurrentAllyPartyID = MAKE_MANAGER_VOID_LAMBDA_A1(CharacterPartyManager, SetCurrentAllyPartyID, const String&);
    auto fnGetCurrentEnemyPartyID = MAKE_MANAGER_RETURN_LAMBDA(CharacterPartyManager, GetCurrentEnemyPartyID, String&);
    auto fnSetCurrentEnemyPartyID = MAKE_MANAGER_VOID_LAMBDA_A1(CharacterPartyManager, SetCurrentEnemyPartyID, const String&);
}

PYBIND11_MAKE_OPAQUE(Gecko::CharacterPartyItemArray);
PYBIND11_MAKE_OPAQUE(Gecko::CharacterPartyArray);

PYBIND11_EMBEDDED_MODULE(GeckoCharacterParty, m)
{
    // CharacterParty.h
    PyBindClass<Gecko::CharacterParty>(m, "CharacterParty")
        WRAPPING_ADD_CONSTRUCTOR_SIMPLE()
        WRAPPING_ADD_METHOD_SIMPLE(RegenerateCharacterData, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(IsPartyAbleToFight, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(IsPartyFull, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(IsMemberPresent, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(IsTargetTypeAvailable, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(IsTargetTypeTaken, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(AddMember, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(RemoveMember, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(MoveMember, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(SwapMembers, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(GetNextAvailableTargetType, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(UseTargetType, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(FreeTargetType, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_OVERLOADED_POLICY_CONST(GetMemberByID, Gecko::CharacterParty, PyBindReturnCopy, const Gecko::String&)
        WRAPPING_ADD_METHOD_OVERLOADED_POLICY(GetMemberByID, Gecko::CharacterParty, PyBindReturnRefInternal, const Gecko::String&)
        WRAPPING_ADD_METHOD_OVERLOADED_POLICY_CONST(GetMemberByTargetType, Gecko::CharacterParty, PyBindReturnCopy, const Gecko::String&)
        WRAPPING_ADD_METHOD_OVERLOADED_POLICY(GetMemberByTargetType, Gecko::CharacterParty, PyBindReturnRefInternal, const Gecko::String&)
        WRAPPING_ADD_METHOD_SIMPLE(GetMemberCharacterIDs, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(GetCharacterIDsFromTargetType, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(GetStatusMemberCount, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(AddRandomItems, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(AddItemByLeaf, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(AddItemByTreeIndex, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(RemoveItemByLeaf, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(RemoveItemByTreeIndex, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_OVERLOADED_POLICY_CONST(GetItemByLeaf, Gecko::CharacterParty, PyBindReturnCopy, const Gecko::String&)
        WRAPPING_ADD_METHOD_OVERLOADED_POLICY(GetItemByLeaf, Gecko::CharacterParty, PyBindReturnRefInternal, const Gecko::String&)
        WRAPPING_ADD_METHOD_OVERLOADED_POLICY_CONST(GetItemByTreeIndex, Gecko::CharacterParty, PyBindReturnCopy, const Gecko::TreeIndex&)
        WRAPPING_ADD_METHOD_OVERLOADED_POLICY(GetItemByTreeIndex, Gecko::CharacterParty, PyBindReturnRefInternal, const Gecko::TreeIndex&)
        WRAPPING_ADD_METHOD_SIMPLE(GetBestUnequippedItem, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(EquipItem, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(UnequipItem, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(EquipBestItems, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(EquipBestItemsForAllMembers, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(UnequipAllItems, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(UnequipAllItemsForAllMembers, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(GetMemberCount, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(GetItemCount, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(GetDescription, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(ResetPlayTime, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(PausePlayTime, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(ResumePlayTime, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(GetPlayTime, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(SetPlayTime, Gecko::CharacterParty)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(PartyID, Gecko::CharacterParty)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(PartyType, Gecko::CharacterParty)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(Members, Gecko::CharacterParty)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(Items, Gecko::CharacterParty)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(AvailableTargetTypes, Gecko::CharacterParty)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(TakenTargetTypes, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(IsPartyAbleToFight_StoreResult, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(IsPartyFull_StoreResult, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(IsMemberPresent_StoreResult, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(IsTargetTypeAvailable_StoreResult, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(IsTargetTypeTaken_StoreResult, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(AddMember_StoreResult, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(RemoveMember_StoreResult, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(MoveMember_StoreResult, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(SwapMembers_StoreResult, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(GetNextAvailableTargetType_StoreResult, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(UseTargetType_StoreResult, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(FreeTargetType_StoreResult, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(GetMemberByID_StoreResult, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(GetMemberByTargetType_StoreResult, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(GetMemberCharacterIDs_StoreResult, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(GetCharacterIDsFromTargetType_StoreResult, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(GetStatusMemberCount_StoreResult, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(AddRandomItems_StoreResult, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(AddItemByLeaf_StoreResult, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(AddItemByTreeIndex_StoreResult, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(RemoveItemByLeaf_StoreResult, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(RemoveItemByTreeIndex_StoreResult, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(GetItemByLeaf_StoreResult, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(GetItemByTreeIndex_StoreResult, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(GetBestUnequippedItem_StoreResult, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(EquipItem_StoreResult, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(UnequipItem_StoreResult, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(EquipBestItems_StoreResult, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(EquipBestItemsForAllMembers_StoreResult, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(UnequipAllItems_StoreResult, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(UnequipAllItemsForAllMembers_StoreResult, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(GetMemberCount_StoreResult, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(GetItemCount_StoreResult, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(GetDescription_StoreResult, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(GetPlayTime_StoreResult, Gecko::CharacterParty)
    ;
    PyBindVector<Gecko::CharacterPartyArray>(m, "CharacterPartyArray");

    // CharacterPartyItem.h
    PyBindClass<Gecko::CharacterPartyItem>(m, "CharacterPartyItem")
        WRAPPING_ADD_CONSTRUCTOR_SIMPLE()
        WRAPPING_ADD_METHOD_SIMPLE(DoesMatchSlot, Gecko::CharacterPartyItem)
        WRAPPING_ADD_METHOD_SIMPLE(CanAddAmount, Gecko::CharacterPartyItem)
        WRAPPING_ADD_METHOD_SIMPLE(CanRemoveAmount, Gecko::CharacterPartyItem)
        WRAPPING_ADD_METHOD_SIMPLE(CanEquipAmount, Gecko::CharacterPartyItem)
        WRAPPING_ADD_METHOD_SIMPLE(CanUnequipAmount, Gecko::CharacterPartyItem)
        WRAPPING_ADD_METHOD_SIMPLE(AddAmount, Gecko::CharacterPartyItem)
        WRAPPING_ADD_METHOD_SIMPLE(RemoveAmount, Gecko::CharacterPartyItem)
        WRAPPING_ADD_METHOD_SIMPLE(EquipAmount, Gecko::CharacterPartyItem)
        WRAPPING_ADD_METHOD_SIMPLE(UnequipAmount, Gecko::CharacterPartyItem)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(ItemTreeIndex, Gecko::CharacterPartyItem)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(ItemAmount, Gecko::CharacterPartyItem)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(EquipCount, Gecko::CharacterPartyItem)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(ApplicableEquipmentSlots, Gecko::CharacterPartyItem)
    ;
    PyBindVector<Gecko::CharacterPartyItemArray>(m, "CharacterPartyItemArray");

    // CharacterPartyEquippedItem.h
    PyBindClass<Gecko::CharacterPartyEquippedItem>(m, "CharacterPartyEquippedItem")
        WRAPPING_ADD_CONSTRUCTOR_SIMPLE()
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(ItemTreeIndex, Gecko::CharacterPartyEquippedItem)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(ItemSlot, Gecko::CharacterPartyEquippedItem)
    ;
    PyBindVector<Gecko::CharacterPartyEquippedItemArray>(m, "CharacterPartyEquippedItemArray");

    // CharacterPartyMember.h
    PyBindClass<Gecko::CharacterPartyMember>(m, "CharacterPartyMember")
        WRAPPING_ADD_CONSTRUCTOR_SIMPLE()
        WRAPPING_ADD_METHOD_SIMPLE(GetEquippedItemTypeCount, Gecko::CharacterPartyMember)
        WRAPPING_ADD_METHOD_SIMPLE(GetEquippedWeaponCount, Gecko::CharacterPartyMember)
        WRAPPING_ADD_METHOD_SIMPLE(GetEquippedShieldCount, Gecko::CharacterPartyMember)
        WRAPPING_ADD_METHOD_SIMPLE(CanAddEquippedItem, Gecko::CharacterPartyMember)
        WRAPPING_ADD_METHOD_SIMPLE(CanRemoveEquippedItem, Gecko::CharacterPartyMember)
        WRAPPING_ADD_METHOD_SIMPLE(AddEquippedItem, Gecko::CharacterPartyMember)
        WRAPPING_ADD_METHOD_SIMPLE(RemoveEquippedItem, Gecko::CharacterPartyMember)
        WRAPPING_ADD_METHOD_SIMPLE(GetHandInfoByWeaponSet, Gecko::CharacterPartyMember)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(EquippedItems, Gecko::CharacterPartyMember)
    ;
    PyBindVector<Gecko::CharacterPartyMemberArray>(m, "CharacterPartyMemberArray");

    // CharacterPartyManager.h
    WRAPPING_STANDALONE_LAMBDA(LoadParty, Gecko::fnLoadParty);
    WRAPPING_STANDALONE_LAMBDA(LoadPartyFromFile, Gecko::fnLoadPartyFromFile);
    WRAPPING_STANDALONE_LAMBDA(SavePartyToFile, Gecko::fnSavePartyToFile);
    WRAPPING_STANDALONE_LAMBDA(CreateParty, Gecko::fnCreateParty);
    WRAPPING_STANDALONE_LAMBDA(UnloadParty, Gecko::fnUnloadParty);
    WRAPPING_STANDALONE_LAMBDA(DoesPartyExistByID, Gecko::fnDoesPartyExistByID);
    WRAPPING_STANDALONE_LAMBDA(DoesPartyExistByType, Gecko::fnDoesPartyExistByType);
    WRAPPING_STANDALONE_LAMBDA(DoesPartyExistByID_StoreResult, Gecko::fnDoesPartyExistByID_StoreResult);
    WRAPPING_STANDALONE_LAMBDA(DoesPartyExistByType_StoreResult, Gecko::fnDoesPartyExistByType_StoreResult);
    WRAPPING_STANDALONE_LAMBDA(IsValidPartyID, Gecko::fnIsValidPartyID);
    WRAPPING_STANDALONE_LAMBDA(IsValidPartyID_StoreResult, Gecko::fnIsValidPartyID_StoreResult);
    WRAPPING_STANDALONE_LAMBDA_POLICY(GetPartyByID, Gecko::fnGetPartyByID1, PyBindReturnCopy);
    WRAPPING_STANDALONE_LAMBDA_POLICY(GetPartyByID, Gecko::fnGetPartyByID2, PyBindReturnRefInternal);
    WRAPPING_STANDALONE_LAMBDA(GetPartyByID_StoreResult, Gecko::fnGetPartyByID_StoreResult);
    WRAPPING_STANDALONE_LAMBDA_POLICY(GetPartyByType, Gecko::fnGetPartyByType1, PyBindReturnCopy);
    WRAPPING_STANDALONE_LAMBDA_POLICY(GetPartyByType, Gecko::fnGetPartyByType2, PyBindReturnRefInternal);
    WRAPPING_STANDALONE_LAMBDA(GetPartyByType_StoreResult, Gecko::fnGetPartyByType_StoreResult);
    WRAPPING_STANDALONE_LAMBDA_POLICY(GetCurrentAllyParty, Gecko::fnGetCurrentAllyParty1, PyBindReturnCopy);
    WRAPPING_STANDALONE_LAMBDA_POLICY(GetCurrentAllyParty, Gecko::fnGetCurrentAllyParty2, PyBindReturnRefInternal);
    WRAPPING_STANDALONE_LAMBDA(GetCurrentAllyParty_StoreResult, Gecko::fnGetCurrentAllyParty_StoreResult);
    WRAPPING_STANDALONE_LAMBDA_POLICY(GetCurrentEnemyParty, Gecko::fnGetCurrentEnemyParty1, PyBindReturnCopy);
    WRAPPING_STANDALONE_LAMBDA_POLICY(GetCurrentEnemyParty, Gecko::fnGetCurrentEnemyParty2, PyBindReturnRefInternal);
    WRAPPING_STANDALONE_LAMBDA(GetCurrentEnemyParty_StoreResult, Gecko::fnGetCurrentEnemyParty_StoreResult);
    WRAPPING_STANDALONE_LAMBDA(GetAllPartyIDs, Gecko::fnGetAllPartyIDs);
    WRAPPING_STANDALONE_LAMBDA(GetAllPartyIDs_StoreResult, Gecko::fnGetAllPartyIDs_StoreResult);
    WRAPPING_STANDALONE_LAMBDA_POLICY(GetCurrentAllyPartyID, Gecko::fnGetCurrentAllyPartyID, PyBindReturnRefInternal);
    WRAPPING_STANDALONE_LAMBDA(SetCurrentAllyPartyID, Gecko::fnSetCurrentAllyPartyID);
    WRAPPING_STANDALONE_LAMBDA_POLICY(GetCurrentEnemyPartyID, Gecko::fnGetCurrentEnemyPartyID, PyBindReturnRefInternal);
    WRAPPING_STANDALONE_LAMBDA(SetCurrentEnemyPartyID, Gecko::fnSetCurrentEnemyPartyID);
}
