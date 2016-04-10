#include <QDateTime>
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>
#include "winman.hpp"
#include "weatherinfo.hpp"

Widget::Widget(int time, WinMan &man, QWidget *parent)
    :QWidget(parent), wm(man)
{
    connect(&timer, &QTimer::timeout, this, &Widget::winout);
    timer.start(time * 1000);
}

void Widget::closeEvent(QCloseEvent *event) {
    Q_UNUSED(event)
    wm.destroy();
}

void Widget::Window(WeatherInfo *wi) {
    QVBoxLayout *mainFrame = new QVBoxLayout;
    QHBoxLayout *lineFrame = new QHBoxLayout;
    QString text = QString("%1(%2)").arg(wi->GetCityName())
                   .arg(wi->GetCountry());
    QLabel *Label = new QLabel;
    Label->setAttribute(Qt::WA_DeleteOnClose);
    Label->setText(text);
    lineFrame->addWidget(Label);

    int c = wi->GetWeatherCount();
    int lastday = 0;
    for(int i = 0; i != c; i++) {
        uint dt = wi->GetKeyByIndex(i, { "dt" }).toUInt();
        QDateTime dt_txt;
        dt_txt.setTime_t(dt);
        int day = dt_txt.date().day();
        if(lastday != day) {
            mainFrame->addLayout(lineFrame);
            lineFrame = new QHBoxLayout;
        }

        QVBoxLayout *curFrame = new QVBoxLayout;
        QLabel *imglabel = new QLabel;
        imglabel->setAttribute(Qt::WA_DeleteOnClose);
        QString key = wi->GetKeyByIndex(i, { "weather"}).toList()[0].
                      toMap()["icon"].toString();
        imglabel->setPixmap(wi->GetImg(key));
        curFrame->addWidget(imglabel);

        QLabel *datetime = new QLabel;
        datetime->setAttribute(Qt::WA_DeleteOnClose);
        datetime->setText(dt_txt.toString(tr("ddd MM-dd:HH(t)")));
        curFrame->addWidget(datetime);

        QLabel *w = new QLabel;
        w->setAttribute(Qt::WA_DeleteOnClose);
        text = tr("%1 %4% %5")
               .arg(wi->GetKeyByIndex(i, { "main", "temp" }).toFloat())
               .arg(wi->GetKeyByIndex(i, { "main", "humidity" }).toFloat())
               .arg(wi->GetKeyByIndex(i, { "weather" }).
                    toList()[0].toMap()["description"].toString());
        w->setText(text);
        curFrame->addWidget(w);

        lineFrame->addLayout(curFrame);
        lastday = day;
    }
    setLayout(mainFrame);
    show();
}
