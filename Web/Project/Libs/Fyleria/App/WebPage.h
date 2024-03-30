// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#ifndef _APP_WEB_PAGE_H_
#define _APP_WEB_PAGE_H_

// Includes
#include "WindowManager.h"

// Web page
class WebPage : public QWebPage
{
    Q_OBJECT

public:

    // Constructor
    WebPage();

    // Destructor
    virtual ~WebPage();

protected:

    // Javascript error message callback
    virtual void javaScriptConsoleMessage(const QString& sMessage, int ilineNumber, const QString& sSourceID) override;
};

#endif
