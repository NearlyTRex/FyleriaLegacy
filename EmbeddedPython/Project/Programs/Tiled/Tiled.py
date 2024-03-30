# Source: https://github.com/NearlyTRex/tiled
# Version: Gitmaster

# Program info
Setup = {}
Setup['url'] = "https://github.com/NearlyTRex/tiled/archive/master.zip"
Setup['extractdir'] = "tiled-master"
Setup['steps'] = {}
Setup['steps']['posix'] = []
Setup['steps']['posix'].append('RunProcess("qmake")')
Setup['steps']['posix'].append('RunProcess("make")')
Setup['steps']['posix'].append('MakeExecutable("./bin/tiled")')
Setup['steps']['windows'] = []
Setup['steps']['windows'].append('RunProcess("qmake")')
Setup['steps']['windows'].append('RunProcess("make")')
Setup['steps']['windows'].append('MakeExecutable("./bin/tiled.exe")')
