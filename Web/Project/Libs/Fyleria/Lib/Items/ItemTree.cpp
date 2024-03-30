// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#include "Items/ItemTree.h"
#include "Config/ConfigManager.h"
#include "Character/CharacterManager.h"
#include "Character/CharacterPartyManager.h"
#include "Utility/Constants.h"
#include "Utility/TypesFantasyName.h"
#include "Utility/TypesJson.h"

namespace Gecko
{

#define POSTPROCESS_ITEMS(tree)                                                         \
{                                                                                       \
    for(const TreeIndex& index : GetAll##tree##Items())                                 \
    {                                                                                   \
        ItemData##tree& itemData = ItemTree##tree::GetInstance()->GetLeaf(index);       \
        itemData.SetItemTreeIndex(index);                                               \
        for(StatChange& statChange : itemData.GetStatChanges())                         \
        {                                                                               \
            statChange.SetItemTreeIndex(index);                                         \
        }                                                                               \
    }                                                                                   \
}

void LoadItemTreesIntoMemory()
{
    // Armor
    ItemTreeArmor::GetInstance()->AddBranch(IndexedString("Chest"), IndexedString(ConfigManager::GetInstance()->GetItemArmorChestFile()));
    ItemTreeArmor::GetInstance()->AddBranch(IndexedString("Feet"), IndexedString(ConfigManager::GetInstance()->GetItemArmorFeetFile()));
    ItemTreeArmor::GetInstance()->AddBranch(IndexedString("Finger"), IndexedString(ConfigManager::GetInstance()->GetItemArmorFingerFile()));
    ItemTreeArmor::GetInstance()->AddBranch(IndexedString("Hands"), IndexedString(ConfigManager::GetInstance()->GetItemArmorHandsFile()));
    ItemTreeArmor::GetInstance()->AddBranch(IndexedString("Head"), IndexedString(ConfigManager::GetInstance()->GetItemArmorHeadFile()));
    ItemTreeArmor::GetInstance()->AddBranch(IndexedString("Neck"), IndexedString(ConfigManager::GetInstance()->GetItemArmorNeckFile()));
    ItemTreeArmor::GetInstance()->AddBranch(IndexedString("Legs"), IndexedString(ConfigManager::GetInstance()->GetItemArmorLegsFile()));
    ItemTreeArmor::GetInstance()->AddBranch(IndexedString("Shield"), IndexedString(ConfigManager::GetInstance()->GetItemArmorShieldFile()));

    // Ingredient
    ItemTreeIngredient::GetInstance()->AddBranch(IndexedString("Bar"), IndexedString(ConfigManager::GetInstance()->GetItemIngredientBarFile()));
    ItemTreeIngredient::GetInstance()->AddBranch(IndexedString("Cloth"), IndexedString(ConfigManager::GetInstance()->GetItemIngredientClothFile()));
    ItemTreeIngredient::GetInstance()->AddBranch(IndexedString("Crystal"), IndexedString(ConfigManager::GetInstance()->GetItemIngredientCrystalFile()));
    ItemTreeIngredient::GetInstance()->AddBranch(IndexedString("Leather"), IndexedString(ConfigManager::GetInstance()->GetItemIngredientLeatherFile()));
    ItemTreeIngredient::GetInstance()->AddBranch(IndexedString("Mail"), IndexedString(ConfigManager::GetInstance()->GetItemIngredientMailFile()));
    ItemTreeIngredient::GetInstance()->AddBranch(IndexedString("Plate"), IndexedString(ConfigManager::GetInstance()->GetItemIngredientPlateFile()));
    ItemTreeIngredient::GetInstance()->AddBranch(IndexedString("Scale"), IndexedString(ConfigManager::GetInstance()->GetItemIngredientScaleFile()));
    ItemTreeIngredient::GetInstance()->AddBranch(IndexedString("Screw"), IndexedString(ConfigManager::GetInstance()->GetItemIngredientScrewFile()));
    ItemTreeIngredient::GetInstance()->AddBranch(IndexedString("Sheet"), IndexedString(ConfigManager::GetInstance()->GetItemIngredientSheetFile()));
    ItemTreeIngredient::GetInstance()->AddBranch(IndexedString("Stud"), IndexedString(ConfigManager::GetInstance()->GetItemIngredientStudFile()));
    ItemTreeIngredient::GetInstance()->AddBranch(IndexedString("Thread"), IndexedString(ConfigManager::GetInstance()->GetItemIngredientThreadFile()));

    // Potion
    ItemTreePotion::GetInstance()->AddBranch(IndexedString("Energy"), IndexedString(ConfigManager::GetInstance()->GetItemPotionEnergyFile()));
    ItemTreePotion::GetInstance()->AddBranch(IndexedString("Heal"), IndexedString(ConfigManager::GetInstance()->GetItemPotionHealFile()));
    ItemTreePotion::GetInstance()->AddBranch(IndexedString("Magic"), IndexedString(ConfigManager::GetInstance()->GetItemPotionMagicFile()));
    ItemTreePotion::GetInstance()->AddBranch(IndexedString("Speed"), IndexedString(ConfigManager::GetInstance()->GetItemPotionSpeedFile()));

    // Weapon
    ItemTreeWeapon::GetInstance()->AddBranch(IndexedString("Blunt"), IndexedString(ConfigManager::GetInstance()->GetItemWeaponBluntFile()));
    ItemTreeWeapon::GetInstance()->AddBranch(IndexedString("Mage"), IndexedString(ConfigManager::GetInstance()->GetItemWeaponMageFile()));
    ItemTreeWeapon::GetInstance()->AddBranch(IndexedString("Pierce"), IndexedString(ConfigManager::GetInstance()->GetItemWeaponPierceFile()));
    ItemTreeWeapon::GetInstance()->AddBranch(IndexedString("Slash"), IndexedString(ConfigManager::GetInstance()->GetItemWeaponSlashFile()));

    // Post process item data
    POSTPROCESS_ITEMS(Armor);
    POSTPROCESS_ITEMS(Ingredient);
    POSTPROCESS_ITEMS(Potion);
    POSTPROCESS_ITEMS(Weapon);
}

void UnloadItemTreesFromMemory()
{
    // Clear all item data
    ItemTreeArmor::GetInstance()->ClearAllData();
    ItemTreeIngredient::GetInstance()->ClearAllData();
    ItemTreePotion::GetInstance()->ClearAllData();
    ItemTreeWeapon::GetInstance()->ClearAllData();
}

#define VERIFY_APPLY_STATCHANGES(tree, character_target)                                                        \
{                                                                                                               \
    for(const TreeIndex& index : GetAll##tree##Items())                                                         \
    {                                                                                                           \
        ItemData##tree& itemData = ItemTree##tree::GetInstance()->GetLeaf(index);                               \
        LOG_FORMAT_STATEMENT("Processing item (ItemTreeType = '%s', "                                           \
                             "ItemType = '%s', "                                                                \
                             "ItemName = '%s', "                                                                \
                             "StatChanges = %zu)\n",                                                            \
            #tree,                                                                                              \
            itemData.GetItemType().c_str(),                                                                     \
            itemData.GetItemName().c_str(),                                                                     \
            itemData.GetStatChanges().size());                                                                  \
        for(StatChange change : itemData.GetStatChanges())                                                      \
        {                                                                                                       \
            Bool bAll, bOne = false;                                                                            \
            change.SetSourceTargetType(character_target);                                                       \
            change.SetDestinationTargetType(character_target);                                                  \
            change.SetChanceToApply(1.0);                                                                       \
            CharacterManager::GetInstance()->ApplyStatChange(IndexedString("Base"), change, bAll, bOne, true);  \
        }                                                                                                       \
    }                                                                                                           \
}

void VerifyItemTrees()
{
    // Log start
    LOG_STATEMENT("Verifying item trees...");

    // Load character generator
    CharacterGenerator generator;
    IndexedString sGeneratorFile(ConfigManager::GetInstance()->GetCharacterGeneratorRandomFile());
    Bool bLoadedGenerator = generator.FromFile(sGeneratorFile);
    ASSERT_ERROR(bLoadedGenerator, "Could not load generator file '%s'\n", sGeneratorFile.c_str());
    if(!bLoadedGenerator)
    {
        return;
    }

    // Generate a character and party
    const IndexedString sCharacterID("CharacterID");
    const IndexedString sCharacterPartyID("CharacterPartyID");
    const IndexedString sCharacterPartyType("Ally");
    CharacterManager::GetInstance()->GenerateCharacter(sCharacterID, generator);
    CharacterPartyManager::GetInstance()->CreateParty(sCharacterPartyID, sCharacterPartyType, true);
    CharacterPartyManager::GetInstance()->GetPartyByID(sCharacterPartyID).AddMember(sCharacterID);
    const IndexedString sCharacterTargetType = CharacterManager::GetInstance()->GetCharacter(sCharacterID).GetCharacterTargetType();

    // Apply all stat changes
    VERIFY_APPLY_STATCHANGES(Armor, sCharacterTargetType);
    VERIFY_APPLY_STATCHANGES(Ingredient, sCharacterTargetType);
    VERIFY_APPLY_STATCHANGES(Potion, sCharacterTargetType);
    VERIFY_APPLY_STATCHANGES(Weapon, sCharacterTargetType);

    // Cleanup
    CharacterPartyManager::GetInstance()->GetPartyByID(sCharacterPartyID).RemoveMember(sCharacterID);
    CharacterPartyManager::GetInstance()->UnloadParty(sCharacterPartyID);
    CharacterManager::GetInstance()->UnloadCharacter(sCharacterID);
}

Bool DoesItemDataExist(const TreeIndex& index)
{
    return (
        DoesItemDataArmorExist(index) ||
        DoesItemDataIngredientExist(index) ||
        DoesItemDataPotionExist(index) ||
        DoesItemDataWeaponExist(index)
    );
}

Bool DoesItemDataArmorExist(const TreeIndex& index)
{
    return ItemTreeArmor::GetInstance()->HasLeaf(index);
}

Bool DoesItemDataIngredientExist(const TreeIndex& index)
{
    return ItemTreeIngredient::GetInstance()->HasLeaf(index);
}

Bool DoesItemDataPotionExist(const TreeIndex& index)
{
    return ItemTreePotion::GetInstance()->HasLeaf(index);
}

Bool DoesItemDataWeaponExist(const TreeIndex& index)
{
    return ItemTreeWeapon::GetInstance()->HasLeaf(index);
}

const ItemDataArmor& RetrieveItemDataArmor(const TreeIndex& index)
{
    return ItemTreeArmor::GetInstance()->GetLeaf(index);
}

const ItemDataIngredient& RetrieveItemDataIngredient(const TreeIndex& index)
{
    return ItemTreeIngredient::GetInstance()->GetLeaf(index);
}

const ItemDataPotion& RetrieveItemDataPotion(const TreeIndex& index)
{
    return ItemTreePotion::GetInstance()->GetLeaf(index);
}

const ItemDataWeapon& RetrieveItemDataWeapon(const TreeIndex& index)
{
    return ItemTreeWeapon::GetInstance()->GetLeaf(index);
}

IndexedString RetrieveItemType(const TreeIndex& index)
{
    if(DoesItemDataArmorExist(index))
    {
        return RetrieveItemDataArmor(index).GetItemType();
    }
    else if(DoesItemDataIngredientExist(index))
    {
        return RetrieveItemDataIngredient(index).GetItemType();
    }
    else if(DoesItemDataPotionExist(index))
    {
        return (RetrieveItemDataPotion(index).GetItemType());
    }
    else if(DoesItemDataWeaponExist(index))
    {
        return RetrieveItemDataWeapon(index).GetItemType();
    }
    return IndexedString("None");
}

#define ADD_ITEM_LEAVES(tree, branch)                                           \
{                                                                               \
    IndexedString sBranchName(#branch);                                         \
    auto vLeaves = ItemTree##tree::GetInstance()->GetAllLeaves(sBranchName);    \
    vFinal.insert(vFinal.end(), vLeaves.begin(), vLeaves.end());                \
}

TreeIndexList GetAllArmorItems()
{
    TreeIndexList vFinal;
    ADD_ITEM_LEAVES(Armor, Chest);
    ADD_ITEM_LEAVES(Armor, Feet);
    ADD_ITEM_LEAVES(Armor, Finger);
    ADD_ITEM_LEAVES(Armor, Hands);
    ADD_ITEM_LEAVES(Armor, Head);
    ADD_ITEM_LEAVES(Armor, Neck);
    ADD_ITEM_LEAVES(Armor, Legs);
    ADD_ITEM_LEAVES(Armor, Shield);
    return vFinal;
}

TreeIndexList GetAllIngredientItems()
{
    TreeIndexList vFinal;
    ADD_ITEM_LEAVES(Ingredient, Bar);
    ADD_ITEM_LEAVES(Ingredient, Cloth);
    ADD_ITEM_LEAVES(Ingredient, Crystal);
    ADD_ITEM_LEAVES(Ingredient, Leather);
    ADD_ITEM_LEAVES(Ingredient, Mail);
    ADD_ITEM_LEAVES(Ingredient, Plate);
    ADD_ITEM_LEAVES(Ingredient, Scale);
    ADD_ITEM_LEAVES(Ingredient, Screw);
    ADD_ITEM_LEAVES(Ingredient, Sheet);
    ADD_ITEM_LEAVES(Ingredient, Stud);
    ADD_ITEM_LEAVES(Ingredient, Thread);
    return vFinal;
}

TreeIndexList GetAllPotionItems()
{
    TreeIndexList vFinal;
    ADD_ITEM_LEAVES(Potion, Energy);
    ADD_ITEM_LEAVES(Potion, Heal);
    ADD_ITEM_LEAVES(Potion, Magic);
    ADD_ITEM_LEAVES(Potion, Speed);
    return vFinal;
}

TreeIndexList GetAllWeaponItems()
{
    TreeIndexList vFinal;
    ADD_ITEM_LEAVES(Weapon, Blunt);
    ADD_ITEM_LEAVES(Weapon, Mage);
    ADD_ITEM_LEAVES(Weapon, Pierce);
    ADD_ITEM_LEAVES(Weapon, Slash);
    return vFinal;
}

TreeIndexList GetAllEquippedItems(const IndexedString& sCharID)
{
    TreeIndexList vFinal;
    if(!CharacterManager::GetInstance()->DoesCharacterExist(sCharID))
    {
        return vFinal;
    }

    const Character& character = CharacterManager::GetInstance()->GetCharacter(sCharID);
    for(const CharacterProgressItem& item : character.GetEquippedItems())
    {
        vFinal.push_back(item.GetTreeIndex());
    }
    return vFinal;
}

TreeIndex ResolveItemLeafIntoIndex(const IndexedString& sLeaf)
{
    TreeIndex armorIndex(IndexedString("Item"), IndexedString("Armor"), sLeaf);
    TreeIndex ingredientIndex(IndexedString("Item"), IndexedString("Ingredient"), sLeaf);
    TreeIndex potionIndex(IndexedString("Item"), IndexedString("Potion"), sLeaf);
    TreeIndex weaponIndex(IndexedString("Item"), IndexedString("Weapon"), sLeaf);
    if(DoesItemDataArmorExist(armorIndex))
    {
        return armorIndex;
    }
    else if(DoesItemDataIngredientExist(ingredientIndex))
    {
        return ingredientIndex;
    }
    else if(DoesItemDataPotionExist(potionIndex))
    {
        return potionIndex;
    }
    else if(DoesItemDataWeaponExist(weaponIndex))
    {
        return weaponIndex;
    }
    return TreeIndex();
}

Bool IsItemActionable(const TreeIndex& index)
{
    if(DoesItemDataArmorExist(index))
    {
        return RetrieveItemDataArmor(index).IsActionable();
    }
    else if(DoesItemDataPotionExist(index))
    {
        return RetrieveItemDataPotion(index).IsActionable();
    }
    else if(DoesItemDataWeaponExist(index))
    {
        return RetrieveItemDataWeapon(index).IsActionable();
    }
    return false;
}

Bool GenerateItemCharacterActions(const TreeIndex& index,
    const IndexedString& sCharacterID,
    const IndexedString& sWeaponSet,
    CharacterActionSharedPtrList& vActions)
{
    if(DoesItemDataArmorExist(index))
    {
        const ItemDataArmor& itemData = RetrieveItemDataArmor(index);
        if(itemData.IsActionable() && itemData.DoesMeetActionRequirements(sCharacterID, sWeaponSet))
        {
            CharacterActionSharedPtrList vNewActions = itemData.CreateArmorActions(sCharacterID, sWeaponSet);
            vActions.insert(vActions.end(), vNewActions.begin(), vNewActions.end());
            return true;
        }
    }
    else if(DoesItemDataPotionExist(index))
    {
        const ItemDataPotion& itemData = RetrieveItemDataPotion(index);
        if(itemData.IsActionable() && itemData.DoesMeetActionRequirements(sCharacterID, sWeaponSet))
        {
            CharacterActionSharedPtrList vNewActions = itemData.CreatePotionActions(sCharacterID, sWeaponSet);
            vActions.insert(vActions.end(), vNewActions.begin(), vNewActions.end());
            return true;
        }
    }
    else if(DoesItemDataWeaponExist(index))
    {
        const ItemDataWeapon& itemData = RetrieveItemDataWeapon(index);
        if(itemData.IsActionable() && itemData.DoesMeetActionRequirements(sCharacterID, sWeaponSet))
        {
            CharacterActionSharedPtrList vNewActions = itemData.CreateWeaponActions(sCharacterID, sWeaponSet);
            vActions.insert(vActions.end(), vNewActions.begin(), vNewActions.end());
            return true;
        }
    }
    return false;
}

Bool IsArmorBetter(const TreeIndex& index1, const TreeIndex& index2)
{
    if(!DoesItemDataArmorExist(index1) || !DoesItemDataArmorExist(index2))
    {
        return false;
    }

    const ItemDataArmor& itemData1 = RetrieveItemDataArmor(index1);
    const ItemDataArmor& itemData2 = RetrieveItemDataArmor(index2);
    return (
        itemData1.GetBluntDefendPercent() > itemData2.GetBluntDefendPercent() &&
        itemData1.GetPierceDefendPercent() > itemData2.GetPierceDefendPercent() &&
        itemData1.GetSlashDefendPercent() > itemData2.GetSlashDefendPercent() &&
        itemData1.GetMagicDefendPercent() > itemData2.GetMagicDefendPercent());
}

Bool IsWeaponBetter(const TreeIndex& index1, const TreeIndex& index2)
{
    if(!DoesItemDataWeaponExist(index1) || !DoesItemDataWeaponExist(index2))
    {
        return false;
    }

    const ItemDataWeapon& itemData1 = RetrieveItemDataWeapon(index1);
    const ItemDataWeapon& itemData2 = RetrieveItemDataWeapon(index2);
    return (
        itemData1.GetBluntAttackPercent() > itemData2.GetBluntAttackPercent() &&
        itemData1.GetPierceAttackPercent() > itemData2.GetPierceAttackPercent() &&
        itemData1.GetSlashAttackPercent() > itemData2.GetSlashAttackPercent());
}

Bool IsItemWeapon(const TreeIndex& index)
{
    return DoesItemDataWeaponExist(index);
}

Bool IsItemShield(const TreeIndex& index)
{
    if(DoesItemDataArmorExist(index))
    {
        const ItemDataArmor& item = RetrieveItemDataArmor(index);
        const ItemType& eType = StringToItemType(item.GetItemType());
        return (
            eType == +ItemType::ArmorShieldPierce ||
            eType == +ItemType::ArmorShieldBlunt ||
            eType == +ItemType::ArmorShieldSlash);
    }
    return false;
}

IndexedStringList GetActionTypes(const TreeIndex& index)
{
    IndexedStringList vActionTypes;
    if(DoesItemDataArmorExist(index))
    {
        const ItemDataArmor& item = RetrieveItemDataArmor(index);
        vActionTypes.insert(vActionTypes.end(), item.GetActionTypes().begin(), item.GetActionTypes().end());
    }
    else if(DoesItemDataPotionExist(index))
    {
        const ItemDataPotion& item = RetrieveItemDataPotion(index);
        vActionTypes.insert(vActionTypes.end(), item.GetActionTypes().begin(), item.GetActionTypes().end());
    }
    else if(DoesItemDataWeaponExist(index))
    {
        const ItemDataWeapon& item = RetrieveItemDataWeapon(index);
        vActionTypes.insert(vActionTypes.end(), item.GetActionTypes().begin(), item.GetActionTypes().end());
    }
    return vActionTypes;
}

void FillItemStatChangeLists(const TreeIndexList& vItemDataList,
    TreeIndexList& vPassives,
    TreeIndexList& vActives,
    TreeIndexList& vActionables)
{
    // Use a set to make sure that we do not include duplicates
    STDUnorderedSet<IndexedString, IndexedStringHasher> tAlreadyUsed;

    // Split them into separate lists
    for(const TreeIndex& index : vItemDataList)
    {
        IndexedString sIndexKey = index.GetTreeBranchLeafType();
        Bool bIsActionable = IsItemActionable(index);
        Bool bIsAlreadyUsed = (tAlreadyUsed.count(sIndexKey) == 1);
        if(bIsActionable && !bIsAlreadyUsed)
        {
            vActionables.push_back(index);
            tAlreadyUsed.insert(sIndexKey);
        }
        else if(!bIsActionable && !bIsAlreadyUsed)
        {
            for(const StatChange& statChange : GetStatChangesFromItemTreeIndex(index))
            {
                if(statChange.IsPassive())
                {
                    vPassives.push_back(index);
                    tAlreadyUsed.insert(sIndexKey);
                    break;
                }
                else if(statChange.IsActive())
                {
                    vActives.push_back(index);
                    tAlreadyUsed.insert(sIndexKey);
                    break;
                }
            }
        }
    }
}

};
