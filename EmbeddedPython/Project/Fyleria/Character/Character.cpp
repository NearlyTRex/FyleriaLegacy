// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

// Internal includes
#include "Character/Character.h"
#include "Character/CharacterManager.h"
#include "CharacterParty/CharacterPartyManager.h"
#include "Character/CharacterTypes.h"
#include "Config/ConfigManager.h"
#include "Battle/BattleManager.h"
#include "Items/ItemTypes.h"
#include "Utility/Constants.h"
#include "Utility/Errors.h"
#include "Utility/Enum.h"

namespace Gecko
{

Character::Character()
{
}

Character::Character(const Json& jsonData)
{
    from_json(jsonData, *this);
}

Character::Character(const String& jsonString)
{
    from_json(JsonParse(jsonString), *this);
}

void Character::Clear()
{
    // Progress data
    GetProgressData().Clear();
    GetProgressDataPassives().Clear();
    GetProgressDataActives().Clear();

    // Battle data
    GetBattleData().Clear();
    GetBattleDataPassives().Clear();
    GetBattleDataActives().Clear();

    // Basic data
    GetBasicData().Clear();

    // Action data
    GetActionData().Clear();

    // Skill data
    GetSkillData().Clear();

    // Stat change data
    GetStatChangeData().Clear();
}

void Character::RegenerateCharacterData(
    Bool bUpdateEquipmentRatings /*= true*/,
    Bool bUpdateAvailableChanges /*= true*/,
    Bool bUpdateAvailableActions /*= true*/,
    Bool bUpdateAvailableAP /*= true*/
)
{
    // Reset all non-base data
    GetProgressDataPassives().Clear();
    GetBattleDataPassives().Clear();
    GetProgressDataActives().Clear();
    GetBattleDataActives().Clear();

    // Update character data
    if(bUpdateEquipmentRatings) { UpdateEquipmentRatings(); }
    if(bUpdateAvailableChanges) { UpdateAvailableChanges(); }
    if(bUpdateAvailableActions) { UpdateAvailableActions(); }
    if(bUpdateAvailableAP) { UpdateAvailableAP(); }

    // Apply passives
    ApplyPassiveChanges();

    // Display the new data
#ifdef DEBUG
    Json jsonData = *this;
    LOG_FORMAT_STATEMENT("Completed regenerating character data (CharacterID = '{}'):\n{}\n",
        GetBasicData().GetCharacterID().c_str(),
        jsonData.dump(4).c_str());
#endif
}

String Character::GetCharacterID() const
{
    return GetBasicData().GetCharacterID();
}

String Character::GetPartyID() const
{
    return GetBasicData().GetPartyID();
}

String Character::GetCharacterTargetType() const
{
    String sCharacterID = GetCharacterID();
    String sPartyID = GetPartyID();
    if(sPartyID.empty())
    {
        return GetNoneTypeForEnum<CharacterResolvedTargetType>();
    }

    const CharacterParty& characterParty = CharacterPartyManager::GetInstance()->GetPartyByID(sPartyID);
    const CharacterPartyMember& characterPartyMember = characterParty.GetMemberByID(sCharacterID);
    return characterPartyMember.GetCharacterTargetType();
}

String Character::GetWeaponSet() const
{
    return GetBasicData().GetWeaponSet();
}

CharacterPartyEquippedItemArray Character::GetEquippedItems() const
{
    String sCharacterID = GetCharacterID();
    String sPartyID = GetPartyID();
    if(sPartyID.empty())
    {
        return CharacterPartyEquippedItemArray();
    }

    const CharacterParty& characterParty = CharacterPartyManager::GetInstance()->GetPartyByID(sPartyID);
    const CharacterPartyMember& characterPartyMember = characterParty.GetMemberByID(sCharacterID);
    return characterPartyMember.GetEquippedItems();
}

TreeIndex Character::GetEquippedItemByType(const String& sEquipmentType) const
{
    auto vEquippedItems = GetEquippedItems();
    if(vEquippedItems.empty())
    {
        return TreeIndex();
    }
    for(auto it = vEquippedItems.begin(); it != vEquippedItems.end(); it++)
    {
        if(it->GetItemSlot() == sEquipmentType)
        {
            return it->GetItemTreeIndex();
        }
    }
    return TreeIndex();
}

const CharacterActionArray& Character::GetAvailableActions() const
{
    return GetActionData().GetAvailableActions();
}

const TreeIndexArray& Character::GetPassiveChanges(const String& sTreeIndexType) const
{
    return GetStatChangeData().GetPassiveChanges(sTreeIndexType);
}

const TreeIndexArray& Character::GetActiveChanges(const String& sTreeIndexType) const
{
    return GetStatChangeData().GetActiveChanges(sTreeIndexType);
}

const TreeIndexArray& Character::GetActionableChanges(const String& sTreeIndexType) const
{
    return GetStatChangeData().GetActionableChanges(sTreeIndexType);
}

const CharacterProgressData& Character::GetProgressDataSegment(const String& sSegment) const
{
    CharacterSegmentType eSegmentType = GetEnumFromString<CharacterSegmentType>(sSegment);
    switch(eSegmentType)
    {
        case CharacterSegmentType::Base: return GetProgressData();
        case CharacterSegmentType::Passive: return GetProgressDataPassives();
        case CharacterSegmentType::Active: return GetProgressDataActives();
        default: break;
    }
    THROW_RUNTIME_ERROR("Invalid or unknown segment requested: " + sSegment);
}

CharacterProgressData& Character::GetProgressDataSegment(const String& sSegment)
{
    return const_cast<CharacterProgressData&>(static_cast<const Character&>(*this).GetProgressDataSegment(sSegment));
}

const CharacterBattleData& Character::GetBattleDataSegment(const String& sSegment) const
{
    CharacterSegmentType eSegmentType = GetEnumFromString<CharacterSegmentType>(sSegment);
    switch(eSegmentType)
    {
        case CharacterSegmentType::Base: return GetBattleData();
        case CharacterSegmentType::Passive: return GetBattleDataPassives();
        case CharacterSegmentType::Active: return GetBattleDataActives();
        default: break;
    }
    THROW_RUNTIME_ERROR("Invalid or unknown segment requested: " + sSegment);
}

CharacterBattleData& Character::GetBattleDataSegment(const String& sSegment)
{
    return const_cast<CharacterBattleData&>(static_cast<const Character&>(*this).GetBattleDataSegment(sSegment));
}

Bool Character::operator==(const Character& other) const
{
    return (Json(*this) == Json(other));
}

Bool Character::operator!=(const Character& other) const
{
    return not operator==(other);
}

void Character::UpdateEquipmentRatings()
{
    // Update equipment ratings
    GetBattleData().UpdateEquipmentRatings(GetCharacterID(), (+CharacterSegmentType::Base)._to_string());
}

void Character::UpdateAvailableChanges()
{
    // Update available changes
    GetStatChangeData().UpdateAvailableChanges(GetCharacterID());
}

void Character::UpdateAvailableActions()
{
    // Update available actions
    GetActionData().UpdateAvailableActions(GetCharacterID());
}

void Character::UpdateAvailableAP()
{
    // Update available AP
    GetActionData().UpdateAvailableAP(GetCharacterID());
}

void Character::ApplyPassiveChanges()
{
    // Data sources should come from base but apply to passive
    const String sSourceSegment("Base");
    const String sDestSegment("Passive");

    // Copy base data into passive to start with
    SetProgressDataPassives(GetProgressData());
    SetBattleDataPassives(GetBattleData());

    // Apply passives
    for(const String& sTreeIndexType : CharacterTreeIndexType::_names())
    {
        if(IsNoneTypeForEnum<CharacterTreeIndexType>(sTreeIndexType))
        {
            continue;
        }
        for(const TreeIndex& treeIndex : GetStatChangeData().GetPassiveChanges(sTreeIndexType))
        {
            for(StatChange change : GetStatChangesFromTreeIndex(sTreeIndexType, treeIndex))
            {
                // Resolve target placeholders
                change.ResolveTargetPlaceholders(GetCharacterID(), sSourceSegment);

                // Apply change
                Bool bAllChangesApplied = false;
                Bool bAtLeastOneChange = false;
                CharacterManager::GetInstance()->ApplyStatChange(sDestSegment, change, bAllChangesApplied, bAtLeastOneChange);
            }
        }
    }
}

void Character::ApplyActiveChanges(const CharacterAction& action)
{
    // Data sources should come from passive but apply to active
    const String sSourceSegment("Passive");
    const String sDestSegment("Active");

    // Copy passive data into active to start with
    SetProgressDataActives(GetProgressDataPassives());
    SetBattleDataActives(GetBattleDataPassives());

    // Apply actives
    for(const String& sTreeIndexType : CharacterTreeIndexType::_names())
    {
        if(IsNoneTypeForEnum<CharacterTreeIndexType>(sTreeIndexType))
        {
            continue;
        }
        for(const TreeIndex& treeIndex : GetStatChangeData().GetActiveChanges(sTreeIndexType))
        {
            for(const StatChange& change : GetStatChangesFromTreeIndex(sTreeIndexType, treeIndex))
            {
                // Ignore active changes that do not meet requirements
                if(!change.DoesMeetActiveRequirements(GetCharacterID(), GetCharacterTargetType(), GetWeaponSet(), action))
                {
                    continue;
                }

                // Make a local copy now that we have passed the check
                StatChange localStatChange(change);

                // Resolve target placeholders
                localStatChange.ResolveTargetPlaceholders(GetCharacterID(), sSourceSegment);

                // Apply change
                Bool bAllChangesApplied = false;
                Bool bAtLeastOneChange = false;
                CharacterManager::GetInstance()->ApplyStatChange(sDestSegment, localStatChange, bAllChangesApplied, bAtLeastOneChange);
            }
        }
    }

    // Apply prolonged stat changes
    GetStatChangeData().ApplyProlongedStatChanges(GetCharacterID(), sDestSegment);
}

void Character::ClearActiveChanges()
{
    GetProgressDataActives().Clear();
    GetBattleDataActives().Clear();
}

void to_json(Json& jsonData, const Character& obj)
{
    // Segmented progress data
    SET_JSON_DATA(ProgressData);
    SET_JSON_DATA(ProgressDataPassives);

    // Segmented battle data
    SET_JSON_DATA(BattleData);
    SET_JSON_DATA(BattleDataPassives);

    // Basic data
    SET_JSON_DATA(BasicData);

    // Action data
    SET_JSON_DATA(ActionData);

    // Skill data
    SET_JSON_DATA(SkillData);

    // Stat change data
    SET_JSON_DATA(StatChangeData);

    // Media data
    SET_JSON_DATA(MediaData);
}

void from_json(const Json& jsonData, Character& obj)
{
    // Segmented progress data
    SET_OBJ_DATA(ProgressData, CharacterProgressData);
    SET_OBJ_DATA(ProgressDataPassives, CharacterProgressData);

    // Segmented battle data
    SET_OBJ_DATA(BattleData, CharacterBattleData);
    SET_OBJ_DATA(BattleDataPassives, CharacterBattleData);

    // Basic data
    SET_OBJ_DATA(BasicData, CharacterBasicData);

    // Action data
    SET_OBJ_DATA(ActionData, CharacterActionData);

    // Skill data
    SET_OBJ_DATA(SkillData, CharacterSkillData);

    // Stat change data
    SET_OBJ_DATA(StatChangeData, CharacterStatChangeData);

    // Media data
    SET_OBJ_DATA(MediaData, CharacterMediaData);
}

Json GetSaveableData(const Character& obj)
{
    // Ouput data
    Json jsonData;

    // Progress data
    SET_JSON_DATA(ProgressData);

    // Basic data
    SET_JSON_DATA(BasicData);

    // Skill data
    SET_JSON_DATA(SkillData);

    // Media data
    SET_JSON_DATA(MediaData);

    // Return saveable data
    return jsonData;
}

Bool operator==(const Character& a, const Character& b)
{
    return (a.GetBasicData().GetCharacterID() == b.GetBasicData().GetCharacterID());
}

};
