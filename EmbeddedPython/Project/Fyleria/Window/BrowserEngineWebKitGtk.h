// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

#ifndef _GECKO_BROWSER_ENGINE_WEBKITGTK_H_
#define _GECKO_BROWSER_ENGINE_WEBKITGTK_H_

// Linux only
#include "Utility/Platform.h"
#if defined(PLATFORM_OS_LINUX)

// External includes
#include <JavaScriptCore/JavaScript.h>
#include <gtk/gtk.h>
#include <webkit2/webkit2.h>

// Internal includes
#include "Window/BrowserEngine.h"
#include "Utility/Types.h"

namespace Gecko
{

// WebKitGtk browser engine
class BrowserEngineWebKitGtk : public BrowserEngine
{
public:

    // Constructor
    BrowserEngineWebKitGtk();

    // Destructor
    virtual ~BrowserEngineWebKitGtk();

    // Initialize
    virtual Bool Init(const String& sTitle, Int iWidth, Int iHeight, Bool bResizable) override;

    // Shutdown
    virtual void Shutdown() override;

    // Navigate to url
    virtual void Navigate(const String& sUrl) override;

    // Inject stylesheet
    virtual void InjectStylesheet(const String& sStyle) override;

    // Inject stylesheet file
    virtual void InjectStylesheetFile(const String& sFile) override;

    // Inject javascript
    virtual void InjectJavascript(const String& sScript) override;

    // Inject javascript file
    virtual void InjectJavascriptFile(const String& sFile) override;

    // Remove all injected data
    virtual void RemoveAllInjectedData() override;

    // Run javascript
    virtual void RunJavascript(const String& sScript) override;

    // Set html content
    virtual void SetHtmlContent(const String& sHtml) override;

    // Set html content file
    virtual void SetHtmlContentFile(const String& sFile) override;

    // Run main loop iteration
    virtual void RunMainLoopIteration(Bool bBlocking) override;

    // Get javascript result string
    String GetJavascriptResultString(WebKitJavascriptResult* pResult);

    // Main window
    MAKE_PRIMITIVE_TYPE_ACCESSORS(MainWindow, GtkWidget*);

    // Main window
    MAKE_PRIMITIVE_TYPE_ACCESSORS(WebView, GtkWidget*);
};

// Typedefs
MAKE_COMMON_TYPEDEFS(BrowserEngineWebKitGtk);

};

#endif /* PLATFORM_OS_LINUX */

#endif
