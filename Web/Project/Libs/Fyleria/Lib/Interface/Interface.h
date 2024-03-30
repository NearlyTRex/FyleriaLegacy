// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#ifndef _GECKO_INTERFACE_H_
#define _GECKO_INTERFACE_H_

#if defined(NO_DLL)
    #define DLL_PUBLIC
#else
    #if defined(_MSC_VER) || defined(__MINGW32__) || defined(__MINGW64__)
        #ifdef BUILDING_DLL
            #define DLL_PUBLIC __declspec(dllexport)
        #else
            #define DLL_PUBLIC __declspec(dllimport)
        #endif
    #elif defined(__GNUC__)
        #define DLL_PUBLIC __attribute__((visibility("default")))
    #else
        #define DLL_PUBLIC
        #pragma warning Unknown dynamic link import/export semantics.
    #endif
#endif

// Initialize module
// This must be run before any other DLL calls
extern "C" DLL_PUBLIC bool DLL_InitModule();

// Finalize module
// This must be run last after all DLL calls are finished
extern "C" DLL_PUBLIC bool DLL_FinalizeModule();

// Run module file
extern "C" DLL_PUBLIC bool DLL_RunModuleFile(const char* sFile);
extern "C" DLL_PUBLIC bool DLL_RunModuleFileResults(const char* sFile, const char* sResultsID);

// Run module command
extern "C" DLL_PUBLIC bool DLL_RunModuleCommand(const char* sCommand);
extern "C" DLL_PUBLIC bool DLL_RunModuleCommandResults(const char* sCommand, const char* sResultsID);

// Clear the results pointed to by the given ID
extern "C" DLL_PUBLIC void DLL_ClearModuleResult(const char* sResultsID);

// Clear all the stored results
extern "C" DLL_PUBLIC void DLL_ClearAllModuleResults();

// Determine if results exist at the given ID
extern "C" DLL_PUBLIC bool DLL_DoesModuleResultExist(const char* sResultsID);

// Get the size of the results from the given ID
extern "C" DLL_PUBLIC unsigned int DLL_GetModuleResultSize(const char* sResultsID);

// Get the results from the given ID
extern "C" DLL_PUBLIC bool DLL_GetModuleResults(const char* sResultsID, char* sResultStr, unsigned int uResultLen);

// Verify module data
extern "C" DLL_PUBLIC void DLL_VerifyModuleData();

// Set user config folder
extern "C" DLL_PUBLIC void DLL_SetUserConfigFolderOverride(const char* sFolder);

// Set user data folder
extern "C" DLL_PUBLIC void DLL_SetUserDataFolderOverride(const char* sFolder);

// Set user cache folder
extern "C" DLL_PUBLIC void DLL_SetUserCacheFolderOverride(const char* sFolder);

// Start program running script
extern "C" DLL_PUBLIC void DLL_Start_RunFileScript(const char* sScriptFilename);

// Start program running web socket server
extern "C" DLL_PUBLIC void DLL_Start_RunWebsocketServer(const char* sHostname, int iPort);

// Start program running rest server
extern "C" DLL_PUBLIC void DLL_Start_RunRestServer(const char* sHostname, const char* sWebRoot, int iPort, int iThreadCount);

#endif
