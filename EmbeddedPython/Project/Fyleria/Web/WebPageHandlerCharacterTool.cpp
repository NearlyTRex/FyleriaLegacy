// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

// Internal includes
#include "Config/ConfigManager.h"
#include "Web/WebPageHandlerCharacterTool.h"
#include "Character/CharacterManager.h"
#include "Character/CharacterTypes.h"
#include "Utility/Constants.h"
#include "Utility/Converters.h"
#include "Utility/Templates.h"

namespace Gecko
{

WebPageHandlerCharacterTool::WebPageHandlerCharacterTool()
    : WebPageHandler()
{
    // Set template
    String sTemplateFile = JoinPathsCanonical(GetDataDirectory(), PAGE_FILE_TOOL_CHARACTER);
    String sTemplateContents = GetFileContentsAsString(sTemplateFile);
    SetPageTemplate(sTemplateContents);

    // Update page
    UpdatePageContent({});
}

WebPageHandlerCharacterTool::~WebPageHandlerCharacterTool()
{
}

void WebPageHandlerCharacterTool::UpdatePageContent(const StringMap& tParams)
{
    // Get fields
    String sAction = GetMapDataOrDefault(tParams, "action", "");
    String sLoadCharacterFromJson_Textarea = GetMapDataOrDefault(tParams, "sLoadCharacterFromJson_Textarea", "");
    String sLoadCharacterFromFile_Filename = GetMapDataOrDefault(tParams, "sLoadCharacterFromFile_Filename", "");
    String sLoadCharacterFromFile_FileType = GetMapDataOrDefault(tParams, "sLoadCharacterFromFile_FileType", "");
    String sSaveCharacterToFile_CharID = GetMapDataOrDefault(tParams, "sSaveCharacterToFile_CharID", "");
    String sSaveCharacterToFile_Filename = GetMapDataOrDefault(tParams, "sSaveCharacterToFile_Filename", "");
    String sSaveCharacterToFile_FileType = GetMapDataOrDefault(tParams, "sSaveCharacterToFile_FileType", "");
    String sUnloadCharacter_CharID = GetMapDataOrDefault(tParams, "sUnloadCharacter_CharID", "");
    String sGenerateCharacter_CharID = GetMapDataOrDefault(tParams, "sGenerateCharacter_CharID", "");
    String sGenerateCharacter_Textarea = GetMapDataOrDefault(tParams, "sGenerateCharacter_Textarea", "");
    String sGenerateRandomCharacter_CharID = GetMapDataOrDefault(tParams, "sGenerateRandomCharacter_CharID", "");
    String sRegenerateCharacterData_CharID = GetMapDataOrDefault(tParams, "sRegenerateCharacterData_CharID", "");
    String sCreateCharacter_CharID = GetMapDataOrDefault(tParams, "sCreateCharacter_CharID", "");
    String sDisplayCharacter_CharID = GetMapDataOrDefault(tParams, "sDisplayCharacter_CharID", "");
    String sCharacterDetails_CharID = GetMapDataOrDefault(tParams, "sCharacterDetails_CharID", "");
    String sCharacterDetails_First_Name = GetMapDataOrDefault(tParams, "sCharacterDetails_First_Name", "");
    String sCharacterDetails_Last_Name = GetMapDataOrDefault(tParams, "sCharacterDetails_Last_Name", "");
    String sCharacterDetails_Age = GetMapDataOrDefault(tParams, "sCharacterDetails_Age", "");
    String sCharacterDetails_Gender = GetMapDataOrDefault(tParams, "sCharacterDetails_Gender", "");
    String sCharacterDetails_Hair = GetMapDataOrDefault(tParams, "sCharacterDetails_Hair", "");
    String sCharacterDetails_Eyes = GetMapDataOrDefault(tParams, "sCharacterDetails_Eyes", "");
    String sCharacterDetails_Handedness = GetMapDataOrDefault(tParams, "sCharacterDetails_Handedness", "");
    String sCharacterDetails_PowerSet = GetMapDataOrDefault(tParams, "sCharacterDetails_PowerSet", "");
    String sCharacterDetails_BaseRace = GetMapDataOrDefault(tParams, "sCharacterDetails_BaseRace", "");
    String sCharacterDetails_TransformedRace = GetMapDataOrDefault(tParams, "sCharacterDetails_TransformedRace", "");
    String sCharacterDetails_WeaponSet = GetMapDataOrDefault(tParams, "sCharacterDetails_WeaponSet", "");
    String sCharacterDetails_HP_Current = GetMapDataOrDefault(tParams, "sCharacterDetails_HP_Current", "");
    String sCharacterDetails_HP_Max = GetMapDataOrDefault(tParams, "sCharacterDetails_HP_Max", "");
    String sCharacterDetails_HP_Regen = GetMapDataOrDefault(tParams, "sCharacterDetails_HP_Regen", "");
    String sCharacterDetails_HP_Delta = GetMapDataOrDefault(tParams, "sCharacterDetails_HP_Delta", "");
    String sCharacterDetails_MP_Current = GetMapDataOrDefault(tParams, "sCharacterDetails_MP_Current", "");
    String sCharacterDetails_MP_Max = GetMapDataOrDefault(tParams, "sCharacterDetails_MP_Max", "");
    String sCharacterDetails_MP_Regen = GetMapDataOrDefault(tParams, "sCharacterDetails_MP_Regen", "");
    String sCharacterDetails_MP_Delta = GetMapDataOrDefault(tParams, "sCharacterDetails_MP_Delta", "");
    String sCharacterDetails_EP_Current = GetMapDataOrDefault(tParams, "sCharacterDetails_EP_Current", "");
    String sCharacterDetails_EP_Max = GetMapDataOrDefault(tParams, "sCharacterDetails_EP_Max", "");
    String sCharacterDetails_EP_Regen = GetMapDataOrDefault(tParams, "sCharacterDetails_EP_Regen", "");
    String sCharacterDetails_EP_Delta = GetMapDataOrDefault(tParams, "sCharacterDetails_EP_Delta", "");
    String sCharacterDetails_Speed = GetMapDataOrDefault(tParams, "sCharacterDetails_Speed", "");
    String sCharacterDetails_Slash_ActionPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Slash_ActionPoints", "");
    String sCharacterDetails_Sever_ActionPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Sever_ActionPoints", "");
    String sCharacterDetails_Slice_ActionPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Slice_ActionPoints", "");
    String sCharacterDetails_Slit_ActionPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Slit_ActionPoints", "");
    String sCharacterDetails_Cleave_ActionPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Cleave_ActionPoints", "");
    String sCharacterDetails_Decapitate_ActionPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Decapitate_ActionPoints", "");
    String sCharacterDetails_Parry_ActionPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Parry_ActionPoints", "");
    String sCharacterDetails_Riposte_ActionPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Riposte_ActionPoints", "");
    String sCharacterDetails_Bash_ActionPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Bash_ActionPoints", "");
    String sCharacterDetails_Smash_ActionPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Smash_ActionPoints", "");
    String sCharacterDetails_Crush_ActionPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Crush_ActionPoints", "");
    String sCharacterDetails_Impact_ActionPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Impact_ActionPoints", "");
    String sCharacterDetails_Break_ActionPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Break_ActionPoints", "");
    String sCharacterDetails_Crack_ActionPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Crack_ActionPoints", "");
    String sCharacterDetails_Block_ActionPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Block_ActionPoints", "");
    String sCharacterDetails_Rush_ActionPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Rush_ActionPoints", "");
    String sCharacterDetails_Pierce_ActionPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Pierce_ActionPoints", "");
    String sCharacterDetails_Drill_ActionPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Drill_ActionPoints", "");
    String sCharacterDetails_Shoot_ActionPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Shoot_ActionPoints", "");
    String sCharacterDetails_Impale_ActionPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Impale_ActionPoints", "");
    String sCharacterDetails_StealthStrike_ActionPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_StealthStrike_ActionPoints", "");
    String sCharacterDetails_CriticalShot_ActionPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_CriticalShot_ActionPoints", "");
    String sCharacterDetails_Dodge_ActionPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Dodge_ActionPoints", "");
    String sCharacterDetails_Counter_ActionPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Counter_ActionPoints", "");
    String sCharacterDetails_Blunt_Attack = GetMapDataOrDefault(tParams, "sCharacterDetails_Blunt_Attack", "");
    String sCharacterDetails_Blunt_Defense = GetMapDataOrDefault(tParams, "sCharacterDetails_Blunt_Defense", "");
    String sCharacterDetails_Pierce_Attack = GetMapDataOrDefault(tParams, "sCharacterDetails_Pierce_Attack", "");
    String sCharacterDetails_Pierce_Defense = GetMapDataOrDefault(tParams, "sCharacterDetails_Pierce_Defense", "");
    String sCharacterDetails_Slash_Attack = GetMapDataOrDefault(tParams, "sCharacterDetails_Slash_Attack", "");
    String sCharacterDetails_Slash_Defense = GetMapDataOrDefault(tParams, "sCharacterDetails_Slash_Defense", "");
    String sCharacterDetails_Magic_Attack = GetMapDataOrDefault(tParams, "sCharacterDetails_Magic_Attack", "");
    String sCharacterDetails_Magic_Defense = GetMapDataOrDefault(tParams, "sCharacterDetails_Magic_Defense", "");
    String sCharacterDetails_Energy_Attack = GetMapDataOrDefault(tParams, "sCharacterDetails_Energy_Attack", "");
    String sCharacterDetails_Energy_Defense = GetMapDataOrDefault(tParams, "sCharacterDetails_Energy_Defense", "");
    String sCharacterDetails_Slash_SkillPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Slash_SkillPoints", "");
    String sCharacterDetails_Sever_SkillPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Sever_SkillPoints", "");
    String sCharacterDetails_Slice_SkillPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Slice_SkillPoints", "");
    String sCharacterDetails_Slit_SkillPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Slit_SkillPoints", "");
    String sCharacterDetails_Cleave_SkillPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Cleave_SkillPoints", "");
    String sCharacterDetails_Decapitate_SkillPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Decapitate_SkillPoints", "");
    String sCharacterDetails_Parry_SkillPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Parry_SkillPoints", "");
    String sCharacterDetails_Riposte_SkillPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Riposte_SkillPoints", "");
    String sCharacterDetails_Bash_SkillPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Bash_SkillPoints", "");
    String sCharacterDetails_Smash_SkillPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Smash_SkillPoints", "");
    String sCharacterDetails_Crush_SkillPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Crush_SkillPoints", "");
    String sCharacterDetails_Impact_SkillPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Impact_SkillPoints", "");
    String sCharacterDetails_Break_SkillPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Break_SkillPoints", "");
    String sCharacterDetails_Crack_SkillPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Crack_SkillPoints", "");
    String sCharacterDetails_Block_SkillPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Block_SkillPoints", "");
    String sCharacterDetails_Rush_SkillPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Rush_SkillPoints", "");
    String sCharacterDetails_Pierce_SkillPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Pierce_SkillPoints", "");
    String sCharacterDetails_Drill_SkillPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Drill_SkillPoints", "");
    String sCharacterDetails_Shoot_SkillPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Shoot_SkillPoints", "");
    String sCharacterDetails_Impale_SkillPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Impale_SkillPoints", "");
    String sCharacterDetails_StealthStrike_SkillPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_StealthStrike_SkillPoints", "");
    String sCharacterDetails_CriticalShot_SkillPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_CriticalShot_SkillPoints", "");
    String sCharacterDetails_Dodge_SkillPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Dodge_SkillPoints", "");
    String sCharacterDetails_Counter_SkillPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Counter_SkillPoints", "");
    String sCharacterDetails_Barbarian_SkillPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Barbarian_SkillPoints", "");
    String sCharacterDetails_Mage_SkillPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Mage_SkillPoints", "");
    String sCharacterDetails_Rogue_SkillPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Rogue_SkillPoints", "");
    String sCharacterDetails_Blademaster_SkillPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Blademaster_SkillPoints", "");
    String sCharacterDetails_Avatar_SkillPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Avatar_SkillPoints", "");
    String sCharacterDetails_Ambidext_SkillPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Ambidext_SkillPoints", "");
    String sCharacterDetails_Focused_SkillPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Focused_SkillPoints", "");
    String sCharacterDetails_Stalwart_SkillPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Stalwart_SkillPoints", "");
    String sCharacterDetails_Healer_SkillPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Healer_SkillPoints", "");
    String sCharacterDetails_Alchemist_SkillPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Alchemist_SkillPoints", "");
    String sCharacterDetails_Energist_SkillPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Energist_SkillPoints", "");
    String sCharacterDetails_Chemist_SkillPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Chemist_SkillPoints", "");
    String sCharacterDetails_Hammersmith_SkillPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Hammersmith_SkillPoints", "");
    String sCharacterDetails_Spellsmith_SkillPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Spellsmith_SkillPoints", "");
    String sCharacterDetails_Bowsmith_SkillPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Bowsmith_SkillPoints", "");
    String sCharacterDetails_Swordsmith_SkillPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Swordsmith_SkillPoints", "");
    String sCharacterDetails_Weaver_SkillPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Weaver_SkillPoints", "");
    String sCharacterDetails_Tanner_SkillPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Tanner_SkillPoints", "");
    String sCharacterDetails_Scalesmith_SkillPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Scalesmith_SkillPoints", "");
    String sCharacterDetails_Platesmith_SkillPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Platesmith_SkillPoints", "");
    String sCharacterDetails_Goldsmith_SkillPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Goldsmith_SkillPoints", "");
    String sCharacterDetails_Shieldsmith_SkillPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Shieldsmith_SkillPoints", "");
    String sCharacterDetails_Hammerbane_SkillPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Hammerbane_SkillPoints", "");
    String sCharacterDetails_Spellbane_SkillPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Spellbane_SkillPoints", "");
    String sCharacterDetails_Bowbane_SkillPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Bowbane_SkillPoints", "");
    String sCharacterDetails_Swordbane_SkillPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Swordbane_SkillPoints", "");
    String sCharacterDetails_Threadbare_SkillPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Threadbare_SkillPoints", "");
    String sCharacterDetails_Studremover_SkillPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Studremover_SkillPoints", "");
    String sCharacterDetails_Scalebane_SkillPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Scalebane_SkillPoints", "");
    String sCharacterDetails_Platebane_SkillPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Platebane_SkillPoints", "");
    String sCharacterDetails_Goldbane_SkillPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Goldbane_SkillPoints", "");
    String sCharacterDetails_Shieldbane_SkillPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Shieldbane_SkillPoints", "");
    String sCharacterDetails_Holy_SkillPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Holy_SkillPoints", "");
    String sCharacterDetails_Fire_SkillPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Fire_SkillPoints", "");
    String sCharacterDetails_Ice_SkillPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Ice_SkillPoints", "");
    String sCharacterDetails_Shock_SkillPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Shock_SkillPoints", "");
    String sCharacterDetails_Dark_SkillPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Dark_SkillPoints", "");
    String sCharacterDetails_Light_SkillPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Light_SkillPoints", "");
    String sCharacterDetails_Force_SkillPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Force_SkillPoints", "");
    String sCharacterDetails_Mind_SkillPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Mind_SkillPoints", "");
    String sCharacterDetails_Earth_SkillPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Earth_SkillPoints", "");
    String sCharacterDetails_Blood_SkillPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Blood_SkillPoints", "");
    String sCharacterDetails_Flesh_SkillPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Flesh_SkillPoints", "");
    String sCharacterDetails_Wind_SkillPoints = GetMapDataOrDefault(tParams, "sCharacterDetails_Wind_SkillPoints", "");

    // Character details
    String sCharacterDetails_PartyID;
    String sCharacterDetails_CharTargetType;
    String sCharacterDetails_Chest;
    String sCharacterDetails_Feet;
    String sCharacterDetails_Hands;
    String sCharacterDetails_Head;
    String sCharacterDetails_Legs;
    String sCharacterDetails_Neck;
    String sCharacterDetails_LeftFingers;
    String sCharacterDetails_RightFingers;
    String sCharacterDetails_Weapon1Left;
    String sCharacterDetails_Weapon1Right;
    String sCharacterDetails_Weapon2Left;
    String sCharacterDetails_Weapon2Right;
    String sCharacterDetails_AvailableActions;
    String sCharacterDetails_SkillPassiveChanges;
    String sCharacterDetails_ItemPassiveChanges;
    String sCharacterDetails_SkillActiveChanges;
    String sCharacterDetails_ItemActiveChanges;
    String sCharacterDetails_SkillActionableChanges;
    String sCharacterDetails_ItemActionableChanges;
    String sCharacterDetails_RawJson;

    // Character to display
    String sCharacterToDisplay;

    // Check action
    if(sAction == "load_character_from_json")
    {
        sCharacterToDisplay = CharacterManager::GetInstance()->LoadCharacter(
            Character(sLoadCharacterFromJson_Textarea), true
        );
    }
    else if(sAction == "load_character_from_file")
    {
        sCharacterToDisplay = CharacterManager::GetInstance()->LoadCharacterFromFile(
            sLoadCharacterFromFile_Filename, sLoadCharacterFromFile_FileType, true
        );
    }
    else if(sAction == "save_character_to_file")
    {
        CharacterManager::GetInstance()->SaveCharacterToFile(
            sSaveCharacterToFile_CharID,
            sSaveCharacterToFile_Filename,
            sSaveCharacterToFile_FileType
        );
        sCharacterToDisplay = sSaveCharacterToFile_CharID;
    }
    else if(sAction == "unload_character")
    {
        CharacterManager::GetInstance()->UnloadCharacter(
            sUnloadCharacter_CharID
        );
        sCharacterToDisplay = sUnloadCharacter_CharID;
    }
    else if(sAction == "generate_character")
    {
        CharacterManager::GetInstance()->GenerateCharacter(
            sGenerateCharacter_CharID,
            CharacterGenerator(sGenerateCharacter_Textarea)
        );
        sCharacterToDisplay = sGenerateCharacter_CharID;
    }
    else if(sAction == "generate_random_character")
    {
        CharacterGenerator generator;
        generator.RandomizeAll();
        CharacterManager::GetInstance()->GenerateCharacter(
            sGenerateRandomCharacter_CharID,
            generator
        );
        sCharacterToDisplay = sGenerateRandomCharacter_CharID;
    }
    else if(sAction == "regenerate_character_data")
    {
        Character& character = CharacterManager::GetInstance()->GetCharacter(sRegenerateCharacterData_CharID);
        character.RegenerateCharacterData();
        sCharacterToDisplay = sRegenerateCharacterData_CharID;
    }
    else if(sAction == "create_character")
    {
        CharacterManager::GetInstance()->CreateCharacter(
            sCreateCharacter_CharID
        );
        sCharacterToDisplay = sCreateCharacter_CharID;
    }
    else if(sAction == "display_character")
    {
        sCharacterToDisplay = sDisplayCharacter_CharID;
    }
    else if(sAction == "save_character")
    {
        Character& character = CharacterManager::GetInstance()->GetCharacter(sCharacterDetails_CharID);
        CharacterActionData& actionData = character.GetActionData();
        actionData.SetSlashPoints(BoostLexicalCast<Int>(sCharacterDetails_Slash_ActionPoints));
        actionData.SetSeverPoints(BoostLexicalCast<Int>(sCharacterDetails_Sever_ActionPoints));
        actionData.SetSlicePoints(BoostLexicalCast<Int>(sCharacterDetails_Slice_ActionPoints));
        actionData.SetSlitPoints(BoostLexicalCast<Int>(sCharacterDetails_Slit_ActionPoints));
        actionData.SetCleavePoints(BoostLexicalCast<Int>(sCharacterDetails_Cleave_ActionPoints));
        actionData.SetDecapitatePoints(BoostLexicalCast<Int>(sCharacterDetails_Decapitate_ActionPoints));
        actionData.SetParryPoints(BoostLexicalCast<Int>(sCharacterDetails_Parry_ActionPoints));
        actionData.SetRipostePoints(BoostLexicalCast<Int>(sCharacterDetails_Riposte_ActionPoints));
        actionData.SetBashPoints(BoostLexicalCast<Int>(sCharacterDetails_Bash_ActionPoints));
        actionData.SetSmashPoints(BoostLexicalCast<Int>(sCharacterDetails_Smash_ActionPoints));
        actionData.SetImpactPoints(BoostLexicalCast<Int>(sCharacterDetails_Impact_ActionPoints));
        actionData.SetCrushPoints(BoostLexicalCast<Int>(sCharacterDetails_Crush_ActionPoints));
        actionData.SetBreakPoints(BoostLexicalCast<Int>(sCharacterDetails_Break_ActionPoints));
        actionData.SetCrackPoints(BoostLexicalCast<Int>(sCharacterDetails_Crack_ActionPoints));
        actionData.SetBlockPoints(BoostLexicalCast<Int>(sCharacterDetails_Block_ActionPoints));
        actionData.SetRushPoints(BoostLexicalCast<Int>(sCharacterDetails_Rush_ActionPoints));
        actionData.SetPiercePoints(BoostLexicalCast<Int>(sCharacterDetails_Pierce_ActionPoints));
        actionData.SetDrillPoints(BoostLexicalCast<Int>(sCharacterDetails_Drill_ActionPoints));
        actionData.SetShootPoints(BoostLexicalCast<Int>(sCharacterDetails_Shoot_ActionPoints));
        actionData.SetImpalePoints(BoostLexicalCast<Int>(sCharacterDetails_Impale_ActionPoints));
        actionData.SetStealthStrikePoints(BoostLexicalCast<Int>(sCharacterDetails_StealthStrike_ActionPoints));
        actionData.SetCriticalShotPoints(BoostLexicalCast<Int>(sCharacterDetails_CriticalShot_ActionPoints));
        actionData.SetDodgePoints(BoostLexicalCast<Int>(sCharacterDetails_Dodge_ActionPoints));
        actionData.SetCounterPoints(BoostLexicalCast<Int>(sCharacterDetails_Counter_ActionPoints));
        CharacterBasicData& basicData = character.GetBasicData();
        basicData.SetFirstName(sCharacterDetails_First_Name);
        basicData.SetLastName(sCharacterDetails_Last_Name);
        basicData.SetGender(sCharacterDetails_Gender);
        basicData.SetHair(sCharacterDetails_Hair);
        basicData.SetEyes(sCharacterDetails_Eyes);
        basicData.SetHandedness(sCharacterDetails_Handedness);
        basicData.SetBaseRace(sCharacterDetails_BaseRace);
        basicData.SetTransformedRace(sCharacterDetails_TransformedRace);
        basicData.SetPowerSet(sCharacterDetails_PowerSet);
        basicData.SetWeaponSet(sCharacterDetails_WeaponSet);
        basicData.SetAge(BoostLexicalCast<Int>(sCharacterDetails_Age));
        CharacterProgressData& progressData = character.GetProgressData();
        progressData.SetHealthPointsCurrent(BoostLexicalCast<Int>(sCharacterDetails_HP_Current));
        progressData.SetMagicPointsCurrent(BoostLexicalCast<Int>(sCharacterDetails_MP_Current));
        progressData.SetEnergyPointsCurrent(BoostLexicalCast<Int>(sCharacterDetails_EP_Current));
        progressData.SetHealthPointsMax(BoostLexicalCast<Int>(sCharacterDetails_HP_Max));
        progressData.SetMagicPointsMax(BoostLexicalCast<Int>(sCharacterDetails_MP_Max));
        progressData.SetEnergyPointsMax(BoostLexicalCast<Int>(sCharacterDetails_EP_Max));
        progressData.SetHealthRegen(BoostLexicalCast<Int>(sCharacterDetails_HP_Regen));
        progressData.SetMagicRegen(BoostLexicalCast<Int>(sCharacterDetails_MP_Regen));
        progressData.SetEnergyRegen(BoostLexicalCast<Int>(sCharacterDetails_EP_Regen));
        progressData.SetHealthCostDelta(BoostLexicalCast<Int>(sCharacterDetails_HP_Delta));
        progressData.SetMagicCostDelta(BoostLexicalCast<Int>(sCharacterDetails_MP_Delta));
        progressData.SetEnergyCostDelta(BoostLexicalCast<Int>(sCharacterDetails_EP_Delta));
        progressData.SetSpeed(BoostLexicalCast<Int>(sCharacterDetails_Speed));
        progressData.SetBluntAttack(BoostLexicalCast<Int>(sCharacterDetails_Blunt_Attack));
        progressData.SetBluntDefense(BoostLexicalCast<Int>(sCharacterDetails_Blunt_Defense));
        progressData.SetMagicAttack(BoostLexicalCast<Int>(sCharacterDetails_Magic_Attack));
        progressData.SetMagicDefense(BoostLexicalCast<Int>(sCharacterDetails_Magic_Defense));
        progressData.SetPierceAttack(BoostLexicalCast<Int>(sCharacterDetails_Pierce_Attack));
        progressData.SetPierceDefense(BoostLexicalCast<Int>(sCharacterDetails_Pierce_Defense));
        progressData.SetSlashAttack(BoostLexicalCast<Int>(sCharacterDetails_Slash_Attack));
        progressData.SetSlashDefense(BoostLexicalCast<Int>(sCharacterDetails_Slash_Defense));
        progressData.SetEnergyAttack(BoostLexicalCast<Int>(sCharacterDetails_Energy_Attack));
        progressData.SetEnergyDefense(BoostLexicalCast<Int>(sCharacterDetails_Energy_Defense));
        CharacterSkillData& skillData = character.GetSkillData();
        skillData.SetBarbarian(BoostLexicalCast<Byte>(sCharacterDetails_Barbarian_SkillPoints));
        skillData.SetMage(BoostLexicalCast<Byte>(sCharacterDetails_Mage_SkillPoints));
        skillData.SetRogue(BoostLexicalCast<Byte>(sCharacterDetails_Rogue_SkillPoints));
        skillData.SetBlademaster(BoostLexicalCast<Byte>(sCharacterDetails_Blademaster_SkillPoints));
        skillData.SetAvatar(BoostLexicalCast<Byte>(sCharacterDetails_Avatar_SkillPoints));
        skillData.SetAmbidextrous(BoostLexicalCast<Byte>(sCharacterDetails_Ambidext_SkillPoints));
        skillData.SetFocused(BoostLexicalCast<Byte>(sCharacterDetails_Focused_SkillPoints));
        skillData.SetStalwart(BoostLexicalCast<Byte>(sCharacterDetails_Stalwart_SkillPoints));
        skillData.SetSlash(BoostLexicalCast<Byte>(sCharacterDetails_Slash_SkillPoints));
        skillData.SetSever(BoostLexicalCast<Byte>(sCharacterDetails_Sever_SkillPoints));
        skillData.SetSlice(BoostLexicalCast<Byte>(sCharacterDetails_Slice_SkillPoints));
        skillData.SetSlit(BoostLexicalCast<Byte>(sCharacterDetails_Slit_SkillPoints));
        skillData.SetCleave(BoostLexicalCast<Byte>(sCharacterDetails_Cleave_SkillPoints));
        skillData.SetDecapitate(BoostLexicalCast<Byte>(sCharacterDetails_Decapitate_SkillPoints));
        skillData.SetParry(BoostLexicalCast<Byte>(sCharacterDetails_Parry_SkillPoints));
        skillData.SetRiposte(BoostLexicalCast<Byte>(sCharacterDetails_Riposte_SkillPoints));
        skillData.SetBash(BoostLexicalCast<Byte>(sCharacterDetails_Bash_SkillPoints));
        skillData.SetSmash(BoostLexicalCast<Byte>(sCharacterDetails_Smash_SkillPoints));
        skillData.SetCrush(BoostLexicalCast<Byte>(sCharacterDetails_Crush_SkillPoints));
        skillData.SetImpact(BoostLexicalCast<Byte>(sCharacterDetails_Impact_SkillPoints));
        skillData.SetBreak(BoostLexicalCast<Byte>(sCharacterDetails_Break_SkillPoints));
        skillData.SetCrack(BoostLexicalCast<Byte>(sCharacterDetails_Crack_SkillPoints));
        skillData.SetBlock(BoostLexicalCast<Byte>(sCharacterDetails_Block_SkillPoints));
        skillData.SetRush(BoostLexicalCast<Byte>(sCharacterDetails_Rush_SkillPoints));
        skillData.SetPierce(BoostLexicalCast<Byte>(sCharacterDetails_Pierce_SkillPoints));
        skillData.SetDrill(BoostLexicalCast<Byte>(sCharacterDetails_Drill_SkillPoints));
        skillData.SetShoot(BoostLexicalCast<Byte>(sCharacterDetails_Shoot_SkillPoints));
        skillData.SetImpale(BoostLexicalCast<Byte>(sCharacterDetails_Impale_SkillPoints));
        skillData.SetStealthStrike(BoostLexicalCast<Byte>(sCharacterDetails_StealthStrike_SkillPoints));
        skillData.SetCriticalShot(BoostLexicalCast<Byte>(sCharacterDetails_CriticalShot_SkillPoints));
        skillData.SetDodge(BoostLexicalCast<Byte>(sCharacterDetails_Dodge_SkillPoints));
        skillData.SetCounter(BoostLexicalCast<Byte>(sCharacterDetails_Counter_SkillPoints));
        skillData.SetHealer(BoostLexicalCast<Byte>(sCharacterDetails_Healer_SkillPoints));
        skillData.SetAlchemist(BoostLexicalCast<Byte>(sCharacterDetails_Alchemist_SkillPoints));
        skillData.SetEnergist(BoostLexicalCast<Byte>(sCharacterDetails_Energist_SkillPoints));
        skillData.SetChemist(BoostLexicalCast<Byte>(sCharacterDetails_Chemist_SkillPoints));
        skillData.SetHammersmith(BoostLexicalCast<Byte>(sCharacterDetails_Hammersmith_SkillPoints));
        skillData.SetSpellsmith(BoostLexicalCast<Byte>(sCharacterDetails_Spellsmith_SkillPoints));
        skillData.SetBowsmith(BoostLexicalCast<Byte>(sCharacterDetails_Bowsmith_SkillPoints));
        skillData.SetSwordsmith(BoostLexicalCast<Byte>(sCharacterDetails_Swordsmith_SkillPoints));
        skillData.SetWeaver(BoostLexicalCast<Byte>(sCharacterDetails_Weaver_SkillPoints));
        skillData.SetTanner(BoostLexicalCast<Byte>(sCharacterDetails_Tanner_SkillPoints));
        skillData.SetScalesmith(BoostLexicalCast<Byte>(sCharacterDetails_Scalesmith_SkillPoints));
        skillData.SetPlatesmith(BoostLexicalCast<Byte>(sCharacterDetails_Platesmith_SkillPoints));
        skillData.SetGoldsmith(BoostLexicalCast<Byte>(sCharacterDetails_Goldsmith_SkillPoints));
        skillData.SetShieldsmith(BoostLexicalCast<Byte>(sCharacterDetails_Shieldsmith_SkillPoints));
        skillData.SetHammerbane(BoostLexicalCast<Byte>(sCharacterDetails_Hammerbane_SkillPoints));
        skillData.SetSpellbane(BoostLexicalCast<Byte>(sCharacterDetails_Spellbane_SkillPoints));
        skillData.SetBowbane(BoostLexicalCast<Byte>(sCharacterDetails_Bowbane_SkillPoints));
        skillData.SetSwordbane(BoostLexicalCast<Byte>(sCharacterDetails_Swordbane_SkillPoints));
        skillData.SetThreadbare(BoostLexicalCast<Byte>(sCharacterDetails_Threadbare_SkillPoints));
        skillData.SetStudRemover(BoostLexicalCast<Byte>(sCharacterDetails_Studremover_SkillPoints));
        skillData.SetScalebane(BoostLexicalCast<Byte>(sCharacterDetails_Scalebane_SkillPoints));
        skillData.SetPlatebane(BoostLexicalCast<Byte>(sCharacterDetails_Platebane_SkillPoints));
        skillData.SetGoldbane(BoostLexicalCast<Byte>(sCharacterDetails_Goldbane_SkillPoints));
        skillData.SetShieldbane(BoostLexicalCast<Byte>(sCharacterDetails_Shieldbane_SkillPoints));
        skillData.SetHoly(BoostLexicalCast<Byte>(sCharacterDetails_Holy_SkillPoints));
        skillData.SetFire(BoostLexicalCast<Byte>(sCharacterDetails_Fire_SkillPoints));
        skillData.SetIce(BoostLexicalCast<Byte>(sCharacterDetails_Ice_SkillPoints));
        skillData.SetShock(BoostLexicalCast<Byte>(sCharacterDetails_Shock_SkillPoints));
        skillData.SetDark(BoostLexicalCast<Byte>(sCharacterDetails_Dark_SkillPoints));
        skillData.SetLight(BoostLexicalCast<Byte>(sCharacterDetails_Light_SkillPoints));
        skillData.SetForce(BoostLexicalCast<Byte>(sCharacterDetails_Force_SkillPoints));
        skillData.SetMind(BoostLexicalCast<Byte>(sCharacterDetails_Mind_SkillPoints));
        skillData.SetEarth(BoostLexicalCast<Byte>(sCharacterDetails_Earth_SkillPoints));
        skillData.SetBlood(BoostLexicalCast<Byte>(sCharacterDetails_Blood_SkillPoints));
        skillData.SetFlesh(BoostLexicalCast<Byte>(sCharacterDetails_Flesh_SkillPoints));
        skillData.SetWind(BoostLexicalCast<Byte>(sCharacterDetails_Wind_SkillPoints));
        character.RegenerateCharacterData();
        sCharacterToDisplay = sCharacterDetails_CharID;
    }

    // Get all character IDs
    String sAllCharacterIDs = ConcatStringVector(CharacterManager::GetInstance()->GetAllCharacterIDs());

    // Display character
    if(!sCharacterToDisplay.empty())
    {
        const String sSkillTreeIndexType = (+CharacterTreeIndexType::Skill)._to_string();
        const String sItemTreeIndexType = (+CharacterTreeIndexType::Item)._to_string();
        const Character& character = CharacterManager::GetInstance()->GetCharacter(sCharacterToDisplay);
        sCharacterDetails_Chest = character.GetEquippedItemByType((+CharacterEquipmentType::Chest)._to_string()).GetLeaf();
        sCharacterDetails_Feet = character.GetEquippedItemByType((+CharacterEquipmentType::Feet)._to_string()).GetLeaf();
        sCharacterDetails_Hands = character.GetEquippedItemByType((+CharacterEquipmentType::Hands)._to_string()).GetLeaf();
        sCharacterDetails_Head = character.GetEquippedItemByType((+CharacterEquipmentType::Head)._to_string()).GetLeaf();
        sCharacterDetails_Legs = character.GetEquippedItemByType((+CharacterEquipmentType::Legs)._to_string()).GetLeaf();
        sCharacterDetails_Neck = character.GetEquippedItemByType((+CharacterEquipmentType::Neck)._to_string()).GetLeaf();
        sCharacterDetails_LeftFingers = character.GetEquippedItemByType((+CharacterEquipmentType::LeftFingers)._to_string()).GetLeaf();
        sCharacterDetails_RightFingers = character.GetEquippedItemByType((+CharacterEquipmentType::RightFingers)._to_string()).GetLeaf();
        sCharacterDetails_Weapon1Left = character.GetEquippedItemByType((+CharacterEquipmentType::Weapon1Left)._to_string()).GetLeaf();
        sCharacterDetails_Weapon1Right = character.GetEquippedItemByType((+CharacterEquipmentType::Weapon1Right)._to_string()).GetLeaf();
        sCharacterDetails_Weapon2Left = character.GetEquippedItemByType((+CharacterEquipmentType::Weapon2Left)._to_string()).GetLeaf();
        sCharacterDetails_Weapon2Right = character.GetEquippedItemByType((+CharacterEquipmentType::Weapon2Right)._to_string()).GetLeaf();
        const CharacterActionData& actionData = character.GetActionData();
        sCharacterDetails_Slash_ActionPoints = STDToString(actionData.GetSlashPoints());
        sCharacterDetails_Sever_ActionPoints = STDToString(actionData.GetSeverPoints());
        sCharacterDetails_Slice_ActionPoints = STDToString(actionData.GetSlicePoints());
        sCharacterDetails_Slit_ActionPoints = STDToString(actionData.GetSlitPoints());
        sCharacterDetails_Cleave_ActionPoints = STDToString(actionData.GetCleavePoints());
        sCharacterDetails_Decapitate_ActionPoints = STDToString(actionData.GetDecapitatePoints());
        sCharacterDetails_Parry_ActionPoints = STDToString(actionData.GetParryPoints());
        sCharacterDetails_Riposte_ActionPoints = STDToString(actionData.GetRipostePoints());
        sCharacterDetails_Bash_ActionPoints = STDToString(actionData.GetBashPoints());
        sCharacterDetails_Smash_ActionPoints = STDToString(actionData.GetSmashPoints());
        sCharacterDetails_Impact_ActionPoints = STDToString(actionData.GetImpactPoints());
        sCharacterDetails_Crush_ActionPoints = STDToString(actionData.GetCrushPoints());
        sCharacterDetails_Break_ActionPoints = STDToString(actionData.GetBreakPoints());
        sCharacterDetails_Crack_ActionPoints = STDToString(actionData.GetCrackPoints());
        sCharacterDetails_Block_ActionPoints = STDToString(actionData.GetBlockPoints());
        sCharacterDetails_Rush_ActionPoints = STDToString(actionData.GetRushPoints());
        sCharacterDetails_Pierce_ActionPoints = STDToString(actionData.GetPiercePoints());
        sCharacterDetails_Drill_ActionPoints = STDToString(actionData.GetDrillPoints());
        sCharacterDetails_Shoot_ActionPoints = STDToString(actionData.GetShootPoints());
        sCharacterDetails_Impale_ActionPoints = STDToString(actionData.GetImpalePoints());
        sCharacterDetails_StealthStrike_ActionPoints = STDToString(actionData.GetStealthStrikePoints());
        sCharacterDetails_CriticalShot_ActionPoints = STDToString(actionData.GetCriticalShotPoints());
        sCharacterDetails_Dodge_ActionPoints = STDToString(actionData.GetDodgePoints());
        sCharacterDetails_Counter_ActionPoints = STDToString(actionData.GetCounterPoints());
        const CharacterBasicData& basicData = character.GetBasicData();
        sCharacterDetails_First_Name = basicData.GetFirstName();
        sCharacterDetails_Last_Name = basicData.GetLastName();
        sCharacterDetails_Gender = basicData.GetGender();
        sCharacterDetails_Hair = basicData.GetHair();
        sCharacterDetails_Eyes = basicData.GetEyes();
        sCharacterDetails_Handedness = basicData.GetHandedness();
        sCharacterDetails_BaseRace = basicData.GetBaseRace();
        sCharacterDetails_TransformedRace = basicData.GetTransformedRace();
        sCharacterDetails_PowerSet = basicData.GetPowerSet();
        sCharacterDetails_WeaponSet = basicData.GetWeaponSet();
        sCharacterDetails_Age = STDToString(basicData.GetAge());
        const CharacterProgressData& progressData = character.GetProgressData();
        sCharacterDetails_HP_Current = STDToString(progressData.GetHealthPointsCurrent());
        sCharacterDetails_MP_Current = STDToString(progressData.GetMagicPointsCurrent());
        sCharacterDetails_EP_Current = STDToString(progressData.GetEnergyPointsCurrent());
        sCharacterDetails_HP_Max = STDToString(progressData.GetHealthPointsMax());
        sCharacterDetails_MP_Max = STDToString(progressData.GetMagicPointsMax());
        sCharacterDetails_EP_Max = STDToString(progressData.GetEnergyPointsMax());
        sCharacterDetails_HP_Regen = STDToString(progressData.GetHealthRegen());
        sCharacterDetails_MP_Regen = STDToString(progressData.GetMagicRegen());
        sCharacterDetails_EP_Regen = STDToString(progressData.GetEnergyRegen());
        sCharacterDetails_HP_Delta = STDToString(progressData.GetHealthCostDelta());
        sCharacterDetails_MP_Delta = STDToString(progressData.GetMagicCostDelta());
        sCharacterDetails_EP_Delta = STDToString(progressData.GetEnergyCostDelta());
        sCharacterDetails_Speed = STDToString(progressData.GetSpeed());
        sCharacterDetails_Blunt_Attack = STDToString(progressData.GetBluntAttack());
        sCharacterDetails_Blunt_Defense = STDToString(progressData.GetBluntDefense());
        sCharacterDetails_Magic_Attack = STDToString(progressData.GetMagicAttack());
        sCharacterDetails_Magic_Defense = STDToString(progressData.GetMagicDefense());
        sCharacterDetails_Pierce_Attack = STDToString(progressData.GetPierceAttack());
        sCharacterDetails_Pierce_Defense = STDToString(progressData.GetPierceDefense());
        sCharacterDetails_Slash_Attack = STDToString(progressData.GetSlashAttack());
        sCharacterDetails_Slash_Defense = STDToString(progressData.GetSlashDefense());
        sCharacterDetails_Energy_Attack = STDToString(progressData.GetEnergyAttack());
        sCharacterDetails_Energy_Defense = STDToString(progressData.GetEnergyDefense());

        const CharacterSkillData& skillData = character.GetSkillData();
        sCharacterDetails_Barbarian_SkillPoints = STDToString(skillData.GetBarbarian());
        sCharacterDetails_Mage_SkillPoints = STDToString(skillData.GetMage());
        sCharacterDetails_Rogue_SkillPoints = STDToString(skillData.GetRogue());
        sCharacterDetails_Blademaster_SkillPoints = STDToString(skillData.GetBlademaster());
        sCharacterDetails_Avatar_SkillPoints = STDToString(skillData.GetAvatar());
        sCharacterDetails_Ambidext_SkillPoints = STDToString(skillData.GetAmbidextrous());
        sCharacterDetails_Focused_SkillPoints = STDToString(skillData.GetFocused());
        sCharacterDetails_Stalwart_SkillPoints = STDToString(skillData.GetStalwart());
        sCharacterDetails_Slash_SkillPoints = STDToString(skillData.GetSlash());
        sCharacterDetails_Sever_SkillPoints = STDToString(skillData.GetSever());
        sCharacterDetails_Slice_SkillPoints = STDToString(skillData.GetSlice());
        sCharacterDetails_Slit_SkillPoints = STDToString(skillData.GetSlit());
        sCharacterDetails_Cleave_SkillPoints = STDToString(skillData.GetCleave());
        sCharacterDetails_Decapitate_SkillPoints = STDToString(skillData.GetDecapitate());
        sCharacterDetails_Parry_SkillPoints = STDToString(skillData.GetParry());
        sCharacterDetails_Riposte_SkillPoints = STDToString(skillData.GetRiposte());
        sCharacterDetails_Bash_SkillPoints = STDToString(skillData.GetBash());
        sCharacterDetails_Smash_SkillPoints = STDToString(skillData.GetSmash());
        sCharacterDetails_Crush_SkillPoints = STDToString(skillData.GetCrush());
        sCharacterDetails_Impact_SkillPoints = STDToString(skillData.GetImpact());
        sCharacterDetails_Break_SkillPoints = STDToString(skillData.GetBreak());
        sCharacterDetails_Crack_SkillPoints = STDToString(skillData.GetCrack());
        sCharacterDetails_Block_SkillPoints = STDToString(skillData.GetBlock());
        sCharacterDetails_Rush_SkillPoints = STDToString(skillData.GetRush());
        sCharacterDetails_Pierce_SkillPoints = STDToString(skillData.GetPierce());
        sCharacterDetails_Drill_SkillPoints = STDToString(skillData.GetDrill());
        sCharacterDetails_Shoot_SkillPoints = STDToString(skillData.GetShoot());
        sCharacterDetails_Impale_SkillPoints = STDToString(skillData.GetImpale());
        sCharacterDetails_StealthStrike_SkillPoints = STDToString(skillData.GetStealthStrike());
        sCharacterDetails_CriticalShot_SkillPoints = STDToString(skillData.GetCriticalShot());
        sCharacterDetails_Dodge_SkillPoints = STDToString(skillData.GetDodge());
        sCharacterDetails_Counter_SkillPoints = STDToString(skillData.GetCounter());
        sCharacterDetails_Healer_SkillPoints = STDToString(skillData.GetHealer());
        sCharacterDetails_Alchemist_SkillPoints = STDToString(skillData.GetAlchemist());
        sCharacterDetails_Energist_SkillPoints = STDToString(skillData.GetEnergist());
        sCharacterDetails_Chemist_SkillPoints = STDToString(skillData.GetChemist());
        sCharacterDetails_Hammersmith_SkillPoints = STDToString(skillData.GetHammersmith());
        sCharacterDetails_Spellsmith_SkillPoints = STDToString(skillData.GetSpellsmith());
        sCharacterDetails_Bowsmith_SkillPoints = STDToString(skillData.GetBowsmith());
        sCharacterDetails_Swordsmith_SkillPoints = STDToString(skillData.GetSwordsmith());
        sCharacterDetails_Weaver_SkillPoints = STDToString(skillData.GetWeaver());
        sCharacterDetails_Tanner_SkillPoints = STDToString(skillData.GetTanner());
        sCharacterDetails_Scalesmith_SkillPoints = STDToString(skillData.GetScalesmith());
        sCharacterDetails_Platesmith_SkillPoints = STDToString(skillData.GetPlatesmith());
        sCharacterDetails_Goldsmith_SkillPoints = STDToString(skillData.GetGoldsmith());
        sCharacterDetails_Shieldsmith_SkillPoints = STDToString(skillData.GetShieldsmith());
        sCharacterDetails_Hammerbane_SkillPoints = STDToString(skillData.GetHammerbane());
        sCharacterDetails_Spellbane_SkillPoints = STDToString(skillData.GetSpellbane());
        sCharacterDetails_Bowbane_SkillPoints = STDToString(skillData.GetBowbane());
        sCharacterDetails_Swordbane_SkillPoints = STDToString(skillData.GetSwordbane());
        sCharacterDetails_Threadbare_SkillPoints = STDToString(skillData.GetThreadbare());
        sCharacterDetails_Studremover_SkillPoints = STDToString(skillData.GetStudRemover());
        sCharacterDetails_Scalebane_SkillPoints = STDToString(skillData.GetScalebane());
        sCharacterDetails_Platebane_SkillPoints = STDToString(skillData.GetPlatebane());
        sCharacterDetails_Goldbane_SkillPoints = STDToString(skillData.GetGoldbane());
        sCharacterDetails_Shieldbane_SkillPoints = STDToString(skillData.GetShieldbane());
        sCharacterDetails_Holy_SkillPoints = STDToString(skillData.GetHoly());
        sCharacterDetails_Fire_SkillPoints = STDToString(skillData.GetFire());
        sCharacterDetails_Ice_SkillPoints = STDToString(skillData.GetIce());
        sCharacterDetails_Shock_SkillPoints = STDToString(skillData.GetShock());
        sCharacterDetails_Dark_SkillPoints = STDToString(skillData.GetDark());
        sCharacterDetails_Light_SkillPoints = STDToString(skillData.GetLight());
        sCharacterDetails_Force_SkillPoints = STDToString(skillData.GetForce());
        sCharacterDetails_Mind_SkillPoints = STDToString(skillData.GetMind());
        sCharacterDetails_Earth_SkillPoints = STDToString(skillData.GetEarth());
        sCharacterDetails_Blood_SkillPoints = STDToString(skillData.GetBlood());
        sCharacterDetails_Flesh_SkillPoints = STDToString(skillData.GetFlesh());
        sCharacterDetails_Wind_SkillPoints = STDToString(skillData.GetWind());
        sCharacterDetails_CharID = character.GetCharacterID();
        sCharacterDetails_AvailableActions = Json(character.GetAvailableActions()).dump();
        sCharacterDetails_SkillPassiveChanges = Json(character.GetPassiveChanges(sSkillTreeIndexType)).dump();
        sCharacterDetails_ItemPassiveChanges = Json(character.GetPassiveChanges(sItemTreeIndexType)).dump();
        sCharacterDetails_SkillActiveChanges = Json(character.GetActiveChanges(sSkillTreeIndexType)).dump();
        sCharacterDetails_ItemActiveChanges = Json(character.GetActiveChanges(sItemTreeIndexType)).dump();
        sCharacterDetails_SkillActionableChanges = Json(character.GetActionableChanges(sSkillTreeIndexType)).dump();
        sCharacterDetails_ItemActionableChanges = Json(character.GetActionableChanges(sItemTreeIndexType)).dump();
        sCharacterDetails_RawJson = Json(character).dump();
    }

    // Build option lists
    String sCharacterDetailsOptionList_CharacterGenderType = MakeSelectedHtmlOptionList<CharacterGenderType>(sCharacterDetails_Gender);
    String sCharacterDetailsOptionList_CharacterHairType = MakeSelectedHtmlOptionList<CharacterHairType>(sCharacterDetails_Hair);
    String sCharacterDetailsOptionList_CharacterEyeType = MakeSelectedHtmlOptionList<CharacterEyeType>(sCharacterDetails_Eyes);
    String sCharacterDetailsOptionList_CharacterHandednessType = MakeSelectedHtmlOptionList<CharacterHandednessType>(sCharacterDetails_Handedness);
    String sCharacterDetailsOptionList_CharacterPowerSetType = MakeSelectedHtmlOptionList<CharacterPowerSetType>(sCharacterDetails_PowerSet);
    String sCharacterDetailsOptionList_CharacterBaseRaceType = MakeSelectedHtmlOptionList<CharacterBaseRaceType>(sCharacterDetails_BaseRace);
    String sCharacterDetailsOptionList_CharacterTransformedRaceType = MakeSelectedHtmlOptionList<CharacterTransformedRaceType>(sCharacterDetails_TransformedRace);
    String sCharacterDetailsOptionList_CharacterWeaponSetType = MakeSelectedHtmlOptionList<CharacterWeaponSetType>(sCharacterDetails_WeaponSet);
    String sOptionList_FileType = MakeDefaultHtmlOptionList<FileType>();

    // Set page content
    String sPage = GetPageTemplate();
    BoostReplaceAll(sPage, "%sCharacterDetailsOptionList_Gender%", sCharacterDetailsOptionList_CharacterGenderType);
    BoostReplaceAll(sPage, "%sCharacterDetailsOptionList_Hair%", sCharacterDetailsOptionList_CharacterHairType);
    BoostReplaceAll(sPage, "%sCharacterDetailsOptionList_Eyes%", sCharacterDetailsOptionList_CharacterEyeType);
    BoostReplaceAll(sPage, "%sCharacterDetailsOptionList_Handed%", sCharacterDetailsOptionList_CharacterHandednessType);
    BoostReplaceAll(sPage, "%sCharacterDetailsOptionList_PowerSet%", sCharacterDetailsOptionList_CharacterPowerSetType);
    BoostReplaceAll(sPage, "%sCharacterDetailsOptionList_BaseRace%", sCharacterDetailsOptionList_CharacterBaseRaceType);
    BoostReplaceAll(sPage, "%sCharacterDetailsOptionList_TransformedRace%", sCharacterDetailsOptionList_CharacterTransformedRaceType);
    BoostReplaceAll(sPage, "%sCharacterDetailsOptionList_WeaponSet%", sCharacterDetailsOptionList_CharacterWeaponSetType);
    BoostReplaceAll(sPage, "%sOptionList_FileType%", sOptionList_FileType);
    BoostReplaceAll(sPage, "%sLoadCharacterFromJson_Textarea%", sLoadCharacterFromJson_Textarea);
    BoostReplaceAll(sPage, "%sLoadCharacterFromFile_Filename%", sLoadCharacterFromFile_Filename);
    BoostReplaceAll(sPage, "%sSaveCharacterToFile_CharID%", sSaveCharacterToFile_CharID);
    BoostReplaceAll(sPage, "%sSaveCharacterToFile_Filename%", sSaveCharacterToFile_Filename);
    BoostReplaceAll(sPage, "%sUnloadCharacter_CharID%", sUnloadCharacter_CharID);
    BoostReplaceAll(sPage, "%sGenerateCharacter_CharID%", sGenerateCharacter_CharID);
    BoostReplaceAll(sPage, "%sGenerateCharacter_Textarea%", sGenerateCharacter_Textarea);
    BoostReplaceAll(sPage, "%sGenerateRandomCharacter_CharID%", sGenerateRandomCharacter_CharID);
    BoostReplaceAll(sPage, "%sRegenerateCharacterData_CharID%", sRegenerateCharacterData_CharID);
    BoostReplaceAll(sPage, "%sCreateCharacter_CharID%", sCreateCharacter_CharID);
    BoostReplaceAll(sPage, "%sDisplayCharacter_CharID%", sDisplayCharacter_CharID);
    BoostReplaceAll(sPage, "%sAllCharacterIDs%", sAllCharacterIDs);
    BoostReplaceAll(sPage, "%sCharacterDetails_CharID%", sCharacterDetails_CharID);
    BoostReplaceAll(sPage, "%sCharacterDetails_PartyID%", sCharacterDetails_PartyID);
    BoostReplaceAll(sPage, "%sCharacterDetails_CharTargetType%", sCharacterDetails_CharTargetType);
    BoostReplaceAll(sPage, "%sCharacterDetails_First_Name%", sCharacterDetails_First_Name);
    BoostReplaceAll(sPage, "%sCharacterDetails_Last_Name%", sCharacterDetails_Last_Name);
    BoostReplaceAll(sPage, "%sCharacterDetails_Age%", sCharacterDetails_Age);
    BoostReplaceAll(sPage, "%sCharacterDetails_Blunt_Attack%", sCharacterDetails_Blunt_Attack);
    BoostReplaceAll(sPage, "%sCharacterDetails_Blunt_Defense%", sCharacterDetails_Blunt_Defense);
    BoostReplaceAll(sPage, "%sCharacterDetails_Pierce_Attack%", sCharacterDetails_Pierce_Attack);
    BoostReplaceAll(sPage, "%sCharacterDetails_Pierce_Defense%", sCharacterDetails_Pierce_Defense);
    BoostReplaceAll(sPage, "%sCharacterDetails_Slash_Attack%", sCharacterDetails_Slash_Attack);
    BoostReplaceAll(sPage, "%sCharacterDetails_Slash_Defense%", sCharacterDetails_Slash_Defense);
    BoostReplaceAll(sPage, "%sCharacterDetails_Magic_Attack%", sCharacterDetails_Magic_Attack);
    BoostReplaceAll(sPage, "%sCharacterDetails_Magic_Defense%", sCharacterDetails_Magic_Defense);
    BoostReplaceAll(sPage, "%sCharacterDetails_Energy_Attack%", sCharacterDetails_Energy_Attack);
    BoostReplaceAll(sPage, "%sCharacterDetails_Energy_Defense%", sCharacterDetails_Energy_Defense);
    BoostReplaceAll(sPage, "%sCharacterDetails_HP_Current%", sCharacterDetails_HP_Current);
    BoostReplaceAll(sPage, "%sCharacterDetails_HP_Max%", sCharacterDetails_HP_Max);
    BoostReplaceAll(sPage, "%sCharacterDetails_HP_Regen%", sCharacterDetails_HP_Regen);
    BoostReplaceAll(sPage, "%sCharacterDetails_HP_Delta%", sCharacterDetails_HP_Delta);
    BoostReplaceAll(sPage, "%sCharacterDetails_MP_Current%", sCharacterDetails_MP_Current);
    BoostReplaceAll(sPage, "%sCharacterDetails_MP_Max%", sCharacterDetails_MP_Max);
    BoostReplaceAll(sPage, "%sCharacterDetails_MP_Regen%", sCharacterDetails_MP_Regen);
    BoostReplaceAll(sPage, "%sCharacterDetails_MP_Delta%", sCharacterDetails_MP_Delta);
    BoostReplaceAll(sPage, "%sCharacterDetails_EP_Current%", sCharacterDetails_EP_Current);
    BoostReplaceAll(sPage, "%sCharacterDetails_EP_Max%", sCharacterDetails_EP_Max);
    BoostReplaceAll(sPage, "%sCharacterDetails_EP_Regen%", sCharacterDetails_EP_Regen);
    BoostReplaceAll(sPage, "%sCharacterDetails_EP_Delta%", sCharacterDetails_EP_Delta);
    BoostReplaceAll(sPage, "%sCharacterDetails_Speed%", sCharacterDetails_Speed);
    BoostReplaceAll(sPage, "%sCharacterDetails_Chest%", sCharacterDetails_Chest);
    BoostReplaceAll(sPage, "%sCharacterDetails_Feet%", sCharacterDetails_Feet);
    BoostReplaceAll(sPage, "%sCharacterDetails_Hands%", sCharacterDetails_Hands);
    BoostReplaceAll(sPage, "%sCharacterDetails_Head%", sCharacterDetails_Head);
    BoostReplaceAll(sPage, "%sCharacterDetails_Legs%", sCharacterDetails_Legs);
    BoostReplaceAll(sPage, "%sCharacterDetails_Neck%", sCharacterDetails_Neck);
    BoostReplaceAll(sPage, "%sCharacterDetails_LeftFingers%", sCharacterDetails_LeftFingers);
    BoostReplaceAll(sPage, "%sCharacterDetails_RightFingers%", sCharacterDetails_RightFingers);
    BoostReplaceAll(sPage, "%sCharacterDetails_Weapon1Left%", sCharacterDetails_Weapon1Left);
    BoostReplaceAll(sPage, "%sCharacterDetails_Weapon1Right%", sCharacterDetails_Weapon1Right);
    BoostReplaceAll(sPage, "%sCharacterDetails_Weapon2Left%", sCharacterDetails_Weapon2Left);
    BoostReplaceAll(sPage, "%sCharacterDetails_Weapon2Right%", sCharacterDetails_Weapon2Right);
    BoostReplaceAll(sPage, "%sCharacterDetails_Bash_ActionPoints%", sCharacterDetails_Bash_ActionPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Block_ActionPoints%", sCharacterDetails_Block_ActionPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Break_ActionPoints%", sCharacterDetails_Break_ActionPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Cleave_ActionPoints%", sCharacterDetails_Cleave_ActionPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Counter_ActionPoints%", sCharacterDetails_Counter_ActionPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Crack_ActionPoints%", sCharacterDetails_Crack_ActionPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Crush_ActionPoints%", sCharacterDetails_Crush_ActionPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_CriticalShot_ActionPoints%", sCharacterDetails_CriticalShot_ActionPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Decapitate_ActionPoints%", sCharacterDetails_Decapitate_ActionPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Dodge_ActionPoints%", sCharacterDetails_Dodge_ActionPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Drill_ActionPoints%", sCharacterDetails_Drill_ActionPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Impact_ActionPoints%", sCharacterDetails_Impact_ActionPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Impale_ActionPoints%", sCharacterDetails_Impale_ActionPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Parry_ActionPoints%", sCharacterDetails_Parry_ActionPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Pierce_ActionPoints%", sCharacterDetails_Pierce_ActionPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Riposte_ActionPoints%", sCharacterDetails_Riposte_ActionPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Rush_ActionPoints%", sCharacterDetails_Rush_ActionPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Sever_ActionPoints%", sCharacterDetails_Sever_ActionPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Shoot_ActionPoints%", sCharacterDetails_Shoot_ActionPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Slash_ActionPoints%", sCharacterDetails_Slash_ActionPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Slice_ActionPoints%", sCharacterDetails_Slice_ActionPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Slit_ActionPoints%", sCharacterDetails_Slit_ActionPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Smash_ActionPoints%", sCharacterDetails_Smash_ActionPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_StealthStrike_ActionPoints%", sCharacterDetails_StealthStrike_ActionPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Alchemist_SkillPoints%", sCharacterDetails_Alchemist_SkillPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Ambidext_SkillPoints%", sCharacterDetails_Ambidext_SkillPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Avatar_SkillPoints%", sCharacterDetails_Avatar_SkillPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Barbarian_SkillPoints%", sCharacterDetails_Barbarian_SkillPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Bash_SkillPoints%", sCharacterDetails_Bash_SkillPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Blademaster_SkillPoints%", sCharacterDetails_Blademaster_SkillPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Block_SkillPoints%", sCharacterDetails_Block_SkillPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Blood_SkillPoints%", sCharacterDetails_Blood_SkillPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Bowbane_SkillPoints%", sCharacterDetails_Bowbane_SkillPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Bowsmith_SkillPoints%", sCharacterDetails_Bowsmith_SkillPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Break_SkillPoints%", sCharacterDetails_Break_SkillPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Chemist_SkillPoints%", sCharacterDetails_Chemist_SkillPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Cleave_SkillPoints%", sCharacterDetails_Cleave_SkillPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Counter_SkillPoints%", sCharacterDetails_Counter_SkillPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Crack_SkillPoints%", sCharacterDetails_Crack_SkillPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Crush_SkillPoints%", sCharacterDetails_Crush_SkillPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_CriticalShot_SkillPoints%", sCharacterDetails_CriticalShot_SkillPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Dark_SkillPoints%", sCharacterDetails_Dark_SkillPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Decapitate_SkillPoints%", sCharacterDetails_Decapitate_SkillPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Dodge_SkillPoints%", sCharacterDetails_Dodge_SkillPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Drill_SkillPoints%", sCharacterDetails_Drill_SkillPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Earth_SkillPoints%", sCharacterDetails_Earth_SkillPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Energist_SkillPoints%", sCharacterDetails_Energist_SkillPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Fire_SkillPoints%", sCharacterDetails_Fire_SkillPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Flesh_SkillPoints%", sCharacterDetails_Flesh_SkillPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Focused_SkillPoints%", sCharacterDetails_Focused_SkillPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Force_SkillPoints%", sCharacterDetails_Force_SkillPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Goldbane_SkillPoints%", sCharacterDetails_Goldbane_SkillPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Goldsmith_SkillPoints%", sCharacterDetails_Goldsmith_SkillPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Hammerbane_SkillPoints%", sCharacterDetails_Hammerbane_SkillPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Hammersmith_SkillPoints%", sCharacterDetails_Hammersmith_SkillPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Healer_SkillPoints%", sCharacterDetails_Healer_SkillPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Holy_SkillPoints%", sCharacterDetails_Holy_SkillPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Ice_SkillPoints%", sCharacterDetails_Ice_SkillPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Impact_SkillPoints%", sCharacterDetails_Impact_SkillPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Impale_SkillPoints%", sCharacterDetails_Impale_SkillPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Light_SkillPoints%", sCharacterDetails_Light_SkillPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Mage_SkillPoints%", sCharacterDetails_Mage_SkillPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Mind_SkillPoints%", sCharacterDetails_Mind_SkillPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Parry_SkillPoints%", sCharacterDetails_Parry_SkillPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Pierce_SkillPoints%", sCharacterDetails_Pierce_SkillPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Platebane_SkillPoints%", sCharacterDetails_Platebane_SkillPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Platesmith_SkillPoints%", sCharacterDetails_Platesmith_SkillPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Riposte_SkillPoints%", sCharacterDetails_Riposte_SkillPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Rogue_SkillPoints%", sCharacterDetails_Rogue_SkillPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Rush_SkillPoints%", sCharacterDetails_Rush_SkillPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Scalebane_SkillPoints%", sCharacterDetails_Scalebane_SkillPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Scalesmith_SkillPoints%", sCharacterDetails_Scalesmith_SkillPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Sever_SkillPoints%", sCharacterDetails_Sever_SkillPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Shieldbane_SkillPoints%", sCharacterDetails_Shieldbane_SkillPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Shieldsmith_SkillPoints%", sCharacterDetails_Shieldsmith_SkillPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Shock_SkillPoints%", sCharacterDetails_Shock_SkillPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Shoot_SkillPoints%", sCharacterDetails_Shoot_SkillPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Slash_SkillPoints%", sCharacterDetails_Slash_SkillPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Slice_SkillPoints%", sCharacterDetails_Slice_SkillPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Slit_SkillPoints%", sCharacterDetails_Slit_SkillPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Smash_SkillPoints%", sCharacterDetails_Smash_SkillPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Spellbane_SkillPoints%", sCharacterDetails_Spellbane_SkillPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Spellsmith_SkillPoints%", sCharacterDetails_Spellsmith_SkillPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_StealthStrike_SkillPoints%", sCharacterDetails_StealthStrike_SkillPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Stalwart_SkillPoints%", sCharacterDetails_Stalwart_SkillPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Studremover_SkillPoints%", sCharacterDetails_Studremover_SkillPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Swordbane_SkillPoints%", sCharacterDetails_Swordbane_SkillPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Swordsmith_SkillPoints%", sCharacterDetails_Swordsmith_SkillPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Tanner_SkillPoints%", sCharacterDetails_Tanner_SkillPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Threadbare_SkillPoints%", sCharacterDetails_Threadbare_SkillPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Weaver_SkillPoints%", sCharacterDetails_Weaver_SkillPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_Wind_SkillPoints%", sCharacterDetails_Wind_SkillPoints);
    BoostReplaceAll(sPage, "%sCharacterDetails_AvailableActions%", sCharacterDetails_AvailableActions);
    BoostReplaceAll(sPage, "%sCharacterDetails_SkillPassiveChanges%", sCharacterDetails_SkillPassiveChanges);
    BoostReplaceAll(sPage, "%sCharacterDetails_ItemPassiveChanges%", sCharacterDetails_ItemPassiveChanges);
    BoostReplaceAll(sPage, "%sCharacterDetails_SkillActiveChanges%", sCharacterDetails_SkillActiveChanges);
    BoostReplaceAll(sPage, "%sCharacterDetails_ItemActiveChanges%", sCharacterDetails_ItemActiveChanges);
    BoostReplaceAll(sPage, "%sCharacterDetails_SkillActionableChanges%", sCharacterDetails_SkillActionableChanges);
    BoostReplaceAll(sPage, "%sCharacterDetails_ItemActionableChanges%", sCharacterDetails_ItemActionableChanges);
    BoostReplaceAll(sPage, "%sCharacterDetails_RawJson%", sCharacterDetails_RawJson);
    SetPageContent(sPage);
}

};
