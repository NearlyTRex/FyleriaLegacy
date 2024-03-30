// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

// Internal includes
#include "Window/MainWindow.h"
#include "Window/BrowserEngineEdgeHtml.h"
#include "Window/BrowserEngineWebKitGtk.h"

namespace Gecko
{

MainWindow::MainWindow()
{
#if defined(PLATFORM_OS_WINDOWS_10)
    SetBrowserEngine(STDMakeSharedPtr<BrowserEngineEdgeHtml>());
#elif defined(PLATFORM_OS_LINUX)
    SetBrowserEngine(STDMakeSharedPtr<BrowserEngineWebKitGtk>());
#else
    #error "No browser engine available for this platform"
#endif
}

MainWindow::~MainWindow()
{
}

};
