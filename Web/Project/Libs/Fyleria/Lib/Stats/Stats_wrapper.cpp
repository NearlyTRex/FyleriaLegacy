// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#include "Stats/StatChange.h"
#include "Stats/StatChangeEntry.h"
#include "Utility/Macros.h"
#include "Utility/Serializable.h"
#include "Utility/TypesPython.h"

PYBIND11_EMBEDDED_MODULE(GeckoStats, m)
{
    // StatChange.h
    PyBindClass<Gecko::ProlongedStatChange, Gecko::SerializableToJson>(m, "ProlongedStatChange")
        WRAPPING_ADD_CONSTRUCTOR_SIMPLE()
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(StatChangeEntry, Gecko::ProlongedStatChange)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(Round, Gecko::ProlongedStatChange)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(Attack, Gecko::ProlongedStatChange)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(Defend, Gecko::ProlongedStatChange)
    ;
    PyBindVector<Gecko::ProlongedStatChangeList>(m, "ProlongedStatChangeList");
    WRAPPING_STANDALONE_METHOD_SIMPLE(ConvertProlongedStatChangeToJsonString, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(ConvertProlongedStatChangeListToJsonString, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetProlongedStatChangeFromJsonString, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetProlongedStatChangeListFromJsonString, Gecko);

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
        WRAPPING_ADD_METHOD_OVERLOADED_CONST(DoesMeetAttackRequirements, Gecko::StatChange, const Gecko::IndexedStringList&)
        WRAPPING_ADD_METHOD_OVERLOADED_CONST(DoesMeetAttackRequirements, Gecko::StatChange, const Gecko::IndexedStringList&, const Gecko::IndexedStringList&)
        WRAPPING_ADD_METHOD_OVERLOADED_CONST(DoesMeetDefendRequirements, Gecko::StatChange, const Gecko::IndexedStringList&)
        WRAPPING_ADD_METHOD_OVERLOADED_CONST(DoesMeetDefendRequirements, Gecko::StatChange, const Gecko::IndexedStringList&, const Gecko::IndexedStringList&)
        WRAPPING_ADD_METHOD_SIMPLE(GetResolvedCharacterLists, Gecko::StatChange)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(SkillTreeIndex, Gecko::StatChange)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(ItemTreeIndex, Gecko::StatChange)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(ChanceToApply, Gecko::StatChange)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(RoundAmount, Gecko::StatChange)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(AttackAmount, Gecko::StatChange)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(DefendAmount, Gecko::StatChange)
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
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(DestinationIsSource, Gecko::StatChange)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(SourceTargetType, Gecko::StatChange)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(DestinationTargetType, Gecko::StatChange)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(StatChangeEntries, Gecko::StatChange)
    ;
    PyBindVector<Gecko::StatChangeList>(m, "StatChangeList");
    WRAPPING_STANDALONE_METHOD_SIMPLE(ConvertStatChangeToJsonString, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(ConvertStatChangeListToJsonString, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetStatChangeFromJsonString, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetStatChangeListFromJsonString, Gecko);

    // StatChangeEntry.h
    PyBindClass<Gecko::StatChangeEntry>(m, "StatChangeEntry")
        WRAPPING_ADD_CONSTRUCTOR_SIMPLE()
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(Round, Gecko::StatChangeEntry)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(Attack, Gecko::StatChangeEntry)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(Defend, Gecko::StatChangeEntry)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(DeltaPercent, Gecko::StatChangeEntry)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(DeltaFloat, Gecko::StatChangeEntry)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(DeltaInt, Gecko::StatChangeEntry)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(DeltaBool, Gecko::StatChangeEntry)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(DeltaString, Gecko::StatChangeEntry)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(DeltaFloatList, Gecko::StatChangeEntry)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(DeltaIntList, Gecko::StatChangeEntry)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(DeltaBoolList, Gecko::StatChangeEntry)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(DeltaStringList, Gecko::StatChangeEntry)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(FullPercent, Gecko::StatChangeEntry)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(FullFloat, Gecko::StatChangeEntry)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(FullInt, Gecko::StatChangeEntry)
        WRAPPING_ADD_BASIC_PROPERTY_SIMPLE(FullBool, Gecko::StatChangeEntry)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(FullString, Gecko::StatChangeEntry)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(FullFloatList, Gecko::StatChangeEntry)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(FullIntList, Gecko::StatChangeEntry)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(FullBoolList, Gecko::StatChangeEntry)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(FullStringList, Gecko::StatChangeEntry)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(OperationType, Gecko::StatChangeEntry)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(SourceStatType, Gecko::StatChangeEntry)
        WRAPPING_ADD_BASIC_PROPERTY_MULTIGET(DestinationStatType, Gecko::StatChangeEntry)
    ;
    PyBindVector<Gecko::StatChangeEntryList>(m, "StatChangeEntryList");
    WRAPPING_STANDALONE_METHOD_SIMPLE(ConvertStatChangeEntryToJsonString, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(ConvertStatChangeEntryListToJsonString, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetStatChangeEntryFromJsonString, Gecko);
    WRAPPING_STANDALONE_METHOD_SIMPLE(GetStatChangeEntryListFromJsonString, Gecko);

    // StatChange.h
    WRAPPING_STANDALONE_METHOD_POLICY(GetStatChangesFromTreeIndex, Gecko, PyBindReturnCopy);
    WRAPPING_STANDALONE_METHOD_POLICY(GetStatChangesFromSkillTreeIndex, Gecko, PyBindReturnCopy);
    WRAPPING_STANDALONE_METHOD_POLICY(GetStatChangesFromItemTreeIndex, Gecko, PyBindReturnCopy);
}
