// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

#ifndef _GECKO_CHARACTER_BASIC_DATA_H_
#define _GECKO_CHARACTER_BASIC_DATA_H_

// Internal includes
#include "Character/CharacterTypes.h"
#include "Stats/StatTypeHolder.h"

namespace Gecko
{

// Character basic data
class CharacterBasicData : public StatTypeHolder
{
public:

    // Constructors
    CharacterBasicData();
    CharacterBasicData(const Json& jsonData);

    // Destructor
    virtual ~CharacterBasicData();

    // Stat names
    static void InitAllStatNames();

    // String stats
    MAKE_STAT_TYPE_ACCESSORS(CharacterID, String);
    MAKE_STAT_TYPE_ACCESSORS(PartyID, String);
    MAKE_STAT_TYPE_ACCESSORS(FirstName, String);
    MAKE_STAT_TYPE_ACCESSORS(LastName, String);
    MAKE_STAT_TYPE_ACCESSORS(Gender, String);
    MAKE_STAT_TYPE_ACCESSORS(Hair, String);
    MAKE_STAT_TYPE_ACCESSORS(Eyes, String);
    MAKE_STAT_TYPE_ACCESSORS(Handedness, String);
    MAKE_STAT_TYPE_ACCESSORS(BaseRace, String);
    MAKE_STAT_TYPE_ACCESSORS(TransformedRace, String);
    MAKE_STAT_TYPE_ACCESSORS(PowerSet, String);
    MAKE_STAT_TYPE_ACCESSORS(WeaponSet, String);

    // Int stats
    MAKE_STAT_TYPE_ACCESSORS(Age, Int);

    // Comparisons
    Bool operator==(const CharacterBasicData& other) const;
    Bool operator!=(const CharacterBasicData& other) const;
};

// Typedef
MAKE_COMMON_TYPEDEFS(CharacterBasicData);

// JSON Converters
void to_json(Json& jsonData, const CharacterBasicData& obj);
void from_json(const Json& jsonData, CharacterBasicData& obj);

};

#endif
