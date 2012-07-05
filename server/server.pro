TARGET = server
TEMPLATE = app

CONFIG += TUFAO LIBBTA
QT -= gui

# Phobos conf
QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp \
    notfound.cpp \
    pluginreloader.cpp \
    webserver.cpp

HEADERS += \
    notfound.h \
    pluginreloader.h \
    webserver.h

RESOURCES += \
    static.qrc
