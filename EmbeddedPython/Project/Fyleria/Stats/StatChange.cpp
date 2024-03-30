// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

// Internal includes
#include "Stats/StatChange.h"
#include "Character/CharacterManager.h"
#include "CharacterParty/CharacterPartyManager.h"
#include "Items/ItemTree.h"
#include "Items/ItemTypes.h"
#include "Skills/SkillTypes.h"
#include "Skills/SkillTree.h"
#include "Utility/Errors.h"
#include "Utility/Templates.h"

namespace Gecko
{

StatChange::StatChange()
{
    SetID(GenerateNewID());
}

StatChange::StatChange(const Json& jsonData)
{
    from_json(jsonData, *this);
}

StatChange::~StatChange()
{
}

void StatChange::Clear()
{
    // Relevant skill data
    SetSkillTreeIndex({});

    // Relevant item data
    SetItemTreeIndex({});

    // Percent chance to apply this change
    SetChanceToApply(0);

    // Amount of rounds to apply this change (0 is indefinite)
    SetRoundAmount(0);

    // Amount of attacks to apply this change (0 is indefinite)
    SetAttackAmount(0);

    // Amount of defends to apply this change (0 is indefinite)
    SetDefendAmount(0);

    // Required items or attack types
    SetRequiredItemEquippedTypesOR({});
    SetRequiredItemEquippedTypesAND({});
    SetRequiredItemUsedTypesOR({});
    SetRequiredItemUsedTypesAND({});
    SetRequiredAttackTypesOR({});
    SetRequiredAttackTypesAND({});
    SetRequiredDefendTypesOR({});
    SetRequiredDefendTypesAND({});
    SetRequiredPreviousAttackTypesOR({});
    SetRequiredPreviousAttackTypesAND({});
    SetRequiredPreviousDefendTypesOR({});
    SetRequiredPreviousDefendTypesAND({});
    SetRequiredEquippedWeaponCount(0);
    SetRequiredEquippedShieldCount(0);

    // Whether destination target is the same as the source target
    SetDestinationIsSource(false);

    // Source and destination targets
    SetSourceTargetType("");
    SetDestinationTargetType("");

    // Stat change entry list
    SetStatChangeEntries({});
}

ULongLong StatChange::GenerateNewID()
{
    static AtomicULongLong s_uCurrentCount(0);
    s_uCurrentCount++;
    return s_uCurrentCount;
}

Bool StatChange::IsActive() const
{
    if(GetChanceToApply() > 0)
    {
        return true;
    }
    else if(GetRoundAmount() > 0)
    {
        return true;
    }
    else if(GetAttackAmount() > 0)
    {
        return true;
    }
    else if(GetDefendAmount() > 0)
    {
        return true;
    }
    else if(DoesHaveActiveRequirements())
    {
        return true;
    }
    return false;
}

Bool StatChange::IsPassive() const
{
    return !IsActive();
}

Bool StatChange::DoesHaveActiveRequirements() const
{
    return (
        DoesHaveItemEquippedRequirements() ||
        DoesHaveItemUsedRequirements() ||
        DoesHaveAttackRequirements() ||
        DoesHaveDefendRequirements()
    );
}

Bool StatChange::DoesHaveItemEquippedRequirements() const
{
    return (
        (GetRequiredEquippedWeaponCount() > 0) ||
        (GetRequiredEquippedShieldCount() > 0) ||
        (!GetRequiredItemEquippedTypesOR().empty()) ||
        (!GetRequiredItemEquippedTypesAND().empty())
    );
}

Bool StatChange::DoesHaveItemUsedRequirements() const
{
    return (
        (!GetRequiredItemUsedTypesOR().empty()) ||
        (!GetRequiredItemUsedTypesAND().empty())
    );
}

Bool StatChange::DoesHaveAttackRequirements() const
{
    return (
        (!GetRequiredAttackTypesOR().empty()) ||
        (!GetRequiredAttackTypesAND().empty()) ||
        (!GetRequiredPreviousAttackTypesOR().empty()) ||
        (!GetRequiredPreviousAttackTypesAND().empty())
    );
}

Bool StatChange::DoesHaveDefendRequirements() const
{
    return (
        (!GetRequiredDefendTypesOR().empty()) ||
        (!GetRequiredDefendTypesAND().empty()) ||
        (!GetRequiredPreviousDefendTypesOR().empty()) ||
        (!GetRequiredPreviousDefendTypesAND().empty())
    );
}

Bool StatChange::DoesMeetItemEquippedRequirements(const String& sCharacterID, const String& sWeaponSet) const
{
    // Check character first
    if(!CharacterManager::GetInstance()->DoesCharacterExist(sCharacterID))
    {
        return false;
    }

    // Get character
    const Character& character = CharacterManager::GetInstance()->GetCharacter(sCharacterID);
    if(character.GetPartyID().empty())
    {
        return false;
    }

    // Get party
    const CharacterParty& party = CharacterPartyManager::GetInstance()->GetPartyByID(character.GetPartyID());
    const CharacterPartyMember& partyMember = party.GetMemberByID(sCharacterID);

    // Get equipped item types
    StringArray vEquippedItemTypes;
    for(auto&& item : partyMember.GetEquippedItems())
    {
        vEquippedItemTypes.push_back(ItemTree::RetrieveItemType(item.GetItemTreeIndex()));
    }

    // Get equipped item counts
    const UInt uActualWeaponCount = partyMember.GetEquippedWeaponCount(sWeaponSet);
    const UInt uActualShieldCount = partyMember.GetEquippedShieldCount(sWeaponSet);

    // Get some info regarding this change
    const UInt uChangeRequiredWeaponCount = GetRequiredEquippedWeaponCount();
    const UInt uChangeRequiredShieldCount = GetRequiredEquippedShieldCount();
    const StringArray vChangeRequiredItemEquippedTypesOR = GetRequiredItemEquippedTypesOR();
    const StringArray vChangeRequiredItemEquippedTypesAND = GetRequiredItemEquippedTypesAND();

    // Change requires certain amounts of weapon or shields
    if(uChangeRequiredWeaponCount > 0)
    {
        return (uChangeRequiredWeaponCount == uActualWeaponCount);
    }
    else if(uChangeRequiredShieldCount > 0)
    {
        return (uChangeRequiredShieldCount == uActualShieldCount);
    }

    // Change requires specific equipped items
    else if(!vChangeRequiredItemEquippedTypesOR.empty())
    {
        return DoesVectorIntersectOR<String>(vEquippedItemTypes, vChangeRequiredItemEquippedTypesOR);
    }
    else if(!vChangeRequiredItemEquippedTypesAND.empty())
    {
        return DoesVectorIntersectAND<String>(vEquippedItemTypes, vChangeRequiredItemEquippedTypesAND);
    }
    return false;
}

Bool StatChange::DoesMeetItemUsedRequirements(const StringArray& vActionItemTypes) const
{
    // Check action item types
    if(vActionItemTypes.empty())
    {
        return false;
    }

    // Get some info regarding this change
    const StringArray vChangeRequiredItemsUsedOR = GetRequiredItemUsedTypesOR();
    const StringArray vChangeRequiredItemsUsedAND = GetRequiredItemUsedTypesAND();

    // The item type being used by the action matches the change requirement
    if(!vChangeRequiredItemsUsedOR.empty() && !vActionItemTypes.front().empty())
    {
        return DoesVectorIntersectOR<String>(vActionItemTypes, vChangeRequiredItemsUsedOR);
    }
    else if(!vChangeRequiredItemsUsedAND.empty() && !vActionItemTypes.front().empty())
    {
        return DoesVectorIntersectAND<String>(vActionItemTypes, vChangeRequiredItemsUsedAND);
    }
    return false;
}

Bool StatChange::DoesMeetAttackRequirements(const StringArray& vActionTypes) const
{
    // Get some info regarding this change
    const StringArray vChangeRequiredAttackTypesOR = GetRequiredAttackTypesOR();
    const StringArray vChangeRequiredAttackTypesAND = GetRequiredAttackTypesAND();

    // Our character is sending action, and the action's types match the required attack types
    if(!vActionTypes.empty() && !vChangeRequiredAttackTypesOR.empty())
    {
        return DoesVectorIntersectOR<String>(vActionTypes, vChangeRequiredAttackTypesOR);
    }
    else if(!vActionTypes.empty() && !vChangeRequiredAttackTypesAND.empty())
    {
        return DoesVectorIntersectAND<String>(vActionTypes, vChangeRequiredAttackTypesAND);
    }
    return false;
}

Bool StatChange::DoesMeetAttackRequirements(const StringArray& vActionTypes, const StringArray& vPreviousActionTypes) const
{
    // Check non-previous action types
    if(!DoesMeetAttackRequirements(vActionTypes))
    {
        return false;
    }

    // Get some info regarding this change
    const StringArray vChangeRequiredPreviousAttackTypesOR = GetRequiredPreviousAttackTypesOR();
    const StringArray vChangeRequiredPreviousAttackTypesAND = GetRequiredPreviousAttackTypesAND();

    // Our character is sending action, and the action's previous types match the required previous attack types
    if(!vPreviousActionTypes.empty() && !vChangeRequiredPreviousAttackTypesOR.empty())
    {
        return DoesVectorIntersectOR<String>(vPreviousActionTypes, vChangeRequiredPreviousAttackTypesOR);
    }
    else if(!vPreviousActionTypes.empty() && !vChangeRequiredPreviousAttackTypesAND.empty())
    {
        return DoesVectorIntersectAND<String>(vPreviousActionTypes, vChangeRequiredPreviousAttackTypesAND);
    }
    return false;
}

Bool StatChange::DoesMeetDefendRequirements(const StringArray& vActionTypes) const
{
    // Get some info regarding this change
    const StringArray vChangeRequiredDefendTypesOR = GetRequiredDefendTypesOR();
    const StringArray vChangeRequiredDefendTypesAND = GetRequiredDefendTypesAND();

    // Our character is receiving action, and the action's types match the required defend types
    if(!vActionTypes.empty() && !vChangeRequiredDefendTypesOR.empty())
    {
        return DoesVectorIntersectOR<String>(vActionTypes, vChangeRequiredDefendTypesOR);
    }
    else if(!vActionTypes.empty() && !vChangeRequiredDefendTypesAND.empty())
    {
        return DoesVectorIntersectAND<String>(vActionTypes, vChangeRequiredDefendTypesAND);
    }
    return false;
}

Bool StatChange::DoesMeetDefendRequirements(const StringArray& vActionTypes, const StringArray& vPreviousActionTypes) const
{
    // Check non-previous action types
    if(!DoesMeetDefendRequirements(vActionTypes))
    {
        return false;
    }

    // Get some info regarding this change
    const StringArray vChangeRequiredPreviousDefendTypesOR = GetRequiredPreviousDefendTypesOR();
    const StringArray vChangeRequiredPreviousDefendTypesAND = GetRequiredPreviousDefendTypesAND();

    // Our character is receiving action, and the action's previous types match the required previous defend types
    if(!vPreviousActionTypes.empty() && !vChangeRequiredPreviousDefendTypesOR.empty())
    {
        return DoesVectorIntersectOR<String>(vPreviousActionTypes, vChangeRequiredPreviousDefendTypesOR);
    }
    else if(!vPreviousActionTypes.empty() && !vChangeRequiredPreviousDefendTypesAND.empty())
    {
        return DoesVectorIntersectAND<String>(vPreviousActionTypes, vChangeRequiredPreviousDefendTypesAND);
    }
    return false;
}

Bool StatChange::DoesMeetActiveRequirements(const String& sCharacterID, const String& sWeaponSet) const
{
    // Check change requirements
    if(DoesHaveItemEquippedRequirements() && DoesMeetItemEquippedRequirements(sCharacterID, sWeaponSet))
    {
        return true;
    }
    return false;
}

Bool StatChange::DoesMeetActiveRequirements(const String& sCharacterID, const String& sCharacterTargetType, const String& sWeaponSet, const CharacterAction& action) const
{
    // Make sure there are some entries first
    if(action.GetActionEntries().empty())
    {
        return false;
    }

    // Find out target information for action
    Bool bSelfIsActionSender = (sCharacterTargetType == action.GetSourceTargetType());
    Bool bSelfIsActionRecipient = DoesVectorIntersectElement<String>(action.GetAllDestinationTargetTypes(), sCharacterTargetType);

    // Check change requirements
    // Only check attack/defend if they are the attacker/defender referenced by the action
    if(DoesHaveItemEquippedRequirements())
    {
        return DoesMeetItemEquippedRequirements(sCharacterID, sWeaponSet);
    }
    else if(DoesHaveItemUsedRequirements())
    {
        return DoesMeetItemUsedRequirements(ItemTree::GetActionTypes(GetItemTreeIndex()));
    }
    else if(DoesHaveAttackRequirements() && bSelfIsActionSender)
    {
        return DoesMeetAttackRequirements(action.GetAllActionTypes(), action.GetPreviousActionTypes());
    }
    else if(DoesHaveDefendRequirements() && bSelfIsActionRecipient)
    {
        return DoesMeetDefendRequirements(action.GetAllActionTypes(), action.GetPreviousActionTypes());
    }
    return false;
}

StringArray StatChange::GetIntersectingAttackRequirements(const StringArray& vActionTypes) const
{
    // Get some info regarding this change
    const StringArray vChangeRequiredAttackTypesOR = GetRequiredAttackTypesOR();
    const StringArray vChangeRequiredAttackTypesAND = GetRequiredAttackTypesAND();

    // Get the intersection of attack types
    if(!vActionTypes.empty() && !vChangeRequiredAttackTypesOR.empty())
    {
        return FindVectorIntersection<String>(vActionTypes, vChangeRequiredAttackTypesOR);
    }
    else if(!vActionTypes.empty() && !vChangeRequiredAttackTypesAND.empty())
    {
        return FindVectorIntersection<String>(vActionTypes, vChangeRequiredAttackTypesAND);
    }
    return StringArray();
}

StringArray StatChange::GetIntersectingDefendRequirements(const StringArray& vActionTypes) const
{
    // Get some info regarding this change
    const StringArray vChangeRequiredDefendTypesOR = GetRequiredDefendTypesOR();
    const StringArray vChangeRequiredDefendTypesAND = GetRequiredDefendTypesAND();

    // Get the intersection of defend types
    if(!vActionTypes.empty() && !vChangeRequiredDefendTypesOR.empty())
    {
        return FindVectorIntersection<String>(vActionTypes, vChangeRequiredDefendTypesOR);
    }
    else if(!vActionTypes.empty() && !vChangeRequiredDefendTypesAND.empty())
    {
        return FindVectorIntersection<String>(vActionTypes, vChangeRequiredDefendTypesAND);
    }
    return StringArray();
}

Bool StatChange::GetResolvedCharacterArrays(StringArray& vSourceCharIDs, StringArray& vDestCharIDs) const
{
    String sSourceTargetType = GetSourceTargetType();
    String sDestTargetType = GetDestinationTargetType();
    String sSourcePartyType = ConvertCharacterTargetTypeToCharacterPartyType(sSourceTargetType);
    String sDestPartyType = ConvertCharacterTargetTypeToCharacterPartyType(sDestTargetType);
    if(CharacterPartyManager::GetInstance()->DoesPartyExistByType(sSourcePartyType))
    {
        CharacterPartyManager::GetInstance()->GetPartyByType(sSourcePartyType).GetCharacterIDsFromTargetType(sSourceTargetType, vSourceCharIDs);
    }
    if(CharacterPartyManager::GetInstance()->DoesPartyExistByType(sDestPartyType))
    {
        CharacterPartyManager::GetInstance()->GetPartyByType(sDestPartyType).GetCharacterIDsFromTargetType(sDestTargetType, vDestCharIDs);
    }
    return (!vSourceCharIDs.empty() || !vDestCharIDs.empty());
}

void StatChange::ResolveTargetPlaceholders(const String& sCharacterID, const String& sSegment)
{
    // Check character first
    if(!CharacterManager::GetInstance()->DoesCharacterExist(sCharacterID))
    {
        return;
    }

    // Get battle data
    const Character& character = CharacterManager::GetInstance()->GetCharacter(sCharacterID);
    const CharacterBattleData& battleData = character.GetBattleDataSegment(sSegment);

    // Get resolved target types
    String sSelfTargetType = character.GetCharacterTargetType();
    StringArray vSourceTargetTypes = battleData.ResolveTargetPlaceholder(sSelfTargetType, GetSourceTargetType());
    StringArray vDestTargetTypes = battleData.ResolveTargetPlaceholder(sSelfTargetType, GetDestinationTargetType());

    // Save resolved target types
    if(!vSourceTargetTypes.empty())
    {
        SetSourceTargetType(vSourceTargetTypes.front());
    }
    if(!vDestTargetTypes.empty())
    {
        SetDestinationTargetType(vDestTargetTypes.front());
    }
}

Bool StatChange::operator==(const StatChange& other) const
{
    return (GetID() == other.GetID());
}

Bool StatChange::operator<(const StatChange& other) const
{
    return (GetID() < other.GetID());
}

void to_json(Json& jsonData, const StatChange& obj)
{
    // ID
    SET_JSON_DATA(ID);

    // Relevant skill data
    SET_JSON_DATA(SkillTreeIndex);

    // Relevant item data
    SET_JSON_DATA(ItemTreeIndex);

    // Percent chance to apply this change
    SET_JSON_DATA(ChanceToApply);

    // Amount of rounds to apply this change (0 is indefinite)
    SET_JSON_DATA(RoundAmount);

    // Amount of attacks to apply this change (0 is indefinite)
    SET_JSON_DATA(AttackAmount);

    // Amount of defends to apply this change (0 is indefinite)
    SET_JSON_DATA(DefendAmount);

    // Required items or attack types
    SET_JSON_DATA(RequiredItemEquippedTypesOR);
    SET_JSON_DATA(RequiredItemEquippedTypesAND);
    SET_JSON_DATA(RequiredItemUsedTypesOR);
    SET_JSON_DATA(RequiredItemUsedTypesAND);
    SET_JSON_DATA(RequiredAttackTypesOR);
    SET_JSON_DATA(RequiredAttackTypesAND);
    SET_JSON_DATA(RequiredDefendTypesOR);
    SET_JSON_DATA(RequiredDefendTypesAND);
    SET_JSON_DATA(RequiredPreviousAttackTypesOR);
    SET_JSON_DATA(RequiredPreviousAttackTypesAND);
    SET_JSON_DATA(RequiredPreviousDefendTypesOR);
    SET_JSON_DATA(RequiredPreviousDefendTypesAND);
    SET_JSON_DATA(RequiredEquippedWeaponCount);
    SET_JSON_DATA(RequiredEquippedShieldCount);

    // Whether destination target is the same as the source target
    SET_JSON_DATA(DestinationIsSource);

    // Source and destination targets
    SET_JSON_DATA(SourceTargetType);
    SET_JSON_DATA(DestinationTargetType);

    // Stat change list
    SET_JSON_DATA(StatChangeEntries);
}

void from_json(const Json& jsonData, StatChange& obj)
{
    // ID
    SET_OBJ_DATA(ID, ULongLong);

    // Relevant skill data
    SET_OBJ_DATA(SkillTreeIndex, TreeIndex);

    // Relevant item data
    SET_OBJ_DATA(ItemTreeIndex, TreeIndex);

    // Percent chance to apply this change
    SET_OBJ_DATA(ChanceToApply, Float);

    // Amount of rounds to apply this change (0 is indefinite)
    SET_OBJ_DATA(RoundAmount, Int);

    // Amount of attacks to apply this change (0 is indefinite)
    SET_OBJ_DATA(AttackAmount, Int);

    // Amount of defends to apply this change (0 is indefinite)
    SET_OBJ_DATA(DefendAmount, Int);

    // Required items or attack types
    SET_OBJ_DATA(RequiredItemEquippedTypesOR, StringArray);
    SET_OBJ_DATA(RequiredItemEquippedTypesAND, StringArray);
    SET_OBJ_DATA(RequiredItemUsedTypesOR, StringArray);
    SET_OBJ_DATA(RequiredItemUsedTypesAND, StringArray);
    SET_OBJ_DATA(RequiredAttackTypesOR, StringArray);
    SET_OBJ_DATA(RequiredAttackTypesAND, StringArray);
    SET_OBJ_DATA(RequiredDefendTypesOR, StringArray);
    SET_OBJ_DATA(RequiredDefendTypesAND, StringArray);
    SET_OBJ_DATA(RequiredPreviousAttackTypesOR, StringArray);
    SET_OBJ_DATA(RequiredPreviousAttackTypesAND, StringArray);
    SET_OBJ_DATA(RequiredPreviousDefendTypesOR, StringArray);
    SET_OBJ_DATA(RequiredPreviousDefendTypesAND, StringArray);
    SET_OBJ_DATA(RequiredEquippedWeaponCount, Int);
    SET_OBJ_DATA(RequiredEquippedShieldCount, Int);

    // Whether destination target is the same as the source target
    SET_OBJ_DATA(DestinationIsSource, Bool);

    // Source and destination targets
    SET_OBJ_DATA(SourceTargetType, String);
    SET_OBJ_DATA(DestinationTargetType, String);

    // Stat change entry list
    SET_OBJ_DATA(StatChangeEntries, StatChangeEntryArray);
}

const StatChangeArray& GetStatChangesFromTreeIndex(const String& sTreeIndexType, const TreeIndex& treeIndex)
{
    const CharacterTreeIndexType eTreeIndexType = GetEnumFromString<CharacterTreeIndexType>(sTreeIndexType);
    switch(eTreeIndexType)
    {
        case CharacterTreeIndexType::Skill:
            return GetStatChangesFromSkillTreeIndex(treeIndex);
        case CharacterTreeIndexType::Item:
            return GetStatChangesFromItemTreeIndex(treeIndex);
        default:
            break;
    }
    THROW_RUNTIME_ERROR("Invalid or unknown tree index type requested: " + sTreeIndexType);
}

const StatChangeArray& GetStatChangesFromSkillTreeIndex(const TreeIndex& treeIndex)
{
    const SkillTreeType eSkillTreeType = GetEnumFromStringOrNone<SkillTreeType>(treeIndex.GetTree());
    switch(eSkillTreeType)
    {
        case SkillTreeType::Affinity:
            return SkillTree::RetrieveSkillDataAffinity(treeIndex).GetStatChanges();
        case SkillTreeType::Alchemy:
            return SkillTree::RetrieveSkillDataAlchemy(treeIndex).GetStatChanges();
        case SkillTreeType::Crafting:
            return SkillTree::RetrieveSkillDataCrafting(treeIndex).GetStatChanges();
        case SkillTreeType::Breakdown:
            return SkillTree::RetrieveSkillDataBreakdown(treeIndex).GetStatChanges();
        case SkillTreeType::Combat:
            return SkillTree::RetrieveSkillDataCombat(treeIndex).GetStatChanges();
        case SkillTreeType::Weapon:
            return SkillTree::RetrieveSkillDataWeapon(treeIndex).GetStatChanges();
        default:
            break;
    }
    THROW_RUNTIME_ERROR("Invalid or unknown tree index requested: " + treeIndex.GetTreeBranchLeafType());
}

const StatChangeArray& GetStatChangesFromItemTreeIndex(const TreeIndex& treeIndex)
{
    const ItemTreeType eItemTreeType = GetEnumFromStringOrNone<ItemTreeType>(treeIndex.GetTree());
    switch(eItemTreeType)
    {
        case ItemTreeType::Armor:
            return ItemTree::RetrieveItemDataArmor(treeIndex).GetStatChanges();
        case ItemTreeType::Ingredient:
            return ItemTree::RetrieveItemDataIngredient(treeIndex).GetStatChanges();
        case ItemTreeType::Potion:
            return ItemTree::RetrieveItemDataPotion(treeIndex).GetStatChanges();
        case ItemTreeType::Weapon:
            return ItemTree::RetrieveItemDataWeapon(treeIndex).GetStatChanges();
        default:
            break;
    }
    THROW_RUNTIME_ERROR("Invalid or unknown tree index requested: " + treeIndex.GetTreeBranchLeafType());
}

};
