// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

// Internal includes
#include "Battle/Battle.h"
#include "CharacterParty/CharacterPartyManager.h"

namespace Gecko
{

Battle::Battle()
{
}

Battle::Battle(const Json& jsonData)
{
    from_json(jsonData, *this);
}

void Battle::Clear()
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

    // Party IDs
    SetEnemyPartyID("");
    SetAllyPartyID("");
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

Bool Battle::IsBattleOver(const String& sPartyID) const
{
    const CharacterParty& party = CharacterPartyManager::GetInstance()->GetPartyByID(sPartyID);
    return party.IsPartyAbleToFight();
}

Bool Battle::IsBattleWon() const
{
    return (GetIsBattleManuallyWon() || IsBattleOver(GetEnemyPartyID()));
}

Bool Battle::IsBattleLost() const
{
    return (GetIsBattleManuallyLost() || IsBattleOver(GetAllyPartyID()));
}

Bool Battle::IsSkillAttackAction(const CharacterAction& action) const
{
    return (!action.GetSkillTreeIndex().empty());
}

void Battle::AddAction(const CharacterAction& action)
{
    GetActions().push_back(action);
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
    CharacterAction& action = GetCurrentAction();
    if(IsSkillAttackAction(action))
    {
        GetSkillAttackHandler().Setup(action);
    }
}

void Battle::RunCurrentActionFinish()
{
    CharacterAction& action = GetCurrentAction();
    if(IsSkillAttackAction(action))
    {
        GetSkillAttackHandler().Finish(action);
    }
}

void Battle::RunCurrentActionGenerateResult()
{
    CharacterAction& action = GetCurrentAction();
    if(IsSkillAttackAction(action))
    {
        GetSkillAttackHandler().GenerateResult(action);
    }
}

void Battle::RunCurrentActionApplyResult()
{
    CharacterAction& action = GetCurrentAction();
    if(IsSkillAttackAction(action))
    {
        GetSkillAttackHandler().ApplyResult(action);
    }
}

void Battle::FinishedWithCurrentAction()
{
    SetCurrentActionIndex(GetCurrentActionIndex() + 1);
}

const CharacterAction& Battle::GetAction(Int iIndex) const
{
    if(iIndex >= 0 && iIndex < GetActionCount())
    {
        return GetActions().at(iIndex);
    }
    THROW_RUNTIME_ERROR("Invalid action index '" + STDToString(iIndex) + "'");
}

CharacterAction& Battle::GetAction(Int iIndex)
{
    return const_cast<CharacterAction&>(static_cast<const Battle&>(*this).GetAction(iIndex));
}

const CharacterAction& Battle::GetCurrentAction() const
{
    return GetAction(GetCurrentActionIndex());
}

CharacterAction& Battle::GetCurrentAction()
{
    return GetAction(GetCurrentActionIndex());
}

Bool Battle::AreAllActionsFinished() const
{
    return (GetCurrentActionIndex() >= GetActionCount());
}

void to_json(Json& jsonData, const Battle& obj)
{
    // Battle status
    SET_JSON_DATA(IsBattleStarted);
    SET_JSON_DATA(IsBattleFinished);
    SET_JSON_DATA(IsBattleManuallyWon);
    SET_JSON_DATA(IsBattleManuallyLost);

    // Current action/round
    SET_JSON_DATA(CurrentActionIndex);
    SET_JSON_DATA(CurrentRoundIndex);

    // Actions
    SET_JSON_DATA(Actions);
    SET_JSON_DATA(ActionCount);

    // Party names
    SET_JSON_DATA(EnemyPartyID);
    SET_JSON_DATA(AllyPartyID);
}

void from_json(const Json& jsonData, Battle& obj)
{
    // Battle status
    SET_OBJ_DATA(IsBattleStarted, Bool);
    SET_OBJ_DATA(IsBattleFinished, Bool);
    SET_OBJ_DATA(IsBattleManuallyWon, Bool);
    SET_OBJ_DATA(IsBattleManuallyLost, Bool);

    // Current action/round
    SET_OBJ_DATA(CurrentActionIndex, Int);
    SET_OBJ_DATA(CurrentRoundIndex, Int);

    // Actions
    SET_OBJ_DATA(Actions, CharacterActionArray);
    SET_OBJ_DATA(ActionCount, Int);

    // Party IDs
    SET_OBJ_DATA(EnemyPartyID, String);
    SET_OBJ_DATA(AllyPartyID, String);
}

};
