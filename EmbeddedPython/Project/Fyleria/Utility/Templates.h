// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

#ifndef _GECKO_UTILITY_TEMPLATES_H_
#define _GECKO_UTILITY_TEMPLATES_H_

// Internal includes
#include "Utility/Assert.h"
#include "Utility/Logging.h"

namespace Gecko
{

// Clip value between two ends
template <typename T>
T ClipValue(const T& n, const T& lower, const T& upper)
{
    return STDMax(lower, STDMin(n, upper));
}

// Find intersection vector
template <typename T>
STDVector<T> FindVectorIntersection(STDVector<T> v1, STDVector<T> v2)
{
    STDVector<T> v3;
    STDSortData(v1.begin(), v1.end());
    STDSortData(v2.begin(), v2.end());
    STDSetIntersection(v1.begin(), v1.end(), v2.begin(), v2.end(), STDBackInserter(v3));
    return v3;
}

// Determine if vector intersects with element
template <typename T>
Bool DoesVectorIntersectElement(const STDVector<T>& v, const T& e)
{
    STDVector<T> v2 = {e};
    STDVector<T> vIntersect = FindVectorIntersection<T>(v, v2);
    return (!vIntersect.empty());
}

// Determine if vector intersects with all elements
template <typename T>
Bool DoesVectorIntersectAND(const STDVector<T>& v1, const STDVector<T>& v2)
{
    STDVector<T> vIntersect = FindVectorIntersection<T>(v1, v2);
    return (vIntersect.size() == v1.size() && vIntersect.size() == v2.size());
}

// Determine if vector intersects with one element
template <typename T>
Bool DoesVectorIntersectOR(const STDVector<T>& v1, const STDVector<T>& v2)
{
    STDVector<T> vIntersect = FindVectorIntersection<T>(v1, v2);
    return (!vIntersect.empty());
}

// Convert list of references to list of copies
template <typename T>
STDVector<T> ConvertRefListToCopyList(const STDVector<STDReferenceWrapper<T>>& vRefList)
{
    STDVector<T> vCopyList(vRefList.size());
    for(auto&& i : vRefList)
    {
        vCopyList.push_back(i.get());
    }
    return vCopyList;
}

// Check if chance succeeded
template <typename T>
Bool DoesChanceSucceed(T varChance)
{
    RandomDevice device;
    RandomGenerator gen(device());
    T varRandomValue = STDGenerateCanonical<T, 10>(gen);
    return (varRandomValue <= varChance);
}

// Random int value
template <typename T>
T GetRandomIntValue(T varMin, T varMax)
{
    if(varMin < varMax)
    {
        RandomDevice device;
        RandomGenerator gen(device());
        STDUniformIntDistribution<T> dis(varMin, varMax);
        return dis(gen);
    }
    return varMin;
}

// Random real value
template <typename T>
T GetRandomRealValue(T varMin, T varMax)
{
    if(varMin < varMax)
    {
        RandomDevice device;
        RandomGenerator gen(device());
        STDUniformRealDistribution<T> dis(varMin, varMax);
        return dis(gen);
    }
    return varMin;
}

// Random vector value
template <typename T>
T GetRandomVectorValue(const STDVector<T>& varValues)
{
    if(varValues.empty())
    {
        return T();
    }

    Int iRandomIndex = GetRandomIntValue<Int>(0, static_cast<Int>(varValues.size()) - 1);
    return varValues[iRandomIndex];
}

// Random enum value
template <typename T>
String GetRandomEnumValue()
{
    ASSERT_FATAL(T::_names().size() >= 2);
    Int iIndex = GetRandomIntValue<Int>(1, static_cast<Int>(T::_names().size()) - 1);
    ASSERT_FATAL(iIndex >= 0 && iIndex < static_cast<Int>(T::_names().size()));
    return T::_names()[iIndex];
}

// Unordered vector remove
template <typename T>
void RemoveVectorElement(STDVector<T>& vVector, T varData)
{
    auto iSearch = STDFindData(vVector.begin(), vVector.end(), varData);
    if(iSearch != vVector.end())
    {
        *iSearch = STDMoveData(vVector.back());
        vVector.pop_back();
    }
}

// Remove vector duplicates
template <typename T>
void RemoveVectorDuplicates(STDVector<T>& vVector)
{
    STDSortData(vVector.begin(), vVector.end());
    vVector.erase(STDUniqueData(vVector.begin(), vVector.end()), vVector.end());
}

// Shuffle vector elements
template <typename T>
void ShuffleVector(STDVector<T>& vVector)
{
    RandomDevice device;
    RandomGenerator gen(device());
    STDShuffleData(vVector.begin(), vVector.end(), gen);
}

// Print vector of strings
template <typename T>
void PrintStringVector(const STDVector<T>& vVector)
{
    printf("[");
    for(UInt i = 0; i < vVector.size(); i++)
    {
        printf("%s", vVector[i].c_str());
        if(i != vVector.size() - 1)
        {
            printf(", ");
        }
    }
    printf("]\n");
}

// Concatenate vector of strings to one string
template <typename T>
T ConcatStringVector(const STDVector<T>& vVector)
{
    T sStr = "[";
    for(UInt i = 0; i < vVector.size(); i++)
    {
        sStr = sStr + vVector[i];
        if(i != vVector.size() - 1)
        {
            sStr = sStr + T(", ");
        }
    }
    sStr = sStr + "]";
    return sStr;
}

// Check if a string starts with another string
template <typename T>
Bool StartsWith(const T& sText, const T& sToken)
{
    if(sText.size() >= sToken.size())
    {
        return (sText.compare(0, sToken.length(), sToken) == 0);
    }
    return false;
}

// Check if a string ends with another string
template <typename T>
Bool EndsWith(const T& sText, const T& sToken)
{
    if(sText.size() >= sToken.size())
    {
        return (sText.compare(sText.size() - sToken.size(), sToken.size(), sToken) == 0);
    }
    return false;
}

// Get map data or a default value
template <typename MapType>
typename MapType::mapped_type GetMapDataOrDefault(
    const MapType& map,
    typename MapType::key_type key,
    typename MapType::mapped_type default_value)
{
    return (map.find(key) != map.end()) ? map.at(key) : default_value;
}

};

#endif
