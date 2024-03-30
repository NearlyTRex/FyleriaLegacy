// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

#ifndef _GECKO_SAVE_MANAGER_H_
#define _GECKO_SAVE_MANAGER_H_

// Internal includes
#include "Saves/Save.h"
#include "Utility/ResultManager.h"
#include "Utility/Singleton.h"

namespace Gecko
{

class SaveManager : public Singleton<SaveManager>
{
public:

    // Types
    typedef STDUnorderedMap<String, Save> SaveMappingType;

    // Constructors
    SaveManager();

    // Load save
    void LoadSave(const Save& save);

    // Create save
    void CreateSave(const String& sSlot);

    // Unload save
    void UnloadSave(const String& sSlot);

    // Unload all saves
    void UnloadAllSaves();

    // Does save exist
    Bool DoesSaveExist(const String& sSlot) const;
    MAKE_MODULE_RESULT_VARIANT_A1(DoesSaveExist, const String&);

    // Get save capacity
    UByte GetSaveCapacity() const;
    MAKE_MODULE_RESULT_VARIANT(GetSaveCapacity);

    // Get list of all available save slots
    StringArray GetAllAvailableSaveSlots() const;
    MAKE_MODULE_RESULT_VARIANT(GetAllAvailableSaveSlots);

    // Get list of all descriptions from save slots
    // Unused slots are also included
    StringArray GetAllSaveDescriptions() const;
    MAKE_MODULE_RESULT_VARIANT(GetAllSaveDescriptions);

    // Is save capacity reached
    Bool IsSaveCapacityReached() const;
    MAKE_MODULE_RESULT_VARIANT(IsSaveCapacityReached);

    // Check if save slot is valid
    Bool IsValidSaveSlot(const String& sSlot) const;
    MAKE_MODULE_RESULT_VARIANT_A1(IsValidSaveSlot, const String&);

    // Get save
    const Save& GetSave(const String& sSlot) const;
    Save& GetSave(const String& sSlot);
    MAKE_MODULE_RESULT_VARIANT_A1(GetSave, const String&);

    // Get all saves
    SaveArray GetAllSaves() const;
    MAKE_MODULE_RESULT_VARIANT(GetAllSaves);

    // Collect data and create a save
    void CollectSaveData(const String& sSlot, const String& sPartyID);
    void CollectSaveData(const String& sSlot, const StringArray& vPartyIDs, const String& sDescription, ULongLong uPlayTime);

    // Disperse save data
    void DisperseSaveData(const String& sSlot);

    // Save to file
    void SaveToFile(const String& sSlot, const String& sFile, const String& sType);

    // Load to file
    void LoadFromFile(const String& sSlot, const String& sFile, const String& sType);

    // Save all to the given directory
    void SaveAllToDirectory(const String& sDirectory, const String& sBase, const String& sExt, const String& sType);

    // Load all from the given directory
    void LoadAllFromDirectory(const String& sDirectory, const String& sBase, const String& sExt, const String& sType);

    // Initialize all save slots
    void InitializeAllSaveSlots();

    // Initialize empty save slots
    void InitializeEmptySaveSlots();

    // Saves
    MAKE_RAW_TYPE_ACCESSORS(Saves, SaveMappingType);
};

};

#endif
