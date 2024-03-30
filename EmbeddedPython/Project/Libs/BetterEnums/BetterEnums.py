# Source: https://github.com/NearlyTRex/better-enums
# Version: Gitmaster

# Steps
SetMacroFile = 'ReplaceText("enum.h", "\\n\\n#ifdef BETTER_ENUMS_MACRO_FILE\\n", "\\n#define BETTER_ENUMS_MACRO_FILE <enum_macros.h>\\n#ifdef BETTER_ENUMS_MACRO_FILE\\n")'

# Library info
Setup = {}
Setup['url'] = "https://github.com/NearlyTRex/better-enums/archive/master.zip"
Setup['extractdir'] = "better-enums-master"
Setup['steps'] = {}
Setup['steps']['all'] = []
Setup['steps']['all'].append(SetMacroFile)
