// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#ifndef _GECKO_ITEM_TREE_H_
#define _GECKO_ITEM_TREE_H_

#include "Character/CharacterAction.h"
#include "Items/ItemDataArmor.h"
#include "Items/ItemDataIngredient.h"
#include "Items/ItemDataPotion.h"
#include "Items/ItemDataWeapon.h"
#include "Utility/Tree.h"

namespace Gecko
{

// Typedefs
typedef Tree<ItemDataArmor> ItemTreeArmor;
typedef Tree<ItemDataIngredient> ItemTreeIngredient;
typedef Tree<ItemDataPotion> ItemTreePotion;
typedef Tree<ItemDataWeapon> ItemTreeWeapon;

// Load/unload item trees into memory
void LoadItemTreesIntoMemory();
void UnloadItemTreesFromMemory();

// Verify
void VerifyItemTrees();

// Retrieve appropriate item data
Bool DoesItemDataExist(const TreeIndex& index);
Bool DoesItemDataArmorExist(const TreeIndex& index);
Bool DoesItemDataIngredientExist(const TreeIndex& index);
Bool DoesItemDataPotionExist(const TreeIndex& index);
Bool DoesItemDataWeaponExist(const TreeIndex& index);
const ItemDataArmor& RetrieveItemDataArmor(const TreeIndex& index);
const ItemDataIngredient& RetrieveItemDataIngredient(const TreeIndex& index);
const ItemDataPotion& RetrieveItemDataPotion(const TreeIndex& index);
const ItemDataWeapon& RetrieveItemDataWeapon(const TreeIndex& index);
IndexedString RetrieveItemType(const TreeIndex& index);

// Get item lists
TreeIndexList GetAllArmorItems();
TreeIndexList GetAllIngredientItems();
TreeIndexList GetAllPotionItems();
TreeIndexList GetAllWeaponItems();
TreeIndexList GetAllEquippedItems(const IndexedString& sCharID);

// Resolve leaf into index
TreeIndex ResolveItemLeafIntoIndex(const IndexedString& sLeaf);

// Determine if item is actionable
Bool IsItemActionable(const TreeIndex& index);

// Generate character actions
Bool GenerateItemCharacterActions(const TreeIndex& index,
    const IndexedString& sCharacterID,
    const IndexedString& sWeaponSet,
    CharacterActionSharedPtrList& vActions);

// Check "better" quality
Bool IsArmorBetter(const TreeIndex& index1, const TreeIndex& index2);
Bool IsWeaponBetter(const TreeIndex& index1, const TreeIndex& index2);

// Check item type
Bool IsItemWeapon(const TreeIndex& index);
Bool IsItemShield(const TreeIndex& index);

// Get action types
IndexedStringList GetActionTypes(const TreeIndex& index);

// Get stat changes
void FillItemStatChangeLists(const TreeIndexList& vItemDataList,
    TreeIndexList& vPassives,
    TreeIndexList& vActives,
    TreeIndexList& vActionables);

};

#endif
