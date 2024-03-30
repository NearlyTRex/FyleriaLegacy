// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

// Internal includes
#include "Window/BrowserEngineEdgeHtml.h"
#include "Scene/SceneManager.h"
#include "Scene/SceneTypes.h"
#include "Config/ConfigManager.h"
#include "Utility/Filesystem.h"
#include "Utility/Constants.h"
#include "Utility/Converters.h"

// EdgeHTML is available for Windows 10 only
#if defined(PLATFORM_OS_WINDOWS_10)

namespace Gecko
{

BrowserEngineEdgeHtml::BrowserEngineEdgeHtml()
{
}

BrowserEngineEdgeHtml::~BrowserEngineEdgeHtml()
{
}

LRESULT CALLBACK WndProcStatic(HWND pWindowHandle, UINT uMessage, WPARAM iWordParam, LPARAM iLongParam)
{
    // Handle window message
    Bool bHandled = false;
    switch(uMessage)
    {
        case WM_CLOSE:
        {
            // Destroy window
            DestroyWindow(pWindowHandle);
            bHandled = true;
            break;
        }
        case WM_DESTROY:
        {
            // Stop program
            PostQuitMessage(0);
            bHandled = true;
            break;
        }
        default:
        {
            break;
        }
    }
    return (bHandled) ? 0 : DefWindowProc(pWindowHandle, uMessage, iWordParam, iLongParam);
}

winrt::Windows::Foundation::Rect GetBoundsRectFromWindow(HWND pHandle)
{
    // Get window rect
    RECT windowRect = {0};
    if(!GetWindowRect(pHandle, &windowRect))
    {
        return winrt::Windows::Foundation::Rect();
    }

    // Create bounds rect
    winrt::Windows::Foundation::Rect boundsRect;
    boundsRect.X = 0;
    boundsRect.Y = 0;
    boundsRect.Width = static_cast<float>(windowRect.right - windowRect.left);
    boundsRect.Height = static_cast<float>(windowRect.bottom - windowRect.top);
    return boundsRect;
}

typedef struct
{
    BYTE bWidth;                // Width, in pixels, of the image
    BYTE bHeight;               // Height, in pixels, of the image
    BYTE bColorCount;           // Number of colors in image (0 if >=8bpp)
    BYTE bReserved;             // Reserved ( must be 0)
    WORD wPlanes;               // Color Planes
    WORD wBitCount;             // Bits per pixel
    DWORD dwBytesInRes;         // How many bytes in this resource?
    DWORD dwImageOffset;        // Where in the file is this image?
} ICONDIRENTRY, *LPICONDIRENTRY;

typedef struct
{
    WORD idReserved;            // Reserved (must be 0)
    WORD idType;                // Resource Type (1 for icons)
    WORD idCount;               // How many images?
    ICONDIRENTRY idEntries[1];  // An entry for each image (idCount of 'em)
} ICONDIR, *LPICONDIR;

typedef struct
{
    BITMAPINFOHEADER icHeader;  // DIB header
    RGBQUAD icColors[1];        // Color table
    BYTE icXOR[1];              // DIB bits for XOR mask
    BYTE icAND[1];              // DIB bits for AND mask
} ICONIMAGE, *LPICONIMAGE;

HICON GetIconFromFile(const String& sPath)
{
    // Get bytes from file
    UByteArray vBytes = GetFileContentsAsByteArray(sPath);
    if(vBytes.empty())
    {
        return NULL;
    }

    // Get the icon offset
    Int iFileSize = static_cast<Int>(vBytes.size());
    Int iOffset = (3 * sizeof(WORD)) + (1 * sizeof(ICONDIRENTRY));
    if(iFileSize <= iOffset)
    {
        return NULL;
    }

    // Create the icon
    return CreateIconFromResourceEx(vBytes.data() + iOffset, iFileSize - iOffset, TRUE, 0x00030000, 0, 0, LR_DEFAULTCOLOR | LR_SHARED);
}

Bool BrowserEngineEdgeHtml::Init(const String& sTitle, Int iWidth, Int iHeight, Bool bResizable)
{
    // Initialize windows runtime to single thread
    winrt::init_apartment(winrt::apartment_type::single_threaded);

    // Create window class
    WNDCLASSEX windowClass;
    ZeroMemory(&windowClass, sizeof(WNDCLASSEX));
    const WString& sWindowClassName = L"WebView";

    // Register window class
    HICON hIcon = GetIconFromFile(JoinPathsCanonical(GetDataDirectory(), ICON_FILE_MAIN_WINDOW));
    windowClass.cbSize = sizeof(WNDCLASSEX);
    windowClass.hInstance = GetModuleHandle(nullptr);
    windowClass.lpszClassName = sWindowClassName.c_str();
    windowClass.lpfnWndProc = WndProcStatic;
    windowClass.hIcon = hIcon;
    windowClass.hIconSm = hIcon;
    if(!RegisterClassEx(&windowClass))
    {
        return false;
    }

    // Create main window
    SetMainWindow(CreateWindow(
        sWindowClassName.c_str(),
        ConvertStringToWideString(sTitle).c_str(),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        iWidth,
        iHeight,
        nullptr,
        nullptr,
        GetModuleHandle(nullptr),
        nullptr)
    );

    // Check if window was created
    if(!GetMainWindow())
    {
        return false;
    }

    // Store window pointer
    SetWindowLongPtr(GetMainWindow(), GWLP_USERDATA, (LONG_PTR)this);

    // Set title
    SetWindowText(GetMainWindow(), ConvertStringToWideString(sTitle).c_str());

    // Set sizing
    RECT sizeRect;
    sizeRect.left = 50;
    sizeRect.top = 50;
    sizeRect.right = iWidth;
    sizeRect.bottom = iHeight;
    AdjustWindowRect(&sizeRect, WS_OVERLAPPEDWINDOW, 0);

    // Set window position
    SetWindowPos(
        GetMainWindow(),
        nullptr,
        sizeRect.left,
        sizeRect.top,
        sizeRect.right - sizeRect.left,
        sizeRect.bottom - sizeRect.top,
        SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED
    );

    // Inject starting javascript / css
    InjectJavascript("(function(){window.external.invoke = s => window.external.notify(s)})();");
    InjectJavascriptFile(LIB_FILE_COMMON_JS);
    InjectStylesheetFile(LIB_FILE_BOOTSTRAP_CSS);
    InjectJavascriptFile(LIB_FILE_BOOTSTRAP_JS);
    InjectJavascriptFile(LIB_FILE_JQUERY_JS);
    InjectJavascriptFile(LIB_FILE_PHASER_JS);

    // Create web view control completion handler
    auto fnCompletionHandler = [this](const auto& sender, const auto& args)
    {
        // Set web view control
        SetWebViewControl(sender.GetResults());

        // Update settings
        GetWebViewControl().Settings().IsScriptNotifyAllowed(true);
        GetWebViewControl().Settings().IsJavaScriptEnabled(true);
        GetWebViewControl().IsVisible(true);

        // Set script notify handler
        GetWebViewControl().ScriptNotify([this](const auto& sender, const auto& args)
            {
                // Call callback
                auto fnCallback = GetPostJavascriptCallback();
                if (fnCallback)
                {
                    fnCallback(winrt::to_string(args.Value()));
                }
            }
        );

        // Set navigation starting handler
        GetWebViewControl().NavigationStarting([this](const auto& sender, const auto& args)
            {
            }
        );

        // Set navigation completed handler
        GetWebViewControl().NavigationCompleted([this](const auto& sender, const auto& args)
            {
            }
        );

        // Set content loading handler
        GetWebViewControl().ContentLoading([this](const auto& sender, const auto& args)
            {
            }
        );

        // Set DOM content loaded handler
        GetWebViewControl().DOMContentLoaded([this](const auto& sender, const auto& args)
            {
            }
        );

        // Set new window requested handler
        GetWebViewControl().NewWindowRequested([this](const auto& sender, const auto& args)
            {
                // Navigate to the new URI
                GetWebViewControl().Navigate(args.Uri());
            }
        );

        // Show window
        ShowWindow(GetMainWindow(), SW_SHOW);
        UpdateWindow(GetMainWindow());
        SetFocus(GetMainWindow());

        // Navigate to starting page
        Navigate(STARTING_URI);

        // Switch to starting scene
        SceneManager::GetInstance()->SwitchToScene((+SceneType::Intro)._to_string());
    };

    // Create web view control process
    SetWebViewControlProcess(winrt::Windows::Web::UI::Interop::WebViewControlProcess());

    // Create web view control
    GetWebViewControlProcess().CreateWebViewControlAsync(
        (FixedSigned64)GetMainWindow(),
        GetBoundsRectFromWindow(GetMainWindow())
    ).Completed(fnCompletionHandler);
    return true;
}

void BrowserEngineEdgeHtml::Shutdown()
{
    // Mark as shutting down
    SetIsShuttingDown(true);
}

void BrowserEngineEdgeHtml::Navigate(const String& sUrl)
{
    // Navigate to url
    GetWebViewControl().Navigate(winrt::Windows::Foundation::Uri::Uri(winrt::to_hstring(sUrl)));
}

void BrowserEngineEdgeHtml::InjectStylesheet(const String& sStyle)
{
    // Add to injectable stylesheets
    SetInjectedStylesheets(GetInjectedStylesheets() + sStyle);
}

void BrowserEngineEdgeHtml::InjectStylesheetFile(const String& sFile)
{
    // Inject file contents
    String sFileContents = GetFileContentsAsString(JoinPathsCanonical(GetDataDirectory(), sFile));
    InjectStylesheet(sFileContents);
}

void BrowserEngineEdgeHtml::InjectJavascript(const String& sScript)
{
    // Add to injectable javascript
    SetInjectedJavascript(GetInjectedJavascript() + sScript);
}

void BrowserEngineEdgeHtml::InjectJavascriptFile(const String& sFile)
{
    // Inject file contents
    String sFileContents = GetFileContentsAsString(JoinPathsCanonical(GetDataDirectory(), sFile));
    InjectJavascript(sFileContents);
}

void BrowserEngineEdgeHtml::RemoveAllInjectedData()
{
    // Clear injectable stylesheets
    SetInjectedStylesheets("");

    // Clear injectable javascript
    SetInjectedJavascript("");
}

void BrowserEngineEdgeHtml::RunJavascript(const String& sScript)
{
}

void BrowserEngineEdgeHtml::SetHtmlContent(const String& sHtml)
{
    // Navigate to the given html string
    GetWebViewControl().NavigateToString(winrt::to_hstring(sHtml));
}

void BrowserEngineEdgeHtml::SetHtmlContentFile(const String& sFile)
{
    // Set document html
    String sFileContents = GetFileContentsAsString(sFile);
    SetHtmlContent(sFileContents);
}

void BrowserEngineEdgeHtml::RunMainLoopIteration(Bool bBlocking)
{
    // Create message
    MSG message;
    ZeroMemory(&message, sizeof(MSG));

    // Fill message
    if(bBlocking)
    {
        GetMessage(&message, 0, 0, 0);
    }
    else
    {
        PeekMessage(&message, 0, 0, 0, PM_REMOVE);
    }

    // Check message contents
    switch(message.message)
    {
        case WM_QUIT:
            Shutdown();
            break;
        default:
            TranslateMessage(&message);
            DispatchMessage(&message);
            break;
    }
}

};

#endif /* PLATFORM_OS_WINDOWS_10 */
