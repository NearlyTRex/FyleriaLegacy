# Imports
import argparse

###########################################################################
# Program options
class ProgramOptions:
    def __init__(self):
        pass
###########################################################################
# Get program options
def GetProgramOptions():
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
        'codelite',
        'vs2005',
        'vs2008',
        'vs2010',
        'vs2012',
        'vs2013',
        'vs2015',
        'vs2017',
        'vs2019',
        'xcode4'
    ], default='gmake2', help='Project type to pass to Premake')
    parser.add_argument('-v', '--verbose', action='store_true', help='Enable verbose messages')
    parser.add_argument('mode', choices=[
        'all',
        'setup_cpp_libraries',
        'setup_python_libraries',
        'setup_javascript_libraries',
        'build_premake',
        'build_tiled',
        'build_zip',
        'build_game',
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
