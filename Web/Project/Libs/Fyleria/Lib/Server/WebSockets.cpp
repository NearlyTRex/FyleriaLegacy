// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#include "Server/WebSockets.h"
#include "Utility/Macros.h"
#include "Interface/Interface.h"

namespace Gecko
{

WebsocketServer::WebsocketServer()
    : m_sHost()
    , m_iPort(-1)
    , m_bClosing(false)
    , m_bShutdown(false)
    , m_pServer()
    , m_ConnectionMap()
    , m_ConnectionMutex()
{
}

void WebsocketServer::SetHostname(const String& sHost)
{
    m_sHost = sHost;
}

void WebsocketServer::SetPort(Int iPort)
{
    m_iPort = iPort;
}

void WebsocketServer::Reset()
{
    LOG_STATEMENT("Resetting server");
    m_pServer = STDMakeSharedPtr<WebsocketAsioServer>();
}

void WebsocketServer::Start()
{
    // Check that server exists
    if (!m_pServer)
    {
        return;
    }

    // Setting up server
    LOG_STATEMENT("Setting up server");

    // Set channels
    m_pServer->clear_access_channels(WebsocketAccessLogAll);
    m_pServer->set_access_channels(WebsocketAccessLogAll);
    m_pServer->clear_error_channels(WebsocketErrorLogAll);
    m_pServer->set_error_channels(WebsocketErrorLogAll);

    // Initialize ASIO
    m_pServer->init_asio();
    m_pServer->set_reuse_addr(true);

    // Set handlers
    m_pServer->set_open_handler(STDBindFunc(&WebsocketServer::OnOpen, this, STDPlaceholder1));
    m_pServer->set_close_handler(STDBindFunc(&WebsocketServer::OnClose, this, STDPlaceholder1));
    m_pServer->set_message_handler(STDBindFunc(&WebsocketServer::OnMessage, this, STDPlaceholder1, STDPlaceholder2));

    // Start listening
    ASSERT_ERROR(!m_sHost.empty(), "Host cannot be empty");
    ASSERT_ERROR(m_iPort > 0, "Port must be a positive integer");
    m_pServer->listen(m_sHost, STDToString(m_iPort));
    LOG_FORMAT_STATEMENT("Now serving at ws://%s:%d\n", m_sHost.c_str(), m_iPort);

    // Start the server accept loop
    m_pServer->start_accept();
    m_pServer->run();
    m_bShutdown = false;
}

void WebsocketServer::Stop()
{
    // Check that server exists
    if (!m_pServer)
    {
        return;
    }

    // Halt server
    m_pServer->stop();
    LOG_STATEMENT("Halting server...");
    m_bShutdown = true;
    m_bClosing = false;
}

void WebsocketServer::OnOpen(WebsocketConnectionHandlePtr pHandle)
{
    // Lock access
    STDLockGuard<STDMutex> lock(m_ConnectionMutex);

    // Stop from closing
    m_bClosing = false;

    // Add connection to map
    auto pSharedHandle = pHandle.lock();
    WebsocketRawConnectionPtr pConnection = pSharedHandle.get();
    LOG_FORMAT_STATEMENT("Opening connection to %p\n", (void*)pConnection);
    m_ConnectionMap[pConnection] = pHandle;
}

void WebsocketServer::OnClose(WebsocketConnectionHandlePtr pHandle)
{
    // Lock access
    STDLockGuard<STDMutex> lock(m_ConnectionMutex);

    // Start closing
    m_bClosing = true;

    // Remove connection from map
    auto pSharedHandle = pHandle.lock();
    WebsocketRawConnectionPtr pConnection = pSharedHandle.get();
    LOG_FORMAT_STATEMENT("Closing connection to %p\n", (void*)pConnection);
    m_ConnectionMap.erase(pConnection);
}

void WebsocketServer::OnMessage(WebsocketConnectionHandlePtr pHandle, WebsocketAsioMessagePtr pMessage)
{
    // Ignore if closing
    if (m_bClosing)
    {
        return;
    }

    // Lock access
    STDLockGuard<STDMutex> lock(m_ConnectionMutex);

    // Parse message payload
    Json jsonData = JsonParse(pMessage->get_payload());
    auto sJsonDataStr = jsonData.dump();
    auto pSharedHandle = pHandle.lock();
    WebsocketRawConnectionPtr pConnection = pSharedHandle.get();
    LOG_FORMAT_STATEMENT("Handing message to %p: %s\n", (void*)pConnection, sJsonDataStr.c_str());

    // Output json
    Json outputJsonData;

    // Built-in functions
    outputJsonData = HandleBuiltinFunctionCall(pHandle, jsonData);

    // Builtin function was handled
    if (outputJsonData["is_handled"] == true)
    {
        LOG_FORMAT_STATEMENT("Message %p was handled by built-in function call\n", (void*)pMessage.get());
        SendPayload(pHandle, outputJsonData);
        return;
    }

    // Module functions
    try
    {
        outputJsonData = HandleModuleFunctionCall(pHandle, jsonData);
    }
    catch (STDGeneralError& error)
    {
        outputJsonData["error_code"] = error.code();
        outputJsonData["error_message"] = error.what();
        outputJsonData["is_handled"] = true;
    }

    // Module function was handled
    if (outputJsonData["is_handled"] == true)
    {
        LOG_FORMAT_STATEMENT("Message %p was handled by module function call\n", (void*)pMessage.get());
        SendPayload(pHandle, outputJsonData);
        return;
    }

    // Message was not handled
    LOG_FORMAT_STATEMENT("Message %p was not handled\n", (void*)pMessage.get());
}

void WebsocketServer::SendPayload(WebsocketRawConnectionPtr pConnection, const Json& jsonData)
{
    // Ignore if closing
    if (m_bClosing)
    {
        return;
    }

    // Find connection handle
    auto it = m_ConnectionMap.find(pConnection);
    if (it == m_ConnectionMap.end())
    {
        return;
    }

    // Send payload
    SendPayload(it->second, jsonData);
}

void WebsocketServer::SendPayload(WebsocketConnectionHandlePtr pHandle, const Json& jsonData)
{
    // Ignore if closing
    if (m_bClosing)
    {
        return;
    }

    // Try to send original payload
    try
    {
        auto sJsonDataStr = jsonData.dump();
        auto pSharedHandle = pHandle.lock();
        WebsocketRawConnectionPtr pConnection = pSharedHandle.get();
        LOG_FORMAT_STATEMENT("Sending message to %p: %s\n", (void*)pConnection, sJsonDataStr.c_str());
        m_pServer->send(pHandle, sJsonDataStr, WebsocketFrameOpcodeText);
    }
    catch (WebsocketException& e)
    {
        ERROR_FORMAT_STATEMENT("Websocket error %d : %s\n", e.code().value(), e.what());
        ERROR_FORMAT_STATEMENT("Original payload: \n%s\n", jsonData.dump(4).c_str());
    }
}

const WebsocketConnectionMap& WebsocketServer::GetConnectionMap() const
{
    return m_ConnectionMap;
}

Json WebsocketServer::HandleBuiltinFunctionCall(WebsocketConnectionHandlePtr pHandle, const Json& jsonData)
{
    // Create output data
    Json outputData(jsonData);
    outputData["is_response"] = true;
    outputData["is_handled"] = false;
    outputData["error_code"] = 0;
    outputData["error_message"] = "";
    outputData["return_value"] = 0;
    outputData["results"] = "";

    // Get function name
    const String sFunctionName = jsonData["function"];
    if (sFunctionName.empty())
    {
        LOG_STATEMENT("No built-in function name specified");
        outputData["error_code"] = (+WebsocketErrorType::NoFunctionSpecified)._to_integral();
        outputData["error_message"] = (+WebsocketErrorType::NoFunctionSpecified)._to_string();
        return outputData;
    }

    // Shutdown
    if (sFunctionName == "shutdown")
    {
        // Halt server
        Stop();
        outputData["is_handled"] = true;
        return outputData;
    }
    return outputData;
}

Json WebsocketServer::HandleModuleFunctionCall(WebsocketConnectionHandlePtr pHandle, const Json& jsonData)
{
    // Create output data
    Json outputData(jsonData);
    outputData["is_response"] = true;
    outputData["is_handled"] = false;
    outputData["error_code"] = 0;
    outputData["error_message"] = "";
    outputData["return_value"] = 0;
    outputData["results"] = "";

    // Get function name
    const String sFunctionName = jsonData["function"];
    if (sFunctionName.empty())
    {
        LOG_STATEMENT("No module function name specified");
        outputData["error_code"] = (+WebsocketErrorType::NoFunctionSpecified)._to_integral();
        outputData["error_message"] = (+WebsocketErrorType::NoFunctionSpecified)._to_string();
        return outputData;
    }

    // Get arguments
    const Json functionArguments = jsonData["args"];
    const Bool bHaveFile = (functionArguments.find("file") != functionArguments.end());
    const Bool bHaveCommand = (functionArguments.find("command") != functionArguments.end());
    const Bool bHaveResultsId = (functionArguments.find("results_id") != functionArguments.end());
    const Bool bHaveKeepResults = (functionArguments.find("keep_results") != functionArguments.end());
    const String sInputFile = (bHaveFile) ? functionArguments["file"] : "";
    const String sInputCommand = (bHaveCommand) ? functionArguments["command"] : "";
    const String sInputResultsId = (bHaveResultsId) ? functionArguments["results_id"] : "";
    const Bool bKeepResults = (bHaveKeepResults) ? functionArguments["keep_results"].get<Bool>() : false;

    // Run module file
    if (sFunctionName == "run_module_file")
    {
        if (!bHaveFile)
        {
            LOG_STATEMENT("Missing required arguments");
            outputData["error_code"] = (+WebsocketErrorType::MissingRequiredArguments)._to_integral();
            outputData["error_message"] = (+WebsocketErrorType::MissingRequiredArguments)._to_string();
            return outputData;
        }

        LOG_STATEMENT("Calling DLL_RunModuleFile");
        bool return_value = DLL_RunModuleFile(sInputFile.c_str());
        outputData["return_value"] = return_value;
        outputData["is_handled"] = true;
        return outputData;
    }

    // Run module file and get results
    else if (sFunctionName == "run_module_file_results")
    {
        if (!bHaveFile || !bHaveCommand)
        {
            LOG_STATEMENT("Missing required arguments");
            outputData["error_code"] = (+WebsocketErrorType::MissingRequiredArguments)._to_integral();
            outputData["error_message"] = (+WebsocketErrorType::MissingRequiredArguments)._to_string();
            return outputData;
        }

        LOG_STATEMENT("Calling DLL_RunModuleFileResults");
        bool return_value = DLL_RunModuleFileResults(sInputFile.c_str(), sInputResultsId.c_str());
        if (!return_value)
        {
            outputData["return_value"] = return_value;
            outputData["is_handled"] = true;
            outputData["results"] = "";
            return outputData;
        }

        LOG_STATEMENT("Calling DLL_GetModuleResultSize");
        unsigned int uResultsLen = DLL_GetModuleResultSize(sInputResultsId.c_str());
        char sResultsStr[uResultsLen + 1] = {0};

        LOG_STATEMENT("Calling DLL_GetModuleResults");
        return_value = DLL_GetModuleResults(sInputResultsId.c_str(), sResultsStr, uResultsLen);
        outputData["return_value"] = return_value;
        outputData["is_handled"] = true;
        outputData["results"] = String(sResultsStr);

        if (!bKeepResults)
        {
            LOG_STATEMENT("Calling DLL_ClearModuleResult");
            DLL_ClearModuleResult(sInputResultsId.c_str());
        }
        return outputData;
    }

    // Run module file
    else if (sFunctionName == "run_module_command")
    {
        if (!bHaveCommand)
        {
            LOG_STATEMENT("Missing required arguments");
            outputData["error_code"] = (+WebsocketErrorType::MissingRequiredArguments)._to_integral();
            outputData["error_message"] = (+WebsocketErrorType::MissingRequiredArguments)._to_string();
            return outputData;
        }

        LOG_STATEMENT("Calling DLL_RunModuleCommand");
        bool return_value = DLL_RunModuleCommand(sInputCommand.c_str());
        outputData["return_value"] = return_value;
        outputData["is_handled"] = true;
        return outputData;
    }

    // Run module file and get results
    else if (sFunctionName == "run_module_command_results")
    {
        if (!bHaveCommand || !bHaveResultsId)
        {
            LOG_STATEMENT("Missing required arguments");
            outputData["error_code"] = (+WebsocketErrorType::MissingRequiredArguments)._to_integral();
            outputData["error_message"] = (+WebsocketErrorType::MissingRequiredArguments)._to_string();
            return outputData;
        }

        LOG_STATEMENT("Calling DLL_RunModuleCommandResults");
        bool return_value = DLL_RunModuleCommandResults(sInputCommand.c_str(), sInputResultsId.c_str());
        if (!return_value)
        {
            outputData["return_value"] = return_value;
            outputData["is_handled"] = true;
            outputData["results"] = "";
            return outputData;
        }

        LOG_STATEMENT("Calling DLL_GetModuleResultSize");
        unsigned int uResultsLen = DLL_GetModuleResultSize(sInputResultsId.c_str());
        char sResultsStr[uResultsLen + 1] = {0};

        LOG_STATEMENT("Calling DLL_GetModuleResults");
        return_value = DLL_GetModuleResults(sInputResultsId.c_str(), sResultsStr, uResultsLen);
        outputData["return_value"] = return_value;
        outputData["is_handled"] = true;
        outputData["results"] = String(sResultsStr);

        if (!bKeepResults)
        {
            LOG_STATEMENT("Calling DLL_ClearModuleResult");
            DLL_ClearModuleResult(sInputResultsId.c_str());
        }
        return outputData;
    }

    // Clear module results
    else if (sFunctionName == "clear_module_results")
    {
        if (!bHaveResultsId)
        {
            LOG_STATEMENT("Missing required arguments");
            outputData["error_code"] = (+WebsocketErrorType::MissingRequiredArguments)._to_integral();
            outputData["error_message"] = (+WebsocketErrorType::MissingRequiredArguments)._to_string();
            return outputData;
        }

        LOG_STATEMENT("Calling DLL_ClearModuleResult");
        DLL_ClearModuleResult(sInputResultsId.c_str());
        outputData["is_handled"] = true;
        return outputData;
    }

    // Clear all module results
    else if (sFunctionName == "clear_all_module_results")
    {
        LOG_STATEMENT("Calling DLL_ClearAllModuleResults");
        DLL_ClearAllModuleResults();
        outputData["is_handled"] = true;
        return outputData;
    }

    // Does module result exist
    else if (sFunctionName == "does_module_result_exist")
    {
        if (!bHaveResultsId)
        {
            LOG_STATEMENT("Missing required arguments");
            outputData["error_code"] = (+WebsocketErrorType::MissingRequiredArguments)._to_integral();
            outputData["error_message"] = (+WebsocketErrorType::MissingRequiredArguments)._to_string();
            return outputData;
        }

        LOG_STATEMENT("Calling DLL_DoesModuleResultExist");
        bool return_value = DLL_DoesModuleResultExist(sInputResultsId.c_str());
        outputData["return_value"] = return_value;
        outputData["is_handled"] = true;
        return outputData;
    }

    // Get module result size
    else if (sFunctionName == "get_module_result_size")
    {
        if (!bHaveResultsId)
        {
            LOG_STATEMENT("Missing required arguments");
            outputData["error_code"] = (+WebsocketErrorType::MissingRequiredArguments)._to_integral();
            outputData["error_message"] = (+WebsocketErrorType::MissingRequiredArguments)._to_string();
            return outputData;
        }

        LOG_STATEMENT("Calling DLL_GetModuleResultSize");
        unsigned int return_value = DLL_GetModuleResultSize(sInputResultsId.c_str());
        outputData["return_value"] = return_value;
        outputData["is_handled"] = true;
        return outputData;
    }

    // Get module results
    else if (sFunctionName == "get_module_results")
    {
        if (!bHaveResultsId)
        {
            LOG_STATEMENT("Missing required arguments");
            outputData["error_code"] = (+WebsocketErrorType::MissingRequiredArguments)._to_integral();
            outputData["error_message"] = (+WebsocketErrorType::MissingRequiredArguments)._to_string();
            return outputData;
        }

        LOG_STATEMENT("Calling DLL_GetModuleResultSize");
        unsigned int uResultsLen = DLL_GetModuleResultSize(sInputResultsId.c_str());
        char sResultsStr[uResultsLen + 1] = {0};

        LOG_STATEMENT("Calling DLL_GetModuleResults");
        bool return_value = DLL_GetModuleResults(sInputResultsId.c_str(), sResultsStr, uResultsLen);
        outputData["return_value"] = return_value;
        outputData["is_handled"] = true;
        outputData["results"] = String(sResultsStr);
        return outputData;
    }

    // Verify module data
    else if (sFunctionName == "verify_module_data")
    {
        LOG_STATEMENT("Calling DLL_VerifyModuleData");
        DLL_VerifyModuleData();
        outputData["is_handled"] = true;
        return outputData;
    }
    return outputData;
}

};
