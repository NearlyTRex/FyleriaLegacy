// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#include "Character/CharacterActionFieldSkill.h"

namespace Gecko
{

CharacterActionFieldSkill::CharacterActionFieldSkill()
    : CharacterActionBattleSkill()
{
    SetTypeName("CharacterActionFieldSkill");
}

CharacterActionFieldSkill::CharacterActionFieldSkill(const Json& jsonData)
    : CharacterActionBattleSkill(jsonData)
{
    from_json(jsonData, *this);
}

Bool CharacterActionFieldSkill::Setup()
{
    return false;
}

Bool CharacterActionFieldSkill::Finish()
{
    return false;
}

Bool CharacterActionFieldSkill::GenerateResult()
{
    return false;
}

Bool CharacterActionFieldSkill::ApplyResult()
{
    return false;
}

void to_json(Json& jsonData, const CharacterActionFieldSkill& obj)
{
}

void from_json(const Json& jsonData, CharacterActionFieldSkill& obj)
{
}

MAKE_JSON_GENERIC_TYPE_CONVERTERS_IMPL(CharacterActionFieldSkill, CharacterActionFieldSkill);

};
