// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#include "Battle/Battle.h"
#include "Battle/BattleManager.h"
#include "Utility/Macros.h"
#include "Utility/TypesPython.h"

namespace Gecko
{

BattleManager* GetBattleManager() { return BattleManager::GetInstance(); }

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
        WRAPPING_ADD_METHOD_OVERLOADED(GetCurrentAction, Gecko::Battle, )
        WRAPPING_ADD_METHOD_OVERLOADED_CONST(GetCurrentAction, Gecko::Battle, )
        WRAPPING_ADD_METHOD_SIMPLE(AreAllActionsFinished, Gecko::Battle)
        WRAPPING_ADD_METHOD_SIMPLE(GetRemainingActions, Gecko::Battle)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(IsBattleStarted, Gecko::Battle)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(IsBattleFinished, Gecko::Battle)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(IsBattleManuallyWon, Gecko::Battle)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(IsBattleManuallyLost, Gecko::Battle)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(CurrentActionIndex, Gecko::Battle)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(CurrentRoundIndex, Gecko::Battle)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(Actions, Gecko::Battle)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(ActionCount, Gecko::Battle)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(EnemyPartyName, Gecko::Battle)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(AllyPartyName, Gecko::Battle)
    ;
    PyBindVector<Gecko::BattleList>(m, "BattleList");
    WRAPPING_STANDALONE_METHOD_SIMPLE(ConvertBattleToJsonString, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(ConvertBattleListToJsonString, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetBattleFromJsonString, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetBattleListFromJsonString, Gecko);

    // BattleManager.h
    PyBindClass<Gecko::BattleManager>(m, "BattleManager")
        WRAPPING_ADD_METHOD_SIMPLE(CreateBattle, Gecko::BattleManager)
        WRAPPING_ADD_METHOD_SIMPLE(UnloadBattle, Gecko::BattleManager)
        WRAPPING_ADD_METHOD_SIMPLE(DoesBattleExist, Gecko::BattleManager)
        WRAPPING_ADD_METHOD_SIMPLE(SetAsCurrentBattle, Gecko::BattleManager)
        WRAPPING_ADD_METHOD_SIMPLE(GetCurrentBattleName, Gecko::BattleManager)
        WRAPPING_ADD_METHOD_OVERLOADED_POLICY(GetBattle, Gecko::BattleManager, PyBindReturnRefInternal, const Gecko::IndexedString&)
        WRAPPING_ADD_METHOD_OVERLOADED_POLICY_CONST(GetBattle, Gecko::BattleManager, PyBindReturnCopy, const Gecko::IndexedString&)
        WRAPPING_ADD_METHOD_OVERLOADED_POLICY(GetCurrentBattle, Gecko::BattleManager, PyBindReturnRefInternal, )
        WRAPPING_ADD_METHOD_OVERLOADED_POLICY_CONST(GetCurrentBattle, Gecko::BattleManager, PyBindReturnCopy, )
    ;

    // Local
    WRAPPING_STANDALONE_METHOD_POLICY(GetBattleManager, Gecko, PyBindReturnAutoRef);
}
