// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#include "RequestParser.h"
#include "Logging.h"

bool SendResultsToUser(
    HttpOutput& http_output,
    long& status_code,
    std::string& mime_type,
    const std::string& sResultsID,
    bool bKeepResults)
{
    // Get results size
    LOG_STATEMENT("Calling DLL_GetModuleResultSize");
    unsigned int uResultsLen = DLL_GetModuleResultSize(sResultsID.c_str());
    char sResultsStr[uResultsLen + 1] = {0};
    if(!uResultsLen)
    {
        std::string sMessage = (boost::format("The result size of '%1%' was zero.") % uResultsLen).str();
        http_output += sMessage;
        status_code = 409;
        mime_type = "text/plain";
        return false;
    }

    // Get result
    LOG_STATEMENT("Calling DLL_GetModuleResults");
    bool return_value = DLL_GetModuleResults(sResultsID.c_str(), sResultsStr, uResultsLen);
    if(!return_value)
    {
        std::string sMessage = (boost::format("Failed retrieving result for '%1%'.") % sResultsID).str();
        http_output += sMessage;
        status_code = 409;
        mime_type = "text/plain";
        return false;
    }

    // Handle results
    std::string sResults = sResultsStr;
    if(!bKeepResults)
    {
        LOG_STATEMENT("Calling DLL_ClearModuleResult");
        DLL_ClearModuleResult(sResultsID.c_str());
    }

    // Send results
    http_output += sResults;
    status_code = 200;
    mime_type = "application/json";
    return true;
}

bool CheckRequiredMethod(
    const HttpInput& http_input,
    HttpOutput& http_output,
    long& status_code,
    std::string& mime_type,
    const std::string& sMethod)
{
    if(!http_input.count(sMethod))
    {
        std::string sMessage = (boost::format("Missing required method '%1%'.") % sMethod).str();
        http_output += sMessage;
        status_code = 400;
        mime_type = "text/plain";
        return false;
    }
    return true;
}

template <class T>
void GetOptionalParameter(
    const HttpInput& http_input,
    const std::string& sMethod,
    const std::string& sParam,
    T& result)
{
    // Determine parameter location
    bool bParamInQuery = (http_input.count(sMethod) > 0 && http_input.at(sMethod).count(sParam) > 0);

    // Optional parameter
    if(bParamInQuery)
    {
        result = boost::lexical_cast<T>(http_input.at(sMethod).at(sParam));
    }
}

template <class T>
bool GetRequiredParameter(
    const HttpInput& http_input,
    HttpOutput& http_output,
    long& status_code,
    std::string& mime_type,
    const std::string& sMethod,
    const std::string& sParam,
    T& result)
{
    // Determine parameter location
    bool bParamInQuery = (http_input.count(sMethod) > 0 && http_input.at(sMethod).count(sParam) > 0);

    // Required parameter
    if(bParamInQuery)
    {
        result = boost::lexical_cast<T>(http_input.at(sMethod).at(sParam));
        return true;
    }

    // Missing parameter so it must be a bad request
    std::string sMessage = (boost::format("Missing required parameter '%1%'.") % sParam).str();
    LOG_FORMAT_STATEMENT("%s\n", sMessage.c_str());
    http_output += sMessage;
    status_code = 400;
    mime_type = "text/plain";
    return false;
}

void Handle_RunModuleFile(
    const HttpInput& http_input,
    HttpOutput& http_output,
    long& status_code,
    std::string& mime_type)
{
    // Required method
    if(!CheckRequiredMethod(http_input, http_output, status_code, mime_type, "POST"))
    {
        return;
    }

    // Get input
    std::string sInputFile = "";
    if(!GetRequiredParameter(http_input, http_output, status_code, mime_type, "POST", "file", sInputFile))
    {
        return;
    }

    // Run method
    LOG_STATEMENT("Calling DLL_RunModuleFile");
    bool return_value = DLL_RunModuleFile(sInputFile.c_str());
    if(!return_value)
    {
        std::string sMessage = (boost::format("Could not run file '%1%'.") % sInputFile).str();
        http_output += sMessage;
        status_code = 400;
        mime_type = "text/plain";
        return;
    }

    // Send results
    nlohmann::json return_json;
    return_json["return_value"] = return_value;
    http_output += return_json.dump();
    status_code = 200;
    mime_type = "application/json";
}

void Handle_RunModuleFileResults(
    const HttpInput& http_input,
    HttpOutput& http_output,
    long& status_code,
    std::string& mime_type)
{
    // Required method
    if(!CheckRequiredMethod(http_input, http_output, status_code, mime_type, "POST"))
    {
        return;
    }

    // Get input
    std::string sInputFile = "";
    std::string sInputResultsId = "";
    if(!GetRequiredParameter(http_input, http_output, status_code, mime_type, "POST", "file", sInputFile) ||
       !GetRequiredParameter(http_input, http_output, status_code, mime_type, "POST", "results_id", sInputResultsId))
    {
        return;
    }

    // Get keep results
    bool bKeepResults = false;
    GetOptionalParameter(http_input, "POST", "keep_results", bKeepResults);

    // Run method
    LOG_STATEMENT("Calling DLL_RunModuleFileResults");
    bool return_value = DLL_RunModuleFileResults(sInputFile.c_str(), sInputResultsId.c_str());
    if(!return_value)
    {
        std::string sMessage = (boost::format("Could not run file '%1%'.") % sInputFile).str();
        http_output += sMessage;
        status_code = 400;
        mime_type = "text/plain";
        return;
    }

    // Send results
    SendResultsToUser(http_output, status_code, mime_type, sInputResultsId, bKeepResults);
}

void Handle_RunModuleCommand(
    const HttpInput& http_input,
    HttpOutput& http_output,
    long& status_code,
    std::string& mime_type)
{
    // Required method
    if(!CheckRequiredMethod(http_input, http_output, status_code, mime_type, "POST"))
    {
        return;
    }

    // Get input
    std::string sInputCommand = "";
    if(!GetRequiredParameter(http_input, http_output, status_code, mime_type, "POST", "command", sInputCommand))
    {
        return;
    }

    // Run method
    LOG_STATEMENT("Calling DLL_RunModuleCommand");
    bool return_value = DLL_RunModuleCommand(sInputCommand.c_str());
    if(!return_value)
    {
        std::string sMessage = (boost::format("Could not run command '%1%'.") % sInputCommand).str();
        http_output += sMessage;
        status_code = 400;
        mime_type = "text/plain";
        return;
    }

    // Send results
    nlohmann::json return_json;
    return_json["return_value"] = return_value;
    http_output += return_json.dump();
    status_code = 200;
    mime_type = "application/json";
}

void Handle_RunModuleCommandResults(
    const HttpInput& http_input,
    HttpOutput& http_output,
    long& status_code,
    std::string& mime_type)
{
    // Required method
    if(!CheckRequiredMethod(http_input, http_output, status_code, mime_type, "POST"))
    {
        return;
    }

    // Get input
    std::string sInputCommand = "";
    std::string sInputResultsId = "";
    if(!GetRequiredParameter(http_input, http_output, status_code, mime_type, "POST", "command", sInputCommand) ||
       !GetRequiredParameter(http_input, http_output, status_code, mime_type, "POST", "results_id", sInputResultsId))
    {
        return;
    }

    // Get keep results
    bool bKeepResults = false;
    GetOptionalParameter(http_input, "POST", "keep_results", bKeepResults);

    // Run method
    LOG_STATEMENT("Calling DLL_RunModuleCommandResults");
    bool return_value = DLL_RunModuleCommandResults(sInputCommand.c_str(), sInputResultsId.c_str());
    if(!return_value)
    {
        std::string sMessage = (boost::format("Could not run command '%1%'.") % sInputCommand).str();
        http_output += sMessage;
        status_code = 400;
        mime_type = "text/plain";
        return;
    }

    // Send results
    SendResultsToUser(http_output, status_code, mime_type, sInputResultsId, bKeepResults);
}

void Handle_ClearModuleResult(
    const HttpInput& http_input,
    HttpOutput& http_output,
    long& status_code,
    std::string& mime_type)
{
    // Required method
    if(!CheckRequiredMethod(http_input, http_output, status_code, mime_type, "POST"))
    {
        return;
    }

    // Get input
    std::string sInputResultsId = "";
    if(!GetRequiredParameter(http_input, http_output, status_code, mime_type, "POST", "results_id", sInputResultsId))
    {
        return;
    }

    // Run method
    LOG_STATEMENT("Calling DLL_ClearModuleResult");
    DLL_ClearModuleResult(sInputResultsId.c_str());

    // Send results
    nlohmann::json return_json;
    return_json["return_value"] = true;
    http_output += return_json.dump();
    status_code = 200;
    mime_type = "application/json";
}

void Handle_ClearAllModuleResults(
    const HttpInput& http_input,
    HttpOutput& http_output,
    long& status_code,
    std::string& mime_type)
{
    // Required method
    if(!CheckRequiredMethod(http_input, http_output, status_code, mime_type, "POST"))
    {
        return;
    }

    // Run method
    LOG_STATEMENT("Calling DLL_ClearAllModuleResults");
    DLL_ClearAllModuleResults();

    // Send results
    nlohmann::json return_json;
    return_json["return_value"] = true;
    http_output += return_json.dump();
    status_code = 200;
    mime_type = "application/json";
}

void Handle_DoesModuleResultExist(
    const HttpInput& http_input,
    HttpOutput& http_output,
    long& status_code,
    std::string& mime_type)
{
    // Required method
    if(!CheckRequiredMethod(http_input, http_output, status_code, mime_type, "GET"))
    {
        return;
    }

    // Get input
    std::string sInputResultsId = "";
    if(!GetRequiredParameter(http_input, http_output, status_code, mime_type, "GET", "results_id", sInputResultsId))
    {
        return;
    }

    // Run method
    LOG_STATEMENT("Calling DLL_DoesModuleResultExist");
    bool return_value = DLL_DoesModuleResultExist(sInputResultsId.c_str());

    // Send results
    nlohmann::json return_json;
    return_json["return_value"] = return_value;
    http_output += return_json.dump();
    status_code = 200;
    mime_type = "application/json";
}

void Handle_GetModuleResultSize(
    const HttpInput& http_input,
    HttpOutput& http_output,
    long& status_code,
    std::string& mime_type)
{
    // Required method
    if(!CheckRequiredMethod(http_input, http_output, status_code, mime_type, "GET"))
    {
        return;
    }

    // Get input
    std::string sInputResultsId = "";
    if(!GetRequiredParameter(http_input, http_output, status_code, mime_type, "GET", "results_id", sInputResultsId))
    {
        return;
    }

    // Run method
    LOG_STATEMENT("Calling DLL_GetModuleResultSize");
    unsigned int return_value = DLL_GetModuleResultSize(sInputResultsId.c_str());

    // Send results
    nlohmann::json return_json;
    return_json["return_value"] = return_value;
    http_output += return_json.dump();
    status_code = 200;
    mime_type = "application/json";
}

void Handle_GetModuleResults(
    const HttpInput& http_input,
    HttpOutput& http_output,
    long& status_code,
    std::string& mime_type)
{
    // Required method
    if(!CheckRequiredMethod(http_input, http_output, status_code, mime_type, "GET"))
    {
        return;
    }

    // Get input
    std::string sInputResultsId = "";
    if(!GetRequiredParameter(http_input, http_output, status_code, mime_type, "GET", "results_id", sInputResultsId))
    {
        return;
    }

    // Send results
    SendResultsToUser(http_output, status_code, mime_type, sInputResultsId, true);
}
