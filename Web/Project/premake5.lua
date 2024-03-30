-- Imports
require "Libs/Fyleria/Fyleria"
require "Libs/Asio/Asio"
require "Libs/Assert/Assert"
require "Libs/BackwardCPP/BackwardCPP"
require "Libs/BetterEnums/BetterEnums"
require "Libs/Boost/Boost"
require "Libs/CFGPath/CFGPath"
require "Libs/CppFS/CppFS"
require "Libs/FantasyName/FantasyName"
require "Libs/ImmutableString/ImmutableString"
require "Libs/MicroPather/MicroPather"
require "Libs/ModernCPPJson/ModernCPPJson"
require "Libs/Pistache/Pistache"
require "Libs/Popl/Popl"
require "Libs/PyBind/PyBind"
require "Libs/Python3/Python3"
require "Libs/TinyXML2/TinyXML2"
require "Libs/TMXParser/TMXParser"
require "Libs/Websocketpp/Websocketpp"
require "Libs/Zlib/Zlib"

-- MinGW 32
newoption {
   trigger     = "with-mingw32",
   value       = "1",
   description = "Force the use of MinGW 32bit options"
}

-- MinGW 64
newoption {
   trigger     = "with-mingw64",
   value       = "1",
   description = "Force the use of MinGW 64bit options"
}

-- Operating system architecture
local function get_architecture()
	local raw_os_name, raw_arch_name = '', ''

	-- LuaJIT shortcut
	if jit and jit.os and jit.arch then
		raw_os_name = jit.os
		raw_arch_name = jit.arch
	else
		-- Is popen supported?
		local popen_status, popen_result = pcall(io.popen, "")
		if popen_status then
			popen_result:close()
			-- Unix-based OS
			raw_os_name = io.popen('uname -s','r'):read('*l')
			raw_arch_name = io.popen('uname -m','r'):read('*l')
		else
			-- Windows
			local env_OS = os.getenv('OS')
			local env_ARCH = os.getenv('PROCESSOR_ARCHITECTURE')
			if env_OS and env_ARCH then
				raw_os_name, raw_arch_name = env_OS, env_ARCH
			end
		end
	end

	raw_os_name = (raw_os_name):lower()
	raw_arch_name = (raw_arch_name):lower()

	local os_patterns = {
		['windows'] = 'windows',
		['linux'] = 'linux',
		['mac'] = 'mac',
		['darwin'] = 'macosx',
		['^mingw'] = 'mingw',
		['^cygwin'] = 'cygwin',
		['bsd$'] = 'bsd',
		['SunOS'] = 'solaris',
	}

	local arch_patterns = {
		['^x86$'] = 'x86',
		['i[%d]86'] = 'x86',
		['amd64'] = 'x86_64',
		['x86_64'] = 'x86_64',
		['Power Macintosh'] = 'powerpc',
		['^arm'] = 'arm',
		['^mips'] = 'mips',
	}

	local os_name, arch_name = 'unknown', 'unknown'

	for pattern, name in pairs(os_patterns) do
		if raw_os_name:match(pattern) then
			os_name = name
			break
		end
	end
	for pattern, name in pairs(arch_patterns) do
		if raw_arch_name:match(pattern) then
			arch_name = name
			break
		end
	end

    if _OPTIONS["with-mingw32"] or _OPTIONS["with-mingw64"] then
        os_name = "mingw"
    end

	return os_name .. "_" .. arch_name
end

--- GCC Prefix
if _OPTIONS["with-mingw32"] then
    gccprefix("i686-w64-mingw32-")
elseif _OPTIONS["with-mingw64"] then
    gccprefix("x86_64-w64-mingw32-")
end

-- Create solution
workspace "all"
    startproject "FyleriaApp"
if _OPTIONS["with-mingw32"] then
    location("Build_mingw32")
elseif _OPTIONS["with-mingw64"] then
    location("Build_mingw64")
else
    location("Build_" .. os.host())
end
    configurations { "Debug32", "Release32", "Debug64", "Release64" }
if _OPTIONS["with-mingw32"] or _OPTIONS["with-mingw64"] then
    buildoptions {
        "-Wa,-mbig-obj"
    }
    linkoptions {
        "-static-libgcc",
        "-static-libstdc++"
    }
end
filter "configurations:*32"
    architecture "x86"
filter "configurations:*64"
    architecture "x86_64"
filter "configurations:Debug*"
    symbols "On"
    targetsuffix("_debug")
filter "configurations:Release*"
    optimize "Full"
    targetsuffix("_release")

-- FyleriaApp
project "FyleriaApp"
kind "ConsoleApp"
language "C++"
pic "On"
    buildoptions(appFyleria_buildoptions)
    includedirs(appFyleria_includedirs)
    includedirs(libBoost_includedirs)
    includedirs(libPopl_includedirs)
    includedirs(libModernCPPJson_includedirs)
    defines(appFyleria_defines)
    files(appFyleria_sources)
    links(appFyleria_libs)
    targetdir("../Bin")
    targetname("fyleria_main_" .. get_architecture())
if _OPTIONS["with-mingw32"] or _OPTIONS["with-mingw64"] then
    targetextension(".exe")
end
filter "configurations:Debug*"
    defines(appFyleria_debugdefines)
filter "configurations:Release*"
    defines(appFyleria_releasedefines)

-- FyleriaLib
project "FyleriaLib"
kind "SharedLib"
language "C++"
pic "On"
    buildoptions(libFyleria_buildoptions)
    includedirs(libFyleria_includedirs)
    includedirs(libAsio_includedirs)
    includedirs(libAssert_includedirs)
    includedirs(libBackwardCPP_includedirs)
    includedirs(libBoost_includedirs)
    includedirs(libCFGPath_includedirs)
    includedirs(libCppFS_includedirs)
    includedirs(libFantasyName_includedirs)
    includedirs(libImmutableString_includedirs)
    includedirs(libBetterEnums_includedirs)
    includedirs(libPistache_includedirs)
    includedirs(libPopl_includedirs)
    includedirs(libModernCPPJson_includedirs)
    includedirs(libPyBind_includedirs)
    includedirs(libPython3_includedirs)
    includedirs(libWebsocketpp_includedirs)
    includedirs(libZlib_includedirs)
    defines(libFyleria_defines)
    defines(libBackwardCPP_defines)
    defines(libBetterEnums_defines)
    defines(libPython3_defines)
    defines(libWebsocketpp_defines)
    files(libFyleria_sources)
    links(libFyleria_libs)
    links(libBackwardCPP_libs)
    targetdir("../Bin")
    targetname("fyleria_" .. get_architecture())
if _OPTIONS["with-mingw32"] or _OPTIONS["with-mingw64"] then
    targetextension(".dll")
end
filter "configurations:Debug*"
    defines(libFyleria_debugdefines)
filter "configurations:Release*"
    defines(libFyleria_releasedefines)

-- Pistache
project "Pistache"
kind "SharedLib"
language "C++"
pic "On"
    includedirs(libPistache_includedirs)
    files(libPistache_sources)
    links(libPistache_libs)
    targetdir("../Bin")
    targetname("pistache_" .. get_architecture())
if _OPTIONS["with-mingw32"] or _OPTIONS["with-mingw64"] then
    targetextension(".dll")
end

-- Assert
project "Assert"
kind "SharedLib"
language "C++"
pic "On"
    includedirs(libAssert_includedirs)
    files(libAssert_sources)
    targetdir("../Bin")
    targetname("assert_" .. get_architecture())
if _OPTIONS["with-mingw32"] or _OPTIONS["with-mingw64"] then
    targetextension(".dll")
end
filter "configurations:Debug*"
    defines(libAssert_debugdefines)
filter "configurations:Release*"
    defines(libAssert_releasedefines)

-- BackwardCPP
project "BackwardCPP"
kind "SharedLib"
language "C++"
pic "On"
    includedirs(libBackwardCPP_includedirs)
    files(libBackwardCPP_sources)
    targetdir("../Bin")
    targetname("backwardcpp_" .. get_architecture())
if _OPTIONS["with-mingw32"] or _OPTIONS["with-mingw64"] then
    targetextension(".dll")
end

-- Boost
project "Boost"
kind "SharedLib"
language "C++"
pic "On"
    includedirs(libBoost_includedirs)
    files(libBoost_sources)
    targetdir("../Bin")
    targetname("boost_" .. get_architecture())
if _OPTIONS["with-mingw32"] or _OPTIONS["with-mingw64"] then
    targetextension(".dll")
end

-- CppFS
project "CppFS"
kind "SharedLib"
language "C++"
pic "On"
    includedirs(libCppFS_includedirs)
    files(libCppFS_sources)
    targetdir("../Bin")
    targetname("cppfs_" .. get_architecture())
if _OPTIONS["with-mingw32"] or _OPTIONS["with-mingw64"] then
    targetextension(".dll")
end

-- FantasyName
project "FantasyName"
kind "SharedLib"
language "C++"
pic "On"
    includedirs(libFantasyName_includedirs)
    defines(libFantasyName_defines)
    files(libFantasyName_sources)
    targetdir("../Bin")
    targetname("fantasyname_" .. get_architecture())
if _OPTIONS["with-mingw32"] or _OPTIONS["with-mingw64"] then
    targetextension(".dll")
end
filter "configurations:Debug*"
    defines(libFantasyName_debugdefines)
filter "configurations:Release*"
    defines(libFantasyName_releasedefines)

-- MicroPather
project "MicroPather"
kind "SharedLib"
language "C++"
pic "On"
    includedirs(libMicroPather_includedirs)
    files(libMicroPather_sources)
    targetdir("../Bin")
    targetname("micropather_" .. get_architecture())
if _OPTIONS["with-mingw32"] or _OPTIONS["with-mingw64"] then
    targetextension(".dll")
end

-- Python3
project "Python3"
kind "SharedLib"
language "C"
pic "On"
    includedirs(libPython3_includedirs)
    includedirs(libZlib_includedirs)
    defines(libPython3_defines)
    files(libPython3_sources)
    links(libPython3_libs)
    targetdir("../Bin")
    targetname("python3_" .. get_architecture())
if _OPTIONS["with-mingw32"] or _OPTIONS["with-mingw64"] then
    targetextension(".dll")
end
filter "configurations:Debug*"
    defines(libPython3_debugdefines)
filter "configurations:Release*"
    defines(libPython3_releasedefines)

-- TinyXML2
project "TinyXML2"
kind "SharedLib"
language "C++"
pic "On"
    includedirs(libTinyXML2_includedirs)
    files(libTinyXML2_sources)
    targetdir("../Bin")
    targetname("tinyxml2_" .. get_architecture())
if _OPTIONS["with-mingw32"] or _OPTIONS["with-mingw64"] then
    targetextension(".dll")
end

-- Zlib
project "Zlib"
kind "SharedLib"
language "C"
pic "On"
    includedirs(libZlib_includedirs)
    defines(libZlib_defines)
    files(libZlib_sources)
    targetdir("../Bin")
    targetname("zlib_" .. get_architecture())
if _OPTIONS["with-mingw32"] or _OPTIONS["with-mingw64"] then
    targetextension(".dll")
end
filter "configurations:Debug*"
    defines(libZlib_debugdefines)
filter "configurations:Release*"
    defines(libZlib_releasedefines)
