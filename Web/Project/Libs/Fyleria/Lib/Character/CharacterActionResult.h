// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#ifndef _GECKO_CHARACTER_ACTION_RESULT_H_
#define _GECKO_CHARACTER_ACTION_RESULT_H_

#include "Utility/IndexedString.h"
#include "Utility/Macros.h"
#include "Utility/Tree.h"
#include "Utility/TypesEnum.h"
#include "Utility/TypesJson.h"
#include "Utility/Serializable.h"

namespace Gecko
{

class CharacterActionResult : public SerializableToJson
{
public:

    // Constructors
    CharacterActionResult();
    explicit CharacterActionResult(const Json& jsonData);
    explicit CharacterActionResult(const String& jsonString);

    // Final skill damage
    MAKE_JSON_BASIC_TYPE_ACCESSORS(FinalDamage, Int);

    // Whether target successfully defended
    MAKE_JSON_BASIC_TYPE_ACCESSORS(HasTargetDefendedSuccessfully, Bool);

    // Whether multiple attacks succeeded
    MAKE_JSON_BASIC_TYPE_ACCESSORS(HaveMultipleAttacksSucceeded, Bool);

    // Number of attacks to use on target
    MAKE_JSON_BASIC_TYPE_ACCESSORS(NumAttacksOnTarget, UByte);

    // Per attack lists of critical hit info and damage
    MAKE_JSON_BASIC_TYPE_ACCESSORS(IndividualAttackIsCriticalCausedList, BoolList);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(IndividualAttackIsCriticalBlockedList, BoolList);
    MAKE_JSON_BASIC_TYPE_ACCESSORS(IndividualAttackTargetDamageList, FloatList);

    // Comparisons
    Bool operator==(const CharacterActionResult& other) const;
    Bool operator!=(const CharacterActionResult& other) const;
};

// Typedef
MAKE_TYPE_TYPEDEFS(CharacterActionResult);

// JSON Converters
MAKE_JSON_BASIC_TYPE_CONVERTERS_DECL(CharacterActionResult);
MAKE_JSON_GENERIC_TYPE_CONVERTERS_DECL(CharacterActionResult, CharacterActionResult);

};

#endif
