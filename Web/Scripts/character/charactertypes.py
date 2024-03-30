# Fyleria Engine
# Copyright © 2018 Go Go Gecko Productions

# Imports
import os, sys, json
import GeckoUtility
import GeckoCharacter
from GeckoModule import StoreRunResult

#################################################################################################
def GetAllTypeNames():
    result = {}
    result["CharacterTreeIndexType"] = GeckoCharacter.GetCharacterTreeIndexTypeNames()
    result["CharacterSegmentType"] = GeckoCharacter.GetCharacterSegmentTypeNames()
    result["CharacterProgressStatType"] = GeckoCharacter.GetCharacterProgressStatTypeNames()
    result["CharacterBattleStatType"] = GeckoCharacter.GetCharacterBattleStatTypeNames()
    result["CharacterStatusType"] = GeckoCharacter.GetCharacterStatusTypeNames()
    result["CharacterBaseRaceType"] = GeckoCharacter.GetCharacterBaseRaceTypeNames()
    result["CharacterTransformedRaceType"] = GeckoCharacter.GetCharacterTransformedRaceTypeNames()
    result["CharacterPowerSetType"] = GeckoCharacter.GetCharacterPowerSetTypeNames()
    result["CharacterWeaponSetType"] = GeckoCharacter.GetCharacterWeaponSetTypeNames()
    result["CharacterGenderType"] = GeckoCharacter.GetCharacterGenderTypeNames()
    result["CharacterHairType"] = GeckoCharacter.GetCharacterHairTypeNames()
    result["CharacterEyeType"] = GeckoCharacter.GetCharacterEyeTypeNames()
    result["CharacterHandednessType"] = GeckoCharacter.GetCharacterHandednessTypeNames()
    result["CharacterHandType"] = GeckoCharacter.GetCharacterHandTypeNames()
    result["CharacterEquipmentType"] = GeckoCharacter.GetCharacterEquipmentTypeNames()
    result["CharacterTargetType"] = GeckoCharacter.GetCharacterTargetTypeNames()
    result["CharacterPartyType"] = GeckoCharacter.GetCharacterPartyTypeNames()
    result["CharacterActionType"] = GeckoCharacter.GetCharacterActionTypeNames()
    StoreRunResult(json.dumps(result))
#################################################################################################
def GetCharacterTreeIndexTypeNames():
    result = GeckoCharacter.GetCharacterTreeIndexTypeNames()
    StoreRunResult(json.dumps(result))
#################################################################################################
def GetCharacterSegmentTypeNames():
    result = GeckoCharacter.GetCharacterSegmentTypeNames()
    StoreRunResult(json.dumps(result))
#################################################################################################
def GetCharacterProgressStatTypeNames():
    result = GeckoCharacter.GetCharacterProgressStatTypeNames()
    StoreRunResult(json.dumps(result))
#################################################################################################
def GetCharacterBattleStatTypeNames():
    result = GeckoCharacter.GetCharacterBattleStatTypeNames()
    StoreRunResult(json.dumps(result))
#################################################################################################
def GetCharacterStatusTypeNames():
    result = GeckoCharacter.GetCharacterStatusTypeNames()
    StoreRunResult(json.dumps(result))
#################################################################################################
def GetCharacterBaseRaceTypeNames():
    result = GeckoCharacter.GetCharacterBaseRaceTypeNames()
    StoreRunResult(json.dumps(result))
#################################################################################################
def GetCharacterTransformedRaceTypeNames():
    result = GeckoCharacter.GetCharacterTransformedRaceTypeNames()
    StoreRunResult(json.dumps(result))
#################################################################################################
def GetCharacterPowerSetTypeNames():
    result = GeckoCharacter.GetCharacterPowerSetTypeNames()
    StoreRunResult(json.dumps(result))
#################################################################################################
def GetCharacterWeaponSetTypeNames():
    result = GeckoCharacter.GetCharacterWeaponSetTypeNames()
    StoreRunResult(json.dumps(result))
#################################################################################################
def GetCharacterGenderTypeNames():
    result = GeckoCharacter.GetCharacterGenderTypeNames()
    StoreRunResult(json.dumps(result))
#################################################################################################
def GetCharacterHairTypeNames():
    result = GeckoCharacter.GetCharacterHairTypeNames()
    StoreRunResult(json.dumps(result))
#################################################################################################
def GetCharacterEyeTypeNames():
    result = GeckoCharacter.GetCharacterEyeTypeNames()
    StoreRunResult(json.dumps(result))
#################################################################################################
def GetCharacterHandednessTypeNames():
    result = GeckoCharacter.GetCharacterHandednessTypeNames()
    StoreRunResult(json.dumps(result))
#################################################################################################
def GetCharacterHandTypeNames():
    result = GeckoCharacter.GetCharacterHandTypeNames()
    StoreRunResult(json.dumps(result))
#################################################################################################
def GetCharacterEquipmentTypeNames():
    result = GeckoCharacter.GetCharacterEquipmentTypeNames()
    StoreRunResult(json.dumps(result))
#################################################################################################
def GetCharacterTargetTypeNames():
    result = GeckoCharacter.GetCharacterTargetTypeNames()
    StoreRunResult(json.dumps(result))
#################################################################################################
def GetCharacterPartyTypeNames():
    result = GeckoCharacter.GetCharacterPartyTypeNames()
    StoreRunResult(json.dumps(result))
#################################################################################################
def GetCharacterActionTypeNames():
    result = GeckoCharacter.GetCharacterActionTypeNames()
    StoreRunResult(json.dumps(result))
#################################################################################################
