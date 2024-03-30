// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#include "Utility/Tree.h"
#include "Utility/TypesJson.h"
#include "Utility/Macros.h"

namespace Gecko
{

TreeIndex::TreeIndex()
    : SerializableToJson()
    , m_sTreeName()
    , m_sBranchName()
    , m_sLeafName()
{}

TreeIndex::TreeIndex(const IndexedString& sTree, const IndexedString& sBranch, const IndexedString& sLeaf)
    : SerializableToJson()
    , m_sTreeName(sTree)
    , m_sBranchName(sBranch)
    , m_sLeafName(sLeaf)
{}

TreeIndex::TreeIndex(const Json& jsonData)
    : SerializableToJson()
    , m_sTreeName()
    , m_sBranchName()
    , m_sLeafName()
{
    from_json(jsonData, *this);
}

TreeIndex::TreeIndex(const String& jsonString)
    : SerializableToJson()
    , m_sTreeName()
    , m_sBranchName()
    , m_sLeafName()
{
    from_json(JsonParse(jsonString), *this);
}

const IndexedString& TreeIndex::GetTree() const
{
    return m_sTreeName;
}

const IndexedString& TreeIndex::GetBranch() const
{
    return m_sBranchName;
}

const IndexedString& TreeIndex::GetLeaf() const
{
    return m_sLeafName;
}

void TreeIndex::SetTree(const IndexedString& sName)
{
    m_sTreeName = sName;
}

void TreeIndex::SetBranch(const IndexedString& sName)
{
    m_sBranchName = sName;
}

void TreeIndex::SetLeaf(const IndexedString& sName)
{
    m_sLeafName = sName;
}

IndexedString TreeIndex::GetTreeBranchType() const
{
    return (GetTree() + GetBranch());
}

IndexedString TreeIndex::GetTreeBranchLeafType() const
{
    return (GetTree() + GetBranch() + GetLeaf());
}

IndexedStringList TreeIndex::GetTypes() const
{
    IndexedStringList vTypes = {
        GetTree(),
        GetBranch(),
        GetLeaf()
    };
    return vTypes;
}

Bool TreeIndex::empty() const
{
    return (GetTree().empty() ||
            GetBranch().empty() ||
            GetLeaf().empty());
}

Bool TreeIndex::operator==(const TreeIndex& other) const
{
    return ((GetTree() == other.GetTree()) &&
            (GetBranch() == other.GetBranch()) &&
            (GetLeaf() == other.GetLeaf()));
}

Bool TreeIndex::operator!=(const TreeIndex& other) const
{
    return !(*this == other);
}

void to_json(Json& jsonData, const TreeIndex& obj)
{
    jsonData["Tree"] = obj.GetTree();
    jsonData["Branch"] = obj.GetBranch();
    jsonData["Leaf"] = obj.GetLeaf();
}

void from_json(const Json& jsonData, TreeIndex& obj)
{
    obj.SetTree(GET_JSON_DATA_OR_DEFAULT(Tree, IndexedString, IndexedString("")));
    obj.SetBranch(GET_JSON_DATA_OR_DEFAULT(Branch, IndexedString, IndexedString("")));
    obj.SetLeaf(GET_JSON_DATA_OR_DEFAULT(Leaf, IndexedString, IndexedString("")));
}

MAKE_JSON_GENERIC_TYPE_CONVERTERS_IMPL(TreeIndex, TreeIndex);

};
