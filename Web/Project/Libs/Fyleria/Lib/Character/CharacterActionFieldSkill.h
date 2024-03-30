// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#ifndef _GECKO_CHARACTER_ACTION_FIELD_SKILL_H_
#define _GECKO_CHARACTER_ACTION_FIELD_SKILL_H_

#include "Character/CharacterActionBattleSkill.h"

namespace Gecko
{

class CharacterActionFieldSkill : public CharacterActionBattleSkill
{
public:

    // Constructors
    CharacterActionFieldSkill();
    CharacterActionFieldSkill(const Json& jsonData);

    // Stages for running the action
    virtual Bool Setup();
    virtual Bool Finish();
    virtual Bool GenerateResult();
    virtual Bool ApplyResult();
};

// Typedef
MAKE_TYPE_TYPEDEFS(CharacterActionFieldSkill);

// JSON Converters
void to_json(Json& jsonData, const CharacterActionFieldSkill& obj);
void from_json(const Json& jsonData, CharacterActionFieldSkill& obj);
MAKE_JSON_GENERIC_TYPE_CONVERTERS_DECL(CharacterActionFieldSkill, CharacterActionFieldSkill);

};

#endif
