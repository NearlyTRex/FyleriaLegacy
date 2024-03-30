// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#ifndef _GECKO_STAT_CHANGE_H_
#define _GECKO_STAT_CHANGE_H_

#include "Character/CharacterAction.h"
#include "Stats/StatChangeEntry.h"
#include "Utility/Macros.h"
#include "Utility/Tree.h"
#include "Utility/TypesEnum.h"
#include "Utility/TypesJson.h"
#include "Utility/Serializable.h"

namespace Gecko
{

// POD class for stat changes
class StatChange
{
public:

    // Constructors
    StatChange();
    StatChange(const Json& jsonData);

    // ID
    static UInt GenerateNewID();
    UInt GetID() const;

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
    Bool DoesMeetItemEquippedRequirements(const IndexedString& sCharacterID, const IndexedString& sWeaponSet) const;
    Bool DoesMeetItemUsedRequirements(const IndexedStringList& vActionItemTypes) const;
    Bool DoesMeetAttackRequirements(const IndexedStringList& vActionTypes) const;
    Bool DoesMeetAttackRequirements(const IndexedStringList& vActionTypes, const IndexedStringList& vPreviousActionTypes) const;
    Bool DoesMeetDefendRequirements(const IndexedStringList& vActionTypes) const;
    Bool DoesMeetDefendRequirements(const IndexedStringList& vActionTypes, const IndexedStringList& vPreviousActionTypes) const;

    // Get intersecting requirements
    IndexedStringList GetIntersectingAttackRequirements(const IndexedStringList& vActionTypes) const;
    IndexedStringList GetIntersectingDefendRequirements(const IndexedStringList& vActionTypes) const;

    // Get resolved characters
    Bool GetResolvedCharacterLists(IndexedStringList& vSourceCharIDs, IndexedStringList& vDestCharIDs) const;

    // Relevant skill data
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(SkillTreeIndex, TreeIndex);

    // Relevant item data
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(ItemTreeIndex, TreeIndex);

    // Percent chance to apply this change
    MAKE_RAW_BASIC_TYPE_ACCESSORS(ChanceToApply, Float);

    // Amount of rounds to apply this change (0 is indefinite)
    MAKE_RAW_BASIC_TYPE_ACCESSORS(RoundAmount, UByte);

    // Amount of attacks to apply this change (0 is indefinite)
    MAKE_RAW_BASIC_TYPE_ACCESSORS(AttackAmount, UByte);

    // Amount of defends to apply this change (0 is indefinite)
    MAKE_RAW_BASIC_TYPE_ACCESSORS(DefendAmount, UByte);

    // Required items or attack types
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(RequiredItemEquippedTypesOR, IndexedStringList);
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(RequiredItemEquippedTypesAND, IndexedStringList);
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(RequiredItemUsedTypesOR, IndexedStringList);
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(RequiredItemUsedTypesAND, IndexedStringList);
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(RequiredAttackTypesOR, IndexedStringList);
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(RequiredAttackTypesAND, IndexedStringList);
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(RequiredDefendTypesOR, IndexedStringList);
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(RequiredDefendTypesAND, IndexedStringList);
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(RequiredPreviousAttackTypesOR, IndexedStringList);
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(RequiredPreviousAttackTypesAND, IndexedStringList);
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(RequiredPreviousDefendTypesOR, IndexedStringList);
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(RequiredPreviousDefendTypesAND, IndexedStringList);
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(RequiredEquippedWeaponCount, UByte);
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(RequiredEquippedShieldCount, UByte);

    // Whether destination target is the same as the source target
    MAKE_RAW_BASIC_TYPE_ACCESSORS(DestinationIsSource, Bool);

    // Source and destination targets
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(SourceTargetType, IndexedString);
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(DestinationTargetType, IndexedString);

    // Stat change list
    MAKE_RAW_OBJECT_TYPE_ACCESSORS(StatChangeEntries, StatChangeEntryList);

    // Comparisons
    Bool operator==(const StatChange& other) const;
    Bool operator<(const StatChange& other) const;

private:

    // ID
    UInt m_uID;
};

// Typedefs
MAKE_TYPE_TYPEDEFS(StatChange);

// JSON Converters
void to_json(Json& jsonData, const StatChange& obj);
void from_json(const Json& jsonData, StatChange& obj);
MAKE_JSON_GENERIC_TYPE_CONVERTERS_DECL(StatChange, StatChange);

// JSON class for prolonged stat changes
class ProlongedStatChange : public SerializableToJson
{
public:
    // Constructors
    ProlongedStatChange();
    ProlongedStatChange(const Json& jsonData);

    // Relevant stat change
    MAKE_JSON_BASIC_TYPE_ACCESSORS(StatChangeEntry, StatChangeEntry);

    // Valid round
    MAKE_JSON_BASIC_TYPE_ACCESSORS(Round, Int);

    // Valid attack
    MAKE_JSON_BASIC_TYPE_ACCESSORS(Attack, Int);

    // Valid defend
    MAKE_JSON_BASIC_TYPE_ACCESSORS(Defend, Int);
};

// Typedefs
MAKE_TYPE_TYPEDEFS(ProlongedStatChange);

// JSON Converters
MAKE_JSON_BASIC_TYPE_CONVERTERS_DECL(ProlongedStatChange);
MAKE_JSON_GENERIC_TYPE_CONVERTERS_DECL(ProlongedStatChange, ProlongedStatChange);

// Get stat changes from the given tree nodes
const StatChangeList& GetStatChangesFromTreeIndex(const IndexedString& sTreeIndexType, const TreeIndex& index);
const StatChangeList& GetStatChangesFromSkillTreeIndex(const TreeIndex& index);
const StatChangeList& GetStatChangesFromItemTreeIndex(const TreeIndex& index);

};

#endif
