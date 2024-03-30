// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#include "NetworkAccessManager.h"
#include "NetworkReply.h"

NetworkAccessManager::NetworkAccessManager(QObject* pParent, QNetworkAccessManager* pPrev)
    : QNetworkAccessManager(pParent)
{
    if(pPrev)
    {
        setCache(pPrev->cache());
        setCookieJar(pPrev->cookieJar());
        setProxy(pPrev->proxy());
        setProxyFactory(pPrev->proxyFactory());
    }
}

NetworkAccessManager::~NetworkAccessManager()
{
}

QNetworkReply* NetworkAccessManager::createRequest(
    QNetworkAccessManager::Operation op,
    const QNetworkRequest& originalReq,
    QIODevice* pOutgoingData /*= nullptr*/)
{
    // Embedded request
    if(originalReq.url().host() == QString(WindowManager::GetHostname().c_str()))
    {
        return new NetworkReply(this, originalReq, op, pOutgoingData);
    }

    // External request
    return QNetworkAccessManager::createRequest(op, originalReq, pOutgoingData);
}
