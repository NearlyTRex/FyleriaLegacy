// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

#ifndef _GECKO_CHARACTER_ACTION_RESULT_H_
#define _GECKO_CHARACTER_ACTION_RESULT_H_

// Internal includes
#include "Utility/Macros.h"
#include "Utility/Tree.h"
#include "Utility/Enum.h"
#include "Utility/Json.h"

namespace Gecko
{

class CharacterActionResult
{
public:

    // Constructors
    CharacterActionResult();
    CharacterActionResult(const Json& jsonData);
    CharacterActionResult(const String& jsonString);

    // Destructor
    virtual ~CharacterActionResult();

    // Clear all data
    void Clear();

    // Final skill damage
    MAKE_RAW_TYPE_ACCESSORS(FinalDamage, Int);

    // Whether target successfully defended
    MAKE_RAW_TYPE_ACCESSORS(HasTargetDefendedSuccessfully, Bool);

    // Whether multiple attacks succeeded
    MAKE_RAW_TYPE_ACCESSORS(HaveMultipleAttacksSucceeded, Bool);

    // Number of attacks to use on target
    MAKE_RAW_TYPE_ACCESSORS(NumAttacksOnTarget, UByte);

    // Per attack lists of critical hit info and damage
    MAKE_RAW_TYPE_ACCESSORS(IndividualAttackIsCriticalCausedArray, BoolArray);
    MAKE_RAW_TYPE_ACCESSORS(IndividualAttackIsCriticalBlockedArray, BoolArray);
    MAKE_RAW_TYPE_ACCESSORS(IndividualAttackTargetDamageArray, FloatArray);

    // Comparisons
    Bool operator==(const CharacterActionResult& other) const;
    Bool operator!=(const CharacterActionResult& other) const;
};

// Typedef
MAKE_COMMON_TYPEDEFS(CharacterActionResult);

// JSON Converters
void to_json(Json& jsonData, const CharacterActionResult& obj);
void from_json(const Json& jsonData, CharacterActionResult& obj);

};

#endif
