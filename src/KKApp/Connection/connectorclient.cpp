#include "connectorclient.h"

ConnectorClient::ConnectorClient()
{
    char data[]="Hello KK !";
    client = new QTcpSocket(this);
    connect(client, SIGNAL(readyRead()), this, SLOT(ReadData()));
    client->connectToHost(QHostAddress("127.0.0.1"), 8910);
    client->write(data);
}

void ConnectorClient::setDataUtil(DataUtil *u){
    util = u;
}

void ConnectorClient::ReadData(){
    QByteArray buffer = client->readAll();
    if(!buffer.isEmpty()){
        QString str = QString(buffer);
        util->Parse(str);
    }
}
