// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

#ifndef _GECKO_CHARACTER_H_
#define _GECKO_CHARACTER_H_

// Internal includes
#include "Character/CharacterTypes.h"
#include "CharacterAction/CharacterAction.h"
#include "CharacterData/CharacterActionData.h"
#include "CharacterData/CharacterBasicData.h"
#include "CharacterData/CharacterBattleData.h"
#include "CharacterData/CharacterProgressData.h"
#include "CharacterData/CharacterMediaData.h"
#include "CharacterData/CharacterSkillData.h"
#include "CharacterData/CharacterStatChangeData.h"
#include "CharacterParty/CharacterPartyEquippedItem.h"
#include "Utility/ResultManager.h"
#include "Items/ItemTree.h"
#include "Skills/SkillTree.h"

namespace Gecko
{

class Character
{
public:

    // Constructors
    Character();
    Character(const Json& jsonData);
    Character(const String& jsonString);

    // Clear all data
    void Clear();

    // Regenerate character data
    void RegenerateCharacterData(
        Bool bUpdateEquipmentRatings = true,
        Bool bUpdateAvailableChanges = true,
        Bool bUpdateAvailableActions = true,
        Bool bUpdateAvailableAP = true
    );

    // Get character ID
    String GetCharacterID() const;
    MAKE_MODULE_RESULT_VARIANT(GetCharacterID);

    // Get party ID
    String GetPartyID() const;
    MAKE_MODULE_RESULT_VARIANT(GetPartyID);

    // Get character target type
    String GetCharacterTargetType() const;
    MAKE_MODULE_RESULT_VARIANT(GetCharacterTargetType);

    // Get weapon set
    String GetWeaponSet() const;
    MAKE_MODULE_RESULT_VARIANT(GetWeaponSet);

    // Get equipped items
    CharacterPartyEquippedItemArray GetEquippedItems() const;
    MAKE_MODULE_RESULT_VARIANT(GetEquippedItems);

    // Get individual equipped items by type
    TreeIndex GetEquippedItemByType(const String& sEquipmentType) const;
    MAKE_MODULE_RESULT_VARIANT_A1(GetEquippedItemByType, const String&);

    // Get available actions
    const CharacterActionArray& GetAvailableActions() const;
    MAKE_MODULE_RESULT_VARIANT(GetAvailableActions);

    // Get passive changes
    const TreeIndexArray& GetPassiveChanges(const String& sTreeIndexType) const;
    MAKE_MODULE_RESULT_VARIANT_A1(GetPassiveChanges, const String&);

    // Get active changes
    const TreeIndexArray& GetActiveChanges(const String& sTreeIndexType) const;
    MAKE_MODULE_RESULT_VARIANT_A1(GetActiveChanges, const String&);

    // Get actionable changes
    const TreeIndexArray& GetActionableChanges(const String& sTreeIndexType) const;
    MAKE_MODULE_RESULT_VARIANT_A1(GetActionableChanges, const String&);

    // Get progress data segment
    const CharacterProgressData& GetProgressDataSegment(const String& sSegment) const;
    CharacterProgressData& GetProgressDataSegment(const String& sSegment);
    MAKE_MODULE_RESULT_VARIANT_A1(GetProgressDataSegment, const String&);

    // Get battle data segment
    const CharacterBattleData& GetBattleDataSegment(const String& sSegment) const;
    CharacterBattleData& GetBattleDataSegment(const String& sSegment);
    MAKE_MODULE_RESULT_VARIANT_A1(GetBattleDataSegment, const String&);

    // Get stat values
    template <class T>
    Bool GetStatValue(const String& sSegment, const String& sStat, T& varValue) const
    {
        const CharacterBasicData& basicData = GetBasicData();
        const CharacterSkillData& skillData = GetSkillData();
        const CharacterMediaData& mediaData = GetMediaData();
        const CharacterProgressData& progressData = GetProgressDataSegment(sSegment);
        const CharacterBattleData& battleData = GetBattleDataSegment(sSegment);
        return (basicData.GetStatValue(sStat, varValue) ||
                progressData.GetStatValue(sStat, varValue) ||
                battleData.GetStatValue(sStat, varValue) ||
                skillData.GetStatValue(sStat, varValue) ||
                mediaData.GetStatValue(sStat, varValue));
    }

    // Set stat values
    template <class T>
    Bool SetStatValue(const String& sSegment, const String& sStat, const T& varValue)
    {
        CharacterBasicData& basicData = GetBasicData();
        CharacterSkillData& skillData = GetSkillData();
        CharacterMediaData& mediaData = GetMediaData();
        CharacterProgressData& progressData = GetProgressDataSegment(sSegment);
        CharacterBattleData& battleData = GetBattleDataSegment(sSegment);
        return (basicData.SetStatValue(sStat, varValue) ||
                progressData.SetStatValue(sStat, varValue) ||
                battleData.SetStatValue(sStat, varValue) ||
                skillData.SetStatValue(sStat, varValue) ||
                mediaData.SetStatValue(sStat, varValue));
    }

    // Update equipment ratings
    // This pulls equipment and current attack/defense percents and fills
    // ratings for all equipment
    void UpdateEquipmentRatings();

    // Update available passive and active changes
    // This pulls all earned skills and equipped items and generates a list
    // of active and passive changes that can be applied
    void UpdateAvailableChanges();

    // Update available actions
    // This polls the list of active changes and creates a list of
    // character actions that can be used as the basis for selectable actions
    void UpdateAvailableActions();

    // Update available AP
    // This searches the skills for ones that give AP and updates each type
    void UpdateAvailableAP();

    // Apply passive changes
    // Copy base data into passive data and apply each passive stat change
    void ApplyPassiveChanges();

    // Apply active changes
    // Copy passive data into active data and apply each active stat change
    void ApplyActiveChanges(const CharacterAction& action);

    // Clear active changes
    void ClearActiveChanges();

    // Progress data
    MAKE_RAW_TYPE_ACCESSORS(ProgressData, CharacterProgressData);
    MAKE_RAW_TYPE_ACCESSORS(ProgressDataPassives, CharacterProgressData);
    MAKE_RAW_TYPE_ACCESSORS(ProgressDataActives, CharacterProgressData);
    MAKE_MODULE_RESULT_VARIANT(GetProgressData);
    MAKE_MODULE_RESULT_VARIANT(GetProgressDataPassives);
    MAKE_MODULE_RESULT_VARIANT(GetProgressDataActives);

    // Battle data
    MAKE_RAW_TYPE_ACCESSORS(BattleData, CharacterBattleData);
    MAKE_RAW_TYPE_ACCESSORS(BattleDataPassives, CharacterBattleData);
    MAKE_RAW_TYPE_ACCESSORS(BattleDataActives, CharacterBattleData);
    MAKE_MODULE_RESULT_VARIANT(GetBattleData);
    MAKE_MODULE_RESULT_VARIANT(GetBattleDataPassives);
    MAKE_MODULE_RESULT_VARIANT(GetBattleDataActives);

    // Basic data
    MAKE_RAW_TYPE_ACCESSORS(BasicData, CharacterBasicData);
    MAKE_MODULE_RESULT_VARIANT(GetBasicData);

    // Action data
    MAKE_RAW_TYPE_ACCESSORS(ActionData, CharacterActionData);
    MAKE_MODULE_RESULT_VARIANT(GetActionData);

    // Skill data
    MAKE_RAW_TYPE_ACCESSORS(SkillData, CharacterSkillData);
    MAKE_MODULE_RESULT_VARIANT(GetSkillData);

    // Stat change data
    MAKE_RAW_TYPE_ACCESSORS(StatChangeData, CharacterStatChangeData);
    MAKE_MODULE_RESULT_VARIANT(GetStatChangeData);

    // Media data
    MAKE_RAW_TYPE_ACCESSORS(MediaData, CharacterMediaData);
    MAKE_MODULE_RESULT_VARIANT(GetMediaData);

    // Comparisons
    Bool operator==(const Character& other) const;
    Bool operator!=(const Character& other) const;
};

// Typedef
MAKE_COMMON_TYPEDEFS(Character);

// JSON Converters
void to_json(Json& jsonData, const Character& obj);
void from_json(const Json& jsonData, Character& obj);

// Get saveable data
Json GetSaveableData(const Character& obj);

// Comparisons
Bool operator==(const Character& a, const Character& b);

};

#endif
