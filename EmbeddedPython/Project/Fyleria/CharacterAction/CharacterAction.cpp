// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

// Internal includes
#include "CharacterAction/CharacterAction.h"
#include "Character/CharacterManager.h"
#include "CharacterParty/CharacterPartyManager.h"
#include "Utility/Constants.h"

namespace Gecko
{

CharacterAction::CharacterAction()
{
}

CharacterAction::CharacterAction(const Json& jsonData)
{
    from_json(jsonData, *this);
}

CharacterAction::CharacterAction(const String& jsonString)
{
    from_json(JsonParse(jsonString), *this);
}

CharacterAction::~CharacterAction()
{
}

void CharacterAction::Clear()
{
    // Run type
    SetRunType("");

    // Order
    SetOrder(0);

    // Cost
    SetCostAP(0);
    SetCostHP(0);
    SetCostMP(0);
    SetCostEP(0);

    // Applicable weapon set
    SetWeaponSet("");

    // Action entries
    SetActionEntries({});

    // Previous action types
    SetPreviousActionTypes({});

    // Skill
    SetSkillTreeIndex({});

    // Item
    SetItemTreeIndex({});
    SetItemAmount(0);

    // Targets
    SetSourceTargetType("");

    // Characters
    SetSourceCharacterID("");
}

StringArray CharacterAction::GetAllCharacterIDs() const
{
    StringArray vAllCharacterIDs;
    if(!GetSourceCharacterID().empty())
    {
        vAllCharacterIDs.push_back(GetSourceCharacterID());
    }
    for(const CharacterActionEntry& entry : GetActionEntries())
    {
        vAllCharacterIDs.insert(
            vAllCharacterIDs.end(),
            entry.GetDestinationCharacterIDs().begin(),
            entry.GetDestinationCharacterIDs().end());
    }
    return vAllCharacterIDs;
}

StringArray CharacterAction::GetAllActionTypes() const
{
    StringArray vAllActionTypes;
    for(const CharacterActionEntry& entry : GetActionEntries())
    {
        vAllActionTypes.insert(vAllActionTypes.end(), entry.GetActionTypes().begin(), entry.GetActionTypes().end());
    }
    return vAllActionTypes;
}

StringArray CharacterAction::GetAllDestinationTargetTypes() const
{
    StringArray vAllDestinationTargetTypes;
    for(const CharacterActionEntry& entry : GetActionEntries())
    {
        vAllDestinationTargetTypes.push_back(entry.GetDestinationTargetType());
    }
    return vAllDestinationTargetTypes;
}

Bool CharacterAction::AreAllCharacterIDsValid() const
{
    StringArray vAllCharacterIDs = GetAllCharacterIDs();
    if(vAllCharacterIDs.empty())
    {
        return false;
    }
    for(const String& sCharacterID : vAllCharacterIDs)
    {
        if(!CharacterManager::GetInstance()->DoesCharacterExist(sCharacterID))
        {
            return false;
        }
    }
    return true;
}

Bool CharacterAction::PrepareCharacterIDs()
{
    // Get source character info if it's not already set
    if(GetSourceCharacterID().empty())
    {
        // Get source character info
        StringArray vSourceCharIDs;
        String sSourceTargetType = GetSourceTargetType();
        String sSourcePartyType = ConvertCharacterTargetTypeToCharacterPartyType(sSourceTargetType);
        CharacterPartyManager::GetInstance()->GetPartyByType(sSourcePartyType).GetCharacterIDsFromTargetType(sSourceTargetType, vSourceCharIDs);
        if(vSourceCharIDs.empty())
        {
            return false;
        }

        // Store source character ID
        SetSourceCharacterID(vSourceCharIDs.front());
    }

    // Do the same for each destination
    for(CharacterActionEntry& entry : GetActionEntries())
    {
        // Get destination character info
        StringArray vDestCharIDs;
        String sDestTargetType = entry.GetDestinationTargetType();
        String sDestPartyType = ConvertCharacterTargetTypeToCharacterPartyType(sDestTargetType);
        CharacterPartyManager::GetInstance()->GetPartyByType(sDestPartyType).GetCharacterIDsFromTargetType(sDestTargetType, vDestCharIDs);
        if(vDestCharIDs.empty())
        {
            return false;
        }

        // Store destination character IDs
        entry.SetDestinationCharacterIDs(vDestCharIDs);
    }
    return true;
}

void to_json(Json& jsonData, const CharacterAction& obj)
{
    // Run type
    SET_JSON_DATA(RunType);

    // Order
    SET_JSON_DATA(Order);

    // Cost
    SET_JSON_DATA(CostAP);
    SET_JSON_DATA(CostHP);
    SET_JSON_DATA(CostMP);
    SET_JSON_DATA(CostEP);

    // Applicable weapon set
    SET_JSON_DATA(WeaponSet);

    // Action entries
    SET_JSON_DATA(ActionEntries);

    // Previous action types
    SET_JSON_DATA(PreviousActionTypes);

    // Skill
    SET_JSON_DATA(SkillTreeIndex);

    // Item
    SET_JSON_DATA(ItemTreeIndex);
    SET_JSON_DATA(ItemAmount);

    // Targets
    SET_JSON_DATA(SourceTargetType);

    // Characters
    SET_JSON_DATA(SourceCharacterID);
}

void from_json(const Json& jsonData, CharacterAction& obj)
{
    // Run type
    SET_OBJ_DATA(RunType, String);

    // Order
    SET_OBJ_DATA(Order, Int);

    // Cost
    SET_OBJ_DATA(CostAP, Int);
    SET_OBJ_DATA(CostHP, Int);
    SET_OBJ_DATA(CostMP, Int);
    SET_OBJ_DATA(CostEP, Int);

    // Applicable weapon set
    SET_OBJ_DATA(WeaponSet, String);

    // Action entries
    SET_OBJ_DATA(ActionEntries, CharacterActionEntryArray);

    // Previous action types
    SET_OBJ_DATA(PreviousActionTypes, StringArray);

    // Skill
    SET_OBJ_DATA(SkillTreeIndex, TreeIndex);

    // Item
    SET_OBJ_DATA(ItemTreeIndex, TreeIndex);
    SET_OBJ_DATA(ItemAmount, Int);

    // Targets
    SET_OBJ_DATA(SourceTargetType, String);

    // Characters
    SET_OBJ_DATA(SourceCharacterID, String);
}

};
