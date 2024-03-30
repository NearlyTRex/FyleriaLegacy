// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#include "WebPage.h"

WebPage::WebPage()
    : QWebPage()
{
}

WebPage::~WebPage()
{
}

void WebPage::javaScriptConsoleMessage(const QString& sMessage, int ilineNumber, const QString& sSourceID)
{
    LOG_FORMAT_STATEMENT("Javascript Console : %s(%d): %s\n", sSourceID.toUtf8().data(), ilineNumber, sMessage.toUtf8().data());
}
