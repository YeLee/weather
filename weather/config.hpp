#ifndef CONFIG_HPP
#define CONFIG_HPP
#include <QSettings>

class config {
public:
    qulonglong id;
    QString lang;
    QString units;
    QString appid;
    int freq;
    int timeout;
    config(QString AppName, QString path) {
        QVariant var;
        QSettings setting(path, QSettings::IniFormat);

        var = setting.value(AppName+"/"+"id");
        id = var.toULongLong();//
        var = setting.value(AppName+"/"+"lang");
        lang = var.toString();
        var = setting.value(AppName+"/"+"units");
        units = var.toString();
        var = setting.value(AppName+"/"+"appid");
        appid = var.toString();
        var = setting.value(AppName+"/"+"freq");
        freq = var.toInt();
        var = setting.value(AppName+"/"+"timeout");
        timeout = var.toInt();
    };
};

#endif // CONFIG_HPP
