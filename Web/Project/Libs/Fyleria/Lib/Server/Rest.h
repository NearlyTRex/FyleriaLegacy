// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#ifndef _GECKO_REST_H_
#define _GECKO_REST_H_

// External includes
#include <pistache/http.h>
#include <pistache/router.h>
#include <pistache/endpoint.h>

// Internal includes
#include <Utility/TypesSimple.h>
#include <Utility/TypesEnum.h>
#include <Utility/IndexedString.h>
#include <Utility/Singleton.h>

namespace Gecko
{

// Typedefs
typedef Pistache::Address HttpAddress;
typedef Pistache::Http::Endpoint HttpEndpoint;
typedef Pistache::Http::Request HttpRequest;
typedef Pistache::Http::Handler HttpHandler;
typedef Pistache::Http::Code HttpCode;
typedef Pistache::Http::ResponseWriter HttpResponseWriter;
typedef Pistache::Rest::Router RestRouter;
typedef Pistache::Rest::Request RestRequest;

// Defines
#define RestOptionsRoute                            Pistache::Rest::Routes::Options
#define RestPostRoute                               Pistache::Rest::Routes::Post
#define RestGetRoute                                Pistache::Rest::Routes::Get
#define RestBindRoute                               Pistache::Rest::Routes::bind
#define TcpOptionNoDelay                            Pistache::Tcp::Options::NoDelay
#define TcpOptionLinger                             Pistache::Tcp::Options::Linger
#define TcpOptionFastOpen                           Pistache::Tcp::Options::FastOpen
#define TcpOptionQuickAck                           Pistache::Tcp::Options::QuickAck
#define TcpOptionReuseAddr                          Pistache::Tcp::Options::ReuseAddr
#define TcpOptionReverseLookup                      Pistache::Tcp::Options::ReverseLookup
#define TcpOptionInstallSignalHandler               Pistache::Tcp::Options::InstallSignalHandler
#define HttpServeFile                               Pistache::Http::serveFile
#define HttpMakeHandler                             Pistache::Http::make_handler
#define HttpMethodGet                               Pistache::Http::Method::Get
#define HttpMethodPost                              Pistache::Http::Method::Post
#define HttpMethodOptions                           Pistache::Http::Method::Options
#define HttpCodeContinue                            Pistache::Http::Code::Continue
#define HttpCodeSwitching_Protocols                 Pistache::Http::Code::Switching_Protocols
#define HttpCodeProcessing                          Pistache::Http::Code::Processing
#define HttpCodeOk                                  Pistache::Http::Code::Ok
#define HttpCodeCreated                             Pistache::Http::Code::Created
#define HttpCodeAccepted                            Pistache::Http::Code::Accepted
#define HttpCodeNonAuthoritativeInformation         Pistache::Http::Code::NonAuthoritative_Information
#define HttpCodeNoContent                           Pistache::Http::Code::No_Content
#define HttpCodeResetContent                        Pistache::Http::Code::Reset_Content
#define HttpCodePartialContent                      Pistache::Http::Code::Partial_Content
#define HttpCodeMultiStatus                         Pistache::Http::Code::MultiStatus
#define HttpCodeAlreadyReported                     Pistache::Http::Code::Already_Reported
#define HttpCodeIMUsed                              Pistache::Http::Code::IM_Used
#define HttpCodeMultipleChoices                     Pistache::Http::Code::Multiple_Choices
#define HttpCodeMovedPermanently                    Pistache::Http::Code::Moved_Permanently
#define HttpCodeFound                               Pistache::Http::Code::Found
#define HttpCodeSeeOther                            Pistache::Http::Code::See_Other
#define HttpCodeNotModified                         Pistache::Http::Code::Not_Modified
#define HttpCodeUseProxy                            Pistache::Http::Code::Use_Proxy
#define HttpCodeTemporaryRedirect                   Pistache::Http::Code::Temporary_Redirect
#define HttpCodePermanentRedirect                   Pistache::Http::Code::Permanent_Redirect
#define HttpCodeBadRequest                          Pistache::Http::Code::Bad_Request
#define HttpCodeUnauthorized                        Pistache::Http::Code::Unauthorized
#define HttpCodePaymentRequired                     Pistache::Http::Code::Payment_Required
#define HttpCodeForbidden                           Pistache::Http::Code::Forbidden
#define HttpCodeNotFound                            Pistache::Http::Code::Not_Found
#define HttpCodeMethodNotAllowed                    Pistache::Http::Code::Method_Not_Allowed
#define HttpCodeNotAcceptable                       Pistache::Http::Code::Not_Acceptable
#define HttpCodeProxyAuthenticationRequired         Pistache::Http::Code::Proxy_Authentication_Required
#define HttpCodeRequestTimeout                      Pistache::Http::Code::Request_Timeout
#define HttpCodeConflict                            Pistache::Http::Code::Conflict
#define HttpCodeGone                                Pistache::Http::Code::Gone
#define HttpCodeLengthRequired                      Pistache::Http::Code::Length_Required
#define HttpCodePreconditionFailed                  Pistache::Http::Code::Precondition_Failed
#define HttpCodeRequestEntityTooLarge               Pistache::Http::Code::Request_Entity_Too_Large
#define HttpCodeRequestURITooLong                   Pistache::Http::Code::RequestURI_Too_Long
#define HttpCodeUnsupportedMediaType                Pistache::Http::Code::Unsupported_Media_Type
#define HttpCodeRequestedRangeNotSatisfiable        Pistache::Http::Code::Requested_Range_Not_Satisfiable
#define HttpCodeExpectationFailed                   Pistache::Http::Code::Expectation_Failed
#define HttpCodeMisdirectedRequest                  Pistache::Http::Code::Misdirected_Request
#define HttpCodeUnprocessableEntity                 Pistache::Http::Code::Unprocessable_Entity
#define HttpCodeLocked                              Pistache::Http::Code::Locked
#define HttpCodeFailedDependency                    Pistache::Http::Code::Failed_Dependency
#define HttpCodeUpgradeRequired                     Pistache::Http::Code::Upgrade_Required
#define HttpCodePreconditionRequired                Pistache::Http::Code::Precondition_Required
#define HttpCodeTooManyRequests                     Pistache::Http::Code::Too_Many_Requests
#define HttpCodeRequestHeaderFieldsTooLarge         Pistache::Http::Code::Request_Header_Fields_Too_Large
#define HttpCodeConnectionClosedWithoutResponse     Pistache::Http::Code::Connection_Closed_Without_Response
#define HttpCodeUnavailableForLegalReasons          Pistache::Http::Code::Unavailable_For_Legal_Reasons
#define HttpCodeClientClosedRequest                 Pistache::Http::Code::Client_Closed_Request
#define HttpCodeInternalServerError                 Pistache::Http::Code::Internal_Server_Error
#define HttpCodeNotImplemented                      Pistache::Http::Code::Not_Implemented
#define HttpCodeBadGateway                          Pistache::Http::Code::Bad_Gateway
#define HttpCodeServiceUnavailable                  Pistache::Http::Code::Service_Unavailable
#define HttpCodeGatewayTimeout                      Pistache::Http::Code::Gateway_Timeout
#define HttpCodeHTTPVersionNotSupported             Pistache::Http::Code::HTTP_Version_Not_Supported
#define HttpCodeVariantAlsoNegotiates               Pistache::Http::Code::Variant_Also_Negotiates
#define HttpCodeInsufficientStorage                 Pistache::Http::Code::Insufficient_Storage
#define HttpCodeLoopDetected                        Pistache::Http::Code::Loop_Detected
#define HttpCodeNotExtended                         Pistache::Http::Code::Not_Extended
#define HttpCodeNetworkAuthenticationRequired       Pistache::Http::Code::Network_Authentication_Required
#define HttpCodeNetworkConnectTimeoutError          Pistache::Http::Code::Network_Connect_Timeout_Error
#define HttpHeaderAllow                             Pistache::Http::Header::Allow
#define HttpHeaderAccept                            Pistache::Http::Header::Accept
#define HttpHeaderAccessControlAllowOrigin          Pistache::Http::Header::AccessControlAllowOrigin
#define HttpHeaderAccessControlAllowMethods         Pistache::Http::Header::AccessControlAllowMethods
#define HttpHeaderAccessControlAllowHeaders         Pistache::Http::Header::AccessControlAllowHeaders
#define HttpHeaderCacheControl                      Pistache::Http::Header::CacheControl
#define HttpHeaderConnection                        Pistache::Http::Header::Connection
#define HttpHeaderEncodingHeader                    Pistache::Http::Header::EncodingHeader
#define HttpHeaderContentEncoding                   Pistache::Http::Header::ContentEncoding
#define HttpHeaderTransferEncoding                  Pistache::Http::Header::TransferEncoding
#define HttpHeaderContentLength                     Pistache::Http::Header::ContentLength
#define HttpHeaderContentType                       Pistache::Http::Header::ContentType
#define HttpHeaderDate                              Pistache::Http::Header::Date
#define HttpHeaderExpect                            Pistache::Http::Header::Expect
#define HttpHeaderHost                              Pistache::Http::Header::Host
#define HttpHeaderLocation                          Pistache::Http::Header::Location
#define HttpHeaderServer                            Pistache::Http::Header::Server
#define HttpHeaderUserAgent                         Pistache::Http::Header::UserAgent
#define HttpHeaderRaw                               Pistache::Http::Header::Raw

// Custom http handler
class CustomHttpHandler : public HttpHandler
{
    HTTP_PROTOTYPE(CustomHttpHandler)

public:

    // Constructor
    CustomHttpHandler();

    // Request handler
    void onRequest(const HttpRequest& request, HttpResponseWriter response);

private:

    // Callbacks
    void DoOptions_RequestToRun(const HttpRequest& request, HttpResponseWriter& response);
    void DoPost_RunModuleFile(const HttpRequest& request, HttpResponseWriter& response);
    void DoPost_RunModuleFileResults(const HttpRequest& request, HttpResponseWriter& response);
    void DoPost_RunModuleCommand(const HttpRequest& request, HttpResponseWriter& response);
    void DoPost_RunModuleCommandResults(const HttpRequest& request, HttpResponseWriter& response);
    void DoPost_ClearModuleResult(const HttpRequest& request, HttpResponseWriter& response);
    void DoPost_ClearAllModuleResults(const HttpRequest& request, HttpResponseWriter& response);
    void DoGet_DoesModuleResultExist(const HttpRequest& request, HttpResponseWriter& response);
    void DoGet_GetModuleResultSize(const HttpRequest& request, HttpResponseWriter& response);
    void DoGet_GetModuleResults(const HttpRequest& request, HttpResponseWriter& response);
    void DoGet_ServeFile(const HttpRequest& request, HttpResponseWriter& response);

    // Handle response
    void HandleResponse(const HttpCode& code, HttpResponseWriter& response, const String& sResponse);

    // Send results back to the user
    Bool SendResultsToUser(HttpResponseWriter& response, const String& sResultsID, Bool bKeepResults);
    Bool SendFileToUser(HttpResponseWriter& response, const String& sFile);

    // Get optional parameter
    template <class T>
    void GetOptionalParameter(const HttpRequest& request, const String& sParam, T& result) const;

    // Get required parameter
    template <class T>
    Bool GetRequiredParameter(const HttpRequest& request, HttpResponseWriter& response, const String& sParam, T& result);
};

// Rest server
class RestServer : public Singleton<RestServer>
{
public:

    // Constructor for web socket server
    RestServer();

    // Set hostname/root/port/threads
    void SetHostname(const String& sHost);
    void SetWebRoot(const String& sWebRoot);
    void SetPort(Int iPort);
    void SetThreadCount(Int iThreadCount);

    // Get hostname/root/port/threads
    const String& GetHostname() const;
    const String& GetWebRoot() const;
    Int GetPort() const;
    Int GetThreadCount() const;

    // Reset server
    void Reset();

    // Start server
    void Start();

    // Stop server
    void Stop();

private:

    // Host name
    String m_sHost;

    // Web root
    String m_sWebRoot;

    // Port number
    Int m_iPort;

    // Thread count
    Int m_iThreadCount;

    // Whether server is closing
    Bool m_bClosing;

    // Whether server has been shutdown
    Bool m_bShutdown;

    // Endpoint
    STDSharedPtr<HttpEndpoint> m_pEndpoint;
};

};

#endif
