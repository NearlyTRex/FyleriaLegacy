-- Imports
require "Fyleria/Fyleria"
require "Libs/Assert/Assert"
require "Libs/BackwardCPP/BackwardCPP"
require "Libs/BetterEnums/BetterEnums"
require "Libs/Boost/Boost"
require "Libs/FantasyName/FantasyName"
require "Libs/ImmutableString/ImmutableString"
require "Libs/MicroPather/MicroPather"
require "Libs/ModernCPPJson/ModernCPPJson"
require "Libs/ObjectThreadsafe/ObjectThreadsafe"
require "Libs/PyBind/PyBind"
require "Libs/Python3/Python3"
require "Libs/SpdLog/SpdLog"
require "Libs/TinyXML2/TinyXML2"
require "Libs/TMXParser/TMXParser"
require "Libs/URIParser/URIParser"
require "Libs/Zlib/Zlib"
require "utility"

-- Create solution
workspace "all"
    startproject "Fyleria"
    cppdialect(GetCppDialect())
    location(GetBuildLocation())
    toolset(GetBuildToolset())
    configurations { "Debug32", "Release32", "Debug64", "Release64" }
filter "configurations:*32"
    architecture "x86"
filter "configurations:*64"
    architecture "x86_64"
filter "configurations:Debug*"
    symbols "On"
    targetsuffix(GetTargetDebugSuffix())
filter "configurations:Release*"
    optimize "Full"
    targetsuffix(GetTargetReleaseSuffix())

-- Fyleria
project "Fyleria"
language "C++"
pic "On"
    kind(GetAppType())
    buildoptions(appFyleria_buildoptions)
    linkoptions(appFyleria_linkoptions)
    includedirs(appFyleria_includedirs)
    includedirs(libAssert_includedirs)
    includedirs(libBackwardCPP_includedirs)
    includedirs(libBoost_includedirs)
    includedirs(libFantasyName_includedirs)
    includedirs(libImmutableString_includedirs)
    includedirs(libBetterEnums_includedirs)
    includedirs(libModernCPPJson_includedirs)
    includedirs(libObjectThreadsafe_includedirs)
    includedirs(libPyBind_includedirs)
    includedirs(libPython3_includedirs)
    includedirs(libSpdLog_includedirs)
    includedirs(libURIParser_includedirs)
    includedirs(libZlib_includedirs)
    defines(appFyleria_defines)
    defines(libBackwardCPP_defines)
    defines(libBetterEnums_defines)
    defines(libBoost_defines)
    defines(libPython3_defines)
    defines(libURIParser_defines)
    files(appFyleria_sources)
    links(appFyleria_libs)
    links(libBackwardCPP_libs)
    links(libPython3_libs)
    targetdir(GetAppTargetDirectory())
    targetname(GetTargetName("FyleriaMain"))
filter "configurations:Debug*"
    defines(appFyleria_debugdefines)
filter "configurations:Release*"
    defines(appFyleria_releasedefines)

-- Assert
project "Assert"
language "C++"
pic "On"
    kind(GetLibraryType())
    includedirs(libAssert_includedirs)
    defines(libAssert_defines)
    files(libAssert_sources)
    targetdir(GetLibraryTargetDirectory())
    targetname(GetTargetName("Assert"))
filter "configurations:Debug*"
    defines(libAssert_debugdefines)
filter "configurations:Release*"
    defines(libAssert_releasedefines)

-- Boost
project "Boost"
language "C++"
pic "On"
    kind(GetLibraryType())
    includedirs(libBoost_includedirs)
    defines(libBoost_defines)
    files(libBoost_sources)
    targetdir(GetLibraryTargetDirectory())
    targetname(GetTargetName("Boost"))
filter "configurations:Debug*"
    defines(libBoost_debugdefines)
filter "configurations:Release*"
    defines(libBoost_releasedefines)

-- FantasyName
project "FantasyName"
language "C++"
pic "On"
    kind(GetLibraryType())
    includedirs(libFantasyName_includedirs)
    defines(libFantasyName_defines)
    files(libFantasyName_sources)
    targetdir(GetLibraryTargetDirectory())
    targetname(GetTargetName("FantasyName"))
filter "configurations:Debug*"
    defines(libFantasyName_debugdefines)
filter "configurations:Release*"
    defines(libFantasyName_releasedefines)

-- MicroPather
project "MicroPather"
language "C++"
pic "On"
    kind(GetLibraryType())
    includedirs(libMicroPather_includedirs)
    defines(libMicroPather_defines)
    files(libMicroPather_sources)
    targetdir(GetLibraryTargetDirectory())
    targetname(GetTargetName("MicroPather"))
filter "configurations:Debug*"
    defines(libMicroPather_debugdefines)
filter "configurations:Release*"
    defines(libMicroPather_releasedefines)

-- Python3
project "Python3"
language "C"
pic "On"
    kind(GetLibraryType())
    includedirs(libPython3_includedirs)
    includedirs(libZlib_includedirs)
    defines(libPython3_defines)
    files(libPython3_sources)
    links(libPython3_libs)
    targetdir(GetLibraryTargetDirectory())
    targetname(GetTargetName("Python3"))
filter "configurations:Debug*"
    defines(libPython3_debugdefines)
filter "configurations:Release*"
    defines(libPython3_releasedefines)

-- SpdLog
project "SpdLog"
language "C++"
pic "On"
    kind(GetLibraryType())
    includedirs(libSpdLog_includedirs)
    defines(libSpdLog_defines)
    files(libSpdLog_sources)
    targetdir(GetLibraryTargetDirectory())
    targetname(GetTargetName("SpdLog"))
filter "configurations:Debug*"
    defines(libSpdLog_debugdefines)
filter "configurations:Release*"
    defines(libSpdLog_releasedefines)

-- TinyXML2
project "TinyXML2"
language "C++"
pic "On"
    kind(GetLibraryType())
    includedirs(libTinyXML2_includedirs)
    defines(libTinyXML2_defines)
    files(libTinyXML2_sources)
    targetdir(GetLibraryTargetDirectory())
    targetname(GetTargetName("TinyXML2"))
filter "configurations:Debug*"
    defines(libTinyXML2_debugdefines)
filter "configurations:Release*"
    defines(libTinyXML2_releasedefines)

-- TMXParser
project "TMXParser"
language "C++"
pic "On"
    kind(GetLibraryType())
    includedirs(libTMXParser_includedirs)
    includedirs(libTinyXML2_includedirs)
    includedirs(libZlib_includedirs)
    defines(libTMXParser_defines)
    files(libTMXParser_sources)
    links(libTMXParser_libs)
    targetdir(GetLibraryTargetDirectory())
    targetname(GetTargetName("TMXParser"))
filter "configurations:Debug*"
    defines(libTMXParser_debugdefines)
filter "configurations:Release*"
    defines(libTMXParser_releasedefines)

-- URIParser
project "URIParser"
language "C"
pic "On"
    kind(GetLibraryType())
    includedirs(libURIParser_includedirs)
    defines(libURIParser_defines)
    files(libURIParser_sources)
    links(libURIParser_libs)
    targetdir(GetLibraryTargetDirectory())
    targetname(GetTargetName("URIParser"))
filter "configurations:Debug*"
    defines(libURIParser_debugdefines)
filter "configurations:Release*"
    defines(libURIParser_releasedefines)

-- Zlib
project "Zlib"
language "C"
pic "On"
    kind(GetLibraryType())
    includedirs(libZlib_includedirs)
    defines(libZlib_defines)
    files(libZlib_sources)
    targetdir(GetLibraryTargetDirectory())
    targetname(GetTargetName("Zlib"))
filter "configurations:Debug*"
    defines(libZlib_debugdefines)
filter "configurations:Release*"
    defines(libZlib_releasedefines)
