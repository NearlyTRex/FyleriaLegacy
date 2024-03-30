// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#ifndef _GECKO_TYPES_SIMPLE_H_
#define _GECKO_TYPES_SIMPLE_H_

// Posix-style OS
#if !defined(_WIN32) && (defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__)))
#include <unistd.h>
#endif

// Apple OSX and iOS (Darwin)
#if defined(__APPLE__) && defined(__MACH__)
#include <TargetConditionals.h>
#endif

// Standard includes
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <sstream>
#include <utility>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <list>
#include <memory>
#include <fstream>
#include <limits>
#include <random>
#include <iterator>
#include <locale>
#include <codecvt>
#include <mutex>
#include <chrono>

// External includes
#include <cfgpath.h>
#include <immutable_string.h>
#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>

// Other includes
#include <Utility/Assert.h>
#include <Utility/Logging.h>

// STD defines
#define STDCout std::cout
#define STDEndl std::endl
#define STDHash std::hash
#define STDPair std::pair
#define STDVector std::vector
#define STDMap std::map
#define STDUnorderedMap std::unordered_map
#define STDSet std::set
#define STDUnorderedSet std::unordered_set
#define STDList std::list
#define STDSharedPtr std::shared_ptr
#define STDUniquePtr std::unique_ptr
#define STDMakeSharedPtr std::make_shared
#define STDMakeUniquePtr std::make_unique
#define STDMakePair std::make_pair
#define STDDistance std::distance
#define STDMoveData std::move
#define STDCopyData std::copy
#define STDFillData std::fill
#define STDFindData std::find
#define STDCountData std::count
#define STDRemoveData std::remove
#define STDClampData std::clamp
#define STDSortData std::sort
#define STDUniqueData std::unique
#define STDShuffleData std::shuffle
#define STDLess std::less
#define STDMin std::min
#define STDMax std::max
#define STDWStringConvert std::wstring_convert
#define STDUTF8AndUTF16Conversion std::codecvt_utf8_utf16
#define STDSetIntersection std::set_intersection
#define STDInserter std::inserter
#define STDBackInserter std::back_inserter
#define STDToString std::to_string
#define STDStringToInt std::stoi
#define STDStringToLong std::stol
#define STDStringToUnsignedLong std::stoul
#define STDStringToUnsignedLongLong std::stoull
#define STDReferenceWrapper std::reference_wrapper
#define STDNumericLimits std::numeric_limits
#define STDFmod std::fmod
#define STDRound std::round
#define STDGenerateCanonical std::generate_canonical
#define STDUniformIntDistribution std::uniform_int_distribution
#define STDUniformRealDistribution std::uniform_real_distribution
#define STDIOSFlagInputOperations std::ios::in
#define STDIOSFlagOutputOperations std::ios::out
#define STDIOSFlagBinaryMode std::ios::binary
#define STDIOSFlagInitialPosAtEnd std::ios::ate
#define STDIOSFlagAppendToEnd std::ios::app
#define STDIOSFlagTruncate std::ios::trunc
#define STDBindFunc std::bind
#define STDPlaceholder1 std::placeholders::_1
#define STDPlaceholder2 std::placeholders::_2
#define STDPlaceholder3 std::placeholders::_3
#define STDMutex std::mutex
#define STDLockGuard std::lock_guard
#define STDException std::exception
#define STDLogicErrorException std::logic_error
#define STDRuntimeErrorException std::runtime_error
#define STDInvalidArgumentException std::invalid_argument
#define STDTimePoint std::chrono::time_point<std::chrono::steady_clock>
#define STDGetCurrentTimePoint std::chrono::steady_clock::now
#define STDGetTimePointDuration std::chrono::duration_cast<std::chrono::seconds>
#define STDSetFill std::setfill
#define STDSetWidth std::setw
#define STDEnableSharedFromThis std::enable_shared_from_this
#define STDGetSharedThis shared_from_this
#define STDLexicalCast boost::lexical_cast
#define STDFormatString boost::format

namespace Gecko
{

// Random
typedef std::random_device RandomDevice;
typedef std::mt19937 RandomGenerator;

// Basics
typedef size_t SizeType;
typedef char Byte;
typedef wchar_t WByte;
typedef bool Bool;
typedef short Short;
typedef int Int;
typedef long Long;
typedef unsigned char UByte;
typedef unsigned short UShort;
typedef unsigned int UInt;
typedef unsigned long ULong;
typedef unsigned long long ULongLong;
typedef float Float;
typedef double Double;
typedef std::uint8_t FixedUnsigned8;
typedef std::uint16_t FixedUnsigned16;
typedef std::uint32_t FixedUnsigned32;
typedef std::uint64_t FixedUnsigned64;
typedef std::int8_t FixedSigned8;
typedef std::int16_t FixedSigned16;
typedef std::int32_t FixedSigned32;
typedef std::int64_t FixedSigned64;
typedef std::string String;
typedef std::wstring WString;
typedef std::ifstream InputFile;
typedef std::ofstream OutputFile;
typedef std::istringstream InputStringStream;
typedef std::ostringstream OutputStringStream;
typedef cdmh::immutable_string ImmutableString;
typedef cdmh::immutable_wstring ImmutableWString;
typedef ImmutableString::value_type ImmutableStringValueType;
typedef ImmutableWString::value_type ImmutableWStringValueType;

// Vectors
typedef STDVector<Byte> ByteList;
typedef STDVector<WByte> WByteList;
typedef STDVector<Bool> BoolList;
typedef STDVector<Short> ShortList;
typedef STDVector<Int> IntList;
typedef STDVector<UByte> UByteList;
typedef STDVector<UShort> UShortList;
typedef STDVector<UInt> UIntList;
typedef STDVector<Float> FloatList;
typedef STDVector<Double> DoubleList;
typedef STDVector<FixedUnsigned8> FixedUnsigned8List;
typedef STDVector<FixedUnsigned16> FixedUnsigned16List;
typedef STDVector<FixedUnsigned32> FixedUnsigned32List;
typedef STDVector<FixedUnsigned64> FixedUnsigned64List;
typedef STDVector<FixedSigned8> FixedSigned8List;
typedef STDVector<FixedSigned16> FixedSigned16List;
typedef STDVector<FixedSigned32> FixedSigned32List;
typedef STDVector<FixedSigned64> FixedSigned64List;
typedef STDVector<String> StringList;
typedef STDVector<WString> WStringList;
typedef STDVector<InputFile> InputFileList;
typedef STDVector<OutputFile> OutputFileList;
typedef STDVector<ImmutableString> ImmutableStringList;
typedef STDVector<ImmutableWString> ImmutableWStringList;

// Error codes
enum ErrorCode {
    GENERAL_ERROR = 1,
    LOGIC_ERROR,
    RUNTIME_ERROR,
    MODULE_ERROR
};

// General error
class STDGeneralError
{
public:
    STDGeneralError(const String& message) : m_sMessage(message), m_Code(GENERAL_ERROR) {}
    STDGeneralError(const String& message, ErrorCode code) : m_sMessage(message), m_Code(code) {}
    const String& what() const { return m_sMessage; }
    const ErrorCode code() const { return m_Code; }

protected:
    const String m_sMessage;
    const ErrorCode m_Code;
};

// Logic error
class STDLogicError : public STDGeneralError
{
public:
    STDLogicError(const String& message) : STDGeneralError(message, LOGIC_ERROR) {}
};

// Runtime error
class STDRuntimeError : public STDGeneralError
{
public:
    STDRuntimeError(const String& message) : STDGeneralError(message, RUNTIME_ERROR) {}
};

// Module error
class STDModuleError : public STDGeneralError
{
public:
    STDModuleError(const String& message) : STDGeneralError(message, MODULE_ERROR) {}
};

// Clip value between two ends
template <typename T>
T STDClip(const T& n, const T& lower, const T& upper)
{
    return STDMax(lower, STDMin(n, upper));
}

// Find intersection vector
template <typename T>
STDVector<T> STDVectorFindIntersect(STDVector<T> v1, STDVector<T> v2)
{
    STDVector<T> v3;
    STDSortData(v1.begin(), v1.end());
    STDSortData(v2.begin(), v2.end());
    STDSetIntersection(v1.begin(), v1.end(), v2.begin(), v2.end(), STDBackInserter(v3));
    return v3;
}

// Determine if vector intersects with element
template <typename T>
Bool STDVectorDoesIntersectElement(const STDVector<T>& v, const T& e)
{
    STDVector<T> v2 = {e};
    STDVector<T> vIntersect = STDVectorFindIntersect<T>(v, v2);
    return (!vIntersect.empty());
}

// Determine if vector intersects with all elements
template <typename T>
Bool STDVectorDoesIntersectAND(const STDVector<T>& v1, const STDVector<T>& v2)
{
    STDVector<T> vIntersect = STDVectorFindIntersect<T>(v1, v2);
    return (vIntersect.size() == v1.size() && vIntersect.size() == v2.size());
}

// Determine if vector intersects with one element
template <typename T>
Bool STDVectorDoesIntersectOR(const STDVector<T>& v1, const STDVector<T>& v2)
{
    STDVector<T> vIntersect = STDVectorFindIntersect<T>(v1, v2);
    return (!vIntersect.empty());
}

// Convert list of references to list of copies
template <typename T>
STDVector<T> STDConvertRefListToCopyList(const STDVector<STDReferenceWrapper<T>>& vRefList)
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
Bool STDDoesChanceSucceed(T varChance)
{
    RandomDevice device;
    RandomGenerator gen(device());
    T varRandomValue = STDGenerateCanonical<T, 10>(gen);
    return (varRandomValue <= varChance);
}

// Random int value
template <typename T>
T STDRandomIntValue(T varMin, T varMax)
{
    RandomDevice device;
    RandomGenerator gen(device());
    STDUniformIntDistribution<T> dis(varMin, varMax);
    return dis(gen);
}

// Random real value
template <typename T>
T STDRandomRealValue(T varMin, T varMax)
{
    RandomDevice device;
    RandomGenerator gen(device());
    STDUniformRealDistribution<T> dis(varMin, varMax);
    return dis(gen);
}

// Random vector value
template <typename T>
T STDRandomVectorValue(const STDVector<T>& varValues)
{
    if(varValues.empty())
    {
        return T();
    }

    Int iRandomIndex = STDRandomIntValue<Int>(0, varValues.size() - 1);
    return varValues[iRandomIndex];
}

// Random enum value
template <typename T>
String STDRandomEnumValue()
{
    ASSERT_FATAL(T::_names().size() >= 2);
    Int iIndex = STDRandomIntValue<Int>(1, T::_names().size() - 1);
    ASSERT_FATAL(iIndex >= 0 && iIndex < static_cast<Int>(T::_names().size()));
    return T::_names()[iIndex];
}

// Unordered vector remove
template <typename T>
void STDVectorRemoveElement(STDVector<T>& vVector, T varData)
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
void STDVectorRemoveDuplicates(STDVector<T>& vVector)
{
    STDSortData(vVector.begin(), vVector.end());
    vVector.erase(STDUniqueData(vVector.begin(), vVector.end()), vVector.end());
}

// Shuffle vector elements
template <typename T>
void STDVectorShuffle(STDVector<T>& vVector)
{
    RandomDevice device;
    RandomGenerator gen(device());
    STDShuffleData(vVector.begin(), vVector.end(), gen);
}

// Print vector of strings
template <typename T>
void STDVectorPrintStrings(const STDVector<T>& vVector)
{
    PRINTF("(");
    for(UInt i = 0; i < vVector.size(); i++)
    {
        PRINTF("%s", vVector[i].c_str());
        if(i != vVector.size() - 1)
        {
            PRINTF(", ");
        }
    }
    PRINTF(")\n");
}

// Convert vector of strings to one string
template <typename T>
T STDVectorConvertStrings(const STDVector<T>& vVector)
{
    T sStr = "(";
    for(UInt i = 0; i < vVector.size(); i++)
    {
        sStr = sStr + vVector[i];
        if(i != vVector.size() - 1)
        {
            sStr = sStr + T(", ");
        }
    }
    sStr = sStr + ")";
    return sStr;
}

// Check if a string starts with another string
template <typename T>
Bool STDStartsWith(const T& sText, const T& sToken)
{
    if(sText.size() >= sToken.size())
    {
        return (sText.compare(0, sToken.length(), sToken) == 0);
    }
    return false;
}

// Check if a string ends with another string
template <typename T>
Bool STDEndsWith(const T& sText, const T& sToken)
{
	if(sText.size() >= sToken.size())
    {
		return (sText.compare(sText.size() - sToken.size(), sToken.size(), sToken) == 0);
    }
	return false;
}

// Convert strings
WString STDConvertStringToWideString(const String& sString);
String STDConvertWideStringToString(const WString& sWideString);

// Time strings
String STDGetGameTime(ULongLong uTime);

};

#endif
