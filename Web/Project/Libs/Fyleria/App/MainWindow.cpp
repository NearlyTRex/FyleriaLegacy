// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#include "MainWindow.h"
#include "WebPage.h"

MainWindow::MainWindow()
    : QMainWindow()
    , m_pView()
    , m_pPage()
    , m_pNet()
{
}

MainWindow::~MainWindow()
{
}

void MainWindow::Init()
{
    // Create web view
    m_pView = QSharedPointer<QWebView>::create(this);
    if(m_pView.isNull())
    {
        throw;
    }

    // Create custom page object
    m_pPage = QSharedPointer<WebPage>::create();
    if(m_pPage.isNull())
    {
        throw;
    }

    // Set the web page object
    m_pView->setPage(m_pPage.data());

    // Create custom network manager
    m_pNet = QSharedPointer<NetworkAccessManager>::create(this, m_pPage->networkAccessManager());
    if(m_pNet.isNull())
    {
        throw;
    }

    // Set our custom network manager
    m_pPage->setNetworkAccessManager(m_pNet.data());

    // Set window title
    setWindowTitle("Fyleria");

    // Set window flags
    Qt::WindowFlags flags = windowFlags();
    flags |= Qt::CustomizeWindowHint;
    flags |= Qt::WindowCloseButtonHint;
    flags |= Qt::WindowMinMaxButtonsHint;
    setWindowFlags(flags);

    // Set width
    setFixedWidth(WindowManager::GetWindowWidth());

    // Set height
    setFixedHeight(WindowManager::GetWindowHeight());

    // Vertical scrollbar
    m_pPage->mainFrame()->setScrollBarPolicy(Qt::Vertical,
        WindowManager::GetWindowAllowVerticalScroll() ? Qt::ScrollBarAsNeeded : Qt::ScrollBarAlwaysOff);

    // Horizontal scrollbar
    m_pPage->mainFrame()->setScrollBarPolicy(Qt::Horizontal,
        WindowManager::GetWindowAllowHorizontalScroll() ? Qt::ScrollBarAsNeeded : Qt::ScrollBarAlwaysOff);

    // Context menu
    m_pView->setContextMenuPolicy(
        WindowManager::GetWindowAllowContextMenu() ? Qt::DefaultContextMenu : Qt::PreventContextMenu);

    // Update settings
    m_pView->settings()->setAttribute(QWebSettings::AutoLoadImages, 1);
    m_pView->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, 1);
    m_pView->settings()->setAttribute(QWebSettings::JavascriptEnabled, 1);
    m_pView->settings()->setAttribute(QWebSettings::LocalContentCanAccessRemoteUrls, 1);
    m_pView->settings()->setAttribute(QWebSettings::LocalContentCanAccessFileUrls, 1);

    // Start the web view
    setCentralWidget(m_pView.data());

    // Connect slots
    connect(m_pNet.data(), SIGNAL(finished(QNetworkReply*)), this, SLOT(onFinished(QNetworkReply*)));

    // Load the home page
    m_pView->load(QUrl(WindowManager::GetWindowWebUrl().c_str()));
}

void MainWindow::Show()
{
    if(WindowManager::GetWindowFullscreen())
    {
        showFullScreen();
    }
    else
    {
        showNormal();
    }
}

void MainWindow::onFinished(QNetworkReply* pReply)
{
    // Was there an error?
    if(pReply->error() == QNetworkReply::NoError)
    {
        return;
    }

    // Log network error
    LOG_FORMAT_STATEMENT(
        "\n--- Network reply ---\n"
        " URL     : %s\n"
        " Status  : %d\n"
        " Message : '%s'\n\n"
        , pReply->url().path().toUtf8().data()
        , (int)pReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt()
        , pReply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toByteArray().data()
    );
}

void MainWindow::keyPressEvent(QKeyEvent* pEvent)
{
    switch(pEvent->key())
    {
        case Qt::Key_Return:
        case Qt::Key_Enter:
            if (pEvent->modifiers() == Qt::AltModifier)
            {
                WindowManager::SetWindowFullscreen(!WindowManager::GetWindowFullscreen());
                Show();
            }
            break;
        default:
            QMainWindow::keyPressEvent(pEvent);
            break;
    }
}
