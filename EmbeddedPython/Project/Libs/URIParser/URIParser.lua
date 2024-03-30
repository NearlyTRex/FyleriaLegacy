-- Configuration
libURIParser_extradir = "Libs/URIParser/extra/"
libURIParser_origdir = "Libs/URIParser/orig/"
libURIParser_srcdir = libURIParser_origdir .. "src/"
libURIParser_incdir = libURIParser_origdir .. "include/"

-- Includes
libURIParser_includedirs = {
    libURIParser_incdir,
    libURIParser_extradir
}

-- Defines
libURIParser_defines = {
    "URI_STATIC_BUILD"
}
libURIParser_debugdefines = {
}
libURIParser_releasedefines = {
}

-- Libs
libURIParser_libs = {
}

-- Sources
libURIParser_sources = {
    libURIParser_srcdir .. "UriCommon.c",
    libURIParser_srcdir .. "UriCompare.c",
    libURIParser_srcdir .. "UriEscape.c",
    libURIParser_srcdir .. "UriFile.c",
    libURIParser_srcdir .. "UriIp4.c",
    libURIParser_srcdir .. "UriIp4Base.c",
    libURIParser_srcdir .. "UriMemory.c",
    libURIParser_srcdir .. "UriNormalize.c",
    libURIParser_srcdir .. "UriNormalizeBase.c",
    libURIParser_srcdir .. "UriParse.c",
    libURIParser_srcdir .. "UriParseBase.c",
    libURIParser_srcdir .. "UriQuery.c",
    libURIParser_srcdir .. "UriRecompose.c",
    libURIParser_srcdir .. "UriResolve.c",
    libURIParser_srcdir .. "UriShorten.c"
}
