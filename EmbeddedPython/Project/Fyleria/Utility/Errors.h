// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

#ifndef _GECKO_UTILITY_ERRORS_H_
#define _GECKO_UTILITY_ERRORS_H_

// Internal includes
#include "Utility/Enum.h"
#include "Utility/Types.h"

namespace Gecko
{

// Logic Error
// A logic error (or a failing assert ....) is by definition always the symptom of
// some bug in the program, e.g. a supposedly sorted array used for dichotomical
// access which happens to be unsorted.

// Runtime Error
// A runtime error may legitimately happen: e.g. some file containing garbage data,
// or some wrong human input, or some lack of resource (no more memory, disk space
// full, broken hardware, network connection failure).

// Python Error
// A module error is specifically designed for errors around Python.

// Error codes
BETTER_ENUM(ErrorCode, Int,
    GeneralError,
    LogicError,
    RuntimeError,
    PythonError
);

// General error
class GeneralError
{
public:
    GeneralError(const String& message)
        : m_sMessage(message)
        , m_Code(ErrorCode::GeneralError)
        , m_sFile()
        , m_iLine()
    {
    }

    GeneralError(const String& message, ErrorCode code)
        : m_sMessage(message)
        , m_Code(code)
        , m_sFile()
        , m_iLine()
    {
    }

    GeneralError(const String& message, ErrorCode code, const String& file, Int line)
        : m_sMessage(message)
        , m_Code(code)
        , m_sFile(file)
        , m_iLine(line)
    {
    }

    String what() const
    {
        return (BoostFormatString("Error of type %1% at line %2% in file %3%: %4%")
            % m_Code._to_string()
            % m_iLine
            % m_sFile
            % m_sMessage).str();
    }

    const String& message() const { return m_sMessage; }
    const ErrorCode code() const { return m_Code; }
    const String& file() const { return m_sFile; }
    Int line() const { return m_iLine; }

protected:
    const String m_sMessage;
    const ErrorCode m_Code;
    const String m_sFile;
    const Int m_iLine;
};

// Logic error
class LogicError : public GeneralError
{
public:
    LogicError(const String& message, const String& file = __FILE__, Int line = __LINE__)
        : GeneralError(message, ErrorCode::LogicError, file, line)
    {}
};

// Runtime error
class RuntimeError : public GeneralError
{
public:
    RuntimeError(const String& message, const String& file = __FILE__, Int line = __LINE__)
        : GeneralError(message, ErrorCode::RuntimeError, file, line)
    {}
};

// Python error
class PythonError : public GeneralError
{
public:
    PythonError(const String& message, const String& file = __FILE__, Int line = __LINE__)
        : GeneralError(message, ErrorCode::PythonError, file, line)
    {}
};

};

#endif
