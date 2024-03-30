# Source: https://github.com/NearlyTRex/unzip
# Version: Gitmaster

# Program info
Setup = {}
Setup['url'] = "https://github.com/NearlyTRex/unzip/archive/master.zip"
Setup['extractdir'] = "unzip-master"
Setup['steps'] = {}
Setup['steps']['windows'] = []
Setup['steps']['windows'].append('RunProcess("cmake .")')
Setup['steps']['windows'].append('RunProcess("make")')
