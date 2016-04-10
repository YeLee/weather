QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = weather_config
TEMPLATE = app
lessThan(QT_MAJOR_VERSION, 5) QMAKE_CXXFLAGS += -std=c++11
greaterThan(QT_MAJOR_VERSION, 4): CONFIG += c++11

SOURCES += main.cpp\
        configwin.cpp \
    citylist.cpp

HEADERS  += \
    citylist.hpp \
    configwin.hpp \
    userdef.hpp
