# Source: https://github.com/NearlyTRex/premake-core
# Version: Gitmaster

# Program info
Setup = {}
Setup['url'] = "https://github.com/NearlyTRex/premake-core/archive/master.zip"
Setup['extractdir'] = "premake-core-master"
Setup['steps'] = {}
Setup['steps']['linux'] = []
Setup['steps']['linux'].append('RunProcess("make -f Bootstrap.mak linux")')
Setup['steps']['linux'].append('MakeExecutable("./bin/release/premake5")')
Setup['steps']['cygwin'] = []
Setup['steps']['cygwin'].append('RunProcess("make -f Bootstrap.mak linux")')
Setup['steps']['cygwin'].append('MakeExecutable("./bin/release/premake5.exe")')
Setup['steps']['wsl'] = []
Setup['steps']['wsl'].append('RunProcess("make -f Bootstrap.mak linux")')
Setup['steps']['wsl'].append('MakeExecutable("./bin/release/premake5.exe")')
Setup['steps']['macosx'] = []
Setup['steps']['macosx'].append('RunProcess("make -f Bootstrap.mak osx")')
Setup['steps']['macosx'].append('MakeExecutable("./bin/release/premake5")')
Setup['steps']['bsd'] = []
Setup['steps']['bsd'].append('RunProcess("make -f Bootstrap.mak bsd")')
Setup['steps']['bsd'].append('MakeExecutable("./bin/release/premake5")')
Setup['steps']['mingw'] = []
Setup['steps']['mingw'].append('RunProcess("CC=mingw32-gcc mingw32-make -f Bootstrap.mak mingw")')
Setup['steps']['mingw'].append('MakeExecutable("./bin/release/premake5.exe")')
Setup['steps']['windows'] = []
Setup['steps']['windows'].append('RunProcess("nmake -f Bootstrap.mak windows")')
Setup['steps']['windows'].append('MakeExecutable("./bin/release/premake5.exe")')
