// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

#ifndef _GECKO_CONFIG_MANAGER_H_
#define _GECKO_CONFIG_MANAGER_H_

// Internal includes
#include "Config/Config.h"
#include "Utility/Singleton.h"

namespace Gecko
{

class ConfigManager : public Singleton<ConfigManager>
{
public:

    // Types
    typedef STDUnorderedMap<String, Config> ConfigMappingType;

    // Constructors
    ConfigManager();

    // Load config
    Bool LoadConfig(const String& sName, const String& sFile);

    // Does a config exist
    Bool DoesConfigExist(const String& sName) const;

    // Get config
    const Config& GetConfig(const String& sName) const;
    const Config& GetCurrentConfig() const;

    // Current config name
    MAKE_RAW_TYPE_ACCESSORS(CurrentConfigName, String);

    // Configuration map
    MAKE_RAW_TYPE_ACCESSORS(LoadedConfigs, ConfigMappingType);

    // Platforms
    Bool Is32Bit() const;
    Bool Is64Bit() const;
    Bool IsPosix() const;
    Bool IsWindows() const;
    Bool IsLinux() const;
    Bool IsMacOS() const;
    Bool IsIOS() const;
    Bool IsAndroid() const;
};

};

#endif
