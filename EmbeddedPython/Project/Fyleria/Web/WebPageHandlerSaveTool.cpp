// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

// Internal includes
#include "Config/ConfigManager.h"
#include "Web/WebPageHandlerSaveTool.h"
#include "Saves/SaveManager.h"
#include "Saves/SaveTypes.h"
#include "Utility/Enum.h"
#include "Utility/Constants.h"
#include "Utility/Converters.h"
#include "Utility/Templates.h"

namespace Gecko
{

WebPageHandlerSaveTool::WebPageHandlerSaveTool()
    : WebPageHandler()
{
    // Set template
    String sTemplateFile = JoinPathsCanonical(GetDataDirectory(), PAGE_FILE_TOOL_SAVE);
    String sTemplateContents = GetFileContentsAsString(sTemplateFile);
    SetPageTemplate(sTemplateContents);

    // Update page
    UpdatePageContent({});
}

WebPageHandlerSaveTool::~WebPageHandlerSaveTool()
{
}

void WebPageHandlerSaveTool::UpdatePageContent(const StringMap& tParams)
{
    // Get fields
    String sAction = GetMapDataOrDefault(tParams, "action", "");
    String sCollectSaveDataSingle_SaveSlotType = GetMapDataOrDefault(tParams, "sCollectSaveDataSingle_SaveSlotType", "");
    String sCollectSaveDataSingle_PartyID = GetMapDataOrDefault(tParams, "sCollectSaveDataSingle_PartyID", "");
    String sCollectSaveDataMultiple_SaveSlotType = GetMapDataOrDefault(tParams, "sCollectSaveDataMultiple_SaveSlotType", "");
    String sCollectSaveDataMultiple_PartyIDs = GetMapDataOrDefault(tParams, "sCollectSaveDataMultiple_PartyIDs", "");
    String sCollectSaveDataMultiple_Description = GetMapDataOrDefault(tParams, "sCollectSaveDataMultiple_Description", "");
    String sCollectSaveDataMultiple_PlayTime = GetMapDataOrDefault(tParams, "sCollectSaveDataMultiple_PlayTime", "");
    String sDisperseSaveData_SaveSlotType = GetMapDataOrDefault(tParams, "sDisperseSaveData_SaveSlotType", "");
    String sLoadSave_Textarea = GetMapDataOrDefault(tParams, "sLoadSave_Textarea", "");
    String sUnloadSave_SaveSlotType = GetMapDataOrDefault(tParams, "sUnloadSave_SaveSlotType", "");
    String sLoadFromFile_SaveSlotType = GetMapDataOrDefault(tParams, "sLoadFromFile_SaveSlotType", "");
    String sLoadFromFile_FileType = GetMapDataOrDefault(tParams, "sLoadFromFile_FileType", "");
    String sLoadFromFile_Filename = GetMapDataOrDefault(tParams, "sLoadFromFile_Filename", "");
    String sSaveToFile_SaveSlotType = GetMapDataOrDefault(tParams, "sSaveToFile_SaveSlotType", "");
    String sSaveToFile_FileType = GetMapDataOrDefault(tParams, "sSaveToFile_FileType", "");
    String sSaveToFile_Filename = GetMapDataOrDefault(tParams, "sSaveToFile_Filename", "");
    String sLoadAllFromDir_Directory = GetMapDataOrDefault(tParams, "sLoadAllFromDir_Directory", "");
    String sLoadAllFromDir_Basename = GetMapDataOrDefault(tParams, "sLoadAllFromDir_Basename", "");
    String sLoadAllFromDir_Extension = GetMapDataOrDefault(tParams, "sLoadAllFromDir_Extension", "");
    String sLoadAllFromDir_FileType = GetMapDataOrDefault(tParams, "sLoadAllFromDir_FileType", "");
    String sSaveAllToDir_Directory = GetMapDataOrDefault(tParams, "sSaveAllToDir_Directory", "");
    String sSaveAllToDir_Basename = GetMapDataOrDefault(tParams, "sSaveAllToDir_Basename", "");
    String sSaveAllToDir_Extension = GetMapDataOrDefault(tParams, "sSaveAllToDir_Extension", "");
    String sSaveAllToDir_FileType = GetMapDataOrDefault(tParams, "sSaveAllToDir_FileType", "");

    // Check action
    if(sAction == "initalize_empty_save_slots")
    {
        SaveManager::GetInstance()->InitializeEmptySaveSlots();
    }
    else if(sAction == "initalize_all_save_slots")
    {
        SaveManager::GetInstance()->InitializeAllSaveSlots();
    }
    else if(sAction == "collect_save_data_single")
    {
        SaveManager::GetInstance()->CollectSaveData(
            sCollectSaveDataSingle_SaveSlotType,
            sCollectSaveDataSingle_PartyID
        );
    }
    else if(sAction == "collect_save_data_multiple")
    {
        StringArray vPartyIDs = ConvertStringToTokenArray(sCollectSaveDataMultiple_PartyIDs, ", ");
        SaveManager::GetInstance()->CollectSaveData(
            sCollectSaveDataMultiple_SaveSlotType,
            vPartyIDs,
            sCollectSaveDataMultiple_Description,
            BoostLexicalCast<ULong>(sCollectSaveDataMultiple_PlayTime)
        );
    }
    else if(sAction == "disperse_save_data")
    {
        SaveManager::GetInstance()->DisperseSaveData(
            sDisperseSaveData_SaveSlotType
        );
    }
    else if(sAction == "load_save")
    {
        SaveManager::GetInstance()->LoadSave(
            Save(sLoadSave_Textarea)
        );
    }
    else if(sAction == "unload_save")
    {
        SaveManager::GetInstance()->UnloadSave(
            sUnloadSave_SaveSlotType
        );
    }
    else if(sAction == "load_from_file")
    {
        SaveManager::GetInstance()->LoadFromFile(
            sLoadFromFile_SaveSlotType,
            sLoadFromFile_Filename,
            sLoadFromFile_FileType
        );
    }
    else if(sAction == "save_to_file")
    {
        SaveManager::GetInstance()->SaveToFile(
            sSaveToFile_SaveSlotType,
            sSaveToFile_Filename,
            sSaveToFile_FileType
        );
    }
    else if(sAction == "load_all_from_dir")
    {
        SaveManager::GetInstance()->LoadAllFromDirectory(
            sLoadAllFromDir_Directory,
            sLoadAllFromDir_Basename,
            sLoadAllFromDir_Extension,
            sLoadAllFromDir_FileType
        );
    }
    else if(sAction == "save_all_to_dir")
    {
        SaveManager::GetInstance()->SaveAllToDirectory(
            sSaveAllToDir_Directory,
            sSaveAllToDir_Basename,
            sSaveAllToDir_Extension,
            sSaveAllToDir_FileType
        );
    }

    // Build option lists
    String sOptionList_SaveSlotType = MakeDefaultHtmlOptionList<SaveSlotType>();
    String sOptionList_FileType = MakeDefaultHtmlOptionList<FileType>();

    // Set page content
    String sPage = GetPageTemplate();
    BoostReplaceAll(sPage, "%sOptionList_SaveSlotType%", sOptionList_SaveSlotType);
    BoostReplaceAll(sPage, "%sOptionList_FileType%", sOptionList_FileType);
    BoostReplaceAll(sPage, "%sCollectSaveDataSingle_PartyID%", sCollectSaveDataSingle_PartyID);
    BoostReplaceAll(sPage, "%sCollectSaveDataMultiple_PartyIDs%", sCollectSaveDataMultiple_PartyIDs);
    BoostReplaceAll(sPage, "%sCollectSaveDataMultiple_Description%", sCollectSaveDataMultiple_Description);
    BoostReplaceAll(sPage, "%sCollectSaveDataMultiple_PlayTime%", sCollectSaveDataMultiple_PlayTime);
    BoostReplaceAll(sPage, "%sLoadSave_Textarea%", sLoadSave_Textarea);
    BoostReplaceAll(sPage, "%sLoadFromFile_Filename%", sLoadFromFile_Filename);
    BoostReplaceAll(sPage, "%sSaveToFile_Filename%", sSaveToFile_Filename);
    BoostReplaceAll(sPage, "%sSaveAllToDir_Directory%", sSaveAllToDir_Directory);
    BoostReplaceAll(sPage, "%sSaveAllToDir_Basename%", sSaveAllToDir_Basename);
    BoostReplaceAll(sPage, "%sSaveAllToDir_Extension%", sSaveAllToDir_Extension);
    BoostReplaceAll(sPage, "%sLoadAllFromDir_Directory%", sLoadAllFromDir_Directory);
    BoostReplaceAll(sPage, "%sLoadAllFromDir_Basename%", sLoadAllFromDir_Basename);
    BoostReplaceAll(sPage, "%sLoadAllFromDir_Extension%", sLoadAllFromDir_Extension);
    for(auto& sSlotName : GetEnumNames<SaveSlotType>())
    {
        String sSaveDataKey = String("%sSaveData_") + sSlotName + String("%");
        String sSaveDataVal = (SaveManager::GetInstance()->DoesSaveExist(sSlotName)) ?
            Json(SaveManager::GetInstance()->GetSave(sSlotName)).dump() : "";
        BoostReplaceAll(sPage, sSaveDataKey, sSaveDataVal);
    }
    SetPageContent(sPage);
}

};
