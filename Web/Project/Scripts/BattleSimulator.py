# Fyleria Engine
# Copyright © 2017 Go Go Gecko Productions

# Battle Test
# This is a simplified test of the battle mechanics.
# In the real game, there will be a give/take across the DLL boundary to the
# Unity part of the game engine. Here we will simulate some of that via user
# inputs and text based displays.

# Imports
from Utility import *
from Battle import *
from Config import *
from Character import *
from CharacterAction import *
from CharacterData import *
from CharacterParty import *
from Saves import *

# Get managers
g_BattleManager = GetBattleManager()
g_CharacterManager = GetCharacterManager()
g_CharacterPartyManager = GetCharacterPartyManager()
g_ConfigManager = GetConfigManager()
g_SaveManager = GetSaveManager()

# Print header
print("\n##### Battle Simulator (Version 1.0) #####\n")

#################################################################################################
## Yes/No Prompt
def GetYesNoInput(prompt, default_value = "n"):

    # Valid inputs
    m_ValidYes = ["y", "yes"]
    m_ValidNo = ["n", "no"]

    # Get raw input and parse it
    m_sPrompt = "%s (y/n) (default is %s): " % (prompt, str(default_value))
    m_RawInput = input(m_sPrompt).lower()
    if not m_RawInput:
        return default_value
    elif m_RawInput in m_ValidYes:
        return m_ValidYes[0]
    elif m_RawInput in m_ValidNo:
        return m_ValidNo[0]
    else:
        return default_value
#################################################################################################
## Value Prompt
def GetValueInput(prompt, default_value, type_name):

    # Get raw input and parse it
    m_sPrompt = "%s (default is %s): " % (prompt, str(default_value))
    m_RawInput = input(m_sPrompt)
    if m_RawInput == "":
        return default_value
    else:
        return type_name(m_RawInput)
#################################################################################################
## Push save into memory
def PushSaveIntoMemory():

    # Get save details
    m_uSaveSlot = GetValueInput("Enter the save slot to push to memory", 0, int)

    # Push the given slot into memory
    g_SaveManager.PushSaveIntoMemory(m_uSaveSlot)
#################################################################################################
## Pull save from memory
def PullSaveFromMemory():

    # Get save details
    m_uSaveSlot = GetValueInput("Enter the save slot to pull from memory", 0, int)
    m_sPartyID = GetValueInput("Enter the Party ID to pull into a save", "PartyID", str)

    # Pull save info from memory
    g_SaveManager.PullSaveFromMemory(m_uSaveSlot, m_sPartyID)
#################################################################################################
## Read save data
def LoadAllSavesFromDirectory():

    # Get save details
    m_sSaveDirectory = GetValueInput("Enter the save directory", "Saves", str)
    m_sSaveBaseName = GetValueInput("Enter the save file basename", "Save_", str)
    m_sSaveExt = GetValueInput("Enter the save file extension", ".json", str)
    m_sSaveType = GetValueInput("Enter the save type", "TextJson", str)

    # Load all saves from the given directory
    g_SaveManager.LoadAllFromDirectory(m_sSaveDirectory, m_sSaveBaseName, m_sSaveExt, m_sSaveType)
#################################################################################################
## Write save data
def SaveAllSavesToDirectory():

    # Get save details
    m_sSaveDirectory = GetValueInput("Enter the save directory", "Saves", str)
    m_sSaveBaseName = GetValueInput("Enter the save file basename", "Save_", str)
    m_sSaveExt = GetValueInput("Enter the save file extension", ".json", str)
    m_sSaveType = GetValueInput("Enter the save type", "TextJson", str)

    # Write all saves to the given directory
    g_SaveManager.SaveAllToDirectory(m_sSaveDirectory, m_sSaveBaseName, m_sSaveExt, m_sSaveType)
#################################################################################################
## Create party
def CreateParty():

    # Create party
    m_sPartyID = GetValueInput("Enter ID for new party", "PartyID", str)
    m_sPartyType = GetValueInput("Enter type for new party", "Ally", str)
    m_bSetAsCurrent = GetYesNoInput("Would you like to set this as the current party for the type you selected?") == "y"
    g_CharacterPartyManager.CreateParty(m_sPartyID, m_sPartyType, m_bSetAsCurrent)
    m_NewParty = g_CharacterPartyManager.GetPartyByID(m_sPartyID)

    # Add members to this party
    if GetYesNoInput("Would you like to add members to this party?") == "y":
        m_NewParty.AddMember(GetValueInput("Enter ID for character to add", "CharacterID", str))
        while not m_NewParty.IsPartyFull() and GetYesNoInput("Would you like to continue to add members to this party?") == "y":
            m_NewParty.AddMember(GetValueInput("Enter ID for character to add", "CharacterID", str))

    # View party items
    if GetYesNoInput("Would you like to view the members in the party?") == "y":
        for i in range(0, len(m_NewParty.Members)):
            member = m_NewParty.Members[i]
            memberObj = g_CharacterManager.GetCharacter(member)
            memberCharID = member.Get()
            memberFirstName = memberObj.FirstName.Get()
            memberLastName = memberObj.LastName.Get()
            memberTargetType = memberObj.CharacterTargetType.Get()
            print("%d) CharID = %s, FirstName = %s, LastName = %s, TargetType = %s" % (i, memberCharID, memberFirstName, memberLastName, memberTargetType))

    # Add specific items to this party
    if GetYesNoInput("Would you like to add some specific items to this party?") == "y":
        m_sLeaf = GetValueInput("Enter item leaf name", "", str)
        m_uAmount = GetValueInput("Enter item amount", 0, int)
        m_NewParty.AddItemByLeaf(m_sLeaf, m_uAmount)
        while GetYesNoInput("Would you like to continue to add some specific items to this party?") == "y":
            m_sLeaf = GetValueInput("Enter item leaf name", "", str)
            m_uAmount = GetValueInput("Enter item amount", 0, int)
            m_NewParty.AddItemByLeaf(m_sLeaf, m_uAmount)

    # Add random items to this party
    if GetYesNoInput("Would you like to add some random items to this party?") == "y":
        m_vTreeTypes = IndexedStringList([])
        m_vTreeTypes.append(GetValueInput("Enter a tree type for random items", "Weapon", str))
        while GetYesNoInput("Would you like to add more tree types for random items?") == "y":
            m_vTreeTypes.append(GetValueInput("Enter a tree type for random items", "Armor", str))
        m_uNumRandomItems = GetValueInput("Enter the number of random items per tree type", 1, int)
        m_uAmountStart = GetValueInput("Enter lower boundary for random amount of each item", 1, int)
        m_uAmountEnd = GetValueInput("Enter higher boundary for random amount of each item", 1, int)
        m_NewParty.AddRandomItems(m_vTreeTypes, m_uNumRandomItems, m_uAmountStart, m_uAmountEnd)

    # View party items
    if GetYesNoInput("Would you like to view the items in the party?") == "y":
        for i in range(0, len(m_NewParty.Items)):
            item = m_NewParty.Items[i]
            itemName = item.TreeIndex.Leaf.Get()
            itemAmount = item.Amount
            itemEquipCount = item.EquipCount
            itemSlots = ConvertIndexedStringVector(item.ApplicableEquipmentSlots).Get()
            print("%d) Name = %s, Amount = %d, EquipCount = %d, Slots = %s" % (i, itemName, itemAmount, itemEquipCount, itemSlots))

    # Equip items for a member
    if GetYesNoInput("Would you like to equip items to members?") == "y":
        m_uCharacterIdx = GetValueInput("Enter character index", 0, int)
        m_uItemIdx = GetValueInput("Enter item index", 0, int)
        m_sEquipSlot = GetValueInput("Enter equipment slot", "Weapon1Left", str)
        print("Result: %d" % (m_NewParty.EquipItem(m_uCharacterIdx, m_uItemIdx, m_sEquipSlot)))
        while GetYesNoInput("Would you like to continue equipping items to members?") == "y":
            m_uCharacterIdx = GetValueInput("Enter character index", 0, int)
            m_uItemIdx = GetValueInput("Enter item index", 0, int)
            m_sEquipSlot = GetValueInput("Enter equipment slot", "Weapon1Left", str)
            print("Result: %d" % (m_NewParty.EquipItem(m_uCharacterIdx, m_uItemIdx, m_sEquipSlot)))

    # Equip the 'best' items for all members
    if GetYesNoInput("Would you like to equip the 'best' items for all members?") == "y":
        m_NewParty.EquipBestItemsForAllMembers()

    # Regenerate character data
    m_NewParty.RegenerateCharacterData()
#################################################################################################
## Create manual character
def CreateManualCharacter():

    # Create character
    m_sCharacterID = GetValueInput("Enter ID for new character", "CharacterID", str)
    g_CharacterManager.CreateCharacter(m_sCharacterID)
    m_NewCharacter = g_CharacterManager.GetCharacter(m_sCharacterID)
    m_NewCharacter.FirstName = GetValueInput("Enter FirstName", "FirstName", str)
    m_NewCharacter.LastName = GetValueInput("Enter LastName", "LastName", str)
    m_NewCharacter.Gender = GetValueInput("Enter Gender", "Female", str)
    m_NewCharacter.Eyes = GetValueInput("Enter Eyes", "Eyes1", str)
    m_NewCharacter.Hair = GetValueInput("Enter Hair", "Hair1", str)
    m_NewCharacter.Handedness = GetValueInput("Enter Handedness", "RightHanded", str)
    m_NewCharacter.BaseRace = GetValueInput("Enter BaseRace", "Human", str)
    m_NewCharacter.TransformedRace = GetValueInput("Enter TransformedRace", "None", str)
    m_NewCharacter.PowerSet = GetValueInput("Enter PowerSet", "Vampire", str)
    m_NewCharacter.Age = GetValueInput("Enter Age", 1, int)
    m_NewCharacter.SetAllSkillRankingValues(GetValueInput("Enter value for all ranks", 1, int))
    m_NewCharacter.SetAllSkillCurrentValues(GetValueInput("Enter value for all rank progress", 0, int))

    # Create progress data
    m_NewProgressData = CharacterProgressData()
    m_NewProgressData.BluntAttack = GetValueInput("Enter BluntAttack", 1, int)
    m_NewProgressData.BluntDefense = GetValueInput("Enter BluntDefense", 1, int)
    m_NewProgressData.PierceAttack = GetValueInput("Enter PierceAttack", 1, int)
    m_NewProgressData.PierceDefense = GetValueInput("Enter PierceDefense", 1, int)
    m_NewProgressData.SlashAttack = GetValueInput("Enter SlashAttack", 1, int)
    m_NewProgressData.SlashDefense = GetValueInput("Enter SlashDefense", 1, int)
    m_NewProgressData.MagicAttack = GetValueInput("Enter MagicAttack", 1, int)
    m_NewProgressData.MagicDefense = GetValueInput("Enter MagicDefense", 1, int)
    m_NewProgressData.EnergyAttack = GetValueInput("Enter EnergyAttack", 1, int)
    m_NewProgressData.EnergyDefense = GetValueInput("Enter EnergyDefense", 1, int)
    m_NewProgressData.HealthPointsCurrent = GetValueInput("Enter HealthPoints", 1, int)
    m_NewProgressData.MagicPointsCurrent = GetValueInput("Enter MagicPoints", 1, int)
    m_NewProgressData.EnergyPointsCurrent = GetValueInput("Enter EnergyPoints", 1, int)
    m_NewProgressData.HealthPointsMax = m_NewProgressData.HealthPointsCurrent
    m_NewProgressData.MagicPointsMax = m_NewProgressData.MagicPointsCurrent
    m_NewProgressData.EnergyPointsMax = m_NewProgressData.EnergyPointsCurrent
    m_NewProgressData.HealthRegen = GetValueInput("Enter HealthRegen", 1, int)
    m_NewProgressData.MagicRegen = GetValueInput("Enter MagicRegen", 1, int)
    m_NewProgressData.EnergyRegen = GetValueInput("Enter EnergyRegen", 1, int)
    m_NewProgressData.Speed = GetValueInput("Enter Speed", 1, int)

    # Set progress data
    m_NewCharacter.ProgressDataBase = m_NewProgressData

#################################################################################################
## Create random character
def CreateRandomCharacter():

    # Get generator details
    m_sDefaultGeneratorFile = g_ConfigManager.CharacterGeneratorRandomFile
    m_sGeneratorFile = GetValueInput("Enter filename for character generator", m_sDefaultGeneratorFile, str)
    m_sCharacterID = GetValueInput("Enter ID for new character", "CharacterID", str)

    # Load generator
    m_RandomCharGenerator = CharacterGenerator()
    m_RandomCharGenerator.FromFile(m_sGeneratorFile)

    # Generate character
    g_CharacterManager.GenerateCharacter(m_sCharacterID, m_RandomCharGenerator)
    m_NewCharacter = g_CharacterManager.GetCharacter(m_sCharacterID)
    m_NewCharacter.SetAllSkillRankingValues(GetValueInput("Enter value for all ranks", 1, int))
    m_NewCharacter.SetAllSkillCurrentValues(GetValueInput("Enter value for all rank progress", 0, int))
#################################################################################################

# Ask the player if they want to load save data
if GetYesNoInput("Would you like to load save data?") == "y":
    LoadAllSavesFromDirectory()
    PushSaveIntoMemory()
    while GetYesNoInput("Would you like to continue loading save data?") == "y":
        PushSaveIntoMemory()

# Ask the player if they want to create manual characters
if GetYesNoInput("Would you like to create some manual characters?") == "y":
    CreateManualCharacter()
    while GetYesNoInput("Would you like to continue creating manual characters?") == "y":
        CreateManualCharacter()

# Ask the player if they want to create random characters
if GetYesNoInput("Would you like to create some random characters?") == "y":
    CreateRandomCharacter()
    while GetYesNoInput("Would you like to continue creating random characters?") == "y":
        CreateRandomCharacter()

# Ask the player if they want to create some parties
if GetYesNoInput("Would you like to create some parties?") == "y":
    CreateParty()
    while GetYesNoInput("Would you like to continue creating parties?") == "y":
        CreateParty()

# Print footer
print("\n##### Battle Simulator Finish #####\n")
