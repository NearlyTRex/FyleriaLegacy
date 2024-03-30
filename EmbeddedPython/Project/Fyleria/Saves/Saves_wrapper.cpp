// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

// Internal includes
#include "Saves/Save.h"
#include "Saves/SaveManager.h"
#include "Saves/SaveTypes.h"
#include "Utility/Macros.h"
#include "Utility/Python.h"

namespace Gecko
{
    // Manager lambdas
    auto fnLoadSave = MAKE_MANAGER_VOID_LAMBDA_A1(SaveManager, LoadSave, const Save&);
    auto fnCreateSave = MAKE_MANAGER_VOID_LAMBDA_A1(SaveManager, CreateSave, const String&);
    auto fnUnloadSave = MAKE_MANAGER_VOID_LAMBDA_A1(SaveManager, UnloadSave, const String&);
    auto fnUnloadAllSaves = MAKE_MANAGER_VOID_LAMBDA(SaveManager, UnloadAllSaves);
    auto fnDoesSaveExist = MAKE_MANAGER_RETURN_LAMBDA_A1(SaveManager, DoesSaveExist, Bool, const String&);
    auto fnDoesSaveExist_StoreResult = MAKE_MANAGER_VOID_LAMBDA_A2(SaveManager, DoesSaveExist_StoreResult, const String&, const String&);
    auto fnGetSaveCapacity = MAKE_MANAGER_RETURN_LAMBDA(SaveManager, GetSaveCapacity, UByte);
    auto fnGetSaveCapacity_StoreResult = MAKE_MANAGER_VOID_LAMBDA_A1(SaveManager, GetSaveCapacity_StoreResult, const String&);
    auto fnGetAllAvailableSaveSlots = MAKE_MANAGER_RETURN_LAMBDA(SaveManager, GetAllAvailableSaveSlots, StringArray);
    auto fnGetAllAvailableSaveSlots_StoreResult = MAKE_MANAGER_VOID_LAMBDA_A1(SaveManager, GetAllAvailableSaveSlots_StoreResult, const String&);
    auto fnGetAllSaveDescriptions = MAKE_MANAGER_RETURN_LAMBDA(SaveManager, GetAllSaveDescriptions, StringArray);
    auto fnGetAllSaveDescriptions_StoreResult = MAKE_MANAGER_VOID_LAMBDA_A1(SaveManager, GetAllSaveDescriptions_StoreResult, const String&);
    auto fnIsSaveCapacityReached = MAKE_MANAGER_RETURN_LAMBDA(SaveManager, IsSaveCapacityReached, Bool);
    auto fnIsSaveCapacityReached_StoreResult = MAKE_MANAGER_VOID_LAMBDA_A1(SaveManager, IsSaveCapacityReached_StoreResult, const String&);
    auto fnIsValidSaveSlot = MAKE_MANAGER_RETURN_LAMBDA_A1(SaveManager, IsValidSaveSlot, Bool, const String&);
    auto fnIsValidSaveSlot_StoreResult = MAKE_MANAGER_VOID_LAMBDA_A2(SaveManager, IsValidSaveSlot_StoreResult, const String&, const String&);
    auto fnGetSave1 = MAKE_MANAGER_RETURN_LAMBDA_A1(SaveManager, GetSave, const Save&, const String&);
    auto fnGetSave2 = MAKE_MANAGER_RETURN_LAMBDA_A1(SaveManager, GetSave, Save&, const String&);
    auto fnGetSave_StoreResult = MAKE_MANAGER_VOID_LAMBDA_A2(SaveManager, GetSave_StoreResult, const String&, const String&);
    auto fnGetAllSaves = MAKE_MANAGER_RETURN_LAMBDA(SaveManager, GetAllSaves, SaveArray);
    auto fnGetAllSaves_StoreResult = MAKE_MANAGER_VOID_LAMBDA_A1(SaveManager, GetAllSaves_StoreResult, const String&);
    auto fnCollectSaveData1 = MAKE_MANAGER_VOID_LAMBDA_A2(SaveManager, CollectSaveData, const String&, const String&);
    auto fnCollectSaveData2 = MAKE_MANAGER_VOID_LAMBDA_A4(SaveManager, CollectSaveData, const String&, const StringArray&, const String&, ULong);
    auto fnDisperseSaveData = MAKE_MANAGER_VOID_LAMBDA_A1(SaveManager, DisperseSaveData, const String&);
    auto fnSaveToFile = MAKE_MANAGER_VOID_LAMBDA_A3(SaveManager, SaveToFile, const String&, const String&, const String&);
    auto fnLoadFromFile = MAKE_MANAGER_VOID_LAMBDA_A3(SaveManager, LoadFromFile, const String&, const String&, const String&);
    auto fnSaveAllToDirectory = MAKE_MANAGER_VOID_LAMBDA_A4(SaveManager, SaveAllToDirectory, const String&, const String&, const String&, const String&);
    auto fnLoadAllFromDirectory = MAKE_MANAGER_VOID_LAMBDA_A4(SaveManager, LoadAllFromDirectory, const String&, const String&, const String&, const String&);
    auto fnInitializeAllSaveSlots = MAKE_MANAGER_VOID_LAMBDA(SaveManager, InitializeAllSaveSlots);
    auto fnInitializeEmptySaveSlots = MAKE_MANAGER_VOID_LAMBDA(SaveManager, InitializeEmptySaveSlots);
};

PYBIND11_EMBEDDED_MODULE(GeckoSaves, m)
{
    // Save.h
    PyBindClass<Gecko::Save>(m, "Save")
        WRAPPING_ADD_CONSTRUCTOR_SIMPLE()
        WRAPPING_ADD_CONSTRUCTOR_ARGS(const Gecko::String&)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(Slot, Gecko::Save)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(Time, Gecko::Save)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(Description, Gecko::Save)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(Parties, Gecko::Save)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(Characters, Gecko::Save)
    ;
    PyBindVector<Gecko::SaveArray>(m, "SaveArray");

    // SaveManager.h
    WRAPPING_STANDALONE_LAMBDA(LoadSave, Gecko::fnLoadSave);
    WRAPPING_STANDALONE_LAMBDA(CreateSave, Gecko::fnCreateSave);
    WRAPPING_STANDALONE_LAMBDA(UnloadSave, Gecko::fnUnloadSave);
    WRAPPING_STANDALONE_LAMBDA(UnloadAllSaves, Gecko::fnUnloadAllSaves);
    WRAPPING_STANDALONE_LAMBDA(DoesSaveExist, Gecko::fnDoesSaveExist);
    WRAPPING_STANDALONE_LAMBDA(DoesSaveExist_StoreResult, Gecko::fnDoesSaveExist_StoreResult);
    WRAPPING_STANDALONE_LAMBDA(GetSaveCapacity, Gecko::fnGetSaveCapacity);
    WRAPPING_STANDALONE_LAMBDA(GetSaveCapacity_StoreResult, Gecko::fnGetSaveCapacity_StoreResult);
    WRAPPING_STANDALONE_LAMBDA(GetAllAvailableSaveSlots, Gecko::fnGetAllAvailableSaveSlots);
    WRAPPING_STANDALONE_LAMBDA(GetAllAvailableSaveSlots_StoreResult, Gecko::fnGetAllAvailableSaveSlots_StoreResult);
    WRAPPING_STANDALONE_LAMBDA(GetAllSaveDescriptions, Gecko::fnGetAllSaveDescriptions);
    WRAPPING_STANDALONE_LAMBDA(GetAllSaveDescriptions_StoreResult, Gecko::fnGetAllSaveDescriptions_StoreResult);
    WRAPPING_STANDALONE_LAMBDA(IsSaveCapacityReached, Gecko::fnIsSaveCapacityReached);
    WRAPPING_STANDALONE_LAMBDA(IsSaveCapacityReached_StoreResult, Gecko::fnIsSaveCapacityReached_StoreResult);
    WRAPPING_STANDALONE_LAMBDA(IsValidSaveSlot, Gecko::fnIsValidSaveSlot);
    WRAPPING_STANDALONE_LAMBDA(IsValidSaveSlot_StoreResult, Gecko::fnIsValidSaveSlot_StoreResult);
    WRAPPING_STANDALONE_LAMBDA_POLICY(GetSave, Gecko::fnGetSave1, PyBindReturnCopy);
    WRAPPING_STANDALONE_LAMBDA_POLICY(GetSave, Gecko::fnGetSave2, PyBindReturnRefInternal);
    WRAPPING_STANDALONE_LAMBDA(GetSave_StoreResult, Gecko::fnGetSave_StoreResult);
    WRAPPING_STANDALONE_LAMBDA(GetAllSaves, Gecko::fnGetAllSaves);
    WRAPPING_STANDALONE_LAMBDA(GetAllSaves_StoreResult, Gecko::fnGetAllSaves_StoreResult);
    WRAPPING_STANDALONE_LAMBDA(CollectSaveData, Gecko::fnCollectSaveData1);
    WRAPPING_STANDALONE_LAMBDA(CollectSaveData, Gecko::fnCollectSaveData2);
    WRAPPING_STANDALONE_LAMBDA(DisperseSaveData, Gecko::fnDisperseSaveData);
    WRAPPING_STANDALONE_LAMBDA(SaveToFile, Gecko::fnSaveToFile);
    WRAPPING_STANDALONE_LAMBDA(LoadFromFile, Gecko::fnLoadFromFile);
    WRAPPING_STANDALONE_LAMBDA(SaveAllToDirectory, Gecko::fnSaveAllToDirectory);
    WRAPPING_STANDALONE_LAMBDA(LoadAllFromDirectory, Gecko::fnLoadAllFromDirectory);
    WRAPPING_STANDALONE_LAMBDA(InitializeAllSaveSlots, Gecko::fnInitializeAllSaveSlots);
    WRAPPING_STANDALONE_LAMBDA(InitializeEmptySaveSlots, Gecko::fnInitializeEmptySaveSlots);

    // SaveTypes.h
    WRAPPING_STANDALONE_METHOD_FUNC(GetSaveSlotTypeNames, GetEnumNames<Gecko::SaveSlotType>, Gecko);
}
