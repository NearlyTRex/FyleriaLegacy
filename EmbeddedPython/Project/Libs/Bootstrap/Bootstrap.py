# Source: https://github.com/NearlyTRex/bootstrap
# Version: Gitmaster

# Steps
CopyFileBootstrapCss = 'CopyFile("dist/css/bootstrap.min.css", "$(RootPath)/Data/Libs/bootstrap.min.css")'
CopyFileBootstrapGridCss = 'CopyFile("dist/css/bootstrap-grid.min.css", "$(RootPath)/Data/Libs/bootstrap-grid.min.css")'
CopyFileBootstrapRebootCss = 'CopyFile("dist/css/bootstrap-reboot.min.css", "$(RootPath)/Data/Libs/bootstrap-reboot.min.css")'
CopyFileBootstrapJs = 'CopyFile("dist/js/bootstrap.min.js", "$(RootPath)/Data/Libs/bootstrap.min.js")'

# Library info
Setup = {}
Setup['url'] = "https://github.com/NearlyTRex/bootstrap/archive/master.zip"
Setup['extractdir'] = "bootstrap-master"
Setup['steps'] = {}
Setup['steps']['all'] = []
Setup['steps']['all'].append(CopyFileBootstrapCss)
Setup['steps']['all'].append(CopyFileBootstrapGridCss)
Setup['steps']['all'].append(CopyFileBootstrapRebootCss)
Setup['steps']['all'].append(CopyFileBootstrapJs)
