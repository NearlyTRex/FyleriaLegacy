# Fyleria Engine
# Copyright © 2018 Go Go Gecko Productions

# Imports
import os, sys, json
import GeckoUtility
import GeckoSaves
from GeckoModule import StoreRunResult

# Get managers
g_SaveManager = GeckoSaves.GetSaveManager()

#################################################################################################
## Load save
def LoadSave(uSlot, sSaveJson):
    g_SaveManager.LoadSave(uSlot, GeckoSaves.GetSaveFromJsonString(sSaveJson))
#################################################################################################
## Create save
def CreateSave(uSlot):
    g_SaveManager.CreateSave(uSlot)
#################################################################################################
## Unload save
def UnloadSave(uSlot):
    g_SaveManager.UnloadSave(uSlot)
#################################################################################################
## Unload all saves
def UnloadAllSaves():
    g_SaveManager.UnloadAllSaves()
#################################################################################################
## Does save exist
def DoesSaveExist(uSlot):
    result = g_SaveManager.DoesSaveExist(uSlot)
    StoreRunResult(json.dumps(result))
#################################################################################################
## Get save capacity
def GetSaveCapacity():
    result = g_SaveManager.GetSaveCapacity()
    StoreRunResult(json.dumps(result))
#################################################################################################
## Get list of all available save slots
def GetAllAvailableSaveSlots():
    result = g_SaveManager.GetAllAvailableSaveSlots()
    StoreRunResult(json.dumps(result))
#################################################################################################
## Get list of all descriptions from save slots
def GetAllSaveDescriptions():
    result = g_SaveManager.GetAllSaveDescriptions()
    StoreRunResult(json.dumps(result))
#################################################################################################
## Is save capacity reached
def IsSaveCapacityReached():
    result = g_SaveManager.IsSaveCapacityReached()
    StoreRunResult(json.dumps(result))
#################################################################################################
## Get save
def GetSave(uSlot):
    result = g_SaveManager.GetSave(uSlot)
    StoreRunResult(GeckoSaves.ConvertSaveToJsonString(result))
#################################################################################################
## Get all saves
def GetAllSaves():
    result = g_SaveManager.GetAllSaves()
    StoreRunResult(GeckoSaves.ConvertSaveListToJsonString(result))
#################################################################################################
## Pull save from memory
def PullSaveFromMemory(uSlot, sPartyID):
    g_SaveManager.PullSaveFromMemory(uSlot, sPartyID)
#################################################################################################
## Push save into memory
def PushSaveIntoMemory(uSlot):
    g_SaveManager.PushSaveIntoMemory(uSlot)
#################################################################################################
## Save to file
def SaveToFile(uSlot, sFile, sType):
    g_SaveManager.SaveToFile(uSlot, sFile, sType)
#################################################################################################
## Load from file
def LoadFromFile(uSlot, sFile, sType):
    g_SaveManager.LoadFromFile(uSlot, sFile, sType)
#################################################################################################
## Save all to the given directory
def SaveAllToDirectory(sDirectory, sBase, sExt, sType):
    g_SaveManager.SaveAllToDirectory(sDirectory, sBase, sExt, sType)
#################################################################################################
## Load all from the given directory
def LoadAllFromDirectory(sDirectory, sBase, sExt, sType):
    g_SaveManager.LoadAllFromDirectory(sDirectory, sBase, sExt, sType)
#################################################################################################
## Initialize all save slots
def InitializeAllSaveSlots():
    g_SaveManager.InitializeAllSaveSlots()
#################################################################################################
## Initialize empty save slots
def InitializeEmptySaveSlots():
    g_SaveManager.InitializeEmptySaveSlots()
#################################################################################################
