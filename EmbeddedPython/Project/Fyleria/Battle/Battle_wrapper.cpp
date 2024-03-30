// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

// Internal includes
#include "Battle/Battle.h"
#include "Battle/BattleEvents.h"
#include "Battle/BattleManager.h"
#include "Utility/Macros.h"
#include "Utility/Python.h"

namespace Gecko
{
    // Manager lambdas
    auto fnCreateBattle = MAKE_MANAGER_VOID_LAMBDA_A1(BattleManager, CreateBattle, const String&);
    auto fnUnloadBattle = MAKE_MANAGER_VOID_LAMBDA_A1(BattleManager, UnloadBattle, const String&);
    auto fnDoesBattleExist = MAKE_MANAGER_RETURN_LAMBDA_A1(BattleManager, DoesBattleExist, Bool, const String&);
    auto fnDoesBattleExist_StoreResult = MAKE_MANAGER_VOID_LAMBDA_A2(BattleManager, DoesBattleExist_StoreResult, const String&, const String&);
    auto fnGetBattle1 = MAKE_MANAGER_RETURN_LAMBDA_A1(BattleManager, GetBattle, const Battle&, const String&);
    auto fnGetBattle2 = MAKE_MANAGER_RETURN_LAMBDA_A1(BattleManager, GetBattle, Battle&, const String&);
    auto fnGetBattle_StoreResult = MAKE_MANAGER_VOID_LAMBDA_A2(BattleManager, GetBattle_StoreResult, const String&, const String&);
    auto fnGetCurrentBattle1 = MAKE_MANAGER_RETURN_LAMBDA(BattleManager, GetCurrentBattle, const Battle&);
    auto fnGetCurrentBattle2 = MAKE_MANAGER_RETURN_LAMBDA(BattleManager, GetCurrentBattle, Battle&);
    auto fnGetCurrentBattle_StoreResult = MAKE_MANAGER_VOID_LAMBDA_A1(BattleManager, GetCurrentBattle_StoreResult, const String&);
    auto fnGetCurrentBattleID = MAKE_MANAGER_RETURN_LAMBDA(BattleManager, GetCurrentBattleID, String&);
    auto fnSetCurrentBattleID = MAKE_MANAGER_VOID_LAMBDA_A1(BattleManager, SetCurrentBattleID, const String&);
};

PYBIND11_EMBEDDED_MODULE(GeckoBattle, m)
{
    // Battle.h
    PyBindClass<Gecko::Battle>(m, "Battle")
        WRAPPING_ADD_CONSTRUCTOR_SIMPLE()
        WRAPPING_ADD_METHOD_SIMPLE(Start, Gecko::Battle)
        WRAPPING_ADD_METHOD_SIMPLE(Finish, Gecko::Battle)
        WRAPPING_ADD_METHOD_SIMPLE(AdvanceRound, Gecko::Battle)
        WRAPPING_ADD_METHOD_SIMPLE(IsBattleOver, Gecko::Battle)
        WRAPPING_ADD_METHOD_SIMPLE(IsBattleWon, Gecko::Battle)
        WRAPPING_ADD_METHOD_SIMPLE(IsBattleLost, Gecko::Battle)
        WRAPPING_ADD_METHOD_SIMPLE(AddAction, Gecko::Battle)
        WRAPPING_ADD_METHOD_SIMPLE(ClearAllActions, Gecko::Battle)
        WRAPPING_ADD_METHOD_SIMPLE(FinishedAddingActions, Gecko::Battle)
        WRAPPING_ADD_METHOD_SIMPLE(RunCurrentActionSetup, Gecko::Battle)
        WRAPPING_ADD_METHOD_SIMPLE(RunCurrentActionFinish, Gecko::Battle)
        WRAPPING_ADD_METHOD_SIMPLE(RunCurrentActionGenerateResult, Gecko::Battle)
        WRAPPING_ADD_METHOD_SIMPLE(RunCurrentActionApplyResult, Gecko::Battle)
        WRAPPING_ADD_METHOD_SIMPLE(FinishedWithCurrentAction, Gecko::Battle)
        WRAPPING_ADD_METHOD_OVERLOADED(GetAction, Gecko::Battle, Gecko::Int)
        WRAPPING_ADD_METHOD_OVERLOADED_CONST(GetAction, Gecko::Battle, Gecko::Int)
        WRAPPING_ADD_METHOD_OVERLOADED_CONST(GetCurrentAction, Gecko::Battle, )
        WRAPPING_ADD_METHOD_OVERLOADED(GetCurrentAction, Gecko::Battle, )
        WRAPPING_ADD_METHOD_SIMPLE(AreAllActionsFinished, Gecko::Battle)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(IsBattleStarted, Gecko::Battle)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(IsBattleFinished, Gecko::Battle)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(IsBattleManuallyWon, Gecko::Battle)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(IsBattleManuallyLost, Gecko::Battle)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(CurrentActionIndex, Gecko::Battle)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(CurrentRoundIndex, Gecko::Battle)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(Actions, Gecko::Battle)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(ActionCount, Gecko::Battle)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(EnemyPartyID, Gecko::Battle)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(AllyPartyID, Gecko::Battle)
        WRAPPING_ADD_METHOD_SIMPLE(IsBattleOver_StoreResult, Gecko::Battle)
        WRAPPING_ADD_METHOD_SIMPLE(IsBattleWon_StoreResult, Gecko::Battle)
        WRAPPING_ADD_METHOD_SIMPLE(IsBattleLost_StoreResult, Gecko::Battle)
        WRAPPING_ADD_METHOD_SIMPLE(GetAction_StoreResult, Gecko::Battle)
        WRAPPING_ADD_METHOD_SIMPLE(GetCurrentAction_StoreResult, Gecko::Battle)
        WRAPPING_ADD_METHOD_SIMPLE(AreAllActionsFinished_StoreResult, Gecko::Battle)
    ;
    PyBindVector<Gecko::BattleArray>(m, "BattleArray");

    // BattleEvents.h
    WRAPPING_STANDALONE_METHOD_SIMPLE(HandleBattleStarted, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(HandleBattleEnded, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(HandleBattleTally, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(HandleBattleFullyCompleted, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(HandleBattleRoundAdvanced, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(HandleBattleGivingDamage, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(HandleBattleTakingDamage, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(HandleBattleChoosingTargets, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(HandleBattleBecomingTarget, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(HandleBattleActionAttackSetup, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(HandleBattleActionDefendSetup, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(HandleBattleActionApplied, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(HandleBattleActionFinished, Gecko);

    // BattleManager.h
    WRAPPING_STANDALONE_LAMBDA(CreateBattle, Gecko::fnCreateBattle);
    WRAPPING_STANDALONE_LAMBDA(UnloadBattle, Gecko::fnUnloadBattle);
    WRAPPING_STANDALONE_LAMBDA(DoesBattleExist, Gecko::fnDoesBattleExist);
    WRAPPING_STANDALONE_LAMBDA(DoesBattleExist_StoreResult, Gecko::fnDoesBattleExist_StoreResult);
    WRAPPING_STANDALONE_LAMBDA_POLICY(GetBattle1, Gecko::fnGetBattle1, PyBindReturnCopy);
    WRAPPING_STANDALONE_LAMBDA_POLICY(GetBattle2, Gecko::fnGetBattle2, PyBindReturnRefInternal);
    WRAPPING_STANDALONE_LAMBDA(GetBattle_StoreResult, Gecko::fnGetBattle_StoreResult);
    WRAPPING_STANDALONE_LAMBDA_POLICY(GetCurrentBattle1, Gecko::fnGetCurrentBattle1, PyBindReturnCopy);
    WRAPPING_STANDALONE_LAMBDA_POLICY(GetCurrentBattle2, Gecko::fnGetCurrentBattle2, PyBindReturnRefInternal);
    WRAPPING_STANDALONE_LAMBDA(GetCurrentBattle_StoreResult, Gecko::fnGetCurrentBattle_StoreResult);
    WRAPPING_STANDALONE_LAMBDA(GetCurrentBattleID, Gecko::fnGetCurrentBattleID);
    WRAPPING_STANDALONE_LAMBDA(SetCurrentBattleID, Gecko::fnSetCurrentBattleID);
}
