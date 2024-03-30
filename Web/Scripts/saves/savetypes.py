# Fyleria Engine
# Copyright © 2018 Go Go Gecko Productions

# Imports
import os, sys, json
import GeckoUtility
import GeckoSaves
from GeckoModule import StoreRunResult

#################################################################################################
def GetAllTypeNames():
    result = {}
    result["SaveFileType"] = GeckoSaves.GetSaveFileTypeNames()
    StoreRunResult(json.dumps(result))
#################################################################################################
def GetSaveFileTypeNames():
    result = GeckoSaves.GetSaveFileTypeNames()
    StoreRunResult(json.dumps(result))
#################################################################################################
