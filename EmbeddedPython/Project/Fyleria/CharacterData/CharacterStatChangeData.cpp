// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

// Internal includes
#include "CharacterData/CharacterStatChangeData.h"
#include "Character/CharacterManager.h"
#include "Battle/BattleManager.h"
#include "Items/ItemTree.h"
#include "Skills/SkillTree.h"
#include "Utility/Errors.h"

namespace Gecko
{

CharacterStatChangeData::CharacterStatChangeData()
{
}

CharacterStatChangeData::CharacterStatChangeData(const Json& jsonData)
{
    from_json(jsonData, *this);
}

CharacterStatChangeData::~CharacterStatChangeData()
{
}

void CharacterStatChangeData::Clear()
{
    // Passive data
    GetPassiveSkillDataArray().clear();
    GetPassiveItemDataArray().clear();

    // Active data
    GetActiveSkillDataArray().clear();
    GetActiveItemDataArray().clear();

    // Actionable data
    GetActionableSkillDataArray().clear();
    GetActionableItemDataArray().clear();

    // Prolonged stat changes
    SetProlongedStatChanges({});
}

void CharacterStatChangeData::UpdateAvailableChanges(const String& sCharacterID)
{
    // Fill skill indices
    TreeIndexArray vSkillPassives;
    TreeIndexArray vSkillActives;
    TreeIndexArray vSkillActionables;
    SkillTree::FillSkillStatChangeArrays(sCharacterID, vSkillPassives, vSkillActives, vSkillActionables, true);

    // Fill item indices
    TreeIndexArray vItemPassives;
    TreeIndexArray vItemActives;
    TreeIndexArray vItemActionables;
    ItemTree::FillItemStatChangeArrays(ItemTree::GetAllEquippedItems(sCharacterID), vItemPassives, vItemActives, vItemActionables);

    // Add to stored changes
    SetPassiveSkillDataArray(vSkillPassives);
    SetPassiveItemDataArray(vItemPassives);
    SetActiveSkillDataArray(vSkillActives);
    SetActiveItemDataArray(vItemActives);
    SetActionableSkillDataArray(vSkillActionables);
    SetActionableItemDataArray(vItemActionables);
}

const TreeIndexArray& CharacterStatChangeData::GetPassiveChanges(const String& sTreeIndexType) const
{
    const CharacterTreeIndexType eTreeIndexType = GetEnumFromString<CharacterTreeIndexType>(sTreeIndexType);
    switch(eTreeIndexType)
    {
        case CharacterTreeIndexType::Skill:
            return GetPassiveSkillDataArray();
        case CharacterTreeIndexType::Item:
            return GetPassiveItemDataArray();
        default:
            break;
    }
    THROW_RUNTIME_ERROR("Invalid or unknown tree index type requested: " + sTreeIndexType);
}

const TreeIndexArray& CharacterStatChangeData::GetActiveChanges(const String& sTreeIndexType) const
{
    const CharacterTreeIndexType eTreeIndexType = GetEnumFromString<CharacterTreeIndexType>(sTreeIndexType);
    switch(eTreeIndexType)
    {
        case CharacterTreeIndexType::Skill:
            return GetActiveSkillDataArray();
        case CharacterTreeIndexType::Item:
            return GetActiveItemDataArray();
        default:
            break;
    }
    THROW_RUNTIME_ERROR("Invalid or unknown tree index type requested: " + sTreeIndexType);
}

const TreeIndexArray& CharacterStatChangeData::GetActionableChanges(const String& sTreeIndexType) const
{
    const CharacterTreeIndexType eTreeIndexType = GetEnumFromString<CharacterTreeIndexType>(sTreeIndexType);
    switch(eTreeIndexType)
    {
        case CharacterTreeIndexType::Skill:
            return GetActionableSkillDataArray();
        case CharacterTreeIndexType::Item:
            return GetActionableItemDataArray();
        default:
            break;
    }
    THROW_RUNTIME_ERROR("Invalid or unknown tree index type requested: " + sTreeIndexType);
}

void CharacterStatChangeData::AddProlongedStatChange(const String& sKey, const ProlongedStatChange& change)
{
    GetProlongedStatChanges()[sKey] = change;
}

Bool CharacterStatChangeData::RemoveProlongedStatChange(const String& sKey)
{
    return (GetProlongedStatChanges().erase(sKey) > 0);
}

const ProlongedStatChange& CharacterStatChangeData::GetProlongedStatChange(const String& sKey) const
{
    return (GetProlongedStatChanges().at(sKey));
}

ProlongedStatChange& CharacterStatChangeData::GetProlongedStatChange(const String& sKey)
{
    return const_cast<ProlongedStatChange&>(static_cast<const CharacterStatChangeData&>(*this).GetProlongedStatChange(sKey));
}

StatChangeEntryArray CharacterStatChangeData::GetProlongedStatChangeEntries(Int iRound, Int iAttack, Int iDefend) const
{
    // Find all prolonged stat change entries that match current conditions
    StatChangeEntryArray vEntries;
    for(auto it = GetProlongedStatChanges().begin(); it != GetProlongedStatChanges().end(); it++)
    {
        // Ignore expired entries
        const String& sKey = String(it->first);
        if(HasProlongedStatChangeExpired(sKey, iRound, iAttack, iDefend))
        {
            continue;
        }

        // Find the only valid round/attack/defend and check if it matches
        const ProlongedStatChange& change = it->second;
        const StatChangeEntry& entry = change.GetStatChangeEntry();
        if(
            (change.GetRound() >= 0 && change.GetRound() == iRound) ||
            (change.GetAttack() >= 0 && change.GetAttack() == iAttack) ||
            (change.GetDefend() >= 0 && change.GetDefend() == iDefend))
        {
            vEntries.push_back(entry);
        }
    }
    return vEntries;
}

Bool CharacterStatChangeData::DoesProlongedStatChangeExist(const String& sKey) const
{
    return (GetProlongedStatChanges().find(sKey) != GetProlongedStatChanges().end());
}

Bool CharacterStatChangeData::HasProlongedStatChangeExpired(const String& sKey, Int iRound, Int iAttack, Int iDefend) const
{
    const ProlongedStatChange& change = GetProlongedStatChange(sKey);
    return (
        (change.GetRound() >= 0 && change.GetRound() < iRound) ||
        (change.GetAttack() >= 0 && change.GetAttack() < iAttack) ||
        (change.GetDefend() >= 0 && change.GetDefend() < iDefend)
    );
}

void CharacterStatChangeData::RemoveAllExpiredProlongedStatChanges(Int iRound, Int iAttack, Int iDefend)
{
    StringArray vKeys;
    for(auto it = GetProlongedStatChanges().begin(); it != GetProlongedStatChanges().end(); it++)
    {
        if(HasProlongedStatChangeExpired(String(it->first), iRound, iAttack, iDefend))
        {
            vKeys.push_back(String(it->first));
        }
    }

    for(const String& sKey : vKeys)
    {
        RemoveProlongedStatChange(sKey);
    }
}

void CharacterStatChangeData::ApplyProlongedStatChanges(const String& sCharacterID, const String& sSegment)
{
    const Character& character = CharacterManager::GetInstance()->GetCharacter(sCharacterID);
    Int iCurrentRound = BattleManager::GetInstance()->GetCurrentBattle().GetCurrentRoundIndex();
    Int iCurrentAttack = character.GetBattleData().GetAttackCounter();
    Int iCurrentDefend = character.GetBattleData().GetDefendCounter();
    for(auto& entry : GetProlongedStatChangeEntries(iCurrentRound, iCurrentAttack, iCurrentDefend))
    {
        CharacterManager::GetInstance()->ApplyStatChangeEntry(sSegment, entry);
    }
}

Bool CharacterStatChangeData::operator==(const CharacterStatChangeData& other) const
{
    return (Json(*this) == Json(other));
}

Bool CharacterStatChangeData::operator!=(const CharacterStatChangeData& other) const
{
    return not operator==(other);
}

void to_json(Json& jsonData, const CharacterStatChangeData& obj)
{
    // Passive data
    SET_JSON_DATA(PassiveSkillDataArray);
    SET_JSON_DATA(PassiveItemDataArray);

    // Active data
    SET_JSON_DATA(ActiveSkillDataArray);
    SET_JSON_DATA(ActiveItemDataArray);

    // Actionable data
    SET_JSON_DATA(ActionableSkillDataArray);
    SET_JSON_DATA(ActionableItemDataArray);
}

void from_json(const Json& jsonData, CharacterStatChangeData& obj)
{
    // Passive data
    SET_OBJ_DATA(PassiveSkillDataArray, TreeIndexArray);
    SET_OBJ_DATA(PassiveItemDataArray, TreeIndexArray);

    // Active data
    SET_OBJ_DATA(ActiveSkillDataArray, TreeIndexArray);
    SET_OBJ_DATA(ActiveItemDataArray, TreeIndexArray);

    // Actionable data
    SET_OBJ_DATA(ActionableSkillDataArray, TreeIndexArray);
    SET_OBJ_DATA(ActionableItemDataArray, TreeIndexArray);
}

};
