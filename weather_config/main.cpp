#include <QApplication>
#include <QMessageBox>
#include "configwin.hpp"
#include "citylist.hpp"

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
    QString path = app.applicationName().right(7);
    if(path != "_config") {
        QMessageBox::critical(
            nullptr,
            QObject::tr("App name Error"),
            QObject::tr("Invalid App name"),
            QMessageBox::Ok);
        return -1;
    }

    path = app.applicationFilePath();
#ifdef __USE_WINDOWS__
    path = path.left(path.size() - 4);
#endif
    CityList list(path);
    if(!list.is_OK()) return -1;

    QString AppName = app.applicationName();
    path.remove(path.size() - 7, 7);
    AppName.remove(AppName.size() - 7, 7);
    path += ".ini";
    ConfigWin win(path, AppName);
    win.addWidgets(list);
    win.show();

    return app.exec();
}
