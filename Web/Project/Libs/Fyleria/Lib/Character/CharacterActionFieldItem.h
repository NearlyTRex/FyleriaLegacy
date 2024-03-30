// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#ifndef _GECKO_CHARACTER_ACTION_FIELD_ITEM_H_
#define _GECKO_CHARACTER_ACTION_FIELD_ITEM_H_

#include "Character/CharacterActionBattleItem.h"

namespace Gecko
{

class CharacterActionFieldItem : public CharacterActionBattleItem
{
public:

    // Constructors
    CharacterActionFieldItem();
    CharacterActionFieldItem(const Json& jsonData);

    // Stages for running the action
    virtual Bool Setup();
    virtual Bool Finish();
    virtual Bool GenerateResult();
    virtual Bool ApplyResult();
};

// Typedef
MAKE_TYPE_TYPEDEFS(CharacterActionFieldItem);

// JSON Converters
void to_json(Json& jsonData, const CharacterActionFieldItem& obj);
void from_json(const Json& jsonData, CharacterActionFieldItem& obj);
MAKE_JSON_GENERIC_TYPE_CONVERTERS_DECL(CharacterActionFieldItem, CharacterActionFieldItem);

};

#endif
