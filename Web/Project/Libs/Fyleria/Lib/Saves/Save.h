// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#ifndef _GECKO_SAVE_H_
#define _GECKO_SAVE_H_

#include "Character/CharacterManager.h"
#include "Character/CharacterPartyManager.h"
#include "Utility/Macros.h"
#include "Utility/TypesEnum.h"
#include "Utility/Serializable.h"

namespace Gecko
{

class Save : public SerializableToJson
{
public:

    // Constructors
    Save();
    explicit Save(const Json& jsonData);
    explicit Save(const String& jsonString);

    // Slot
    MAKE_JSON_BASIC_TYPE_ACCESSORS(Slot, UByte);

    // Time
    MAKE_JSON_BASIC_TYPE_ACCESSORS(Time, ULong);

    // Description
    MAKE_JSON_BASIC_TYPE_ACCESSORS(Description, String);

    // Party
    MAKE_JSON_BASIC_TYPE_ACCESSORS(Party, CharacterParty);

    // Characters
    MAKE_JSON_BASIC_TYPE_ACCESSORS(Characters, CharacterList);

};

// Typedef
MAKE_TYPE_TYPEDEFS(Save);

// JSON Converters
MAKE_JSON_BASIC_TYPE_CONVERTERS_DECL(Save);
MAKE_JSON_GENERIC_TYPE_CONVERTERS_DECL(Save, Save);

};

#endif
