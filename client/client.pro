TARGET = blowthemall
TEMPLATE = app

CONFIG += TUFAO0 LIBBTA
QT += gui svg

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp \
    work.cpp

HEADERS += \
    work.h
