// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

// Internal includes
#include "Scene/SceneToolMain.h"
#include "Window/MainWindow.h"
#include "Utility/Constants.h"

namespace Gecko
{

SceneToolMain::SceneToolMain()
    : Scene()
{
}

SceneToolMain::~SceneToolMain()
{
}

void SceneToolMain::Start()
{
    // Register callbacks
    SetPostCallback(STDBindFunc(&SceneToolMain::OnMessageReceived, this, STDPlaceholder1));

    // Load page content
    LoadHtmlFromFile(PAGE_FILE_TOOL_MAIN);
}

void SceneToolMain::Finish()
{
    // Clear callbacks
    ClearPostCallback();
}

void SceneToolMain::Update()
{
}

void SceneToolMain::Input()
{
}

void SceneToolMain::OnMessageReceived(const String& sMessage)
{
    // Function / arguments
    String sFunction;
    StringArray vArgs;

    // Handle common messages
    if(Scene::HandleMessage(sMessage, sFunction, vArgs))
    {
        return;
    }
}

};
