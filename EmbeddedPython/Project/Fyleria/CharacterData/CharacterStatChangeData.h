// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

#ifndef _GECKO_CHARACTER_STAT_CHANGE_DATA_H_
#define _GECKO_CHARACTER_STAT_CHANGE_DATA_H_

// Internal includes
#include "Character/CharacterTypes.h"
#include "Stats/ProlongedStatChange.h"
#include "Utility/TreeIndex.h"

namespace Gecko
{

class CharacterStatChangeData
{
public:

    // Types
    typedef STDUnorderedMap<String, ProlongedStatChange> ProlongedStatChangeMapType;

    // Constructors
    CharacterStatChangeData();
    CharacterStatChangeData(const Json& jsonData);

    // Destructor
    virtual ~CharacterStatChangeData();

    // Clear all data
    void Clear();

    // Update available passive, active, and actionable changes
    void UpdateAvailableChanges(const String& sCharacterID);

    // Get tree actives/passives
    const TreeIndexArray& GetPassiveChanges(const String& sTreeIndexType) const;
    const TreeIndexArray& GetActiveChanges(const String& sTreeIndexType) const;
    const TreeIndexArray& GetActionableChanges(const String& sTreeIndexType) const;

    // Add/remove prolonged stat changes
    void AddProlongedStatChange(const String& sKey, const ProlongedStatChange& change);
    Bool RemoveProlongedStatChange(const String& sKey);

    // Get prolonged stat change
    const ProlongedStatChange& GetProlongedStatChange(const String& sKey) const;
    ProlongedStatChange& GetProlongedStatChange(const String& sKey);

    // Get stat change entry lists from prolonged entries
    StatChangeEntryArray GetProlongedStatChangeEntries(Int iRound, Int iAttack, Int iDefend) const;

    // Determine if prolonged stat change exists
    Bool DoesProlongedStatChangeExist(const String& sKey) const;

    // Determine if prolonged change has fully expired
    Bool HasProlongedStatChangeExpired(const String& sKey, Int iRound, Int iAttack, Int iDefend) const;

    // Remove all expired prolonged stat changes
    void RemoveAllExpiredProlongedStatChanges(Int iRound, Int iAttack, Int iDefend);

    // Apply prolonged stat changes
    void ApplyProlongedStatChanges(const String& sCharacterID, const String& sSegment);

    // Passive data
    MAKE_RAW_TYPE_ACCESSORS(PassiveSkillDataArray, TreeIndexArray);
    MAKE_RAW_TYPE_ACCESSORS(PassiveItemDataArray, TreeIndexArray);

    // Active data
    MAKE_RAW_TYPE_ACCESSORS(ActiveSkillDataArray, TreeIndexArray);
    MAKE_RAW_TYPE_ACCESSORS(ActiveItemDataArray, TreeIndexArray);

    // Actionable data
    MAKE_RAW_TYPE_ACCESSORS(ActionableSkillDataArray, TreeIndexArray);
    MAKE_RAW_TYPE_ACCESSORS(ActionableItemDataArray, TreeIndexArray);

    // Prolonged stat changes
    MAKE_RAW_TYPE_ACCESSORS(ProlongedStatChanges, ProlongedStatChangeMapType);

    // Comparisons
    Bool operator==(const CharacterStatChangeData& other) const;
    Bool operator!=(const CharacterStatChangeData& other) const;

};

// Typedef
MAKE_COMMON_TYPEDEFS(CharacterStatChangeData);

// JSON Converters
void to_json(Json& jsonData, const CharacterStatChangeData& obj);
void from_json(const Json& jsonData, CharacterStatChangeData& obj);

};

#endif
