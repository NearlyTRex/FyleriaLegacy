// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#include "Battle/Battle.h"
#include "Character/CharacterPartyManager.h"

namespace Gecko
{

Battle::Battle()
{
    // Battle status
    SetIsBattleStarted(false);
    SetIsBattleFinished(false);
    SetIsBattleManuallyWon(false);
    SetIsBattleManuallyLost(false);

    // Current action/round
    SetCurrentActionIndex(0);
    SetCurrentRoundIndex(0);

    // Actions
    SetActions({});
    SetActionCount(0);

    // Party names
    SetEnemyPartyName(IndexedString(""));
    SetAllyPartyName(IndexedString(""));
}

Battle::Battle(const Json& jsonData)
{
    from_json(jsonData, *this);
}

void Battle::Start()
{
    // Reset battle
    SetCurrentRoundIndex(0);
    SetCurrentActionIndex(0);

    // Battle has begun!
    SetIsBattleStarted(true);
}

void Battle::Finish()
{
    // Battle has finished
    SetIsBattleFinished(true);
}

void Battle::AdvanceRound()
{
    // Advance round number
    SetCurrentRoundIndex(GetCurrentRoundIndex() + 1);

    // Clear all actions
    ClearAllActions();
}

Bool Battle::IsBattleOver(const IndexedString& sPartyID) const
{
    // A battle is over for sure if all of either party is dead
    const CharacterParty& party = CharacterPartyManager::GetInstance()->GetPartyByID(sPartyID);
    UInt uMemberCount = party.GetMemberCount();
    return ((uMemberCount == 0) || uMemberCount == party.GetStatusMemberCount((+CharacterStatusType::Dead)._to_string()));
}

Bool Battle::IsBattleWon() const
{
    return (GetIsBattleManuallyWon() || IsBattleOver(GetEnemyPartyName()));
}

Bool Battle::IsBattleLost() const
{
    return (GetIsBattleManuallyLost() || IsBattleOver(GetAllyPartyName()));
}

void Battle::AddAction(const CharacterActionSharedPtr& pAction)
{
    GetActions().push_back(pAction);
    SetActionCount(GetActionCount() + 1);
}

void Battle::ClearAllActions()
{
    GetActions().clear();
    SetActionCount(0);
}

void Battle::FinishedAddingActions()
{
    SetCurrentActionIndex(0);
}

void Battle::RunCurrentActionSetup()
{
    if(GetCurrentAction())
    {
        GetCurrentAction()->Setup();
    }
}

void Battle::RunCurrentActionFinish()
{
    if(GetCurrentAction())
    {
        GetCurrentAction()->Finish();
    }
}

void Battle::RunCurrentActionGenerateResult()
{
    if(GetCurrentAction())
    {
        GetCurrentAction()->GenerateResult();
    }
}

void Battle::RunCurrentActionApplyResult()
{
    if(GetCurrentAction())
    {
        GetCurrentAction()->ApplyResult();
    }
}

void Battle::FinishedWithCurrentAction()
{
    SetCurrentActionIndex(GetCurrentActionIndex() + 1);
}

CharacterActionSharedPtr& Battle::GetAction(Int iIndex)
{
    ASSERT_ERROR(iIndex >= 0 && iIndex < GetActionCount());
    return GetActions()[iIndex];
}

const CharacterActionSharedPtr& Battle::GetAction(Int iIndex) const
{
    ASSERT_ERROR(iIndex >= 0 && iIndex < GetActionCount());
    return GetActions()[iIndex];
}

CharacterActionSharedPtr& Battle::GetCurrentAction()
{
    return GetAction(GetCurrentActionIndex());
}

const CharacterActionSharedPtr& Battle::GetCurrentAction() const
{
    return GetAction(GetCurrentActionIndex());
}

Bool Battle::AreAllActionsFinished() const
{
    return (GetCurrentActionIndex() >= GetActionCount());
}

CharacterActionSharedPtrList Battle::GetRemainingActions() const
{
    if(GetCurrentActionIndex() < GetActionCount())
    {
        return CharacterActionSharedPtrList(GetActions().begin() + GetCurrentActionIndex(), GetActions().end());
    }
    return CharacterActionSharedPtrList();
}

void to_json(Json& jsonData, const Battle& obj)
{
    // Battle status
    SET_JSON_DATA_IF_NOT_DEFAULT(IsBattleStarted, false);
    SET_JSON_DATA_IF_NOT_DEFAULT(IsBattleFinished, false);
    SET_JSON_DATA_IF_NOT_DEFAULT(IsBattleManuallyWon, false);
    SET_JSON_DATA_IF_NOT_DEFAULT(IsBattleManuallyLost, false);

    // Current action/round
    SET_JSON_DATA_IF_NOT_DEFAULT(CurrentActionIndex, 0);
    SET_JSON_DATA_IF_NOT_DEFAULT(CurrentRoundIndex, 0);

    // Actions
    SET_JSON_DATA_FROM_PTR_ARRAY_IF_NOT_EMPTY(Actions);
    SET_JSON_DATA_IF_NOT_DEFAULT(ActionCount, 0);

    // Party names
    SET_JSON_DATA_IF_NOT_DEFAULT(EnemyPartyName, IndexedString(""));
    SET_JSON_DATA_IF_NOT_DEFAULT(AllyPartyName, IndexedString(""));
}

void from_json(const Json& jsonData, Battle& obj)
{
    // Battle status
    obj.SetIsBattleStarted(GET_JSON_DATA_OR_DEFAULT(IsBattleStarted, Bool, false));
    obj.SetIsBattleFinished(GET_JSON_DATA_OR_DEFAULT(IsBattleFinished, Bool, false));
    obj.SetIsBattleManuallyWon(GET_JSON_DATA_OR_DEFAULT(IsBattleManuallyWon, Bool, false));
    obj.SetIsBattleManuallyLost(GET_JSON_DATA_OR_DEFAULT(IsBattleManuallyLost, Bool, false));

    // Current action/round
    obj.SetCurrentActionIndex(GET_JSON_DATA_OR_DEFAULT(CurrentActionIndex, Int, 0));
    obj.SetCurrentRoundIndex(GET_JSON_DATA_OR_DEFAULT(CurrentRoundIndex, Int, 0));

    // Actions
    obj.SetActions(GET_JSON_DATA_OR_DEFAULT(Actions, CharacterActionSharedPtrList, CharacterActionSharedPtrList()));
    obj.SetActionCount(GET_JSON_DATA_OR_DEFAULT(ActionCount, Int, 0));

    // Party names
    obj.SetEnemyPartyName(GET_JSON_DATA_OR_DEFAULT(EnemyPartyName, IndexedString, IndexedString("")));
    obj.SetAllyPartyName(GET_JSON_DATA_OR_DEFAULT(AllyPartyName, IndexedString, IndexedString("")));
}

MAKE_JSON_GENERIC_TYPE_CONVERTERS_IMPL(Battle, Battle);

};
