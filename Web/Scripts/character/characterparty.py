# Fyleria Engine
# Copyright © 2018 Go Go Gecko Productions

# Imports
import os, sys, json
import GeckoUtility
import GeckoCharacterParty
from GeckoModule import StoreRunResult

# Get managers
g_PartyManager = GeckoCharacterParty.GetCharacterPartyManager()

## CharacterParty
class CharacterParty:

    ## Constructors
    def __init__(self, sPartyID, sPartyJson):
        if sPartyID != None:
            self.LoadFromID(sPartyID)
        elif sParyJson != None:
            self.LoadFromJson(sPartyJson)

    ## Load from ID
    def LoadFromID(self, sPartyID):
        self.partyObj = g_PartyManager.GetPartyByID(sPartyID)

    ## Load from Json
    def LoadFromJson(self, sPartyJson):
        self.partyObj = GeckoCharacterParty.GetCharacterPartyFromJsonString(sPartyJson)

    ## Regenerate character data
    def RegenerateCharacterData(self):
        self.partyObj.RegenerateCharacterData()

    ## Determine if party is full
    def IsPartyFull(self):
        result = self.partyObj.IsPartyFull()
        StoreRunResult(json.dumps(result))

    ## Determine if member is present
    def IsMemberPresent(self, sCharacterID):
        result = self.partyObj.IsMemberPresent()
        StoreRunResult(json.dumps(result))

    ## Determine if target type is available
    def IsTargetTypeAvailable(self, sCharacterTargetType):
        result = self.partyObj.IsTargetTypeAvailable()
        StoreRunResult(json.dumps(result))

    ## Determine if target type is taken
    def IsTargetTypeTaken(self, sCharacterTargetType):
        result = self.partyObj.IsTargetTypeTaken()
        StoreRunResult(json.dumps(result))

    ## Add member
    def AddMember(self, sCharacterID):
        result = self.partyObj.AddMember()
        StoreRunResult(json.dumps(result))

    ## Remove member
    def RemoveMember(self, sCharacterID):
        result = self.partyObj.RemoveMember()
        StoreRunResult(json.dumps(result))

    ## Move/swap members
    def MoveMember(self, sCharacterID, sCharacterTargetType):
        result = self.partyObj.MoveMember()
        StoreRunResult(json.dumps(result))

    def SwapMembers(self, sFirstCharacterID, sSecondCharacterID):
        result = self.partyObj.SwapMembers()
        StoreRunResult(json.dumps(result))

    ## Get next available target type
    def GetNextAvailableTargetType(self):
        result = self.partyObj.GetNextAvailableTargetType()
        StoreRunResult(json.dumps(result))

    ## Use target type
    def UseTargetType(self, sCharacterTargetType):
        result = self.partyObj.UseTargetType()
        StoreRunResult(json.dumps(result))

    ## Free target type
    def FreeTargetType(self, sCharacterTargetType):
        result = self.partyObj.FreeTargetType()
        StoreRunResult(json.dumps(result))

    ## Get member index by ID
    def GetMemberIndexByID(self, sCharacterID):
        result = self.partyObj.GetMemberIndexByID()
        StoreRunResult(json.dumps(result))

    ## Get member index by target type
    def GetMemberIndexByTargetType(self, sCharacterTargetType):
        result = self.partyObj.GetMemberIndexByTargetType()
        StoreRunResult(json.dumps(result))

    ## Get member string
    def GetMember(self, uIndex):
        result = self.partyObj.GetMember()
        StoreRunResult(json.dumps(result))

    ## Get character IDs
    def GetCharacterIDsFromTargetType(self, sCharacterTargetType):
        vCharacterIDs = GeckoUtility.IndexedStringList()
        result = self.partyObj.GetCharacterIDsFromTargetType(sCharacterTargetType, vCharacterIDs)
        StoreRunResult(json.dumps(vCharacterIDs))

    ## Check member status
    def GetStatusMemberCount(self, sStatus):
        result = self.partyObj.GetStatusMemberCount()
        StoreRunResult(json.dumps(result))

    ## Add random items
    def AddRandomItems(self, svTreeTypes, iNumRandomItems, iAmountStart, iAmountEnd):
        vTreeTypes = GetTreeIndexListFromJsonString(svTreeTypes)
        result = self.partyObj.AddRandomItems(vTreeTypes, iNumRandomItems, iAmountStart, iAmountEnd)
        StoreRunResult(json.dumps(result))

    ## Add item by leaf
    def AddItemByLeaf(self, sLeaf, uAmount):
        result = self.partyObj.AddItemByLeaf()
        StoreRunResult(json.dumps(result))

    ## Add item by index
    def AddItemByIndex(self, sTreeIndex, uAmount):
        treeIndexObj = GeckoUtility.TreeIndex()
        treeIndexObj.FromJsonString(sTreeIndex)
        result = self.partyObj.AddItemByIndex(treeIndexObj, uAmount)
        StoreRunResult(json.dumps(result))

    ## Remove item
    def RemoveItem(self, const TreeIndex& index, uAmount):
        result = self.partyObj.RemoveItem()
        StoreRunResult(json.dumps(result))

    ## Get item index by tree index
    def GetItemIndexByTreeIndex(self, const TreeIndex& index):
        result = self.partyObj.GetItemIndexByTreeIndex()
        StoreRunResult(json.dumps(result))

    ## Get item object
    def GetItem(self, uIndex):
        result = self.partyObj.GetItem(uIndex)
        StoreRunResult(result.ToJsonString())

    ## Get best unequipped item for the given slot
    def GetBestUnequippedItemIndex(self, uCharacterIndex, sSlot):
        result = self.partyObj.GetBestUnequippedItemIndex(uCharacterIndex, sSlot)
        StoreRunResult(json.dumps(result))

    ## Equip item
    def EquipItem(self, uCharacterIndex, uItemIndex, sSlot):
        result = self.partyObj.EquipItem(uCharacterIndex, uItemIndex, sSlot)
        StoreRunResult(json.dumps(result))

    ## Unequip item
    def UnequipItem(self, uCharacterIndex, uItemIndex, sSlot):
        result = self.partyObj.UnequipItem(uCharacterIndex, uItemIndex, sSlot)
        StoreRunResult(json.dumps(result))

    ## Equip best items
    def EquipBestItems(self, uCharacterIndex):
        result = self.partyObj.EquipBestItems(uCharacterIndex)
        StoreRunResult(json.dumps(result))

    ## Equip best items for all members
    def EquipBestItemsForAllMembers(self):
        result = self.partyObj.EquipBestItemsForAllMembers()
        StoreRunResult(json.dumps(result))

    ## Unequip all items
    def UnequipAllItems(self, uCharacterIndex):
        result = self.partyObj.UnequipAllItems(uCharacterIndex)
        StoreRunResult(json.dumps(result))

    ## Unequip all items from all members
    def UnequipAllItemsForAllMembers(self):
        result = self.partyObj.UnequipAllItemsForAllMembers()
        StoreRunResult(json.dumps(result))

    ## Get member count
    def GetMemberCount(self):
        result = self.partyObj.GetMemberCount()
        StoreRunResult(json.dumps(result))

    ## Get item count
    def GetItemCount(self):
        result = self.partyObj.GetItemCount()
        StoreRunResult(json.dumps(result))

    ## Get description
    def GetDescription(self):
        result = self.partyObj.GetDescription()
        StoreRunResult(json.dumps(result))

    ## Reset playtime
    def ResetPlayTime(self):
        self.partyObj.ResetPlayTime()

    ## Pause playtime
    def PausePlayTime(self):
        self.partyObj.PausePlayTime()

    ## Resume playtime
    def ResumePlayTime(self):
        self.partyObj.ResumePlayTime()

    ## Get playtime
    def GetPlayTime(self):
        result = self.partyObj.GetPlayTime()
        StoreRunResult(json.dumps(result))

    ## Set playtime
    def SetPlayTime(self, uTime):
        self.partyObj.SetPlayTime(uTime)

## CharacterPartyItem
class CharacterPartyItem:

    ## Constructors
    def __init__(self, sPartyItemJson):
        LoadFromJson(sPartyItemJson)

    ## Load from Json
    def LoadFromJson(self, sPartyItemJson):
        self.partyItemObj = GeckoCharacterParty.GetCharacterPartyItemFromJsonString(sPartyItemJson)

    ## Does the type match the given slot?
    def DoesMatchSlot(sSlot):
        result = self.partyItemObj.DoesMatchSlot(sSlot)
        StoreRunResult(json.dumps(result))

    ## Can amount be added
    def CanAddAmount(uAmount):
        result = self.partyItemObj.CanAddAmount(uAmount)
        StoreRunResult(json.dumps(result))

    ## Can amount be removed
    def CanRemoveAmount(uAmount):
        result = self.partyItemObj.CanRemoveAmount(uAmount)
        StoreRunResult(json.dumps(result))

    ## Can amount be equipped?
    def CanEquipAmount(uAmount):
        result = self.partyItemObj.CanEquipAmount(uAmount)
        StoreRunResult(json.dumps(result))

    ## Can amount be unequipped?
    def CanUnequipAmount(uAmount):
        result = self.partyItemObj.CanUnequipAmount(uAmount)
        StoreRunResult(json.dumps(result))

    ## Add amount
    def AddAmount(uAmount):
        result = self.partyItemObj.AddAmount(uAmount)
        StoreRunResult(json.dumps(result))

    ## Remove amount
    def RemoveAmount(uAmount):
        result = self.partyItemObj.RemoveAmount(uAmount)
        StoreRunResult(json.dumps(result))

    ## Equip amount
    def EquipAmount(uAmount):
        result = self.partyItemObj.EquipAmount(uAmount)
        StoreRunResult(json.dumps(result))

    ## Unequip amount
    def UnequipAmount(uAmount):
        result = self.partyItemObj.UnequipAmount(uAmount)
        StoreRunResult(json.dumps(result))
