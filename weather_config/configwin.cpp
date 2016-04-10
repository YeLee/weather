#include <QGridLayout>
#include <QHBoxLayout>
#include <QObject>
#include <QVBoxLayout>
#include "configwin.hpp"
#include "userdef.hpp"

ConfigWin::ConfigWin(QString &path, QString &Name, QWidget *parent)
    : QMainWindow(parent),
      setting(new QSettings(path, QSettings::IniFormat)),
      AppName(Name)
{
}

void ConfigWin::addWidgets(CityList &list)
{
    citylist = &list;
    QSharedPointer<QList<QString>> country = citylist->GetList();
for(QString str : *country) {
        cbc.addItem(str);
    }
    QVBoxLayout *vbox = new QVBoxLayout;

    QHBoxLayout *bcb = new QHBoxLayout;
    QGridLayout *glc = new QGridLayout;
    QLabel *lbc = new QLabel;
    lbc->setAttribute(Qt::WA_DeleteOnClose);
    lbc->setText(tr("Country:"));
    glc->addWidget(lbc);
    glc->addWidget(&cbc);
    bcb->addLayout(glc);
    QGridLayout *gln = new QGridLayout;
    QLabel *lbn = new QLabel;
    lbn->setAttribute(Qt::WA_DeleteOnClose);
    lbn->setText(tr("City:"));
    gln->addWidget(lbn);
    gln->addWidget(&cbn);
    bcb->addLayout(gln);
    vbox->addLayout(bcb);

    QGridLayout *glci = new QGridLayout;
    QLabel *lbci = new QLabel;
    lbci->setAttribute(Qt::WA_DeleteOnClose);
    lbci->setText(tr("City Information:"));
    glci->addWidget(lbci);
    glci->addWidget(&cbci);
    vbox->addLayout(glci);

    QHBoxLayout *lbt = new QHBoxLayout;
    QGridLayout *gllang = new QGridLayout;
    QLabel *lblang = new QLabel;
    lblang->setAttribute(Qt::WA_DeleteOnClose);
    lblang->setText(tr("Language:"));
    gllang->addWidget(lblang);
    gllang->addWidget(&cblang);
    lbt->addLayout(gllang);
    QGridLayout *gltemp = new QGridLayout;
    QLabel *lbtemp = new QLabel;
    lbtemp->setAttribute(Qt::WA_DeleteOnClose);
    lbtemp->setText(tr("Temperature:"));
    gltemp->addWidget(lbtemp);
    gltemp->addWidget(&cbtemp);
    lbt->addLayout(gltemp);
    vbox->addLayout(lbt);
    for(int i=0; i != LangCount; i++) {
        cblang.addItem(WeatherLanguage[i][0]);
    }
    for(int i=0; i != TempTypeCount; i++) {
        cbtemp.addItem(TemperatureType[i][0]);
    }

    QHBoxLayout *lbe = new QHBoxLayout;
    QGridLayout *glfreq = new QGridLayout;
    QLabel *lbFreq = new QLabel;
    lbFreq->setAttribute(Qt::WA_DeleteOnClose);
    lbFreq->setText(tr("Update Frequency(min):"));
    glfreq->addWidget(lbFreq);
    glfreq->addWidget(&UpdateFreq);
    lbe->addLayout(glfreq);
    QGridLayout *glclose = new QGridLayout;
    QLabel *lbClose = new QLabel;
    lbClose->setAttribute(Qt::WA_DeleteOnClose);
    lbClose->setText(tr("AutoCloseWindow(s):"));
    glclose->addWidget(lbClose);
    glclose->addWidget(&AutoClose);
    lbe->addLayout(glclose);
    vbox->addLayout(lbe);

    QHBoxLayout *lbs = new QHBoxLayout;
    QGridLayout *glapp = new QGridLayout;
    QLabel *lbAPPID = new QLabel;
    lbAPPID->setAttribute(Qt::WA_DeleteOnClose);
    lbAPPID->setText(tr("APPID:"));
    glapp->addWidget(lbAPPID);
    glapp->addWidget(&APPID);
    lbs->addLayout(glapp);
    QGridLayout *glsubmit = new QGridLayout;
    QLabel *lbsubmit = new QLabel;
    lbsubmit->setAttribute(Qt::WA_DeleteOnClose);
    Submit.setText(tr("Submit"));
    glsubmit->addWidget(lbsubmit);
    glsubmit->addWidget(&Submit);
    lbs->addLayout(glsubmit);
    vbox->addLayout(lbs);

    QWidget *wm = new QWidget;
    wm->setLayout(vbox);
    this->setCentralWidget(wm);

    QObject::connect(&cbc, SIGNAL(currentIndexChanged(int)),
                     this, SLOT(UpdateCBN(int)));
    QObject::connect(&cbn, SIGNAL(currentIndexChanged(int)),
                     this, SLOT(UpdateLBCI(int)));
    QObject::connect(&Submit, SIGNAL(released()),
                     this, SLOT(SubmitData()));

    return;
}

ConfigWin::~ConfigWin()
{

}

void ConfigWin::UpdateCBN(int idx)
{
    QString str = cbc.itemText(idx);
    QSharedPointer<QList<QString>> name = citylist->GetList(str);

    cbn.clear();
for(QString str : *name) {
        cbn.addItem(str);
    }
}

void ConfigWin::UpdateLBCI(int idx)
{
    QString str = cbn.itemText(idx);
    QString cbctext = cbc.currentText();
    QString cbntext = cbn.currentText();
    cbntext.replace("\'", "\'\'");
    info = citylist->GetList(cbctext, cbntext);
    cbci.clear();
for(QSharedPointer<CityInfo> swap: *info) {
        QString text;
        text = tr("CityID:%1 Longitude:%2 Latitude:%3")
               .arg(swap->CityID).arg(swap->coord_lon).arg(swap->coord_lat);
        cbci.addItem(text);
    }
}

void ConfigWin::SubmitData()
{
    int idx = cbci.currentIndex();
    if(idx == -1) return;
    QString id = APPID.text();
    if(id.length() == 0)  return;
    int freq = UpdateFreq.text().toInt();
    int close = AutoClose.text().toInt();

    setting->beginGroup(AppName);

    QSharedPointer<CityInfo> io = info->at(idx);
    setting->setValue("id", io->CityID);
    setting->setValue("lang",
                      WeatherLanguage[cblang.currentIndex()][1]);
    setting->setValue("units",
                      TemperatureType[cbtemp.currentIndex()][1]);
    setting->setValue("appid", id);
    setting->setValue("freq", freq);
    setting->setValue("timeout", close);

    setting->endGroup();
    this->close();
}
