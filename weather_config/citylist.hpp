#ifndef CITYLIST_HPP
#define CITYLIST_HPP

#include <QList>
#include <QSharedPointer>
#include <QSqlDatabase>
#include <QString>
#include <QWidget>

typedef struct __CITY_INFO__ {
    QString CityID;
    float coord_lon;
    float coord_lat;
} CityInfo;

class CityList
{
private:
    bool initialized;
    QSqlDatabase db;
public:
    bool is_OK() {
        return initialized;
    };
    CityList(QString &name);
    QSharedPointer<QList<QString>> GetList();
    QSharedPointer<QList<QString>> GetList(QString &country);
    QSharedPointer<QList<QSharedPointer<CityInfo>>> GetList(QString &country,
            QString &name);
};

#endif // CITYLIST_HPP
