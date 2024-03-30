// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

#ifndef _GECKO_UTILITY_TREE_H_
#define _GECKO_UTILITY_TREE_H_

// Internal includes
#include "Utility/Assert.h"
#include "Utility/Logging.h"
#include "Utility/Singleton.h"
#include "Utility/Errors.h"
#include "Utility/Filesystem.h"
#include "Utility/TreeIndex.h"
#include "Utility/Serialization.h"

namespace Gecko
{

template <class T>
class Tree : public Singleton<Tree<T>>
{
public:

    // Constructors
    Tree()
        : m_tBranches()
    {
    }

    // Get tree type
    static String GetTreeType()
    {
        return T::GetTreeType();
    }

    // Clear all data
    void ClearAllData()
    {
        m_tBranches.clear();
    }

    // Add branch
    void AddBranch(const String& sBranchName, const String& sBranchFile)
    {
        // Log loading of JSON data
        LOG_FORMAT_STATEMENT("Loading JSON file '{}' into branch {}\n", sBranchFile.c_str(), sBranchName.c_str());

        // Check that the file exists first
        if(!DoesPathExist(sBranchFile.c_str()))
        {
            ERROR_FORMAT_STATEMENT("JSON file '{}' does not exist!\n", sBranchFile.c_str());
            return;
        }

        // Read json data
        Json jsonData;
        if(!ReadJsonFile(sBranchFile, jsonData))
        {
            ERROR_FORMAT_STATEMENT("Could not load data from '{}' as JSON\n", sBranchName.c_str());
        }

        // Add branches
        for(auto it = jsonData.begin(); it != jsonData.end(); it++)
        {
            AddLeaf(sBranchName, String(it.key()), T(it.value()));
        }
    }

    // Add leaf
    void AddLeaf(const String& sBranchName, const String& sLeafName, const T& data)
    {
        if(!sBranchName.empty() && !sLeafName.empty())
        {
            m_tBranches[sBranchName][sLeafName] = data;
        }
    }

    // Get leaf
    T& GetLeaf(const String& sBranchName, const String& sLeafName)
    {
        if(!HasLeaf(sBranchName, sLeafName))
        {
            THROW_RUNTIME_ERROR("Specified leaf '" + sLeafName + "' on branch '" + sBranchName + "' was not found");
        }
        return m_tBranches[sBranchName][sLeafName];
    }

    // Get leaf
    T& GetLeaf(const String& sLeafName)
    {
        String sBranchName = GetBranchFromLeaf(sLeafName);
        if(sBranchName.empty())
        {
            THROW_RUNTIME_ERROR("Specified leaf '" + sLeafName + "' was not found on any branches");
        }
        return GetLeaf(sBranchName, sLeafName);
    }

    // Get leaf
    T& GetLeaf(const TreeIndex& index)
    {
        return GetLeaf(index.GetBranch(), index.GetLeaf());
    }

    // Get numbered leaf
    T& GetNumberedLeaf(const String& sBranchName, const String& sLeafBase, Int iLeafNumber)
    {
        return GetLeaf(sBranchName, GetLeafNameFromNumber(sLeafBase, iLeafNumber));
    }

    // Get all leaves
    TreeIndexArray GetAllLeaves(const String& sBranchName)
    {
        // Check branch
        TreeIndexArray vLeaves;
        if(sBranchName.empty())
        {
            return vLeaves;
        }

        // Make sure branch exists
        if(!HasBranch(sBranchName))
        {
            THROW_RUNTIME_ERROR("Specified branch '" + sBranchName + "' was not found");
        }

        // Look at all the leaves
        for(LeafTypeIterator it = m_tBranches[sBranchName].begin(); it != m_tBranches[sBranchName].end(); it++)
        {
            // Add new leaf
            vLeaves.push_back(TreeIndex(GetTreeType(), sBranchName, it->first));
        }
        return vLeaves;
    }

    // Get all unique leaves under the given number
    TreeIndexArray GetLeavesUnderNumber(const String& sBranchName, const String& sLeafBase, Int iLeafNumber, Bool bUniqueOnly)
    {
        // Check branch
        TreeIndexArray vLeaves;
        if(sBranchName.empty())
        {
            return vLeaves;
        }

        // Look at each of the leaves at or below the given number
        StringArray vCheckedClasses;
        for(Int i = iLeafNumber; i >= 0; i--)
        {
            // Ignore invalid leaves
            if(!HasLeaf(sBranchName, sLeafBase, i))
            {
                continue;
            }

            // Only store unique leaves if they asked for that
            if(bUniqueOnly)
            {
                // Get leaf
                T& leaf = GetNumberedLeaf(sBranchName, sLeafBase, i);

                // Skip if we already have a matching class
                String sClass = leaf.GetSkillType() + String("_") + leaf.GetDataClass();
                auto iClassSearch = STDFindData(vCheckedClasses.begin(), vCheckedClasses.end(), sClass);
                if(iClassSearch != vCheckedClasses.end())
                {
                    continue;
                }

                // Store newly checked class
                vCheckedClasses.push_back(sClass);
            }

            // Add new leaf
            vLeaves.push_back(TreeIndex(GetTreeType(), sBranchName, GetLeafNameFromNumber(sLeafBase, i)));
        }
        return vLeaves;
    }

    // Check if a branch exists
    Bool HasBranch(const String& sBranchName)
    {
        return (m_tBranches.find(sBranchName) != m_tBranches.end());
    }

    // Check if a leaf exists
    Bool HasLeaf(const String& sBranchName, const String& sLeafName)
    {
        return (m_tBranches.find(sBranchName) != m_tBranches.end() &&
                m_tBranches[sBranchName].find(sLeafName) != m_tBranches[sBranchName].end());
    }

    // Check if a numbered leaf exists
    Bool HasLeaf(const String& sBranchName, const String& sLeafBase, Int iLeafNumber)
    {
        return HasLeaf(sBranchName, GetLeafNameFromNumber(sLeafBase, iLeafNumber));
    }

    // Check if a leaf exists
    Bool HasLeaf(const String& sLeafName)
    {
        return HasLeaf(GetBranchFromLeaf(sLeafName), sLeafName);
    }

    // Check if a leaf exists
    Bool HasLeaf(const TreeIndex& index)
    {
        return HasLeaf(index.GetBranch(), index.GetLeaf());
    }

    // Get branch name from leaf name
    String GetBranchFromLeaf(const String& sLeafName)
    {
        String sBranchName("");
        for(auto it = m_tBranches.begin(); it != m_tBranches.end(); ++it)
        {
            if(HasLeaf(it->first, sLeafName))
            {
                sBranchName = it->first;
                break;
            }
        }
        return sBranchName;
    }

    // Get leaf name from base and number
    String GetLeafNameFromNumber(const String& sLeafBase, Int iLeafNumber)
    {
        return sLeafBase + String(STDToString(iLeafNumber));
    }

private:

    // Deleted
    Tree(Tree const&) = delete;
    Tree& operator=(Tree const&) = delete;

    // Leaves
    typedef STDUnorderedMap<String, T> LeafType;
    typedef STDUnorderedMap<String, LeafType> BranchType;
    typedef typename LeafType::iterator LeafTypeIterator;
    typedef typename LeafType::const_iterator LeafTypeConstIterator;
    typedef STDPair<String, T> BranchNodeType;
    BranchType m_tBranches;
};

};

#endif
