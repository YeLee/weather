#ifndef CITYLIST_HPP
#define CITYLIST_HPP

#include <QList>
#include <QSharedPointer>
#include <QSqlDatabase>
#include <QString>
#include <QWidget>

#include <tuple>

struct CityInfo {
    QString CityID;
    float coord_lon;
    float coord_lat;
    CityInfo() {}
    CityInfo(QString CityID, float coord_lon, float coord_lat)
        : CityID(CityID), coord_lon(coord_lon), coord_lat(coord_lat)
    { }
};                           

class CityList
{
private:
    bool initialized;
    QSqlDatabase db;

public:
    CityList(QString &name);

public:
    bool is_OK() {
        return initialized;
    };
    QSharedPointer<QList<QString>> GetCountryList();
    QSharedPointer<QList<QString>> GetCityList(QString &country);
    QSharedPointer<QList<QSharedPointer<CityInfo>>> GetCityInfoList(QString &country,
                                                                    QString &name);

    std::tuple<CityInfo, QString, QString> GetCityInfoById(const QString& id);
};

#endif // CITYLIST_HPP
