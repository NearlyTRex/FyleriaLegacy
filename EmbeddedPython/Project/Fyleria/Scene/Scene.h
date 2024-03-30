// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

#ifndef _GECKO_SCENE_H_
#define _GECKO_SCENE_H_

// Internal includes
#include "Window/BrowserEngine.h"
#include "Web/WebPageHandler.h"
#include "Utility/Types.h"
#include "Utility/Macros.h"

namespace Gecko
{

class Scene
{
public:

    // Constructor
    Scene();

    // Destructor
    virtual ~Scene();

    // Start scene
    virtual void Start() = 0;

    // Finish scene
    virtual void Finish() = 0;

    // Update scene
    virtual void Update() = 0;

    // Handle scene input
    virtual void Input() = 0;

protected:

    // Handle message received
    virtual void OnMessageReceived(const String& sMessage) = 0;

    // Parse message and get the function and arguments
    virtual Bool ParseMessage(const String& sMessage, String& sFunction, StringArray& vArgs);

    // Handle message or return false if it could not be handled
    virtual Bool HandleMessage(const String& sMessage, String& sFunction, StringArray& vArgs);

    // Process form
    virtual void ProcessForm(const String& sAction, const String& sParameters);

    // Load html from file
    virtual void LoadHtmlFromFile(const String& sFile);

    // Load html from handler
    virtual void LoadHtmlFromHandler(const WebPageHandlerSharedPtr& pHandler);

    // Run javascript
    virtual void RunJavascript(const String& sScript);

    // Set html content
    virtual void SetHtmlContent(const String& sHtml);

    // Define javascript shortcut
    virtual void DefineJavascriptShortcut(const String& sFunction, const String& sArgs);

    // Clear javascript shortcut
    virtual void ClearJavascriptShortcut(const String& sFunction);

    // Set callbacks
    virtual void SetPostCallback(const BrowserEngine::JavascriptCallback& fnCallback);
    virtual void SetRunResultCallback(const BrowserEngine::JavascriptCallback& fnCallback);

    // Clear callbacks
    virtual void ClearPostCallback();
    virtual void ClearRunResultCallback();

    // Page content
    MAKE_RAW_TYPE_ACCESSORS(PageContent, String);

    // Page handler
    MAKE_RAW_TYPE_ACCESSORS(PageHandler, WebPageHandlerSharedPtr);
};

// Typedef
MAKE_COMMON_TYPEDEFS(Scene);

};

#endif
