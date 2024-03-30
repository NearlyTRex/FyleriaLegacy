// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#include "Character/CharacterManager.h"
#include "Character/CharacterPartyManager.h"
#include "Character/CharacterTypes.h"
#include "Battle/BattleManager.h"

namespace Gecko
{

CharacterManager::CharacterManager()
    : Singleton<CharacterManager>()
    , m_tCharacters()
{
}

void CharacterManager::LoadCharacter(const IndexedString& sCharacterID, const Character& character)
{
    // Load a character
    ASSERT_ERROR(!character.GetCharacterID().empty(), "Invalid character ID '%s'", character.GetCharacterID().c_str());
    ASSERT_ERROR(IsValidCharacterTargetType(character.GetCharacterTargetType()), "Character target type '%s' was not valid", character.GetCharacterTargetType().c_str());
    m_tCharacters[character.GetCharacterID()] = character;
    m_tCharacters[character.GetCharacterID()].SetCharacterID(sCharacterID);
}

void CharacterManager::LoadCharacterFromFile(const IndexedString& sCharacterID, const IndexedString& sFilename, const IndexedString& sType)
{
    // Load a character
    Json jsonData;
    Bool bSuccess = ReadSerializedFile(sFilename, sType, jsonData);
    ASSERT_ERROR(bSuccess, "Unable to read file '%s' as type '%s'", sFilename.c_str(), sType.c_str());
    LoadCharacter(sCharacterID, jsonData.get<Character>());
}

void CharacterManager::SaveCharacterToFile(const IndexedString& sCharacterID, const IndexedString& sFilename, const IndexedString& sType)
{
    // Save a character
    Json jsonData = GetCharacter(sCharacterID);
    Bool bSuccess = WriteSerializedFile(sFilename, sType, jsonData);
    ASSERT_ERROR(bSuccess, "Unable to write file '%s' as type '%s'", sFilename.c_str(), sType.c_str());
}

void CharacterManager::CreateCharacter(const IndexedString& sCharacterID)
{
    // Create a new character
    ASSERT_ERROR(!DoesCharacterExist(sCharacterID), "Character with ID '%s' was already registered", sCharacterID.c_str());
    Character newCharacter;
    newCharacter.SetCharacterID(sCharacterID);
    newCharacter.SetProgressDataBase(CharacterGenerator::CreateEmptyProgressData());
    newCharacter.SetBattleDataBase(CharacterGenerator::CreateEmptyBattleData());
    m_tCharacters.insert({sCharacterID, newCharacter});
}

void CharacterManager::UnloadCharacter(const IndexedString& sCharacterID)
{
    // Unload character
    ASSERT_ERROR(DoesCharacterExist(sCharacterID), "Character with ID '%s' was not registered", sCharacterID.c_str());
    m_tCharacters.erase(sCharacterID);
}

Bool CharacterManager::DoesCharacterExist(const IndexedString& sCharacterID) const
{
    // Check if party exists
    auto iSearch = m_tCharacters.find(sCharacterID);
    return (iSearch != m_tCharacters.end());
}

void CharacterManager::GenerateCharacter(const IndexedString& sCharacterID, const CharacterGenerator& generator)
{
    // Log start
    LOG_FORMAT_STATEMENT("Generating character (CharacterID = '%s') ...\n", sCharacterID.c_str());

    // Check generator
    ASSERT_ERROR(!generator.IsEmpty(), "Generator is empty, it should have some data set to it. Check that it loaded properly.");
    if(generator.IsEmpty())
    {
        return;
    }

    // Make sure that this character does not already exist
    ASSERT_ERROR(!DoesCharacterExist(sCharacterID), "Character with ID '%s' was already registered", sCharacterID.c_str());

    // Create a new character
    CreateCharacter(sCharacterID);
    Character& newCharacter = GetCharacter(sCharacterID);
    newCharacter.SetFirstName(generator.GenerateFirstName());
    newCharacter.SetLastName(generator.GenerateLastName());
    newCharacter.SetAge(generator.GenerateAge());
    newCharacter.SetGender(generator.GenerateGender());
    newCharacter.SetHair(generator.GenerateHair());
    newCharacter.SetEyes(generator.GenerateEyes());
    newCharacter.SetHandedness(generator.GenerateHandedness());
    newCharacter.SetBaseRace(generator.GenerateBaseRace());
    newCharacter.SetTransformedRace(generator.GenerateTransformedRace());
    newCharacter.SetPowerSet(generator.GeneratePowerSet());
    newCharacter.SetProgressDataBase(generator.GenerateProgressData());

    // Display the new character
#ifdef DEBUG
    Json jsonData = newCharacter;
    String sJsonString = jsonData.dump(4);
    LOG_FORMAT_STATEMENT("Completed generating character (CharacterID = '%s'):\n%s\n",
        sCharacterID.c_str(),
        sJsonString.c_str());
#endif
}

Character& CharacterManager::GetCharacter(const IndexedString& sCharacterID)
{
    // Get character
    ASSERT_ERROR(DoesCharacterExist(sCharacterID), "Character with ID '%s' was not registered", sCharacterID.c_str());
    return m_tCharacters[sCharacterID];
}

const Character& CharacterManager::GetCharacter(const IndexedString& sCharacterID) const
{
    // Get character
    ASSERT_ERROR(DoesCharacterExist(sCharacterID), "Character with ID '%s' was not registered", sCharacterID.c_str());
    auto iSearch = m_tCharacters.find(sCharacterID);
    return iSearch->second;
}

void CharacterManager::ApplyStatChange(const IndexedString& sSegment, const StatChange& change, Bool& bAllChangesApplied, Bool& bAtLeastOneChange, Bool bApplyAllEntries /*= false*/)
{
    // Skip invalid changes
    const TreeIndex& skillIndex = change.GetSkillTreeIndex();
    const TreeIndex& itemIndex = change.GetItemTreeIndex();
    if((skillIndex.empty() && itemIndex.empty()) ||
       change.GetStatChangeEntries().empty())
    {
        LOG_FORMAT_STATEMENT("Skipping stat change (Skill = '%s', "
                             "Item = '%s', "
                             "StatChangeEntries = %zu)\n",
            skillIndex.GetTreeBranchLeafType().c_str(),
            itemIndex.GetTreeBranchLeafType().c_str(),
            change.GetStatChangeEntries().size());
        return;
    }

    // Get character IDs
    IndexedStringList vSourceCharIDs;
    IndexedStringList vDestCharIDs;
    if(!change.GetResolvedCharacterLists(vSourceCharIDs, vDestCharIDs))
    {
        LOG_FORMAT_STATEMENT("Invalid character IDs (Skill = '%s', "
                             "Item = '%s', "
                             "StatChangeEntries = %zu)\n",
            skillIndex.GetTreeBranchLeafType().c_str(),
            itemIndex.GetTreeBranchLeafType().c_str(),
            change.GetStatChangeEntries().size());
        return;
    }

    // Get tree index info
    const TreeIndex& treeIndex = (!skillIndex.empty()) ? skillIndex : itemIndex;
    LOG_FORMAT_STATEMENT("Applying stat change (Tree = '%s', "
                         "Branch = '%s', "
                         "Leaf = '%s', "
                         "StatChangeEntries = %zu, "
                         "IsSkill = %d, "
                         "IsItem = %d)\n",
        treeIndex.GetTree().c_str(),
        treeIndex.GetBranch().c_str(),
        treeIndex.GetLeaf().c_str(),
        change.GetStatChangeEntries().size(),
        (!skillIndex.empty()),
        (!itemIndex.empty()));

    // Apply each change entry
    bAllChangesApplied = (change.GetStatChangeEntries().empty()) ? false : true;
    bAtLeastOneChange = false;
    for(const StatChangeEntry& entry : change.GetStatChangeEntries())
    {
        // Check stat change targets
        Bool bDoesUseDelta = DoesStatChangeEntryUseDelta(entry);
        ASSERT_WARNING(bDoesUseDelta || !change.GetDestinationTargetType().empty(),
            "Stat change (tree = '%s', type = '%s', skill = '%s') is missing a valid source/dest target set",
            treeIndex.GetTree().c_str(),
            treeIndex.GetBranch().c_str(),
            treeIndex.GetLeaf().c_str());
        if(!bDoesUseDelta && change.GetDestinationTargetType().empty())
        {
            continue;
        }

        // Check operation type
        IndexedString sOperation = entry.GetOperationType();
        ASSERT_WARNING(!sOperation.empty(),
            "Stat change (tree = '%s', type = '%s', skill = '%s') is missing a valid operation type",
            treeIndex.GetTree().c_str(),
            treeIndex.GetBranch().c_str(),
            treeIndex.GetLeaf().c_str());
        if(sOperation.empty())
        {
            continue;
        }

        // Check chance of application first
        if(change.GetChanceToApply() != 0 && !STDDoesChanceSucceed<Float>(change.GetChanceToApply()))
        {
            continue;
        }

        // Get source character ID
        // This normally should be just one character as the source of the value
        // Otherwise, we could have a many-to-many relationship which is harder to resolve
        IndexedString sSourceCharID("");
        if(bDoesUseDelta)
        {
            sSourceCharID = (vSourceCharIDs.size() >= 1) ? vSourceCharIDs.front() : IndexedString("");
        }
        else
        {
            sSourceCharID = (vDestCharIDs.size() >= 1) ? vDestCharIDs.front() : IndexedString("");
        }

        // Check that source character ID can resolve
        if(!DoesCharacterExist(sSourceCharID))
        {
            continue;
        }

        // Save character IDs to
        // Make copy of stat change entry and save character data
        StatChangeEntry localEntry(entry);
        localEntry.SetSourceCharacterID(sSourceCharID);
        localEntry.SetDestinationCharacterIDs(vDestCharIDs);

        // This is where you want to determine if it is a prolonged entry
        // Create a prolonged stat change entry object and fill in the relevant start/end data
        if(!bApplyAllEntries && (localEntry.GetRound() > 1 || localEntry.GetAttack() > 1 || localEntry.GetDefend() > 1))
        {
            // Get character
            Character& character = CharacterManager::GetInstance()->GetCharacter(sSourceCharID);

            // Create prolonged stat change
            ProlongedStatChange prolongedStatChange;
            prolongedStatChange.SetStatChangeEntry(localEntry);
            if(localEntry.GetRound() > 1)
            {
                prolongedStatChange.SetRound(BattleManager::GetInstance()->GetCurrentBattle().GetCurrentRoundIndex() + localEntry.GetRound());
            }
            else if(localEntry.GetAttack() > 1)
            {
                prolongedStatChange.SetAttack(character.GetAttackCounter() + localEntry.GetAttack());
            }
            else if(localEntry.GetDefend() > 1)
            {
                prolongedStatChange.SetDefend(character.GetDefendCounter() + localEntry.GetDefend());
            }

            // Add prolonged entry
            character.AddProlongedStatChange(treeIndex.GetTreeBranchLeafType(), prolongedStatChange);
        }
        else
        {
            // Process entry now
            Bool bSuccessful = ApplyStatChangeEntry(sSegment, localEntry);
            bAllChangesApplied = bAllChangesApplied && bSuccessful;
            bAtLeastOneChange = bAtLeastOneChange || bSuccessful;
        }
    }
}

Bool CharacterManager::ApplyStatChangeEntry(const IndexedString& sSegment, const StatChangeEntry& entry)
{
    // Determine if we are doing a delta change
    Bool bDoesUseDelta = DoesStatChangeEntryUseDelta(entry);

    // Get source values
    // If they are using delta values, then we pull from one character a stat and give it to another
    // They could be the same character, but completely different values
    // Otherwise, we assume the destination character is where we are pulling a value from
    IndexedString sSourceStatType = entry.GetSourceStatType();
    IndexedString sDestStatType = entry.GetDestinationStatType();
    FloatList vSourceFloatValues;
    IntList vSourceIntValues;
    BoolList vSourceBoolValues;
    IndexedStringList vSourceStringValues;
    if(bDoesUseDelta)
    {
        if(!GetSourceStatChangeEntryValues(sSegment, entry.GetSourceCharacterID(), sSourceStatType, entry,
            vSourceFloatValues,
            vSourceIntValues,
            vSourceBoolValues,
            vSourceStringValues))
        {
            return false;
        }
    }
    else
    {
        if(!GetDestStatChangeEntryValues(sSegment, entry.GetSourceCharacterID(), sDestStatType, entry,
            vSourceFloatValues,
            vSourceIntValues,
            vSourceBoolValues,
            vSourceStringValues))
        {
            return false;
        }
    }

    // Loop through destination characters
    // We are going to try to apply this change to all of them
    Bool bAtLeastOneChange = false;
    IndexedString sOperation = entry.GetOperationType();
    for(const IndexedString& sCharID : entry.GetDestinationCharacterIDs())
    {
        // Float value in a Float stat
        if(vSourceFloatValues.size() == 1 && IsStatFloat(sDestStatType))
        {
            bAtLeastOneChange = bAtLeastOneChange || ApplyStatChangeEntryOperation(sSegment, sCharID, sOperation, sDestStatType, vSourceFloatValues[0]);
        }

        // Float value in an Int stat
        else if(vSourceFloatValues.size() == 1 && IsStatInt(sDestStatType))
        {
            bAtLeastOneChange = bAtLeastOneChange || ApplyStatChangeEntryOperation(sSegment, sCharID, sOperation, sDestStatType, static_cast<Int>(STDRound(vSourceFloatValues[0])));
        }

        // Int value in an Int stat
        else if(vSourceIntValues.size() == 1 && IsStatInt(sDestStatType))
        {
            bAtLeastOneChange = bAtLeastOneChange || ApplyStatChangeEntryOperation(sSegment, sCharID, sOperation, sDestStatType, vSourceIntValues[0]);
        }

        // Int value in a Float stat
        else if(vSourceIntValues.size() == 1 && IsStatFloat(sDestStatType))
        {
            bAtLeastOneChange = bAtLeastOneChange || ApplyStatChangeEntryOperation(sSegment, sCharID, sOperation, sDestStatType, static_cast<Float>(vSourceIntValues[0]));
        }

        // Int value in a Bool stat
        else if(vSourceIntValues.size() == 1 && IsStatBool(sDestStatType))
        {
            bAtLeastOneChange = bAtLeastOneChange || ApplyStatChangeEntryOperation(sSegment, sCharID, sOperation, sDestStatType, static_cast<Bool>(vSourceIntValues[0]));
        }

        // Bool value in a Bool stat
        else if(vSourceBoolValues.size() == 1 && IsStatBool(sDestStatType))
        {
            bAtLeastOneChange = bAtLeastOneChange || ApplyStatChangeEntryOperation(sSegment, sCharID, sOperation, sDestStatType, vSourceBoolValues[0]);
        }

        // String value in a String stat
        else if(vSourceStringValues.size() == 1 && IsStatString(sDestStatType))
        {
            bAtLeastOneChange = bAtLeastOneChange || ApplyStatChangeEntryOperation(sSegment, sCharID, sOperation, sDestStatType, vSourceStringValues[0]);
        }

        // StringList value in a StringList stat
        else if(vSourceStringValues.size() > 1 && IsStatStringList(sDestStatType))
        {
            bAtLeastOneChange = bAtLeastOneChange || ApplyStatChangeEntryOperation(sSegment, sCharID, sOperation, sDestStatType, vSourceStringValues);
        }
    }
    return bAtLeastOneChange;
}

Bool CharacterManager::ApplyStatChangeEntryOperation(const IndexedString& sSegment, const IndexedString& sCharacterID, const IndexedString& sOperation, const IndexedString& sStat, Float fValue)
{
    // Get character
    Character& character = GetCharacter(sCharacterID);

    // Get existing value
    Float fStatValue = 0;
    if(!character.GetFloatStatValue(sSegment, sStat, fStatValue))
    {
        return false;
    }

    // Apply new value
    const OperationType eOperationType = StringToOperationType(sOperation);
    switch(eOperationType)
    {
        case OperationType::Add:
            LOG_FORMAT_STATEMENT("-- Adding %f to %s's current value of %f in character '%s'\n",
                fValue,
                sStat.c_str(),
                fStatValue,
                sCharacterID.c_str());
            return character.SetFloatStatValue(sSegment, sStat, fStatValue + fValue);
        case OperationType::Subtract:
            LOG_FORMAT_STATEMENT("-- Subtracting %f from %s's current value of %f in character '%s'\n",
                fValue,
                sStat.c_str(),
                fStatValue,
                sCharacterID.c_str());
            return character.SetFloatStatValue(sSegment, sStat, fStatValue - fValue);
        case OperationType::Multiply:
            LOG_FORMAT_STATEMENT("-- Multiplying %f against %s's current value of %f in character '%s'\n",
                fValue,
                sStat.c_str(),
                fStatValue,
                sCharacterID.c_str());
            return character.SetFloatStatValue(sSegment, sStat, fStatValue * fValue);
        case OperationType::Divide:
            if(fValue != 0)
            {
                LOG_FORMAT_STATEMENT("-- Dividing %s's current value of %f by %f in character '%s'\n",
                    sStat.c_str(),
                    fStatValue,
                    fValue,
                    sCharacterID.c_str());
                return character.SetFloatStatValue(sSegment, sStat, fStatValue / fValue);
            }
        case OperationType::Modulus:
            if(fValue != 0)
            {
                LOG_FORMAT_STATEMENT("-- Modulusing %s's current value of %f by %f in character '%s'\n",
                    sStat.c_str(),
                    fStatValue,
                    fValue,
                    sCharacterID.c_str());
                return character.SetFloatStatValue(sSegment, sStat, STDFmod(fStatValue, fValue));
            }
        case OperationType::Set:
            LOG_FORMAT_STATEMENT("-- Setting %f to %s in character '%s'\n",
                fValue,
                sStat.c_str(),
                sCharacterID.c_str());
            return character.SetFloatStatValue(sSegment, sStat, fValue);
        default:
            break;
    }
    return false;
}

Bool CharacterManager::ApplyStatChangeEntryOperation(const IndexedString& sSegment, const IndexedString& sCharacterID, const IndexedString& sOperation, const IndexedString& sStat, Int iValue)
{
    // Get character
    Character& character = GetCharacter(sCharacterID);

    // Get existing value
    Int iStatValue = 0;
    if(!character.GetIntStatValue(sSegment, sStat, iStatValue))
    {
        return false;
    }

    // Apply new value
    const OperationType eOperationType = StringToOperationType(sOperation);
    switch(eOperationType)
    {
        case OperationType::Add:
            LOG_FORMAT_STATEMENT("-- Adding %i to %s's current value of %i in character '%s'\n",
                iValue,
                sStat.c_str(),
                iStatValue,
                sCharacterID.c_str());
            return character.SetIntStatValue(sSegment, sStat, iStatValue + iValue);
        case OperationType::Subtract:
            LOG_FORMAT_STATEMENT("-- Subtracting %i from %s's current value of %i in character '%s'\n",
                iValue,
                sStat.c_str(),
                iStatValue,
                sCharacterID.c_str());
            return character.SetIntStatValue(sSegment, sStat, iStatValue - iValue);
        case OperationType::Multiply:
            LOG_FORMAT_STATEMENT("-- Multiplying %i against %s's current value of %i in character '%s'\n",
                iValue,
                sStat.c_str(),
                iStatValue,
                sCharacterID.c_str());
            return character.SetIntStatValue(sSegment, sStat, iStatValue * iValue);
        case OperationType::Divide:
            if(iValue != 0)
            {
                LOG_FORMAT_STATEMENT("-- Dividing %s's current value of %i by %i in character '%s'\n",
                    sStat.c_str(),
                    iStatValue,
                    iValue,
                    sCharacterID.c_str());
                return character.SetIntStatValue(sSegment, sStat, iStatValue / iValue);
            }
        case OperationType::Modulus:
            if(iValue != 0)
            {
                LOG_FORMAT_STATEMENT("-- Modulusing %s's current value of %i by %i in character '%s'\n",
                    sStat.c_str(),
                    iStatValue,
                    iValue,
                    sCharacterID.c_str());
                return character.SetIntStatValue(sSegment, sStat, iStatValue % iValue);
            }
        case OperationType::Set:
            LOG_FORMAT_STATEMENT("-- Setting %i to %s stat in character '%s'\n",
                iValue,
                sStat.c_str(),
                sCharacterID.c_str());
            return character.SetIntStatValue(sSegment, sStat, iValue);
        default:
            break;
    }
    return false;
}

Bool CharacterManager::ApplyStatChangeEntryOperation(const IndexedString& sSegment, const IndexedString& sCharacterID, const IndexedString& sOperation, const IndexedString& sStat, Bool bValue)
{
    // Get character
    Character& character = GetCharacter(sCharacterID);

    // Apply new value
    const OperationType eOperationType = StringToOperationType(sOperation);
    switch(eOperationType)
    {
        case OperationType::Set:
            LOG_FORMAT_STATEMENT("-- Setting %d to %s stat in character '%s'\n",
                bValue,
                sStat.c_str(),
                sCharacterID.c_str());
            return character.SetBoolStatValue(sSegment, sStat, bValue);
        default:
            break;
    }
    return false;
}

Bool CharacterManager::ApplyStatChangeEntryOperation(const IndexedString& sSegment, const IndexedString& sCharacterID, const IndexedString& sOperation, const IndexedString& sStat, const IndexedString& sValue)
{
    // Get character
    Character& character = GetCharacter(sCharacterID);

    // Get existing value
    IndexedString sStatValue("");
    if(!character.GetStringStatValue(sSegment, sStat, sStatValue))
    {
        return false;
    }

    // Apply new value
    const OperationType eOperationType = StringToOperationType(sOperation);
    switch(eOperationType)
    {
        case OperationType::Add:
            LOG_FORMAT_STATEMENT("-- Adding %s to %s's current value of %s in character '%s'\n",
                sValue.c_str(),
                sStat.c_str(),
                sStatValue.c_str(),
                sCharacterID.c_str());
            return character.SetStringStatValue(sSegment, sStat, sStatValue + sValue);
        case OperationType::Set:
            LOG_FORMAT_STATEMENT("-- Setting %s to %s stat in character '%s'\n",
                sValue.c_str(),
                sStat.c_str(),
                sCharacterID.c_str());
            return character.SetStringStatValue(sSegment, sStat, sValue);
        default:
            break;
    }
    return false;
}

Bool CharacterManager::ApplyStatChangeEntryOperation(const IndexedString& sSegment, const IndexedString& sCharacterID, const IndexedString& sOperation, const IndexedString& sStat, const IndexedStringList& vValues)
{
    // Get character
    Character& character = GetCharacter(sCharacterID);

    // Apply new value
    const OperationType eOperationType = StringToOperationType(sOperation);
    switch(eOperationType)
    {
        case OperationType::Set:
        {
#ifdef DEBUG
            String sValue = "";
            for(UInt i = 0; i < vValues.size(); i++)
            {
                sValue += (vValues[i].Get() + String(","));
            }
            LOG_FORMAT_STATEMENT("-- Setting (%s) to %s stat in character '%s'\n",
                sValue.c_str(),
                sStat.c_str(),
                sCharacterID.c_str());
#endif
            return character.SetStringListStatValue(sSegment, sStat, vValues);
        }
        default:
            break;
    }
    return false;
}

Bool CharacterManager::DoesStatChangeEntryUseDelta(const StatChangeEntry& changeEntry) const
{
    // Delta values need a percent or an integer amount
    return (changeEntry.GetDeltaPercent() != 0 ||
            changeEntry.GetDeltaInt() != 0 ||
            changeEntry.GetDeltaFloat() != 0 ||
            changeEntry.GetDeltaBool() != 0 ||
            !changeEntry.GetDeltaString().empty() ||
            !changeEntry.GetDeltaFloatList().empty() ||
            !changeEntry.GetDeltaIntList().empty() ||
            !changeEntry.GetDeltaBoolList().empty() ||
            !changeEntry.GetDeltaStringList().empty());
}

Bool CharacterManager::IsStatFloat(const IndexedString& sStat) const
{
    const STDUnorderedSet<String>& tBattle_Floats = CharacterBattleData::GetFloatStatNames();
    return (
        tBattle_Floats.find(sStat.Get()) != tBattle_Floats.end()
    );
}

Bool CharacterManager::IsStatInt(const IndexedString& sStat) const
{
    const STDUnorderedSet<String>& tBattle_UBytes = CharacterBattleData::GetUByteStatNames();
    const STDUnorderedSet<String>& tBattle_Ints = CharacterBattleData::GetIntStatNames();
    const STDUnorderedSet<String>& tProgress_UBytes = CharacterProgressData::GetUByteStatNames();
    const STDUnorderedSet<String>& tProgress_UShorts = CharacterProgressData::GetUShortStatNames();
    const STDUnorderedSet<String>& tProgress_Shorts = CharacterProgressData::GetShortStatNames();
    return (
        tBattle_UBytes.find(sStat.Get()) != tBattle_UBytes.end() ||
        tBattle_Ints.find(sStat.Get()) != tBattle_Ints.end() ||
        tProgress_UBytes.find(sStat.Get()) != tProgress_UBytes.end() ||
        tProgress_UShorts.find(sStat.Get()) != tProgress_UShorts.end() ||
        tProgress_Shorts.find(sStat.Get()) != tProgress_Shorts.end()
    );
}

Bool CharacterManager::IsStatBool(const IndexedString& sStat) const
{
    const STDUnorderedSet<String>& tBattle_Bools = CharacterBattleData::GetBoolStatNames();
    return (
        tBattle_Bools.find(sStat.Get()) != tBattle_Bools.end()
    );
}

Bool CharacterManager::IsStatString(const IndexedString& sStat) const
{
    const STDUnorderedSet<String>& tBattle_IndexedStrings = CharacterBattleData::GetIndexedStringStatNames();
    return (
        tBattle_IndexedStrings.find(sStat.Get()) != tBattle_IndexedStrings.end()
    );
}

Bool CharacterManager::IsStatStringList(const IndexedString& sStat) const
{
    const STDUnorderedSet<String>& tBattle_IndexedStringLists = CharacterBattleData::GetIndexedStringListStatNames();
    return (
        tBattle_IndexedStringLists.find(sStat.Get()) != tBattle_IndexedStringLists.end()
    );
}

Bool CharacterManager::GetSourceStatChangeEntryValues(const IndexedString& sSegment, const IndexedString& sCharacterID, const IndexedString& sStat, const StatChangeEntry& changeEntry,
    FloatList& vFloatValues,
    IntList& vIntValues,
    BoolList& vBoolValues,
    IndexedStringList& vStringValues) const
{
    // Get source character
    const Character& sourceChar = GetCharacter(sCharacterID);

    // Get source value
    Bool bSuccess = false;
    if(changeEntry.GetDeltaPercent() != 0)
    {
        Float fStatValue = 0;
        Int iStatValue = 0;
        if(sourceChar.GetFloatStatValue(sSegment, sStat, fStatValue))
        {
            Float fNewValue = changeEntry.GetDeltaPercent() * fStatValue;
            LOG_FORMAT_STATEMENT("-- Getting %s value of %f from character '%s' and multiplying by delta percent of %f to get float value %f\n",
                sStat.c_str(),
                fStatValue,
                sCharacterID.c_str(),
                changeEntry.GetDeltaPercent(),
                fNewValue);
            vFloatValues.push_back(fNewValue);
            bSuccess = true;
        }
        else if(sourceChar.GetIntStatValue(sSegment, sStat, iStatValue))
        {
            Float fNewValue = changeEntry.GetDeltaPercent() * (Float)iStatValue;
            LOG_FORMAT_STATEMENT("-- Getting %s value of %i from character '%s' and multiplying by delta percent of %f to get float value %f\n",
                sStat.c_str(),
                iStatValue,
                sCharacterID.c_str(),
                changeEntry.GetDeltaPercent(),
                fNewValue);
            vFloatValues.push_back(fNewValue);
            bSuccess = true;
        }
    }
    else if(changeEntry.GetDeltaFloat() != 0)
    {
        Float fStatValue = 0;
        if(sourceChar.GetFloatStatValue(sSegment, sStat, fStatValue))
        {
            Float fNewValue = fStatValue + changeEntry.GetDeltaFloat();
            LOG_FORMAT_STATEMENT("-- Getting %s value of %f from character '%s' and adding delta float of %f to get float value %f\n",
                sStat.c_str(),
                fStatValue,
                sCharacterID.c_str(),
                changeEntry.GetDeltaFloat(),
                fNewValue);
            vFloatValues.push_back(fNewValue);
            bSuccess = true;
        }
    }
    else if(changeEntry.GetDeltaInt() != 0)
    {
        Int iStatValue = 0;
        if(sourceChar.GetIntStatValue(sSegment, sStat, iStatValue))
        {
            Int iNewValue = iStatValue + changeEntry.GetDeltaInt();
            LOG_FORMAT_STATEMENT("-- Getting %s value of %i from character '%s' and adding delta int of %i to get int value %i\n",
                sStat.c_str(),
                iStatValue,
                sCharacterID.c_str(),
                changeEntry.GetDeltaInt(),
                iNewValue);
            vIntValues.push_back(iNewValue);
            bSuccess = true;
        }
    }
    return bSuccess;
}

Bool CharacterManager::GetDestStatChangeEntryValues(const IndexedString& sSegment, const IndexedString& sCharacterID, const IndexedString& sStat, const StatChangeEntry& changeEntry,
    FloatList& vFloatValues,
    IntList& vIntValues,
    BoolList& vBoolValues,
    IndexedStringList& vStringValues) const
{
    // Get dest character
    const Character& destChar = GetCharacter(sCharacterID);

    // Get dest value
    Bool bSuccess = false;
    if(changeEntry.GetFullPercent() != 0)
    {
        Float fStatValue = 0;
        Int iStatValue = 0;
        if(destChar.GetFloatStatValue(sSegment, sStat, fStatValue))
        {
            Float fNewValue = changeEntry.GetFullPercent() * fStatValue;
            LOG_FORMAT_STATEMENT("-- Getting %s value of %f from character '%s' and multiplying by full percent of %f to get float value %f\n",
                sStat.c_str(),
                fStatValue,
                sCharacterID.c_str(),
                changeEntry.GetFullPercent(),
                fNewValue);
            vFloatValues.push_back(fNewValue);
            bSuccess = true;
        }
        else if(destChar.GetIntStatValue(sSegment, sStat, iStatValue))
        {
            Float fNewValue = changeEntry.GetFullPercent() * (Float)iStatValue;
            LOG_FORMAT_STATEMENT("-- Getting %s value of %i from character '%s' and multiplying by full percent of %f to get float value %f\n",
                sStat.c_str(),
                iStatValue,
                sCharacterID.c_str(),
                changeEntry.GetFullPercent(),
                fNewValue);
            vFloatValues.push_back(fNewValue);
            bSuccess = true;
        }
    }
    else if(changeEntry.GetFullFloat() != 0)
    {
        Float fNewValue = changeEntry.GetFullFloat();
        LOG_FORMAT_STATEMENT("-- Using full float value of %f directly\n", fNewValue);
        vFloatValues.push_back(fNewValue);
        bSuccess = true;
    }
    else if(changeEntry.GetFullInt() != 0)
    {
        Int iNewValue = changeEntry.GetFullInt();
        LOG_FORMAT_STATEMENT("-- Using full int value of %i directly\n", iNewValue);
        vIntValues.push_back(iNewValue);
        bSuccess = true;
    }
    else if(!changeEntry.GetFullString().empty())
    {
        IndexedString sNewValue = changeEntry.GetFullString();
        LOG_FORMAT_STATEMENT("-- Using full string value of %s directly\n", sNewValue.c_str());
        vStringValues.push_back(sNewValue);
        bSuccess = true;
    }
    else if(!changeEntry.GetFullStringList().empty())
    {
        IndexedStringList vNewValues = changeEntry.GetFullStringList();
#ifdef DEBUG
        String sNewValue = "";
        for(UInt i = 0; i < vNewValues.size(); i++)
        {
            sNewValue += (vNewValues[i].Get() + String(","));
        }
        LOG_FORMAT_STATEMENT("-- Using full string list value of %s directly\n", sNewValue.c_str());
#endif
        vStringValues = vNewValues;
        bSuccess = true;
    }
    return bSuccess;
}

};
