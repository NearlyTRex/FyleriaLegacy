// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

// Internal includes
#include "Saves/SaveManager.h"
#include "Saves/SaveTypes.h"
#include "Utility/Constants.h"

namespace Gecko
{

SaveManager::SaveManager()
    : Singleton<SaveManager>()
{
}

void SaveManager::LoadSave(const Save& save)
{
    // Check if save slot is valid
    const String& sSlot = save.GetSlot();
    if(!IsValidSaveSlot(sSlot))
    {
        THROW_RUNTIME_ERROR("Save slot '" + sSlot + "' was not valid");
    }

    // Load a save
    GetSaves().insert({sSlot, save});
}

void SaveManager::CreateSave(const String& sSlot)
{
    // Check if save exists
    if(DoesSaveExist(sSlot))
    {
        THROW_RUNTIME_ERROR("Save slot '" + sSlot + "' was already registered");
    }

    // Create a new save
    Save newSave;
    newSave.SetSlot(sSlot);
    GetSaves().insert({sSlot, newSave});
}

void SaveManager::UnloadSave(const String& sSlot)
{
    // Check if save exists
    if(!DoesSaveExist(sSlot))
    {
        THROW_RUNTIME_ERROR("Save slot '" + sSlot + "' was not registered");
    }

    // Unload save
    GetSaves().erase(sSlot);
}

void SaveManager::UnloadAllSaves()
{
    // Unload all saves
    GetSaves().clear();
}

Bool SaveManager::DoesSaveExist(const String& sSlot) const
{
    // Check if save exists
    auto iSearch = GetSaves().find(sSlot);
    return (iSearch != GetSaves().end());
}

UByte SaveManager::GetSaveCapacity() const
{
    // Get max number of save slots
    return MAX_SAVE_SLOT;
}

StringArray SaveManager::GetAllAvailableSaveSlots() const
{
    // Get a list of all slots that are not used
    StringArray vSlots;
    for(auto& sSlotName : GetEnumNames<SaveSlotType>())
    {
        if(!DoesSaveExist(sSlotName))
        {
            vSlots.push_back(sSlotName);
        }
    }
    return vSlots;
}

StringArray SaveManager::GetAllSaveDescriptions() const
{
    // Get all save descriptions
    StringArray vDescriptions;
    for(auto& sSlotName : GetEnumNames<SaveSlotType>())
    {
        vDescriptions.push_back(DoesSaveExist(sSlotName) ? GetSave(sSlotName).GetDescription() : "");
    }
    return vDescriptions;
}

Bool SaveManager::IsSaveCapacityReached() const
{
    // Get whether save capacity is reached
    StringArray vAvailableSlots = GetAllAvailableSaveSlots();
    return vAvailableSlots.empty();
}

Bool SaveManager::IsValidSaveSlot(const String& sSlot) const
{
    // Check save slot validity
    return IsValidEnumString<SaveSlotType>(sSlot);
}

const Save& SaveManager::GetSave(const String& sSlot) const
{
    // Check if save exists
    if(!DoesSaveExist(sSlot))
    {
        THROW_RUNTIME_ERROR("Save slot '" + sSlot + "' was not registered");
    }

    // Get save
    auto iSearch = GetSaves().find(sSlot);
    return iSearch->second;
}

Save& SaveManager::GetSave(const String& sSlot)
{
    // Get save
    return const_cast<Save&>(static_cast<const SaveManager&>(*this).GetSave(sSlot));
}

SaveArray SaveManager::GetAllSaves() const
{
    SaveArray vSaves;
    for(auto it = GetSaves().begin(); it != GetSaves().end(); it++)
    {
        vSaves.push_back(it->second);
    }
    return vSaves;
}

void SaveManager::CollectSaveData(const String& sSlot, const String& sPartyID)
{
    const CharacterParty& party = CharacterPartyManager::GetInstance()->GetPartyByID(sPartyID);
    CollectSaveData(sSlot, {sPartyID}, party.GetDescription(), party.GetPlayTime());
}

void SaveManager::CollectSaveData(const String& sSlot, const StringArray& vPartyIDs, const String& sDescription, ULongLong uPlayTime)
{
    // Get parties and attached characters
    CharacterPartyArray vParties;
    CharacterArray vCharacters;
    for (auto& sPartyID : vPartyIDs)
    {
        // Add party
        CharacterParty& party = CharacterPartyManager::GetInstance()->GetPartyByID(sPartyID);
        party.RegenerateCharacterData();
        vParties.push_back(party);

        // Add members of this party
        for(auto& member : party.GetMembers())
        {
            vCharacters.push_back(CharacterManager::GetInstance()->GetCharacter(member.first));
        }
    }

    // Create save from this
    Save newSave;
    newSave.SetSlot(sSlot);
    newSave.SetTime(uPlayTime);
    newSave.SetParties(vParties);
    newSave.SetCharacters(vCharacters);
    newSave.SetDescription(sDescription);

    // Load save into manager, potentially overwriting an existing save
    LoadSave(newSave);
}

void SaveManager::DisperseSaveData(const String& sSlot)
{
    // Get save from slot
    const Save& save = GetSave(sSlot);

    // Load characters
    for(const Character& character : save.GetCharacters())
    {
        CharacterManager::GetInstance()->LoadCharacter(character, false);
    }

    // Load parties
    for(const CharacterParty& party : save.GetParties())
    {
        CharacterPartyManager::GetInstance()->LoadParty(party, true);
    }
}

void SaveManager::SaveToFile(const String& sSlot, const String& sFile, const String& sType)
{
    // Serialize save data to file
    Json jsonData = GetSave(sSlot);
    Bool bSuccess = WriteSerializedFile(sFile, sType, jsonData);
    if(!bSuccess)
    {
        THROW_RUNTIME_ERROR("Writing save '" + sSlot + "' to file '" + sFile + "' as type '" + sType + "' failed");
    }
}

void SaveManager::LoadFromFile(const String& sSlot, const String& sFile, const String& sType)
{
    // Deserialize file to save data
    Json jsonData;
    Bool bSuccess = ReadSerializedFile(sFile, sType, jsonData);
    if(!bSuccess)
    {
        THROW_RUNTIME_ERROR("Reading save '" + sSlot + "' from file '" + sFile + "' as type '" + sType + "' failed");
    }

    // Load save
    LoadSave(jsonData.get<Save>());
}

void SaveManager::SaveAllToDirectory(const String& sDirectory, const String& sBase, const String& sExt, const String& sType)
{
    // Save each slot into a save file
    for(auto& sSlotName : GetEnumNames<SaveSlotType>())
    {
        if(IsNoneTypeForEnum<SaveSlotType>(sSlotName))
        {
            continue;
        }
        String sPath = JoinPaths(sDirectory, sBase + sSlotName + String(".") + sExt);
        SaveToFile(sSlotName, String(sPath), sType);
    }
}

void SaveManager::LoadAllFromDirectory(const String& sDirectory, const String& sBase, const String& sExt, const String& sType)
{
    // Get save path
    String sSavePath = GetCanonicalPath(sDirectory);

    // Load each slot from a save file
    for(auto& sSlotName : GetEnumNames<SaveSlotType>())
    {
        if(IsNoneTypeForEnum<SaveSlotType>(sSlotName))
        {
            continue;
        }
        String sPath = JoinPaths(sSavePath, sBase + sSlotName + String(".") + sExt);
        if(DoesPathExist(sPath))
        {
            LoadFromFile(sSlotName, String(sPath), sType);
        }
    }
}

void SaveManager::InitializeAllSaveSlots()
{
    // Unload all saves first
    UnloadAllSaves();

    // Create a save for all slots
    for(auto& sSlotName : GetEnumNames<SaveSlotType>())
    {
        if(IsNoneTypeForEnum<SaveSlotType>(sSlotName))
        {
            continue;
        }
        CreateSave(sSlotName);
    }
}

void SaveManager::InitializeEmptySaveSlots()
{
    // Create a save for empty slots
    for(auto& sSlotName : GetEnumNames<SaveSlotType>())
    {
        if(IsNoneTypeForEnum<SaveSlotType>(sSlotName))
        {
            continue;
        }
        if (!DoesSaveExist(sSlotName))
        {
            CreateSave(sSlotName);
        }
    }
}

};
