#ifndef TRAYER_HPP
#define TRAYER_HPP

#include <QAction>
#include <QMenu>
#include <QSystemTrayIcon>
#include <QTimer>
#include "weatherinfo.hpp"

class trayer : public QObject
{
    Q_OBJECT
private:
    config cfg;
    QTimer timer;
    QString APPName;
    QSystemTrayIcon trayicon;
    QAction actShow;
    QAction actUpdate;
    QAction actExit;
    QMenu menu;
public:
    trayer(QString app,  config c);
signals:
    void GetData();
    void Show();
public slots:
    void OnClick(QAction *act);
    void Timeout() {
        emit GetData();
    };
    void update(WeatherInfo *info);
};

#endif // TRAYER_HPP
