#ifndef CONFIG_HPP
#define CONFIG_HPP
#include <QSettings>

class config {
public:
    qulonglong  id;
    QString     lang;
    QString     units;
    QString     appid;
    int         freq;
    int         timeout;

    config(QString AppName, QString path) {
        QSettings setting(path, QSettings::IniFormat);

        id      = setting.value(AppName+"/"+"id").toULongLong();//
        lang    = setting.value(AppName+"/"+"lang").toString();
        units   = setting.value(AppName+"/"+"units").toString();
        appid   = setting.value(AppName+"/"+"appid").toString();
        freq    = setting.value(AppName+"/"+"freq").toInt();
        timeout = setting.value(AppName+"/"+"timeout").toInt();
    };
};

#endif // CONFIG_HPP
