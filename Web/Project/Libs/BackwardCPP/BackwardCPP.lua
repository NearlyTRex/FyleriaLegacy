-- Configuration
libBackwardCPP_extradir = "Libs/BackwardCPP/extra/"
libBackwardCPP_origdir = "Libs/BackwardCPP/orig/"
libBackwardCPP_srcdir = libBackwardCPP_origdir
libBackwardCPP_incdir = libBackwardCPP_origdir

-- Includes
libBackwardCPP_includedirs = {
    libBackwardCPP_incdir
}

-- Sources
libBackwardCPP_sources = {
    libBackwardCPP_srcdir .. "backward.cpp",
}

-- Defines
libBackwardCPP_defines = {
    "BACKWARD_HAS_BFD=1",
    "BACKWARD_HAS_DW=1",
    "BACKWARD_HAS_DWARF=1"
}

-- Libs
libBackwardCPP_libs = {
}
if os.host() == "windows" or _OPTIONS["with-mingw32"] or _OPTIONS["with-mingw64"] then
elseif os.host() == "linux" then
    table.insert(libBackwardCPP_libs, "bfd")
    table.insert(libBackwardCPP_libs, "dl")
    table.insert(libBackwardCPP_libs, "dw")
    table.insert(libBackwardCPP_libs, "dwarf")
end
