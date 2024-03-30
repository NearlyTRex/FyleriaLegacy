// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#ifndef _GECKO_CONFIG_MANAGER_H_
#define _GECKO_CONFIG_MANAGER_H_

#include "Config/Config.h"
#include "Utility/IndexedString.h"
#include "Utility/Singleton.h"

namespace Gecko
{

class ConfigManager : public Singleton<ConfigManager>
{
public:

    // Constructors
    ConfigManager();

    // Load config
    Bool LoadConfig(const String& sName, const String& sFile);

    // Does a config exist
    Bool DoesConfigExist(const String& sName) const;

    // Get config
    const Config& GetConfig(const String& sName) const;
    const Config& GetCurrentConfig() const;

    // Get python library
    String GetPythonLib() const;
    WString GetPythonLibW() const;

    // Character generator file locations
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(CharacterGeneratorRandomFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(CharacterGeneratorStaticFile);

    // Item file locations
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(ItemArmorChestFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(ItemArmorFeetFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(ItemArmorFingerFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(ItemArmorHandsFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(ItemArmorHeadFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(ItemArmorNeckFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(ItemArmorLegsFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(ItemArmorShieldFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(ItemIngredientBarFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(ItemIngredientClothFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(ItemIngredientCrystalFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(ItemIngredientLeatherFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(ItemIngredientMailFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(ItemIngredientPlateFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(ItemIngredientScaleFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(ItemIngredientScrewFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(ItemIngredientSheetFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(ItemIngredientStudFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(ItemIngredientThreadFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(ItemPotionEnergyFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(ItemPotionHealFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(ItemPotionMagicFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(ItemPotionSpeedFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(ItemWeaponBluntFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(ItemWeaponMageFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(ItemWeaponPierceFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(ItemWeaponSlashFile);

    // Skill file locations
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(SkillAffinityBloodFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(SkillAffinityDarkFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(SkillAffinityEarthFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(SkillAffinityFireFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(SkillAffinityFleshFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(SkillAffinityForceFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(SkillAffinityHolyFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(SkillAffinityIceFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(SkillAffinityLightFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(SkillAffinityMindFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(SkillAffinityShockFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(SkillAffinityWindFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(SkillAlchemyAlchemistFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(SkillAlchemyChemistFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(SkillAlchemyEnergistFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(SkillAlchemyHealerFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(SkillBreakdownBowbaneFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(SkillBreakdownGoldbaneFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(SkillBreakdownHammerbaneFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(SkillBreakdownPlatebaneFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(SkillBreakdownScalebaneFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(SkillBreakdownShieldbaneFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(SkillBreakdownSpellbaneFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(SkillBreakdownStudRemoverFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(SkillBreakdownSwordbaneFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(SkillBreakdownThreadbareFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(SkillCombatAmbidextrousFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(SkillCombatAvatarFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(SkillCombatBarbarianFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(SkillCombatBlademasterFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(SkillCombatFocusedFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(SkillCombatMageFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(SkillCombatRogueFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(SkillCombatStalwartFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(SkillCraftingBowsmithFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(SkillCraftingGoldsmithFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(SkillCraftingHammersmithFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(SkillCraftingPlatesmithFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(SkillCraftingScalesmithFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(SkillCraftingShieldsmithFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(SkillCraftingSpellsmithFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(SkillCraftingSwordsmithFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(SkillCraftingTannerFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(SkillCraftingWeaverFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(SkillWeaponBashFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(SkillWeaponBlockFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(SkillWeaponBreakFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(SkillWeaponCleaveFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(SkillWeaponCounterFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(SkillWeaponCrackFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(SkillWeaponCriticalShotFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(SkillWeaponCrushFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(SkillWeaponDecapitateFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(SkillWeaponDodgeFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(SkillWeaponDrillFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(SkillWeaponImpactFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(SkillWeaponImpaleFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(SkillWeaponParryFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(SkillWeaponPierceFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(SkillWeaponRiposteFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(SkillWeaponRushFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(SkillWeaponSeverFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(SkillWeaponShootFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(SkillWeaponSlashFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(SkillWeaponSliceFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(SkillWeaponSlitFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(SkillWeaponSmashFile);
    MAKE_CURRENT_CONFIG_SHORTCUT_STRING(SkillWeaponStealthStrikeFile);

    // Current config name
    const String& GetCurrentConfigName() const;
    void SetCurrentConfigName(const String& sName);

    // Portable config data
    String GetUserConfigFile() const;
    String GetUserConfigFolder() const;
    String GetUserDataFolder() const;
    String GetUserCacheFolder() const;
    String GetUserConfigFolderLocation(const String& sLocation) const;
    String GetUserDataFolderLocation(const String& sLocation) const;
    String GetUserCacheFolderLocation(const String& sLocation) const;
    FilesystemPath GetUserConfigFilePath() const;
    FilesystemPath GetUserConfigFolderPath() const;
    FilesystemPath GetUserDataFolderPath() const;
    FilesystemPath GetUserCacheFolderPath() const;

    // Override for config data
    void SetUserConfigFileOverride(const String& sOverride);
    void SetUserConfigFolderOverride(const String& sOverride);
    void SetUserDataFolderOverride(const String& sOverride);
    void SetUserCacheFolderOverride(const String& sOverride);

    // Platforms
    Bool IsPosix() const;
    Bool IsWindows() const;
    Bool IsWindows32() const;
    Bool IsWindows64() const;
    Bool IsMac() const;
    Bool IsIOS() const;
    Bool IsAndroid() const;

private:

    // Empty config
    const Config m_Empty;

    // Loaded configs
    STDUnorderedMap<String, Config> m_tConfigs;

    // Current config name
    String m_sCurrentConfigName;

    // Overrides
    String m_sConfigFileOverride;
    String m_sConfigFolderOverride;
    String m_sDataFolderOverride;
    String m_sCacheFolderOverride;
};

};

#endif
