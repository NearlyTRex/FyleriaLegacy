// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

#ifndef _GECKO_STAT_CHANGE_H_
#define _GECKO_STAT_CHANGE_H_

// Internal includes
#include "CharacterAction/CharacterAction.h"
#include "Stats/StatChangeEntry.h"
#include "Utility/Macros.h"
#include "Utility/Tree.h"
#include "Utility/Enum.h"
#include "Utility/Json.h"

namespace Gecko
{

// Class for stat changes
class StatChange
{
public:

    // Constructors
    StatChange();
    StatChange(const Json& jsonData);

    // Destructor
    virtual ~StatChange();

    // Clear all data
    void Clear();

    // ID
    static ULongLong GenerateNewID();

    // Determine if change is passive, active, etc
    // Passive means that there are no requirements on costs/time/equipment, chances to run, or actions
    Bool IsActive() const;
    Bool IsPassive() const;
    Bool DoesHaveActiveRequirements() const;

    // Determine if change has specific requirements
    Bool DoesHaveItemEquippedRequirements() const;
    Bool DoesHaveItemUsedRequirements() const;
    Bool DoesHaveAttackRequirements() const;
    Bool DoesHaveDefendRequirements() const;

    // Determine if change meets specific requirements
    Bool DoesMeetItemEquippedRequirements(const String& sCharacterID, const String& sWeaponSet) const;
    Bool DoesMeetItemUsedRequirements(const StringArray& vActionItemTypes) const;
    Bool DoesMeetAttackRequirements(const StringArray& vActionTypes) const;
    Bool DoesMeetAttackRequirements(const StringArray& vActionTypes, const StringArray& vPreviousActionTypes) const;
    Bool DoesMeetDefendRequirements(const StringArray& vActionTypes) const;
    Bool DoesMeetDefendRequirements(const StringArray& vActionTypes, const StringArray& vPreviousActionTypes) const;
    Bool DoesMeetActiveRequirements(const String& sCharacterID, const String& sWeaponSet) const;
    Bool DoesMeetActiveRequirements(const String& sCharacterID, const String& sCharacterTargetType, const String& sWeaponSet, const CharacterAction& action) const;

    // Get intersecting requirements
    StringArray GetIntersectingAttackRequirements(const StringArray& vActionTypes) const;
    StringArray GetIntersectingDefendRequirements(const StringArray& vActionTypes) const;

    // Get resolved characters
    Bool GetResolvedCharacterArrays(StringArray& vSourceCharIDs, StringArray& vDestCharIDs) const;

    // Resolve target placeholders
    void ResolveTargetPlaceholders(const String& sCharacterID, const String& sSegment);

    // ID
    MAKE_RAW_TYPE_ACCESSORS(ID, ULongLong);

    // Relevant skill data
    MAKE_RAW_TYPE_ACCESSORS(SkillTreeIndex, TreeIndex);

    // Relevant item data
    MAKE_RAW_TYPE_ACCESSORS(ItemTreeIndex, TreeIndex);

    // Percent chance to apply this change
    MAKE_RAW_TYPE_ACCESSORS(ChanceToApply, Float);

    // Amount of rounds to apply this change (0 is indefinite)
    MAKE_RAW_TYPE_ACCESSORS(RoundAmount, UByte);

    // Amount of attacks to apply this change (0 is indefinite)
    MAKE_RAW_TYPE_ACCESSORS(AttackAmount, UByte);

    // Amount of defends to apply this change (0 is indefinite)
    MAKE_RAW_TYPE_ACCESSORS(DefendAmount, UByte);

    // Required items or attack types
    MAKE_RAW_TYPE_ACCESSORS(RequiredItemEquippedTypesOR, StringArray);
    MAKE_RAW_TYPE_ACCESSORS(RequiredItemEquippedTypesAND, StringArray);
    MAKE_RAW_TYPE_ACCESSORS(RequiredItemUsedTypesOR, StringArray);
    MAKE_RAW_TYPE_ACCESSORS(RequiredItemUsedTypesAND, StringArray);
    MAKE_RAW_TYPE_ACCESSORS(RequiredAttackTypesOR, StringArray);
    MAKE_RAW_TYPE_ACCESSORS(RequiredAttackTypesAND, StringArray);
    MAKE_RAW_TYPE_ACCESSORS(RequiredDefendTypesOR, StringArray);
    MAKE_RAW_TYPE_ACCESSORS(RequiredDefendTypesAND, StringArray);
    MAKE_RAW_TYPE_ACCESSORS(RequiredPreviousAttackTypesOR, StringArray);
    MAKE_RAW_TYPE_ACCESSORS(RequiredPreviousAttackTypesAND, StringArray);
    MAKE_RAW_TYPE_ACCESSORS(RequiredPreviousDefendTypesOR, StringArray);
    MAKE_RAW_TYPE_ACCESSORS(RequiredPreviousDefendTypesAND, StringArray);
    MAKE_RAW_TYPE_ACCESSORS(RequiredEquippedWeaponCount, UByte);
    MAKE_RAW_TYPE_ACCESSORS(RequiredEquippedShieldCount, UByte);

    // Whether destination target is the same as the source target
    MAKE_RAW_TYPE_ACCESSORS(DestinationIsSource, Bool);

    // Source and destination targets
    MAKE_RAW_TYPE_ACCESSORS(SourceTargetType, String);
    MAKE_RAW_TYPE_ACCESSORS(DestinationTargetType, String);

    // Stat change list
    MAKE_RAW_TYPE_ACCESSORS(StatChangeEntries, StatChangeEntryArray);

    // Comparisons
    Bool operator==(const StatChange& other) const;
    Bool operator<(const StatChange& other) const;
};

// Typedefs
MAKE_COMMON_TYPEDEFS(StatChange);

// JSON Converters
void to_json(Json& jsonData, const StatChange& obj);
void from_json(const Json& jsonData, StatChange& obj);

// Get stat changes from the given tree nodes
const StatChangeArray& GetStatChangesFromTreeIndex(const String& sTreeIndexType, const TreeIndex& treeIndex);
const StatChangeArray& GetStatChangesFromSkillTreeIndex(const TreeIndex& treeIndex);
const StatChangeArray& GetStatChangesFromItemTreeIndex(const TreeIndex& treeIndex);

};

#endif
