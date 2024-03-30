// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

// Internal includes
#include "CharacterData/CharacterSkillData.h"
#include "Character/CharacterTypes.h"
#include "Utility/Constants.h"

namespace Gecko
{

CharacterSkillData::CharacterSkillData()
{
}

CharacterSkillData::CharacterSkillData(const Json& jsonData)
{
    from_json(jsonData, *this);
}

CharacterSkillData::~CharacterSkillData()
{
}

Short CharacterSkillData::GetSkillCurrentValue(const String& sSkillType) const
{
    // Get current value
    Short iValue = 0;
    if(GetStatValue(sSkillType, iValue))
    {
        return (iValue % SKILL_RANK_UPGRADE_AMOUNT);
    }
    return 0;
}

Short CharacterSkillData::GetSkillRankValue(const String& sSkillType) const
{
    // Get rank value
    Short iValue = 0;
    if(GetStatValue(sSkillType, iValue))
    {
        return (iValue / SKILL_RANK_UPGRADE_AMOUNT);
    }
    return 0;
}

void CharacterSkillData::UpdateSkillValue(const String& sSkillType, Short iDelta)
{
    // Get existing value
    Short iValue = 0;
    if(!GetStatValue(sSkillType, iValue))
    {
        return;
    }

    // Update existing value
    SetStatValue(sSkillType, iValue + iDelta);
}

void CharacterSkillData::InitAllStatNames()
{
    // Initialize stat type names
    InitializeStatTypeNames<CharacterSkillStatType_Short>(GetShortStatNames());
}

Bool CharacterSkillData::operator==(const CharacterSkillData& other) const
{
    return (Json(*this) == Json(other));
}

Bool CharacterSkillData::operator!=(const CharacterSkillData& other) const
{
    return not operator==(other);
}

void to_json(Json& jsonData, const CharacterSkillData& obj)
{
    // Stat values
    SetJsonValuesFromStatTypeValues<CharacterSkillStatType_Short, Short>(jsonData, obj.GetShortStats());
}

void from_json(const Json& jsonData, CharacterSkillData& obj)
{
    // Stat values
    SetStatTypeValuesFromJsonValues<CharacterSkillStatType_Short, Short>(jsonData, obj.GetShortStats());
}

};
