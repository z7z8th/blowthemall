QT       += core gui

TARGET = blowthemall
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++0x

include(phobos.pri)

SOURCES += src/main.cpp\
        src/mainwindow.cpp

HEADERS  += src/mainwindow.h

FORMS    += ui/mainwindow.ui

RESOURCES += \
    data/resources.qrc
