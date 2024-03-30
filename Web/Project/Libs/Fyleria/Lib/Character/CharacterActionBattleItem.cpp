// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#include "Character/CharacterActionBattleItem.h"

namespace Gecko
{

CharacterActionBattleItem::CharacterActionBattleItem()
    : CharacterAction()
{
    SetTypeName("CharacterActionBattleItem");
}

CharacterActionBattleItem::CharacterActionBattleItem(const Json& jsonData)
    : CharacterAction(jsonData)
{
    from_json(jsonData, *this);
}

Bool CharacterActionBattleItem::Setup()
{
    return false;
}

Bool CharacterActionBattleItem::Finish()
{
    return false;
}

Bool CharacterActionBattleItem::GenerateResult()
{
    return false;
}

Bool CharacterActionBattleItem::ApplyResult()
{
    return false;
}

void to_json(Json& jsonData, const CharacterActionBattleItem& obj)
{
}

void from_json(const Json& jsonData, CharacterActionBattleItem& obj)
{
}

MAKE_JSON_GENERIC_TYPE_CONVERTERS_IMPL(CharacterActionBattleItem, CharacterActionBattleItem);

};
