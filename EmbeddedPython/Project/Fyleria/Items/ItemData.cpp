// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

// Internal includes
#include "Items/ItemData.h"
#include "CharacterAction/CharacterAction.h"
#include "Character/CharacterManager.h"

namespace Gecko
{

ItemData::ItemData()
{
}

ItemData::ItemData(const Json& jsonData)
{
    from_json(jsonData, *this);
}

ItemData::~ItemData()
{
}

void ItemData::Clear()
{
    // Run types
    SetRunTypes({});

    // Data class
    SetDataClass("");

    // Item name
    SetItemName("");

    // Item description
    SetItemDescription("");

    // Item type
    SetItemType("");

    // Action types
    SetActionTypes({});

    // Item index
    SetItemTreeIndex({});

    // Stat changes
    SetStatChanges({});
}

Bool ItemData::IsActionable() const
{
    // First check that all the necessary information is filled out
    if(GetRunTypes().empty() ||
       GetDataClass().empty() ||
       GetItemName().empty() ||
       GetItemDescription().empty() ||
       GetItemType().empty())
    {
        return false;
    }

    // Check if action types is empty
    if(GetActionTypes().empty())
    {
        return false;
    }
    return true;
}

Bool ItemData::DoesMeetActionRequirements(const String& sCharacterID, const String& sWeaponSet) const
{
    // Check character
    if(!CharacterManager::GetInstance()->DoesCharacterExist(sCharacterID))
    {
        return false;
    }

    // Check each of the stat changes against the equipped items and their action types
    for(const StatChange& change : GetStatChanges())
    {
        if(change.DoesHaveItemUsedRequirements())
        {
            return change.DoesMeetItemUsedRequirements(GetActionTypes());
        }
        else if(change.DoesHaveItemEquippedRequirements())
        {
            return change.DoesMeetItemEquippedRequirements(sCharacterID, sWeaponSet);
        }
    }
    return false;
}

CharacterActionArray ItemData::CreateBaseActions(const String& sCharacterID, const String& sWeaponSet) const
{
    // Check character
    CharacterActionArray vNewActions;
    if(!CharacterManager::GetInstance()->DoesCharacterExist(sCharacterID))
    {
        return vNewActions;
    }

    // Get character
    const Character& character = CharacterManager::GetInstance()->GetCharacter(sCharacterID);

    // Create actions
    for(auto& sType : GetRunTypes())
    {
        CharacterAction newAction;
        newAction.SetRunType(sType);
        newAction.SetWeaponSet(sWeaponSet);
        newAction.SetItemTreeIndex(GetItemTreeIndex());
        newAction.SetSourceTargetType(character.GetCharacterTargetType());
        newAction.SetSourceCharacterID(sCharacterID);
        vNewActions.push_back(newAction);
    }
    return vNewActions;
}

void to_json(Json& jsonData, const ItemData& obj)
{
    // Run types
    SET_JSON_DATA(RunTypes);

    // Data class
    SET_JSON_DATA(DataClass);

    // Item name
    SET_JSON_DATA(ItemName);

    // Item description
    SET_JSON_DATA(ItemDescription);

    // Item type
    SET_JSON_DATA(ItemType);

    // Item index
    SET_JSON_DATA(ItemTreeIndex);

    // Action types
    SET_JSON_DATA(ActionTypes);

    // Stat changes
    SET_JSON_DATA(StatChanges);
}

void from_json(const Json& jsonData, ItemData& obj)
{
    // Run types
    SET_OBJ_DATA(RunTypes, StringArray);

    // Data class
    SET_OBJ_DATA(DataClass, String);

    // Item name
    SET_OBJ_DATA(ItemName, String);

    // Item description
    SET_OBJ_DATA(ItemDescription, String);

    // Item type
    SET_OBJ_DATA(ItemType, String);

    // Item index
    SET_OBJ_DATA(ItemTreeIndex, TreeIndex);

    // Action types
    SET_OBJ_DATA(ActionTypes, StringArray);

    // Stat changes
    SET_OBJ_DATA(StatChanges, StatChangeArray);
}

};
