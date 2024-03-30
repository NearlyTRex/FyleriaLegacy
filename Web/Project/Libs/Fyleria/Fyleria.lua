-- Configuration
libFyleria_srcdir_lib = "Libs/Fyleria/Lib/"
libFyleria_srcdir_app = "Libs/Fyleria/App/"

-- Includes
libFyleria_includedirs = {
    libFyleria_srcdir_lib
}
appFyleria_includedirs = {
    libFyleria_srcdir_lib,
    libFyleria_srcdir_app
}
if os.host() == "linux" then
    table.insert(appFyleria_includedirs, "/usr/include/qt5/")
    table.insert(appFyleria_includedirs, "/usr/include/x86_64-linux-gnu/qt5/")
end

-- Defines
libFyleria_defines = {
    "BUILDING_DLL"
}
libFyleria_debugdefines = {
    "DEBUG"
}
libFyleria_releasedefines = {
    "NDEBUG"
}
appFyleria_defines = {
    "QT_NO_VERSION_TAGGING"
}
appFyleria_debugdefines = {
    "DEBUG"
}
appFyleria_releasedefines = {
    "NDEBUG"
}

-- Options
libFyleria_buildoptions = {
}
appFyleria_buildoptions = {
}
libFyleria_linkoptions = {
}
appFyleria_linkoptions = {
}
if os.host() == "linux" then
    table.insert(libFyleria_buildoptions, "-Wall")
    table.insert(libFyleria_buildoptions, "-Wfatal-errors")
end

-- Libs
libFyleria_libs = {
    "Assert",
    "BackwardCPP",
    "Boost",
    "CppFS",
    "FantasyName",
    "MicroPather",
    "Pistache",
    "Python3",
    "TinyXML2",
    "Zlib"
}
appFyleria_libs = {
    "FyleriaLib"
}
if os.host() == "windows" or _OPTIONS["with-mingw32"] or _OPTIONS["with-mingw64"] then
    table.insert(libFyleria_libs, "wsock32")
    table.insert(appFyleria_libs, "wsock32")
    table.insert(libFyleria_libs, "ws2_32")
    table.insert(appFyleria_libs, "ws2_32")
else
    table.insert(libFyleria_libs, "pthread")
    table.insert(libFyleria_libs, "util")
    table.insert(appFyleria_libs, "Qt5Gui")
    table.insert(appFyleria_libs, "Qt5WebKit")
    table.insert(appFyleria_libs, "Qt5Xml")
    table.insert(appFyleria_libs, "Qt5Widgets")
    table.insert(appFyleria_libs, "Qt5WebKitWidgets")
    table.insert(appFyleria_libs, "Qt5Core")
    table.insert(appFyleria_libs, "Qt5Network")
end

-- Sources
libFyleria_sources = {
    libFyleria_srcdir_lib .. "**.cpp"
}
appFyleria_sources = {
    libFyleria_srcdir_app .. "**.cpp"
}
