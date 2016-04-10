#ifndef WINMAN_HPP
#define WINMAN_HPP

#include <QCloseEvent>
#include <QCursor>
#include <QTimer>
#include <QWidget>
#include "config.hpp"

class WeatherInfo;
class WinMan;
class Widget : public QWidget {
    Q_OBJECT
    QTimer timer;
    WinMan &wm;
    void closeEvent(QCloseEvent *event);
public:
    Widget(int time, WinMan &man, QWidget *parent = 0);
    void Window(WeatherInfo *wi);
public slots:
    void winout() {
        QCursor cursor;
        if(cursor.pos().x() < this->pos().x() ||
                cursor.pos().x() > (this->pos().x() + this->width()) ||
                cursor.pos().y() < this->pos().y() ||
                cursor.pos().y() > (this->pos().y() + this->height()))
            this->close();
    }
};

class WinMan : public QObject {
    Q_OBJECT
private:
    Widget *win;
    int time;
    WeatherInfo *wi;
public:
    void destroy() {
        delete win;
        win = nullptr;
    }
    WinMan(config &cfg) : win(nullptr), time(cfg.timeout) ,wi(nullptr) { }
public slots:
    void Show() {
        if(wi == nullptr) return;
        if(win == nullptr) {
            win = new Widget(time, *this);
        }
        win->Window(wi);
    };
    void update(WeatherInfo *i) {
        wi = i;
    }
};

#endif // WINMAN_HPP
