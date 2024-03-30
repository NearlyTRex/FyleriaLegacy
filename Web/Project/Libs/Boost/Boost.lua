-- Configuration
libBoost_extradir = "Libs/Boost/extra/"
libBoost_origdir = "Libs/Boost/orig/"
libBoost_srcdir = libBoost_origdir .. "libs/"
libBoost_incdir = libBoost_origdir

-- Includes
libBoost_includedirs = {
    libBoost_incdir
}

-- Libs
libBoost_libs = {
}

-- Sources
libBoost_sources = {
    libBoost_srcdir .. "thread/src/future.cpp",
    libBoost_srcdir .. "thread/src/tss_null.cpp",
    libBoost_srcdir .. "system/src/error_code.cpp"
}
if os.host() == "windows" or _OPTIONS["with-mingw32"] or _OPTIONS["with-mingw64"] then
    --table.insert(libBoost_sources, libBoost_srcdir .. "thread/src/win32/thread.cpp")
    table.insert(libBoost_sources, libBoost_srcdir .. "thread/src/win32/thread_primitives.cpp")
    --table.insert(libBoost_sources, libBoost_srcdir .. "thread/src/win32/tss_dll.cpp")
    --table.insert(libBoost_sources, libBoost_srcdir .. "thread/src/win32/tss_pe.cpp")
else
    table.insert(libBoost_sources, libBoost_srcdir .. "thread/src/pthread/once.cpp")
    --table.insert(libBoost_sources, libBoost_srcdir .. "thread/src/pthread/once_atomic.cpp")
    table.insert(libBoost_sources, libBoost_srcdir .. "thread/src/pthread/thread.cpp")
end
