// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

#ifndef _GECKO_BATTLE_EVENTS_H_
#define _GECKO_BATTLE_EVENTS_H_

// Internal includes
#include "Utility/Types.h"
#include "CharacterAction/CharacterAction.h"

namespace Gecko
{

// Handle battle starts/ends/advances round
void HandleBattleStarted(const String& sCharacterID);
void HandleBattleEnded(const String& sCharacterID);
void HandleBattleTally(const String& sCharacterID);
void HandleBattleFullyCompleted(const String& sCharacterID);
void HandleBattleRoundAdvanced(const String& sCharacterID);

// Handle giving/taking damage during battle
void HandleBattleGivingDamage(const String& sCharacterID, Int iAmount);
void HandleBattleTakingDamage(const String& sCharacterID, Int iAmount);

// Handle choosing/becoming target during battle
void HandleBattleChoosingTargets(const String& sCharacterID, const StringArray& vDestTargets);
void HandleBattleBecomingTarget(const String& sCharacterID, const String& sSourceTarget);

// Handle battle action is initiated/received and finished
void HandleBattleActionAttackSetup(const String& sCharacterID, const CharacterAction& action);
void HandleBattleActionDefendSetup(const String& sCharacterID, const CharacterAction& action);
void HandleBattleActionApplied(const String& sCharacterID, const CharacterAction& action);
void HandleBattleActionFinished(const String& sCharacterID, const CharacterAction& action);

};

#endif
