// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#ifndef _APP_REQUEST_PARSER_H_
#define _APP_REQUEST_PARSER_H_

// System includes
#include <string>
#include <iostream>
#include <map>

// External includes
#include <json.hpp>
#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>

// Internal includes
#include <Interface/Interface.h>

// Typedefs
typedef std::map<std::string, std::map<std::string, std::string>> HttpInput;
typedef std::string HttpOutput;

// Send results to user
bool SendResultsToUser(
    HttpOutput& out,
    long& status_code,
    std::string& mime_type,
    const std::string& sResultsID,
    bool bKeepResults);

// Check required method
bool CheckRequiredMethod(
    const HttpInput& http_input,
    HttpOutput& out,
    long& status_code,
    std::string& mime_type,
    const std::string& sMethod);

// Get optional parameter
template <class T>
void GetOptionalParameter(
    const HttpInput& http_input,
    const std::string& sMethod,
    const std::string& sParam,
    T& result);

// Get required parameter
template <class T>
bool GetRequiredParameter(
    const HttpInput& http_input,
    HttpOutput& out,
    long& status_code,
    std::string& mime_type,
    const std::string& sMethod,
    const std::string& sParam,
    T& result);

// Parse http request and return the results to show
void Handle_RunModuleFile(const HttpInput& http_input, HttpOutput& out, long& status_code, std::string& mime_type);
void Handle_RunModuleFileResults(const HttpInput& http_input, HttpOutput& out, long& status_code, std::string& mime_type);
void Handle_RunModuleCommand(const HttpInput& http_input, HttpOutput& out, long& status_code, std::string& mime_type);
void Handle_RunModuleCommandResults(const HttpInput& http_input, HttpOutput& out, long& status_code, std::string& mime_type);
void Handle_ClearModuleResult(const HttpInput& http_input, HttpOutput& out, long& status_code, std::string& mime_type);
void Handle_ClearAllModuleResults(const HttpInput& http_input, HttpOutput& out, long& status_code, std::string& mime_type);
void Handle_DoesModuleResultExist(const HttpInput& http_input, HttpOutput& out, long& status_code, std::string& mime_type);
void Handle_GetModuleResultSize(const HttpInput& http_input, HttpOutput& out, long& status_code, std::string& mime_type);
void Handle_GetModuleResults(const HttpInput& http_input, HttpOutput& out, long& status_code, std::string& mime_type);

#endif
