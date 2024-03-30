// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

// Internal includes
#include "CharacterAction/CharacterActionResult.h"

namespace Gecko
{

CharacterActionResult::CharacterActionResult()
{
}

CharacterActionResult::CharacterActionResult(const Json& jsonData)
{
    from_json(jsonData, *this);
}

CharacterActionResult::CharacterActionResult(const String& jsonString)
{
    from_json(JsonParse(jsonString), *this);
}

CharacterActionResult::~CharacterActionResult()
{
}

void CharacterActionResult::Clear()
{
    // Final skill damage
    SetFinalDamage(0);

    // Whether target successfully defended
    SetHasTargetDefendedSuccessfully(false);

    // Whether multiple attacks succeeded
    SetHaveMultipleAttacksSucceeded(false);

    // Number of attacks to use on target
    SetNumAttacksOnTarget(0);

    // Per attack lists of critical hit info and damage
    SetIndividualAttackIsCriticalCausedArray({});
    SetIndividualAttackIsCriticalBlockedArray({});
    SetIndividualAttackTargetDamageArray({});
}

Bool CharacterActionResult::operator==(const CharacterActionResult& other) const
{
    return (Json(*this) == Json(other));
}

Bool CharacterActionResult::operator!=(const CharacterActionResult& other) const
{
    return not operator==(other);
}

void to_json(Json& jsonData, const CharacterActionResult& obj)
{
    // Final skill damage
    SET_JSON_DATA(FinalDamage);

    // Whether target successfully defended
    SET_JSON_DATA(HasTargetDefendedSuccessfully);

    // Whether multiple attacks succeeded
    SET_JSON_DATA(HaveMultipleAttacksSucceeded);

    // Number of attacks to use on target
    SET_JSON_DATA(NumAttacksOnTarget);

    // Per attack lists of critical hit info and damage
    SET_JSON_DATA(IndividualAttackIsCriticalCausedArray);
    SET_JSON_DATA(IndividualAttackIsCriticalBlockedArray);
    SET_JSON_DATA(IndividualAttackTargetDamageArray);
}

void from_json(const Json& jsonData, CharacterActionResult& obj)
{
    // Final skill damage
    SET_OBJ_DATA(FinalDamage, Int);

    // Whether target successfully defended
    SET_OBJ_DATA(HasTargetDefendedSuccessfully, Bool);

    // Whether multiple attacks succeeded
    SET_OBJ_DATA(HaveMultipleAttacksSucceeded, Bool);

    // Number of attacks to use on target
    SET_OBJ_DATA(NumAttacksOnTarget, UByte);

    // Per attack lists of critical hit info and damage
    SET_OBJ_DATA(IndividualAttackIsCriticalCausedArray, BoolArray);
    SET_OBJ_DATA(IndividualAttackIsCriticalBlockedArray, BoolArray);
    SET_OBJ_DATA(IndividualAttackTargetDamageArray, FloatArray);
}

};
