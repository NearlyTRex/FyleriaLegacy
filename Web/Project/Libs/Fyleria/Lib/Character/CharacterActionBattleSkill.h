// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#ifndef _GECKO_CHARACTER_ACTION_BATTLE_SKILL_H_
#define _GECKO_CHARACTER_ACTION_BATTLE_SKILL_H_

#include "Character/CharacterAction.h"

namespace Gecko
{

class CharacterActionBattleSkill : public CharacterAction
{
public:

    // Constructors
    CharacterActionBattleSkill();
    CharacterActionBattleSkill(const Json& jsonData);

    // Get skill attack result
    CharacterActionResult GetSkillAttackResult(const CharacterActionEntry& entry) const;

    // Stages for running the action
    virtual Bool Setup();
    virtual Bool Finish();
    virtual Bool GenerateResult();
    virtual Bool ApplyResult();
};

// Typedef
MAKE_TYPE_TYPEDEFS(CharacterActionBattleSkill);

// JSON Converters
void to_json(Json& jsonData, const CharacterActionBattleSkill& obj);
void from_json(const Json& jsonData, CharacterActionBattleSkill& obj);
MAKE_JSON_GENERIC_TYPE_CONVERTERS_DECL(CharacterActionBattleSkill, CharacterActionBattleSkill);

};

#endif
