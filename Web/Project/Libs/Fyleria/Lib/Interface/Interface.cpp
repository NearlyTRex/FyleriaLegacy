// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#include "Interface/Interface.h"
#include "Module/Module.h"
#include "Utility/Assert.h"
#include "Utility/Logging.h"
#include "Utility/TypesPython.h"
#include "Utility/TypesSimple.h"
#include "Utility/TypesTrace.h"

#include "Config/ConfigManager.h"

#include "Character/Character.h"
#include "Character/CharacterParty.h"
#include "Items/ItemTree.h"
#include "Skills/SkillTree.h"

#include "Battle/Battle_wrapper.h"
#include "Config/Config_wrapper.h"
#include "Character/Character_wrapper_Character.h"
#include "Character/Character_wrapper_CharacterAction.h"
#include "Character/Character_wrapper_CharacterData.h"
#include "Character/Character_wrapper_CharacterParty.h"
#include "Items/Items_wrapper.h"
#include "Module/Module_wrapper.h"
#include "Recipes/Recipes_wrapper.h"
#include "Saves/Saves_wrapper.h"
#include "Skills/Skills_wrapper.h"
#include "Stats/Stats_wrapper.h"
#include "Utility/Utility_wrapper.h"

#include "Utility/TypesFantasyName.h"
#include "Server/WebSockets.h"
#include "Server/Rest.h"

namespace Gecko
{

// Interface mutex
STDMutex g_ModuleMutex;

extern "C" DLL_PUBLIC bool DLL_InitModule()
{
    // Lock API call
    STDLockGuard<STDMutex> lock(g_ModuleMutex);

    // Check supported platforms
    if(
        ConfigManager::GetInstance()->IsIOS() ||
        ConfigManager::GetInstance()->IsAndroid()
    )
    {
        ERROR_STATEMENT("Unsupported platform");
        return false;
    }

    // Load config data
    ConfigManager::GetInstance()->SetCurrentConfigName("Default");
    String sConfigFileLocation = ConfigManager::GetInstance()->GetUserConfigFolderLocation("config.json");
    if (!DoesFileExist(FilesystemPath(sConfigFileLocation)))
    {
        ERROR_FORMAT_STATEMENT("Config file %s was not found.\n", sConfigFileLocation.c_str());
        return false;
    }
    if(!ConfigManager::GetInstance()->LoadConfig("Default", "config.json"))
    {
        ERROR_STATEMENT("Could not load config data");
        return false;
    }

    // Check python library
    if(!DoesFileExist(ConfigManager::GetInstance()->GetPythonLib()))
    {
        ERROR_FORMAT_STATEMENT("Python library '%s' could not be found, check configuration file\n",
            ConfigManager::GetInstance()->GetPythonLib().c_str());
        return false;
    }

    // Skip site usage and ignore environment variables
    Py_NoSiteFlag++;
    Py_NoUserSiteDirectory++;
    Py_IgnoreEnvironmentFlag++;

    // Set python home
#ifdef Py_USING_UNICODE
    Py_SetPythonHome(const_cast<wchar_t*>(ConfigManager::GetInstance()->GetPythonLibW().c_str()));
    Py_SetPath(ConfigManager::GetInstance()->GetPythonLibW().c_str());
#else
    Py_SetPythonHome(const_cast<char*>(ConfigManager::GetInstance()->GetPythonLib().c_str()));
    Py_SetPath(ConfigManager::GetInstance()->GetPythonLib().c_str());
#endif

    // Initialize interpreter
    PyBindInitializeInterpreter(false);

    // Import basic modules
    PyRun_SimpleString("import os");
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('Scripts')");

    // Load trees into memory
    LOG_STATEMENT("Loading trees into memory...");
    LoadSkillTreesIntoMemory();
    LoadItemTreesIntoMemory();
    LOG_STATEMENT("Finished loading trees into memory");

    // Initialization finished!
    LOG_STATEMENT("Module successfully initialized");
    return true;
}

extern "C" DLL_PUBLIC bool DLL_FinalizeModule()
{
    // Lock API call
    STDLockGuard<STDMutex> lock(g_ModuleMutex);

    // Unload trees from memory
    LOG_STATEMENT("Unloading trees from memory...");
    UnloadSkillTreesFromMemory();
    UnloadItemTreesFromMemory();
    LOG_STATEMENT("Finished unloading trees from memory");

    // Finalize interpreter
    PyBindFinalizeInterpreter();

    // Clear module results
    LOG_STATEMENT("Clearing all module results...");
    ModuleResult::ClearAllResults();
    LOG_STATEMENT("Finished clearing module results");

    // Finalization finished!
    LOG_STATEMENT("Module successfully finalized");
    return true;
}

bool DLL_Internal_RunModuleFile(const char* sFile, const char* sResultsID)
{
    // Lock API call
    STDLockGuard<STDMutex> lock(g_ModuleMutex);

    try
    {
        // Set run result ID
        if(sResultsID)
        {
            ModuleResult::SetRunResultID(sResultsID);
        }

        // Lock python state
        PyBindAcquireScopedGIL acquire;

        // Evaluate in scope of main module
        PyBindObject scope = PyBindModuleImport("__main__").attr("__dict__");

        // Evaluate the statements in an separate Python file on disk
        LOG_FORMAT_STATEMENT("Running file '%s'\n", sFile);
        PyBindEvalFile(sFile, scope);
    }
    catch (PyBindRuntimeException& error)
    {
        if(sResultsID)
        {
            ModuleResult::SetRunResultID("");
        }
        auto sMessage = error.what();
        error.restore();
        ERROR_FORMAT_STATEMENT("%s\n", sMessage);
        throw STDModuleError(sMessage);
    }
    if(sResultsID)
    {
        ModuleResult::SetRunResultID("");
    }
    return true;
}

extern "C" DLL_PUBLIC bool DLL_RunModuleFile(const char* sFile)
{
    return DLL_Internal_RunModuleFile(sFile, nullptr);
}

extern "C" DLL_PUBLIC bool DLL_RunModuleFileResults(const char* sFile, const char* sResultsID)
{
    return DLL_Internal_RunModuleFile(sFile, sResultsID);
}

bool DLL_Internal_RunModuleCommand(const char* sCommand, const char* sResultsID)
{
    // Lock API call
    STDLockGuard<STDMutex> lock(g_ModuleMutex);

    try
    {
        // Set run result ID
        if(sResultsID)
        {
            ModuleResult::SetRunResultID(sResultsID);
        }

        // Lock python state
        PyBindAcquireScopedGIL acquire;

        // Evaluate in scope of main module
        PyBindObject scope = PyBindModuleImport("__main__").attr("__dict__");

        // Evaluate a string containing a sequence of statements
        LOG_FORMAT_STATEMENT("Running command '%s'\n", sCommand);
        PyBindExec(sCommand, scope);
    }
    catch (PyBindRuntimeException& error)
    {
        if(sResultsID)
        {
            ModuleResult::SetRunResultID("");
        }
        auto sMessage = error.what();
        error.restore();
        ERROR_FORMAT_STATEMENT("%s\n", sMessage);
        throw STDModuleError(sMessage);
    }
    if(sResultsID)
    {
        ModuleResult::SetRunResultID("");
    }
    return true;
}

extern "C" DLL_PUBLIC bool DLL_RunModuleCommand(const char* sCommand)
{
    return DLL_Internal_RunModuleCommand(sCommand, nullptr);
}

extern "C" DLL_PUBLIC bool DLL_RunModuleCommandResults(const char* sCommand, const char* sResultsID)
{
    return DLL_Internal_RunModuleCommand(sCommand, sResultsID);
}

extern "C" DLL_PUBLIC void DLL_ClearModuleResult(const char* sResultsID)
{
    // Lock API call
    STDLockGuard<STDMutex> lock(g_ModuleMutex);

    // Clear the specific result
    ModuleResult::ClearResult(String(sResultsID));
}

extern "C" DLL_PUBLIC void DLL_ClearAllModuleResults()
{
    // Lock API call
    STDLockGuard<STDMutex> lock(g_ModuleMutex);

    // Clear all results
    ModuleResult::ClearAllResults();
}

extern "C" DLL_PUBLIC bool DLL_DoesModuleResultExist(const char* sResultsID)
{
    // Lock API call
    STDLockGuard<STDMutex> lock(g_ModuleMutex);

    // Determine if result exists
    return ModuleResult::DoesResultExist(String(sResultsID));
}

extern "C" DLL_PUBLIC unsigned int DLL_GetModuleResultSize(const char* sResultsID)
{
    // Lock API call
    STDLockGuard<STDMutex> lock(g_ModuleMutex);

    // Get the result size
    return ModuleResult::GetResult(String(sResultsID)).size();
}

extern "C" DLL_PUBLIC bool DLL_GetModuleResults(const char* sResultsID, char* sResultStr, unsigned int uResultLen)
{
    // Lock API call
    STDLockGuard<STDMutex> lock(g_ModuleMutex);

    // Search for the given result
    String sResult = ModuleResult::GetResult(String(sResultsID));
    if(sResult.empty())
    {
        ERROR_FORMAT_STATEMENT("Cannot get result for ID '%s'\n", sResultsID);
        return false;
    }

    // Copy the result to the given buffer
    strncpy(sResultStr, sResult.c_str(), uResultLen);
    return true;
}

extern "C" DLL_PUBLIC void DLL_VerifyModuleData()
{
    // Lock API call
    STDLockGuard<STDMutex> lock(g_ModuleMutex);

    // Verify trees
    VerifySkillTrees();
    VerifyItemTrees();
}

extern "C" DLL_PUBLIC void DLL_SetUserConfigFolderOverride(const char* sFolder)
{
    // Lock API call
    STDLockGuard<STDMutex> lock(g_ModuleMutex);

    // Set override
    ConfigManager::GetInstance()->SetUserConfigFolderOverride(sFolder);
}

extern "C" DLL_PUBLIC void DLL_SetUserDataFolderOverride(const char* sFolder)
{
    // Lock API call
    STDLockGuard<STDMutex> lock(g_ModuleMutex);

    // Set override
    ConfigManager::GetInstance()->SetUserDataFolderOverride(sFolder);
}

extern "C" DLL_PUBLIC void DLL_SetUserCacheFolderOverride(const char* sFolder)
{
    // Lock API call
    STDLockGuard<STDMutex> lock(g_ModuleMutex);

    // Set override
    ConfigManager::GetInstance()->SetUserCacheFolderOverride(sFolder);
}

extern "C" DLL_PUBLIC void DLL_Start_RunFileScript(const char* sScriptFilename)
{
    // Register signal handler
#ifdef DEBUG
    SignalHandler signalHandler(GetTraceSignals());
#endif

    // Check that the script file exists
    if(!InputFile(sScriptFilename).good())
    {
        ERROR_FORMAT_STATEMENT("Script file '%s' was not found\n", sScriptFilename);
        return;
    }

    // Initialize module
    if (!DLL_InitModule())
    {
        ERROR_STATEMENT("Unable to initialize module");
        return;
    }

    // Run script
    DLL_RunModuleFile(sScriptFilename);

    // Finalize module
    if (!DLL_FinalizeModule())
    {
        ERROR_STATEMENT("Unable to finalize module");
        return;
    }
}

#ifdef WIN32
BOOL WebsocketServerCtrlHandler(DWORD fdwCtrlType)
{
    switch(fdwCtrlType)
    {
    case CTRL_C_EVENT:
    case CTRL_CLOSE_EVENT:
        PRINTF("\nHandling Ctrl event\n");
        WebsocketServer::GetInstance()->Stop();
        return TRUE;
    default:
        return FALSE;
    }
}
BOOL RestServerCtrlHandler(DWORD fdwCtrlType)
{
    switch(fdwCtrlType)
    {
    case CTRL_C_EVENT:
    case CTRL_CLOSE_EVENT:
        PRINTF("\nHandling Ctrl event\n");
        RestServer::GetInstance()->Stop();
        return TRUE;
    default:
        return FALSE;
    }
}
#else
static void WebsocketServerCtrlHandler(int signo)
{
    PRINTF("\nHandling Ctrl event\n");
    WebsocketServer::GetInstance()->Stop();
}
static void RestServerCtrlHandler(int signo)
{
    PRINTF("\nHandling Ctrl event\n");
    RestServer::GetInstance()->Stop();
}
#endif

extern "C" DLL_PUBLIC void DLL_Start_RunWebsocketServer(const char* sHostname, int iPort)
{
    // Register signal handler
#ifdef DEBUG
    SignalHandler signalHandler(GetTraceSignals());
#endif

    // Register control interrupt handler
#ifdef WIN32
    SetConsoleCtrlHandler((PHANDLER_ROUTINE)WebsocketServerCtrlHandler, TRUE);
#else
    struct sigaction sigact;
    sigact.sa_handler = WebsocketServerCtrlHandler;
    sigemptyset(&sigact.sa_mask);
    sigact.sa_flags = 0;
    sigaction(SIGINT, &sigact, NULL);
    sigaction(SIGTERM, &sigact, NULL);
#endif

    // Initialize module
    if (!DLL_InitModule())
    {
        ERROR_STATEMENT("Unable to initialize module");
        return;
    }

    // Start server
    WebsocketServer::GetInstance()->SetHostname(sHostname);
    WebsocketServer::GetInstance()->SetPort(iPort);
    WebsocketServer::GetInstance()->Reset();
    WebsocketServer::GetInstance()->Start();

    // Finalize module
    if (!DLL_FinalizeModule())
    {
        ERROR_STATEMENT("Unable to finalize module");
        return;
    }
}

extern "C" DLL_PUBLIC void DLL_Start_RunRestServer(const char* sHostname, const char* sWebRoot, int iPort, int iThreadCount)
{
    // Register signal handler
#ifdef DEBUG
    SignalHandler signalHandler(GetTraceSignals());
#endif

    // Register control interrupt handler
#ifdef WIN32
    SetConsoleCtrlHandler((PHANDLER_ROUTINE)RestServerCtrlHandler, TRUE);
#else
    struct sigaction sigact;
    sigact.sa_handler = RestServerCtrlHandler;
    sigemptyset(&sigact.sa_mask);
    sigact.sa_flags = 0;
    sigaction(SIGINT, &sigact, NULL);
    sigaction(SIGTERM, &sigact, NULL);
#endif

    // Initialize module
    if (!DLL_InitModule())
    {
        ERROR_STATEMENT("Unable to initialize module");
        return;
    }

    // Start server
    RestServer::GetInstance()->SetHostname(sHostname);
    RestServer::GetInstance()->SetWebRoot(sWebRoot);
    RestServer::GetInstance()->SetPort(iPort);
    RestServer::GetInstance()->SetThreadCount(iThreadCount);
    RestServer::GetInstance()->Reset();
    RestServer::GetInstance()->Start();

    // Finalize module
    if (!DLL_FinalizeModule())
    {
        ERROR_STATEMENT("Unable to finalize module");
        return;
    }
}

};
