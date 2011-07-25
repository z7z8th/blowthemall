#-------------------------------------------------
#
# Project created by QtCreator 2011-07-23T23:36:07
#
#-------------------------------------------------

QT       += core gui

TARGET = phobosnode
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++0x
#include(phobos.pri)

SOURCES += main.cpp\
        mainwindow.cpp \
    tcpserverwindow.cpp

HEADERS  += mainwindow.h \
    tcpserverwindow.h

FORMS    += mainwindow.ui \
    tcpserverwindow.ui
