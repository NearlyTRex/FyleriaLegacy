// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

#ifndef _GECKO_RECIPE_ENTRY_H_
#define _GECKO_RECIPE_ENTRY_H_

// Internal includes
#include "Utility/Macros.h"
#include "Utility/Enum.h"
#include "Utility/Json.h"

namespace Gecko
{

// Class for recipe entries
class RecipeEntry
{
public:

    // Constructors
    RecipeEntry();
    RecipeEntry(const Json& jsonData);

    // Destructor
    virtual ~RecipeEntry();

    // Clear all data
    void Clear();

    // Chance to success
    MAKE_RAW_TYPE_ACCESSORS(ChanceToSucceed, Float);

    // Input type
    MAKE_RAW_TYPE_ACCESSORS(InputPotionName, String);
    MAKE_RAW_TYPE_ACCESSORS(InputIngredientName, String);
    MAKE_RAW_TYPE_ACCESSORS(InputWeaponName, String);
    MAKE_RAW_TYPE_ACCESSORS(InputArmorName, String);

    // Output type
    MAKE_RAW_TYPE_ACCESSORS(OutputPotionName, String);
    MAKE_RAW_TYPE_ACCESSORS(OutputIngredientName, String);
    MAKE_RAW_TYPE_ACCESSORS(OutputWeaponName, String);
    MAKE_RAW_TYPE_ACCESSORS(OutputArmorName, String);

    // Input amount
    MAKE_RAW_TYPE_ACCESSORS(InputAmount, UByte);

    // Output amount
    MAKE_RAW_TYPE_ACCESSORS(OutputAmount, UByte);
};

// Typedefs
MAKE_COMMON_TYPEDEFS(RecipeEntry);

// JSON Converters
void to_json(Json& jsonData, const RecipeEntry& obj);
void from_json(const Json& jsonData, RecipeEntry& obj);

};

#endif
