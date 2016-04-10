QT       += core gui network widgets

TARGET = weather
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp \
    weatherinfo.cpp \
    trayer.cpp \
    winman.cpp

HEADERS += \
    weatherinfo.hpp \
    trayer.hpp \
    winman.hpp \
    config.hpp

RESOURCES += \
    weather.qrc

DISTFILES +=
