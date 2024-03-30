// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

#ifndef _GECKO_STAT_TYPE_H_
#define _GECKO_STAT_TYPE_H_

// Internal includes
#include "Utility/Types.h"
#include "Utility/Json.h"
#include "Utility/Enum.h"

namespace Gecko
{

// Typedefs
typedef STDUnorderedMap<String, Bool> BoolStatTypeMap;
typedef STDUnorderedMap<String, Byte> ByteStatTypeMap;
typedef STDUnorderedMap<String, Short> ShortStatTypeMap;
typedef STDUnorderedMap<String, Int> IntStatTypeMap;
typedef STDUnorderedMap<String, Float> FloatStatTypeMap;
typedef STDUnorderedMap<String, Double> DoubleStatTypeMap;
typedef STDUnorderedMap<String, String> StringStatTypeMap;
typedef STDUnorderedMap<String, StringArray> StringArrayStatTypeMap;

// Set stat map value
template <class MappedType>
Bool SetStatMapValue(STDUnorderedMap<String, MappedType>& tStatMap, const String& sStatName, const MappedType& inValue)
{
    if(tStatMap.find(sStatName) == tStatMap.end())
    {
        auto result = tStatMap.insert({sStatName, inValue});
        return (result.first != tStatMap.end());
    }
    else
    {
        tStatMap.at(sStatName) = inValue;
        return true;
    }
}

// Get stat map value
template <class MappedType>
Bool GetStatMapValue(const STDUnorderedMap<String, MappedType>& tStatMap, const String& sStatName, MappedType& outValue)
{
    if(tStatMap.find(sStatName) == tStatMap.end())
    {
        return false;
    }
    outValue = tStatMap.at(sStatName);
    return true;
}

// Initialize stat type names
template <class EnumType>
void InitializeStatTypeNames(SafeObject<STDUnorderedSet<String>>& tStatNameMap)
{
    for(auto& sStatTypeName : GetEnumNames<EnumType>())
    {
        if(IsNoneTypeForEnum<EnumType>(sStatTypeName))
        {
            continue;
        }

        tStatNameMap->insert(sStatTypeName);
    }
}

// Initialize stat type values
template <class EnumType, class MappedType>
void InitializeStatTypeValues(STDUnorderedMap<String, MappedType>& tStatValueMap)
{
    for(auto& sStatTypeName : GetEnumNames<EnumType>())
    {
        if(IsNoneTypeForEnum<EnumType>(sStatTypeName))
        {
            continue;
        }

        SetStatMapValue<MappedType>(tStatValueMap, sStatTypeName, {});
    }
}

// Set json values from stat type values
template <class EnumType, class MappedType>
void SetJsonValuesFromStatTypeValues(Json& jsonData, const STDUnorderedMap<String, MappedType>& tStatValueMap)
{
    for(auto& sStatTypeName : GetEnumNames<EnumType>())
    {
        if(IsNoneTypeForEnum<EnumType>(sStatTypeName))
        {
            continue;
        }

        MappedType varStatValue {};
        if(GetStatMapValue<MappedType>(tStatValueMap, sStatTypeName, varStatValue))
        {
            jsonData[sStatTypeName] = varStatValue;
        }
    }
}

// Set stat type values from json values
template <class EnumType, class MappedType>
void SetStatTypeValuesFromJsonValues(const Json& jsonData, STDUnorderedMap<String, MappedType>& tStatValueMap)
{
    for(auto& sStatTypeName : GetEnumNames<EnumType>())
    {
        if(IsNoneTypeForEnum<EnumType>(sStatTypeName))
        {
            continue;
        }

        if(jsonData.find(sStatTypeName) != jsonData.end())
        {
            MappedType varStatValue = jsonData[sStatTypeName].template get<MappedType>();
            SetStatMapValue<MappedType>(tStatValueMap, sStatTypeName, varStatValue);
        }
    }
}

};

#endif
