// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

// Internal includes
#include "Config/ConfigManager.h"
#include "Web/WebPageHandlerPartyTool.h"
#include "Character/CharacterTypes.h"
#include "CharacterParty/CharacterPartyManager.h"
#include "Items/ItemTypes.h"
#include "Utility/Constants.h"
#include "Utility/Converters.h"
#include "Utility/Enum.h"
#include "Utility/Templates.h"

namespace Gecko
{

WebPageHandlerPartyTool::WebPageHandlerPartyTool()
    : WebPageHandler()
{
    // Set template
    String sTemplateFile = JoinPathsCanonical(GetDataDirectory(), PAGE_FILE_TOOL_PARTY);
    String sTemplateContents = GetFileContentsAsString(sTemplateFile);
    SetPageTemplate(sTemplateContents);

    // Update page
    UpdatePageContent({});
}

WebPageHandlerPartyTool::~WebPageHandlerPartyTool()
{
}

void WebPageHandlerPartyTool::UpdatePageContent(const StringMap& tParams)
{
    // Get fields
    String sAction = GetMapDataOrDefault(tParams, "action", "");
    String sLoadPartyFromJson_Textarea = GetMapDataOrDefault(tParams, "sLoadPartyFromJson_Textarea", "");
    String sLoadPartyFromFile_Filename = GetMapDataOrDefault(tParams, "sLoadPartyFromFile_Filename", "");
    String sLoadPartyFromFile_FileType = GetMapDataOrDefault(tParams, "sLoadPartyFromFile_FileType", "");
    String sSavePartyToFile_PartyID = GetMapDataOrDefault(tParams, "sSavePartyToFile_PartyID", "");
    String sSavePartyToFile_Filename = GetMapDataOrDefault(tParams, "sSavePartyToFile_Filename", "");
    String sSavePartyToFile_FileType = GetMapDataOrDefault(tParams, "sSavePartyToFile_FileType", "");
    String sUnloadParty_PartyID = GetMapDataOrDefault(tParams, "sUnloadParty_PartyID", "");
    String sSetCurrentParty_PartyID = GetMapDataOrDefault(tParams, "sSetCurrentParty_PartyID", "");
    String sSetCurrentParty_PartyType = GetMapDataOrDefault(tParams, "sSetCurrentParty_PartyType", "");
    String sCreateParty_PartyID = GetMapDataOrDefault(tParams, "sCreateParty_PartyID", "");
    String sCreateParty_PartyType = GetMapDataOrDefault(tParams, "sCreateParty_PartyType", "");
    String sCreateParty_SetAsCurrent = GetMapDataOrDefault(tParams, "sCreateParty_SetAsCurrent", "");
    String sAddMember_PartyID = GetMapDataOrDefault(tParams, "sAddMember_PartyID", "");
    String sAddMember_CharID = GetMapDataOrDefault(tParams, "sAddMember_CharID", "");
    String sRemoveMember_PartyID = GetMapDataOrDefault(tParams, "sRemoveMember_PartyID", "");
    String sRemoveMember_CharID = GetMapDataOrDefault(tParams, "sRemoveMember_CharID", "");
    String sMoveMember_PartyID = GetMapDataOrDefault(tParams, "sMoveMember_PartyID", "");
    String sMoveMember_CharID = GetMapDataOrDefault(tParams, "sMoveMember_CharID", "");
    String sMoveMember_CharTargetType = GetMapDataOrDefault(tParams, "sMoveMember_CharTargetType", "");
    String sSwapMember_PartyID = GetMapDataOrDefault(tParams, "sSwapMember_PartyID", "");
    String sSwapMember_First_CharID = GetMapDataOrDefault(tParams, "sSwapMember_First_CharID", "");
    String sSwapMember_Second_CharID = GetMapDataOrDefault(tParams, "sSwapMember_Second_CharID", "");
    String sAddItem_PartyID = GetMapDataOrDefault(tParams, "sAddItem_PartyID", "");
    String sAddItem_ItemName = GetMapDataOrDefault(tParams, "sAddItem_ItemName", "");
    String sAddItem_ItemAmount = GetMapDataOrDefault(tParams, "sAddItem_ItemAmount", "");
    String sAddRandomItems_PartyID = GetMapDataOrDefault(tParams, "sAddRandomItems_PartyID", "");
    String sAddRandomItems_ItemTreeType = GetMapDataOrDefault(tParams, "sAddRandomItems_ItemTreeType", "");
    String sAddRandomItems_ItemCount = GetMapDataOrDefault(tParams, "sAddRandomItems_ItemCount", "");
    String sAddRandomItems_ItemAmount = GetMapDataOrDefault(tParams, "sAddRandomItems_ItemAmount", "");
    String sRemoveItem_PartyID = GetMapDataOrDefault(tParams, "sRemoveItem_PartyID", "");
    String sRemoveItem_ItemName = GetMapDataOrDefault(tParams, "sRemoveItem_ItemName", "");
    String sRemoveItem_ItemAmount = GetMapDataOrDefault(tParams, "sRemoveItem_ItemAmount", "");
    String sEquipItem_PartyID = GetMapDataOrDefault(tParams, "sEquipItem_PartyID", "");
    String sEquipItem_CharID = GetMapDataOrDefault(tParams, "sEquipItem_CharID", "");
    String sEquipItem_ItemName = GetMapDataOrDefault(tParams, "sEquipItem_ItemName", "");
    String sEquipItem_CharacterEquipmentType = GetMapDataOrDefault(tParams, "sEquipItem_CharacterEquipmentType", "");
    String sUnequipItem_PartyID = GetMapDataOrDefault(tParams, "sUnequipItem_PartyID", "");
    String sUnequipItem_CharID = GetMapDataOrDefault(tParams, "sUnequipItem_CharID", "");
    String sUnequipItem_ItemName = GetMapDataOrDefault(tParams, "sUnequipItem_ItemName", "");
    String sUnequipItem_CharacterEquipmentType = GetMapDataOrDefault(tParams, "sUnequipItem_CharacterEquipmentType", "");
    String sEquipBestItems_PartyID = GetMapDataOrDefault(tParams, "sEquipBestItems_PartyID", "");
    String sEquipBestItems_CharID = GetMapDataOrDefault(tParams, "sEquipBestItems_CharID", "");
    String sUnequipBestItems_PartyID = GetMapDataOrDefault(tParams, "sUnequipBestItems_PartyID", "");
    String sUnequipBestItems_CharID = GetMapDataOrDefault(tParams, "sUnequipBestItems_CharID", "");
    String sEquipBestItemsAllMembers_PartyID = GetMapDataOrDefault(tParams, "sEquipBestItemsAllMembers_PartyID", "");
    String sUnequipBestItemsAllMembers_PartyID = GetMapDataOrDefault(tParams, "sUnequipBestItemsAllMembers_PartyID", "");
    String sDisplayParty_PartyID = GetMapDataOrDefault(tParams, "sDisplayParty_PartyID", "");

    // Party details
    String sPartyDetails_PartyID;
    String sPartyDetails_PartyType;
    String sPartyDetails_PlayTime;
    String sPartyDetails_TakenTargetTypes;
    String sPartyDetails_AvailableTargetTypes;
    String sPartyDetails_Members;
    String sPartyDetails_Items;
    String sPartyDetails_Description;

    // Party to display
    String sPartyToDisplay;

    // Check action
    if(sAction == "load_party_from_json")
    {
        sPartyToDisplay = CharacterPartyManager::GetInstance()->LoadParty(
            CharacterParty(sLoadPartyFromJson_Textarea), true
        );
    }
    else if(sAction == "load_party_from_file")
    {
        sPartyToDisplay = CharacterPartyManager::GetInstance()->LoadPartyFromFile(
            sLoadPartyFromFile_Filename, sLoadPartyFromFile_FileType, true
        );
    }
    else if(sAction == "save_party_to_file")
    {
        CharacterPartyManager::GetInstance()->SavePartyToFile(
            sSavePartyToFile_PartyID,
            sSavePartyToFile_Filename,
            sSavePartyToFile_FileType
        );
        sPartyToDisplay = sSavePartyToFile_PartyID;
    }
    else if(sAction == "unload_party")
    {
        CharacterPartyManager::GetInstance()->UnloadParty(
            sUnloadParty_PartyID
        );
    }
    else if(sAction == "set_current_party")
    {
        const CharacterPartyType ePartyType = GetEnumFromString<CharacterPartyType>(sSetCurrentParty_PartyType);
        switch(ePartyType)
        {
            case CharacterPartyType::Ally:
                CharacterPartyManager::GetInstance()->SetCurrentAllyPartyID(sSetCurrentParty_PartyID);
                break;
            case CharacterPartyType::Enemy:
                CharacterPartyManager::GetInstance()->SetCurrentEnemyPartyID(sSetCurrentParty_PartyID);
                break;
            default:
                break;
        }
        sPartyToDisplay = sSetCurrentParty_PartyID;
    }
    else if(sAction == "create_party")
    {
        CharacterPartyManager::GetInstance()->CreateParty(
            sCreateParty_PartyID,
            sCreateParty_PartyType,
            (sCreateParty_SetAsCurrent == "current")
        );
        sPartyToDisplay = sCreateParty_PartyID;
    }
    else if(sAction == "add_member")
    {
        CharacterParty& party = CharacterPartyManager::GetInstance()->GetPartyByID(sAddMember_PartyID);
        party.AddMember(
            sAddMember_CharID
        );
        sPartyToDisplay = sAddMember_PartyID;
    }
    else if(sAction == "remove_member")
    {
        CharacterParty& party = CharacterPartyManager::GetInstance()->GetPartyByID(sRemoveMember_PartyID);
        party.RemoveMember(
            sRemoveMember_CharID
        );
        sPartyToDisplay = sRemoveMember_PartyID;
    }
    else if(sAction == "move_member")
    {
        CharacterParty& party = CharacterPartyManager::GetInstance()->GetPartyByID(sMoveMember_PartyID);
        party.MoveMember(
            sMoveMember_CharID,
            sMoveMember_CharTargetType
        );
        sPartyToDisplay = sMoveMember_PartyID;
    }
    else if(sAction == "swap_member")
    {
        CharacterParty& party = CharacterPartyManager::GetInstance()->GetPartyByID(sSwapMember_PartyID);
        party.SwapMembers(
            sSwapMember_First_CharID,
            sSwapMember_Second_CharID
        );
        sPartyToDisplay = sSwapMember_PartyID;
    }
    else if(sAction == "add_item")
    {
        CharacterParty& party = CharacterPartyManager::GetInstance()->GetPartyByID(sAddItem_PartyID);
        party.AddItemByLeaf(
            sAddItem_ItemName,
            BoostLexicalCast<UInt>(sAddItem_ItemAmount)
        );
        sPartyToDisplay = sAddItem_PartyID;
    }
    else if(sAction == "add_random_items")
    {
        CharacterParty& party = CharacterPartyManager::GetInstance()->GetPartyByID(sAddRandomItems_PartyID);
        party.AddRandomItems(
            {sAddRandomItems_ItemTreeType},
            BoostLexicalCast<Int>(sAddRandomItems_ItemCount),
            BoostLexicalCast<Int>(sAddRandomItems_ItemAmount),
            BoostLexicalCast<Int>(sAddRandomItems_ItemAmount)
        );
        sPartyToDisplay = sAddRandomItems_PartyID;
    }
    else if(sAction == "remove_item")
    {
        CharacterParty& party = CharacterPartyManager::GetInstance()->GetPartyByID(sRemoveItem_PartyID);
        party.RemoveItemByLeaf(
            sRemoveItem_ItemName,
            BoostLexicalCast<UInt>(sRemoveItem_ItemAmount)
        );
        sPartyToDisplay = sRemoveItem_PartyID;
    }
    else if(sAction == "equip_item")
    {
        CharacterParty& party = CharacterPartyManager::GetInstance()->GetPartyByID(sEquipItem_PartyID);
        party.EquipItem(
            sEquipItem_CharID,
            sEquipItem_ItemName,
            sEquipItem_CharacterEquipmentType
        );
        sPartyToDisplay = sEquipItem_PartyID;
    }
    else if(sAction == "unequip_item")
    {
        CharacterParty& party = CharacterPartyManager::GetInstance()->GetPartyByID(sUnequipItem_PartyID);
        party.UnequipItem(
            sUnequipItem_CharID,
            sUnequipItem_ItemName,
            sUnequipItem_CharacterEquipmentType
        );
        sPartyToDisplay = sUnequipItem_PartyID;
    }
    else if(sAction == "equip_best_items")
    {
        CharacterParty& party = CharacterPartyManager::GetInstance()->GetPartyByID(sEquipBestItems_PartyID);
        party.EquipBestItems(
            sEquipBestItems_CharID
        );
        sPartyToDisplay = sEquipBestItems_PartyID;
    }
    else if(sAction == "unequip_best_items")
    {
        CharacterParty& party = CharacterPartyManager::GetInstance()->GetPartyByID(sUnequipBestItems_PartyID);
        party.UnequipAllItems(
            sUnequipBestItems_CharID
        );
        sPartyToDisplay = sUnequipBestItems_PartyID;
    }
    else if(sAction == "equip_best_items_all_members")
    {
        CharacterParty& party = CharacterPartyManager::GetInstance()->GetPartyByID(sEquipBestItemsAllMembers_PartyID);
        party.EquipBestItemsForAllMembers();
        sPartyToDisplay = sEquipBestItemsAllMembers_PartyID;
    }
    else if(sAction == "unequip_best_items_all_members")
    {
        CharacterParty& party = CharacterPartyManager::GetInstance()->GetPartyByID(sUnequipBestItemsAllMembers_PartyID);
        party.UnequipAllItemsForAllMembers();
        sPartyToDisplay = sUnequipBestItemsAllMembers_PartyID;
    }
    else if(sAction == "display_party")
    {
        sPartyToDisplay = sDisplayParty_PartyID;
    }

    // Get all party ids
    String sAllPartyIDs = ConcatStringVector(CharacterPartyManager::GetInstance()->GetAllPartyIDs());

    // Get current parties
    String sCurrentParty_Ally = CharacterPartyManager::GetInstance()->GetCurrentAllyPartyID();
    String sCurrentParty_Enemy = CharacterPartyManager::GetInstance()->GetCurrentEnemyPartyID();

    // Display party
    if(!sPartyToDisplay.empty())
    {
        const CharacterParty& party = CharacterPartyManager::GetInstance()->GetPartyByID(sPartyToDisplay);
        sPartyDetails_PartyID = party.GetPartyID();
        sPartyDetails_PartyType = party.GetPartyType();
        sPartyDetails_PlayTime = ConvertGameTimeToString(party.GetPlayTime());
        sPartyDetails_TakenTargetTypes = ConcatStringVector(party.GetTakenTargetTypes());
        sPartyDetails_AvailableTargetTypes = ConcatStringVector(party.GetAvailableTargetTypes());
        sPartyDetails_Members = Json(party.GetMembers()).dump();
        sPartyDetails_Items = Json(party.GetItems()).dump();
        sPartyDetails_Description = party.GetDescription();
    }

    // Build option lists
    String sOptionList_CharacterPartyType = MakeDefaultHtmlOptionList<CharacterPartyType>();
    String sOptionList_CharacterResolvedTargetType = MakeDefaultHtmlOptionList<CharacterResolvedTargetType>();
    String sOptionList_CharacterEquipmentType = MakeDefaultHtmlOptionList<CharacterEquipmentType>();
    String sOptionList_ItemTreeType = MakeDefaultHtmlOptionList<ItemTreeType>();
    String sOptionList_FileType = MakeDefaultHtmlOptionList<FileType>();

    // Set page content
    String sPage = GetPageTemplate();
    BoostReplaceAll(sPage, "%sOptionList_CharacterPartyType%", sOptionList_CharacterPartyType);
    BoostReplaceAll(sPage, "%sOptionList_CharacterResolvedTargetType%", sOptionList_CharacterResolvedTargetType);
    BoostReplaceAll(sPage, "%sOptionList_CharacterEquipmentType%", sOptionList_CharacterEquipmentType);
    BoostReplaceAll(sPage, "%sOptionList_ItemTreeType%", sOptionList_ItemTreeType);
    BoostReplaceAll(sPage, "%sOptionList_FileType%", sOptionList_FileType);
    BoostReplaceAll(sPage, "%sLoadPartyFromJson_Textarea%", sLoadPartyFromJson_Textarea);
    BoostReplaceAll(sPage, "%sLoadPartyFromFile_Filename%", sLoadPartyFromFile_Filename);
    BoostReplaceAll(sPage, "%sSavePartyToFile_PartyID%", sSavePartyToFile_PartyID);
    BoostReplaceAll(sPage, "%sSavePartyToFile_Filename%", sSavePartyToFile_Filename);
    BoostReplaceAll(sPage, "%sUnloadParty_PartyID%", sUnloadParty_PartyID);
    BoostReplaceAll(sPage, "%sSetCurrentParty_PartyID%", sSetCurrentParty_PartyID);
    BoostReplaceAll(sPage, "%sCreateParty_PartyID%", sCreateParty_PartyID);
    BoostReplaceAll(sPage, "%sCreateParty_SetAsCurrent%", sCreateParty_SetAsCurrent);
    BoostReplaceAll(sPage, "%sAddMember_PartyID%", sAddMember_PartyID);
    BoostReplaceAll(sPage, "%sAddMember_CharID%", sAddMember_CharID);
    BoostReplaceAll(sPage, "%sRemoveMember_PartyID%", sRemoveMember_PartyID);
    BoostReplaceAll(sPage, "%sRemoveMember_CharID%", sRemoveMember_CharID);
    BoostReplaceAll(sPage, "%sMoveMember_PartyID%", sMoveMember_PartyID);
    BoostReplaceAll(sPage, "%sMoveMember_CharID%", sMoveMember_CharID);
    BoostReplaceAll(sPage, "%sSwapMember_PartyID%", sSwapMember_PartyID);
    BoostReplaceAll(sPage, "%sSwapMember_First_CharID%", sSwapMember_First_CharID);
    BoostReplaceAll(sPage, "%sSwapMember_Second_CharID%", sSwapMember_Second_CharID);
    BoostReplaceAll(sPage, "%sAddItem_PartyID%", sAddItem_PartyID);
    BoostReplaceAll(sPage, "%sAddItem_ItemName%", sAddItem_ItemName);
    BoostReplaceAll(sPage, "%sAddItem_ItemAmount%", sAddItem_ItemAmount);
    BoostReplaceAll(sPage, "%sAddRandomItems_PartyID%", sAddRandomItems_PartyID);
    BoostReplaceAll(sPage, "%sAddRandomItems_ItemCount%", sAddRandomItems_ItemCount);
    BoostReplaceAll(sPage, "%sAddRandomItems_ItemAmount%", sAddRandomItems_ItemAmount);
    BoostReplaceAll(sPage, "%sRemoveItem_PartyID%", sRemoveItem_PartyID);
    BoostReplaceAll(sPage, "%sRemoveItem_ItemName%", sRemoveItem_ItemName);
    BoostReplaceAll(sPage, "%sRemoveItem_ItemAmount%", sRemoveItem_ItemAmount);
    BoostReplaceAll(sPage, "%sEquipItem_PartyID%", sEquipItem_PartyID);
    BoostReplaceAll(sPage, "%sEquipItem_CharID%", sEquipItem_CharID);
    BoostReplaceAll(sPage, "%sEquipItem_ItemName%", sEquipItem_ItemName);
    BoostReplaceAll(sPage, "%sUnequipItem_PartyID%", sUnequipItem_PartyID);
    BoostReplaceAll(sPage, "%sUnequipItem_CharID%", sUnequipItem_CharID);
    BoostReplaceAll(sPage, "%sUnequipItem_ItemName%", sUnequipItem_ItemName);
    BoostReplaceAll(sPage, "%sEquipBestItems_PartyID%", sEquipBestItems_PartyID);
    BoostReplaceAll(sPage, "%sEquipBestItems_CharID%", sEquipBestItems_CharID);
    BoostReplaceAll(sPage, "%sUnequipBestItems_PartyID%", sUnequipBestItems_PartyID);
    BoostReplaceAll(sPage, "%sUnequipBestItems_CharID%", sUnequipBestItems_CharID);
    BoostReplaceAll(sPage, "%sEquipBestItemsAllMembers_PartyID%", sEquipBestItemsAllMembers_PartyID);
    BoostReplaceAll(sPage, "%sUnequipBestItemsAllMembers_PartyID%", sUnequipBestItemsAllMembers_PartyID);
    BoostReplaceAll(sPage, "%sDisplayParty_PartyID%", sDisplayParty_PartyID);
    BoostReplaceAll(sPage, "%sAllPartyIDs%", sAllPartyIDs);
    BoostReplaceAll(sPage, "%sCurrentParty_Ally%", sCurrentParty_Ally);
    BoostReplaceAll(sPage, "%sCurrentParty_Enemy%", sCurrentParty_Enemy);
    BoostReplaceAll(sPage, "%sPartyDetails_PartyID%", sPartyDetails_PartyID);
    BoostReplaceAll(sPage, "%sPartyDetails_PartyType%", sPartyDetails_PartyType);
    BoostReplaceAll(sPage, "%sPartyDetails_PlayTime%", sPartyDetails_PlayTime);
    BoostReplaceAll(sPage, "%sPartyDetails_TakenTargetTypes%", sPartyDetails_TakenTargetTypes);
    BoostReplaceAll(sPage, "%sPartyDetails_AvailableTargetTypes%", sPartyDetails_AvailableTargetTypes);
    BoostReplaceAll(sPage, "%sPartyDetails_Members%", sPartyDetails_Members);
    BoostReplaceAll(sPage, "%sPartyDetails_Items%", sPartyDetails_Items);
    BoostReplaceAll(sPage, "%sPartyDetails_Description%", sPartyDetails_Description);
    SetPageContent(sPage);
}

};
