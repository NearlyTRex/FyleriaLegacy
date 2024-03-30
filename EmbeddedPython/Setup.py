# Setup script
# Download, extract, and configure libraries
# Configure project for various platforms

# Base imports
import sys
import os
import os.path
from Setup import ProgramOptions
from Setup import SystemInformation
from Setup import Python
from Setup import Project
from Setup import Utility

###########################################################################
## Main
def main():

    # Get program options and system info
    program_options = ProgramOptions.GetProgramOptions()
    system_info = SystemInformation.GetSystemInformation(program_options, os.path.dirname(os.path.abspath( __file__ )))

    # Check Python
    if Python.DetectPython(Python.GetRequiredPythonVersion()) == False:
        Utility.ErrorStatement("Python %d.%d or higher is required to run this script" % Python.GetRequiredPythonVersion())
        sys.exit(-1)

    # Parse program options
    do_all = program_options.mode == "all"
    do_setup_cpp_libraries = program_options.mode == "setup_cpp_libraries"
    do_setup_python_libraries = program_options.mode == "setup_python_libraries"
    do_setup_javascript_libraries = program_options.mode == "setup_javascript_libraries"
    do_build_premake = program_options.mode == "build_premake"
    do_build_tiled = program_options.mode == "build_tiled"
    do_build_zip = program_options.mode == "build_zip"
    do_build_game = program_options.mode == "build_game"
    if do_build_premake or do_all:
        Project.SetupProject("Premake5", "Project/Programs", system_info, program_options)
    if do_build_tiled or do_all:
        Project.SetupProject("Tiled", "Project/Programs", system_info, program_options)
    if do_build_zip or do_all:
        Project.SetupProject("Zip", "Project/Programs", system_info, program_options)
        Project.SetupProject("Unzip", "Project/Programs", system_info, program_options)
    if do_setup_cpp_libraries or do_all:
        Project.SetupProject("Assert", "Project/Libs", system_info, program_options)
        Project.SetupProject("BackwardCPP", "Project/Libs", system_info, program_options)
        Project.SetupProject("BetterEnums", "Project/Libs", system_info, program_options)
        Project.SetupProject("Boost", "Project/Libs", system_info, program_options)
        Project.SetupProject("FantasyName", "Project/Libs", system_info, program_options)
        Project.SetupProject("ImmutableString", "Project/Libs", system_info, program_options)
        Project.SetupProject("MicroPather", "Project/Libs", system_info, program_options)
        Project.SetupProject("ModernCPPJson", "Project/Libs", system_info, program_options)
        Project.SetupProject("ObjectThreadsafe", "Project/Libs", system_info, program_options)
        Project.SetupProject("PyBind", "Project/Libs", system_info, program_options)
        Project.SetupProject("Python3", "Project/Libs", system_info, program_options)
        Project.SetupProject("SpdLog", "Project/Libs", system_info, program_options)
        Project.SetupProject("TinyXML2", "Project/Libs", system_info, program_options)
        Project.SetupProject("TMXParser", "Project/Libs", system_info, program_options)
        Project.SetupProject("URIParser", "Project/Libs", system_info, program_options)
        Project.SetupProject("Zlib", "Project/Libs", system_info, program_options)
    if do_setup_javascript_libraries or do_all:
        Project.SetupProject("Bootstrap", "Project/Libs", system_info, program_options)
        Project.SetupProject("jQuery", "Project/Libs", system_info, program_options)
        Project.SetupProject("Phaser", "Project/Libs", system_info, program_options)
    if do_setup_python_libraries or do_all:
        Python.SetupPythonLibrary(system_info, program_options)
    if do_build_game or do_all:
        Project.BuildProject(system_info, program_options)
###########################################################################
main()
