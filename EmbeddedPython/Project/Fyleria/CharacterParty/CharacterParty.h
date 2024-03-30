// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

#ifndef _GECKO_CHARACTER_PARTY_H_
#define _GECKO_CHARACTER_PARTY_H_

// Internal includes
#include "Character/Character.h"
#include "CharacterParty/CharacterPartyMember.h"
#include "CharacterParty/CharacterPartyItem.h"
#include "Utility/ResultManager.h"

namespace Gecko
{

class CharacterParty
{
public:

    // Types
    typedef STDUnorderedMap<String, CharacterPartyMember> CharacterPartyMemberMapType;
    typedef STDUnorderedMap<String, CharacterPartyItem> CharacterPartyItemMapType;

    // Constructors
    CharacterParty();
    CharacterParty(const Json& jsonData);
    CharacterParty(const String& jsonString);

    // Regenerate character data
    void RegenerateCharacterData(
        Bool bUpdateEquipmentRatings = true,
        Bool bUpdateAvailableChanges = true,
        Bool bUpdateAvailableActions = true,
        Bool bUpdateAvailableAP = true
    );

    // Determine if party is able to fight
    Bool IsPartyAbleToFight() const;
    MAKE_MODULE_RESULT_VARIANT(IsPartyAbleToFight);

    // Determine if party is full
    Bool IsPartyFull() const;
    MAKE_MODULE_RESULT_VARIANT(IsPartyFull);

    // Determine if member is present
    Bool IsMemberPresent(const String& sCharacterID) const;
    MAKE_MODULE_RESULT_VARIANT_A1(IsMemberPresent, const String&);

    // Determine if target type is available
    Bool IsTargetTypeAvailable(const String& sCharacterTargetType) const;
    MAKE_MODULE_RESULT_VARIANT_A1(IsTargetTypeAvailable, const String&);

    // Determine if target type is taken
    Bool IsTargetTypeTaken(const String& sCharacterTargetType) const;
    MAKE_MODULE_RESULT_VARIANT_A1(IsTargetTypeTaken, const String&);

    // Add member
    Bool AddMember(const String& sCharacterID);
    MAKE_MODULE_RESULT_VARIANT_A1(AddMember, const String&);

    // Remove member
    Bool RemoveMember(const String& sCharacterID);
    MAKE_MODULE_RESULT_VARIANT_A1(RemoveMember, const String&);

    // Move member to the given target type
    Bool MoveMember(const String& sCharacterID, const String& sCharacterTargetType);
    MAKE_MODULE_RESULT_VARIANT_A2(MoveMember, const String&, const String&);

    // Swap target types between members
    Bool SwapMembers(const String& sFirstCharacterID, const String& sSecondCharacterID);
    MAKE_MODULE_RESULT_VARIANT_A2(SwapMembers, const String&, const String&);

    // Get next available target type
    String GetNextAvailableTargetType() const;
    MAKE_MODULE_RESULT_VARIANT(GetNextAvailableTargetType);

    // Use target types
    Bool UseTargetType(const String& sCharacterTargetType);
    MAKE_MODULE_RESULT_VARIANT_A1(UseTargetType, const String&);

    // Free target type
    Bool FreeTargetType(const String& sCharacterTargetType);
    MAKE_MODULE_RESULT_VARIANT_A1(FreeTargetType, const String&);

    // Get member by ID
    const CharacterPartyMember& GetMemberByID(const String& sCharacterID) const;
    CharacterPartyMember& GetMemberByID(const String& sCharacterID);
    MAKE_MODULE_RESULT_VARIANT_A1(GetMemberByID, const String&);

    // Get member by target type
    const CharacterPartyMember& GetMemberByTargetType(const String& sCharacterTargetType) const;
    CharacterPartyMember& GetMemberByTargetType(const String& sCharacterTargetType);
    MAKE_MODULE_RESULT_VARIANT_A1(GetMemberByTargetType, const String&);

    // Get member character IDs
    StringArray GetMemberCharacterIDs() const;
    MAKE_MODULE_RESULT_VARIANT(GetMemberCharacterIDs);

    // Get character IDs from target type
    Bool GetCharacterIDsFromTargetType(const String& sCharacterTargetType, StringArray& vCharacterIDs) const;
    MAKE_MODULE_RESULT_VARIANT_A2(GetCharacterIDsFromTargetType, const String&, StringArray&);

    // Check member status
    UInt GetStatusMemberCount(const String& sStatus) const;
    MAKE_MODULE_RESULT_VARIANT_A1(GetStatusMemberCount, const String&);

    // Add random items
    Bool AddRandomItems(const StringArray& vTreeTypes, Int iNumRandomItems, Int iAmountStart, Int iAmountEnd);
    MAKE_MODULE_RESULT_VARIANT_A4(AddRandomItems, const StringArray&, Int, Int, Int);

    // Add item by leaf
    Bool AddItemByLeaf(const String& sLeaf, UInt uAmount);
    MAKE_MODULE_RESULT_VARIANT_A2(AddItemByLeaf, const String&, UInt);

    // Add item by tree index
    Bool AddItemByTreeIndex(const TreeIndex& treeIndex, UInt uAmount);
    MAKE_MODULE_RESULT_VARIANT_A2(AddItemByTreeIndex, const TreeIndex&, UInt);

    // Remove item by leaf
    Bool RemoveItemByLeaf(const String& sLeaf, UInt uAmount);
    MAKE_MODULE_RESULT_VARIANT_A2(RemoveItemByLeaf, const String&, UInt);

    // Remove item by tree index
    Bool RemoveItemByTreeIndex(const TreeIndex& treeIndex, UInt uAmount);
    MAKE_MODULE_RESULT_VARIANT_A2(RemoveItemByTreeIndex, const TreeIndex&, UInt);

    // Get item by leaf
    const CharacterPartyItem& GetItemByLeaf(const String& sLeaf) const;
    CharacterPartyItem& GetItemByLeaf(const String& sLeaf);
    MAKE_MODULE_RESULT_VARIANT_A1(GetItemByLeaf, const String&);

    // Get item by tree index
    const CharacterPartyItem& GetItemByTreeIndex(const TreeIndex& treeIndex) const;
    CharacterPartyItem& GetItemByTreeIndex(const TreeIndex& treeIndex);
    MAKE_MODULE_RESULT_VARIANT_A1(GetItemByTreeIndex, const TreeIndex&);

    // Get best unequipped item for the given slot
    TreeIndex GetBestUnequippedItem(const String& sCharacterID, const String& sSlot) const;
    MAKE_MODULE_RESULT_VARIANT_A2(GetBestUnequippedItem, const String&, const String&);

    // Equip item
    Bool EquipItem(const String& sCharacterID, const String& sLeaf, const String& sSlot);
    MAKE_MODULE_RESULT_VARIANT_A3(EquipItem, const String&, const String&, const String&);

    // Unequip item
    Bool UnequipItem(const String& sCharacterID, const String& sLeaf, const String& sSlot);
    MAKE_MODULE_RESULT_VARIANT_A3(UnequipItem, const String&, const String&, const String&);

    // Equip best items for the given member
    Bool EquipBestItems(const String& sCharacterID);
    MAKE_MODULE_RESULT_VARIANT_A1(EquipBestItems, const String&);

    // Equip best items for all members
    Bool EquipBestItemsForAllMembers();
    MAKE_MODULE_RESULT_VARIANT(EquipBestItemsForAllMembers);

    // Unequip all items for the given member
    Bool UnequipAllItems(const String& sCharacterID);
    MAKE_MODULE_RESULT_VARIANT_A1(UnequipAllItems, const String&);

    // Unequip all items for all members
    Bool UnequipAllItemsForAllMembers();
    MAKE_MODULE_RESULT_VARIANT(UnequipAllItemsForAllMembers);

    // Get member count
    UInt GetMemberCount() const;
    MAKE_MODULE_RESULT_VARIANT(GetMemberCount);

    // Get item count
    UInt GetItemCount() const;
    MAKE_MODULE_RESULT_VARIANT(GetItemCount);

    // Get description
    String GetDescription() const;
    MAKE_MODULE_RESULT_VARIANT(GetDescription);

    // Reset play time
    void ResetPlayTime();

    // Pause play time
    void PausePlayTime();

    // Resume play time
    void ResumePlayTime();

    // Get play time
    ULongLong GetPlayTime() const;
    MAKE_MODULE_RESULT_VARIANT(GetPlayTime);

    // Set play time
    void SetPlayTime(ULongLong uTime);

    // Party ID
    MAKE_RAW_TYPE_ACCESSORS(PartyID, String);

    // Party type
    MAKE_RAW_TYPE_ACCESSORS(PartyType, String);

    // Map of members
    MAKE_RAW_TYPE_ACCESSORS(Members, CharacterPartyMemberMapType);

    // Map of items
    MAKE_RAW_TYPE_ACCESSORS(Items, CharacterPartyItemMapType);

    // Arrays of available target types
    MAKE_RAW_TYPE_ACCESSORS(AvailableTargetTypes, StringArray);

    // Array of taken target types
    MAKE_RAW_TYPE_ACCESSORS(TakenTargetTypes, StringArray);

    // Paused playtime
    MAKE_RAW_TYPE_ACCESSORS(PlayTimePaused, Bool);

    // Current playtime
    MAKE_RAW_TYPE_ACCESSORS(CurrentPlayTime, ULongLong);

    // Last time point
    MAKE_RAW_TYPE_ACCESSORS(LastTimePoint, STDTimePoint);
};

// Typedef
MAKE_COMMON_TYPEDEFS(CharacterParty);

// JSON Converters
void to_json(Json& jsonData, const CharacterParty& obj);
void from_json(const Json& jsonData, CharacterParty& obj);

};

#endif
