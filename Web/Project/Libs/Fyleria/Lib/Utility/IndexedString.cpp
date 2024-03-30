// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#include "Utility/IndexedString.h"
#include "Utility/Logging.h"

namespace Gecko
{

ImmutableStringList IndexedString::s_vStoredStrings;

IndexedString::IndexedString()
    : m_iIndex(-1)
{
}

IndexedString::IndexedString(const IndexedString& other)
    : m_iIndex(other.m_iIndex)
{
}

IndexedString::IndexedString(const String& sStr)
    : m_iIndex(-1)
{
    Set(sStr);
}

IndexedString::IndexedString(const char* sStr)
    : m_iIndex(-1)
{
    Set(sStr);
}

IndexedString::IndexedString(char* sStr)
    : m_iIndex(-1)
{
    Set(sStr);
}

IndexedString& IndexedString::operator=(const IndexedString& other)
{
    if(this != &other)
    {
        m_iIndex = other.m_iIndex;
    }
    return *this;
}

IndexedString& IndexedString::operator=(const String& sStr)
{
    Set(sStr);
    return *this;
}

void IndexedString::Set(const String& sStr)
{
    // Find out if new string is already stored
    ImmutableString sImmutableStr = sStr;
    auto iSearch = STDFindData(s_vStoredStrings.begin(), s_vStoredStrings.end(), sImmutableStr);

    // String is not found, we will have to add it
    if(iSearch == s_vStoredStrings.end())
    {
        // Add new string
        s_vStoredStrings.push_back(sImmutableStr);
        m_iIndex = s_vStoredStrings.size() - 1;

        // Some extra logging
        LOG_FORMAT_STATEMENT("Adding string '%s' to index %i, current count is %zu\n",
            sImmutableStr.c_str(),
            m_iIndex,
            s_vStoredStrings.size());
        return;
    }

    // String was found, make sure to update the index
    m_iIndex = STDDistance(s_vStoredStrings.begin(), iSearch);
}

String IndexedString::Get() const
{
    // Return actual string
    return (IsValid()) ? s_vStoredStrings[m_iIndex].mutable_string() : String();
}

const ImmutableStringValueType* IndexedString::c_str() const
{
    // Return c-string
    return (IsValid()) ? s_vStoredStrings[m_iIndex].c_str() : nullptr;
}

Bool IndexedString::empty() const
{
    // Return empty status
    return (IsValid()) ? s_vStoredStrings[m_iIndex].empty() : true;
}

SizeType IndexedString::length() const
{
    // Return length
    return (IsValid()) ? s_vStoredStrings[m_iIndex].length() : 0;
}

Int IndexedString::compare(SizeType szPos, SizeType szLen, const IndexedString& sStr) const
{
    // Return comparison
    return (IsValid()) ? s_vStoredStrings[m_iIndex].compare(szPos, szLen, sStr.Get()) : 0;
}

Bool IndexedString::IsNone() const
{
    // Return none status
    return (GetIndex() == IndexedString("None").GetIndex());
}

Bool IndexedString::IsValid() const
{
    // Return validity status
    return (GetIndex() >= 0 && GetIndex() < static_cast<Int>(s_vStoredStrings.size()));
}

Int IndexedString::GetIndex() const
{
    return m_iIndex;
}

Bool IndexedString::operator==(const IndexedString& other) const
{
    return (GetIndex() == other.GetIndex());
}

Bool IndexedString::operator!=(const IndexedString& other) const
{
    return (GetIndex() != other.GetIndex());
}

Bool IndexedString::operator<(const IndexedString& other) const
{
    return (GetIndex() < other.GetIndex());
}

IndexedString operator+(const IndexedString& a, const IndexedString& b)
{
    return IndexedString(a.Get() + b.Get());
}

void to_json(Json& jsonData, const IndexedString& obj)
{
    jsonData = obj.Get();
}

void from_json(const Json& jsonData, IndexedString& obj)
{
    obj.Set(jsonData.get<String>());
}

};
