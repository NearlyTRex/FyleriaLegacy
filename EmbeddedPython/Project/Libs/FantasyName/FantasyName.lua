-- Configuration
libFantasyName_extradir = "Libs/FantasyName/extra/"
libFantasyName_origdir = "Libs/FantasyName/orig/"
libFantasyName_srcdir = libFantasyName_origdir .. "c++/"
libFantasyName_incdir = libFantasyName_origdir .. "c++/"

-- Includes
libFantasyName_includedirs = {
    libFantasyName_incdir
}

-- Defines
libFantasyName_defines = {
    "HAVE_CXX14"
}
libFantasyName_debugdefines = {
}
libFantasyName_releasedefines = {
}

-- Sources
libFantasyName_sources = {
    libFantasyName_srcdir .. "namegen.cc",
}
