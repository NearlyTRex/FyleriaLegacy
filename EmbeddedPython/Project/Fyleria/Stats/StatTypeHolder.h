// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

#ifndef _GECKO_STAT_TYPE_HOLDER_H_
#define _GECKO_STAT_TYPE_HOLDER_H_

// Internal includes
#include "Stats/StatType.h"
#include "Stats/StatNames.h"
#include "Utility/Types.h"
#include "Utility/Macros.h"
#include "Utility/Enum.h"
#include "Utility/Errors.h"
#include "Utility/Json.h"

namespace Gecko
{

// Stat type holder
class StatTypeHolder
{
public:

    // Constructor
    StatTypeHolder();

    // Destructor
    virtual ~StatTypeHolder();

    // Clear all data
    virtual void Clear();

    // Get stat values
    Bool GetStatValue(const String& sStat, Bool& bValue) const;
    Bool GetStatValue(const String& sStat, Byte& iValue) const;
    Bool GetStatValue(const String& sStat, Short& iValue) const;
    Bool GetStatValue(const String& sStat, Int& iValue) const;
    Bool GetStatValue(const String& sStat, Float& fValue) const;
    Bool GetStatValue(const String& sStat, Double& fValue) const;
    Bool GetStatValue(const String& sStat, String& sValue) const;
    Bool GetStatValue(const String& sStat, StringArray& vValues) const;

    // Get stat value
    template <class T>
    T GetStatValue(const String& sStat) const
    {
        T varStat {};
        GetStatValue(sStat, varStat);
        return varStat;
    }

    // Set stat values
    Bool SetStatValue(const String& sStat, const Bool& bValue);
    Bool SetStatValue(const String& sStat, const Byte& iValue);
    Bool SetStatValue(const String& sStat, const Short& iValue);
    Bool SetStatValue(const String& sStat, const Int& iValue);
    Bool SetStatValue(const String& sStat, const Float& fValue);
    Bool SetStatValue(const String& sStat, const Double& fValue);
    Bool SetStatValue(const String& sStat, const String& sValue);
    Bool SetStatValue(const String& sStat, const StringArray& vValues);

    // Stat types
    MAKE_RAW_TYPE_ACCESSORS(BoolStats, BoolStatTypeMap);
    MAKE_RAW_TYPE_ACCESSORS(ByteStats, ByteStatTypeMap);
    MAKE_RAW_TYPE_ACCESSORS(ShortStats, ShortStatTypeMap);
    MAKE_RAW_TYPE_ACCESSORS(IntStats, IntStatTypeMap);
    MAKE_RAW_TYPE_ACCESSORS(FloatStats, FloatStatTypeMap);
    MAKE_RAW_TYPE_ACCESSORS(DoubleStats, DoubleStatTypeMap);
    MAKE_RAW_TYPE_ACCESSORS(StringStats, StringStatTypeMap);
    MAKE_RAW_TYPE_ACCESSORS(StringArrayStats, StringArrayStatTypeMap);
};

};

#endif
