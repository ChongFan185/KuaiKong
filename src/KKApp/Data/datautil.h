#ifndef DATAUTIL_H
#define DATAUTIL_H

#include <QObject>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class DataUtil : public QObject
{
    Q_OBJECT
public:
    explicit DataUtil(QObject *parent = nullptr);
    void Parse(QString);
    QJsonObject QstringToJson(QString jsonString);
    QString JsonToQstring(QJsonObject jsonObject);

signals:
    void SendPos(float f);
};

#endif // DATAUTIL_H
