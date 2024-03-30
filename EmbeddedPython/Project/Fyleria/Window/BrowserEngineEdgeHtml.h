// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

#ifndef _GECKO_BROWSER_ENGINE_EDGEHTML_H_
#define _GECKO_BROWSER_ENGINE_EDGEHTML_H_

// EdgeHTML is available for Windows 10 only
#include "Utility/Platform.h"
#if defined(PLATFORM_OS_WINDOWS_10)

// External includes
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <objbase.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Web.UI.Interop.h>

// Internal includes
#include "Window/BrowserEngine.h"
#include "Utility/Types.h"

namespace Gecko
{

// EdgeHtml browser engine
class BrowserEngineEdgeHtml : public BrowserEngine
{
public:

    // Constructor
    BrowserEngineEdgeHtml();

    // Destructor
    virtual ~BrowserEngineEdgeHtml();

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

    // Main window
    MAKE_RAW_TYPE_ACCESSORS(MainWindow, HWND);

    // Web view control
    MAKE_RAW_TYPE_ACCESSORS_INITIAL_VALUE(WebViewControl, winrt::Windows::Web::UI::Interop::WebViewControl, nullptr);

    // Web view control process
    MAKE_RAW_TYPE_ACCESSORS_INITIAL_VALUE(WebViewControlProcess, winrt::Windows::Web::UI::Interop::WebViewControlProcess, nullptr);

    // Injected stylesheets
    MAKE_RAW_TYPE_ACCESSORS(InjectedStylesheets, String);

    // Injected javascript
    MAKE_RAW_TYPE_ACCESSORS(InjectedJavascript, String);
};

// Typedefs
MAKE_COMMON_TYPEDEFS(BrowserEngineEdgeHtml);

};

#endif /* PLATFORM_OS_WINDOWS_10 */

#endif
