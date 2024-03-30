// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#include "Character/CharacterParty.h"
#include "Character/CharacterPartyItem.h"
#include "Character/CharacterPartyManager.h"
#include "Utility/Macros.h"
#include "Utility/TypesPython.h"

namespace Gecko
{

CharacterPartyManager* GetCharacterPartyManager() { return CharacterPartyManager::GetInstance(); }

};

PYBIND11_MAKE_OPAQUE(Gecko::CharacterPartyItemList);
PYBIND11_MAKE_OPAQUE(Gecko::CharacterPartyList);

PYBIND11_EMBEDDED_MODULE(GeckoCharacterParty, m)
{
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
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(TreeIndex, Gecko::CharacterPartyItem)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(Amount, Gecko::CharacterPartyItem)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(EquipCount, Gecko::CharacterPartyItem)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(ApplicableEquipmentSlots, Gecko::CharacterPartyItem)
    ;
    PyBindVector<Gecko::CharacterPartyItemList>(m, "CharacterPartyItemList");
    WRAPPING_STANDALONE_METHOD_SIMPLE(ConvertCharacterPartyItemToJsonString, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(ConvertCharacterPartyItemListToJsonString, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetCharacterPartyItemFromJsonString, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetCharacterPartyItemListFromJsonString, Gecko);

    // CHaracterParty.h
    PyBindClass<Gecko::CharacterParty>(m, "CharacterParty")
        WRAPPING_ADD_CONSTRUCTOR_SIMPLE()
        WRAPPING_ADD_METHOD_SIMPLE(RegenerateCharacterData, Gecko::CharacterParty)
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
        WRAPPING_ADD_METHOD_SIMPLE(GetMemberIndexByID, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(GetMemberIndexByTargetType, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(GetMember, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(GetCharacterIDsFromTargetType, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(GetStatusMemberCount, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(AddRandomItems, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(AddItemByLeaf, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(AddItemByIndex, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(RemoveItem, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_SIMPLE(GetItemIndexByTreeIndex, Gecko::CharacterParty)
        WRAPPING_ADD_METHOD_POLICY(GetItem, Gecko::CharacterParty, PyBindReturnRefInternal)
        WRAPPING_ADD_METHOD_SIMPLE(GetBestUnequippedItemIndex, Gecko::CharacterParty)
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
    ;
    PyBindVector<Gecko::CharacterPartyList>(m, "CharacterPartyList");
    WRAPPING_STANDALONE_METHOD_SIMPLE(ConvertCharacterPartyToJsonString, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(ConvertCharacterPartyListToJsonString, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetCharacterPartyFromJsonString, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetCharacterPartyListFromJsonString, Gecko);

    // CharacterPartyManager.h
    PyBindClass<Gecko::CharacterPartyManager>(m, "CharacterPartyManager")
        WRAPPING_ADD_METHOD_SIMPLE(LoadParty, Gecko::CharacterPartyManager)
        WRAPPING_ADD_METHOD_SIMPLE(LoadPartyFromFile, Gecko::CharacterPartyManager)
        WRAPPING_ADD_METHOD_SIMPLE(SavePartyToFile, Gecko::CharacterPartyManager)
        WRAPPING_ADD_METHOD_SIMPLE(CreateParty, Gecko::CharacterPartyManager)
        WRAPPING_ADD_METHOD_SIMPLE(UnloadParty, Gecko::CharacterPartyManager)
        WRAPPING_ADD_METHOD_SIMPLE(DoesPartyExist, Gecko::CharacterPartyManager)
        WRAPPING_ADD_METHOD_SIMPLE(SetAsCurrentAllyParty, Gecko::CharacterPartyManager)
        WRAPPING_ADD_METHOD_SIMPLE(SetAsCurrentEnemyParty, Gecko::CharacterPartyManager)
        WRAPPING_ADD_METHOD_SIMPLE(GetCurrentAllyPartyID, Gecko::CharacterPartyManager)
        WRAPPING_ADD_METHOD_SIMPLE(GetCurrentEnemyPartyID, Gecko::CharacterPartyManager)
        WRAPPING_ADD_METHOD_OVERLOADED_POLICY(GetPartyByID, Gecko::CharacterPartyManager, PyBindReturnRefInternal, const Gecko::IndexedString&)
        WRAPPING_ADD_METHOD_OVERLOADED_POLICY_CONST(GetPartyByID, Gecko::CharacterPartyManager, PyBindReturnCopy, const Gecko::IndexedString&)
        WRAPPING_ADD_METHOD_OVERLOADED_POLICY(GetPartyByType, Gecko::CharacterPartyManager, PyBindReturnRefInternal, const Gecko::IndexedString&)
        WRAPPING_ADD_METHOD_OVERLOADED_POLICY_CONST(GetPartyByType, Gecko::CharacterPartyManager, PyBindReturnCopy, const Gecko::IndexedString&)
        WRAPPING_ADD_METHOD_OVERLOADED_POLICY(GetCurrentAllyParty, Gecko::CharacterPartyManager, PyBindReturnRefInternal, )
        WRAPPING_ADD_METHOD_OVERLOADED_POLICY_CONST(GetCurrentAllyParty, Gecko::CharacterPartyManager, PyBindReturnCopy, )
        WRAPPING_ADD_METHOD_OVERLOADED_POLICY(GetCurrentEnemyParty, Gecko::CharacterPartyManager, PyBindReturnRefInternal, )
        WRAPPING_ADD_METHOD_OVERLOADED_POLICY_CONST(GetCurrentEnemyParty, Gecko::CharacterPartyManager, PyBindReturnCopy, )
    ;

    // Local
    WRAPPING_STANDALONE_METHOD_POLICY(GetCharacterPartyManager, Gecko, PyBindReturnAutoRef);
}
