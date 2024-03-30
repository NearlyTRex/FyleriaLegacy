// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

// System includes
#include <string>
#include <iostream>

// External includes
#include <popl.hpp>
#include <json.hpp>

// Internal includes
#include <Interface/Interface.h>

// Local includes
#include "MainWindow.h"

// Main
int main(int argc, char** argv)
{
    // Parse program options
    popl::Switch option_help("h", "help", "Print help message");
    popl::Value<std::string> option_script("s", "script", "Script to run");
    popl::Value<std::string> option_hostname("n", "hostname", "Server host", "localhost");
    popl::Value<std::string> option_webroot("o", "webroot", "Server web root", "Web");
    popl::Value<int> option_port("p", "port", "Server port", 3080);
    popl::Value<int> option_threads("t", "threads", "Server threads", 1);
    popl::Value<int> option_width("y", "width", "Window width", 1600);
    popl::Value<int> option_height("z", "height", "Window height", 900);
    popl::Switch option_fullscreen("f", "fullscreen", "Fullscreen window");
    popl::Switch option_allow_vscroll("v", "allow_vscroll", "Allow vertical scrolling");
    popl::Switch option_allow_hscroll("u", "allow_hscroll", "Allow horizontal scrolling");
    popl::Switch option_allow_contextmenu("m", "allow_contextmenu", "Allow context menu");
    popl::Switch option_websocket_server("w", "websocket_server", "Run websocket server");
    popl::Switch option_rest_server("r", "rest_server", "Run rest server");
    popl::Switch option_gui("g", "gui", "Run GUI");
    popl::Value<std::string> option_set_user_config_folder("c", "user_config_folder", "Set user config folder");
    popl::Value<std::string> option_set_user_data_folder("d", "user_data_folder", "Set user data folder");
    popl::Value<std::string> option_set_user_cache_folder("e", "user_cache_folder", "Set user cache folder");
    popl::OptionParser option_parser("Allowed options");
    try
    {
        option_parser
            .add(option_help)
            .add(option_script)
            .add(option_hostname)
            .add(option_webroot)
            .add(option_port)
            .add(option_threads)
            .add(option_width)
            .add(option_height)
            .add(option_fullscreen)
            .add(option_allow_vscroll)
            .add(option_allow_hscroll)
            .add(option_allow_contextmenu)
            .add(option_websocket_server)
            .add(option_rest_server)
            .add(option_gui)
            .add(option_set_user_config_folder)
            .add(option_set_user_data_folder)
            .add(option_set_user_cache_folder);
        option_parser.parse(argc, argv);
    }
    catch (std::invalid_argument e)
    {
        LOG_FORMAT_STATEMENT("%s\n", e.what());
        return -1;
    }

    // Set user folders
    if (option_set_user_config_folder.isSet())
    {
        DLL_SetUserConfigFolderOverride(option_set_user_config_folder.getValue().c_str());
    }
    if (option_set_user_data_folder.isSet())
    {
        DLL_SetUserDataFolderOverride(option_set_user_data_folder.getValue().c_str());
    }
    if (option_set_user_cache_folder.isSet())
    {
        DLL_SetUserCacheFolderOverride(option_set_user_cache_folder.getValue().c_str());
    }

    // Run script
    if (option_script.isSet())
    {
        std::string sScriptToRun = option_script.getValue();
        DLL_Start_RunFileScript(sScriptToRun.c_str());
        return 0;
    }

    // Run websocket server
    if (option_websocket_server.isSet())
    {
        std::string sHostname = option_hostname.getValue();
        int iPort = option_port.getValue();
        DLL_Start_RunWebsocketServer(sHostname.c_str(), iPort);
        return 0;
    }

    // Run rest server
    if (option_rest_server.isSet())
    {
        std::string sHostname = option_hostname.getValue();
        std::string sWebRoot = option_webroot.getValue();
        int iPort = option_port.getValue();
        int iThreadCount = option_threads.getValue();
        DLL_Start_RunRestServer(sHostname.c_str(), sWebRoot.c_str(), iPort, iThreadCount);
        return 0;
    }

    // Run gui
    if (option_gui.isSet())
    {
        // Initialize module
        if(!DLL_InitModule())
        {
            return -1;
        }

        // Set window options
        WindowManager::SetHostname(option_hostname.getValue());
        if(option_port.getValue() > 0)
        {
            WindowManager::SetWindowWebUrl((boost::format("http://%1%:%2%/index.html")
                % option_hostname.getValue()
                % option_port.getValue()).str());
        }
        else
        {
            WindowManager::SetWindowWebUrl((boost::format("http://%1%/index.html")
                % option_hostname.getValue()).str());
        }
        WindowManager::SetWindowWebRoot(option_webroot.getValue());
        WindowManager::SetWindowWidth(option_width.getValue());
        WindowManager::SetWindowHeight(option_height.getValue());
        WindowManager::SetWindowFullscreen(option_fullscreen.isSet());
        WindowManager::SetWindowAllowVerticalScroll(option_allow_vscroll.isSet());
        WindowManager::SetWindowAllowHorizontalScroll(option_allow_hscroll.isSet());
        WindowManager::SetWindowAllowContextMenu(option_allow_contextmenu.isSet());

        // Initialize application object
        QApplication app(argc, argv);

        // Create main window
        std::shared_ptr<MainWindow> pWindow = std::make_shared<MainWindow>();
        if (!pWindow)
        {
            return -1;
        }

        // Initialize the window
        pWindow->Init();

        // Show the window
        pWindow->Show();

        // Run the app
        int ret = app.exec();

        // Finalize module
        if(!DLL_FinalizeModule())
        {
            return -1;
        }

        // Finish
        return ret;
    }

    // Print auto-generated help message
    if (option_help.count() || argc <= 1)
    {
        std::cout << option_parser << std::endl;
        return 0;
    }

    // Unknown options
    if (option_parser.unknownOptions().size())
    {
        for (const auto& unknown_option: option_parser.unknownOptions())
        {
            std::cout << "Unknown option: " << unknown_option << std::endl;
        }
        std::cout << option_parser << std::endl;
    }
    return 0;
}
