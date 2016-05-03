#include <QMessageBox>
#include <QObject>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariant>
#include "citylist.hpp"

const char *TableName = "city_list";

CityList::CityList(QString &name)
{
    initialized = false;

    QString database = name;
    database += ".db";

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(database);
    if(!db.open()) {
        QSqlError err;
        QMessageBox::critical(
            nullptr,
            QObject::tr("Database Error"),
            db.lastError().text(),
            QMessageBox::Ok);
        return;
    }

    initialized = true;
}

QSharedPointer<QList<QString>> CityList::GetCountryList() {
    QSharedPointer<QList<QString>> list(new QList<QString>);
    QString sql = "SELECT DISTINCT country FROM ";
    sql += TableName;
    sql += " ORDER BY country;";
    QSqlQuery query(sql);

    while(query.next()) {
        list->append(query.value(0).toString());
    }
    return list;
}

QSharedPointer<QList<QString>> CityList::GetCityList(QString &country) {
    QSharedPointer<QList<QString>> list(new QList<QString>);
    QString sql = "SELECT DISTINCT name FROM ";
    sql += TableName;
    sql += " WHERE country=\'";
    sql += country;
    sql += "\' ORDER BY name;";
    QSqlQuery query(sql);

    while(query.next()) {
        list->append(query.value(0).toString());
    }
    return list;
}

QSharedPointer<QList<QSharedPointer<CityInfo>>> CityList::GetCityInfoList(
QString &country, QString &name) {
    QSharedPointer<QList<QSharedPointer<CityInfo>>>
    list(new QList<QSharedPointer<CityInfo>>);
    QString sql = "SELECT DISTINCT _id, coord_lon, coord_lat FROM ";
    sql += TableName;
    sql += " WHERE country=\'";
    sql += country;
    sql += "\' AND name=\'";
    sql += name;
    sql += "\' ORDER BY _id;";

    QSqlQuery query(sql);

    while(query.next()) {
        QSharedPointer<CityInfo> info(new CityInfo);
        info->CityID = query.value(0).toString();
        info->coord_lon = query.value(1).toFloat();
        info->coord_lat = query.value(2).toFloat();
        list->append(info);
    }
    return list;
}

std::tuple<CityInfo, QString, QString> CityList::GetCityInfoById(const QString& id)
{
    std::tuple<CityInfo, QString, QString> ret;
    QSqlQuery query;

    QString prepareSql = "SELECT _id, coord_lon, coord_lat, country, name FROM ";
    prepareSql += TableName;
    prepareSql += " WHERE _id=:id;";
    query.prepare(prepareSql);

    query.bindValue(":id", id);

    if (!query.exec()) {
        QMessageBox::critical(0, QObject::tr("Database Error"),
                              query.lastError().text());
        return ret;
    }

    if (query.next()) {
        ret = std::make_tuple(CityInfo(query.value(0).toString(), query.value(1).toFloat(), query.value(2).toFloat()),
                              query.value(3).toString(),
                              query.value(4).toString());
    }

    return ret;
}
