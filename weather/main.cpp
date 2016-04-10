#include <QApplication>
#include "config.hpp"
#include "trayer.hpp"
#include "weatherinfo.hpp"
#include "winman.hpp"

#ifdef WIN32
#define __USE_WINDOWS__
#endif
#ifdef WIN64
#ifndef __USE_WINDOWS__
#define __USE_WINDOWS__
#endif
#endif

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setQuitOnLastWindowClosed(false);

    QString path = app.applicationFilePath();
#ifdef __USE_WINDOWS__
    path = path.left(path.size() - 4);
#endif
    path += ".ini";
    config cfg(app.applicationName(), path);
    if(cfg.id == 0ULL) return -1;

    WeatherInfo in(cfg);
    WinMan wm(cfg);
    trayer te(app.applicationName(), cfg);
    QObject::connect(&te, &trayer::GetData,
                     &in, &WeatherInfo::GetData);
    QObject::connect(&te, &trayer::Show,
                     &wm, &WinMan::Show);
    QObject::connect(&in, &WeatherInfo::update,
                     &te, &trayer::update);
    QObject::connect(&in, &WeatherInfo::update,
                     &wm, &WinMan::update);

    in.GetData();

    return app.exec();
}
