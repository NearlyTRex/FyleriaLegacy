// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#ifndef _GECKO_INDEXED_STRING_H_
#define _GECKO_INDEXED_STRING_H_

#include "Utility/TypesSimple.h"
#include "Utility/TypesJson.h"

namespace Gecko
{

// Indexed string class
class IndexedString
{
public:

    // Constructors
    IndexedString();
    IndexedString(const IndexedString& other);
    IndexedString(const String& sStr);
    IndexedString(const char* sStr);
    IndexedString(char* sStr);

    // Operators
    IndexedString& operator=(const IndexedString& other);
    IndexedString& operator=(const String& sStr);

    // Set/get string
    void Set(const String& sStr);
    String Get() const;

    // Compatibility
    const ImmutableStringValueType* c_str() const;
    Bool empty() const;
    SizeType length() const;
    Int compare(SizeType szPos, SizeType szLen, const IndexedString& sStr) const;

    // Check if equal to None
    Bool IsNone() const;

    // Check if valid
    Bool IsValid() const;

    // Index
    Int GetIndex() const;

    // Comparison
    Bool operator==(const IndexedString& other) const;
    Bool operator!=(const IndexedString& other) const;
    Bool operator<(const IndexedString& other) const;

private:

    // Instance specific index
    Int m_iIndex;

    // Stored strings
    static ImmutableStringList s_vStoredStrings;
};

// Typedefs for IndexedString
typedef STDVector<IndexedString> IndexedStringList;

// Operators for IndexedString
IndexedString operator+(const IndexedString& a, const IndexedString& b);

// JSON converters for IndexedString
void to_json(Json& jsonData, const IndexedString& obj);
void from_json(const Json& jsonData, IndexedString& obj);

// Hashing function for IndexedString
struct IndexedStringHasher
{
    SizeType operator()(const IndexedString& obj) const noexcept
    {
        return STDHash<Int>()(obj.GetIndex());
    }
};

};

#endif
