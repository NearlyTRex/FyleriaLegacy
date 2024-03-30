# Imports
import os
import sys
import shutil
import subprocess
from . import Utility

###########################################################################
# Required python version
def GetRequiredPythonVersion():
    return (3,5)
###########################################################################
# Detect Python version
def DetectPython(required_version):
    if (sys.version_info <= required_version):
        return False
    else:
        return True
###########################################################################
## Setup Python Library
def SetupPythonLibrary(system_info, program_options):

    # Inform user
    Utility.LogStatement("Building Python library")

    # Zip file
    new_zip_file = "PythonLib.zip"
    new_zip_location = "../../../../../Data/"

    # Check lib directory
    if not os.path.exists(system_info.python3_libdir):
        Utility.ErrorStatement("Python source library directory does not exist")
        return False

    # Change to lib directory
    Utility.LogStatement("Changing directory to " + system_info.python3_libdir)
    os.chdir(system_info.python3_libdir)

    # Zip python library
    Utility.LogStatement("Zipping Python library")
    Utility.RunLiveSubprocess(subprocess_args=[
        system_info.zip_bin,
        "-r",
        new_zip_file,
        "."], verbose_output=program_options.verbose)

    # Check zip file
    if not os.path.exists(new_zip_file) and not os.path.isfile(new_zip_file):
        Utility.ErrorStatement("Python library was not created")
        return False

    # Moving python library
    Utility.LogStatement("Copying Python library to " + os.path.abspath(new_zip_location))
    try:
        shutil.copyfile(new_zip_file, os.path.join(new_zip_location, new_zip_file))
    except shutil.Error:
        pass

    # Change to script directory
    Utility.LogStatement("Changing directory to " + system_info.root_path)
    os.chdir(system_info.root_path)
    return True
###########################################################################
