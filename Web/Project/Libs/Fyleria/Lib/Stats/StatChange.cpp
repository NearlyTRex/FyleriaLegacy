// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#include "Stats/StatChange.h"
#include "Character/CharacterManager.h"
#include "Character/CharacterPartyManager.h"
#include "Items/ItemTree.h"
#include "Items/ItemTypes.h"
#include "Skills/SkillTypes.h"
#include "Skills/SkillTree.h"

namespace Gecko
{

StatChange::StatChange()
    : m_uID(GenerateNewID())
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
    SetSourceTargetType(IndexedString("None"));
    SetDestinationTargetType(IndexedString("None"));

    // Stat change entry list
    SetStatChangeEntries({});
}

StatChange::StatChange(const Json& jsonData)
    : m_uID(GenerateNewID())
{
    from_json(jsonData, *this);
}

UInt StatChange::GenerateNewID()
{
    static UInt s_uCurrentCount = 0;
    s_uCurrentCount++;
    return s_uCurrentCount;
}

UInt StatChange::GetID() const
{
    return m_uID;
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

Bool StatChange::DoesMeetItemEquippedRequirements(const IndexedString& sCharacterID, const IndexedString& sWeaponSet) const
{
    // Check character first
    if(!CharacterManager::GetInstance()->DoesCharacterExist(sCharacterID))
    {
        return false;
    }

    // Get equipped item types
    IndexedStringList vEquippedItemTypes;
    const Character& character = CharacterManager::GetInstance()->GetCharacter(sCharacterID);
    for(auto&& progressItem : character.GetEquippedItems())
    {
        vEquippedItemTypes.push_back(RetrieveItemType(progressItem.GetTreeIndex()));
    }

    // Get equipped item counts
    const UInt uActualWeaponCount = character.GetEquippedWeaponCount(sWeaponSet);
    const UInt uActualShieldCount = character.GetEquippedShieldCount(sWeaponSet);

    // Get some info regarding this change
    const UInt uChangeRequiredWeaponCount = GetRequiredEquippedWeaponCount();
    const UInt uChangeRequiredShieldCount = GetRequiredEquippedShieldCount();
    const IndexedStringList vChangeRequiredItemEquippedTypesOR = GetRequiredItemEquippedTypesOR();
    const IndexedStringList vChangeRequiredItemEquippedTypesAND = GetRequiredItemEquippedTypesAND();

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
        return STDVectorDoesIntersectOR<IndexedString>(vEquippedItemTypes, vChangeRequiredItemEquippedTypesOR);
    }
    else if(!vChangeRequiredItemEquippedTypesAND.empty())
    {
        return STDVectorDoesIntersectAND<IndexedString>(vEquippedItemTypes, vChangeRequiredItemEquippedTypesAND);
    }
    return false;
}

Bool StatChange::DoesMeetItemUsedRequirements(const IndexedStringList& vActionItemTypes) const
{
    // Check action item types
    if(vActionItemTypes.empty())
    {
        return false;
    }

    // Get some info regarding this change
    const IndexedStringList vChangeRequiredItemsUsedOR = GetRequiredItemUsedTypesOR();
    const IndexedStringList vChangeRequiredItemsUsedAND = GetRequiredItemUsedTypesAND();

    // The item type being used by the action matches the change requirement
    if(!vChangeRequiredItemsUsedOR.empty() && !vActionItemTypes.front().empty())
    {
        return STDVectorDoesIntersectOR<IndexedString>(vActionItemTypes, vChangeRequiredItemsUsedOR);
    }
    else if(!vChangeRequiredItemsUsedAND.empty() && !vActionItemTypes.front().empty())
    {
        return STDVectorDoesIntersectAND<IndexedString>(vActionItemTypes, vChangeRequiredItemsUsedAND);
    }
    return false;
}

Bool StatChange::DoesMeetAttackRequirements(const IndexedStringList& vActionTypes) const
{
    // Get some info regarding this change
    const IndexedStringList vChangeRequiredAttackTypesOR = GetRequiredAttackTypesOR();
    const IndexedStringList vChangeRequiredAttackTypesAND = GetRequiredAttackTypesAND();

    // Our character is sending action, and the action's types match the required attack types
    if(!vActionTypes.empty() && !vChangeRequiredAttackTypesOR.empty())
    {
        return STDVectorDoesIntersectOR<IndexedString>(vActionTypes, vChangeRequiredAttackTypesOR);
    }
    else if(!vActionTypes.empty() && !vChangeRequiredAttackTypesAND.empty())
    {
        return STDVectorDoesIntersectAND<IndexedString>(vActionTypes, vChangeRequiredAttackTypesAND);
    }
    return false;
}

Bool StatChange::DoesMeetAttackRequirements(const IndexedStringList& vActionTypes, const IndexedStringList& vPreviousActionTypes) const
{
    // Check non-previous action types
    if(!DoesMeetAttackRequirements(vActionTypes))
    {
        return false;
    }

    // Get some info regarding this change
    const IndexedStringList vChangeRequiredPreviousAttackTypesOR = GetRequiredPreviousAttackTypesOR();
    const IndexedStringList vChangeRequiredPreviousAttackTypesAND = GetRequiredPreviousAttackTypesAND();

    // Our character is sending action, and the action's previous types match the required previous attack types
    if(!vPreviousActionTypes.empty() && !vChangeRequiredPreviousAttackTypesOR.empty())
    {
        return STDVectorDoesIntersectOR<IndexedString>(vPreviousActionTypes, vChangeRequiredPreviousAttackTypesOR);
    }
    else if(!vPreviousActionTypes.empty() && !vChangeRequiredPreviousAttackTypesAND.empty())
    {
        return STDVectorDoesIntersectAND<IndexedString>(vPreviousActionTypes, vChangeRequiredPreviousAttackTypesAND);
    }
    return false;
}

Bool StatChange::DoesMeetDefendRequirements(const IndexedStringList& vActionTypes) const
{
    // Get some info regarding this change
    const IndexedStringList vChangeRequiredDefendTypesOR = GetRequiredDefendTypesOR();
    const IndexedStringList vChangeRequiredDefendTypesAND = GetRequiredDefendTypesAND();

    // Our character is receiving action, and the action's types match the required defend types
    if(!vActionTypes.empty() && !vChangeRequiredDefendTypesOR.empty())
    {
        return STDVectorDoesIntersectOR<IndexedString>(vActionTypes, vChangeRequiredDefendTypesOR);
    }
    else if(!vActionTypes.empty() && !vChangeRequiredDefendTypesAND.empty())
    {
        return STDVectorDoesIntersectAND<IndexedString>(vActionTypes, vChangeRequiredDefendTypesAND);
    }
    return false;
}

Bool StatChange::DoesMeetDefendRequirements(const IndexedStringList& vActionTypes, const IndexedStringList& vPreviousActionTypes) const
{
    // Check non-previous action types
    if(!DoesMeetDefendRequirements(vActionTypes))
    {
        return false;
    }

    // Get some info regarding this change
    const IndexedStringList vChangeRequiredPreviousDefendTypesOR = GetRequiredPreviousDefendTypesOR();
    const IndexedStringList vChangeRequiredPreviousDefendTypesAND = GetRequiredPreviousDefendTypesAND();

    // Our character is receiving action, and the action's previous types match the required previous defend types
    if(!vPreviousActionTypes.empty() && !vChangeRequiredPreviousDefendTypesOR.empty())
    {
        return STDVectorDoesIntersectOR<IndexedString>(vPreviousActionTypes, vChangeRequiredPreviousDefendTypesOR);
    }
    else if(!vPreviousActionTypes.empty() && !vChangeRequiredPreviousDefendTypesAND.empty())
    {
        return STDVectorDoesIntersectAND<IndexedString>(vPreviousActionTypes, vChangeRequiredPreviousDefendTypesAND);
    }
    return false;
}

IndexedStringList StatChange::GetIntersectingAttackRequirements(const IndexedStringList& vActionTypes) const
{
    // Get some info regarding this change
    const IndexedStringList vChangeRequiredAttackTypesOR = GetRequiredAttackTypesOR();
    const IndexedStringList vChangeRequiredAttackTypesAND = GetRequiredAttackTypesAND();

    // Get the intersection of attack types
    if(!vActionTypes.empty() && !vChangeRequiredAttackTypesOR.empty())
    {
        return STDVectorFindIntersect<IndexedString>(vActionTypes, vChangeRequiredAttackTypesOR);
    }
    else if(!vActionTypes.empty() && !vChangeRequiredAttackTypesAND.empty())
    {
        return STDVectorFindIntersect<IndexedString>(vActionTypes, vChangeRequiredAttackTypesAND);
    }
    return IndexedStringList();
}

IndexedStringList StatChange::GetIntersectingDefendRequirements(const IndexedStringList& vActionTypes) const
{
    // Get some info regarding this change
    const IndexedStringList vChangeRequiredDefendTypesOR = GetRequiredDefendTypesOR();
    const IndexedStringList vChangeRequiredDefendTypesAND = GetRequiredDefendTypesAND();

    // Get the intersection of defend types
    if(!vActionTypes.empty() && !vChangeRequiredDefendTypesOR.empty())
    {
        return STDVectorFindIntersect<IndexedString>(vActionTypes, vChangeRequiredDefendTypesOR);
    }
    else if(!vActionTypes.empty() && !vChangeRequiredDefendTypesAND.empty())
    {
        return STDVectorFindIntersect<IndexedString>(vActionTypes, vChangeRequiredDefendTypesAND);
    }
    return IndexedStringList();
}

Bool StatChange::GetResolvedCharacterLists(IndexedStringList& vSourceCharIDs, IndexedStringList& vDestCharIDs) const
{
    IndexedString sSourceTargetType = GetSourceTargetType();
    IndexedString sDestTargetType = GetDestinationTargetType();
    IndexedString sSourcePartyType = ConvertCharacterTargetTypeToCharacterPartyType(sSourceTargetType);
    IndexedString sDestPartyType = ConvertCharacterTargetTypeToCharacterPartyType(sDestTargetType);
    CharacterPartyManager::GetInstance()->GetPartyByType(sSourcePartyType).GetCharacterIDsFromTargetType(sSourceTargetType, vSourceCharIDs);
    CharacterPartyManager::GetInstance()->GetPartyByType(sDestPartyType).GetCharacterIDsFromTargetType(sDestTargetType, vDestCharIDs);
    return (!vSourceCharIDs.empty() || !vDestCharIDs.empty());
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
    // Relevant skill data
    SET_JSON_DATA_IF_NOT_DEFAULT(SkillTreeIndex, TreeIndex());

    // Relevant item data
    SET_JSON_DATA_IF_NOT_DEFAULT(ItemTreeIndex, TreeIndex());

    // Percent chance to apply this change
    SET_JSON_DATA_IF_NOT_DEFAULT(ChanceToApply, 0);

    // Amount of rounds to apply this change (0 is indefinite)
    SET_JSON_DATA_IF_NOT_DEFAULT(RoundAmount, 0);

    // Amount of attacks to apply this change (0 is indefinite)
    SET_JSON_DATA_IF_NOT_DEFAULT(AttackAmount, 0);

    // Amount of defends to apply this change (0 is indefinite)
    SET_JSON_DATA_IF_NOT_DEFAULT(DefendAmount, 0);

    // Required items or attack types
    SET_JSON_DATA_IF_NOT_EMPTY(RequiredItemEquippedTypesOR);
    SET_JSON_DATA_IF_NOT_EMPTY(RequiredItemEquippedTypesAND);
    SET_JSON_DATA_IF_NOT_EMPTY(RequiredItemUsedTypesOR);
    SET_JSON_DATA_IF_NOT_EMPTY(RequiredItemUsedTypesAND);
    SET_JSON_DATA_IF_NOT_EMPTY(RequiredAttackTypesOR);
    SET_JSON_DATA_IF_NOT_EMPTY(RequiredAttackTypesAND);
    SET_JSON_DATA_IF_NOT_EMPTY(RequiredDefendTypesOR);
    SET_JSON_DATA_IF_NOT_EMPTY(RequiredDefendTypesAND);
    SET_JSON_DATA_IF_NOT_EMPTY(RequiredPreviousAttackTypesOR);
    SET_JSON_DATA_IF_NOT_EMPTY(RequiredPreviousAttackTypesAND);
    SET_JSON_DATA_IF_NOT_EMPTY(RequiredPreviousDefendTypesOR);
    SET_JSON_DATA_IF_NOT_EMPTY(RequiredPreviousDefendTypesAND);
    SET_JSON_DATA_IF_NOT_DEFAULT(RequiredEquippedWeaponCount, 0);
    SET_JSON_DATA_IF_NOT_DEFAULT(RequiredEquippedShieldCount, 0);

    // Whether destination target is the same as the source target
    SET_JSON_DATA_IF_NOT_DEFAULT(DestinationIsSource, false);

    // Source and destination targets
    SET_JSON_DATA_IF_NOT_DEFAULT(SourceTargetType, IndexedString("None"));
    SET_JSON_DATA_IF_NOT_DEFAULT(DestinationTargetType, IndexedString("None"));

    // Stat change list
    SET_JSON_DATA_IF_NOT_EMPTY(StatChangeEntries);
}

void from_json(const Json& jsonData, StatChange& obj)
{
    // Relevant skill data
    obj.SetSkillTreeIndex(GET_JSON_DATA_OR_DEFAULT(SkillTreeIndex, TreeIndex, TreeIndex()));

    // Relevant item data
    obj.SetItemTreeIndex(GET_JSON_DATA_OR_DEFAULT(ItemTreeIndex, TreeIndex, TreeIndex()));

    // Percent chance to apply this change
    obj.SetChanceToApply(GET_JSON_DATA_OR_DEFAULT(ChanceToApply, Int, 0));

    // Amount of rounds to apply this change (0 is indefinite)
    obj.SetRoundAmount(GET_JSON_DATA_OR_DEFAULT(RoundAmount, Int, 0));

    // Amount of attacks to apply this change (0 is indefinite)
    obj.SetAttackAmount(GET_JSON_DATA_OR_DEFAULT(AttackAmount, Int, 0));

    // Amount of defends to apply this change (0 is indefinite)
    obj.SetDefendAmount(GET_JSON_DATA_OR_DEFAULT(DefendAmount, Int, 0));

    // Required items or attack types
    obj.SetRequiredItemEquippedTypesOR(GET_JSON_DATA_OR_DEFAULT(RequiredItemEquippedTypesOR, IndexedStringList, IndexedStringList()));
    obj.SetRequiredItemEquippedTypesAND(GET_JSON_DATA_OR_DEFAULT(RequiredItemEquippedTypesAND, IndexedStringList, IndexedStringList()));
    obj.SetRequiredItemUsedTypesOR(GET_JSON_DATA_OR_DEFAULT(RequiredItemUsedTypesOR, IndexedStringList, IndexedStringList()));
    obj.SetRequiredItemUsedTypesAND(GET_JSON_DATA_OR_DEFAULT(RequiredItemUsedTypesAND, IndexedStringList, IndexedStringList()));
    obj.SetRequiredAttackTypesOR(GET_JSON_DATA_OR_DEFAULT(RequiredAttackTypesOR, IndexedStringList, IndexedStringList()));
    obj.SetRequiredAttackTypesAND(GET_JSON_DATA_OR_DEFAULT(RequiredAttackTypesAND, IndexedStringList, IndexedStringList()));
    obj.SetRequiredDefendTypesOR(GET_JSON_DATA_OR_DEFAULT(RequiredDefendTypesOR, IndexedStringList, IndexedStringList()));
    obj.SetRequiredDefendTypesAND(GET_JSON_DATA_OR_DEFAULT(RequiredDefendTypesAND, IndexedStringList, IndexedStringList()));
    obj.SetRequiredPreviousAttackTypesOR(GET_JSON_DATA_OR_DEFAULT(RequiredPreviousAttackTypesOR, IndexedStringList, IndexedStringList()));
    obj.SetRequiredPreviousAttackTypesAND(GET_JSON_DATA_OR_DEFAULT(RequiredPreviousAttackTypesAND, IndexedStringList, IndexedStringList()));
    obj.SetRequiredPreviousDefendTypesOR(GET_JSON_DATA_OR_DEFAULT(RequiredPreviousDefendTypesOR, IndexedStringList, IndexedStringList()));
    obj.SetRequiredPreviousDefendTypesAND(GET_JSON_DATA_OR_DEFAULT(RequiredPreviousDefendTypesAND, IndexedStringList, IndexedStringList()));
    obj.SetRequiredEquippedWeaponCount(GET_JSON_DATA_OR_DEFAULT(RequiredEquippedWeaponCount, Int, 0));
    obj.SetRequiredEquippedShieldCount(GET_JSON_DATA_OR_DEFAULT(RequiredEquippedShieldCount, Int, 0));

    // Whether destination target is the same as the source target
    obj.SetDestinationIsSource(GET_JSON_DATA_OR_DEFAULT(DestinationIsSource, Bool, false));

    // Source and destination targets
    obj.SetSourceTargetType(GET_JSON_DATA_OR_DEFAULT(SourceTargetType, IndexedString, IndexedString("None")));
    obj.SetDestinationTargetType(GET_JSON_DATA_OR_DEFAULT(DestinationTargetType, IndexedString, IndexedString("None")));

    // Stat change entry list
    obj.SetStatChangeEntries(GET_JSON_DATA_OR_DEFAULT(StatChangeEntries, StatChangeEntryList, StatChangeEntryList()));
}

MAKE_JSON_GENERIC_TYPE_CONVERTERS_IMPL(StatChange, StatChange);

ProlongedStatChange::ProlongedStatChange()
    : SerializableToJson()
{
}

ProlongedStatChange::ProlongedStatChange(const Json& jsonData)
    : SerializableToJson(jsonData)
{
}

MAKE_JSON_BASIC_TYPE_CONVERTERS_IMPL(ProlongedStatChange);
MAKE_JSON_GENERIC_TYPE_CONVERTERS_IMPL(ProlongedStatChange, ProlongedStatChange);

static const StatChangeList s_vEmptyChanges;
const StatChangeList& GetStatChangesFromTreeIndex(const IndexedString& sTreeIndexType, const TreeIndex& index)
{
    const CharacterTreeIndexType eTreeIndexType = StringToCharacterTreeIndexType(sTreeIndexType);
    switch(eTreeIndexType)
    {
        case CharacterTreeIndexType::Skill:
            return GetStatChangesFromSkillTreeIndex(index);
        case CharacterTreeIndexType::Item:
            return GetStatChangesFromItemTreeIndex(index);
        default:
            break;
    }
    return s_vEmptyChanges;
}

const StatChangeList& GetStatChangesFromSkillTreeIndex(const TreeIndex& index)
{
    const SkillTreeType eSkillTreeType = (IsValidSkillTreeType(index.GetTree())) ? StringToSkillTreeType(index.GetTree()) : +SkillTreeType::None;
    switch(eSkillTreeType)
    {
        case SkillTreeType::Affinity:
            return RetrieveSkillDataAffinity(index).GetStatChanges();
        case SkillTreeType::Alchemy:
            return RetrieveSkillDataAlchemy(index).GetStatChanges();
        case SkillTreeType::Crafting:
            return RetrieveSkillDataCrafting(index).GetStatChanges();
        case SkillTreeType::Breakdown:
            return RetrieveSkillDataBreakdown(index).GetStatChanges();
        case SkillTreeType::Combat:
            return RetrieveSkillDataCombat(index).GetStatChanges();
        case SkillTreeType::Weapon:
            return RetrieveSkillDataWeapon(index).GetStatChanges();
        default:
            break;
    }
    return s_vEmptyChanges;
}

const StatChangeList& GetStatChangesFromItemTreeIndex(const TreeIndex& index)
{
    const ItemTreeType eItemTreeType = (IsValidItemTreeType(index.GetTree())) ? StringToItemTreeType(index.GetTree()) : +ItemTreeType::None;
    switch(eItemTreeType)
    {
        case ItemTreeType::Armor:
            return RetrieveItemDataArmor(index).GetStatChanges();
        case ItemTreeType::Ingredient:
            return RetrieveItemDataIngredient(index).GetStatChanges();
        case ItemTreeType::Potion:
            return RetrieveItemDataPotion(index).GetStatChanges();
        case ItemTreeType::Weapon:
            return RetrieveItemDataWeapon(index).GetStatChanges();
        default:
            break;
    }
    return s_vEmptyChanges;
}

};
