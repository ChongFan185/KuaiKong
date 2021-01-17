#include "datautil.h"

DataUtil::DataUtil(QObject *parent) : QObject(parent)
{

}

void DataUtil::Parse(QString str){
    QJsonObject json = QstringToJson(str);
    qDebug()<<str<<","<<json.keys();
    if (json["name"].toString()=="can"){
        QJsonArray content = json["content"].toArray();
        int speed = content[0].toInt();
        qDebug()<<"json can:"<<speed;
    }
    if(json["name"].toString()=="radar"){
        QJsonArray content = json["content"].toArray();
        double x = content[0].toDouble();
        double y = content[1].toDouble();
        double z = content[2].toDouble();
        double ax = content[3].toDouble();
        double ay = content[4].toDouble();
        double az = content[5].toDouble();
        double angle = content[6].toDouble();
        qDebug()<<"json radar:"<<x<<","<<y<<","<<z<<",aim"<<ax<<","<<ay<<","<<az<<",angle"<<angle;
        emit SendPos((float)angle);
    }

}

QJsonObject DataUtil::QstringToJson(QString jsonString)
{
    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonString.toLocal8Bit().data());
    if(jsonDocument.isNull())
    {
        qDebug()<< "String NULL"<< jsonString.toLocal8Bit().data();
    }
    QJsonObject jsonObject = jsonDocument.object();
    return jsonObject;
}

QString DataUtil::JsonToQstring(QJsonObject jsonObject)
{
    return QString(QJsonDocument(jsonObject).toJson());
}
