# Source: https://github.com/NearlyTRex/cpython
# Version: Gitmaster

# Steps
RunProcessConfigure32 = 'RunProcess("./configure CFLAGS=-m32 CXXFLAGS=-m32 LDFLAGS=-m32")'
RunProcessConfigure64 = 'RunProcess("./configure CFLAGS=-m64 CXXFLAGS=-m64 LDFLAGS=-m64")'

# Library info
Setup = {}
Setup['url'] = "https://github.com/NearlyTRex/cpython/archive/master.zip"
Setup['extractdir'] = "cpython-master"
Setup['steps'] = {}
