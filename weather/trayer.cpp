#include <QApplication>
#include "trayer.hpp"

trayer::trayer(QString app, config c) :
    cfg(c), actShow(this), actUpdate(this), actExit(this)
{
    APPName = app;

    actShow.setText(tr("Show"));
    actUpdate.setText(tr("Update"));
    actExit.setText(tr("Exit"));
    menu.addAction(&actShow);
    menu.addAction(&actUpdate);
    menu.addAction(&actExit);

    trayicon.setToolTip(APPName);
    trayicon.setIcon(QPixmap(":/weather.png"));
    trayicon.showMessage(APPName, tr("I am here."));
    trayicon.setContextMenu(&menu);
    trayicon.show();

    connect(&menu, &QMenu::triggered,
            this, &trayer::OnClick);
    connect(&timer, &QTimer::timeout,
            this, &trayer::Timeout);
    timer.start(cfg.freq * 1000 * 60);
}

void trayer::OnClick(QAction *act)
{
    if(act->text() == tr("Show")) {
        emit Show();
    } else if(act->text() == tr("Update")) {
        emit GetData();
    } else if(act->text() == tr("Exit")) {
        QApplication::quit();
    }
}

void trayer::update(WeatherInfo *wi) {
    if(!wi->is_OK()) return;
    QString tip = QString("%1(%2):%3 %4% %5")
                  .arg(wi->GetCityName())
                  .arg(wi->GetCountry())
                  .arg(wi->GetKeyByIndex(0, { "main", "temp" }).toFloat())
                  .arg(wi->GetKeyByIndex(0, { "main", "humidity" }).toFloat())
                  .arg(wi->GetKeyByIndex(0, { "weather" }).toList()[0].
                       toMap()["description"].toString());
    trayicon.setToolTip(tip);
    QString key = wi->GetKeyByIndex(0, { "weather"}).toList()[0].
                  toMap()["icon"].toString();
    trayicon.setIcon(wi->GetImg(key));
}
