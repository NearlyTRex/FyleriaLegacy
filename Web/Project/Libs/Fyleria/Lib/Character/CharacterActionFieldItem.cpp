// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#include "Character/CharacterActionFieldItem.h"

namespace Gecko
{

CharacterActionFieldItem::CharacterActionFieldItem()
    : CharacterActionBattleItem()
{
    SetTypeName("CharacterActionFieldItem");
}

CharacterActionFieldItem::CharacterActionFieldItem(const Json& jsonData)
    : CharacterActionBattleItem(jsonData)
{
    from_json(jsonData, *this);
}

Bool CharacterActionFieldItem::Setup()
{
    return false;
}

Bool CharacterActionFieldItem::Finish()
{
    return false;
}

Bool CharacterActionFieldItem::GenerateResult()
{
    return false;
}

Bool CharacterActionFieldItem::ApplyResult()
{
    return false;
}

void to_json(Json& jsonData, const CharacterActionFieldItem& obj)
{
}

void from_json(const Json& jsonData, CharacterActionFieldItem& obj)
{
}

MAKE_JSON_GENERIC_TYPE_CONVERTERS_IMPL(CharacterActionFieldItem, CharacterActionFieldItem);

};
