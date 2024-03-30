// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#ifndef _GECKO_WEBSOCKETS_H_
#define _GECKO_WEBSOCKETS_H_

// External includes
#include <websocketpp/config/boost_config.hpp>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

// Internal includes
#include <Utility/TypesSimple.h>
#include <Utility/TypesEnum.h>
#include <Utility/IndexedString.h>
#include <Utility/Singleton.h>

namespace Gecko
{

// Errors
BETTER_ENUM(WebsocketErrorType, Int,
    None,
    NoFunctionSpecified,
    MissingRequiredArguments
);

// Typedefs
typedef void* WebsocketRawConnectionPtr;
typedef websocketpp::exception WebsocketException;
typedef websocketpp::connection_hdl WebsocketConnectionHandlePtr;
typedef websocketpp::server<websocketpp::config::asio> WebsocketAsioServer;
typedef websocketpp::server<websocketpp::config::asio>::message_ptr WebsocketAsioMessagePtr;
typedef STDMap<WebsocketRawConnectionPtr, WebsocketConnectionHandlePtr> WebsocketConnectionMap;

// Defines
#define WebsocketErrorLogNone               websocketpp::log::elevel::none
#define WebsocketErrorLogDevel              websocketpp::log::elevel::devel
#define WebsocketErrorLogLibrary            websocketpp::log::elevel::library
#define WebsocketErrorLogInfo               websocketpp::log::elevel::info
#define WebsocketErrorLogWarn               websocketpp::log::elevel::warn
#define WebsocketErrorLogRecoverableError   websocketpp::log::elevel::rerror
#define WebsocketErrorLogFatalError         websocketpp::log::elevel::fatal
#define WebsocketErrorLogAll                websocketpp::log::elevel::all
#define WebsocketAccessLogNone              websocketpp::log::alevel::none
#define WebsocketAccessLogConnect           websocketpp::log::alevel::connect
#define WebsocketAccessLogDisconnect        websocketpp::log::alevel::disconnect
#define WebsocketAccessLogControl           websocketpp::log::alevel::control
#define WebsocketAccessLogFrameHeader       websocketpp::log::alevel::frame_header
#define WebsocketAccessLogFramePayload      websocketpp::log::alevel::frame_payload
#define WebsocketAccessLogMessageHeader     websocketpp::log::alevel::message_header
#define WebsocketAccessLogMessagePayload    websocketpp::log::alevel::message_payload
#define WebsocketAccessLogEndpoint          websocketpp::log::alevel::endpoint
#define WebsocketAccessLogDebugHandshake    websocketpp::log::alevel::debug_handshake
#define WebsocketAccessLogDebugClose        websocketpp::log::alevel::debug_close
#define WebsocketAccessLogDevel             websocketpp::log::alevel::devel
#define WebsocketAccessLogApp               websocketpp::log::alevel::app
#define WebsocketAccessLogHTTP              websocketpp::log::alevel::http
#define WebsocketAccessLogFail              websocketpp::log::alevel::fail
#define WebsocketAccessLogAccessCore        websocketpp::log::alevel::access_core
#define WebsocketAccessLogAll               websocketpp::log::alevel::all
#define WebsocketFrameOpcodeContinuation    websocketpp::frame::opcode::continuation
#define WebsocketFrameOpcodeText            websocketpp::frame::opcode::text
#define WebsocketFrameOpcodeBinary          websocketpp::frame::opcode::binary
#define WebsocketFrameOpcodeRSV3            websocketpp::frame::opcode::rsv3
#define WebsocketFrameOpcodeRSV4            websocketpp::frame::opcode::rsv4
#define WebsocketFrameOpcodeRSV5            websocketpp::frame::opcode::rsv5
#define WebsocketFrameOpcodeRSV6            websocketpp::frame::opcode::rsv6
#define WebsocketFrameOpcodeRSV7            websocketpp::frame::opcode::rsv7
#define WebsocketFrameOpcodeClose           websocketpp::frame::opcode::close
#define WebsocketFrameOpcodePing            websocketpp::frame::opcode::ping
#define WebsocketFrameOpcodePong            websocketpp::frame::opcode::pong
#define WebsocketFrameOpcodeControlRSVB     websocketpp::frame::opcode::control_rsvb
#define WebsocketFrameOpcodeControlRSVC     websocketpp::frame::opcode::control_rsvc
#define WebsocketFrameOpcodeControlRSVD     websocketpp::frame::opcode::control_rsvd
#define WebsocketFrameOpcodeControlRSVE     websocketpp::frame::opcode::control_rsve
#define WebsocketFrameOpcodeControlRSVF     websocketpp::frame::opcode::control_rsvf

// Websocket server
class WebsocketServer : public Singleton<WebsocketServer>
{
public:

    // Constructor for web socket server
    WebsocketServer();

    // Set hostname/port
    void SetHostname(const String& sHost);
    void SetPort(Int iPort);

    // Reset server
    void Reset();

    // Start server
    void Start();

    // Stop server
    void Stop();

    // Callback for a connection being opened
    void OnOpen(WebsocketConnectionHandlePtr pHandle);

    // Callback for a connection being closed
    void OnClose(WebsocketConnectionHandlePtr pHandle);

    // Callback for a connection message
    void OnMessage(WebsocketConnectionHandlePtr pHandle, WebsocketAsioMessagePtr pMessage);

    // Send payload
    void SendPayload(WebsocketRawConnectionPtr pConnection, const Json& jsonData);

    // Send payload
    void SendPayload(WebsocketConnectionHandlePtr pHandle, const Json& jsonData);

    // Get connection map
    const WebsocketConnectionMap& GetConnectionMap() const;

private:

    // Handle built-in functions
    Json HandleBuiltinFunctionCall(WebsocketConnectionHandlePtr pHandle, const Json& jsonData);

    // Handle module functions
    Json HandleModuleFunctionCall(WebsocketConnectionHandlePtr pHandle, const Json& jsonData);

    // Host name
    String m_sHost;

    // Port number
    Int m_iPort;

    // Whether server is closing
    Bool m_bClosing;

    // Whether server has been shutdown
    Bool m_bShutdown;

    // ASIO server
    STDSharedPtr<WebsocketAsioServer> m_pServer;

    // Server connection map
    WebsocketConnectionMap m_ConnectionMap;

    // Server connection mutex
    STDMutex m_ConnectionMutex;
};

};

#endif
