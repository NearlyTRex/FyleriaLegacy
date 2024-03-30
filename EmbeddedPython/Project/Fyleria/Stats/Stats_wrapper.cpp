// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

// Internal includes
#include "Stats/StatChange.h"
#include "Stats/StatChangeEntry.h"
#include "Stats/ProlongedStatChange.h"
#include "Stats/StatTypeHolder.h"
#include "Utility/Macros.h"
#include "Utility/Python.h"

PYBIND11_EMBEDDED_MODULE(GeckoStats, m)
{
    // ProlongedStatChange.h
    PyBindClass<Gecko::ProlongedStatChange>(m, "ProlongedStatChange")
        WRAPPING_ADD_CONSTRUCTOR_SIMPLE()
        WRAPPING_ADD_METHOD_SIMPLE(Clear, Gecko::ProlongedStatChange)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(StatChangeEntry, Gecko::ProlongedStatChange)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(Round, Gecko::ProlongedStatChange)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(Attack, Gecko::ProlongedStatChange)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(Defend, Gecko::ProlongedStatChange)
    ;
    PyBindVector<Gecko::ProlongedStatChangeArray>(m, "ProlongedStatChangeArray");

    // StatChange.h
    PyBindClass<Gecko::StatChange>(m, "StatChange")
        WRAPPING_ADD_CONSTRUCTOR_SIMPLE()
        WRAPPING_ADD_METHOD_SIMPLE(IsActive, Gecko::StatChange)
        WRAPPING_ADD_METHOD_SIMPLE(IsPassive, Gecko::StatChange)
        WRAPPING_ADD_METHOD_SIMPLE(DoesHaveActiveRequirements, Gecko::StatChange)
        WRAPPING_ADD_METHOD_SIMPLE(DoesHaveItemEquippedRequirements, Gecko::StatChange)
        WRAPPING_ADD_METHOD_SIMPLE(DoesHaveItemUsedRequirements, Gecko::StatChange)
        WRAPPING_ADD_METHOD_SIMPLE(DoesHaveAttackRequirements, Gecko::StatChange)
        WRAPPING_ADD_METHOD_SIMPLE(DoesHaveDefendRequirements, Gecko::StatChange)
        WRAPPING_ADD_METHOD_SIMPLE(DoesMeetItemEquippedRequirements, Gecko::StatChange)
        WRAPPING_ADD_METHOD_SIMPLE(DoesMeetItemUsedRequirements, Gecko::StatChange)
        WRAPPING_ADD_METHOD_OVERLOADED_CONST(DoesMeetAttackRequirements, Gecko::StatChange, const Gecko::StringArray&)
        WRAPPING_ADD_METHOD_OVERLOADED_CONST(DoesMeetAttackRequirements, Gecko::StatChange, const Gecko::StringArray&, const Gecko::StringArray&)
        WRAPPING_ADD_METHOD_OVERLOADED_CONST(DoesMeetDefendRequirements, Gecko::StatChange, const Gecko::StringArray&)
        WRAPPING_ADD_METHOD_OVERLOADED_CONST(DoesMeetDefendRequirements, Gecko::StatChange, const Gecko::StringArray&, const Gecko::StringArray&)
        WRAPPING_ADD_METHOD_SIMPLE(GetResolvedCharacterArrays, Gecko::StatChange)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(SkillTreeIndex, Gecko::StatChange)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(ItemTreeIndex, Gecko::StatChange)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(ChanceToApply, Gecko::StatChange)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(RoundAmount, Gecko::StatChange)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(AttackAmount, Gecko::StatChange)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(DefendAmount, Gecko::StatChange)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(RequiredItemEquippedTypesOR, Gecko::StatChange)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(RequiredItemEquippedTypesAND, Gecko::StatChange)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(RequiredItemUsedTypesOR, Gecko::StatChange)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(RequiredItemUsedTypesAND, Gecko::StatChange)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(RequiredAttackTypesOR, Gecko::StatChange)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(RequiredAttackTypesAND, Gecko::StatChange)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(RequiredDefendTypesOR, Gecko::StatChange)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(RequiredDefendTypesAND, Gecko::StatChange)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(RequiredPreviousAttackTypesOR, Gecko::StatChange)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(RequiredPreviousAttackTypesAND, Gecko::StatChange)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(RequiredPreviousDefendTypesOR, Gecko::StatChange)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(RequiredPreviousDefendTypesAND, Gecko::StatChange)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(RequiredEquippedWeaponCount, Gecko::StatChange)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(RequiredEquippedShieldCount, Gecko::StatChange)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(DestinationIsSource, Gecko::StatChange)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(SourceTargetType, Gecko::StatChange)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(DestinationTargetType, Gecko::StatChange)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(StatChangeEntries, Gecko::StatChange)
    ;
    PyBindVector<Gecko::StatChangeArray>(m, "StatChangeArray");

    // StatChangeEntry.h
    PyBindClass<Gecko::StatChangeEntry>(m, "StatChangeEntry")
        WRAPPING_ADD_CONSTRUCTOR_SIMPLE()
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(Round, Gecko::StatChangeEntry)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(Attack, Gecko::StatChangeEntry)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(Defend, Gecko::StatChangeEntry)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(DeltaFloat, Gecko::StatChangeEntry)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(DeltaInt, Gecko::StatChangeEntry)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(FullPercent, Gecko::StatChangeEntry)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(FullFloat, Gecko::StatChangeEntry)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(FullInt, Gecko::StatChangeEntry)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(FullBool, Gecko::StatChangeEntry)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(FullString, Gecko::StatChangeEntry)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(FullFloatArray, Gecko::StatChangeEntry)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(FullIntArray, Gecko::StatChangeEntry)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(FullBoolArray, Gecko::StatChangeEntry)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(FullStringArray, Gecko::StatChangeEntry)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(OperationType, Gecko::StatChangeEntry)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(SourceStatType, Gecko::StatChangeEntry)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(DestinationStatType, Gecko::StatChangeEntry)
    ;
    PyBindVector<Gecko::StatChangeEntryArray>(m, "StatChangeEntryArray");

    // StatChange.h
    WRAPPING_STANDALONE_METHOD_POLICY(GetStatChangesFromTreeIndex, Gecko, PyBindReturnCopy);
    WRAPPING_STANDALONE_METHOD_POLICY(GetStatChangesFromSkillTreeIndex, Gecko, PyBindReturnCopy);
    WRAPPING_STANDALONE_METHOD_POLICY(GetStatChangesFromItemTreeIndex, Gecko, PyBindReturnCopy);
}
