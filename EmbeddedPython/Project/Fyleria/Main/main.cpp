// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

// Internal includes
#include "Main/Application.h"
#include "Config/ConfigManager.h"
#include "Utility/Logging.h"
#include "Utility/Types.h"
#include "Utility/Standard.h"
#include "Utility/Boost.h"
#include "Utility/StackTrace.h"
#include "Utility/Filesystem.h"

// Main
#if defined(PLATFORM_OS_WINDOWS)
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
#else
int main(int argc, char** argv)
#endif
{
    // Register signal handler
#ifdef DEBUG
    Gecko::RegisterSignalHandler();
#endif

    try
    {
        // Create save folder
        if(!Gecko::DoesPathExist(Gecko::GetSaveDirectory()))
        {
            Gecko::CreateNewDirectory(Gecko::GetSaveDirectory());
        }

        // Create log folder
        if(!Gecko::DoesPathExist(Gecko::GetLogDirectory()))
        {
            Gecko::CreateNewDirectory(Gecko::GetLogDirectory());
        }

        // Setup logging
        SETUP_FILE_LOGGING(Log, Gecko::JoinPaths(Gecko::GetLogDirectory(), Gecko::GetLogFile()));

        // Check data folder
        if(!Gecko::DoesPathExist(Gecko::GetDataDirectory()))
        {
            ERROR_STATEMENT("Missing data folder, stopping.");
            return EXIT_FAILURE;
        }

        // Run application
        Gecko::Application app;
        app.Run();
        return EXIT_SUCCESS;
    }
    catch (STDException& e)
    {
        ERROR_FORMAT_STATEMENT("Caught exception: {}", e.what());
        return EXIT_FAILURE;
    }
}
