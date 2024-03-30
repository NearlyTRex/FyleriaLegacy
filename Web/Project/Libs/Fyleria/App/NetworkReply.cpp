// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#include "NetworkReply.h"
#include "RequestParser.h"

NetworkReply::NetworkReply(QObject* pParent,
    const QNetworkRequest& request,
    const QNetworkAccessManager::Operation op,
    QIODevice* pOutgoingData /*= nullptr*/)
    : QNetworkReply(pParent)
    , m_lOffset()
    , m_sContent()
{
    // Setup the request
    setRequest(request);
    setUrl(request.url());
    setOperation(op);
    QNetworkReply::open(QIODevice::ReadOnly | QIODevice::Unbuffered);

    // Clear content
    m_lOffset = 0;
    m_sContent.clear();

    // Get the path to the file
    QByteArray sResourceRequest = request.url().path().toUtf8();
    QByteArray sFileRequest = QByteArray(WindowManager::GetWindowWebRoot().c_str()) + sResourceRequest;

    // Log request
    LOG_STATEMENT("---------------------------------");
    LOG_FORMAT_STATEMENT("Resource request: %s\n", sResourceRequest.data());
    LOG_FORMAT_STATEMENT("File request: %s\n", sFileRequest.data());

    // Try opening supposed actual file
    QFile fsActualFile(sFileRequest.data());
    bool bFileIsOpen = fsActualFile.open(QFile::ReadOnly);
    bool bFileExists = fsActualFile.exists();

    // Check existence of a real file at this location
    if(bFileIsOpen && bFileExists)
    {
        // Append file data
        m_sContent.append(fsActualFile.readAll());

        // Get mime type
        std::string mime_type = "application/octet-stream";
        if(sResourceRequest.endsWith(".html"))
        {
            mime_type = "text/html";
        }
        else if(sResourceRequest.endsWith(".txt"))
        {
            mime_type = "text/plain";
        }
        else if(sResourceRequest.endsWith(".css") || sResourceRequest.endsWith(".map"))
        {
            mime_type = "text/css";
        }
        else if(sResourceRequest.endsWith(".js"))
        {
            mime_type = "application/javascript";
        }
        else if(sResourceRequest.endsWith(".json"))
        {
            mime_type = "application/json";
        }
        else if(sResourceRequest.endsWith(".jpg") || sResourceRequest.endsWith(".jpeg"))
        {
            mime_type = "image/jpeg";
        }
        else if(sResourceRequest.endsWith(".png"))
        {
            mime_type = "image/png";
        }

        // Set content type
        setHeader(QNetworkRequest::ContentTypeHeader, QVariant(mime_type.c_str()));

        // Set return type
        setAttribute(QNetworkRequest::HttpStatusCodeAttribute, QVariant(200));
    }
    else
    {
        // Input/output/code
        HttpInput http_input;
        HttpOutput http_output;
        long status_code = 404;
        std::string mime_type = "text/plain";

        // Insert GET and POST tables
        http_input["GET"] = std::map<std::string, std::string>();
        http_input["POST"] = std::map<std::string, std::string>();

        // Check operation type
        switch(op)
        {
            // GET operation
            case QNetworkAccessManager::GetOperation:
            {
                // Retrieve "GET" parameters
                auto params_get = QUrlQuery(request.url()).queryItems(QUrl::PrettyDecoded);

                // Add to input
                for(int i = 0; i < params_get.size(); i++)
                {
                    std::string sKey = params_get[i].first.toStdString();
                    std::string sValue = params_get[i].second.toStdString();
                    http_input["GET"].emplace(std::make_pair(sKey, sValue));
                }
                break;
            }

            // POST operation
            case QNetworkAccessManager::PostOperation:
            {
                // Retrieve "POST" parameters
                auto params_post = QJsonDocument::fromJson((pOutgoingData) ? pOutgoingData->readAll() : "{}").object();

                // Add to input
                auto vKeyList = params_post.keys();
                for(int i = 0; i < vKeyList.size(); i++)
                {
                    if(params_post[vKeyList[i]].isString())
                    {
                        std::string sKey = vKeyList[i].toStdString();
                        std::string sValue = params_post.value(vKeyList[i]).toString().toStdString();
                        http_input["POST"].emplace(std::make_pair(sKey, sValue));
                    }
                    else if(params_post[vKeyList[i]].isBool())
                    {
                        std::string sKey = vKeyList[i].toStdString();
                        std::string sValue = (params_post.value(vKeyList[i]).toBool()) ? "1" : "0";
                        http_input["POST"].emplace(std::make_pair(sKey, sValue));
                    }
                }
                break;
            }
        }

        // Handle internal resource
        if(sResourceRequest == "/api/run_module_file")
        {
            Handle_RunModuleFile(http_input, http_output, status_code, mime_type);
        }
        else if(sResourceRequest == "/api/run_module_file_results")
        {
            Handle_RunModuleFileResults(http_input, http_output, status_code, mime_type);
        }
        else if(sResourceRequest == "/api/run_module_command")
        {
            Handle_RunModuleCommand(http_input, http_output, status_code, mime_type);
        }
        else if(sResourceRequest == "/api/run_module_command_results")
        {
            Handle_RunModuleCommandResults(http_input, http_output, status_code, mime_type);
        }
        else if(sResourceRequest == "/api/clear_module_results")
        {
            Handle_ClearModuleResult(http_input, http_output, status_code, mime_type);
        }
        else if(sResourceRequest == "/api/clear_all_module_results")
        {
            Handle_ClearAllModuleResults(http_input, http_output, status_code, mime_type);
        }
        else if(sResourceRequest == "/api/does_module_result_exist")
        {
            Handle_DoesModuleResultExist(http_input, http_output, status_code, mime_type);
        }
        else if(sResourceRequest == "/api/get_module_result_size")
        {
            Handle_GetModuleResultSize(http_input, http_output, status_code, mime_type);
        }
        else if(sResourceRequest == "/api/get_module_results")
        {
            Handle_GetModuleResults(http_input, http_output, status_code, mime_type);
        }

        // Append result data
        m_sContent.append(http_output.c_str());

        // Set return type
        setAttribute(QNetworkRequest::HttpStatusCodeAttribute, QVariant(static_cast<int>(status_code)));

        // Set content type
        setHeader(QNetworkRequest::ContentTypeHeader, QVariant(mime_type.c_str()));
    }

    // Close file
    fsActualFile.close();

    // Set content size
    setHeader(QNetworkRequest::ContentLengthHeader, QVariant(m_sContent.size()));

    // Call notify functions
    QMetaObject::invokeMethod(this, "metaDataChanged", Qt::QueuedConnection);
    QMetaObject::invokeMethod(this, "readyRead", Qt::QueuedConnection);
    QMetaObject::invokeMethod(this, "downloadProgress",
        Qt::QueuedConnection, Q_ARG(qint64, m_sContent.size()), Q_ARG(qint64, m_sContent.size()));
    QMetaObject::invokeMethod(this, "finished", Qt::QueuedConnection);
}

NetworkReply::~NetworkReply()
{
}

void NetworkReply::abort()
{
    // Do nothing
}

qint64 NetworkReply::bytesAvailable() const
{
    // Number of bytes available to read
    return m_sContent.size() - m_lOffset + QIODevice::bytesAvailable();
}

bool NetworkReply::isSequential() const
{
    // Sequential read
    return true;
}

qint64 NetworkReply::readData(char* pData, qint64 lMaxSize)
{
    // Have we copied all the data?
    if(m_lOffset >= m_sContent.size())
    {
        return -1;
    }

    // Copy a block of data
    qint64 lCount = qMin(lMaxSize, m_sContent.size() - m_lOffset);
    memcpy(pData, m_sContent.constData() + m_lOffset, lCount);
    m_lOffset += lCount;

    // Return the number of bytes copied
    return lCount;
}
