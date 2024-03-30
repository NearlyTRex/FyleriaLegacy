// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#ifndef _GECKO_SAVE_MANAGER_H_
#define _GECKO_SAVE_MANAGER_H_

#include "Saves/Save.h"
#include "Utility/Singleton.h"

namespace Gecko
{

class SaveManager : public Singleton<SaveManager>
{
public:

    // Constructors
    SaveManager();

    // Load save
    void LoadSave(UByte uSlot, const Save& save);

    // Create save
    void CreateSave(UByte uSlot);

    // Unload save
    void UnloadSave(UByte uSlot);

    // Unload all saves
    void UnloadAllSaves();

    // Does save exist
    Bool DoesSaveExist(UByte uSlot) const;

    // Get save capacity
    UByte GetSaveCapacity() const;

    // Get list of all available save slots
    UByteList GetAllAvailableSaveSlots() const;

    // Get list of all descriptions from save slots
    // Unused slots are also included
    StringList GetAllSaveDescriptions() const;

    // Is save capacity reached
    Bool IsSaveCapacityReached() const;

    // Get save
    Save& GetSave(UByte uSlot);
    const Save& GetSave(UByte uSlot) const;

    // Get all saves
    SaveList GetAllSaves() const;

    // Pull save from memory
    // Creates a new save from the manager data in memory and loads it in the specified save slot
    void PullSaveFromMemory(UByte uSlot, const IndexedString& sPartyID);

    // Push save into memory
    // Copies the data from the specified save slot into manager memory
    void PushSaveIntoMemory(UByte uSlot);

    // Save to file
    void SaveToFile(UByte uSlot, const IndexedString& sFile, const IndexedString& sType);

    // Load to file
    void LoadFromFile(UByte uSlot, const IndexedString& sFile, const IndexedString& sType);

    // Save all to the given directory
    void SaveAllToDirectory(const IndexedString& sDirectory, const IndexedString& sBase, const IndexedString& sExt, const IndexedString& sType);

    // Load all from the given directory
    void LoadAllFromDirectory(const IndexedString& sDirectory, const IndexedString& sBase, const IndexedString& sExt, const IndexedString& sType);

    // Initialize all save slots
    void InitializeAllSaveSlots();

    // Initialize empty save slots
    void InitializeEmptySaveSlots();

private:

    // Saves
    STDUnorderedMap<UByte, Save> m_tSaves;

};

};

#endif
