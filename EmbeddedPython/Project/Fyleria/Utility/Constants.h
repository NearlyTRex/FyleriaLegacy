// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

#ifndef _GECKO_UTILITY_CONSTANTS_H_
#define _GECKO_UTILITY_CONSTANTS_H_

// Application name
#define APPLICATION_NAME_SHORT                      "Fyleria"
#define APPLICATION_NAME_LONG                       "Fyleria Game Engine"

// Application version
#define APPLICATION_VERSION                         "v1.0"

// Save limits
#define MAX_SAVE_SLOT                               5

// Tree limits
#define MAX_SKILL_RANK                              20

// Character limits
#define MAX_TEAM_CHARACTER_AMOUNT                   6

// Limits on equipped items
#define HAND_SIZE_LIMIT                             4
#define BODY_SIZE_LIMIT                             1

// Skill attacks
#define BASE_NUMBER_OF_SKILL_ATTACKS                1

// Skill damage boundary
#define SKILL_DAMAGE_BOUNDARY_PERCENT               0.1
#define SKILL_DAMAGE_BOUNDARY_DEFAULT_VALUE         1.0

// Skill rank upgrade amount
#define SKILL_RANK_UPGRADE_AMOUNT                   10

// Defaults for generators
#define DEFAULT_MAX_AGE                             100
#define DEFAULT_MAX_METER                           200
#define DEFAULT_MAX_SCORING                         200
#define DEFAULT_MAX_SKILL                           200

// Paths
#define DEFAULT_MAX_PATH_SIZE                       256

// File URI base
#define FILE_URI_BASE                               "file://"

// Starting URI
#define STARTING_URI                                "about:blank"

// Folders
#define FOLDER_DATA                                 "Data"
#define FOLDER_SAVE                                 "Save"
#define FOLDER_LOG                                  "Log"

// Config file
#define CONFIG_FILE                                 "Config.json"

// Python file
#define PYTHON_FILE                                 "PythonLib.zip"

// Icon files
#define ICON_FILE_MAIN_WINDOW                       "Icons/Icon-32x32.ico"

// Item files
#define ITEM_FILE_ARMOR_CHEST                       "Items/ItemTreeArmor-Chest.json"
#define ITEM_FILE_ARMOR_FEET                        "Items/ItemTreeArmor-Feet.json"
#define ITEM_FILE_ARMOR_FINGER                      "Items/ItemTreeArmor-Finger.json"
#define ITEM_FILE_ARMOR_HANDS                       "Items/ItemTreeArmor-Hands.json"
#define ITEM_FILE_ARMOR_HEAD                        "Items/ItemTreeArmor-Head.json"
#define ITEM_FILE_ARMOR_NECK                        "Items/ItemTreeArmor-Neck.json"
#define ITEM_FILE_ARMOR_LEGS                        "Items/ItemTreeArmor-Legs.json"
#define ITEM_FILE_ARMOR_SHIELD                      "Items/ItemTreeArmor-Shield.json"
#define ITEM_FILE_INGREDIENT_BAR                    "Items/ItemTreeIngredient-Bar.json"
#define ITEM_FILE_INGREDIENT_CLOTH                  "Items/ItemTreeIngredient-Cloth.json"
#define ITEM_FILE_INGREDIENT_CRYSTAL                "Items/ItemTreeIngredient-Crystal.json"
#define ITEM_FILE_INGREDIENT_LEATHER                "Items/ItemTreeIngredient-Leather.json"
#define ITEM_FILE_INGREDIENT_MAIL                   "Items/ItemTreeIngredient-Mail.json"
#define ITEM_FILE_INGREDIENT_PLATE                  "Items/ItemTreeIngredient-Plate.json"
#define ITEM_FILE_INGREDIENT_SCALE                  "Items/ItemTreeIngredient-Scale.json"
#define ITEM_FILE_INGREDIENT_SCREW                  "Items/ItemTreeIngredient-Screw.json"
#define ITEM_FILE_INGREDIENT_SHEET                  "Items/ItemTreeIngredient-Sheet.json"
#define ITEM_FILE_INGREDIENT_STUD                   "Items/ItemTreeIngredient-Stud.json"
#define ITEM_FILE_INGREDIENT_THREAD                 "Items/ItemTreeIngredient-Thread.json"
#define ITEM_FILE_POTION_ENERGY                     "Items/ItemTreePotion-Energy.json"
#define ITEM_FILE_POTION_HEAL                       "Items/ItemTreePotion-Heal.json"
#define ITEM_FILE_POTION_MAGIC                      "Items/ItemTreePotion-Magic.json"
#define ITEM_FILE_POTION_SPEED                      "Items/ItemTreePotion-Speed.json"
#define ITEM_FILE_WEAPON_BLUNT                      "Items/ItemTreeWeapon-Blunt.json"
#define ITEM_FILE_WEAPON_MAGE                       "Items/ItemTreeWeapon-Mage.json"
#define ITEM_FILE_WEAPON_PIERCE                     "Items/ItemTreeWeapon-Pierce.json"
#define ITEM_FILE_WEAPON_SLASH                      "Items/ItemTreeWeapon-Slash.json"

// Skill files
#define SKILL_FILE_AFFINITY_BLOOD                   "Skills/SkillTreeAffinity-Blood.json"
#define SKILL_FILE_AFFINITY_DARK                    "Skills/SkillTreeAffinity-Dark.json"
#define SKILL_FILE_AFFINITY_EARTH                   "Skills/SkillTreeAffinity-Earth.json"
#define SKILL_FILE_AFFINITY_FIRE                    "Skills/SkillTreeAffinity-Fire.json"
#define SKILL_FILE_AFFINITY_FLESH                   "Skills/SkillTreeAffinity-Flesh.json"
#define SKILL_FILE_AFFINITY_FORCE                   "Skills/SkillTreeAffinity-Force.json"
#define SKILL_FILE_AFFINITY_HOLY                    "Skills/SkillTreeAffinity-Holy.json"
#define SKILL_FILE_AFFINITY_ICE                     "Skills/SkillTreeAffinity-Ice.json"
#define SKILL_FILE_AFFINITY_LIGHT                   "Skills/SkillTreeAffinity-Light.json"
#define SKILL_FILE_AFFINITY_MIND                    "Skills/SkillTreeAffinity-Mind.json"
#define SKILL_FILE_AFFINITY_SHOCK                   "Skills/SkillTreeAffinity-Shock.json"
#define SKILL_FILE_AFFINITY_WIND                    "Skills/SkillTreeAffinity-Wind.json"
#define SKILL_FILE_ALCHEMY_ALCHEMIST                "Skills/SkillTreeAlchemy-Alchemist.json"
#define SKILL_FILE_ALCHEMY_CHEMIST                  "Skills/SkillTreeAlchemy-Chemist.json"
#define SKILL_FILE_ALCHEMY_ENERGIST                 "Skills/SkillTreeAlchemy-Energist.json"
#define SKILL_FILE_ALCHEMY_HEALER                   "Skills/SkillTreeAlchemy-Healer.json"
#define SKILL_FILE_BREAKDOWN_BOWBANE                "Skills/SkillTreeBreakdown-Bowbane.json"
#define SKILL_FILE_BREAKDOWN_GOLDBANE               "Skills/SkillTreeBreakdown-Goldbane.json"
#define SKILL_FILE_BREAKDOWN_HAMMERBANE             "Skills/SkillTreeBreakdown-Hammerbane.json"
#define SKILL_FILE_BREAKDOWN_PLATEBANE              "Skills/SkillTreeBreakdown-Platebane.json"
#define SKILL_FILE_BREAKDOWN_SCALEBANE              "Skills/SkillTreeBreakdown-Scalebane.json"
#define SKILL_FILE_BREAKDOWN_SHIELDBANE             "Skills/SkillTreeBreakdown-Shieldbane.json"
#define SKILL_FILE_BREAKDOWN_SPELLBANE              "Skills/SkillTreeBreakdown-Spellbane.json"
#define SKILL_FILE_BREAKDOWN_STUDREMOVER            "Skills/SkillTreeBreakdown-StudRemover.json"
#define SKILL_FILE_BREAKDOWN_SWORDBANE              "Skills/SkillTreeBreakdown-Swordbane.json"
#define SKILL_FILE_BREAKDOWN_THREADBARE             "Skills/SkillTreeBreakdown-Threadbare.json"
#define SKILL_FILE_COMBAT_AMBIDEXTROUS              "Skills/SkillTreeCombat-Ambidextrous.json"
#define SKILL_FILE_COMBAT_AVATAR                    "Skills/SkillTreeCombat-Avatar.json"
#define SKILL_FILE_COMBAT_BARBARIAN                 "Skills/SkillTreeCombat-Barbarian.json"
#define SKILL_FILE_COMBAT_BLADEMASTER               "Skills/SkillTreeCombat-Blademaster.json"
#define SKILL_FILE_COMBAT_FOCUSED                   "Skills/SkillTreeCombat-Focused.json"
#define SKILL_FILE_COMBAT_MAGE                      "Skills/SkillTreeCombat-Mage.json"
#define SKILL_FILE_COMBAT_ROGUE                     "Skills/SkillTreeCombat-Rogue.json"
#define SKILL_FILE_COMBAT_STALWART                  "Skills/SkillTreeCombat-Stalwart.json"
#define SKILL_FILE_CRAFTING_BOWSMITH                "Skills/SkillTreeCrafting-Bowsmith.json"
#define SKILL_FILE_CRAFTING_GOLDSMITH               "Skills/SkillTreeCrafting-Goldsmith.json"
#define SKILL_FILE_CRAFTING_HAMMERSMITH             "Skills/SkillTreeCrafting-Hammersmith.json"
#define SKILL_FILE_CRAFTING_PLATESMITH              "Skills/SkillTreeCrafting-Platesmith.json"
#define SKILL_FILE_CRAFTING_SCALESMITH              "Skills/SkillTreeCrafting-Scalesmith.json"
#define SKILL_FILE_CRAFTING_SHIELDSMITH             "Skills/SkillTreeCrafting-Shieldsmith.json"
#define SKILL_FILE_CRAFTING_SPELLSMITH              "Skills/SkillTreeCrafting-Spellsmith.json"
#define SKILL_FILE_CRAFTING_SWORDSMITH              "Skills/SkillTreeCrafting-Swordsmith.json"
#define SKILL_FILE_CRAFTING_TANNER                  "Skills/SkillTreeCrafting-Tanner.json"
#define SKILL_FILE_CRAFTING_WEAVER                  "Skills/SkillTreeCrafting-Weaver.json"
#define SKILL_FILE_WEAPON_BASH                      "Skills/SkillTreeWeapon-Bash.json"
#define SKILL_FILE_WEAPON_BLOCK                     "Skills/SkillTreeWeapon-Block.json"
#define SKILL_FILE_WEAPON_BREAK                     "Skills/SkillTreeWeapon-Break.json"
#define SKILL_FILE_WEAPON_CLEAVE                    "Skills/SkillTreeWeapon-Cleave.json"
#define SKILL_FILE_WEAPON_COUNTER                   "Skills/SkillTreeWeapon-Counter.json"
#define SKILL_FILE_WEAPON_CRACK                     "Skills/SkillTreeWeapon-Crack.json"
#define SKILL_FILE_WEAPON_CRITICALSHOT              "Skills/SkillTreeWeapon-CriticalShot.json"
#define SKILL_FILE_WEAPON_CRUSH                     "Skills/SkillTreeWeapon-Crush.json"
#define SKILL_FILE_WEAPON_DECAPITATE                "Skills/SkillTreeWeapon-Decapitate.json"
#define SKILL_FILE_WEAPON_DODGE                     "Skills/SkillTreeWeapon-Dodge.json"
#define SKILL_FILE_WEAPON_DRILL                     "Skills/SkillTreeWeapon-Drill.json"
#define SKILL_FILE_WEAPON_IMPACT                    "Skills/SkillTreeWeapon-Impact.json"
#define SKILL_FILE_WEAPON_IMPALE                    "Skills/SkillTreeWeapon-Impale.json"
#define SKILL_FILE_WEAPON_PARRY                     "Skills/SkillTreeWeapon-Parry.json"
#define SKILL_FILE_WEAPON_PIERCE                    "Skills/SkillTreeWeapon-Pierce.json"
#define SKILL_FILE_WEAPON_RIPOSTE                   "Skills/SkillTreeWeapon-Riposte.json"
#define SKILL_FILE_WEAPON_RUSH                      "Skills/SkillTreeWeapon-Rush.json"
#define SKILL_FILE_WEAPON_SEVER                     "Skills/SkillTreeWeapon-Sever.json"
#define SKILL_FILE_WEAPON_SHOOT                     "Skills/SkillTreeWeapon-Shoot.json"
#define SKILL_FILE_WEAPON_SLASH                     "Skills/SkillTreeWeapon-Slash.json"
#define SKILL_FILE_WEAPON_SLICE                     "Skills/SkillTreeWeapon-Slice.json"
#define SKILL_FILE_WEAPON_SLIT                      "Skills/SkillTreeWeapon-Slit.json"
#define SKILL_FILE_WEAPON_SMASH                     "Skills/SkillTreeWeapon-Smash.json"
#define SKILL_FILE_WEAPON_STEALTHSTRIKE             "Skills/SkillTreeWeapon-StealthStrike.json"

// Lib files
#define LIB_FILE_COMMON_JS                          "Libs/common.js"
#define LIB_FILE_BOOTSTRAP_CSS                      "Libs/bootstrap.min.css"
#define LIB_FILE_BOOTSTRAP_JS                       "Libs/bootstrap.min.js"
#define LIB_FILE_JQUERY_JS                          "Libs/jquery.min.js"
#define LIB_FILE_PHASER_JS                          "Libs/phaser.min.js"

// Page files
#define PAGE_FILE_INTRO                             "Pages/Intro.html"
#define PAGE_FILE_LOADING                           "Pages/Loading.html"
#define PAGE_FILE_MAIN_MENU                         "Pages/MainMenu.html"
#define PAGE_FILE_STATUS_MENU                       "Pages/StatusMenu.html"
#define PAGE_FILE_SAVE_MENU                         "Pages/SaveMenu.html"
#define PAGE_FILE_CRAFTING_MENU                     "Pages/CraftingMenu.html"
#define PAGE_FILE_MAP                               "Pages/Map.html"
#define PAGE_FILE_SHOP                              "Pages/Shop.html"
#define PAGE_FILE_BATTLE                            "Pages/Battle.html"
#define PAGE_FILE_CHARACTER_CREATION                "Pages/CharacterCreation.html"
#define PAGE_FILE_CREDITS                           "Pages/Credits.html"
#define PAGE_FILE_TOOL_MAIN                         "Pages/Tool.html"
#define PAGE_FILE_TOOL_CHARACTER                    "Pages/ToolCharacter.html"
#define PAGE_FILE_TOOL_PARTY                        "Pages/ToolParty.html"
#define PAGE_FILE_TOOL_SAVE                         "Pages/ToolSave.html"

#endif
