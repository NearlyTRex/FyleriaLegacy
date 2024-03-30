// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#ifndef _APP_NETWORK_ACCESS_MANAGER_H_
#define _APP_NETWORK_ACCESS_MANAGER_H_

// Includes
#include "WindowManager.h"

// Network access manager
class NetworkAccessManager : public QNetworkAccessManager
{
    Q_OBJECT

public:

    // Constructor
    NetworkAccessManager(QObject* pParent, QNetworkAccessManager* pPrev);

    // Destructor
    virtual ~NetworkAccessManager();

protected:

    // Create a request response object
    virtual QNetworkReply* createRequest(
        QNetworkAccessManager::Operation op,
        const QNetworkRequest& originalReq,
        QIODevice* pOutgoingData = nullptr) override;
};

#endif
