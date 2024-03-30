// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

// Internal includes
#include "Config/Config.h"
#include "Config/ConfigManager.h"
#include "Utility/Macros.h"
#include "Utility/Python.h"

namespace Gecko
{
    // Manager lambdas
    auto fnLoadConfig = MAKE_MANAGER_RETURN_LAMBDA_A2(ConfigManager, LoadConfig, Bool, const String&, const String&);
    auto fnDoesConfigExist = MAKE_MANAGER_RETURN_LAMBDA_A1(ConfigManager, DoesConfigExist, Bool, const String&);
    auto fnGetConfig = MAKE_MANAGER_RETURN_LAMBDA_A1(ConfigManager, GetConfig, const Config&, const String&);
    auto fnGetCurrentConfig = MAKE_MANAGER_RETURN_LAMBDA(ConfigManager, GetCurrentConfig, const Config&);
    auto fnGetCurrentConfigName = MAKE_MANAGER_RETURN_LAMBDA(ConfigManager, GetCurrentConfigName, const String&);
    auto fnSetCurrentConfigName = MAKE_MANAGER_VOID_LAMBDA_A1(ConfigManager, SetCurrentConfigName, const String&);
    auto fnIs32Bit = MAKE_MANAGER_RETURN_LAMBDA(ConfigManager, Is32Bit, Bool);
    auto fnIs64Bit = MAKE_MANAGER_RETURN_LAMBDA(ConfigManager, Is64Bit, Bool);
    auto fnIsPosix = MAKE_MANAGER_RETURN_LAMBDA(ConfigManager, IsPosix, Bool);
    auto fnIsWindows = MAKE_MANAGER_RETURN_LAMBDA(ConfigManager, IsWindows, Bool);
    auto fnIsLinux = MAKE_MANAGER_RETURN_LAMBDA(ConfigManager, IsLinux, Bool);
    auto fnIsMacOS = MAKE_MANAGER_RETURN_LAMBDA(ConfigManager, IsMacOS, Bool);
    auto fnIsIOS = MAKE_MANAGER_RETURN_LAMBDA(ConfigManager, IsIOS, Bool);
    auto fnIsAndroid = MAKE_MANAGER_RETURN_LAMBDA(ConfigManager, IsAndroid, Bool);
};

PYBIND11_EMBEDDED_MODULE(GeckoConfig, m)
{
    // Config.h
    PyBindClass<Gecko::Config>(m, "Config")
        WRAPPING_ADD_CONSTRUCTOR_SIMPLE()
        WRAPPING_ADD_CONSTRUCTOR_ARGS(const Gecko::String&)
        WRAPPING_ADD_BASIC_PROPERTY_READONLY_MULTIGET(ScreenWidth, Gecko::Config)
        WRAPPING_ADD_BASIC_PROPERTY_READONLY_MULTIGET(ScreenHeight, Gecko::Config)
    ;
    PyBindVector<Gecko::ConfigArray>(m, "ConfigArray");

    // ConfigManager.h
    WRAPPING_STANDALONE_LAMBDA(LoadConfig, Gecko::fnLoadConfig);
    WRAPPING_STANDALONE_LAMBDA(DoesConfigExist, Gecko::fnDoesConfigExist);
    WRAPPING_STANDALONE_LAMBDA_POLICY(GetConfig, Gecko::fnGetConfig, PyBindReturnCopy);
    WRAPPING_STANDALONE_LAMBDA_POLICY(GetCurrentConfig, Gecko::fnGetCurrentConfig, PyBindReturnCopy);
    WRAPPING_STANDALONE_LAMBDA_POLICY(GetCurrentConfigName, Gecko::fnGetCurrentConfigName, PyBindReturnCopy);
    WRAPPING_STANDALONE_LAMBDA(SetCurrentConfigName, Gecko::fnSetCurrentConfigName);
    WRAPPING_STANDALONE_LAMBDA(Is32Bit, Gecko::fnIs32Bit);
    WRAPPING_STANDALONE_LAMBDA(Is64Bit, Gecko::fnIs64Bit);
    WRAPPING_STANDALONE_LAMBDA(IsPosix, Gecko::fnIsPosix);
    WRAPPING_STANDALONE_LAMBDA(IsWindows, Gecko::fnIsWindows);
    WRAPPING_STANDALONE_LAMBDA(IsLinux, Gecko::fnIsLinux);
    WRAPPING_STANDALONE_LAMBDA(IsMacOS, Gecko::fnIsMacOS);
    WRAPPING_STANDALONE_LAMBDA(IsIOS, Gecko::fnIsIOS);
    WRAPPING_STANDALONE_LAMBDA(IsAndroid, Gecko::fnIsAndroid);
}
