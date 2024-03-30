// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

#ifndef _GECKO_BROWSER_ENGINE_H_
#define _GECKO_BROWSER_ENGINE_H_

// Internal includes
#include "Utility/Types.h"
#include "Utility/Macros.h"
#include "Utility/Logging.h"

namespace Gecko
{

// Browser engine interface
class BrowserEngine
{
public:

    // Types
    typedef STDFunction<void(const String&)> JavascriptCallback;

    // Constructor
    BrowserEngine();

    // Destructor
    virtual ~BrowserEngine();

    // Initialize
    virtual Bool Init(const String& sTitle, Int iWidth, Int iHeight, Bool bResizable) = 0;

    // Shutdown
    virtual void Shutdown() = 0;

    // Navigate to url
    virtual void Navigate(const String& sUrl) = 0;

    // Inject stylesheet
    virtual void InjectStylesheet(const String& sStyle) = 0;

    // Inject stylesheet file
    virtual void InjectStylesheetFile(const String& sFile) = 0;

    // Inject javascript
    virtual void InjectJavascript(const String& sScript) = 0;

    // Inject javascript file
    virtual void InjectJavascriptFile(const String& sFile) = 0;

    // Remove all injected data
    virtual void RemoveAllInjectedData() = 0;

    // Run javascript
    virtual void RunJavascript(const String& sScript) = 0;

    // Set html content
    virtual void SetHtmlContent(const String& sHtml) = 0;

    // Set html content file
    virtual void SetHtmlContentFile(const String& sFile) = 0;

    // Run main loop iteration
    virtual void RunMainLoopIteration(Bool bBlocking) = 0;

    // Define javascript shortcut
    virtual void DefineJavascriptShortcut(const String& sFunction, const String& sArgs);

    // Clear javascript shortcut
    virtual void ClearJavascriptShortcut(const String& sFunction);

    // Shutting down
    MAKE_RAW_TYPE_ACCESSORS(IsShuttingDown, Bool);

    // Post (Javascript -> C++) callback
    MAKE_RAW_TYPE_ACCESSORS(PostJavascriptCallback, JavascriptCallback);

    // Run result (C++ -> Javascript) callback
    MAKE_RAW_TYPE_ACCESSORS(RunResultJavascriptCallback, JavascriptCallback);
};

// Typedefs
MAKE_COMMON_TYPEDEFS(BrowserEngine);

};

#endif
