#include <QGridLayout>
#include <QHBoxLayout>
#include <QObject>
#include <QVBoxLayout>
#include <QFileInfo>
#include <QDebug>

#include <algorithm>
#include <functional>

#include "configwin.hpp"
#include "userdef.hpp"
#include "citylist.hpp"

#ifndef VALUE_MSG
#define VALUE_MSG(a) (#a) << " = " << (a);
#endif

ConfigWin::ConfigWin(QString &path, QString &Name, QWidget *parent)
    : QMainWindow(parent),
      setting(new QSettings(path, QSettings::IniFormat)),
      AppName(Name)
{
}

ConfigWin::~ConfigWin()
{
}

void ConfigWin::addWidgets(CityList &list)
{
    citylist = &list;
    QSharedPointer<QList<QString>> country = citylist->GetCountryList();
    for(QString str : *country) {
        cbNation.addItem(str);
    }
    QVBoxLayout *vbox = new QVBoxLayout;

    QHBoxLayout *bcb = new QHBoxLayout;
    QGridLayout *glc = new QGridLayout;
    QLabel *lbc = new QLabel(tr("Country:"));
    // lbc->setAttribute(Qt::WA_DeleteOnClose);
    lbc->setBuddy(&cbNation);
    glc->addWidget(lbc);
    glc->addWidget(&cbNation);
    bcb->addLayout(glc);
    QGridLayout *gln = new QGridLayout;
    QLabel *lbn = new QLabel(tr("City:"));
    // lbn->setAttribute(Qt::WA_DeleteOnClose);
    lbn->setBuddy(&cbCity);
    gln->addWidget(lbn);
    gln->addWidget(&cbCity);
    bcb->addLayout(gln);
    vbox->addLayout(bcb);

    QGridLayout *glci = new QGridLayout;
    QLabel *lbci = new QLabel(tr("City Information:"));
    lbci->setBuddy(&cbCityInfo);
    glci->addWidget(lbci);
    glci->addWidget(&cbCityInfo);
    vbox->addLayout(glci);

    QHBoxLayout *lbt = new QHBoxLayout;
    QGridLayout *gllang = new QGridLayout;
    QLabel *lblang = new QLabel(tr("Language:"));
    lblang->setBuddy(&cblang);
    gllang->addWidget(lblang);
    gllang->addWidget(&cblang);
    lbt->addLayout(gllang);
    QGridLayout *gltemp = new QGridLayout;
    QLabel *lbtemp = new QLabel(tr("Temperature:"));
    lbtemp->setBuddy(&cbtemp);
    gltemp->addWidget(lbtemp);
    gltemp->addWidget(&cbtemp);
    lbt->addLayout(gltemp);
    vbox->addLayout(lbt);

    for(const auto & item : WeatherLanguage) {
        cblang.addItem(item.fullName);
    }
    for(const auto & item : TemperatureType) {
        cbtemp.addItem(item.name);
    }

    QHBoxLayout *lbe = new QHBoxLayout;
    QGridLayout *glfreq = new QGridLayout;
    QLabel *lbFreq = new QLabel(tr("Update Frequency(min):"));
    lbFreq->setBuddy(&UpdateFreq);
    glfreq->addWidget(lbFreq);
    glfreq->addWidget(&UpdateFreq);
    lbe->addLayout(glfreq);
    QGridLayout *glclose = new QGridLayout;
    QLabel *lbClose = new QLabel(tr("AutoCloseWindow(s):"));
    lbClose->setAttribute(Qt::WA_DeleteOnClose);
    lbClose->setBuddy(&AutoClose);
    glclose->addWidget(lbClose);
    glclose->addWidget(&AutoClose);
    lbe->addLayout(glclose);
    vbox->addLayout(lbe);

    QHBoxLayout *lbs = new QHBoxLayout;
    QGridLayout *glapp = new QGridLayout;
    QLabel *lbAPPID = new QLabel(tr("APPID:"));
    lbAPPID->setBuddy(&APPID);
    glapp->addWidget(lbAPPID);
    glapp->addWidget(&APPID);
    lbs->addLayout(glapp);
    QGridLayout *glsubmit = new QGridLayout;

    QLabel *lbsubmit = new QLabel;// 仅用于占位
    Submit.setText(tr("Submit"));
    glsubmit->addWidget(lbsubmit);
    glsubmit->addWidget(&Submit);
    lbs->addLayout(glsubmit);
    vbox->addLayout(lbs);

    QWidget *wm = new QWidget;
    wm->setLayout(vbox);
    this->setCentralWidget(wm);

    QObject::connect(&cbNation, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
                     this, &ConfigWin::UpdateCBCity);
    QObject::connect(&cbCity, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
                     this, &ConfigWin::UpdateLBCityInfo);
    QObject::connect(&Submit, &QPushButton::clicked,
                     this, &ConfigWin::SubmitData);
}

template<typename T, size_t N, typename Func> int locate_if(T (&a)[N], Func f)
{
    auto iter = std::find_if(std::begin(a), std::end(a), f);
    if (iter == std::end(a)) {
        return -1;
    }
    return std::distance(std::begin(a), iter);
}

void ConfigWin::loadSettings()
{
    qDebug() << __func__ << this->setting->fileName();
    QFileInfo finfo(this->setting->fileName());

    if (finfo.isReadable() && 
        setting->contains(AppName+"/"+"id") &&
        setting->contains(AppName+"/"+"lang") &&
        setting->contains(AppName+"/"+"units") &&
        setting->contains(AppName+"/"+"appid") &&
        setting->contains(AppName+"/"+"freq") &&
        setting->contains(AppName+"/"+"timeout"))
    {
        QString     id      = setting->value(AppName+"/"+"id").toString();
        QString     lang    = setting->value(AppName+"/"+"lang").toString();
        QString     units   = setting->value(AppName+"/"+"units").toString();

        QString     appid   = setting->value(AppName+"/"+"appid").toString();
        int         freq    = setting->value(AppName+"/"+"freq").toInt();
        int         timeout = setting->value(AppName+"/"+"timeout").toInt();

        auto cityInfo = this->citylist->GetCityInfoById(id);

        if (!std::get<0>(cityInfo).CityID.isEmpty()) {

            // 由于是单线程UI截面，并且connect动作是 Qt::DirectConnection
            // 这样，可以保证界面的修改的"原子性"！
            this->cbNation.setCurrentText(std::get<1>(cityInfo));

            this->cbCity.setCurrentText(std::get<2>(cityInfo));
        }

        int langIndex = locate_if(WeatherLanguage,
                                  [&lang](const LangInfo_t& li)->bool {
                                      return li.shortName == lang;
                                  });

        qDebug() << VALUE_MSG(langIndex);
        if (langIndex >= 0)
        {
            this->cblang.setCurrentIndex(langIndex);
            qDebug() << VALUE_MSG(cblang.currentIndex());
        }

        int unitsIndex = locate_if(TemperatureType,
                                   [&units](const TemperatureUnit_t& tu)->bool {
                                       return tu.shortName == units;
                                   });
        qDebug() << VALUE_MSG(unitsIndex);
        if (unitsIndex >= 0)
        {
            this->cbtemp.setCurrentIndex(unitsIndex);
            qDebug() << VALUE_MSG(cbtemp.currentIndex());
        }

        if (freq > 0) {
            this->UpdateFreq.setText(QString::number(freq));
        }
        if (timeout > 0) {
            this->AutoClose.setText(QString::number(timeout));
        }
        if (!appid.isEmpty()) {
            this->APPID.setText(appid);
        }
    }
}

void ConfigWin::UpdateCBCity(int idx)
{
    QString str = cbNation.itemText(idx);
    QSharedPointer<QList<QString>> name = citylist->GetCityList(str);

    cbCity.clear();
    for(QString str : *name) {
        cbCity.addItem(str);
    }
    cbCity.setCurrentIndex(-1);
    qDebug() << __func__ << this->cbCity.count();
}

void ConfigWin::UpdateLBCityInfo(int idx)
{
    QString str = cbCity.itemText(idx);
    QString cbctext = cbNation.currentText();
    QString cbntext = cbCity.currentText();
    cbntext.replace("\'", "\'\'");
    info = citylist->GetCityInfoList(cbctext, cbntext);
    cbCityInfo.clear();
    for(QSharedPointer<CityInfo> swap: *info) {
        QString text;
        text = tr("CityID:%1 Longitude:%2 Latitude:%3")
            .arg(swap->CityID).arg(swap->coord_lon).arg(swap->coord_lat);
        cbCityInfo.addItem(text);
    }
}

void ConfigWin::SubmitData()
{
    int idx = cbCityInfo.currentIndex();
    if(idx == -1) return;
    QString id = APPID.text();
    if(id.length() == 0)  return;
    int freq = UpdateFreq.text().toInt();
    int close = AutoClose.text().toInt();

    setting->beginGroup(AppName);

    QSharedPointer<CityInfo> io = info->at(idx);
    setting->setValue("id", io->CityID);

    setting->setValue("lang",
                      WeatherLanguage[cblang.currentIndex()].shortName);
    setting->setValue("units",
                      TemperatureType[cbtemp.currentIndex()].shortName);

    setting->setValue("appid", id);
    setting->setValue("freq", freq);
    setting->setValue("timeout", close);

    setting->endGroup();
    this->close();
}
