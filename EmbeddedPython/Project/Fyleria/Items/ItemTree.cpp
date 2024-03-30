// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

// Internal includes
#include "Items/ItemTree.h"
#include "Config/ConfigManager.h"
#include "Character/CharacterManager.h"
#include "CharacterParty/CharacterPartyManager.h"
#include "Utility/Constants.h"
#include "Utility/FantasyName.h"
#include "Utility/Json.h"

namespace Gecko
{

template <class T>
void PostProcessItems(const TreeIndexArray& vTreeIndices)
{
    for(auto& treeIndex : vTreeIndices)
    {
        auto& itemData = T::GetInstance()->GetLeaf(treeIndex);
        itemData.SetItemTreeIndex(treeIndex);
        for(auto& statChange : itemData.GetStatChanges())
        {
            statChange.SetItemTreeIndex(treeIndex);
        }
    }
}

void ItemTree::LoadItemTreesIntoMemory()
{
    // Armor
    ItemTreeArmor::GetInstance()->AddBranch("Chest", JoinPathsCanonical(GetDataDirectory(), ITEM_FILE_ARMOR_CHEST));
    ItemTreeArmor::GetInstance()->AddBranch("Feet", JoinPathsCanonical(GetDataDirectory(), ITEM_FILE_ARMOR_FEET));
    ItemTreeArmor::GetInstance()->AddBranch("Finger", JoinPathsCanonical(GetDataDirectory(), ITEM_FILE_ARMOR_FINGER));
    ItemTreeArmor::GetInstance()->AddBranch("Hands", JoinPathsCanonical(GetDataDirectory(), ITEM_FILE_ARMOR_HANDS));
    ItemTreeArmor::GetInstance()->AddBranch("Head", JoinPathsCanonical(GetDataDirectory(), ITEM_FILE_ARMOR_HEAD));
    ItemTreeArmor::GetInstance()->AddBranch("Neck", JoinPathsCanonical(GetDataDirectory(), ITEM_FILE_ARMOR_NECK));
    ItemTreeArmor::GetInstance()->AddBranch("Legs", JoinPathsCanonical(GetDataDirectory(), ITEM_FILE_ARMOR_LEGS));
    ItemTreeArmor::GetInstance()->AddBranch("Shield", JoinPathsCanonical(GetDataDirectory(), ITEM_FILE_ARMOR_SHIELD));

    // Ingredient
    ItemTreeIngredient::GetInstance()->AddBranch("Bar", JoinPathsCanonical(GetDataDirectory(), ITEM_FILE_INGREDIENT_BAR));
    ItemTreeIngredient::GetInstance()->AddBranch("Cloth", JoinPathsCanonical(GetDataDirectory(), ITEM_FILE_INGREDIENT_CLOTH));
    ItemTreeIngredient::GetInstance()->AddBranch("Crystal", JoinPathsCanonical(GetDataDirectory(), ITEM_FILE_INGREDIENT_CRYSTAL));
    ItemTreeIngredient::GetInstance()->AddBranch("Leather", JoinPathsCanonical(GetDataDirectory(), ITEM_FILE_INGREDIENT_LEATHER));
    ItemTreeIngredient::GetInstance()->AddBranch("Mail", JoinPathsCanonical(GetDataDirectory(), ITEM_FILE_INGREDIENT_MAIL));
    ItemTreeIngredient::GetInstance()->AddBranch("Plate", JoinPathsCanonical(GetDataDirectory(), ITEM_FILE_INGREDIENT_PLATE));
    ItemTreeIngredient::GetInstance()->AddBranch("Scale", JoinPathsCanonical(GetDataDirectory(), ITEM_FILE_INGREDIENT_SCALE));
    ItemTreeIngredient::GetInstance()->AddBranch("Screw", JoinPathsCanonical(GetDataDirectory(), ITEM_FILE_INGREDIENT_SCREW));
    ItemTreeIngredient::GetInstance()->AddBranch("Sheet", JoinPathsCanonical(GetDataDirectory(), ITEM_FILE_INGREDIENT_SHEET));
    ItemTreeIngredient::GetInstance()->AddBranch("Stud", JoinPathsCanonical(GetDataDirectory(), ITEM_FILE_INGREDIENT_STUD));
    ItemTreeIngredient::GetInstance()->AddBranch("Thread", JoinPathsCanonical(GetDataDirectory(), ITEM_FILE_INGREDIENT_THREAD));

    // Potion
    ItemTreePotion::GetInstance()->AddBranch("Energy", JoinPathsCanonical(GetDataDirectory(), ITEM_FILE_POTION_ENERGY));
    ItemTreePotion::GetInstance()->AddBranch("Heal", JoinPathsCanonical(GetDataDirectory(), ITEM_FILE_POTION_HEAL));
    ItemTreePotion::GetInstance()->AddBranch("Magic", JoinPathsCanonical(GetDataDirectory(), ITEM_FILE_POTION_MAGIC));
    ItemTreePotion::GetInstance()->AddBranch("Speed", JoinPathsCanonical(GetDataDirectory(), ITEM_FILE_POTION_SPEED));

    // Weapon
    ItemTreeWeapon::GetInstance()->AddBranch("Blunt", JoinPathsCanonical(GetDataDirectory(), ITEM_FILE_WEAPON_BLUNT));
    ItemTreeWeapon::GetInstance()->AddBranch("Mage", JoinPathsCanonical(GetDataDirectory(), ITEM_FILE_WEAPON_MAGE));
    ItemTreeWeapon::GetInstance()->AddBranch("Pierce", JoinPathsCanonical(GetDataDirectory(), ITEM_FILE_WEAPON_PIERCE));
    ItemTreeWeapon::GetInstance()->AddBranch("Slash", JoinPathsCanonical(GetDataDirectory(), ITEM_FILE_WEAPON_SLASH));

    // Post process item data
    PostProcessItems<ItemTreeArmor>(GetAllArmorItems());
    PostProcessItems<ItemTreeIngredient>(GetAllIngredientItems());
    PostProcessItems<ItemTreePotion>(GetAllPotionItems());
    PostProcessItems<ItemTreeWeapon>(GetAllWeaponItems());
}

void ItemTree::UnloadItemTreesFromMemory()
{
    // Clear all item data
    ItemTreeArmor::GetInstance()->ClearAllData();
    ItemTreeIngredient::GetInstance()->ClearAllData();
    ItemTreePotion::GetInstance()->ClearAllData();
    ItemTreeWeapon::GetInstance()->ClearAllData();
}

template <class T>
void VerifyApplyStatChanges(const TreeIndexArray& vTreeIndices, const String& sCharacterTargetType)
{
    String sBaseType = (+CharacterSegmentType::Base)._to_string();
    for(auto& treeIndex : vTreeIndices)
    {
        auto& itemData = T::GetInstance()->GetLeaf(treeIndex);
        LOG_FORMAT_STATEMENT("Processing item (ItemTreeType = '{}', "
                             "ItemType = '{}', "
                             "ItemName = '{}', "
                             "StatChanges = %zu)\n",
            T::GetTreeType().c_str(),
            itemData.GetItemType().c_str(),
            itemData.GetItemName().c_str(),
            itemData.GetStatChanges().size());
        for(auto change : itemData.GetStatChanges())
        {
            Bool bAll, bOne = false;
            change.SetSourceTargetType(sCharacterTargetType);
            change.SetDestinationTargetType(sCharacterTargetType);
            change.SetChanceToApply(1.0);
            CharacterManager::GetInstance()->ApplyStatChange(sBaseType, change, bAll, bOne, true);
        }
    }
}

void ItemTree::VerifyItemTrees()
{
    // Log start
    LOG_STATEMENT("Verifying item trees...");

    // Load character generator
    CharacterGenerator generator;
    generator.RandomizeAll();

    // Generate a character and party
    const String sCharacterID("CharacterID");
    const String sCharacterPartyID("CharacterPartyID");
    const String sCharacterPartyType("Ally");
    CharacterManager::GetInstance()->GenerateCharacter(sCharacterID, generator);
    CharacterPartyManager::GetInstance()->CreateParty(sCharacterPartyID, sCharacterPartyType, true);
    CharacterPartyManager::GetInstance()->GetPartyByID(sCharacterPartyID).AddMember(sCharacterID);
    const String sCharacterTargetType = CharacterManager::GetInstance()->GetCharacter(sCharacterID).GetCharacterTargetType();

    // Apply all stat changes
    VerifyApplyStatChanges<ItemTreeArmor>(GetAllArmorItems(), sCharacterTargetType);
    VerifyApplyStatChanges<ItemTreeIngredient>(GetAllIngredientItems(), sCharacterTargetType);
    VerifyApplyStatChanges<ItemTreePotion>(GetAllPotionItems(), sCharacterTargetType);
    VerifyApplyStatChanges<ItemTreeWeapon>(GetAllWeaponItems(), sCharacterTargetType);

    // Cleanup
    CharacterPartyManager::GetInstance()->GetPartyByID(sCharacterPartyID).RemoveMember(sCharacterID);
    CharacterPartyManager::GetInstance()->UnloadParty(sCharacterPartyID);
    CharacterManager::GetInstance()->UnloadCharacter(sCharacterID);
}

Bool ItemTree::DoesItemDataExist(const TreeIndex& treeIndex)
{
    return (
        DoesItemDataArmorExist(treeIndex) ||
        DoesItemDataIngredientExist(treeIndex) ||
        DoesItemDataPotionExist(treeIndex) ||
        DoesItemDataWeaponExist(treeIndex)
    );
}

Bool ItemTree::DoesItemDataArmorExist(const TreeIndex& treeIndex)
{
    return ItemTreeArmor::GetInstance()->HasLeaf(treeIndex);
}

Bool ItemTree::DoesItemDataIngredientExist(const TreeIndex& treeIndex)
{
    return ItemTreeIngredient::GetInstance()->HasLeaf(treeIndex);
}

Bool ItemTree::DoesItemDataPotionExist(const TreeIndex& treeIndex)
{
    return ItemTreePotion::GetInstance()->HasLeaf(treeIndex);
}

Bool ItemTree::DoesItemDataWeaponExist(const TreeIndex& treeIndex)
{
    return ItemTreeWeapon::GetInstance()->HasLeaf(treeIndex);
}

const ItemDataArmor& ItemTree::RetrieveItemDataArmor(const TreeIndex& treeIndex)
{
    return ItemTreeArmor::GetInstance()->GetLeaf(treeIndex);
}

const ItemDataIngredient& ItemTree::RetrieveItemDataIngredient(const TreeIndex& treeIndex)
{
    return ItemTreeIngredient::GetInstance()->GetLeaf(treeIndex);
}

const ItemDataPotion& ItemTree::RetrieveItemDataPotion(const TreeIndex& treeIndex)
{
    return ItemTreePotion::GetInstance()->GetLeaf(treeIndex);
}

const ItemDataWeapon& ItemTree::RetrieveItemDataWeapon(const TreeIndex& treeIndex)
{
    return ItemTreeWeapon::GetInstance()->GetLeaf(treeIndex);
}

String ItemTree::RetrieveItemType(const TreeIndex& treeIndex)
{
    if(DoesItemDataArmorExist(treeIndex))
    {
        return RetrieveItemDataArmor(treeIndex).GetItemType();
    }
    else if(DoesItemDataIngredientExist(treeIndex))
    {
        return RetrieveItemDataIngredient(treeIndex).GetItemType();
    }
    else if(DoesItemDataPotionExist(treeIndex))
    {
        return (RetrieveItemDataPotion(treeIndex).GetItemType());
    }
    else if(DoesItemDataWeaponExist(treeIndex))
    {
        return RetrieveItemDataWeapon(treeIndex).GetItemType();
    }
    return GetNoneTypeForEnum<ItemTreeType>();
}

template <class T>
void AddItemLeaves(const String& sBranchName, TreeIndexArray& vLeaves)
{
    auto vNewLeaves = T::GetInstance()->GetAllLeaves(sBranchName);
    vLeaves.insert(vLeaves.end(), vNewLeaves.begin(), vNewLeaves.end());
}

TreeIndexArray ItemTree::GetAllArmorItems()
{
    TreeIndexArray vFinal;
    AddItemLeaves<ItemTreeArmor>("Chest", vFinal);
    AddItemLeaves<ItemTreeArmor>("Feet", vFinal);
    AddItemLeaves<ItemTreeArmor>("Finger", vFinal);
    AddItemLeaves<ItemTreeArmor>("Hands", vFinal);
    AddItemLeaves<ItemTreeArmor>("Head", vFinal);
    AddItemLeaves<ItemTreeArmor>("Neck", vFinal);
    AddItemLeaves<ItemTreeArmor>("Legs", vFinal);
    AddItemLeaves<ItemTreeArmor>("Shield", vFinal);
    return vFinal;
}

TreeIndexArray ItemTree::GetAllIngredientItems()
{
    TreeIndexArray vFinal;
    AddItemLeaves<ItemTreeIngredient>("Bar", vFinal);
    AddItemLeaves<ItemTreeIngredient>("Cloth", vFinal);
    AddItemLeaves<ItemTreeIngredient>("Crystal", vFinal);
    AddItemLeaves<ItemTreeIngredient>("Leather", vFinal);
    AddItemLeaves<ItemTreeIngredient>("Mail", vFinal);
    AddItemLeaves<ItemTreeIngredient>("Plate", vFinal);
    AddItemLeaves<ItemTreeIngredient>("Scale", vFinal);
    AddItemLeaves<ItemTreeIngredient>("Screw", vFinal);
    AddItemLeaves<ItemTreeIngredient>("Sheet", vFinal);
    AddItemLeaves<ItemTreeIngredient>("Stud", vFinal);
    AddItemLeaves<ItemTreeIngredient>("Thread", vFinal);
    return vFinal;
}

TreeIndexArray ItemTree::GetAllPotionItems()
{
    TreeIndexArray vFinal;
    AddItemLeaves<ItemTreePotion>("Energy", vFinal);
    AddItemLeaves<ItemTreePotion>("Heal", vFinal);
    AddItemLeaves<ItemTreePotion>("Magic", vFinal);
    AddItemLeaves<ItemTreePotion>("Speed", vFinal);
    return vFinal;
}

TreeIndexArray ItemTree::GetAllWeaponItems()
{
    TreeIndexArray vFinal;
    AddItemLeaves<ItemTreeWeapon>("Blunt", vFinal);
    AddItemLeaves<ItemTreeWeapon>("Mage", vFinal);
    AddItemLeaves<ItemTreeWeapon>("Pierce", vFinal);
    AddItemLeaves<ItemTreeWeapon>("Slash", vFinal);
    return vFinal;
}

TreeIndexArray ItemTree::GetAllEquippedItems(const String& sCharID)
{
    TreeIndexArray vFinal;
    if(!CharacterManager::GetInstance()->DoesCharacterExist(sCharID))
    {
        return vFinal;
    }

    const Character& character = CharacterManager::GetInstance()->GetCharacter(sCharID);
    for(auto& item : character.GetEquippedItems())
    {
        vFinal.push_back(item.GetItemTreeIndex());
    }
    return vFinal;
}

TreeIndex ItemTree::ResolveItemLeafIntoIndex(const String& sLeaf)
{
    // Branch name
    String sBranch;

    // Check armor
    sBranch = ItemTreeArmor::GetInstance()->GetBranchFromLeaf(sLeaf);
    if(!sBranch.empty())
    {
        return TreeIndex((+ItemTreeType::Armor)._to_string(), sBranch, sLeaf);
    }

    // Check weapon
    sBranch = ItemTreeWeapon::GetInstance()->GetBranchFromLeaf(sLeaf);
    if(!sBranch.empty())
    {
        return TreeIndex((+ItemTreeType::Weapon)._to_string(), sBranch, sLeaf);
    }

    // Check potion
    sBranch = ItemTreePotion::GetInstance()->GetBranchFromLeaf(sLeaf);
    if(!sBranch.empty())
    {
        return TreeIndex((+ItemTreeType::Potion)._to_string(), sBranch, sLeaf);
    }

    // Check ingredient
    sBranch = ItemTreeIngredient::GetInstance()->GetBranchFromLeaf(sLeaf);
    if(!sBranch.empty())
    {
        return TreeIndex((+ItemTreeType::Ingredient)._to_string(), sBranch, sLeaf);
    }

    // Nothing found
    return TreeIndex();
}

Bool ItemTree::IsItemActionable(const TreeIndex& treeIndex)
{
    if(DoesItemDataArmorExist(treeIndex))
    {
        return RetrieveItemDataArmor(treeIndex).IsActionable();
    }
    else if(DoesItemDataPotionExist(treeIndex))
    {
        return RetrieveItemDataPotion(treeIndex).IsActionable();
    }
    else if(DoesItemDataWeaponExist(treeIndex))
    {
        return RetrieveItemDataWeapon(treeIndex).IsActionable();
    }
    return false;
}

Bool ItemTree::GenerateItemCharacterActions(const TreeIndex& treeIndex,
    const String& sCharacterID,
    const String& sWeaponSet,
    CharacterActionArray& vActions)
{
    if(DoesItemDataArmorExist(treeIndex))
    {
        const ItemDataArmor& itemData = RetrieveItemDataArmor(treeIndex);
        if(itemData.IsActionable() && itemData.DoesMeetActionRequirements(sCharacterID, sWeaponSet))
        {
            CharacterActionArray vNewActions = itemData.CreateArmorActions(sCharacterID, sWeaponSet);
            vActions.insert(vActions.end(), vNewActions.begin(), vNewActions.end());
            return true;
        }
    }
    else if(DoesItemDataPotionExist(treeIndex))
    {
        const ItemDataPotion& itemData = RetrieveItemDataPotion(treeIndex);
        if(itemData.IsActionable() && itemData.DoesMeetActionRequirements(sCharacterID, sWeaponSet))
        {
            CharacterActionArray vNewActions = itemData.CreatePotionActions(sCharacterID, sWeaponSet);
            vActions.insert(vActions.end(), vNewActions.begin(), vNewActions.end());
            return true;
        }
    }
    else if(DoesItemDataWeaponExist(treeIndex))
    {
        const ItemDataWeapon& itemData = RetrieveItemDataWeapon(treeIndex);
        if(itemData.IsActionable() && itemData.DoesMeetActionRequirements(sCharacterID, sWeaponSet))
        {
            CharacterActionArray vNewActions = itemData.CreateWeaponActions(sCharacterID, sWeaponSet);
            vActions.insert(vActions.end(), vNewActions.begin(), vNewActions.end());
            return true;
        }
    }
    return false;
}

Bool ItemTree::IsArmorBetter(const TreeIndex& treeIndex1, const TreeIndex& treeIndex2)
{
    if(!DoesItemDataArmorExist(treeIndex1) || !DoesItemDataArmorExist(treeIndex2))
    {
        return false;
    }

    const ItemDataArmor& itemData1 = RetrieveItemDataArmor(treeIndex1);
    const ItemDataArmor& itemData2 = RetrieveItemDataArmor(treeIndex2);
    return (
        itemData1.GetBluntDefendPercent() > itemData2.GetBluntDefendPercent() &&
        itemData1.GetPierceDefendPercent() > itemData2.GetPierceDefendPercent() &&
        itemData1.GetSlashDefendPercent() > itemData2.GetSlashDefendPercent() &&
        itemData1.GetMagicDefendPercent() > itemData2.GetMagicDefendPercent());
}

Bool ItemTree::IsWeaponBetter(const TreeIndex& treeIndex1, const TreeIndex& treeIndex2)
{
    if(!DoesItemDataWeaponExist(treeIndex1) || !DoesItemDataWeaponExist(treeIndex2))
    {
        return false;
    }

    const ItemDataWeapon& itemData1 = RetrieveItemDataWeapon(treeIndex1);
    const ItemDataWeapon& itemData2 = RetrieveItemDataWeapon(treeIndex2);
    return (
        itemData1.GetBluntAttackPercent() > itemData2.GetBluntAttackPercent() &&
        itemData1.GetPierceAttackPercent() > itemData2.GetPierceAttackPercent() &&
        itemData1.GetSlashAttackPercent() > itemData2.GetSlashAttackPercent());
}

Bool ItemTree::IsItemWeapon(const TreeIndex& treeIndex)
{
    return DoesItemDataWeaponExist(treeIndex);
}

Bool ItemTree::IsItemShield(const TreeIndex& treeIndex)
{
    if(DoesItemDataArmorExist(treeIndex))
    {
        const ItemDataArmor& item = RetrieveItemDataArmor(treeIndex);
        const ItemType& eType = GetEnumFromString<ItemType>(item.GetItemType());
        return (
            eType == +ItemType::ArmorShieldPierce ||
            eType == +ItemType::ArmorShieldBlunt ||
            eType == +ItemType::ArmorShieldSlash);
    }
    return false;
}

StringArray ItemTree::GetActionTypes(const TreeIndex& treeIndex)
{
    StringArray vActionTypes;
    if(DoesItemDataArmorExist(treeIndex))
    {
        const ItemDataArmor& item = RetrieveItemDataArmor(treeIndex);
        vActionTypes.insert(vActionTypes.end(), item.GetActionTypes().begin(), item.GetActionTypes().end());
    }
    else if(DoesItemDataPotionExist(treeIndex))
    {
        const ItemDataPotion& item = RetrieveItemDataPotion(treeIndex);
        vActionTypes.insert(vActionTypes.end(), item.GetActionTypes().begin(), item.GetActionTypes().end());
    }
    else if(DoesItemDataWeaponExist(treeIndex))
    {
        const ItemDataWeapon& item = RetrieveItemDataWeapon(treeIndex);
        vActionTypes.insert(vActionTypes.end(), item.GetActionTypes().begin(), item.GetActionTypes().end());
    }
    return vActionTypes;
}

void ItemTree::FillItemStatChangeArrays(const TreeIndexArray& vItemDataArray,
    TreeIndexArray& vPassives,
    TreeIndexArray& vActives,
    TreeIndexArray& vActionables)
{
    // Use a set to make sure that we do not include duplicates
    STDUnorderedSet<String> tAlreadyUsed;

    // Split them into separate lists
    for(const TreeIndex& treeIndex : vItemDataArray)
    {
        String sIndexKey = treeIndex.GetTreeBranchLeafType();
        Bool bIsActionable = IsItemActionable(treeIndex);
        Bool bIsAlreadyUsed = (tAlreadyUsed.count(sIndexKey) == 1);
        if(bIsActionable && !bIsAlreadyUsed)
        {
            vActionables.push_back(treeIndex);
            tAlreadyUsed.insert(sIndexKey);
        }
        else if(!bIsActionable && !bIsAlreadyUsed)
        {
            for(const StatChange& statChange : GetStatChangesFromItemTreeIndex(treeIndex))
            {
                if(statChange.IsPassive())
                {
                    vPassives.push_back(treeIndex);
                    tAlreadyUsed.insert(sIndexKey);
                    break;
                }
                else if(statChange.IsActive())
                {
                    vActives.push_back(treeIndex);
                    tAlreadyUsed.insert(sIndexKey);
                    break;
                }
            }
        }
    }
}

};
