// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#ifndef _GECKO_BATTLE_H_
#define _GECKO_BATTLE_H_

#include "Character/CharacterAction.h"
#include "Utility/Macros.h"
#include "Utility/TypesEnum.h"

namespace Gecko
{

class Battle
{
public:

    // Constructors
    Battle();
    Battle(const Json& jsonData);

    // Start/end battle
    void Start();
    void Finish();

    // Advance the round
    void AdvanceRound();

    // Determine if battle is won/lost
    Bool IsBattleOver(const IndexedString& sPartyID) const;
    Bool IsBattleWon() const;
    Bool IsBattleLost() const;

    // Adding and processing actions that are chosen by the player
    void AddAction(const CharacterActionSharedPtr& pAction);
    void ClearAllActions();
    void FinishedAddingActions();

    // Action stages
    void RunCurrentActionSetup();
    void RunCurrentActionFinish();
    void RunCurrentActionGenerateResult();
    void RunCurrentActionApplyResult();
    void FinishedWithCurrentAction();

    // Get action
    CharacterActionSharedPtr& GetAction(Int iIndex);
    const CharacterActionSharedPtr& GetAction(Int iIndex) const;
    CharacterActionSharedPtr& GetCurrentAction();
    const CharacterActionSharedPtr& GetCurrentAction() const;

    // Are all actions finished
    Bool AreAllActionsFinished() const;

    // Get remaining actions
    CharacterActionSharedPtrList GetRemainingActions() const;

    // Battle status
    MAKE_RAW_BASIC_TYPE_ACCESSORS(IsBattleStarted, Bool);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(IsBattleFinished, Bool);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(IsBattleManuallyWon, Bool);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(IsBattleManuallyLost, Bool);

    // Current action/round
    MAKE_RAW_BASIC_TYPE_ACCESSORS(CurrentActionIndex, Int);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(CurrentRoundIndex, Int);

    // Actions
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(Actions, CharacterActionSharedPtrList);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(ActionCount, Int);

    // Party names
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(EnemyPartyName, IndexedString);
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(AllyPartyName, IndexedString);
};

// Typedef
MAKE_TYPE_TYPEDEFS(Battle);

// JSON Converters
void to_json(Json& jsonData, const Battle& obj);
void from_json(const Json& jsonData, Battle& obj);
MAKE_JSON_GENERIC_TYPE_CONVERTERS_DECL(Battle, Battle);

};

#endif
