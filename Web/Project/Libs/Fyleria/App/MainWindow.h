// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#ifndef _APP_MAIN_WINDOW_H_
#define _APP_MAIN_WINDOW_H_

// Includes
#include "WebPage.h"
#include "NetworkAccessManager.h"
#include "WindowManager.h"

// Main window
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    // Constructor
    MainWindow();

    // Destructor
    virtual ~MainWindow();

    // Initializes the window
    void Init();

    // Show the window
    void Show();

public slots:

    // On network finished handler
    void onFinished(QNetworkReply* pReply);

protected:

    // Handle keypress event
    void keyPressEvent(QKeyEvent* pEvent) override;

private:

    // Web view
    QSharedPointer<QWebView> m_pView;

    // Web page
    QSharedPointer<WebPage> m_pPage;

    // Custom network object
    QSharedPointer<NetworkAccessManager> m_pNet;
};

#endif
