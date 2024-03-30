# Source: https://github.com/NearlyTRex/zip
# Version: Gitmaster

# Program info
Setup = {}
Setup['url'] = "https://github.com/NearlyTRex/zip/archive/master.zip"
Setup['extractdir'] = "zip-master"
Setup['steps'] = {}
Setup['steps']['windows'] = []
Setup['steps']['windows'].append('RunProcess("cmake .")')
Setup['steps']['windows'].append('RunProcess("make")')
