#ifndef CONFIGWIN_HPP
#define CONFIGWIN_HPP

#include <QMainWindow>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSettings>
#include "citylist.hpp"

class ConfigWin : public QMainWindow
{
    Q_OBJECT
private:
    QComboBox cbc;
    QComboBox cbn;
    QComboBox cbci;
    QComboBox cblang;
    QComboBox cbtemp;
    QLineEdit APPID;
    QLineEdit UpdateFreq;
    QLineEdit AutoClose;
    QPushButton Submit;
    CityList *citylist;
    QSharedPointer<QList<QSharedPointer<CityInfo>>> info;
    QSharedPointer<QSettings> setting;
    QString AppName;
public:
    ConfigWin(QString &path, QString &Name, QWidget *parent = 0);
    void addWidgets(CityList &list);
    ~ConfigWin();
public slots:
    void UpdateCBN(int idx);
    void UpdateLBCI(int idx);
    void SubmitData();
};

#endif // CONFIGWIN_HPP
