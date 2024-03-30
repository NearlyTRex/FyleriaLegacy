// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

#ifndef _GECKO_UTILITY_TREEINDEX_H_
#define _GECKO_UTILITY_TREEINDEX_H_

// Internal includes
#include "Utility/Types.h"
#include "Utility/Json.h"

namespace Gecko
{

class TreeIndex
{
public:

    // Constructors
    TreeIndex();
    TreeIndex(const String& sTree, const String& sBranch, const String& sLeaf);
    TreeIndex(const Json& jsonData);
    TreeIndex(const String& jsonString);

    // Destructor
    virtual ~TreeIndex();

    // Composite types
    String GetTreeBranchType() const;
    String GetTreeBranchLeafType() const;
    StringArray GetTypes() const;

    // Compatibility
    Bool empty() const;

    // Operators
    TreeIndex& operator=(const TreeIndex& other);

    // Comparisons
    Bool operator==(const TreeIndex& other) const;
    Bool operator!=(const TreeIndex& other) const;

    // Tree name
    MAKE_RAW_TYPE_ACCESSORS(Tree, String);

    // Branch name
    MAKE_RAW_TYPE_ACCESSORS(Branch, String);

    // Leaf name
    MAKE_RAW_TYPE_ACCESSORS(Leaf, String);
};

// Typedef
MAKE_COMMON_TYPEDEFS(TreeIndex);

// JSON Converters
void to_json(Json& jsonData, const TreeIndex& obj);
void from_json(const Json& jsonData, TreeIndex& obj);

};

#endif
