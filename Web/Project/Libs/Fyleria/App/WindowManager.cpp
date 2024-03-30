// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#include "WindowManager.h"

static std::string g_sHostname = "";
static std::string g_sWebUrl = "";
static std::string g_sWebRoot = "";
static int g_iWidth = 1;
static int g_iHeight = 1;
static bool g_bFullscreen = false;
static bool g_bAllowVScroll = false;
static bool g_bAllowHScroll = false;
static bool g_bAllowContextMenu = false;

void WindowManager::SetHostname(const std::string& sHostname)
{
    g_sHostname = sHostname;
}

const std::string& WindowManager::GetHostname()
{
    return g_sHostname;
}

void WindowManager::SetWindowWebUrl(const std::string& sWebUrl)
{
    g_sWebUrl = sWebUrl;
}

const std::string& WindowManager::GetWindowWebUrl()
{
    return g_sWebUrl;
}

void WindowManager::SetWindowWebRoot(const std::string& sWebRoot)
{
    g_sWebRoot = sWebRoot;
}

const std::string& WindowManager::GetWindowWebRoot()
{
    return g_sWebRoot;
}

void WindowManager::SetWindowWidth(int iWidth)
{
    g_iWidth = iWidth;
}

int WindowManager::GetWindowWidth()
{
    return g_iWidth;
}

void WindowManager::SetWindowHeight(int iHeight)
{
    g_iHeight = iHeight;
}

int WindowManager::GetWindowHeight()
{
    return g_iHeight;
}

void WindowManager::SetWindowFullscreen(bool bFullscreen)
{
    g_bFullscreen = bFullscreen;
}

bool WindowManager::GetWindowFullscreen()
{
    return g_bFullscreen;
}

void WindowManager::SetWindowAllowVerticalScroll(bool bAllow)
{
    g_bAllowVScroll = bAllow;
}

bool WindowManager::GetWindowAllowVerticalScroll()
{
    return g_bAllowVScroll;
}

void WindowManager::SetWindowAllowHorizontalScroll(bool bAllow)
{
    g_bAllowHScroll = bAllow;
}

bool WindowManager::GetWindowAllowHorizontalScroll()
{
    return g_bAllowHScroll;
}

void WindowManager::SetWindowAllowContextMenu(bool bAllow)
{
    g_bAllowContextMenu = bAllow;
}

bool WindowManager::GetWindowAllowContextMenu()
{
    return g_bAllowContextMenu;
}
