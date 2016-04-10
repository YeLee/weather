#ifndef WEATHERINFO_HPP
#define WEATHERINFO_HPP

#include <initializer_list>
#include <QJsonDocument>
#include <QMap>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QPixmap>
#include <QSharedPointer>
#include <QString>
#include <QVariant>
#include "config.hpp"

class WeatherInfo : public QObject
{
    Q_OBJECT
private:
    int iconcount;
    bool initialized;
    config &cfg;
    QSharedPointer<QNetworkAccessManager> instance;
    QSharedPointer<QNetworkAccessManager> ins;
    QSharedPointer<QString> HTTPData;
    QSharedPointer<QMap<QString, QPixmap>> imglist;
    QJsonDocument doc;
public:
    bool is_OK() {
        return initialized;
    }
    WeatherInfo(config &conf);
    QString GetCityName() {
        return doc.toVariant().toMap()["city"].toMap()["name"].toString();
    }
    QString GetCountry() {
        return doc.toVariant().toMap()["city"].toMap()["country"].toString();
    }
    QVariantMap GetWeatherByIndex(int idx) {
        return doc.toVariant().toMap()["list"].toList()[idx].toMap();
    }
    int GetWeatherCount() {
        return doc.isEmpty()?0:doc.toVariant().toMap()["list"].toList().size();
    }
    QVariant GetKeyByIndex(int idx, std::initializer_list<const char *> il);
    QPixmap &GetImg(QString name) {
        return (*imglist)[name];
    }
signals:
    void update(WeatherInfo* info);
public slots:
    void GetData();
    void HttpReply(QNetworkReply *reply);
    void GetIconList(QNetworkReply *reply);
};

#endif // WEATHERINFO_HPP
