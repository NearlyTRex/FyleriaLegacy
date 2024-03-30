# Setup script
# Download, extract, and configure libraries
# Configure project for various platforms
#
# Windows useful tools:
# - Cygwin (https://www.cygwin.com/)
# - TDM-GCC (http://tdm-gcc.tdragon.net/)
# - Visual Studio Express (http://www.visualstudio.com/en-us/products/visual-studio-express-vs.aspx)
# - Windows subsystem for linux (https://docs.microsoft.com/en-us/windows/wsl/install-win10)

# Base imports
import sys
import os
import os.path
import stat
import subprocess
import shutil
import importlib

###########################################################################
# Paths
sys.path.append("Project/Libs/EasyProcess/orig")
sys.path.append("Project/Libs/Patool/orig")
sys.path.append("Project/Libs/Pyunpack/orig")
###########################################################################
# Globals
required_python_version = (3,5)
###########################################################################
# Program options
class ProgramOptions:
    def __init__(self):
        pass
###########################################################################
# System information
class SystemInformation:
    def __init__(self):
        pass
###########################################################################
# Get program options
def GetProgramOptions():
    import argparse
    parser = argparse.ArgumentParser(description='Setup build environment.')
    parser.add_argument('--force32', action='store_true', help='Force 32-bit steps')
    parser.add_argument('--force64', action='store_true', help='Force 64-bit steps')
    parser.add_argument('--forcelinux', action='store_true', help='Force Linux steps')
    parser.add_argument('--forcemacosx', action='store_true', help='Force MacOSX steps')
    parser.add_argument('--forcebsd', action='store_true', help='Force BSD steps')
    parser.add_argument('--forcewindows', action='store_true', help='Force Windows steps')
    parser.add_argument('--forcewsl', action='store_true', help='Force Windows Subsystem for Linux steps')
    parser.add_argument('--forcecygwin', action='store_true', help='Force Cygwin steps')
    parser.add_argument('--forcemingw', action='store_true', help='Force MinGW steps')
    parser.add_argument('--forcedownload', action='store_true', help='Force downloads')
    parser.add_argument('--configuration', choices=[
        'release',
        'debug'
    ], default='debug', help="Configuration type")
    parser.add_argument('--buildtype', choices=[
        'gmake',
        'gmake2',
        'vs2005',
        'vs2008',
        'vs2010',
        'vs2012',
        'vs2013',
        'vs2015',
        'vs2017'
    ], default='gmake', help='Project type to pass to Premake')
    parser.add_argument('-v', '--verbose', action='store_true', help='Enable verbose messages')
    parser.add_argument('mode', choices=[
        'all',
        'libraries',
        'programs',
        'build',
        'pythonlib',
    ], help='Setup mode')
    args = parser.parse_args()
    options = ProgramOptions()
    options.force_32bits = args.force32
    options.force_64bits = args.force64
    options.force_linux = args.forcelinux
    options.force_macosx = args.forcemacosx
    options.force_bsd = args.forcebsd
    options.force_windows = args.forcewindows
    options.force_wsl = args.forcewsl
    options.force_cygwin = args.forcecygwin
    options.force_mingw = args.forcemingw
    options.force_download = args.forcedownload
    options.configuration = args.configuration
    options.build_type = args.buildtype
    options.verbose = args.verbose
    options.mode = args.mode
    return options
###########################################################################
# Get system information
def GetSystemInformation(program_options):
    import platform
    current_path = os.path.dirname(os.path.abspath( __file__ ))
    current_system = platform.system().lower()
    detect_cygwin = False
    detect_mingw = False
    detect_wsl = False
    detect_macosx = False
    detect_linux = False
    detect_windows = False
    detect_bsd = False
    detect_bin_suffix = ""
    detect_which_bin = "which"
    detect_premake_bin = "Project/premake5"
    detect_make_bin = "make"
    detect_pip3_bin = "pip3"
    detect_zip_bin = "zip"
    detect_python3_libdir = "Project/Libs/Python3/orig/Lib"
    if 'cygwin' in current_system:
        detect_cygwin = True
    elif 'darwin' in current_system:
        detect_macosx = True
    elif 'linux' in current_system:
        detect_linux = True
        with open('/proc/version','r') as f:
            if 'microsoft' in f.read().lower():
                detect_wsl = True
                detect_linux = False
    elif 'windows' in current_system:
        detect_windows = True
        detect_bin_suffix = ".exe"
        detect_make_bin = "nmake"
    elif 'bsd' in current_system:
        detect_bsd = True
    info = SystemInformation()
    info.bin_suffix = detect_bin_suffix
    info.which_bin = detect_which_bin
    info.premake_bin = os.path.join(current_path, detect_premake_bin + detect_bin_suffix)
    info.make_bin = detect_make_bin
    info.pip3_bin = detect_pip3_bin
    info.zip_bin = detect_zip_bin
    info.python3_libdir = detect_python3_libdir
    detect_64bits = sys.maxsize > 2**32
    info.is_32bits = not detect_64bits
    info.is_64bits = detect_64bits
    info.has_forced_platform = (
        program_options.force_linux or
        program_options.force_macosx or
        program_options.force_windows or
        program_options.force_bsd or
        program_options.force_wsl or
        program_options.force_cygwin or
        program_options.force_mingw)
    if info.has_forced_platform:
        info.is_linux = program_options.force_linux
        info.is_macosx = program_options.force_macosx
        info.is_windows = program_options.force_windows
        info.is_bsd = program_options.force_bsd
        info.is_wsl = program_options.force_wsl
        info.is_cygwin = program_options.force_cygwin
        info.is_mingw = program_options.force_mingw
        info.is_posix = (info.is_linux or info.is_macosx or info.is_bsd or info.is_wsl or info.is_cygwin or info.is_mingw)
    else:
        info.is_linux = detect_linux
        info.is_macosx = detect_macosx
        info.is_windows = detect_windows
        info.is_bsd = detect_bsd
        info.is_wsl = detect_wsl
        info.is_cygwin = detect_cygwin
        info.is_mingw = detect_mingw
        info.is_posix = (info.is_linux or info.is_macosx or info.is_bsd or info.is_wsl or info.is_cygwin or info.is_mingw)
    if program_options.force_32bits:
        info.is_32bits = True
        info.is_64bits = False
    elif program_options.force_64bits:
        info.is_32bits = False
        info.is_64bits = True
    if info.is_linux or info.is_wsl:
        info.build_path = "Project/Build_linux"
    elif info.is_macosx:
        info.build_path = "Project/Build_macosx"
    elif info.is_windows:
        info.build_path = "Project/Build_windows"
    elif info.is_bsd:
        info.build_path = "Project/Build_bsd"
    elif info.is_cygwin:
        info.build_path = "Project/Build_cygwin"
    elif info.is_mingw and info.is_32bits:
        info.build_path = "Project/Build_mingw32"
    elif info.is_mingw and info.is_64bits:
        info.build_path = "Project/Build_mingw64"
    else:
        info.build_path = "Project/Build"
    return info
###########################################################################
# Detect Python version
def DetectPython(required_version):
    if (sys.version_info <= required_version):
        return False
    else:
        return True
###########################################################################
# Print log statement
def LogStatement(message, include_elipses = True):
    output = " -- "
    output += message
    if include_elipses:
        output += " ... "
    print(output)
###########################################################################
# Print error statement
def ErrorStatement(message, include_elipses = True):
    output = "ERROR: "
    output += message
    if include_elipses:
        output += " ... "
    print(output)
###########################################################################
## Check if a given package is found
def FoundPythonPackage(package):
    spec = importlib.util.find_spec(package)
    is_present = spec is not None
    return is_present
###########################################################################
## Check if a program is found
def FoundProgram(program, system_info, verbose_output = False):
    if system_info.is_windows:
        return False

    if system_info.is_posix:
        success, output = RunSubprocess(subprocess_args = [system_info.which_bin, program], verbose_output = verbose_output)
        if success:
            return (len(output) > 0)
    return False
###########################################################################
## Run subprocess
def RunSubprocess(subprocess_args = [], expected_substr = "", verbose_output = False):
    cleared_subprocess_args = [x for x in subprocess_args if x.strip()]
    if not len(cleared_subprocess_args):
        return (False, "")
    try:
        if verbose_output:
            LogStatement("Running subprocess '%s'" % (" ".join(cleared_subprocess_args)))
        result = subprocess.run(
            args=cleared_subprocess_args,
            stderr=subprocess.STDOUT,
            stdout=subprocess.PIPE,
            universal_newlines=True)
        if verbose_output:
            if len(result.stdout) > 0:
                print(result.stdout)
        if len(expected_substr) > 0:
            return (expected_substr in output, result.stdout)
        return (True, result.stdout)
    except Exception:
        return (False, "")
###########################################################################
## Run subprocess and get live output
def RunLiveSubprocess(subprocess_args = [], verbose_output = False):
    cleared_subprocess_args = [x for x in subprocess_args if x.strip()]
    if not len(cleared_subprocess_args):
        return (False, "")
    try:
        if verbose_output:
            LogStatement("Running subprocess '%s'" % (" ".join(cleared_subprocess_args)))
        process = subprocess.Popen(
            args=cleared_subprocess_args,
            stderr=subprocess.STDOUT,
            stdout=subprocess.PIPE,
            universal_newlines=True)
        while verbose_output and True:
            output = process.stdout.readline()
            if output == '' and process.poll() is not None:
                break
            if output:
                print(output.strip())
        code = process.poll()
        return code
    except Exception:
        return -1
###########################################################################
# Run extra steps
def RunExtraSteps(steps, platform, flags):

    # Run process and show output in realtime
    def RunProcess(process):
        subprocess.call(process, shell=True)

    # Copy file
    def CopyFile(src, dest):
        if os.path.isfile(src) and not os.path.exists(dest):
            shutil.copyfile(src, dest)

    # Replace text in the given file
    def ReplaceText(filename, old, new):
        if os.path.isfile(filename):
            f = open(filename,'r')
            filedata = f.read()
            f.close()
            newdata = filedata.replace(old, new)
            f = open(filename,'w')
            f.write(newdata)
            f.close()

    # Make the file executable
    def MakeExecutable(file):
        if os.path.isfile(file):
            st = os.stat(file)
            os.chmod(file, st.st_mode | stat.S_IEXEC)

    # Evaluate the steps for the given platform
    if platform in steps and flags:
        for step in steps[platform]:
            LogStatement("Running extra step " + step)
            eval(step)
###########################################################################
# Setup project
def SetupProject(project_name, project_base_dir, system_info, program_options):

    # Inform user
    LogStatement("Setting up project: " + project_name)

    # Import library module
    scriptdir = os.path.dirname(os.path.abspath(__file__))
    projectdir = os.path.join(project_base_dir, project_name)
    sys.path.append(projectdir)
    module = importlib.import_module(project_name)

    # Generate archive info
    archive_base = module.Setup['url'].split('/')[-1].split('.')[0]
    archive_ext = module.Setup['url'].split('.')[-1]
    archive_file = os.path.join(projectdir, archive_base + '.' + archive_ext)
    archive_olddir = os.path.join(projectdir, module.Setup['extractdir'])
    archive_newdir = os.path.join(projectdir, "orig")

    # Remove archive if we are forcing a new download
    if program_options.force_download:
        LogStatement("Removing old archive file %s" % archive_file)
        os.remove(archive_file)

    # Remove old folders if we are forcing a new download
    if program_options.force_download:
        LogStatement("Removing old folders %s and %s" % (archive_olddir, archive_newdir))
        shutil.rmtree(archive_olddir, ignore_errors=True)
        shutil.rmtree(archive_newdir, ignore_errors=True)

    # Download archive
    if program_options.force_download or not os.path.exists(archive_file):
        from urllib.request import urlopen
        LogStatement("Downloading " + module.Setup['url'] + " to file " + archive_file)
        request = urlopen(module.Setup['url'])
        output = open(archive_file, "wb")
        output.write(request.read())
        output.close()
        if not os.path.exists(archive_file):
            ErrorStatement("Could not download archive for %s" % project_name)
            sys.exit(-1)

    # Extract library archive
    if os.path.isfile(archive_file) and os.path.exists(projectdir) and not os.path.exists(archive_newdir):
        import pyunpack
        LogStatement("Extracting " + archive_file + " to " + projectdir)
        pyunpack.Archive(archive_file).extractall(projectdir, True)

    # Move extracted archive
    if os.path.exists(archive_olddir) and not os.path.exists(archive_newdir):
        LogStatement("Moving " + archive_olddir + " to " + archive_newdir)
        shutil.move(archive_olddir, archive_newdir)

    # Run extra setup steps
    if module.Setup['steps'] and os.path.exists(archive_newdir):

        # Go to new archive directory
        if os.path.exists(archive_newdir):
            LogStatement("Changing directory to " + archive_newdir)
            os.chdir(archive_newdir)

        # Run basic extra steps
        RunExtraSteps(module.Setup['steps'], "linux", system_info.is_linux and not system_info.is_mingw)
        RunExtraSteps(module.Setup['steps'], "macosx", system_info.is_macosx and not system_info.is_mingw)
        RunExtraSteps(module.Setup['steps'], "bsd", system_info.is_bsd and not system_info.is_mingw)
        RunExtraSteps(module.Setup['steps'], "wsl", system_info.is_macosx and not system_info.is_mingw)
        RunExtraSteps(module.Setup['steps'], "posix", system_info.is_posix and not system_info.is_mingw)
        RunExtraSteps(module.Setup['steps'], "windows", system_info.is_windows)
        RunExtraSteps(module.Setup['steps'], "cygwin", system_info.is_cygwin)
        RunExtraSteps(module.Setup['steps'], "mingw", system_info.is_mingw)
        RunExtraSteps(module.Setup['steps'], "all", True)

        # Run bitsize extra steps
        RunExtraSteps(module.Setup['steps'], "linux32", system_info.is_linux and system_info.is_32bits and not system_info.is_mingw)
        RunExtraSteps(module.Setup['steps'], "linux64", system_info.is_linux and system_info.is_64bits and not system_info.is_mingw)
        RunExtraSteps(module.Setup['steps'], "macosx32", system_info.is_macosx and system_info.is_32bits and not system_info.is_mingw)
        RunExtraSteps(module.Setup['steps'], "macosx64", system_info.is_macosx and system_info.is_64bits and not system_info.is_mingw)
        RunExtraSteps(module.Setup['steps'], "bsd32", system_info.is_bsd and system_info.is_32bits and not system_info.is_mingw)
        RunExtraSteps(module.Setup['steps'], "bsd64", system_info.is_bsd and system_info.is_64bits and not system_info.is_mingw)
        RunExtraSteps(module.Setup['steps'], "wsl32", system_info.is_wsl and system_info.is_32bits and not system_info.is_mingw)
        RunExtraSteps(module.Setup['steps'], "wsl64", system_info.is_wsl and system_info.is_64bits and not system_info.is_mingw)
        RunExtraSteps(module.Setup['steps'], "posix32", system_info.is_posix and system_info.is_32bits and not system_info.is_mingw)
        RunExtraSteps(module.Setup['steps'], "posix64", system_info.is_posix and system_info.is_64bits and not system_info.is_mingw)
        RunExtraSteps(module.Setup['steps'], "windows32", system_info.is_windows and system_info.is_32bits)
        RunExtraSteps(module.Setup['steps'], "windows64", system_info.is_windows and system_info.is_64bits)
        RunExtraSteps(module.Setup['steps'], "cygwin32", system_info.is_cygwin and system_info.is_32bits)
        RunExtraSteps(module.Setup['steps'], "cygwin64", system_info.is_cygwin and system_info.is_64bits)
        RunExtraSteps(module.Setup['steps'], "mingw32", system_info.is_mingw and system_info.is_32bits)
        RunExtraSteps(module.Setup['steps'], "mingw64", system_info.is_mingw and system_info.is_64bits)
        RunExtraSteps(module.Setup['steps'], "all32", system_info.is_32bits)
        RunExtraSteps(module.Setup['steps'], "all64", system_info.is_64bits)

        # Go back to script directory
        if os.path.exists(scriptdir):
            LogStatement("Changing directory to " + scriptdir)
            os.chdir(scriptdir)
###########################################################################
## Build Project
def BuildProject(system_info, program_options):

    # Inform user
    LogStatement("Building project")

    # Flags
    premake_file_flag = "--file=Project/premake5.lua"
    premake_verbose_flag = "--verbose=1" if program_options.verbose else ""
    premake_mingw32_flag = "--with-mingw32=1" if (system_info.is_mingw and system_info.is_32bits) else ""
    premake_mingw64_flag = "--with-mingw64=1" if (system_info.is_mingw and system_info.is_64bits) else ""
    make_verbose_flag = "verbose=1"
    make_debug32_flag = "config=debug32" if (system_info.is_32bits and program_options.configuration == "debug") else ""
    make_debug64_flag = "config=debug64" if (system_info.is_64bits and program_options.configuration == "debug") else ""
    make_release32_flag = "config=release32" if (system_info.is_32bits and program_options.configuration == "release") else ""
    make_release64_flag = "config=release64" if (system_info.is_64bits and program_options.configuration == "release") else ""

    # Create project files
    RunSubprocess(subprocess_args=[
        system_info.premake_bin,
        program_options.build_type,
        premake_file_flag,
        premake_verbose_flag,
        premake_mingw32_flag,
        premake_mingw64_flag], verbose_output=program_options.verbose)

    # Change to build directory
    if os.path.exists(system_info.build_path):
        LogStatement("Changing directory to " + system_info.build_path)
        os.chdir(system_info.build_path)

    # Build project
    RunLiveSubprocess(subprocess_args=[
        system_info.make_bin,
        make_debug32_flag,
        make_debug64_flag,
        make_release32_flag,
        make_release64_flag,
        make_verbose_flag], verbose_output=program_options.verbose)
###########################################################################
## Build Python Library
def BuildPythonLibrary(system_info, program_options):

    # Inform user
    LogStatement("Building Python library")

    # Store script dir
    scriptdir = os.path.dirname(os.path.abspath(__file__))

    # Zip file
    new_zip_file = "PythonLib.zip"
    new_zip_location = "../../../../../Data/"

    # Check lib directory
    if not os.path.exists(system_info.python3_libdir):
        return False

    # Change to lib directory
    LogStatement("Changing directory to " + system_info.python3_libdir)
    os.chdir(system_info.python3_libdir)

    # Zip python library
    LogStatement("Zipping Python library")
    RunLiveSubprocess(subprocess_args=[
        system_info.zip_bin,
        "-r",
        new_zip_file,
        "."], verbose_output=program_options.verbose)

    # Check zip file
    if not os.path.exists(new_zip_file) and not os.path.isfile(new_zip_file):
        return False

    # Moving python library
    LogStatement("Copying Python library")
    try:
        shutil.copyfile(new_zip_file, os.path.join(new_zip_location, new_zip_file))
    except shutil.Error:
        pass

    # Change to script directory
    LogStatement("Changing directory to " + scriptdir)
    os.chdir(scriptdir)
    return True
###########################################################################
## Main
def main():

    # Get program options and system info
    program_options = GetProgramOptions()
    system_info = GetSystemInformation(program_options)

    # Check Python
    if DetectPython(required_python_version) == False:
        ErrorStatement("Python %d.%d or higher is required to run this script" % required_python_version)
        sys.exit(-1)

    # Parse program options
    do_all = program_options.mode == "all"
    do_libraries = program_options.mode == "libraries"
    do_programs = program_options.mode == "programs"
    do_build = program_options.mode == "build"
    do_pythonlib = program_options.mode == "pythonlib"
    if do_libraries or do_all:
        SetupProject("Asio", "Project/Libs", system_info, program_options)
        SetupProject("Assert", "Project/Libs", system_info, program_options)
        SetupProject("BackwardCPP", "Project/Libs", system_info, program_options)
        SetupProject("BetterEnums", "Project/Libs", system_info, program_options)
        SetupProject("Boost", "Project/Libs", system_info, program_options)
        SetupProject("CFGPath", "Project/Libs", system_info, program_options)
        SetupProject("CppFS", "Project/Libs", system_info, program_options)
        SetupProject("EasyProcess", "Project/Libs", system_info, program_options)
        SetupProject("FantasyName", "Project/Libs", system_info, program_options)
        SetupProject("HTMApp", "Project/Libs", system_info, program_options)
        SetupProject("ImmutableString", "Project/Libs", system_info, program_options)
        SetupProject("MicroPather", "Project/Libs", system_info, program_options)
        SetupProject("ModernCPPJson", "Project/Libs", system_info, program_options)
        SetupProject("Patool", "Project/Libs", system_info, program_options)
        SetupProject("Pistache", "Project/Libs", system_info, program_options)
        SetupProject("Popl", "Project/Libs", system_info, program_options)
        SetupProject("PyBind", "Project/Libs", system_info, program_options)
        SetupProject("Python3", "Project/Libs", system_info, program_options)
        SetupProject("Pyunpack", "Project/Libs", system_info, program_options)
        SetupProject("TinyXML2", "Project/Libs", system_info, program_options)
        SetupProject("TMXParser", "Project/Libs", system_info, program_options)
        SetupProject("Websocketpp", "Project/Libs", system_info, program_options)
        SetupProject("Zlib", "Project/Libs", system_info, program_options)
    if do_programs or do_all:
        SetupProject("Premake5", "Project/Programs", system_info, program_options)
        SetupProject("Tiled", "Project/Programs", system_info, program_options)
    if do_build or do_all:
        BuildProject(system_info, program_options)
    if do_pythonlib or do_all:
        BuildPythonLibrary(system_info, program_options)
###########################################################################
main()
