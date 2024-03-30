// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

#ifndef _GECKO_SAVE_H_
#define _GECKO_SAVE_H_

// Internal includes
#include "Character/CharacterManager.h"
#include "CharacterParty/CharacterPartyManager.h"
#include "Utility/Macros.h"
#include "Utility/Enum.h"

namespace Gecko
{

class Save
{
public:

    // Constructors
    Save();
    Save(const Json& jsonData);
    Save(const String& jsonString);

    // Destructor
    virtual ~Save();

    // Clear all data
    void Clear();

    // Slot
    MAKE_RAW_TYPE_ACCESSORS(Slot, String);

    // Time
    MAKE_RAW_TYPE_ACCESSORS(Time, ULongLong);

    // Description
    MAKE_RAW_TYPE_ACCESSORS(Description, String);

    // Party
    MAKE_RAW_TYPE_ACCESSORS(Parties, CharacterPartyArray);

    // Characters
    MAKE_RAW_TYPE_ACCESSORS(Characters, CharacterArray);
};

// Typedef
MAKE_COMMON_TYPEDEFS(Save);

// JSON Converters
void to_json(Json& jsonData, const Save& obj);
void from_json(const Json& jsonData, Save& obj);

};

#endif
