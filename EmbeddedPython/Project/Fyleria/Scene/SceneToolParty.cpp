// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

// Internal includes
#include "Scene/SceneToolParty.h"
#include "Web/WebPageHandlerPartyTool.h"

namespace Gecko
{

SceneToolParty::SceneToolParty()
    : Scene()
{
    // Create handler
    SetPageHandler(STDMakeSharedPtr<WebPageHandlerPartyTool>());
}

SceneToolParty::~SceneToolParty()
{
}

void SceneToolParty::Start()
{
    // Register callbacks
    SetPostCallback(STDBindFunc(&SceneToolParty::OnMessageReceived, this, STDPlaceholder1));

    // Load page content
    LoadHtmlFromHandler(GetPageHandler());
}

void SceneToolParty::Finish()
{
    // Clear callbacks
    ClearPostCallback();
}

void SceneToolParty::Update()
{
}

void SceneToolParty::Input()
{
}

void SceneToolParty::OnMessageReceived(const String& sMessage)
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
