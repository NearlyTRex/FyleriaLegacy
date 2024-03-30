// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

// Internal includes
#include "Config/ConfigManager.h"
#include "Utility/Assert.h"
#include "Utility/Constants.h"
#include "Utility/Converters.h"
#include "Utility/Logging.h"
#include "Utility/Types.h"
#include "Utility/Python.h"
#include "Utility/StackTrace.h"
#include "Utility/Filesystem.h"
#include "Utility/Errors.h"

namespace Gecko
{

STDMutex g_PythonMutex;

Bool InitPython()
{
    // Lock API call
    STDLockGuard<STDMutex> lock(g_PythonMutex);

    // Check python library
    String sPythonLibFile = JoinPathsCanonical(GetDataDirectory(), PYTHON_FILE);
    LOG_FORMAT_STATEMENT("Loading python library '{}'\n", sPythonLibFile.c_str());
    if(!DoesPathExist(sPythonLibFile))
    {
        ERROR_FORMAT_STATEMENT("Python library '{}' could not be found\n",
            sPythonLibFile.c_str());
        return false;
    }

    // Get python path separator
#if defined(PLATFORM_OS_WINDOWS)
    String sPathSeparator = ";";
#else
    String sPathSeparator = ":";
#endif

    // Generate python path
    LOG_STATEMENT("Generating python path...");
    String sPythonPath = sPathSeparator + sPythonLibFile + sPathSeparator;
    WString sPythonPathW = ConvertStringToWideString(sPythonPath);
    LOG_FORMAT_STATEMENT("Generated python path is '{}'\n", sPythonPath.c_str());

    // Skip site usage and ignore environment variables
    Py_NoSiteFlag++;
    Py_NoUserSiteDirectory++;
    Py_IgnoreEnvironmentFlag++;
#ifdef DEBUG
    Py_VerboseFlag++;
#endif

    // Set python home
#ifdef Py_USING_UNICODE
    Py_SetPythonHome(const_cast<wchar_t*>(sPythonPathW.c_str()));
    Py_SetPath(sPythonPathW.c_str());
#else
    Py_SetPythonHome(const_cast<char*>(sPythonPath.c_str()));
    Py_SetPath(sPythonPath.c_str());
#endif

    // Initialize interpreter
    LOG_STATEMENT("Initializing python interpreter");
    PyBindInitializeInterpreter(false);
    LOG_STATEMENT("Finished initializing python interpreter");

    // Import basic modules
    PyRun_SimpleString("import os");
    PyRun_SimpleString("import sys");

    // Initialization finished!
    LOG_STATEMENT("Python successfully initialized");
    return true;
}

Bool FinalizePython()
{
    // Lock API call
    STDLockGuard<STDMutex> lock(g_PythonMutex);

    // Finalize interpreter
    LOG_STATEMENT("Finalizing python interpreter");
    PyBindFinalizeInterpreter();
    LOG_STATEMENT("Finished finalizing python interpreter");

    // Finalization finished!
    LOG_STATEMENT("Python successfully finalized");
    return true;
}

Bool RunPythonFile(const String& sFile)
{
    // Lock API call
    STDLockGuard<STDMutex> lock(g_PythonMutex);

    try
    {
        // Lock python state
        PyBindAcquireScopedGIL acquire;

        // Evaluate in scope of main module
        PyBindObject scope = PyBindModuleImport("__main__").attr("__dict__");

        // Evaluate the statements in an separate Python file on disk
        LOG_FORMAT_STATEMENT("Running file '{}'\n", sFile.c_str());
        PyBindEvalFile(sFile.c_str(), scope);
        return true;
    }
    catch (PyBindRuntimeException& error)
    {
        auto sMessage = error.what();
        error.restore();
        ERROR_FORMAT_STATEMENT("{}\n", sMessage);
        THROW_PYTHON_ERROR(sMessage);
    }
    return false;
}

Bool RunPythonCommand(const String& sCommand)
{
    // Lock API call
    STDLockGuard<STDMutex> lock(g_PythonMutex);

    try
    {
        // Lock python state
        PyBindAcquireScopedGIL acquire;

        // Evaluate in scope of main module
        PyBindObject scope = PyBindModuleImport("__main__").attr("__dict__");

        // Evaluate a string containing a sequence of statements
        LOG_FORMAT_STATEMENT("Running command '{}'\n", sCommand.c_str());
        PyBindExec(sCommand.c_str(), scope);
        return true;
    }
    catch (PyBindRuntimeException& error)
    {
        auto sMessage = error.what();
        error.restore();
        ERROR_FORMAT_STATEMENT("{}\n", sMessage);
        THROW_PYTHON_ERROR(sMessage);
    }
    return false;
}

};
