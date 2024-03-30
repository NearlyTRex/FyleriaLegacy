// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

// Internal includes
#include "Scene/SceneToolCharacter.h"
#include "Web/WebPageHandlerCharacterTool.h"

namespace Gecko
{

SceneToolCharacter::SceneToolCharacter()
    : Scene()
{
    // Create handler
    SetPageHandler(STDMakeSharedPtr<WebPageHandlerCharacterTool>());
}

SceneToolCharacter::~SceneToolCharacter()
{
}

void SceneToolCharacter::Start()
{
    // Register callbacks
    SetPostCallback(STDBindFunc(&SceneToolCharacter::OnMessageReceived, this, STDPlaceholder1));

    // Load page content
    LoadHtmlFromHandler(GetPageHandler());
}

void SceneToolCharacter::Finish()
{
    // Clear callbacks
    ClearPostCallback();
}

void SceneToolCharacter::Update()
{
}

void SceneToolCharacter::Input()
{
}

void SceneToolCharacter::OnMessageReceived(const String& sMessage)
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
