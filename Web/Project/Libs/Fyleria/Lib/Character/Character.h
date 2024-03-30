// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#ifndef _GECKO_CHARACTER_H_
#define _GECKO_CHARACTER_H_

#include "Character/CharacterAction.h"
#include "Character/CharacterProgressData.h"
#include "Character/CharacterBattleData.h"
#include "Character/CharacterTypes.h"
#include "Items/ItemTree.h"
#include "Skills/SkillTree.h"

namespace Gecko
{

class Character
{
public:

    // Types
    typedef UByte (Character::*CharacterSkillFunction_Get)() const;
    typedef void (Character::*CharacterSkillFunction_Set)(UByte);
    typedef STDUnorderedMap<IndexedString, ProlongedStatChange, IndexedStringHasher> ProlongedStatChangeMapType;
    typedef STDUnorderedMap<IndexedString, UInt, IndexedStringHasher> SkillUseTrackingMapType;

    // Constructors
    Character();
    ~Character();

    // Regenerate character data
    void RegenerateCharacterData(
        Bool bUpdateSkillRankings = true,
        Bool bUpdateEquipmentRatings = true,
        Bool bUpdateAvailableChanges = true,
        Bool bUpdateAvailableActions = true,
        Bool bUpdateAvailableAP = true
    );

    // Called when battle starts/ends/advances round
    void OnBattleStarted();
    void OnBattleEnded();
    void OnBattleTally();
    void OnBattleFullyCompleted();
    void OnBattleRoundAdvanced();

    // Called when giving/taking damage during battle
    void OnBattleGivingDamage(Int iAmount);
    void OnBattleTakingDamage(Int iAmount);

    // Called when choosing/becoming target during battle
    void OnBattleChoosingTargets(const IndexedStringList& vDestTargets);
    void OnBattleBecomingTarget(const IndexedString& sSourceTarget);

    // Called when battle action is initiated/received and finished
    void OnBattleActionAttackSetup(const CharacterActionSharedPtr& pAction);
    void OnBattleActionDefendSetup(const CharacterActionSharedPtr& pAction);
    void OnBattleActionApplied(const CharacterActionSharedPtr& pAction);
    void OnBattleActionFinished(const CharacterActionSharedPtr& pAction);

    // Segments
    STDSharedPtr<CharacterProgressData> GetProgressSegment(const IndexedString& sSegment);
    STDSharedPtr<const CharacterProgressData> GetProgressSegment(const IndexedString& sSegment) const;
    STDSharedPtr<CharacterBattleData> GetBattleSegment(const IndexedString& sSegment);
    STDSharedPtr<const CharacterBattleData> GetBattleSegment(const IndexedString& sSegment) const;

    // Stat values
    Bool GetBoolStatValue(const IndexedString& sSegment, const IndexedString& sStat, Bool& bValue) const;
    Bool GetIntStatValue(const IndexedString& sSegment, const IndexedString& sStat, Int& iValue) const;
    Bool GetFloatStatValue(const IndexedString& sSegment, const IndexedString& sStat, Float& fValue) const;
    Bool GetStringStatValue(const IndexedString& sSegment, const IndexedString& sStat, IndexedString& sValue) const;
    Bool GetStringListStatValue(const IndexedString& sSegment, const IndexedString& sStat, IndexedStringList& vValues) const;
    Bool SetBoolStatValue(const IndexedString& sSegment, const IndexedString& sStat, const Bool& bValue);
    Bool SetIntStatValue(const IndexedString& sSegment, const IndexedString& sStat, const Int& iValue);
    Bool SetFloatStatValue(const IndexedString& sSegment, const IndexedString& sStat, const Float& fValue);
    Bool SetStringStatValue(const IndexedString& sSegment, const IndexedString& sStat, const IndexedString& sValue);
    Bool SetStringListStatValue(const IndexedString& sSegment, const IndexedString& sStat, const IndexedStringList& vValues);

    // Resolve target placeholders
    IndexedStringList ResolveTargetPlaceholder(const IndexedString& sSegment, const IndexedString& sPlaceholderTargetType) const;
    void ResolveTargetPlaceholders(const IndexedString& sSegment, StatChange& change);

    // Get item counts
    UInt GetEquippedItemTypeCount(const TreeIndex& index) const;
    UInt GetEquippedWeaponCount(const IndexedString& sWeaponSet) const;
    UInt GetEquippedShieldCount(const IndexedString& sWeaponSet) const;

    // Check if an item can be added/removed
    Bool CanAddEquippedItem(const TreeIndex& index) const;
    Bool CanRemoveEquippedItem(const TreeIndex& index) const;

    // Add/remove equipped items
    Bool AddEquippedItem(const TreeIndex& index, const IndexedString& sEquipSlot);
    Bool RemoveEquippedItem(const TreeIndex& index, const IndexedString& sEquipSlot);

    // Get primary/secondary hand info
    Bool GetHandInfoByWeaponSet(const IndexedString& sWeaponSet,
        TreeIndex& primaryItemIndex,
        TreeIndex& secondaryItemIndex,
        IndexedStringList& vPrimaryActionTypes,
        IndexedStringList& vSecondaryActionTypes) const;

    // Add/remove prolonged stat changes
    void AddProlongedStatChange(const IndexedString& sKey, const ProlongedStatChange& change);
    Bool RemoveProlongedStatChange(const IndexedString& sKey);

    // Get prolonged stat change
    ProlongedStatChange& GetProlongedStatChange(const IndexedString& sKey);
    const ProlongedStatChange& GetProlongedStatChange(const IndexedString& sKey) const;

    // Get stat change entry lists from prolonged entries
    StatChangeEntryList GetProlongedStatChangeEntries() const;

    // Determine if prolonged stat change exists
    Bool DoesProlongedStatChangeExist(const IndexedString& sKey) const;

    // Determine if prolonged change has fully expired
    Bool HasProlongedStatChangeExpired(const IndexedString& sKey) const;

    // Remove all expired prolonged stat changes
    void RemoveAllExpiredProlongedStatChanges();

    // Add skill use
    void AddSkillUse(const IndexedString& sSkillType, UInt uNum);

    // Get number of skill uses
    UInt GetSkillUseCount(const IndexedString& sSkillType) const;

    // Set all skill data to a specific value
    void SetAllSkillCurrentValues(UByte uValue);
    void SetAllSkillRankingValues(UByte uValue);

    // Get tree actives/passives
    const TreeIndexList& GetPassiveChanges(const IndexedString& sTreeIndexType) const;
    const TreeIndexList& GetActiveChanges(const IndexedString& sTreeIndexType) const;
    const TreeIndexList& GetActionableChanges(const IndexedString& sTreeIndexType) const;

    // Basic character data
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(FirstName, IndexedString);
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(LastName, IndexedString);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(Age, Short);
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(Gender, IndexedString);
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(Hair, IndexedString);
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(Eyes, IndexedString);
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(Handedness, IndexedString);
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(BaseRace, IndexedString);
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(TransformedRace, IndexedString);
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(PowerSet, IndexedString);
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(EquippedItems, CharacterProgressItemList);
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(CurrentWeaponSet, IndexedString);

    // Combat Skills
    MAKE_RAW_BASIC_TYPE_ACCESSORS(BarbarianCurrent, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(BarbarianRank, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(MageCurrent, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(MageRank, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(RogueCurrent, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(RogueRank, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(BlademasterCurrent, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(BlademasterRank, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(AvatarCurrent, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(AvatarRank, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(AmbidextrousCurrent, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(AmbidextrousRank, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(FocusedCurrent, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(FocusedRank, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(StalwartCurrent, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(StalwartRank, UByte);

    // Weapon Skills
    MAKE_RAW_BASIC_TYPE_ACCESSORS(SlashCurrent, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(SlashRank, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(SeverCurrent, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(SeverRank, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(SliceCurrent, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(SliceRank, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(SlitCurrent, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(SlitRank, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(CleaveCurrent, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(CleaveRank, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(DecapitateCurrent, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(DecapitateRank, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(ParryCurrent, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(ParryRank, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(RiposteCurrent, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(RiposteRank, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(BashCurrent, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(BashRank, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(SmashCurrent, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(SmashRank, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(CrushCurrent, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(CrushRank, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(ImpactCurrent, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(ImpactRank, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(BreakCurrent, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(BreakRank, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(CrackCurrent, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(CrackRank, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(BlockCurrent, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(BlockRank, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(RushCurrent, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(RushRank, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(PierceCurrent, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(PierceRank, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(DrillCurrent, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(DrillRank, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(ShootCurrent, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(ShootRank, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(ImpaleCurrent, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(ImpaleRank, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(StealthStrikeCurrent, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(StealthStrikeRank, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(CriticalShotCurrent, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(CriticalShotRank, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(DodgeCurrent, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(DodgeRank, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(CounterCurrent, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(CounterRank, UByte);

    // Alchemy Skills
    MAKE_RAW_BASIC_TYPE_ACCESSORS(HealerCurrent, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(HealerRank, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(AlchemistCurrent, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(AlchemistRank, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(EnergistCurrent, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(EnergistRank, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(ChemistCurrent, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(ChemistRank, UByte);

    // Crafting Skills
    MAKE_RAW_BASIC_TYPE_ACCESSORS(HammersmithCurrent, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(HammersmithRank, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(SpellsmithCurrent, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(SpellsmithRank, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(BowsmithCurrent, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(BowsmithRank, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(SwordsmithCurrent, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(SwordsmithRank, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(WeaverCurrent, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(WeaverRank, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(TannerCurrent, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(TannerRank, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(ScalesmithCurrent, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(ScalesmithRank, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(PlatesmithCurrent, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(PlatesmithRank, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(GoldsmithCurrent, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(GoldsmithRank, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(ShieldsmithCurrent, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(ShieldsmithRank, UByte);

    // Breakdown Skills
    MAKE_RAW_BASIC_TYPE_ACCESSORS(HammerbaneCurrent, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(HammerbaneRank, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(SpellbaneCurrent, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(SpellbaneRank, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(BowbaneCurrent, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(BowbaneRank, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(SwordbaneCurrent, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(SwordbaneRank, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(ThreadbareCurrent, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(ThreadbareRank, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(StudRemoverCurrent, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(StudRemoverRank, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(ScalebaneCurrent, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(ScalebaneRank, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(PlatebaneCurrent, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(PlatebaneRank, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(GoldbaneCurrent, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(GoldbaneRank, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(ShieldbaneCurrent, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(ShieldbaneRank, UByte);

    // Affinity Skills
    MAKE_RAW_BASIC_TYPE_ACCESSORS(HolyCurrent, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(HolyRank, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(FireCurrent, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(FireRank, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(IceCurrent, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(IceRank, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(ShockCurrent, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(ShockRank, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(DarkCurrent, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(DarkRank, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(LightCurrent, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(LightRank, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(ForceCurrent, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(ForceRank, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(MindCurrent, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(MindRank, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(EarthCurrent, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(EarthRank, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(BloodCurrent, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(BloodRank, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(FleshCurrent, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(FleshRank, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(WindCurrent, UByte);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(WindRank, UByte);

    // Segmented progress data
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(ProgressDataBase, STDSharedPtr<CharacterProgressData>);
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(ProgressDataPassives, STDSharedPtr<CharacterProgressData>);
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(ProgressDataActives, STDSharedPtr<CharacterProgressData>);

    // Segmented battle data
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(BattleDataBase, STDSharedPtr<CharacterBattleData>);
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(BattleDataPassives, STDSharedPtr<CharacterBattleData>);
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(BattleDataActives, STDSharedPtr<CharacterBattleData>);

    // Previous action types
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(PreviousActionTypes, IndexedStringList);

    // List of passive/active/actionable data
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(PassiveSkillDataList, TreeIndexList);
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(ActiveSkillDataList, TreeIndexList);
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(ActionableSkillDataList, TreeIndexList);
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(PassiveItemDataList, TreeIndexList);
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(ActiveItemDataList, TreeIndexList);
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(ActionableItemDataList, TreeIndexList);

    // List of character actions
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(AvailableActions, CharacterActionSharedPtrList);

    // Prolonged stat changes
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(ProlongedStatChanges, ProlongedStatChangeMapType);

    // Skill use tracking
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(SkillUseTrackingMap, SkillUseTrackingMapType);

    // Attack/defend counters
    MAKE_RAW_BASIC_TYPE_ACCESSORS(AttackCounter, Int);
    MAKE_RAW_BASIC_TYPE_ACCESSORS(DefendCounter, Int);

    // Character ID
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(CharacterID, IndexedString);

    // Character target type
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(CharacterTargetType, IndexedString);

    // Comparisons
    Bool operator==(const Character& other) const;
    Bool operator!=(const Character& other) const;

private:

    // Character skill functions
    struct CharacterSkillFunctionNode
    {
        // Constructor
        CharacterSkillFunctionNode()
            : fnGetCurrent(nullptr)
            , fnGetRank(nullptr)
            , fnSetCurrent(nullptr)
            , fnSetRank(nullptr)
        {}

        // Check if pointers are valid
        Bool IsValid() const
        {
            return (
                fnGetCurrent != nullptr &&
                fnGetRank != nullptr &&
                fnSetCurrent != nullptr &&
                fnSetRank != nullptr
            );
        }

        // Accessors
        UByte GetCurrent(const Character& obj) const { return CALL_MEMBER_FN_PTR(obj, fnGetCurrent)(); }
        UByte GetRank(const Character& obj) const { return CALL_MEMBER_FN_PTR(obj, fnGetRank)(); }
        void SetCurrent(Character& obj, UByte uValue) { CALL_MEMBER_FN_PTR(obj, fnSetCurrent)(uValue); }
        void SetRank(Character& obj, UByte uValue) { CALL_MEMBER_FN_PTR(obj, fnSetRank)(uValue); }

        // Pointers
        CharacterSkillFunction_Get fnGetCurrent;
        CharacterSkillFunction_Get fnGetRank;
        CharacterSkillFunction_Set fnSetCurrent;
        CharacterSkillFunction_Set fnSetRank;
    };

    // Update equipment ratings
    // This pulls equipment and current attack/defense percents and fills
    // ratings for all equipment
    void UpdateEquipmentRatings(const IndexedString& sSegment);

    // Update available passive and active changes
    // This pulls all earned skills and equipped items and generates a list
    // of active and passive changes that can be applied
    void UpdateAvailableChanges(const IndexedString& sSegment);

    // Update available actions
    // This polls the list of active changes and creates a list of
    // character actions that can be used as the basis for selectable actions
    void UpdateAvailableActions(const IndexedString& sSegment);

    // Update available AP
    // This searches the skills for ones that give AP and updates each type
    void UpdateAvailableAP(const IndexedString& sSegment);

    // Update skill rankings
    // This searches through the skill uses and upgrades ranks if necessary
    void UpdateSkillRankings(const IndexedString& sSegment);

    // Get skill ranking/current functions
    CharacterSkillFunctionNode GetSkillFunctions(const IndexedString& sSkillType) const;

    // Determine if change meets requirements
    Bool DoesChangeMeetActiveRequirements(const StatChange& change) const;
    Bool DoesChangeMeetActiveRequirements(const StatChange& change, const CharacterActionSharedPtr& pAction) const;

    // Apply changes
    void ApplyPassiveChanges();
    void ApplyActiveChanges(const CharacterActionSharedPtr& pAction);
    void ClearActiveChanges();

    // Empty change list
    static const TreeIndexList s_vEmptyChanges;
};

// Typedef
MAKE_TYPE_TYPEDEFS(Character);

// JSON Converters
void to_json(Json& jsonData, const Character& obj);
void from_json(const Json& jsonData, Character& obj);
MAKE_JSON_GENERIC_TYPE_CONVERTERS_DECL(Character, Character);

// Comparisons
Bool operator==(const Character& a, const Character& b);

};

#endif
