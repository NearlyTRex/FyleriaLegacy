// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#ifndef _APP_WINDOW_H_
#define _APP_WINDOW_H_

// System includes
#include <string>
#include <list>
#include <map>
#include <vector>
#include <iostream>

// External includes
#include <json.hpp>
#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>

// QT includes
#include <QtGui/QtGui>
#include <QtWebKit/QtWebKit>
#include <QtWebKitWidgets/QtWebKitWidgets>
#include <QtNetwork/QNetworkAccessManager>

// Internal includes
#include <Interface/Interface.h>

// Local includes
#include "Logging.h"

// Window manager
class WindowManager
{
public:
    // Hostname
    static void SetHostname(const std::string& sHostname);
    static const std::string& GetHostname();

    // Web URL
    static void SetWindowWebUrl(const std::string& sWebUrl);
    static const std::string& GetWindowWebUrl();

    // Web Root
    static void SetWindowWebRoot(const std::string& sWebRoot);
    static const std::string& GetWindowWebRoot();

    // Window width
    static void SetWindowWidth(int iWidth);
    static int GetWindowWidth();

    // Window height
    static void SetWindowHeight(int iHeight);
    static int GetWindowHeight();

    // Window fullscreen
    static void SetWindowFullscreen(bool bFullscreen);
    static bool GetWindowFullscreen();

    // Allow vertical scrolling window
    static void SetWindowAllowVerticalScroll(bool bAllow);
    static bool GetWindowAllowVerticalScroll();

    // Allow horizontal scrolling window
    static void SetWindowAllowHorizontalScroll(bool bAllow);
    static bool GetWindowAllowHorizontalScroll();

    // Allow window context menu
    static void SetWindowAllowContextMenu(bool bAllow);
    static bool GetWindowAllowContextMenu();
};

#endif
