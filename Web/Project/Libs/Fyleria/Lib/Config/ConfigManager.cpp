// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#include "Config/ConfigManager.h"
#include "Utility/Constants.h"

namespace Gecko
{

static const char* s_ksAppName = "Fyleria";

ConfigManager::ConfigManager()
    : Singleton<ConfigManager>()
    , m_Empty()
    , m_tConfigs()
    , m_sCurrentConfigName("")
    , m_sConfigFileOverride("")
    , m_sConfigFolderOverride("")
    , m_sDataFolderOverride("")
    , m_sCacheFolderOverride("")
{
}

Bool ConfigManager::LoadConfig(const String& sName, const String& sFile)
{
    // Create full path
    FilesystemPath pathConfigFolder = GetUserConfigFolder();
    FilesystemPath pathFile = sFile;
    FilesystemPath pathFull = pathConfigFolder / pathFile;
    ASSERT_ERROR(DoesFileExist(pathFull), "Path '%s' could not be loaded for configuration", GetNativeFileLocation(pathFull).c_str());
    if(!DoesFileExist(pathFull))
    {
        return false;
    }

    // Read json data into config object
    Json jsonData;
    if(!ReadJsonFile(IndexedString(GetNativeFileLocation(pathFull)), jsonData))
    {
        return false;
    }

    // Add config
    m_tConfigs[sName] = Config(jsonData);
    return true;
}

Bool ConfigManager::DoesConfigExist(const String& sName) const
{
    auto iSearch = m_tConfigs.find(sName);
    return (iSearch != m_tConfigs.end());
}

const Config& ConfigManager::GetConfig(const String& sName) const
{
    ASSERT_ERROR(DoesConfigExist(sName), "Config with name '%s' was not registered", sName.c_str());
    auto iSearch = m_tConfigs.find(sName);
    return (iSearch != m_tConfigs.end()) ? iSearch->second : m_Empty;
}

const Config& ConfigManager::GetCurrentConfig() const
{
    return GetConfig(GetCurrentConfigName());
}

String ConfigManager::GetPythonLib() const
{
    FilesystemPath basePath = GetUserConfigFolder();
    FilesystemPath libPath = GetCurrentConfig().GetPythonLib();
    FilesystemPath fullPath = basePath / libPath;
    return GetNativeFileLocation(fullPath);
}

WString ConfigManager::GetPythonLibW() const
{
    FilesystemPath basePath = GetUserConfigFolder();
    FilesystemPath libPath = GetCurrentConfig().GetPythonLib();
    FilesystemPath fullPath = basePath / libPath;
    return GetNativeFileLocationW(fullPath);
}

const String& ConfigManager::GetCurrentConfigName() const
{
    return m_sCurrentConfigName;
}

void ConfigManager::SetCurrentConfigName(const String& sName)
{
    m_sCurrentConfigName = sName;
}

String ConfigManager::GetUserConfigFile() const
{
    if (!m_sConfigFileOverride.empty())
    {
        return m_sConfigFileOverride;
    }
    Byte aConfigInfo[MAX_PATH] = {0};
    get_user_config_file(aConfigInfo, sizeof(aConfigInfo), s_ksAppName);
    return String(aConfigInfo);
}

String ConfigManager::GetUserConfigFolder() const
{
    if (!m_sConfigFolderOverride.empty())
    {
        return m_sConfigFolderOverride;
    }
    Byte aConfigInfo[MAX_PATH] = {0};
    get_user_config_folder(aConfigInfo, sizeof(aConfigInfo), s_ksAppName);
    return String(aConfigInfo);
}

String ConfigManager::GetUserDataFolder() const
{
    if (!m_sDataFolderOverride.empty())
    {
        return m_sDataFolderOverride;
    }
    Byte aConfigInfo[MAX_PATH] = {0};
    get_user_data_folder(aConfigInfo, sizeof(aConfigInfo), s_ksAppName);
    return String(aConfigInfo);
}

String ConfigManager::GetUserCacheFolder() const
{
    if (!m_sCacheFolderOverride.empty())
    {
        return m_sCacheFolderOverride;
    }
    Byte aConfigInfo[MAX_PATH] = {0};
    get_user_cache_folder(aConfigInfo, sizeof(aConfigInfo), s_ksAppName);
    return String(aConfigInfo);
}

FilesystemPath ConfigManager::GetUserConfigFilePath() const
{
    return FilesystemPath(GetUserConfigFile());
}

FilesystemPath ConfigManager::GetUserConfigFolderPath() const
{
    return FilesystemPath(GetUserConfigFolder());
}

FilesystemPath ConfigManager::GetUserDataFolderPath() const
{
    return FilesystemPath(GetUserDataFolder());
}

FilesystemPath ConfigManager::GetUserCacheFolderPath() const
{
    return FilesystemPath(GetUserCacheFolder());
}

String ConfigManager::GetUserConfigFolderLocation(const String& sLocation) const
{
    return GetNativeFileLocation(FilesystemPath(GetUserConfigFolder() / FilesystemPath(sLocation)));
}

String ConfigManager::GetUserDataFolderLocation(const String& sLocation) const
{
    return GetNativeFileLocation(FilesystemPath(GetUserDataFolder() / FilesystemPath(sLocation)));
}

String ConfigManager::GetUserCacheFolderLocation(const String& sLocation) const
{
    return GetNativeFileLocation(FilesystemPath(GetUserCacheFolder() / FilesystemPath(sLocation)));
}

void ConfigManager::SetUserConfigFileOverride(const String& sOverride)
{
    m_sConfigFileOverride = sOverride;
}

void ConfigManager::SetUserConfigFolderOverride(const String& sOverride)
{
    m_sConfigFolderOverride = sOverride;
}

void ConfigManager::SetUserDataFolderOverride(const String& sOverride)
{
    m_sDataFolderOverride = sOverride;
}

void ConfigManager::SetUserCacheFolderOverride(const String& sOverride)
{
    m_sCacheFolderOverride = sOverride;
}

Bool ConfigManager::IsPosix() const
{
#if defined(_POSIX_VERSION)
    return true;
#else
    return false;
#endif
}

Bool ConfigManager::IsWindows() const
{
#if defined(_WIN64) || defined(_WIN32)
    return true;
#else
    return false;
#endif
}

Bool ConfigManager::IsWindows32() const
{
#if defined(_WIN32)
    return true;
#else
    return false;
#endif
}

Bool ConfigManager::IsWindows64() const
{
#if defined(_WIN64)
    return true;
#else
    return false;
#endif
}

Bool ConfigManager::IsMac() const
{
#if TARGET_OS_MAC == 1
    return true;
#else
    return false;
#endif
}

Bool ConfigManager::IsIOS() const
{
#if (TARGET_IPHONE_SIMULATOR == 1) || (TARGET_OS_IPHONE == 1)
    return true;
#else
    return false;
#endif
}

Bool ConfigManager::IsAndroid() const
{
#if defined(__ANDROID__)
    return true;
#else
    return false;
#endif
}

};
