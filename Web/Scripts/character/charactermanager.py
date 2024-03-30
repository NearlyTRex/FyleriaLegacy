# Fyleria Engine
# Copyright © 2018 Go Go Gecko Productions

# Imports
import os, sys, json
import GeckoUtility
import GeckoCharacter
from GeckoModule import StoreRunResult

# Get managers
g_CharacterManager = GeckoCharacter.GetCharacterManager()

#################################################################################################
def LoadCharacterFromJson(sCharacterID, sCharacterJson):
    g_CharacterManager.LoadCharacter(sCharacterID, GeckoCharacter.GetCharacterFromJsonString(sCharacterJson))
#################################################################################################
def LoadCharacterFromFile(sCharacterID, sCharacterFile):
    charObj = GeckoCharacter.Character()
    charObj.FromFile(sCharacterFile)
    g_CharacterManager.LoadCharacter(sCharacterID, charObj)
#################################################################################################
def SaveCharacterToFile(sCharacterID, sCharacterFile):
    charObj = g_CharacterManager.GetCharacter(sCharacterID)
    charObj.ToFile(sCharacterFile)
#################################################################################################
def CreateCharacter(sCharacterID):
    g_CharacterManager.CreateCharacter(sCharacterID)
#################################################################################################
def UnloadCharacter(sCharacterID):
    g_CharacterManager.UnloadCharacter(sCharacterID)
#################################################################################################
def DoesCharacterExist(sCharacterID):
    result = g_CharacterManager.DoesCharacterExist(sCharacterID)
    StoreRunResult(json.dumps(result))
#################################################################################################
def GenerateCharacter(sCharacterID, sCharacterGeneratorJson):
    g_CharacterManager.GenerateCharacter(sCharacterID, GeckoCharacter.GetCharacterGeneratorFromJsonString(sCharacterGeneratorJson))
#################################################################################################
def GetCharacter(sCharacterID):
    result = g_CharacterManager.GetCharacter(sCharacterID)
    StoreRunResult(GeckoCharacter.ConvertCharacterToJsonString(result))
#################################################################################################
def ApplyStatChange(sSegment, sStatChangeJson, bApplyAllEntries):
    bAllChangesApplied = False
    bAtLeastOneChange = False
    g_CharacterManager.ApplyStatChange(sSegment, GeckoCharacter.GetStatChangeFromJsonString(sStatChangeJson), bAllChangesApplied, bAtLeastOneChange, bApplyAllEntries)
    result = [bAllChangesApplied, bAtLeastOneChange]
    StoreRunResult(json.dumps(result))
#################################################################################################
def ApplyStatChangeEntry(sSegment, sStatChangeEntryJson):
    result = g_CharacterManager.ApplyStatChangeEntry(sSegment, GeckoCharacter.GetStatChangeEntryFromJsonString(sStatChangeEntryJson))
    StoreRunResult(json.dumps(result))
#################################################################################################
def ApplyStatChangeEntryOperation(sSegment, sCharacterID, sOperation, sStat, fValue):
    result = g_CharacterManager.ApplyStatChangeEntryOperation(sSegment, sCharacterID, sOperation, sStat, fValue)
    StoreRunResult(json.dumps(result))
#################################################################################################
def ApplyStatChangeEntryOperation(sSegment, sCharacterID, sOperation, sStat, iValue):
    result = g_CharacterManager.ApplyStatChangeEntryOperation(sSegment, sCharacterID, sOperation, sStat, iValue)
    StoreRunResult(json.dumps(result))
#################################################################################################
def ApplyStatChangeEntryOperation(sSegment, sCharacterID, sOperation, sStat, bValue):
    result = g_CharacterManager.ApplyStatChangeEntryOperation(sSegment, sCharacterID, sOperation, sStat, bValue)
    StoreRunResult(json.dumps(result))
#################################################################################################
def ApplyStatChangeEntryOperation(sSegment, sCharacterID, sOperation, sStat, sValue):
    result = g_CharacterManager.ApplyStatChangeEntryOperation(sSegment, sCharacterID, sOperation, sStat, sValue)
    StoreRunResult(json.dumps(result))
#################################################################################################
def ApplyStatChangeEntryOperation(sSegment, sCharacterID, sOperation, sStat, svValuesJson):
    result = g_CharacterManager.ApplyStatChangeEntryOperation(sSegment, sCharacterID, sOperation, sStat, json.loads(svValuesJson))
    StoreRunResult(json.dumps(result))
#################################################################################################
def DoesStatChangeEntryUseDelta(sStatChangeEntryJson):
    result = g_CharacterManager.DoesStatChangeEntryUseDelta(GeckoCharacter.GetStatChangeEntryFromJsonString(sStatChangeEntryJson))
    StoreRunResult(json.dumps(result))
#################################################################################################
def IsStatFloat(sStat):
    result = g_CharacterManager.IsStatFloat(sStat)
    StoreRunResult(json.dumps(result))
#################################################################################################
def IsStatInt(sStat):
    result = g_CharacterManager.IsStatInt(sStat)
    StoreRunResult(json.dumps(result))
#################################################################################################
def IsStatBool(sStat):
    result = g_CharacterManager.IsStatBool(sStat)
    StoreRunResult(json.dumps(result))
#################################################################################################
def IsStatString(sStat):
    result = g_CharacterManager.IsStatString(sStat)
    StoreRunResult(json.dumps(result))
#################################################################################################
def IsStatStringList(sStat):
    result = g_CharacterManager.IsStatStringList(sStat)
    StoreRunResult(json.dumps(result))
#################################################################################################
def GetSourceStatChangeEntryValues(sSegment, sCharacterID, sStat, sStatChangeEntryJson):
    vFloatValues = []
    vIntValues = []
    vBoolValues = []
    vStringValues = []
    g_CharacterManager.GetSourceStatChangeEntryValues(
        sSegment, sCharacterID, sStat,
        GeckoCharacter.GetStatChangeEntryFromJsonString(sStatChangeEntryJson),
        vFloatValues, vIntValues, vBoolValues, vStringValues)
    result = [vFloatValues, vIntValues, vBoolValues, vStringValues]
    StoreRunResult(json.dumps(result))
#################################################################################################
def GetDestStatChangeEntryValues(sSegment, sCharacterID, sStat, sStatChangeEntryJson):
    vFloatValues = []
    vIntValues = []
    vBoolValues = []
    vStringValues = []
    g_CharacterManager.GetDestStatChangeEntryValues(
        sSegment, sCharacterID, sStat,
        GeckoCharacter.GetStatChangeEntryFromJsonString(sStatChangeEntryJson),
        vFloatValues, vIntValues, vBoolValues, vStringValues)
    result = [vFloatValues, vIntValues, vBoolValues, vStringValues]
    StoreRunResult(json.dumps(result))
#################################################################################################
