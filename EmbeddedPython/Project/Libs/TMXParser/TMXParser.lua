-- Configuration
libTMXParser_extradir = "Libs/TMXParser/extra/"
libTMXParser_origdir = "Libs/TMXParser/orig/"
libTMXParser_srcdir = libTMXParser_origdir .. "src/"
libTMXParser_incdir = libTMXParser_origdir .. "include/"

-- Includes
libTMXParser_includedirs = {
    libTMXParser_incdir
}

-- Defines
libTMXParser_defines = {
}
libTMXParser_debugdefines = {
}
libTMXParser_releasedefines = {
}

-- Libs
libTMXParser_libs = {
    "TinyXML2"
}

-- Sources
libTMXParser_sources = {
    libTMXParser_srcdir .. "base64/base64.cpp",
    libTMXParser_srcdir .. "miniz.c",
    libTMXParser_srcdir .. "TmxColor.cpp",
    libTMXParser_srcdir .. "TmxEllipse.cpp",
    libTMXParser_srcdir .. "TmxGroupLayer.cpp",
    libTMXParser_srcdir .. "TmxImage.cpp",
    libTMXParser_srcdir .. "TmxImageLayer.cpp",
    libTMXParser_srcdir .. "TmxLayer.cpp",
    libTMXParser_srcdir .. "TmxMap.cpp",
    libTMXParser_srcdir .. "TmxObject.cpp",
    libTMXParser_srcdir .. "TmxObjectGroup.cpp",
    libTMXParser_srcdir .. "TmxPolygon.cpp",
    libTMXParser_srcdir .. "TmxPolyline.cpp",
    libTMXParser_srcdir .. "TmxProperty.cpp",
    libTMXParser_srcdir .. "TmxPropertySet.cpp",
    libTMXParser_srcdir .. "TmxTerrain.cpp",
    libTMXParser_srcdir .. "TmxTerrainArray.cpp",
    libTMXParser_srcdir .. "TmxText.cpp",
    libTMXParser_srcdir .. "TmxTile.cpp",
    libTMXParser_srcdir .. "TmxTileLayer.cpp",
    libTMXParser_srcdir .. "TmxTileOffset.cpp",
    libTMXParser_srcdir .. "TmxTileset.cpp",
    libTMXParser_srcdir .. "TmxUtil.cpp"
}
