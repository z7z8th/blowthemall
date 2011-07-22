#-------------------------------------------------
#
# Project created by QtCreator 2011-07-11T22:23:02
#
#-------------------------------------------------

QT       += core gui network

TARGET = jrpcnode
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++0x

#include(phobos.pri)

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
