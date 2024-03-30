-- Configuration
appFyleria_srcdir = "Fyleria/"

-- Includes
appFyleria_includedirs = {
    appFyleria_srcdir
}

-- Defines
appFyleria_defines = {
}
appFyleria_debugdefines = {
    "DEBUG"
}
appFyleria_releasedefines = {
    "NDEBUG"
}
if os.host() == "windows" then
    table.insert(appFyleria_defines, "NOMINMAX")
    table.insert(appFyleria_defines, "_SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING")
    table.insert(appFyleria_defines, "_SILENCE_CXX17_OLD_ALLOCATOR_MEMBERS_DEPRECATION_WARNING")
end

-- Options
appFyleria_buildoptions = {
}
appFyleria_linkoptions = {
}
if os.host() == "windows" then
    table.insert(appFyleria_buildoptions, "/bigobj")
elseif os.host() == "linux" then
    table.insert(appFyleria_buildoptions, "-Wall")
    table.insert(appFyleria_buildoptions, "-Wfatal-errors")
    table.insert(appFyleria_buildoptions, "`pkg-config --cflags gtk+-3.0 webkit2gtk-4.0`")
    table.insert(appFyleria_linkoptions, "`pkg-config --libs gtk+-3.0 webkit2gtk-4.0`")
end

-- Libs
appFyleria_libs = {
    "Assert",
    "Boost",
    "FantasyName",
    "MicroPather",
    "Python3",
    "SpdLog",
    "TinyXML2",
    "TMXParser",
    "URIParser",
    "Zlib"
}
if os.host() == "windows" then
    table.insert(appFyleria_libs, "windowsapp")
end

-- Sources
appFyleria_sources = {
    appFyleria_srcdir .. "**.h",
    appFyleria_srcdir .. "**.cpp"
}
