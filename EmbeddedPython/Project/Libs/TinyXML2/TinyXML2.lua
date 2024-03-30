-- Configuration
libTinyXML2_extradir = "Libs/TinyXML2/extra/"
libTinyXML2_origdir = "Libs/TinyXML2/orig/"
libTinyXML2_srcdir = libTinyXML2_origdir
libTinyXML2_incdir = libTinyXML2_origdir

-- Includes
libTinyXML2_includedirs = {
    libTinyXML2_incdir
}

-- Defines
libTinyXML2_defines = {
}
libTinyXML2_debugdefines = {
}
libTinyXML2_releasedefines = {
}

-- Sources
libTinyXML2_sources = {
    libTinyXML2_srcdir .. "tinyxml2.cpp"
}
