// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#ifndef _GECKO_RECIPE_ENTRY_H_
#define _GECKO_RECIPE_ENTRY_H_

#include "Utility/IndexedString.h"
#include "Utility/Macros.h"
#include "Utility/TypesEnum.h"
#include "Utility/TypesJson.h"

namespace Gecko
{

// POD class for recipe entries
class RecipeEntry
{
public:

    // Constructors
    RecipeEntry();
    RecipeEntry(const Json& jsonData);

    // Chance to success
    MAKE_RAW_BASIC_TYPE_ACCESSORS(ChanceToSucceed, Float);

    // Input type
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(InputPotionName, IndexedString);
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(InputIngredientName, IndexedString);
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(InputWeaponName, IndexedString);
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(InputArmorName, IndexedString);

    // Output type
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(OutputPotionName, IndexedString);
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(OutputIngredientName, IndexedString);
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(OutputWeaponName, IndexedString);
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(OutputArmorName, IndexedString);

    // Input amount
    MAKE_RAW_BASIC_TYPE_ACCESSORS(InputAmount, UByte);

    // Output amount
    MAKE_RAW_BASIC_TYPE_ACCESSORS(OutputAmount, UByte);
};

// Typedefs
MAKE_TYPE_TYPEDEFS(RecipeEntry);

// JSON Converters
void to_json(Json& jsonData, const RecipeEntry& obj);
void from_json(const Json& jsonData, RecipeEntry& obj);
MAKE_JSON_GENERIC_TYPE_CONVERTERS_DECL(RecipeEntry, RecipeEntry);

};

#endif
