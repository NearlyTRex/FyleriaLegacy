// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#ifndef _GECKO_CHARACTER_PROGRESS_ITEM_H_
#define _GECKO_CHARACTER_PROGRESS_ITEM_H_

#include "Utility/IndexedString.h"
#include "Utility/Macros.h"
#include "Utility/Tree.h"
#include "Utility/TypesEnum.h"
#include "Utility/TypesJson.h"

namespace Gecko
{

// POD class for items in progress data
class CharacterProgressItem
{
public:

    // Constructors
    CharacterProgressItem();
    CharacterProgressItem(const Json& jsonData);

    // Item tree index
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(TreeIndex, TreeIndex);

    // Item slot
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(ItemSlot, IndexedString);
};

// Typedef
MAKE_TYPE_TYPEDEFS(CharacterProgressItem);

// JSON Converters
void to_json(Json& jsonData, const CharacterProgressItem& obj);
void from_json(const Json& jsonData, CharacterProgressItem& obj);
MAKE_JSON_GENERIC_TYPE_CONVERTERS_DECL(CharacterProgressItem, CharacterProgressItem);

// Comparisons
Bool operator==(const CharacterProgressItem& a, const CharacterProgressItem& b);

};

#endif
