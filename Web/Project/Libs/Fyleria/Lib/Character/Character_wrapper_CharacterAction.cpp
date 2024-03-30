// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#include "Character/CharacterAction.h"
#include "Character/CharacterActionBattleItem.h"
#include "Character/CharacterActionBattleSkill.h"
#include "Character/CharacterActionFieldItem.h"
#include "Character/CharacterActionFieldSkill.h"
#include "Character/CharacterActionResult.h"
#include "Utility/Macros.h"
#include "Utility/TypesPython.h"

PYBIND11_MAKE_OPAQUE(Gecko::CharacterActionResultList);
PYBIND11_MAKE_OPAQUE(Gecko::CharacterActionEntryList);
PYBIND11_MAKE_OPAQUE(Gecko::CharacterActionList);

PYBIND11_EMBEDDED_MODULE(GeckoCharacterAction, m)
{
    // CharacterActionResult.h
    PyBindClass<Gecko::CharacterActionResult>(m, "CharacterActionResult")
        WRAPPING_ADD_CONSTRUCTOR_SIMPLE()
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(FinalDamage, Gecko::CharacterActionResult)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(HasTargetDefendedSuccessfully, Gecko::CharacterActionResult)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(HaveMultipleAttacksSucceeded, Gecko::CharacterActionResult)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(NumAttacksOnTarget, Gecko::CharacterActionResult)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(IndividualAttackIsCriticalCausedList, Gecko::CharacterActionResult)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(IndividualAttackIsCriticalBlockedList, Gecko::CharacterActionResult)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(IndividualAttackTargetDamageList, Gecko::CharacterActionResult)
    ;
    PyBindVector<Gecko::CharacterActionResultList>(m, "CharacterActionResultList");
    WRAPPING_STANDALONE_METHOD_SIMPLE(ConvertCharacterActionResultToJsonString, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(ConvertCharacterActionResultListToJsonString, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetCharacterActionResultFromJsonString, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetCharacterActionResultListFromJsonString, Gecko);

    // CharacterActionEntry.h
    PyBindClass<Gecko::CharacterActionEntry>(m, "CharacterActionEntry")
        WRAPPING_ADD_CONSTRUCTOR_SIMPLE()
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(ActionTypes, Gecko::CharacterActionEntry)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(HandType, Gecko::CharacterActionEntry)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(IsHandTypeShield, Gecko::CharacterActionEntry)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(DestinationTargetType, Gecko::CharacterActionEntry)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(DestinationCharacterID, Gecko::CharacterActionEntry)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(Result, Gecko::CharacterActionEntry)
    ;
    PyBindVector<Gecko::CharacterActionEntryList>(m, "CharacterActionEntryList");
    WRAPPING_STANDALONE_METHOD_SIMPLE(ConvertCharacterActionEntryToJsonString, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(ConvertCharacterActionEntryListToJsonString, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetCharacterActionEntryFromJsonString, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetCharacterActionEntryListFromJsonString, Gecko);

    // CharacterAction.h
    PyBindClass<Gecko::CharacterAction, STDSharedPtr<Gecko::CharacterAction>>(m, "CharacterAction")
        WRAPPING_ADD_METHOD_SIMPLE(GetAllCharacterIDs, Gecko::CharacterAction)
        WRAPPING_ADD_METHOD_SIMPLE(GetAllActionTypes, Gecko::CharacterAction)
        WRAPPING_ADD_METHOD_SIMPLE(GetAllDestinationTargetTypes, Gecko::CharacterAction)
        WRAPPING_ADD_METHOD_SIMPLE(AreAllCharacterIDsValid, Gecko::CharacterAction)
        WRAPPING_ADD_METHOD_SIMPLE(PrepareCharacterIDs, Gecko::CharacterAction)
        WRAPPING_ADD_METHOD_SIMPLE(Setup, Gecko::CharacterAction)
        WRAPPING_ADD_METHOD_SIMPLE(Finish, Gecko::CharacterAction)
        WRAPPING_ADD_METHOD_SIMPLE(GenerateResult, Gecko::CharacterAction)
        WRAPPING_ADD_METHOD_SIMPLE(ApplyResult, Gecko::CharacterAction)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(RunType, Gecko::CharacterAction)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(Order, Gecko::CharacterAction)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(CostAP, Gecko::CharacterAction)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(CostHP, Gecko::CharacterAction)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(CostMP, Gecko::CharacterAction)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(CostEP, Gecko::CharacterAction)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(WeaponSet, Gecko::CharacterAction)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(PreviousActionTypes, Gecko::CharacterAction)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(SkillTreeIndex, Gecko::CharacterAction)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(ItemTreeIndex, Gecko::CharacterAction)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(ItemAmount, Gecko::CharacterAction)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(SourceTargetType, Gecko::CharacterAction)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(SourceCharacterID, Gecko::CharacterAction)
    ;
    PyBindVector<Gecko::CharacterActionList>(m, "CharacterActionList");
    PyBindVector<Gecko::CharacterActionSharedPtrList>(m, "CharacterActionSharedPtrList");
    WRAPPING_STANDALONE_METHOD_SIMPLE(ConvertCharacterActionToJsonString, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(ConvertCharacterActionListToJsonString, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetCharacterActionFromJsonString, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetCharacterActionListFromJsonString, Gecko);

    PyBindClass<Gecko::CharacterActionBattleItem, Gecko::CharacterAction, STDSharedPtr<Gecko::CharacterActionBattleItem>>(m, "CharacterActionBattleItem")
        WRAPPING_ADD_CONSTRUCTOR_SIMPLE()
    ;

    PyBindClass<Gecko::CharacterActionBattleSkill, Gecko::CharacterAction, STDSharedPtr<Gecko::CharacterActionBattleSkill>>(m, "CharacterActionBattleSkill")
        WRAPPING_ADD_CONSTRUCTOR_SIMPLE()
    ;

    PyBindClass<Gecko::CharacterActionFieldItem, Gecko::CharacterActionBattleItem, STDSharedPtr<Gecko::CharacterActionFieldItem>>(m, "CharacterActionFieldItem")
        WRAPPING_ADD_CONSTRUCTOR_SIMPLE()
    ;

    PyBindClass<Gecko::CharacterActionFieldSkill, Gecko::CharacterActionBattleSkill, STDSharedPtr<Gecko::CharacterActionFieldSkill>>(m, "CharacterActionFieldSkill")
        WRAPPING_ADD_CONSTRUCTOR_SIMPLE()
    ;
}
