// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#ifndef _GECKO_TREE_H_
#define _GECKO_TREE_H_

#include "Utility/IndexedString.h"
#include "Utility/Assert.h"
#include "Utility/Logging.h"
#include "Utility/Serializable.h"
#include "Utility/Serialization.h"
#include "Utility/Singleton.h"
#include "Utility/TypesFilesystem.h"

namespace Gecko
{

class TreeIndex : public SerializableToJson
{
public:

    // Constructors
    TreeIndex();
    TreeIndex(const IndexedString& sTree, const IndexedString& sBranch, const IndexedString& sLeaf);
    explicit TreeIndex(const Json& jsonData);
    explicit TreeIndex(const String& jsonString);

    // Tree/branch/leaf name
    const IndexedString& GetTree() const;
    const IndexedString& GetBranch() const;
    const IndexedString& GetLeaf() const;
    void SetTree(const IndexedString& sName);
    void SetBranch(const IndexedString& sName);
    void SetLeaf(const IndexedString& sName);

    // Composite types
    IndexedString GetTreeBranchType() const;
    IndexedString GetTreeBranchLeafType() const;
    IndexedStringList GetTypes() const;

    // Compatibility
    Bool empty() const;

    // Comparisons
    Bool operator==(const TreeIndex& other) const;
    Bool operator!=(const TreeIndex& other) const;

private:

    // Branch/leaf name
    IndexedString m_sTreeName;
    IndexedString m_sBranchName;
    IndexedString m_sLeafName;
};
typedef STDVector<TreeIndex> TreeIndexList;
void to_json(Json& jsonData, const TreeIndex& obj);
void from_json(const Json& jsonData, TreeIndex& obj);
MAKE_JSON_GENERIC_TYPE_CONVERTERS_DECL(TreeIndex, TreeIndex);

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
    static IndexedString GetTreeType()
    {
        return T::GetTreeType();
    }

    // Clear all data
    void ClearAllData()
    {
        m_tBranches.clear();
    }

    // Add branch
    void AddBranch(const IndexedString& sBranchName, const IndexedString& sBranchFile)
    {
        // Log loading of JSON data
        LOG_FORMAT_STATEMENT("Loading JSON file '%s' into branch %s\n", sBranchFile.c_str(), sBranchName.c_str());

        // Check that the file exists first
        FilesystemPath branchPath(sBranchFile.c_str());
        if(!DoesFileExist(branchPath))
        {
            ERROR_FORMAT_STATEMENT("JSON file '%s' does not exist!\n", sBranchFile.c_str());
            return;
        }

        // Read json data
        Json jsonData;
        if(!ReadJsonFile(sBranchFile, jsonData))
        {
            ERROR_FORMAT_STATEMENT("Could not load data from '%s' as JSON\n", sBranchName.c_str());
        }

        // Add branches
        for(auto it = jsonData.begin(); it != jsonData.end(); it++)
        {
            AddLeaf(sBranchName, IndexedString(it.key()), T(it.value()));
        }
    }

    // Add leaf
    void AddLeaf(const IndexedString& sBranchName, const IndexedString& sLeafName, const T& data)
    {
        if(!sBranchName.empty() && !sLeafName.empty())
        {
            m_tBranches[sBranchName][sLeafName] = data;
        }
    }

    // Get leaf
    T& GetLeaf(const IndexedString& sBranchName, const IndexedString& sLeafName)
    {
        ASSERT_ERROR(HasLeaf(sBranchName, sLeafName), "Specified leaf '%s' on branch '%s' was not found", sLeafName.c_str(), sBranchName.c_str());
        return m_tBranches[sBranchName][sLeafName];
    }

    // Get leaf
    T& GetLeaf(const IndexedString& sLeafName)
    {
        IndexedString sBranchName = GetBranchFromLeaf(sLeafName);
        ASSERT_ERROR(!sBranchName.empty(), "Specified leaf '%s' was not found on any branches", sLeafName.c_str());
        return GetLeaf(sBranchName, sLeafName);
    }

    // Get leaf
    T& GetLeaf(const TreeIndex& index)
    {
        return GetLeaf(index.GetBranch(), index.GetLeaf());
    }

    // Get numbered leaf
    T& GetNumberedLeaf(const IndexedString& sBranchName, const IndexedString& sLeafBase, Int iLeafNumber)
    {
        return GetLeaf(sBranchName, GetLeafNameFromNumber(sLeafBase, iLeafNumber));
    }

    // Get all leaves
    TreeIndexList GetAllLeaves(const IndexedString& sBranchName)
    {
        // Check branch
        TreeIndexList vLeaves;
        if(sBranchName.empty())
        {
            return vLeaves;
        }

        // Make sure branch exists
        Bool bHasBranch = HasBranch(sBranchName);
        ASSERT_ERROR(bHasBranch, "Specified branch '%s' was not found", sBranchName.c_str());
        if(!bHasBranch)
        {
            return vLeaves;
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
    TreeIndexList GetLeavesUnderNumber(const IndexedString& sBranchName, const IndexedString& sLeafBase, Int iLeafNumber, Bool bUniqueOnly)
    {
        // Check branch
        TreeIndexList vLeaves;
        if(sBranchName.empty())
        {
            return vLeaves;
        }

        // Look at each of the leaves at or below the given number
        StringList vCheckedClasses;
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
                String sClass = leaf.GetSkillType().Get() + String("_") + leaf.GetDataClass().Get();
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
    Bool HasBranch(const IndexedString& sBranchName)
    {
        return (m_tBranches.find(sBranchName) != m_tBranches.end());
    }

    // Check if a leaf exists
    Bool HasLeaf(const IndexedString& sBranchName, const IndexedString& sLeafName)
    {
        return (m_tBranches.find(sBranchName) != m_tBranches.end() &&
                m_tBranches[sBranchName].find(sLeafName) != m_tBranches[sBranchName].end());
    }

    // Check if a numbered leaf exists
    Bool HasLeaf(const IndexedString& sBranchName, const IndexedString& sLeafBase, Int iLeafNumber)
    {
        return HasLeaf(sBranchName, GetLeafNameFromNumber(sLeafBase, iLeafNumber));
    }

    // Check if a leaf exists
    Bool HasLeaf(const IndexedString& sLeafName)
    {
        return HasLeaf(GetBranchFromLeaf(sLeafName), sLeafName);
    }

    // Check if a leaf exists
    Bool HasLeaf(const TreeIndex& index)
    {
        return HasLeaf(index.GetBranch(), index.GetLeaf());
    }

    // Get branch name from leaf name
    IndexedString GetBranchFromLeaf(const IndexedString& sLeafName)
    {
        IndexedString sBranchName("");
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
    IndexedString GetLeafNameFromNumber(const IndexedString& sLeafBase, Int iLeafNumber)
    {
        return sLeafBase + IndexedString(STDToString(iLeafNumber));
    }

private:

    // Deleted
    Tree(Tree const&) = delete;
    Tree& operator=(Tree const&) = delete;

    // Leaves
    typedef STDUnorderedMap<IndexedString, T, IndexedStringHasher> LeafType;
    typedef STDUnorderedMap<IndexedString, LeafType, IndexedStringHasher> BranchType;
    typedef typename LeafType::iterator LeafTypeIterator;
    typedef typename LeafType::const_iterator LeafTypeConstIterator;
    typedef STDPair<IndexedString, T> BranchNodeType;
    BranchType m_tBranches;
};

};

#endif
