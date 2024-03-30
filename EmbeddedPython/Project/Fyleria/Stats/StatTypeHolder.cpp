// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

// Internal includes
#include "Stats/StatTypeHolder.h"

namespace Gecko
{

StatTypeHolder::StatTypeHolder()
{
}

StatTypeHolder::~StatTypeHolder()
{
}

void StatTypeHolder::Clear()
{
    GetBoolStats().clear();
    GetByteStats().clear();
    GetShortStats().clear();
    GetIntStats().clear();
    GetFloatStats().clear();
    GetDoubleStats().clear();
    GetStringStats().clear();
    GetStringArrayStats().clear();
}

Bool StatTypeHolder::GetStatValue(const String& sStat, Bool& bValue) const
{
    return GetStatMapValue<Bool>(GetBoolStats(), sStat, bValue);
}

Bool StatTypeHolder::GetStatValue(const String& sStat, Byte& iValue) const
{
    return GetStatMapValue<Byte>(GetByteStats(), sStat, iValue);
}

Bool StatTypeHolder::GetStatValue(const String& sStat, Short& iValue) const
{
    return GetStatMapValue<Short>(GetShortStats(), sStat, iValue);
}

Bool StatTypeHolder::GetStatValue(const String& sStat, Int& iValue) const
{
    return GetStatMapValue<Int>(GetIntStats(), sStat, iValue);
}

Bool StatTypeHolder::GetStatValue(const String& sStat, Float& fValue) const
{
    return GetStatMapValue<Float>(GetFloatStats(), sStat, fValue);
}

Bool StatTypeHolder::GetStatValue(const String& sStat, Double& fValue) const
{
    return GetStatMapValue<Double>(GetDoubleStats(), sStat, fValue);
}

Bool StatTypeHolder::GetStatValue(const String& sStat, String& sValue) const
{
    return GetStatMapValue<String>(GetStringStats(), sStat, sValue);
}

Bool StatTypeHolder::GetStatValue(const String& sStat, StringArray& vValues) const
{
    return GetStatMapValue<StringArray>(GetStringArrayStats(), sStat, vValues);
}

Bool StatTypeHolder::SetStatValue(const String& sStat, const Bool& bValue)
{
    return SetStatMapValue<Bool>(GetBoolStats(), sStat, bValue);
}

Bool StatTypeHolder::SetStatValue(const String& sStat, const Byte& iValue)
{
    return SetStatMapValue<Byte>(GetByteStats(), sStat, iValue);
}

Bool StatTypeHolder::SetStatValue(const String& sStat, const Short& iValue)
{
    return SetStatMapValue<Short>(GetShortStats(), sStat, iValue);
}

Bool StatTypeHolder::SetStatValue(const String& sStat, const Int& iValue)
{
    return SetStatMapValue<Int>(GetIntStats(), sStat, iValue);
}

Bool StatTypeHolder::SetStatValue(const String& sStat, const Float& fValue)
{
    return SetStatMapValue<Float>(GetFloatStats(), sStat, fValue);
}

Bool StatTypeHolder::SetStatValue(const String& sStat, const Double& fValue)
{
    return SetStatMapValue<Double>(GetDoubleStats(), sStat, fValue);
}

Bool StatTypeHolder::SetStatValue(const String& sStat, const String& sValue)
{
    return SetStatMapValue<String>(GetStringStats(), sStat, sValue);
}

Bool StatTypeHolder::SetStatValue(const String& sStat, const StringArray& vValues)
{
    return SetStatMapValue<StringArray>(GetStringArrayStats(), sStat, vValues);
}

};
