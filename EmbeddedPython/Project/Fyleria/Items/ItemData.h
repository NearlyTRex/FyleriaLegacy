// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

#ifndef _GECKO_ITEMDATA_H_
#define _GECKO_ITEMDATA_H_

// Internal includes
#include "Stats/StatChange.h"
#include "Utility/Macros.h"
#include "Utility/Enum.h"
#include "Utility/Json.h"

namespace Gecko
{

class ItemData
{
public:

    // Constructors
    ItemData();
    ItemData(const Json& jsonData);

    // Destructor
    virtual ~ItemData();

    // Clear all data
    virtual void Clear();

    // Is actionable
    Bool IsActionable() const;

    // Does meet action requirements
    Bool DoesMeetActionRequirements(const String& sCharacterID, const String& sWeaponSet) const;

    // Create base character action
    CharacterActionArray CreateBaseActions(const String& sCharacterID, const String& sWeaponSet) const;

    // Run types
    MAKE_RAW_TYPE_ACCESSORS(RunTypes, StringArray);

    // Data class
    MAKE_RAW_TYPE_ACCESSORS(DataClass, String);

    // Item name
    MAKE_RAW_TYPE_ACCESSORS(ItemName, String);

    // Item description
    MAKE_RAW_TYPE_ACCESSORS(ItemDescription, String);

    // Item type
    MAKE_RAW_TYPE_ACCESSORS(ItemType, String);

    // Action types
    MAKE_RAW_TYPE_ACCESSORS(ActionTypes, StringArray);

    // Item index
    MAKE_RAW_TYPE_ACCESSORS(ItemTreeIndex, TreeIndex);

    // Stat changes
    MAKE_RAW_TYPE_ACCESSORS(StatChanges, StatChangeArray);
};

// Typedef
MAKE_COMMON_TYPEDEFS(ItemData);

// JSON Converters
void to_json(Json& jsonData, const ItemData& obj);
void from_json(const Json& jsonData, ItemData& obj);

};

#endif
