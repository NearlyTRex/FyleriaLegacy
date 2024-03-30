# Source: https://github.com/NearlyTRex/phaser
# Version: Gitmaster

# Steps
CopyFilePhaserJs = 'CopyFile("dist/phaser.min.js", "$(RootPath)/Data/Libs/phaser.min.js")'
CopyFilePhaserArcadePhysicsJs = 'CopyFile("dist/phaser-arcade-physics.min.js", "$(RootPath)/Data/Libs/phaser-arcade-physics.min.js")'

# Library info
Setup = {}
Setup['url'] = "https://github.com/NearlyTRex/phaser/archive/master.zip"
Setup['extractdir'] = "phaser-master"
Setup['steps'] = {}
Setup['steps']['all'] = []
Setup['steps']['all'].append(CopyFilePhaserJs)
Setup['steps']['all'].append(CopyFilePhaserArcadePhysicsJs)
