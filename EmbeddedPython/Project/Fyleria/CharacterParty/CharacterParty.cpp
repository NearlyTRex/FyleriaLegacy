// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

// Internal includes
#include "CharacterParty/CharacterParty.h"
#include "CharacterData/CharacterProgressData.h"
#include "Character/CharacterManager.h"
#include "Character/CharacterTypes.h"
#include "Utility/Errors.h"
#include "Utility/Converters.h"
#include "Utility/Templates.h"

namespace Gecko
{

CharacterParty::CharacterParty()
{
}

CharacterParty::CharacterParty(const Json& jsonData)
{
    from_json(jsonData, *this);
}

CharacterParty::CharacterParty(const String& jsonString)
{
    from_json(JsonParse(jsonString), *this);
}

void CharacterParty::RegenerateCharacterData(
    Bool bUpdateEquipmentRatings /*= true*/,
    Bool bUpdateAvailableChanges /*= true*/,
    Bool bUpdateAvailableActions /*= true*/,
    Bool bUpdateAvailableAP /*= true*/
)
{
    for(auto& member : GetMembers())
    {
        CharacterManager::GetInstance()->GetCharacter(member.first).RegenerateCharacterData(
            bUpdateEquipmentRatings,
            bUpdateAvailableChanges,
            bUpdateAvailableActions,
            bUpdateAvailableAP
        );
    }
}

Bool CharacterParty::IsPartyAbleToFight() const
{
    UInt uMemberCount = GetMemberCount();
    if(uMemberCount == 0)
    {
        return false;
    }

    UInt uDeadMemberCount = GetStatusMemberCount((+CharacterStatusType::Dead)._to_string());
    if(uMemberCount == uDeadMemberCount)
    {
        return false;
    }
    return true;
}

Bool CharacterParty::IsPartyFull() const
{
    String sNoneType = GetNoneTypeForEnum<CharacterResolvedTargetType>();
    return (GetNextAvailableTargetType() == sNoneType);
}

Bool CharacterParty::IsMemberPresent(const String& sCharacterID) const
{
    for(auto& member : GetMembers())
    {
        if (member.first == sCharacterID)
        {
            return true;
        }
    }
    return false;
}

Bool CharacterParty::IsTargetTypeAvailable(const String& sCharacterTargetType) const
{
    const StringArray& vTargetTypes = GetAvailableTargetTypes();
    auto iLocation = STDFindData(vTargetTypes.begin(), vTargetTypes.end(), sCharacterTargetType);
    return (iLocation != vTargetTypes.end());
}

Bool CharacterParty::IsTargetTypeTaken(const String& sCharacterTargetType) const
{
    const StringArray& vTargetTypes = GetTakenTargetTypes();
    auto iLocation = STDFindData(vTargetTypes.begin(), vTargetTypes.end(), sCharacterTargetType);
    return (iLocation != vTargetTypes.end());
}

Bool CharacterParty::AddMember(const String& sCharacterID)
{
    // Check if party is full
    if(IsPartyFull())
    {
        ERROR_FORMAT_STATEMENT("Party at ID '{}' is full\n", GetPartyID().c_str());
        return false;
    }

    // Check if member does not exist first
    if(IsMemberPresent(sCharacterID))
    {
        ERROR_FORMAT_STATEMENT("Character at ID '{}' was already present in party\n", sCharacterID.c_str());
        return false;
    }

    // Add member
    CharacterPartyMember newMember;
    newMember.SetCharacterID(sCharacterID);
    newMember.SetCharacterTargetType(GetNextAvailableTargetType());
    GetMembers().insert({sCharacterID, newMember});
    UseTargetType(newMember.GetCharacterTargetType());
    Character& character = CharacterManager::GetInstance()->GetCharacter(sCharacterID);
    character.GetBasicData().SetPartyID(GetPartyID());
    character.RegenerateCharacterData();
    return true;
}

Bool CharacterParty::RemoveMember(const String& sCharacterID)
{
    // Check if member exists first
    if(!IsMemberPresent(sCharacterID))
    {
        ERROR_FORMAT_STATEMENT("Character at ID '{}' was not present in party\n", sCharacterID.c_str());
        return false;
    }

    // Remove member
    UnequipAllItems(sCharacterID);
    FreeTargetType(GetMemberByID(sCharacterID).GetCharacterTargetType());
    Character& character = CharacterManager::GetInstance()->GetCharacter(sCharacterID);
    character.GetBasicData().SetPartyID({});
    character.RegenerateCharacterData();
    GetMembers().erase(sCharacterID);
    return true;
}

Bool CharacterParty::MoveMember(const String& sCharacterID, const String& sCharacterTargetType)
{
    // Check if member exists first
    if(!IsMemberPresent(sCharacterID))
    {
        ERROR_FORMAT_STATEMENT("Character at ID '{}' was not present in party\n", sCharacterID.c_str());
        return false;
    }

    // Check if new target type is available
    if(!IsTargetTypeAvailable(sCharacterTargetType))
    {
        ERROR_FORMAT_STATEMENT("Target type '{}' is not available\n", sCharacterTargetType.c_str());
        return false;
    }

    // Set new target type
    CharacterPartyMember& member = GetMemberByID(sCharacterID);
    FreeTargetType(member.GetCharacterTargetType());
    UseTargetType(sCharacterTargetType);
    member.SetCharacterTargetType(sCharacterTargetType);
    return true;
}

Bool CharacterParty::SwapMembers(const String& sFirstCharacterID, const String& sSecondCharacterID)
{
    // Check if members exists first
    if(!IsMemberPresent(sFirstCharacterID) || !IsMemberPresent(sSecondCharacterID))
    {
        ERROR_FORMAT_STATEMENT("Character at ID '{}' or ID '{}' was not present in party\n",
            sFirstCharacterID.c_str(),
            sSecondCharacterID.c_str());
        return false;
    }

    // Swap target types
    CharacterPartyMember& firstMember = GetMemberByID(sFirstCharacterID);
    CharacterPartyMember& secondMember = GetMemberByID(sSecondCharacterID);
    String sFirstTargetType = firstMember.GetCharacterTargetType();
    String sSecondTargetType = secondMember.GetCharacterTargetType();
    firstMember.SetCharacterTargetType(sSecondTargetType);
    secondMember.SetCharacterTargetType(sFirstTargetType);
    return true;
}

String CharacterParty::GetNextAvailableTargetType() const
{
    for(const String& sTarget : GetAvailableTargetTypes())
    {
        return sTarget;
    }
    return GetNoneTypeForEnum<CharacterResolvedTargetType>();
}

Bool CharacterParty::UseTargetType(const String& sCharacterTargetType)
{
    if(!IsTargetTypeAvailable(sCharacterTargetType))
    {
        return false;
    }

    RemoveVectorElement<String>(GetAvailableTargetTypes(), sCharacterTargetType);
    GetTakenTargetTypes().push_back(sCharacterTargetType);
    return true;
}

Bool CharacterParty::FreeTargetType(const String& sCharacterTargetType)
{
    if(!IsTargetTypeTaken(sCharacterTargetType))
    {
        return false;
    }

    GetAvailableTargetTypes().push_back(sCharacterTargetType);
    RemoveVectorElement<String>(GetTakenTargetTypes(), sCharacterTargetType);
    return true;
}

const CharacterPartyMember& CharacterParty::GetMemberByID(const String& sCharacterID) const
{
    return GetMembers().at(sCharacterID);
}

const CharacterPartyMember& CharacterParty::GetMemberByTargetType(const String& sCharacterTargetType) const
{
    for (auto& member : GetMembers())
    {
        if (member.second.GetCharacterTargetType() == sCharacterTargetType)
        {
            return member.second;
        }
    }
    THROW_RUNTIME_ERROR("No character matching character target type '" + sCharacterTargetType + "' was found");
}

CharacterPartyMember& CharacterParty::GetMemberByID(const String& sCharacterID)
{
    return const_cast<CharacterPartyMember&>(static_cast<const CharacterParty&>(*this).GetMemberByID(sCharacterID));
}

CharacterPartyMember& CharacterParty::GetMemberByTargetType(const String& sCharacterTargetType)
{
    return const_cast<CharacterPartyMember&>(static_cast<const CharacterParty&>(*this).GetMemberByTargetType(sCharacterTargetType));
}

StringArray CharacterParty::GetMemberCharacterIDs() const
{
    StringArray vMemberCharacterIDs;
    for(auto& member : GetMembers())
    {
        vMemberCharacterIDs.push_back(member.first);
    }
    return vMemberCharacterIDs;
}

Bool CharacterParty::GetCharacterIDsFromTargetType(const String& sCharacterTargetType, StringArray& vCharacterIDs) const
{
    // Check if requesting something that cannot be resolved
    CharacterTargetType eTargetType = GetEnumFromString<CharacterTargetType>(sCharacterTargetType);
    switch(eTargetType)
    {
        case CharacterTargetType::Self:
        case CharacterTargetType::ActionTargetsThisAction:
        case CharacterTargetType::ActionSourceThisAction:
        case CharacterTargetType::ActionTargetsThisRound:
        case CharacterTargetType::ActionSourcesThisRound:
        case CharacterTargetType::ActionTargetsLastRound:
        case CharacterTargetType::ActionSourcesLastRound:
        case CharacterTargetType::MostRecentActionTargets:
        case CharacterTargetType::MostRecentActionSource:
            return false;
        default:
            break;
    }

    // Check if requesting for all allies/enemies
    StringArray vAllMemberCharacterIDs = GetMemberCharacterIDs();
    CharacterPartyType ePartyType = GetEnumFromString<CharacterPartyType>(GetPartyType());
    if((ePartyType == +CharacterPartyType::Ally && eTargetType == +CharacterTargetType::AllAllies) ||
       (ePartyType == +CharacterPartyType::Enemy && eTargetType == +CharacterTargetType::AllEnemies))
    {
        vCharacterIDs = vAllMemberCharacterIDs;
        return true;
    }

    // Then check for specific targets
    const CharacterPartyMember& member = GetMemberByTargetType(sCharacterTargetType);
    if(!member.GetCharacterID().empty())
    {
        vCharacterIDs.push_back(member.GetCharacterID());
        return true;
    }
    return false;
}

UInt CharacterParty::GetStatusMemberCount(const String& sStatus) const
{
    UInt uCount = 0;
    const CharacterStatusType eStatusType = GetEnumFromStringOrNone<CharacterStatusType>(sStatus);
    for(auto& member : GetMembers())
    {
        const Character& character = CharacterManager::GetInstance()->GetCharacter(member.first);
        const CharacterBattleData& battleData = character.GetBattleData();
        switch(eStatusType)
        {
            case CharacterStatusType::Dead:
                uCount += (battleData.GetIsDead()) ? 1 : 0;
                break;
            case CharacterStatusType::Unconscious:
                uCount += (battleData.GetIsUnconscious()) ? 1 : 0;
                break;
            default:
                break;
        }
    }
    return uCount;
}

Bool CharacterParty::AddRandomItems(const StringArray& vTreeTypes, Int iNumRandomItems, Int iAmountStart, Int iAmountEnd)
{
    // Notify user
    LOG_FORMAT_STATEMENT(
        "Trying to add random items to party '{}' "
        "(vTreeTypes = '{}', iNumRandomItems = {}, iAmountStart = {}, iAmountEnd = {})\n",
        GetPartyID().c_str(),
        ConcatStringVector(vTreeTypes).c_str(),
        iNumRandomItems,
        iAmountStart,
        iAmountEnd);

    // Get lists of all items
    TreeIndexArray vAllArmors = ItemTree::GetAllArmorItems();
    TreeIndexArray vAllIngredients = ItemTree::GetAllIngredientItems();
    TreeIndexArray vAllPotions = ItemTree::GetAllPotionItems();
    TreeIndexArray vAllWeapons = ItemTree::GetAllWeaponItems();

    // Shuffle item lists
    ShuffleVector<TreeIndex>(vAllArmors);
    ShuffleVector<TreeIndex>(vAllIngredients);
    ShuffleVector<TreeIndex>(vAllPotions);
    ShuffleVector<TreeIndex>(vAllWeapons);

    // Take a look at each tree type
    Bool bAtLeastOneAdded = false;
    TreeIndexArray vAddedRandomTreeIndices;
    for(const String& sTreeType : vTreeTypes)
    {
        // Only do a certain amount of random pulls
        const ItemTreeType eItemTreeType = GetEnumFromStringOrNone<ItemTreeType>(sTreeType);
        for(Int i = 0; i < iNumRandomItems; i++)
        {
            // Get the random item
            TreeIndex randomTreeIndex;
            switch(eItemTreeType)
            {
                case ItemTreeType::Armor:
                    randomTreeIndex = GetRandomVectorValue<TreeIndex>(vAllArmors);
                    break;
                case ItemTreeType::Ingredient:
                    randomTreeIndex = GetRandomVectorValue<TreeIndex>(vAllIngredients);
                    break;
                case ItemTreeType::Potion:
                    randomTreeIndex = GetRandomVectorValue<TreeIndex>(vAllPotions);
                    break;
                case ItemTreeType::Weapon:
                    randomTreeIndex = GetRandomVectorValue<TreeIndex>(vAllWeapons);
                    break;
                default:
                    break;
            }

            // Add item
            if(!randomTreeIndex.empty())
            {
                UInt uAmount = GetRandomIntValue<Int>(iAmountStart, iAmountEnd);
                Bool bSuccess = AddItemByTreeIndex(randomTreeIndex, uAmount);
                if(bSuccess)
                {
                    LOG_FORMAT_STATEMENT("Added item '{}' to party '{}' by amount {}\n",
                        randomTreeIndex.GetTreeBranchLeafType().c_str(),
                        GetPartyID().c_str(),
                        uAmount);
                    vAddedRandomTreeIndices.push_back(randomTreeIndex);
                }
                bAtLeastOneAdded = bAtLeastOneAdded || bSuccess;
            }
        }
    }
    return bAtLeastOneAdded;
}

Bool CharacterParty::AddItemByLeaf(const String& sLeaf, UInt uAmount)
{
    TreeIndex treeIndex = ItemTree::ResolveItemLeafIntoIndex(sLeaf);
    return AddItemByTreeIndex(treeIndex, uAmount);
}

Bool CharacterParty::AddItemByTreeIndex(const TreeIndex& treeIndex, UInt uAmount)
{
    if(treeIndex.empty())
    {
        ERROR_STATEMENT("Received an empty tree index");
        return false;
    }

    if(!ItemTree::DoesItemDataExist(treeIndex))
    {
        ERROR_FORMAT_STATEMENT("Tree index '{}' was not found\n", treeIndex.GetTreeBranchLeafType().c_str());
        return false;
    }

    String sLeaf = treeIndex.GetLeaf();
    if(GetItems().count(sLeaf) > 0)
    {
        CharacterPartyItem& item = GetItems().at(sLeaf);
#ifdef DEBUG
        Json jsonData = item;
        String sJsonString = jsonData.dump(4);
        LOG_FORMAT_STATEMENT("Adding value of {} to existing item '{}' to party (PartyID = '{}'):\n{}\n",
            uAmount,
            sLeaf.c_str(),
            GetPartyID().c_str(),
            sJsonString.c_str());
#endif
        return item.AddAmount(uAmount);
    }
    else
    {
        String sItemType = ItemTree::RetrieveItemType(treeIndex);
        StringArray vEquipTypes = ConvertItemTypeToCharacterEquipTypes(sItemType);
        CharacterPartyItem newItem;
        newItem.SetItemTreeIndex(treeIndex);
        newItem.SetItemAmount(uAmount);
        newItem.SetEquipCount(0);
        newItem.SetApplicableEquipmentSlots(vEquipTypes);
        GetItems().insert({sLeaf, newItem});
#ifdef DEBUG
        Json jsonData = newItem;
        String sJsonString = jsonData.dump(4);
        LOG_FORMAT_STATEMENT("Adding new item '{}' to party (PartyID = '{}'):\n{}\n",
            sLeaf.c_str(),
            GetPartyID().c_str(),
            sJsonString.c_str());
#endif
        return true;
    }
}

Bool CharacterParty::RemoveItemByLeaf(const String& sLeaf, UInt uAmount)
{
    TreeIndex treeIndex = ItemTree::ResolveItemLeafIntoIndex(sLeaf);
    return RemoveItemByTreeIndex(treeIndex, uAmount);
}

Bool CharacterParty::RemoveItemByTreeIndex(const TreeIndex& treeIndex, UInt uAmount)
{
    if(treeIndex.empty())
    {
        ERROR_STATEMENT("Received an empty tree index");
        return false;
    }

    if(!ItemTree::DoesItemDataExist(treeIndex))
    {
        ERROR_FORMAT_STATEMENT("Tree index '{}' was not found\n", treeIndex.GetTreeBranchLeafType().c_str());
        return false;
    }

    String sLeaf = treeIndex.GetLeaf();
    if(GetItems().count(sLeaf) == 0)
    {
        LOG_FORMAT_STATEMENT("Item '{}' could not be removed from party '{}' because it was not present\n",
            sLeaf.c_str(),
            GetPartyID().c_str());
        return false;
    }

    if(GetItems().count(sLeaf) > 0)
    {
        CharacterPartyItem& item = GetItems().at(sLeaf);
#ifdef DEBUG
        Json jsonData = item;
        String sJsonString = jsonData.dump(4);
        LOG_FORMAT_STATEMENT("Subtracting value of {} from existing item '{}' to party (PartyID = '{}'):\n{}\n",
            uAmount,
            sLeaf.c_str(),
            GetPartyID().c_str(),
            sJsonString.c_str());
#endif
        return item.RemoveAmount(uAmount);
    }
    return false;
}

const CharacterPartyItem& CharacterParty::GetItemByLeaf(const String& sLeaf) const
{
    return GetItems().at(sLeaf);
}

const CharacterPartyItem& CharacterParty::GetItemByTreeIndex(const TreeIndex& treeIndex) const
{
    return GetItems().at(treeIndex.GetLeaf());
}

CharacterPartyItem& CharacterParty::GetItemByLeaf(const String& sLeaf)
{
    return const_cast<CharacterPartyItem&>(static_cast<const CharacterParty&>(*this).GetItemByLeaf(sLeaf));
}

CharacterPartyItem& CharacterParty::GetItemByTreeIndex(const TreeIndex& treeIndex)
{
    return const_cast<CharacterPartyItem&>(static_cast<const CharacterParty&>(*this).GetItemByTreeIndex(treeIndex));
}

TreeIndex CharacterParty::GetBestUnequippedItem(const String& sCharacterID, const String& sSlot) const
{
    // Check character
    TreeIndex bestItem;
    if(!IsMemberPresent(sCharacterID))
    {
        return bestItem;
    }

    // Get shield count for this weapon set (if applicable)
    // We do this because we don't want to autofill more than one shield
    LOG_FORMAT_STATEMENT("Looking for best unequipped item (matching slot '{}') for character '{}' in party '{}'\n",
        sSlot.c_str(),
        sCharacterID.c_str(),
        GetPartyID().c_str());
    const String sWeaponSet = ConvertCharacterEquipmentTypeToCharacterWeaponSetType(sSlot);
    UInt uShieldCount = 0;
    if(!IsNoneTypeForEnum<CharacterWeaponSetType>(sWeaponSet))
    {
        uShieldCount = GetMemberByID(sCharacterID).GetEquippedShieldCount(sWeaponSet);
    }

    // Look at each of the matching, unequipped items the party has and find the best one
    for(auto& item : GetItems())
    {
        if(uShieldCount == 1 && ItemTree::IsItemShield(item.second.GetItemTreeIndex()))
        {
            continue;
        }

        if(!item.second.DoesMatchSlot(sSlot))
        {
            continue;
        }

        if(!item.second.CanEquipAmount(1))
        {
            continue;
        }

        if(bestItem.empty())
        {
            bestItem = item.second.GetItemTreeIndex();
            continue;
        }

        Bool bIsArmor = ItemTree::DoesItemDataArmorExist(item.second.GetItemTreeIndex());
        Bool bIsWeapon = ItemTree::DoesItemDataWeaponExist(item.second.GetItemTreeIndex());
        if(
            (bIsArmor && ItemTree::IsArmorBetter(item.second.GetItemTreeIndex(), bestItem)) ||
            (bIsWeapon && ItemTree::IsWeaponBetter(item.second.GetItemTreeIndex(), bestItem)))
        {
            bestItem = item.second.GetItemTreeIndex();
        }
    }
#if DEBUG
    if(!bestItem.empty())
    {
        LOG_FORMAT_STATEMENT("Found item '{}'\n", bestItem.GetTreeBranchLeafType().c_str());
    }
#endif
    return bestItem;
}

Bool CharacterParty::EquipItem(const String& sCharacterID, const String& sLeaf, const String& sSlot)
{
    // Get the item and character
    CharacterPartyItem& item = GetItemByLeaf(sLeaf);
    CharacterPartyMember& member = GetMemberByID(sCharacterID);

    // Check if the item can be equipped
    if(!item.DoesMatchSlot(sSlot))
    {
        ERROR_FORMAT_STATEMENT("Item '{}' does not match slot '{}'\n",
            sLeaf.c_str(),
            sSlot.c_str());
        return false;
    }
    if(!item.CanEquipAmount(1))
    {
        ERROR_FORMAT_STATEMENT("Item '{}' cannot be equipped (Amount = {}, Equip Count = {})\n",
            sLeaf.c_str(),
            item.GetItemAmount(),
            item.GetEquipCount());
        return false;
    }
    if(!member.CanAddEquippedItem(item.GetItemTreeIndex()))
    {
        ERROR_FORMAT_STATEMENT("Member '{}' in party '{}' cannot equip item '{}'\n",
            sCharacterID.c_str(),
            GetPartyID().c_str(),
            sLeaf.c_str());
        return false;
    }

    // Mark the item as being equipped
    if(!member.AddEquippedItem(item.GetItemTreeIndex(), sSlot) || !item.EquipAmount(1))
    {
        ERROR_FORMAT_STATEMENT("Member '{}' in party '{}' was not able to equip item '{}' to slot '{}'\n",
            sCharacterID.c_str(),
            GetPartyID().c_str(),
            sLeaf.c_str(),
            sSlot.c_str());
        return false;
    }
    return true;
}

Bool CharacterParty::UnequipItem(const String& sCharacterID, const String& sLeaf, const String& sSlot)
{
    // Get the item and character
    CharacterPartyItem& item = GetItemByLeaf(sLeaf);
    CharacterPartyMember& member = GetMemberByID(sCharacterID);

    // Check if the item can be unequipped
    if(!item.DoesMatchSlot(sSlot))
    {
        ERROR_FORMAT_STATEMENT("Item '{}' does not match slot '{}'\n",
            sLeaf.c_str(),
            sSlot.c_str());
        return false;
    }
    if(!item.CanUnequipAmount(1))
    {
        ERROR_FORMAT_STATEMENT("Item '{}' cannot be unequipped (Amount = {}, Equip Count = {})\n",
            sLeaf.c_str(),
            item.GetItemAmount(),
            item.GetEquipCount());
        return false;
    }
    if(!member.CanRemoveEquippedItem(item.GetItemTreeIndex()))
    {
        ERROR_FORMAT_STATEMENT("Member '{}' in party '{}' cannot unequip item '{}'\n",
            sCharacterID.c_str(),
            GetPartyID().c_str(),
            sLeaf.c_str());
        return false;
    }

    // Mark the item as being equipped
    if(!member.RemoveEquippedItem(item.GetItemTreeIndex(), sSlot) || !item.UnequipAmount(1))
    {
        ERROR_FORMAT_STATEMENT("Member '{}' in party '{}' was not able to unequip item '{}' to slot '{}'\n",
            sCharacterID.c_str(),
            GetPartyID().c_str(),
            sLeaf.c_str(),
            sSlot.c_str());
        return false;
    }
    return true;
}

Bool CharacterParty::EquipBestItems(const String& sCharacterID)
{
    // First unequip all that character's items
    UnequipAllItems(sCharacterID);

    // Get the best available item for each equipment slot
    for(const String& sEquipType : CharacterEquipmentType::_names())
    {
        // Get best item for this slot
        TreeIndex bestItemForSlot = GetBestUnequippedItem(sCharacterID, sEquipType);
        if(bestItemForSlot.empty())
        {
            continue;
        }

        // Try equipping
        if(!EquipItem(sCharacterID, bestItemForSlot.GetLeaf(), sEquipType))
        {
            continue;
        }
    }
    return true;
}

Bool CharacterParty::EquipBestItemsForAllMembers()
{
    for(auto& member : GetMembers())
    {
        EquipBestItems(member.first);
    }
    return true;
}

Bool CharacterParty::UnequipAllItems(const String& sCharacterID)
{
    // Get the member
    CharacterPartyMember& member = GetMemberByID(sCharacterID);

    // Try unequipping all of the character's items
    Bool bAtLeastOneSuccess = false;
    for(auto&& equippedItem : member.GetEquippedItems())
    {
        Bool bSuccess = UnequipItem(
            sCharacterID,
            equippedItem.GetItemTreeIndex().GetLeaf(),
            equippedItem.GetItemSlot());
        bAtLeastOneSuccess = bAtLeastOneSuccess || bSuccess;
    }
    return bAtLeastOneSuccess;
}

Bool CharacterParty::UnequipAllItemsForAllMembers()
{
    for(auto& member : GetMembers())
    {
        UnequipAllItems(member.first);
    }
    return true;
}

UInt CharacterParty::GetMemberCount() const
{
    return static_cast<UInt>(GetMembers().size());
}

UInt CharacterParty::GetItemCount() const
{
    return static_cast<UInt>(GetItems().size());
}

String CharacterParty::GetDescription() const
{
    String sDescription;
#if DEBUG
    sDescription += "Party ID: " + GetPartyID() + "\n";
    sDescription += "Party Type: " + GetPartyType() + "\n";
    sDescription += "Play Time: " + ConvertGameTimeToString(GetPlayTime()) + "\n";
    sDescription += "Members: \n";
    for(auto& member: GetMembers())
    {
        sDescription += "\t" + member.first + "\n";
    }
#endif
    return sDescription;
}

void CharacterParty::ResetPlayTime()
{
    LOG_FORMAT_STATEMENT("Resetting play time for party '{}'\n", GetPartyID().c_str());
    SetCurrentPlayTime(0);
    SetLastTimePoint(STDGetCurrentTimePoint());
    SetPlayTimePaused(true);
}

void CharacterParty::PausePlayTime()
{
    LOG_FORMAT_STATEMENT("Pausing play time for party '{}'\n", GetPartyID().c_str());
    if (GetPlayTimePaused())
    {
        return;
    }
    STDTimePoint currentTimePoint = STDGetCurrentTimePoint();
    ULongLong uDuration = STDGetTimePointDuration(currentTimePoint - GetLastTimePoint()).count();
    SetCurrentPlayTime(GetCurrentPlayTime() + uDuration);
    SetPlayTimePaused(true);
}

void CharacterParty::ResumePlayTime()
{
    LOG_FORMAT_STATEMENT("Resuming play time for party '{}'\n", GetPartyID().c_str());
    if (!GetPlayTimePaused())
    {
        return;
    }
    SetLastTimePoint(STDGetCurrentTimePoint());
    SetPlayTimePaused(false);
}

ULongLong CharacterParty::GetPlayTime() const
{
    if (GetPlayTimePaused())
    {
        return GetCurrentPlayTime();
    }
    else
    {
        STDTimePoint currentTimePoint = STDGetCurrentTimePoint();
        ULongLong uDuration = STDGetTimePointDuration(currentTimePoint - GetLastTimePoint()).count();
        return (GetCurrentPlayTime() + uDuration);
    }
}

void CharacterParty::SetPlayTime(ULongLong uTime)
{
    SetCurrentPlayTime(uTime);
}

void to_json(Json& jsonData, const CharacterParty& obj)
{
    // Party ID
    SET_JSON_DATA(PartyID);

    // Party type
    SET_JSON_DATA(PartyType);

    // Map of members
    SET_JSON_DATA(Members);

    // Map of items
    SET_JSON_DATA(Items);

    // Arrays of available target types
    SET_JSON_DATA(AvailableTargetTypes);

    // Array of taken target types
    SET_JSON_DATA(TakenTargetTypes);

    // Play time
    SET_JSON_DATA(PlayTime);
}

void from_json(const Json& jsonData, CharacterParty& obj)
{
    // Party ID
    SET_OBJ_DATA(PartyID, String);

    // Party type
    SET_OBJ_DATA(PartyType, String);

    // Map of members
    SET_OBJ_DATA(Members, CharacterParty::CharacterPartyMemberMapType);

    // Map of items
    SET_OBJ_DATA(Items, CharacterParty::CharacterPartyItemMapType);

    // Arrays of available target types
    SET_OBJ_DATA(AvailableTargetTypes, StringArray);

    // Array of taken target types
    SET_OBJ_DATA(TakenTargetTypes, StringArray);

    // Play time
    SET_OBJ_DATA(PlayTime, ULongLong);
}

};
