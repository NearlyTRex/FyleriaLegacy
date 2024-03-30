// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#include "Saves/Save.h"
#include "Saves/SaveManager.h"
#include "Saves/SaveTypes.h"
#include "Utility/Macros.h"
#include "Utility/TypesPython.h"

namespace Gecko
{

SaveManager* GetSaveManager() { return SaveManager::GetInstance(); }

};

PYBIND11_EMBEDDED_MODULE(GeckoSaves, m)
{
    // Save.h
    PyBindClass<Gecko::Save, Gecko::SerializableToJson>(m, "Save")
        WRAPPING_ADD_CONSTRUCTOR_SIMPLE()
        WRAPPING_ADD_CONSTRUCTOR_ARGS(const Gecko::String&)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(Slot, Gecko::Save)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(Time, Gecko::Save)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(Description, Gecko::Save)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(Party, Gecko::Save)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(Characters, Gecko::Save)
    ;
    PyBindVector<Gecko::SaveList>(m, "SaveList");
    WRAPPING_STANDALONE_METHOD_SIMPLE(ConvertSaveToJsonString, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(ConvertSaveListToJsonString, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetSaveFromJsonString, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetSaveListFromJsonString, Gecko);

    // SaveManager.h
    PyBindClass<Gecko::SaveManager>(m, "SaveManager")
        WRAPPING_ADD_METHOD_SIMPLE(LoadSave, Gecko::SaveManager)
        WRAPPING_ADD_METHOD_SIMPLE(CreateSave, Gecko::SaveManager)
        WRAPPING_ADD_METHOD_SIMPLE(UnloadSave, Gecko::SaveManager)
        WRAPPING_ADD_METHOD_SIMPLE(UnloadAllSaves, Gecko::SaveManager)
        WRAPPING_ADD_METHOD_SIMPLE(DoesSaveExist, Gecko::SaveManager)
        WRAPPING_ADD_METHOD_SIMPLE(GetSaveCapacity, Gecko::SaveManager)
        WRAPPING_ADD_METHOD_SIMPLE(GetAllAvailableSaveSlots, Gecko::SaveManager)
        WRAPPING_ADD_METHOD_SIMPLE(GetAllSaveDescriptions, Gecko::SaveManager)
        WRAPPING_ADD_METHOD_SIMPLE(IsSaveCapacityReached, Gecko::SaveManager)
        WRAPPING_ADD_METHOD_OVERLOADED_POLICY(GetSave, Gecko::SaveManager, PyBindReturnRefInternal, Gecko::UByte)
        WRAPPING_ADD_METHOD_OVERLOADED_POLICY_CONST(GetSave, Gecko::SaveManager, PyBindReturnCopy, Gecko::UByte)
        WRAPPING_ADD_METHOD_SIMPLE(GetAllSaves, Gecko::SaveManager)
        WRAPPING_ADD_METHOD_SIMPLE(PullSaveFromMemory, Gecko::SaveManager)
        WRAPPING_ADD_METHOD_SIMPLE(PushSaveIntoMemory, Gecko::SaveManager)
        WRAPPING_ADD_METHOD_SIMPLE(SaveToFile, Gecko::SaveManager)
        WRAPPING_ADD_METHOD_SIMPLE(LoadFromFile, Gecko::SaveManager)
        WRAPPING_ADD_METHOD_SIMPLE(SaveAllToDirectory, Gecko::SaveManager)
        WRAPPING_ADD_METHOD_SIMPLE(LoadAllFromDirectory, Gecko::SaveManager)
        WRAPPING_ADD_METHOD_SIMPLE(InitializeAllSaveSlots, Gecko::SaveManager)
        WRAPPING_ADD_METHOD_SIMPLE(InitializeEmptySaveSlots, Gecko::SaveManager)
    ;

    // Local
    WRAPPING_STANDALONE_METHOD_POLICY(GetSaveManager, Gecko, PyBindReturnAutoRef);
}
