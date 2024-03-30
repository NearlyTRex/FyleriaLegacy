// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#ifndef _APP_NETWORK_REPLY_H_
#define _APP_NETWORK_REPLY_H_

// Includes
#include "WindowManager.h"

// Network reply
class NetworkReply : public QNetworkReply
{
    Q_OBJECT

public:

    // Constructor
    NetworkReply(QObject* pParent,
        const QNetworkRequest& request,
        const QNetworkAccessManager::Operation op,
        QIODevice* pOutgoingData = nullptr);

    // Destructor
    virtual ~NetworkReply();

    // Aborts the transfer
    virtual void abort() override;

    // Return the number of bytes available
    virtual qint64 bytesAvailable() const override;

    // Return non zero for sequential data
    virtual bool isSequential() const override;

protected:

    // Used to retrieve a block of content data
    virtual qint64 readData(char* pData, qint64 lMaxSize) override;

private:

    // Offset progress
    qint64 m_lOffset;

    // Data buffer
    QByteArray m_sContent;
};

#endif
