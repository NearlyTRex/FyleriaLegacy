// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

// Internal includes
#include "Scene/Scene.h"
#include "Scene/SceneTypes.h"
#include "Scene/SceneManager.h"
#include "Config/ConfigManager.h"
#include "Window/MainWindow.h"
#include "Utility/Converters.h"
#include "Utility/Json.h"
#include "Utility/Constants.h"

namespace Gecko
{

Scene::Scene()
{
}

Scene::~Scene()
{
}

Bool Scene::ParseMessage(const String& sMessage, String& sFunction, StringArray& vArgs)
{
    // Parse json data
    Json jsonData = JsonParse(sMessage);

    // Keys
    const String sKeyFunction = (+SceneMessageKeyType::Function)._to_string();
    const String sKeyArgs = (+SceneMessageKeyType::Args)._to_string();

    // Check function
    if(!jsonData.at(sKeyFunction).is_string())
    {
        return false;
    }

    // Check arguments
    if(!jsonData.at(sKeyArgs).is_array())
    {
        return false;
    }

    // Get function and arguments
    sFunction = jsonData.at(sKeyFunction).get<String>();
    vArgs = jsonData.at(sKeyArgs).get<StringArray>();
    return true;
}

Bool Scene::HandleMessage(const String& sMessage, String& sFunction, StringArray& vArgs)
{
    // Parse message
    if(!ParseMessage(sMessage, sFunction, vArgs))
    {
        return false;
    }

    // Set arguments
    const String sArg1 = (vArgs.size() >= 1) ? vArgs[0] : "";
    const String sArg2 = (vArgs.size() >= 2) ? vArgs[1] : "";
    const String sArg3 = (vArgs.size() >= 3) ? vArgs[2] : "";

    // Check scene function
    const SceneMessageFunctionType eFunctionType = GetEnumFromStringOrNone<SceneMessageFunctionType>(sFunction);
    switch(eFunctionType)
    {
        case SceneMessageFunctionType::SwitchToScene:
            SceneManager::GetInstance()->SwitchToScene(sArg1);
            return true;
        case SceneMessageFunctionType::SubmitForm:
            ProcessForm(sArg1, sArg2);
            SetHtmlContent(GetPageContent());
            return true;
        case SceneMessageFunctionType::ReloadPage:
            SetHtmlContent(GetPageContent());
            return true;
        default:
            break;
    }

    // Nothing was handled
    return false;
}

void Scene::ProcessForm(const String& sAction, const String& sParameters)
{
    // Check input data
    if(sAction.empty() || sParameters.empty())
    {
        ERROR_STATEMENT("Invalid action or parameters");
        return;
    }

    // Check page handler
    if(GetPageHandler())
    {
        // Notify user
        LOG_FORMAT_STATEMENT("Processing form action '{}'\n", sAction.c_str());

        try
        {
            // Get parameters
            StringMap tParameters = ConvertQueryStringToStringMap(sParameters);
            tParameters.insert({"action", sAction});

            // Update page content
            GetPageHandler()->UpdatePageContent(tParameters);
            SetPageContent(GetPageHandler()->GetPageContent());
        }
        catch(STDException& e)
        {
            // Print exception
            ERROR_FORMAT_STATEMENT("Caught exception: '{}'\n", e.what());
        }
        catch(GeneralError& e)
        {
            // Print exception
            ERROR_FORMAT_STATEMENT("Caught exception: '{}'\n", e.what().c_str());
        }

        // Notify user
        LOG_FORMAT_STATEMENT("Processing of action '{}' completed\n", sAction.c_str());
    }
}

void Scene::LoadHtmlFromFile(const String& sFile)
{
    // Load html file
    String sFileContents = GetFileContentsAsString(JoinPathsCanonical(GetDataDirectory(), sFile));
    SetPageContent(sFileContents);
    SetHtmlContent(sFileContents);
}

void Scene::LoadHtmlFromHandler(const WebPageHandlerSharedPtr& pHandler)
{
    // Load html from handler
    if(pHandler)
    {
        String sHandlerContents = pHandler->GetPageContent();
        SetPageContent(sHandlerContents);
        SetHtmlContent(sHandlerContents);
    }
}

void Scene::RunJavascript(const String& sScript)
{
    // Run javascript
    MainWindow::GetInstance()->GetBrowserEngine()->RunJavascript(sScript);
}

void Scene::SetHtmlContent(const String& sHtml)
{
    // Set html
    MainWindow::GetInstance()->GetBrowserEngine()->SetHtmlContent(sHtml);
}

void Scene::DefineJavascriptShortcut(const String& sFunction, const String& sArgs)
{
    // Define shortcut
    MainWindow::GetInstance()->GetBrowserEngine()->DefineJavascriptShortcut(sFunction, sArgs);
}

void Scene::ClearJavascriptShortcut(const String& sFunction)
{
    // Clear shortcut
    MainWindow::GetInstance()->GetBrowserEngine()->ClearJavascriptShortcut(sFunction);
}

void Scene::SetPostCallback(const BrowserEngine::JavascriptCallback& fnCallback)
{
    // Set callback
    MainWindow::GetInstance()->GetBrowserEngine()->SetPostJavascriptCallback(fnCallback);
}

void Scene::SetRunResultCallback(const BrowserEngine::JavascriptCallback& fnCallback)
{
    // Set callback
    MainWindow::GetInstance()->GetBrowserEngine()->SetRunResultJavascriptCallback(fnCallback);
}

void Scene::ClearPostCallback()
{
    // Clear callback
    MainWindow::GetInstance()->GetBrowserEngine()->SetPostJavascriptCallback(nullptr);
}

void Scene::ClearRunResultCallback()
{
    // Clear callback
    MainWindow::GetInstance()->GetBrowserEngine()->SetRunResultJavascriptCallback(nullptr);
}

};
