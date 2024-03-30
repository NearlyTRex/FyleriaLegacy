# Fyleria Engine
# Copyright © 2018 Go Go Gecko Productions

# Imports
import os, sys, json
import GeckoUtility
import GeckoCharacterParty
from GeckoModule import StoreRunResult

# Get managers
g_PartyManager = GeckoCharacterParty.GetCharacterPartyManager()

#################################################################################################
## Load a party
def LoadParty(sPartyJson):
    g_PartyManager.LoadParty(GeckoCharacterParty.GetCharacterPartyFromJsonString(sPartyJson))
#################################################################################################
## Create a party
def CreateParty(sPartyID, sPartyType, bSetAsCurrent):
    g_PartyManager.CreateParty(sPartyID, sPartyType, bSetAsCurrent)
#################################################################################################
## Unload party
def UnloadParty(sPartyID):
    g_PartyManager.UnloadParty(sPartyID)
#################################################################################################
## Determine if party exists
def DoesPartyExist(sPartyID):
    result = g_PartyManager.DoesPartyExist(sPartyID)
    StoreRunResult(json.dumps(result))
#################################################################################################
## Set party ID as current ally party
def SetAsCurrentAllyParty(sPartyID):
    g_PartyManager.SetAsCurrentAllyParty(sPartyID)
#################################################################################################
## Set party ID as current enemy party
def SetAsCurrentEnemyParty(sPartyID):
    g_PartyManager.SetAsCurrentEnemyParty(sPartyID)
#################################################################################################
## Get current ally party ID
def GetCurrentAllyPartyID():
    result = g_PartyManager.GetCurrentAllyPartyID()
    StoreRunResult(json.dumps(result))
#################################################################################################
## Get current enemy party ID
def GetCurrentEnemyPartyID():
    result = g_PartyManager.GetCurrentEnemyPartyID()
    StoreRunResult(json.dumps(result))
#################################################################################################
## Get party by ID
def GetPartyByID(sPartyID):
    result = g_PartyManager.GetPartyByID(sPartyID)
    StoreRunResult(GeckoCharacterParty.ConvertCharacterPartyToJsonString(result))
#################################################################################################
## Get party by type
def GetPartyByType(sPartyType):
    result = g_PartyManager.GetPartyByType(sPartyType)
    StoreRunResult(GeckoCharacterParty.ConvertCharacterPartyToJsonString(result))
#################################################################################################
## Get current ally party
def GetCurrentAllyParty():
    result = g_PartyManager.GetCurrentAllyParty()
    StoreRunResult(GeckoCharacterParty.ConvertCharacterPartyToJsonString(result))
#################################################################################################
## Get current enemy party
def GetCurrentEnemyParty():
    result = g_PartyManager.GetCurrentEnemyParty()
    StoreRunResult(GeckoCharacterParty.ConvertCharacterPartyToJsonString(result))
#################################################################################################
