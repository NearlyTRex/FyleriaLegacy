# Start websocket server
import os, os.path, sys
import subprocess
import argparse

###########################################################################
## Parse options
parser = argparse.ArgumentParser(description='Start game server.')
parser.add_argument('--bitsize', choices=[
    '32',
    '64'
], default='64', help="Bit size")
parser.add_argument('--os', choices=[
    'linux',
    'mingw'
], default='linux', help="Operating system type")
parser.add_argument('--buildtype', choices=[
    'release',
    'debug'
], default='debug', help="Build type")
parser.add_argument('--servertype', choices=[
    'websocket',
    'rest'
], default='rest', help="Server type")
args = parser.parse_args()
bit_type = args.bitsize
os_type = args.os
build_type = args.buildtype
server_type = args.servertype
###########################################################################
# Globals
required_python_version = (3,5)
build_path = "Bin"
build_files = {}
build_files["linux"] = {}
build_files["linux"]["32"] = {}
build_files["linux"]["32"]["release"] = "fyleria_main_linux_x86_release"
build_files["linux"]["32"]["debug"] = "fyleria_main_linux_x86_debug"
build_files["linux"]["64"] = {}
build_files["linux"]["64"]["release"] = "fyleria_main_linux_x86_64_release"
build_files["linux"]["64"]["debug"] = "fyleria_main_linux_x86_64_debug"
build_files["mingw"] = {}
build_files["mingw"]["32"] = {}
build_files["mingw"]["32"]["release"] = "fyleria_main_mingw_x86_release.exe"
build_files["mingw"]["32"]["debug"] = "fyleria_main_mingw_x86_debug.exe"
build_files["mingw"]["64"] = {}
build_files["mingw"]["64"]["release"] = "fyleria_main_mingw_x86_64_release.exe"
build_files["mingw"]["64"]["debug"] = "fyleria_main_mingw_x86_64_debug.exe"
build_file = os.path.join(build_path, build_files[os_type][bit_type][build_type])
flag_start_server = ""
if server_type == "websocket":
    flag_start_server = "-w"
elif server_type == "rest":
    flag_start_server = "-r"
flag_user_config_folder = "--user_config_folder=Data"
flag_webroot_folder = "--webroot=Web"
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
## Main
def main():

    # Check Python
    if DetectPython(required_python_version) == False:
        ErrorStatement("Python %d.%d or higher is required to run this script" % required_python_version)
        sys.exit(-1)

    # Start server
    subprocess.call([build_file, flag_start_server, flag_user_config_folder, flag_webroot_folder])
###########################################################################
main()
