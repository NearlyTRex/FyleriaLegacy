-- Get system architecture
function GetSystemArchitecture()
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
        ['linux'] = 'linux',
        ['mac'] = 'macos',
        ['darwin'] = 'macos',
        ['windows'] = 'windows',
        ['^mingw'] = 'windows',
        ['^cygwin'] = 'windows',
    }

    local arch_patterns = {
        ['^x86$'] = 'x86_32',
        ['i[%d]86'] = 'x86_32',
        ['amd64'] = 'x86_64',
        ['x86_64'] = 'x86_64',
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

    return os_name .. "_" .. arch_name
end

-- Get C++ dialect
function GetCppDialect()
    return "C++17"
end

-- Get build toolset
function GetBuildToolset()
    if os.host() == "linux" then
        return "gcc"
    elseif os.host() == "windows" then
        return "msc"
    end
end

-- Get build location
function GetBuildLocation()
    return "Build_" .. os.host()
end

-- Get target debug suffix
function GetTargetDebugSuffix()
    return "_debug"
end

-- Get target release suffix
function GetTargetReleaseSuffix()
    return "_release"
end

-- Get application target directory
function GetAppTargetDirectory()
    return GetBuildLocation() .. "/App"
end

-- Get library target directory
function GetLibraryTargetDirectory()
    return GetBuildLocation() .. "/Lib"
end

-- Get target name
function GetTargetName(target)
    return target .. "_" .. GetSystemArchitecture()
end

-- Get app type
function GetAppType()
    if os.host() == "windows" then
        return "WindowedApp"
    else
        return "ConsoleApp"
    end
end

-- Get library type
function GetLibraryType()
    return "StaticLib"
end
