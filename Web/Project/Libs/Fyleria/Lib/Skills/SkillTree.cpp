// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#include "Skills/SkillTree.h"
#include "Config/ConfigManager.h"
#include "Character/CharacterManager.h"
#include "Character/CharacterPartyManager.h"
#include "Stats/StatChange.h"
#include "Utility/Constants.h"
#include "Utility/TypesFantasyName.h"
#include "Utility/TypesJson.h"

namespace Gecko
{

#define POSTPROCESS_SKILLS(tree)                                                            \
{                                                                                           \
    for(const TreeIndex& index : GetAll##tree##Skills())                                    \
    {                                                                                       \
        SkillData##tree& skillData = SkillTree##tree::GetInstance()->GetLeaf(index);        \
        skillData.SetSkillTreeIndex(index);                                                 \
        for(StatChange& statChange : skillData.GetStatChanges())                            \
        {                                                                                   \
            statChange.SetSkillTreeIndex(index);                                            \
        }                                                                                   \
    }                                                                                       \
}

void LoadSkillTreesIntoMemory()
{
    // Affinity
    SkillTreeAffinity::GetInstance()->AddBranch(IndexedString("Blood"), IndexedString(ConfigManager::GetInstance()->GetSkillAffinityBloodFile()));
    SkillTreeAffinity::GetInstance()->AddBranch(IndexedString("Dark"), IndexedString(ConfigManager::GetInstance()->GetSkillAffinityDarkFile()));
    SkillTreeAffinity::GetInstance()->AddBranch(IndexedString("Earth"), IndexedString(ConfigManager::GetInstance()->GetSkillAffinityEarthFile()));
    SkillTreeAffinity::GetInstance()->AddBranch(IndexedString("Fire"), IndexedString(ConfigManager::GetInstance()->GetSkillAffinityFireFile()));
    SkillTreeAffinity::GetInstance()->AddBranch(IndexedString("Flesh"), IndexedString(ConfigManager::GetInstance()->GetSkillAffinityFleshFile()));
    SkillTreeAffinity::GetInstance()->AddBranch(IndexedString("Force"), IndexedString(ConfigManager::GetInstance()->GetSkillAffinityForceFile()));
    SkillTreeAffinity::GetInstance()->AddBranch(IndexedString("Holy"), IndexedString(ConfigManager::GetInstance()->GetSkillAffinityHolyFile()));
    SkillTreeAffinity::GetInstance()->AddBranch(IndexedString("Ice"), IndexedString(ConfigManager::GetInstance()->GetSkillAffinityIceFile()));
    SkillTreeAffinity::GetInstance()->AddBranch(IndexedString("Light"), IndexedString(ConfigManager::GetInstance()->GetSkillAffinityLightFile()));
    SkillTreeAffinity::GetInstance()->AddBranch(IndexedString("Mind"), IndexedString(ConfigManager::GetInstance()->GetSkillAffinityMindFile()));
    SkillTreeAffinity::GetInstance()->AddBranch(IndexedString("Shock"), IndexedString(ConfigManager::GetInstance()->GetSkillAffinityShockFile()));
    SkillTreeAffinity::GetInstance()->AddBranch(IndexedString("Wind"), IndexedString(ConfigManager::GetInstance()->GetSkillAffinityWindFile()));

    // Alchemy
    SkillTreeAlchemy::GetInstance()->AddBranch(IndexedString("Alchemist"), IndexedString(ConfigManager::GetInstance()->GetSkillAlchemyAlchemistFile()));
    SkillTreeAlchemy::GetInstance()->AddBranch(IndexedString("Chemist"), IndexedString(ConfigManager::GetInstance()->GetSkillAlchemyChemistFile()));
    SkillTreeAlchemy::GetInstance()->AddBranch(IndexedString("Energist"), IndexedString(ConfigManager::GetInstance()->GetSkillAlchemyEnergistFile()));
    SkillTreeAlchemy::GetInstance()->AddBranch(IndexedString("Healer"), IndexedString(ConfigManager::GetInstance()->GetSkillAlchemyHealerFile()));

    // Breakdown
    SkillTreeBreakdown::GetInstance()->AddBranch(IndexedString("Bowbane"), IndexedString(ConfigManager::GetInstance()->GetSkillBreakdownBowbaneFile()));
    SkillTreeBreakdown::GetInstance()->AddBranch(IndexedString("Goldbane"), IndexedString(ConfigManager::GetInstance()->GetSkillBreakdownGoldbaneFile()));
    SkillTreeBreakdown::GetInstance()->AddBranch(IndexedString("Hammerbane"), IndexedString(ConfigManager::GetInstance()->GetSkillBreakdownHammerbaneFile()));
    SkillTreeBreakdown::GetInstance()->AddBranch(IndexedString("Platebane"), IndexedString(ConfigManager::GetInstance()->GetSkillBreakdownPlatebaneFile()));
    SkillTreeBreakdown::GetInstance()->AddBranch(IndexedString("Scalebane"), IndexedString(ConfigManager::GetInstance()->GetSkillBreakdownScalebaneFile()));
    SkillTreeBreakdown::GetInstance()->AddBranch(IndexedString("Shieldbane"), IndexedString(ConfigManager::GetInstance()->GetSkillBreakdownShieldbaneFile()));
    SkillTreeBreakdown::GetInstance()->AddBranch(IndexedString("Spellbane"), IndexedString(ConfigManager::GetInstance()->GetSkillBreakdownSpellbaneFile()));
    SkillTreeBreakdown::GetInstance()->AddBranch(IndexedString("StudRemover"), IndexedString(ConfigManager::GetInstance()->GetSkillBreakdownStudRemoverFile()));
    SkillTreeBreakdown::GetInstance()->AddBranch(IndexedString("Swordbane"), IndexedString(ConfigManager::GetInstance()->GetSkillBreakdownSwordbaneFile()));
    SkillTreeBreakdown::GetInstance()->AddBranch(IndexedString("Threadbare"), IndexedString(ConfigManager::GetInstance()->GetSkillBreakdownThreadbareFile()));

    // Combat
    SkillTreeCombat::GetInstance()->AddBranch(IndexedString("Ambidextrous"), IndexedString(ConfigManager::GetInstance()->GetSkillCombatAmbidextrousFile()));
    SkillTreeCombat::GetInstance()->AddBranch(IndexedString("Avatar"), IndexedString(ConfigManager::GetInstance()->GetSkillCombatAvatarFile()));
    SkillTreeCombat::GetInstance()->AddBranch(IndexedString("Barbarian"), IndexedString(ConfigManager::GetInstance()->GetSkillCombatBarbarianFile()));
    SkillTreeCombat::GetInstance()->AddBranch(IndexedString("Blademaster"), IndexedString(ConfigManager::GetInstance()->GetSkillCombatBlademasterFile()));
    SkillTreeCombat::GetInstance()->AddBranch(IndexedString("Focused"), IndexedString(ConfigManager::GetInstance()->GetSkillCombatFocusedFile()));
    SkillTreeCombat::GetInstance()->AddBranch(IndexedString("Mage"), IndexedString(ConfigManager::GetInstance()->GetSkillCombatMageFile()));
    SkillTreeCombat::GetInstance()->AddBranch(IndexedString("Rogue"), IndexedString(ConfigManager::GetInstance()->GetSkillCombatRogueFile()));
    SkillTreeCombat::GetInstance()->AddBranch(IndexedString("Stalwart"), IndexedString(ConfigManager::GetInstance()->GetSkillCombatStalwartFile()));

    // Crafting
    SkillTreeCrafting::GetInstance()->AddBranch(IndexedString("Bowsmith"), IndexedString(ConfigManager::GetInstance()->GetSkillCraftingBowsmithFile()));
    SkillTreeCrafting::GetInstance()->AddBranch(IndexedString("Goldsmith"), IndexedString(ConfigManager::GetInstance()->GetSkillCraftingGoldsmithFile()));
    SkillTreeCrafting::GetInstance()->AddBranch(IndexedString("Hammersmith"), IndexedString(ConfigManager::GetInstance()->GetSkillCraftingHammersmithFile()));
    SkillTreeCrafting::GetInstance()->AddBranch(IndexedString("Platesmith"), IndexedString(ConfigManager::GetInstance()->GetSkillCraftingPlatesmithFile()));
    SkillTreeCrafting::GetInstance()->AddBranch(IndexedString("Scalesmith"), IndexedString(ConfigManager::GetInstance()->GetSkillCraftingScalesmithFile()));
    SkillTreeCrafting::GetInstance()->AddBranch(IndexedString("Shieldsmith"), IndexedString(ConfigManager::GetInstance()->GetSkillCraftingShieldsmithFile()));
    SkillTreeCrafting::GetInstance()->AddBranch(IndexedString("Spellsmith"), IndexedString(ConfigManager::GetInstance()->GetSkillCraftingSpellsmithFile()));
    SkillTreeCrafting::GetInstance()->AddBranch(IndexedString("Swordsmith"), IndexedString(ConfigManager::GetInstance()->GetSkillCraftingSwordsmithFile()));
    SkillTreeCrafting::GetInstance()->AddBranch(IndexedString("Tanner"), IndexedString(ConfigManager::GetInstance()->GetSkillCraftingTannerFile()));
    SkillTreeCrafting::GetInstance()->AddBranch(IndexedString("Weaver"), IndexedString(ConfigManager::GetInstance()->GetSkillCraftingWeaverFile()));

    // Weapon
    SkillTreeWeapon::GetInstance()->AddBranch(IndexedString("Bash"), IndexedString(ConfigManager::GetInstance()->GetSkillWeaponBashFile()));
    SkillTreeWeapon::GetInstance()->AddBranch(IndexedString("Block"), IndexedString(ConfigManager::GetInstance()->GetSkillWeaponBlockFile()));
    SkillTreeWeapon::GetInstance()->AddBranch(IndexedString("Break"), IndexedString(ConfigManager::GetInstance()->GetSkillWeaponBreakFile()));
    SkillTreeWeapon::GetInstance()->AddBranch(IndexedString("Cleave"), IndexedString(ConfigManager::GetInstance()->GetSkillWeaponCleaveFile()));
    SkillTreeWeapon::GetInstance()->AddBranch(IndexedString("Counter"), IndexedString(ConfigManager::GetInstance()->GetSkillWeaponCounterFile()));
    SkillTreeWeapon::GetInstance()->AddBranch(IndexedString("Crack"), IndexedString(ConfigManager::GetInstance()->GetSkillWeaponCrackFile()));
    SkillTreeWeapon::GetInstance()->AddBranch(IndexedString("CriticalShot"), IndexedString(ConfigManager::GetInstance()->GetSkillWeaponCriticalShotFile()));
    SkillTreeWeapon::GetInstance()->AddBranch(IndexedString("Crush"), IndexedString(ConfigManager::GetInstance()->GetSkillWeaponCrushFile()));
    SkillTreeWeapon::GetInstance()->AddBranch(IndexedString("Decapitate"), IndexedString(ConfigManager::GetInstance()->GetSkillWeaponDecapitateFile()));
    SkillTreeWeapon::GetInstance()->AddBranch(IndexedString("Dodge"), IndexedString(ConfigManager::GetInstance()->GetSkillWeaponDodgeFile()));
    SkillTreeWeapon::GetInstance()->AddBranch(IndexedString("Drill"), IndexedString(ConfigManager::GetInstance()->GetSkillWeaponDrillFile()));
    SkillTreeWeapon::GetInstance()->AddBranch(IndexedString("Impact"), IndexedString(ConfigManager::GetInstance()->GetSkillWeaponImpactFile()));
    SkillTreeWeapon::GetInstance()->AddBranch(IndexedString("Impale"), IndexedString(ConfigManager::GetInstance()->GetSkillWeaponImpaleFile()));
    SkillTreeWeapon::GetInstance()->AddBranch(IndexedString("Parry"), IndexedString(ConfigManager::GetInstance()->GetSkillWeaponParryFile()));
    SkillTreeWeapon::GetInstance()->AddBranch(IndexedString("Pierce"), IndexedString(ConfigManager::GetInstance()->GetSkillWeaponPierceFile()));
    SkillTreeWeapon::GetInstance()->AddBranch(IndexedString("Riposte"), IndexedString(ConfigManager::GetInstance()->GetSkillWeaponRiposteFile()));
    SkillTreeWeapon::GetInstance()->AddBranch(IndexedString("Rush"), IndexedString(ConfigManager::GetInstance()->GetSkillWeaponRushFile()));
    SkillTreeWeapon::GetInstance()->AddBranch(IndexedString("Sever"), IndexedString(ConfigManager::GetInstance()->GetSkillWeaponSeverFile()));
    SkillTreeWeapon::GetInstance()->AddBranch(IndexedString("Shoot"), IndexedString(ConfigManager::GetInstance()->GetSkillWeaponShootFile()));
    SkillTreeWeapon::GetInstance()->AddBranch(IndexedString("Slash"), IndexedString(ConfigManager::GetInstance()->GetSkillWeaponSlashFile()));
    SkillTreeWeapon::GetInstance()->AddBranch(IndexedString("Slice"), IndexedString(ConfigManager::GetInstance()->GetSkillWeaponSliceFile()));
    SkillTreeWeapon::GetInstance()->AddBranch(IndexedString("Slit"), IndexedString(ConfigManager::GetInstance()->GetSkillWeaponSlitFile()));
    SkillTreeWeapon::GetInstance()->AddBranch(IndexedString("Smash"), IndexedString(ConfigManager::GetInstance()->GetSkillWeaponSmashFile()));
    SkillTreeWeapon::GetInstance()->AddBranch(IndexedString("StealthStrike"), IndexedString(ConfigManager::GetInstance()->GetSkillWeaponStealthStrikeFile()));

    // Post process skill data
    POSTPROCESS_SKILLS(Affinity);
    POSTPROCESS_SKILLS(Alchemy);
    POSTPROCESS_SKILLS(Breakdown);
    POSTPROCESS_SKILLS(Combat);
    POSTPROCESS_SKILLS(Crafting);
    POSTPROCESS_SKILLS(Weapon);
}

void UnloadSkillTreesFromMemory()
{
    // Clear all skill data
    SkillTreeAffinity::GetInstance()->ClearAllData();
    SkillTreeAlchemy::GetInstance()->ClearAllData();
    SkillTreeBreakdown::GetInstance()->ClearAllData();
    SkillTreeCombat::GetInstance()->ClearAllData();
    SkillTreeCrafting::GetInstance()->ClearAllData();
    SkillTreeWeapon::GetInstance()->ClearAllData();
}

#define VERIFY_APPLY_STATCHANGES(tree, character_target)                                                        \
{                                                                                                               \
    for(const TreeIndex& index : GetAll##tree##Skills())                                                        \
    {                                                                                                           \
        SkillData##tree& skillData = SkillTree##tree::GetInstance()->GetLeaf(index);                            \
        LOG_FORMAT_STATEMENT("Processing skill (SkillRank = '%d', "                                             \
                             "SkillTreeType = '%s', "                                                           \
                             "SkillType = '%s', "                                                               \
                             "SkillName = '%s', "                                                               \
                             "StatChanges = %zu)\n",                                                            \
            skillData.GetSkillRank(),                                                                           \
            #tree,                                                                                              \
            skillData.GetSkillType().c_str(),                                                                   \
            skillData.GetSkillName().c_str(),                                                                   \
            skillData.GetStatChanges().size());                                                                 \
        for(StatChange change : skillData.GetStatChanges())                                                     \
        {                                                                                                       \
            Bool bAll, bOne = false;                                                                            \
            change.SetSourceTargetType(character_target);                                                       \
            change.SetDestinationTargetType(character_target);                                                  \
            change.SetChanceToApply(1.0);                                                                       \
            CharacterManager::GetInstance()->ApplyStatChange(IndexedString("Base"), change, bAll, bOne, true);  \
        }                                                                                                       \
    }                                                                                                           \
}

void VerifySkillTrees()
{
    // Log start
    LOG_STATEMENT("Verifying skill trees...");

    // Load character generator
    CharacterGenerator generator;
    IndexedString sGeneratorFile(ConfigManager::GetInstance()->GetCharacterGeneratorStaticFile());
    Bool bLoadedGenerator = generator.FromFile(sGeneratorFile);
    ASSERT_ERROR(bLoadedGenerator, "Could not load generator file '%s'\n", sGeneratorFile.c_str());
    if(!bLoadedGenerator)
    {
        return;
    }

    // Generate a character and party
    const IndexedString sCharacterID("CharacterID");
    const IndexedString sCharacterPartyID("CharacterPartyID");
    const IndexedString sCharacterPartyType("Ally");
    CharacterManager::GetInstance()->GenerateCharacter(sCharacterID, generator);
    CharacterPartyManager::GetInstance()->CreateParty(sCharacterPartyID, sCharacterPartyType, true);
    CharacterPartyManager::GetInstance()->GetPartyByID(sCharacterPartyID).AddMember(sCharacterID);
    const IndexedString sCharacterTargetType = CharacterManager::GetInstance()->GetCharacter(sCharacterID).GetCharacterTargetType();

    // Apply all stat changes
    VERIFY_APPLY_STATCHANGES(Affinity, sCharacterTargetType);
    VERIFY_APPLY_STATCHANGES(Alchemy, sCharacterTargetType);
    VERIFY_APPLY_STATCHANGES(Breakdown, sCharacterTargetType);
    VERIFY_APPLY_STATCHANGES(Combat, sCharacterTargetType);
    VERIFY_APPLY_STATCHANGES(Crafting, sCharacterTargetType);
    VERIFY_APPLY_STATCHANGES(Weapon, sCharacterTargetType);

    // Cleanup
    CharacterPartyManager::GetInstance()->GetPartyByID(sCharacterPartyID).RemoveMember(sCharacterID);
    CharacterPartyManager::GetInstance()->UnloadParty(sCharacterPartyID);
    CharacterManager::GetInstance()->UnloadCharacter(sCharacterID);
}

Bool DoesSkillDataAffinityExist(const TreeIndex& index)
{
    return SkillTreeAffinity::GetInstance()->HasLeaf(index);
}

Bool DoesSkillDataAlchemyExist(const TreeIndex& index)
{
    return SkillTreeAlchemy::GetInstance()->HasLeaf(index);
}

Bool DoesSkillDataBreakdownExist(const TreeIndex& index)
{
    return SkillTreeBreakdown::GetInstance()->HasLeaf(index);
}

Bool DoesSkillDataCombatExist(const TreeIndex& index)
{
    return SkillTreeCombat::GetInstance()->HasLeaf(index);
}

Bool DoesSkillDataCraftingExist(const TreeIndex& index)
{
    return SkillTreeCrafting::GetInstance()->HasLeaf(index);
}

Bool DoesSkillDataWeaponExist(const TreeIndex& index)
{
    return SkillTreeWeapon::GetInstance()->HasLeaf(index);
}

const SkillDataAffinity& RetrieveSkillDataAffinity(const TreeIndex& index)
{
    return SkillTreeAffinity::GetInstance()->GetLeaf(index);
}

const SkillDataAlchemy& RetrieveSkillDataAlchemy(const TreeIndex& index)
{
    return SkillTreeAlchemy::GetInstance()->GetLeaf(index);
}

const SkillDataBreakdown& RetrieveSkillDataBreakdown(const TreeIndex& index)
{
    return SkillTreeBreakdown::GetInstance()->GetLeaf(index);
}

const SkillDataCombat& RetrieveSkillDataCombat(const TreeIndex& index)
{
    return SkillTreeCombat::GetInstance()->GetLeaf(index);
}

const SkillDataCrafting& RetrieveSkillDataCrafting(const TreeIndex& index)
{
    return SkillTreeCrafting::GetInstance()->GetLeaf(index);
}

const SkillDataWeapon& RetrieveSkillDataWeapon(const TreeIndex& index)
{
    return SkillTreeWeapon::GetInstance()->GetLeaf(index);
}

#define ADD_ALL_SKILL_LEAVES(tree, branch)                                      \
{                                                                               \
    IndexedString sBranchName(#branch);                                         \
    auto vLeaves = SkillTree##tree::GetInstance()->GetAllLeaves(sBranchName);   \
    vFinal.insert(vFinal.end(), vLeaves.begin(), vLeaves.end());                \
}

#define ADD_SKILL_LEAVES_PROGRESS(tree, branch)                                                                             \
{                                                                                                                           \
    IndexedString sBranchName(#branch);                                                                                     \
    IndexedString sRankBase("Rank");                                                                                        \
    Int iLeafNumber = character.Get##branch##Rank();                                                                        \
    auto vLeaves = SkillTree##tree::GetInstance()->GetLeavesUnderNumber(sBranchName, sRankBase, iLeafNumber, bUniqueOnly);  \
    vFinal.insert(vFinal.end(), vLeaves.begin(), vLeaves.end());                                                            \
}

TreeIndexList GetAllAffinitySkills()
{
    TreeIndexList vFinal;
    ADD_ALL_SKILL_LEAVES(Affinity, Holy);
    ADD_ALL_SKILL_LEAVES(Affinity, Fire);
    ADD_ALL_SKILL_LEAVES(Affinity, Ice);
    ADD_ALL_SKILL_LEAVES(Affinity, Shock);
    ADD_ALL_SKILL_LEAVES(Affinity, Dark);
    ADD_ALL_SKILL_LEAVES(Affinity, Light);
    ADD_ALL_SKILL_LEAVES(Affinity, Force);
    ADD_ALL_SKILL_LEAVES(Affinity, Mind);
    ADD_ALL_SKILL_LEAVES(Affinity, Earth);
    ADD_ALL_SKILL_LEAVES(Affinity, Blood);
    ADD_ALL_SKILL_LEAVES(Affinity, Flesh);
    ADD_ALL_SKILL_LEAVES(Affinity, Wind);
    return vFinal;
}

TreeIndexList GetAllAlchemySkills()
{
    TreeIndexList vFinal;
    ADD_ALL_SKILL_LEAVES(Alchemy, Alchemist);
    ADD_ALL_SKILL_LEAVES(Alchemy, Chemist);
    ADD_ALL_SKILL_LEAVES(Alchemy, Energist);
    ADD_ALL_SKILL_LEAVES(Alchemy, Healer);
    return vFinal;
}

TreeIndexList GetAllBreakdownSkills()
{
    TreeIndexList vFinal;
    ADD_ALL_SKILL_LEAVES(Breakdown, Bowbane);
    ADD_ALL_SKILL_LEAVES(Breakdown, Goldbane);
    ADD_ALL_SKILL_LEAVES(Breakdown, Hammerbane);
    ADD_ALL_SKILL_LEAVES(Breakdown, Platebane);
    ADD_ALL_SKILL_LEAVES(Breakdown, Scalebane);
    ADD_ALL_SKILL_LEAVES(Breakdown, Shieldbane);
    ADD_ALL_SKILL_LEAVES(Breakdown, Spellbane);
    ADD_ALL_SKILL_LEAVES(Breakdown, StudRemover);
    ADD_ALL_SKILL_LEAVES(Breakdown, Swordbane);
    ADD_ALL_SKILL_LEAVES(Breakdown, Threadbare);
    return vFinal;
}

TreeIndexList GetAllCombatSkills()
{
    TreeIndexList vFinal;
    ADD_ALL_SKILL_LEAVES(Combat, Ambidextrous);
    ADD_ALL_SKILL_LEAVES(Combat, Avatar);
    ADD_ALL_SKILL_LEAVES(Combat, Barbarian);
    ADD_ALL_SKILL_LEAVES(Combat, Blademaster);
    ADD_ALL_SKILL_LEAVES(Combat, Focused);
    ADD_ALL_SKILL_LEAVES(Combat, Mage);
    ADD_ALL_SKILL_LEAVES(Combat, Rogue);
    ADD_ALL_SKILL_LEAVES(Combat, Stalwart);
    return vFinal;
}

TreeIndexList GetAllCraftingSkills()
{
    TreeIndexList vFinal;
    ADD_ALL_SKILL_LEAVES(Crafting, Bowsmith);
    ADD_ALL_SKILL_LEAVES(Crafting, Goldsmith);
    ADD_ALL_SKILL_LEAVES(Crafting, Hammersmith);
    ADD_ALL_SKILL_LEAVES(Crafting, Platesmith);
    ADD_ALL_SKILL_LEAVES(Crafting, Scalesmith);
    ADD_ALL_SKILL_LEAVES(Crafting, Shieldsmith);
    ADD_ALL_SKILL_LEAVES(Crafting, Spellsmith);
    ADD_ALL_SKILL_LEAVES(Crafting, Swordsmith);
    ADD_ALL_SKILL_LEAVES(Crafting, Tanner);
    ADD_ALL_SKILL_LEAVES(Crafting, Weaver);
    return vFinal;
}

TreeIndexList GetAllWeaponSkills()
{
    TreeIndexList vFinal;
    ADD_ALL_SKILL_LEAVES(Weapon, Bash);
    ADD_ALL_SKILL_LEAVES(Weapon, Block);
    ADD_ALL_SKILL_LEAVES(Weapon, Break);
    ADD_ALL_SKILL_LEAVES(Weapon, Cleave);
    ADD_ALL_SKILL_LEAVES(Weapon, Counter);
    ADD_ALL_SKILL_LEAVES(Weapon, Crack);
    ADD_ALL_SKILL_LEAVES(Weapon, CriticalShot);
    ADD_ALL_SKILL_LEAVES(Weapon, Crush);
    ADD_ALL_SKILL_LEAVES(Weapon, Decapitate);
    ADD_ALL_SKILL_LEAVES(Weapon, Dodge);
    ADD_ALL_SKILL_LEAVES(Weapon, Drill);
    ADD_ALL_SKILL_LEAVES(Weapon, Impact);
    ADD_ALL_SKILL_LEAVES(Weapon, Impale);
    ADD_ALL_SKILL_LEAVES(Weapon, Parry);
    ADD_ALL_SKILL_LEAVES(Weapon, Pierce);
    ADD_ALL_SKILL_LEAVES(Weapon, Riposte);
    ADD_ALL_SKILL_LEAVES(Weapon, Rush);
    ADD_ALL_SKILL_LEAVES(Weapon, Sever);
    ADD_ALL_SKILL_LEAVES(Weapon, Shoot);
    ADD_ALL_SKILL_LEAVES(Weapon, Slash);
    ADD_ALL_SKILL_LEAVES(Weapon, Slice);
    ADD_ALL_SKILL_LEAVES(Weapon, Slit);
    ADD_ALL_SKILL_LEAVES(Weapon, Smash);
    ADD_ALL_SKILL_LEAVES(Weapon, StealthStrike);
    return vFinal;
}

TreeIndexList GetAffinitySkills(const IndexedString& sCharID, Bool bUniqueOnly /*= false*/)
{
    TreeIndexList vFinal;
    if(sCharID.IsValid())
    {
        const Character& character = CharacterManager::GetInstance()->GetCharacter(sCharID);
        ADD_SKILL_LEAVES_PROGRESS(Affinity, Holy);
        ADD_SKILL_LEAVES_PROGRESS(Affinity, Fire);
        ADD_SKILL_LEAVES_PROGRESS(Affinity, Ice);
        ADD_SKILL_LEAVES_PROGRESS(Affinity, Shock);
        ADD_SKILL_LEAVES_PROGRESS(Affinity, Dark);
        ADD_SKILL_LEAVES_PROGRESS(Affinity, Light);
        ADD_SKILL_LEAVES_PROGRESS(Affinity, Force);
        ADD_SKILL_LEAVES_PROGRESS(Affinity, Mind);
        ADD_SKILL_LEAVES_PROGRESS(Affinity, Earth);
        ADD_SKILL_LEAVES_PROGRESS(Affinity, Blood);
        ADD_SKILL_LEAVES_PROGRESS(Affinity, Flesh);
        ADD_SKILL_LEAVES_PROGRESS(Affinity, Wind);
    }
    return vFinal;
}

TreeIndexList GetAlchemySkills(const IndexedString& sCharID, Bool bUniqueOnly /*= false*/)
{
    TreeIndexList vFinal;
    if(sCharID.IsValid())
    {
        const Character& character = CharacterManager::GetInstance()->GetCharacter(sCharID);
        ADD_SKILL_LEAVES_PROGRESS(Alchemy, Alchemist);
        ADD_SKILL_LEAVES_PROGRESS(Alchemy, Chemist);
        ADD_SKILL_LEAVES_PROGRESS(Alchemy, Energist);
        ADD_SKILL_LEAVES_PROGRESS(Alchemy, Healer);
    }
    return vFinal;
}

TreeIndexList GetBreakdownSkills(const IndexedString& sCharID, Bool bUniqueOnly /*= false*/)
{
    TreeIndexList vFinal;
    if(sCharID.IsValid())
    {
        const Character& character = CharacterManager::GetInstance()->GetCharacter(sCharID);
        ADD_SKILL_LEAVES_PROGRESS(Breakdown, Bowbane);
        ADD_SKILL_LEAVES_PROGRESS(Breakdown, Goldbane);
        ADD_SKILL_LEAVES_PROGRESS(Breakdown, Hammerbane);
        ADD_SKILL_LEAVES_PROGRESS(Breakdown, Platebane);
        ADD_SKILL_LEAVES_PROGRESS(Breakdown, Scalebane);
        ADD_SKILL_LEAVES_PROGRESS(Breakdown, Shieldbane);
        ADD_SKILL_LEAVES_PROGRESS(Breakdown, Spellbane);
        ADD_SKILL_LEAVES_PROGRESS(Breakdown, StudRemover);
        ADD_SKILL_LEAVES_PROGRESS(Breakdown, Swordbane);
        ADD_SKILL_LEAVES_PROGRESS(Breakdown, Threadbare);
    }
    return vFinal;
}

TreeIndexList GetCombatSkills(const IndexedString& sCharID, Bool bUniqueOnly /*= false*/)
{
    TreeIndexList vFinal;
    if(sCharID.IsValid())
    {
        const Character& character = CharacterManager::GetInstance()->GetCharacter(sCharID);
        ADD_SKILL_LEAVES_PROGRESS(Combat, Ambidextrous);
        ADD_SKILL_LEAVES_PROGRESS(Combat, Avatar);
        ADD_SKILL_LEAVES_PROGRESS(Combat, Barbarian);
        ADD_SKILL_LEAVES_PROGRESS(Combat, Blademaster);
        ADD_SKILL_LEAVES_PROGRESS(Combat, Focused);
        ADD_SKILL_LEAVES_PROGRESS(Combat, Mage);
        ADD_SKILL_LEAVES_PROGRESS(Combat, Rogue);
        ADD_SKILL_LEAVES_PROGRESS(Combat, Stalwart);
    }
    return vFinal;
}

TreeIndexList GetCraftingSkills(const IndexedString& sCharID, Bool bUniqueOnly /*= false*/)
{
    TreeIndexList vFinal;
    if(sCharID.IsValid())
    {
        const Character& character = CharacterManager::GetInstance()->GetCharacter(sCharID);
        ADD_SKILL_LEAVES_PROGRESS(Crafting, Bowsmith);
        ADD_SKILL_LEAVES_PROGRESS(Crafting, Goldsmith);
        ADD_SKILL_LEAVES_PROGRESS(Crafting, Hammersmith);
        ADD_SKILL_LEAVES_PROGRESS(Crafting, Platesmith);
        ADD_SKILL_LEAVES_PROGRESS(Crafting, Scalesmith);
        ADD_SKILL_LEAVES_PROGRESS(Crafting, Shieldsmith);
        ADD_SKILL_LEAVES_PROGRESS(Crafting, Spellsmith);
        ADD_SKILL_LEAVES_PROGRESS(Crafting, Swordsmith);
        ADD_SKILL_LEAVES_PROGRESS(Crafting, Tanner);
        ADD_SKILL_LEAVES_PROGRESS(Crafting, Weaver);
    }
    return vFinal;
}

TreeIndexList GetWeaponSkills(const IndexedString& sCharID, Bool bUniqueOnly /*= false*/)
{
    TreeIndexList vFinal;
    if(sCharID.IsValid())
    {
        const Character& character = CharacterManager::GetInstance()->GetCharacter(sCharID);
        ADD_SKILL_LEAVES_PROGRESS(Weapon, Bash);
        ADD_SKILL_LEAVES_PROGRESS(Weapon, Block);
        ADD_SKILL_LEAVES_PROGRESS(Weapon, Break);
        ADD_SKILL_LEAVES_PROGRESS(Weapon, Cleave);
        ADD_SKILL_LEAVES_PROGRESS(Weapon, Counter);
        ADD_SKILL_LEAVES_PROGRESS(Weapon, Crack);
        ADD_SKILL_LEAVES_PROGRESS(Weapon, CriticalShot);
        ADD_SKILL_LEAVES_PROGRESS(Weapon, Crush);
        ADD_SKILL_LEAVES_PROGRESS(Weapon, Decapitate);
        ADD_SKILL_LEAVES_PROGRESS(Weapon, Dodge);
        ADD_SKILL_LEAVES_PROGRESS(Weapon, Drill);
        ADD_SKILL_LEAVES_PROGRESS(Weapon, Impact);
        ADD_SKILL_LEAVES_PROGRESS(Weapon, Impale);
        ADD_SKILL_LEAVES_PROGRESS(Weapon, Parry);
        ADD_SKILL_LEAVES_PROGRESS(Weapon, Pierce);
        ADD_SKILL_LEAVES_PROGRESS(Weapon, Riposte);
        ADD_SKILL_LEAVES_PROGRESS(Weapon, Rush);
        ADD_SKILL_LEAVES_PROGRESS(Weapon, Sever);
        ADD_SKILL_LEAVES_PROGRESS(Weapon, Shoot);
        ADD_SKILL_LEAVES_PROGRESS(Weapon, Slash);
        ADD_SKILL_LEAVES_PROGRESS(Weapon, Slice);
        ADD_SKILL_LEAVES_PROGRESS(Weapon, Slit);
        ADD_SKILL_LEAVES_PROGRESS(Weapon, Smash);
        ADD_SKILL_LEAVES_PROGRESS(Weapon, StealthStrike);
    }
    return vFinal;
}

IndexedString GetSkillType(const TreeIndex& index)
{
    if(DoesSkillDataAffinityExist(index))
    {
        return RetrieveSkillDataAffinity(index).GetSkillType();
    }
    else if(DoesSkillDataAlchemyExist(index))
    {
        return RetrieveSkillDataAlchemy(index).GetSkillType();
    }
    else if(DoesSkillDataBreakdownExist(index))
    {
        return RetrieveSkillDataBreakdown(index).GetSkillType();
    }
    else if(DoesSkillDataCombatExist(index))
    {
        return RetrieveSkillDataCombat(index).GetSkillType();
    }
    else if(DoesSkillDataCraftingExist(index))
    {
        return RetrieveSkillDataCrafting(index).GetSkillType();
    }
    else if(DoesSkillDataWeaponExist(index))
    {
        return RetrieveSkillDataWeapon(index).GetSkillType();
    }
    return IndexedString("None");
}

Bool IsBaseWeaponSkill(const TreeIndex& index)
{
    if(DoesSkillDataWeaponExist(index))
    {
        const SkillDataWeapon& skillData = RetrieveSkillDataWeapon(index);
        return (
            skillData.GetSkillCostAP() == 0 &&
            skillData.GetActionPoints() == 0 &&
            skillData.GetWeaponBaseType().IsValid() &&
            !skillData.GetWeaponBaseType().IsNone()
        );
    }
    return false;
}

Bool IsSkillActionable(const TreeIndex& index)
{
    if(DoesSkillDataCombatExist(index))
    {
        return RetrieveSkillDataCombat(index).IsActionable();
    }
    else if(DoesSkillDataWeaponExist(index))
    {
        return RetrieveSkillDataWeapon(index).IsActionable();
    }
    return false;
}

Bool GenerateSkillCharacterActions(const TreeIndex& index,
    const IndexedString& sCharacterID,
    const IndexedString& sWeaponSet,
    CharacterActionSharedPtrList& vActions)
{
    if(DoesSkillDataCombatExist(index))
    {
        const SkillDataCombat& skillData = RetrieveSkillDataCombat(index);
        if(skillData.IsActionable() && skillData.DoesMeetActionRequirements(sCharacterID, sWeaponSet))
        {
            CharacterActionSharedPtrList vNewActions = skillData.CreateCombatActions(sCharacterID, sWeaponSet);
            vActions.insert(vActions.end(), vNewActions.begin(), vNewActions.end());
            return true;
        }
    }
    else if(DoesSkillDataWeaponExist(index))
    {
        const SkillDataWeapon& skillData = RetrieveSkillDataWeapon(index);
        if(skillData.IsActionable() && skillData.DoesMeetActionRequirements(sCharacterID, sWeaponSet))
        {
            CharacterActionSharedPtrList vNewActions = skillData.CreateWeaponActions(sCharacterID, sWeaponSet);
            vActions.insert(vActions.end(), vNewActions.begin(), vNewActions.end());
            return true;
        }
    }
    return false;
}

void FillSkillStatChangeLists(const IndexedString& sCharID,
    TreeIndexList& vPassives,
    TreeIndexList& vActives,
    TreeIndexList& vActionables,
    Bool bUniqueOnly /*= false*/)
{
    // Get all skill datas
    TreeIndexList vSkillDataList;
    TreeIndexList vSkillDataAffinityList = GetAffinitySkills(sCharID, bUniqueOnly);
    TreeIndexList vSkillDataAlchemyList = GetAlchemySkills(sCharID, bUniqueOnly);
    TreeIndexList vSkillDataBreakdownList = GetBreakdownSkills(sCharID, bUniqueOnly);
    TreeIndexList vSkillDataCombatList = GetCombatSkills(sCharID, bUniqueOnly);
    TreeIndexList vSkillDataCraftingList = GetCraftingSkills(sCharID, bUniqueOnly);
    TreeIndexList vSkillDataWeaponList = GetWeaponSkills(sCharID, bUniqueOnly);
    vSkillDataList.insert(vSkillDataList.end(), vSkillDataAffinityList.begin(), vSkillDataAffinityList.end());
    vSkillDataList.insert(vSkillDataList.end(), vSkillDataAlchemyList.begin(), vSkillDataAlchemyList.end());
    vSkillDataList.insert(vSkillDataList.end(), vSkillDataBreakdownList.begin(), vSkillDataBreakdownList.end());
    vSkillDataList.insert(vSkillDataList.end(), vSkillDataCombatList.begin(), vSkillDataCombatList.end());
    vSkillDataList.insert(vSkillDataList.end(), vSkillDataCraftingList.begin(), vSkillDataCraftingList.end());
    vSkillDataList.insert(vSkillDataList.end(), vSkillDataWeaponList.begin(), vSkillDataWeaponList.end());

    // Use a set to make sure that we do not include duplicates
    STDUnorderedSet<IndexedString, IndexedStringHasher> tAlreadyUsed;

    // Split them into separate lists
    for(const TreeIndex& index : vSkillDataList)
    {
        IndexedString sIndexKey = index.GetTreeBranchLeafType();
        Bool bIsActionable = IsSkillActionable(index);
        Bool bIsBaseWeaponSkill = IsBaseWeaponSkill(index);
        Bool bIsAlreadyUsed = (tAlreadyUsed.count(sIndexKey) == 1);
        if(bIsActionable && !bIsBaseWeaponSkill && !bIsAlreadyUsed)
        {
            vActionables.push_back(index);
            tAlreadyUsed.insert(sIndexKey);
        }
        else if(!bIsActionable && !bIsBaseWeaponSkill && !bIsAlreadyUsed)
        {
            for(const StatChange& statChange : GetStatChangesFromSkillTreeIndex(index))
            {
                if(statChange.IsPassive())
                {
                    vPassives.push_back(index);
                    tAlreadyUsed.insert(sIndexKey);
                    break;
                }
                else if(statChange.IsActive())
                {
                    vActives.push_back(index);
                    tAlreadyUsed.insert(sIndexKey);
                    break;
                }
            }
        }
    }
}

};
