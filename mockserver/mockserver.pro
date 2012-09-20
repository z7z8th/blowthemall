#-------------------------------------------------
#
# Project created by QtCreator 2012-09-18T16:29:34
#
#-------------------------------------------------

CONFIG += TUFAO0 LIBBTA

QT       += core
QT       -= gui

TARGET = mockserver
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11


SOURCES += main.cpp \
    basestate.cpp \
    httpserver.cpp

HEADERS += \
    basestate.h \
    httpserver.h
