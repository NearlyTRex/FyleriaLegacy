// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

#ifndef _GECKO_CHARACTER_MEDIA_DATA_H_
#define _GECKO_CHARACTER_MEDIA_DATA_H_

// Internal includes
#include "Character/CharacterTypes.h"
#include "Stats/StatTypeHolder.h"

namespace Gecko
{

// Character media data
class CharacterMediaData : public StatTypeHolder
{
public:

    // Constructors
    CharacterMediaData();
    CharacterMediaData(const Json& jsonData);

    // Destructor
    virtual ~CharacterMediaData();

    // Stat names
    static void InitAllStatNames();

    // String stats
    MAKE_STAT_TYPE_ACCESSORS(PortraitImage, String);

    // Comparisons
    Bool operator==(const CharacterMediaData& other) const;
    Bool operator!=(const CharacterMediaData& other) const;
};

// Typedef
MAKE_COMMON_TYPEDEFS(CharacterMediaData);

// JSON Converters
void to_json(Json& jsonData, const CharacterMediaData& obj);
void from_json(const Json& jsonData, CharacterMediaData& obj);

};

#endif
