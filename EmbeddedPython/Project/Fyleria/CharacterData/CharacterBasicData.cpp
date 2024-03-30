// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

// Internal includes
#include "CharacterData/CharacterBasicData.h"

namespace Gecko
{

CharacterBasicData::CharacterBasicData()
{
}

CharacterBasicData::CharacterBasicData(const Json& jsonData)
{
    from_json(jsonData, *this);
}

CharacterBasicData::~CharacterBasicData()
{
}

void CharacterBasicData::InitAllStatNames()
{
    // Initialize stat type names
    InitializeStatTypeNames<CharacterBasicStatType_String>(GetStringStatNames());
    InitializeStatTypeNames<CharacterBasicStatType_Int>(GetIntStatNames());
}

Bool CharacterBasicData::operator==(const CharacterBasicData& other) const
{
    return (Json(*this) == Json(other));
}

Bool CharacterBasicData::operator!=(const CharacterBasicData& other) const
{
    return not operator==(other);
}

void to_json(Json& jsonData, const CharacterBasicData& obj)
{
    // Stat values
    SetJsonValuesFromStatTypeValues<CharacterBasicStatType_String, String>(jsonData, obj.GetStringStats());
    SetJsonValuesFromStatTypeValues<CharacterBasicStatType_Int, Int>(jsonData, obj.GetIntStats());
}

void from_json(const Json& jsonData, CharacterBasicData& obj)
{
    // Stat values
    SetStatTypeValuesFromJsonValues<CharacterBasicStatType_String, String>(jsonData, obj.GetStringStats());
    SetStatTypeValuesFromJsonValues<CharacterBasicStatType_Int, Int>(jsonData, obj.GetIntStats());
}

};
