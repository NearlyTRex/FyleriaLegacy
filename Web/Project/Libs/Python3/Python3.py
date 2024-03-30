# Source: http://www.python.org/
# Version: 3.6.2

# Steps
RunProcessConfigure32 = 'RunProcess("./configure CFLAGS=-m32 CXXFLAGS=-m32 LDFLAGS=-m32")'
RunProcessConfigure64 = 'RunProcess("./configure CFLAGS=-m64 CXXFLAGS=-m64 LDFLAGS=-m64")'

# Library info
Setup = {}
Setup['url'] = "https://www.python.org/ftp/python/3.6.2/Python-3.6.2.tgz"
Setup['extractdir'] = "Python-3.6.2"
Setup['steps'] = {}
