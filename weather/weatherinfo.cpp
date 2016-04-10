#include <QList>
#include <QNetworkRequest>
#include <QUrl>
#include "weatherinfo.hpp"

WeatherInfo::WeatherInfo(config &conf)
    : cfg(conf),
      instance(new QNetworkAccessManager(this)),
      ins(new QNetworkAccessManager(this)),
      HTTPData(new QString),
      imglist(new QMap<QString, QPixmap>)
{
    connect(&(*instance), &QNetworkAccessManager::finished,
            this, &WeatherInfo::HttpReply);
    connect(&(*ins), &QNetworkAccessManager::finished,
            this, &WeatherInfo::GetIconList);
}

void WeatherInfo::GetData()
{
    const char *baseURL
    ("http://api.openweathermap.org/data/2.5/forecast?mode=json");
    QString url;
    QString units;
    units = (cfg.units == "")? "":"&units="+cfg.units;
    url = QString("%1&id=%2&lang=%3%4&appid=%5").arg(baseURL)
          .arg(cfg.id).arg(cfg.lang).arg(units).arg(cfg.appid);
    instance->get(QNetworkRequest(QUrl(url)));
}

void WeatherInfo::GetIconList(QNetworkReply *reply)
{
    iconcount ++;
    QString name = reply->url().toString();
    name = name.right(name.size() - name.lastIndexOf('/') - 1);
    name = name.left(name.size() - 4);
    QPixmap pix;
    pix.loadFromData(reply->readAll());
    imglist->insert(name, pix);
    if(iconcount == GetWeatherCount()) {
        initialized = true;
        emit update(this);
    }
}

QVariant WeatherInfo::GetKeyByIndex(int idx,
                                    std::initializer_list<const char *> il) {
    QVariantMap map = doc.toVariant().toMap()["list"].toList()[idx].toMap();
    auto beg = il.begin();
    for(; beg != (il.end() - 1); ++beg) {
        map = map[*beg].toMap();
    }
    return map[*beg];
}

void WeatherInfo::HttpReply(QNetworkReply *reply)
{
    initialized = false;
    *HTTPData = QString(reply->readAll().data());
    doc = QJsonDocument::fromJson(HTTPData->toUtf8());
    if(!doc.isObject()) return;
    int c = GetWeatherCount();
    if(c == 0) return;

    iconcount = 0;
    const char *baseURL("http://openweathermap.org/img/w/");
    QList<QString> ql;
    for(int i = 0; i != c; i++) {
        QString key = GetKeyByIndex(i,
        { "weather"}).toList()[0].toMap()["icon"].toString();

        if(ql.contains(key)) {
            iconcount ++;
            continue;
        }
        ql.append(key);
        QString url = QString("%1%2.png").arg(baseURL).arg(key);
        ins->get(QNetworkRequest(QUrl(url)));
    }
}
