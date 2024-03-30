// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#ifndef _GECKO_ITEMDATA_H_
#define _GECKO_ITEMDATA_H_

#include "Stats/StatChange.h"
#include "Utility/IndexedString.h"
#include "Utility/Macros.h"
#include "Utility/TypesEnum.h"
#include "Utility/TypesJson.h"

namespace Gecko
{

class ItemData
{
public:

    // Constructors
    ItemData();
    ItemData(const Json& jsonData);

    // Is actionable
    Bool IsActionable() const;

    // Does meet action requirements
    Bool DoesMeetActionRequirements(const IndexedString& sCharacterID, const IndexedString& sWeaponSet) const;

    // Create base character action
    CharacterActionSharedPtrList CreateBaseActions(const IndexedString& sCharacterID, const IndexedString& sWeaponSet) const;

    // Run types
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(RunTypes, IndexedStringList);

    // Data class
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(DataClass, IndexedString);

    // Item name
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(ItemName, IndexedString);

    // Item description
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(ItemDescription, IndexedString);

    // Item type
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(ItemType, IndexedString);

    // Action types
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(ActionTypes, IndexedStringList);

    // Item index
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(ItemTreeIndex, TreeIndex);

    // Stat changes
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(StatChanges, StatChangeList);
};

// Typedef
MAKE_TYPE_TYPEDEFS(ItemData);

// JSON Converters
void to_json(Json& jsonData, const ItemData& obj);
void from_json(const Json& jsonData, ItemData& obj);

};

#endif
