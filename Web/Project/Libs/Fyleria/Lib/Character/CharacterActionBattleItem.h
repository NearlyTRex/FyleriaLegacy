// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#ifndef _GECKO_CHARACTER_ACTION_BATTLE_ITEM_H_
#define _GECKO_CHARACTER_ACTION_BATTLE_ITEM_H_

#include "Character/CharacterAction.h"

namespace Gecko
{

class CharacterActionBattleItem : public CharacterAction
{
public:

    // Constructors
    CharacterActionBattleItem();
    CharacterActionBattleItem(const Json& jsonData);

    // Stages for running the action
    virtual Bool Setup();
    virtual Bool Finish();
    virtual Bool GenerateResult();
    virtual Bool ApplyResult();
};

// Typedef
MAKE_TYPE_TYPEDEFS(CharacterActionBattleItem);

// JSON Converters
void to_json(Json& jsonData, const CharacterActionBattleItem& obj);
void from_json(const Json& jsonData, CharacterActionBattleItem& obj);
MAKE_JSON_GENERIC_TYPE_CONVERTERS_DECL(CharacterActionBattleItem, CharacterActionBattleItem);

};

#endif
