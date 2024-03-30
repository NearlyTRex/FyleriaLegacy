// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#include "Character/CharacterAction.h"
#include "Character/CharacterActionBattleSkill.h"
#include "Character/CharacterActionBattleItem.h"
#include "Character/CharacterActionFieldSkill.h"
#include "Character/CharacterActionFieldItem.h"
#include "Character/CharacterManager.h"
#include "Character/CharacterPartyManager.h"
#include "Utility/Constants.h"

namespace Gecko
{

CharacterAction::CharacterAction()
    : PolymorphicBase(IndexedString("CharacterAction"))
    , STDEnableSharedFromThis<CharacterAction>()
{
    // Run type
    SetRunType(IndexedString("None"));

    // Order
    SetOrder(0);

    // Cost
    SetCostAP(0);
    SetCostHP(0);
    SetCostMP(0);
    SetCostEP(0);

    // Applicable weapon set
    SetWeaponSet(IndexedString("None"));

    // Actions
    SetPreviousActionTypes({});

    // Skill
    SetSkillTreeIndex({});

    // Item
    SetItemTreeIndex({});
    SetItemAmount(0);

    // Targets
    SetSourceTargetType(IndexedString("None"));
    SetAreDestinationTargetsIdentical(false);

    // Characters
    SetSourceCharacterID(IndexedString(""));
}

CharacterAction::CharacterAction(const Json& jsonData)
    : PolymorphicBase(jsonData)
    , STDEnableSharedFromThis<CharacterAction>()
{
    from_json(jsonData, *this);
}

IndexedStringList CharacterAction::GetAllCharacterIDs() const
{
    IndexedStringList vAllCharacterIDs;
    vAllCharacterIDs.push_back(GetSourceCharacterID());
    for(const CharacterActionEntry& entry : GetActionEntries())
    {
        vAllCharacterIDs.push_back(entry.GetDestinationCharacterID());
    }
    return vAllCharacterIDs;
}

IndexedStringList CharacterAction::GetAllActionTypes() const
{
    IndexedStringList vAllActionTypes;
    for(const CharacterActionEntry& entry : GetActionEntries())
    {
        vAllActionTypes.insert(vAllActionTypes.end(), entry.GetActionTypes().begin(), entry.GetActionTypes().end());
    }
    return vAllActionTypes;
}

IndexedStringList CharacterAction::GetAllDestinationTargetTypes() const
{
    IndexedStringList vAllDestinationTargetTypes;
    for(const CharacterActionEntry& entry : GetActionEntries())
    {
        vAllDestinationTargetTypes.push_back(entry.GetDestinationTargetType());
    }
    return vAllDestinationTargetTypes;
}

Bool CharacterAction::AreAllCharacterIDsValid() const
{
    for(const IndexedString& sCharacterID : GetAllCharacterIDs())
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
        IndexedStringList vSourceCharIDs;
        IndexedString sSourceTargetType = GetSourceTargetType();
        IndexedString sSourcePartyType = ConvertCharacterTargetTypeToCharacterPartyType(sSourceTargetType);
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
        IndexedStringList vDestCharIDs;
        IndexedString sDestTargetType = entry.GetDestinationTargetType();
        IndexedString sDestPartyType = ConvertCharacterTargetTypeToCharacterPartyType(sDestTargetType);
        CharacterPartyManager::GetInstance()->GetPartyByType(sDestPartyType).GetCharacterIDsFromTargetType(sDestTargetType, vDestCharIDs);
        if(vDestCharIDs.empty())
        {
            return false;
        }

        // Store destination character ID
        entry.SetDestinationCharacterID(vDestCharIDs.front());
    }
    return true;
}

Bool CharacterAction::Setup()
{
    return false;
}

Bool CharacterAction::Finish()
{
    return false;
}

Bool CharacterAction::GenerateResult()
{
    return false;
}

Bool CharacterAction::ApplyResult()
{
    return false;
}

CharacterActionSharedPtr MakePolymorphicCharacterAction(const Json& jsonData)
{
    PolymorphicBase base(jsonData);
    if(base.GetTypeName() == CharacterActionBattleSkill().GetTypeName())
    {
        return STDMakeSharedPtr<CharacterActionBattleSkill>(jsonData);
    }
    else if(base.GetTypeName() == CharacterActionFieldSkill().GetTypeName())
    {
        return STDMakeSharedPtr<CharacterActionFieldSkill>(jsonData);
    }
    else if(base.GetTypeName() == CharacterActionBattleItem().GetTypeName())
    {
        return STDMakeSharedPtr<CharacterActionBattleItem>(jsonData);
    }
    else if(base.GetTypeName() == CharacterActionFieldItem().GetTypeName())
    {
        return STDMakeSharedPtr<CharacterActionFieldItem>(jsonData);
    }
    return CharacterActionSharedPtr();
}

void to_json(Json& jsonData, const CharacterAction& obj)
{
    // Run type
    SET_JSON_DATA_IF_NOT_DEFAULT(RunType, IndexedString("None"));

    // Order
    SET_JSON_DATA_IF_NOT_DEFAULT(Order, 0);

    // Cost
    SET_JSON_DATA_IF_NOT_DEFAULT(CostAP, 0);
    SET_JSON_DATA_IF_NOT_DEFAULT(CostHP, 0);
    SET_JSON_DATA_IF_NOT_DEFAULT(CostMP, 0);
    SET_JSON_DATA_IF_NOT_DEFAULT(CostEP, 0);

    // Applicable weapon set
    SET_JSON_DATA_IF_NOT_DEFAULT(WeaponSet, IndexedString("None"));

    // Action entries
    SET_JSON_DATA_IF_NOT_EMPTY(ActionEntries);

    // Previous action types
    SET_JSON_DATA_IF_NOT_EMPTY(PreviousActionTypes);

    // Skill
    SET_JSON_DATA_IF_NOT_EMPTY(SkillTreeIndex);

    // Item
    SET_JSON_DATA_IF_NOT_EMPTY(ItemTreeIndex);
    SET_JSON_DATA_IF_NOT_DEFAULT(ItemAmount, 0);

    // Targets
    SET_JSON_DATA_IF_NOT_DEFAULT(SourceTargetType, IndexedString("None"));
    SET_JSON_DATA_IF_NOT_DEFAULT(AreDestinationTargetsIdentical, false);

    // Characters
    SET_JSON_DATA_IF_NOT_DEFAULT(SourceCharacterID, IndexedString(""));
}

void to_json(Json& jsonData, const CharacterActionSharedPtr& pObj)
{
    if(pObj)
    {
        jsonData = *pObj;
    }
}

void to_json(Json& jsonData, const CharacterActionSharedPtrList& vObjs)
{
    // Convert obj array to json array
    jsonData = JsonArray();
    for(auto& pObj : vObjs)
    {
        if(pObj)
        {
            jsonData.push_back(*pObj);
        }
    }
}

void from_json(const Json& jsonData, CharacterAction& obj)
{
    // Run type
    obj.SetRunType(GET_JSON_DATA_OR_DEFAULT(RunType, IndexedString, IndexedString("None")));

    // Order
    obj.SetOrder(GET_JSON_DATA_OR_DEFAULT(Order, Int, 0));

    // Cost
    obj.SetCostAP(GET_JSON_DATA_OR_DEFAULT(CostAP, Int, 0));
    obj.SetCostHP(GET_JSON_DATA_OR_DEFAULT(CostHP, Int, 0));
    obj.SetCostMP(GET_JSON_DATA_OR_DEFAULT(CostMP, Int, 0));
    obj.SetCostEP(GET_JSON_DATA_OR_DEFAULT(CostEP, Int, 0));

    // Applicable weapon set
    obj.SetWeaponSet(GET_JSON_DATA_OR_DEFAULT(WeaponSet, IndexedString, IndexedString("None")));

    // Action entries
    obj.SetActionEntries(GET_JSON_DATA_OR_DEFAULT(ActionEntries, CharacterActionEntryList, CharacterActionEntryList()));

    // Previous action types
    obj.SetPreviousActionTypes(GET_JSON_DATA_OR_DEFAULT(PreviousActionTypes, IndexedStringList, IndexedStringList()));

    // Skill
    obj.SetSkillTreeIndex(GET_JSON_DATA_OR_DEFAULT(SkillTreeIndex, TreeIndex, TreeIndex()));

    // Item
    obj.SetItemTreeIndex(GET_JSON_DATA_OR_DEFAULT(ItemTreeIndex, TreeIndex, TreeIndex()));
    obj.SetItemAmount(GET_JSON_DATA_OR_DEFAULT(ItemAmount, Int, 0));

    // Targets
    obj.SetSourceTargetType(GET_JSON_DATA_OR_DEFAULT(SourceTargetType, IndexedString, IndexedString("None")));
    obj.SetAreDestinationTargetsIdentical(GET_JSON_DATA_OR_DEFAULT(AreDestinationTargetsIdentical, Bool, false));

    // Characters
    obj.SetSourceCharacterID(GET_JSON_DATA_OR_DEFAULT(SourceCharacterID, IndexedString, IndexedString("")));
}

void from_json(const Json& jsonData, CharacterActionSharedPtr& pObj)
{
    pObj = MakePolymorphicCharacterAction(jsonData);
}

void from_json(const Json& jsonData, CharacterActionSharedPtrList& vObjs)
{
    // Convert json array to obj array
    vObjs.clear();
    for (auto it = jsonData.begin(); it != jsonData.end(); ++it)
    {
        vObjs.push_back(MakePolymorphicCharacterAction(*it));
    }
}

MAKE_JSON_GENERIC_TYPE_CONVERTERS_IMPL(CharacterAction, CharacterActionSharedPtr);

};
