#ifndef CONNECTORCLIENT_H
#define CONNECTORCLIENT_H

#include <QObject>
#include <QtNetwork>
#include "Data/datautil.h"

class ConnectorClient: public QObject
{
    Q_OBJECT
public:
    ConnectorClient();
    bool sendMessage();
    void setDataUtil(DataUtil *u);
private:
    QTcpSocket *client;
    DataUtil *util;
private slots:
    void ReadData();
};

#endif // CONNECTORCLIENT_H
