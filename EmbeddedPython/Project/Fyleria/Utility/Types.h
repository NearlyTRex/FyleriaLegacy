// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

#ifndef _GECKO_UTILITY_TYPES_H_
#define _GECKO_UTILITY_TYPES_H_

// Internal includes
#include "Utility/Platform.h"
#include "Utility/Standard.h"
#include "Utility/Boost.h"
#include "Utility/ObjectThreadsafe.h"

// Posix-style OS
#if defined(PLATFORM_POSIX)
#include <unistd.h>
#endif

namespace Gecko
{

// Types
typedef std::random_device RandomDevice;
typedef std::mt19937 RandomGenerator;
typedef std::time_t TimeType;
typedef size_t SizeType;
typedef char Byte;
typedef wchar_t WByte;
typedef bool Bool;
typedef short Short;
typedef int Int;
typedef long Long;
typedef long long LongLong;
typedef unsigned char UByte;
typedef unsigned short UShort;
typedef unsigned int UInt;
typedef unsigned long ULong;
typedef unsigned long long ULongLong;
typedef float Float;
typedef double Double;
typedef long double LongDouble;
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
typedef std::stringstream StringStream;
typedef std::istringstream InputStringStream;
typedef std::ostringstream OutputStringStream;
typedef std::atomic_size_t AtomicSizeType;
typedef std::atomic_bool AtomicBool;
typedef std::atomic_char AtomicByte;
typedef std::atomic_wchar_t AtomicWByte;
typedef std::atomic_short AtomicShort;
typedef std::atomic_int AtomicInt;
typedef std::atomic_long AtomicLong;
typedef std::atomic_llong AtomicLongLong;
typedef std::atomic_uchar AtomicUByte;
typedef std::atomic_ushort AtomicUShort;
typedef std::atomic_uint AtomicUInt;
typedef std::atomic_ulong AtomicULong;
typedef std::atomic_ullong AtomicULongLong;
typedef std::atomic<float> AtomicFloat;
typedef std::atomic<double> AtomicDouble;
typedef std::atomic<long double> AtomicLongDouble;
typedef std::atomic_uint8_t AtomicFixedUnsigned8;
typedef std::atomic_uint16_t AtomicFixedUnsigned16;
typedef std::atomic_uint32_t AtomicFixedUnsigned32;
typedef std::atomic_uint64_t AtomicFixedUnsigned64;
typedef std::atomic_int8_t AtomicFixedSigned8;
typedef std::atomic_int16_t AtomicFixedSigned16;
typedef std::atomic_int32_t AtomicFixedSigned32;
typedef std::atomic_int64_t AtomicFixedSigned64;
typedef STDVector<Byte> ByteArray;
typedef STDVector<WByte> WByteArray;
typedef STDVector<Bool> BoolArray;
typedef STDVector<Short> ShortArray;
typedef STDVector<Int> IntArray;
typedef STDVector<Long> LongArray;
typedef STDVector<LongLong> LongLongArray;
typedef STDVector<UByte> UByteArray;
typedef STDVector<UShort> UShortArray;
typedef STDVector<UInt> UIntArray;
typedef STDVector<ULong> ULongArray;
typedef STDVector<ULongLong> ULongLongArray;
typedef STDVector<Float> FloatArray;
typedef STDVector<Double> DoubleArray;
typedef STDVector<LongDouble> LongDoubleArray;
typedef STDVector<FixedUnsigned8> FixedUnsigned8Array;
typedef STDVector<FixedUnsigned16> FixedUnsigned16Array;
typedef STDVector<FixedUnsigned32> FixedUnsigned32Array;
typedef STDVector<FixedUnsigned64> FixedUnsigned64Array;
typedef STDVector<FixedSigned8> FixedSigned8Array;
typedef STDVector<FixedSigned16> FixedSigned16Array;
typedef STDVector<FixedSigned32> FixedSigned32Array;
typedef STDVector<FixedSigned64> FixedSigned64Array;
typedef STDVector<String> StringArray;
typedef STDVector<WString> WStringArray;
typedef STDVector<InputFile> InputFileArray;
typedef STDVector<OutputFile> OutputFileArray;
typedef STDMap<String, String> StringMap;
typedef STDMap<WString, WString> WStringMap;
typedef STDSet<String> StringSet;
typedef STDSet<WString> WStringSet;
typedef STDUnorderedMap<String, String> StringUnorderedMap;
typedef STDUnorderedMap<WString, WString> WStringUnorderedMap;
typedef STDUnorderedSet<String> StringUnorderedSet;
typedef STDUnorderedSet<WString> WStringUnorderedSet;
typedef STDFunction<Byte()> ByteGetFunction;
typedef STDFunction<void(Byte)> ByteSetFunction;
typedef STDFunction<Short()> ShortGetFunction;
typedef STDFunction<void(Short)> ShortSetFunction;
typedef STDFunction<Int()> IntGetFunction;
typedef STDFunction<void(Int)> IntSetFunction;
typedef STDFunction<UByte()> UByteGetFunction;
typedef STDFunction<void(UByte)> UByteSetFunction;
typedef STDFunction<UShort()> UShortGetFunction;
typedef STDFunction<void(UShort)> UShortSetFunction;
typedef STDFunction<UInt()> UIntGetFunction;
typedef STDFunction<void(UInt)> UIntSetFunction;
typedef STDFunction<Float()> FloatGetFunction;
typedef STDFunction<void(Float)> FloatSetFunction;
typedef STDFunction<Double()> DoubleGetFunction;
typedef STDFunction<void(Double)> DoubleSetFunction;
typedef SafeObject<String> SafeString;
typedef SafeObject<WString> SafeWString;
typedef SafeObject<InputFile> SafeInputFile;
typedef SafeObject<OutputFile> SafeOutputFile;
typedef SafeObject<InputStringStream> SafeInputStringStream;
typedef SafeObject<OutputStringStream> SafeOutputStringStream;
typedef SafeObject<StringMap> SafeStringMap;
typedef SafeObject<WStringMap> SafeWStringMap;
typedef SafeObject<StringSet> SafeStringSet;
typedef SafeObject<WStringSet> SafeWStringSet;
typedef SafeObject<StringUnorderedMap> SafeStringUnorderedMap;
typedef SafeObject<WStringUnorderedMap> SafeWStringUnorderedMap;
typedef SafeObject<StringUnorderedSet> SafeStringUnorderedSet;
typedef SafeObject<WStringUnorderedSet> SafeWStringUnorderedSet;

};

#endif
