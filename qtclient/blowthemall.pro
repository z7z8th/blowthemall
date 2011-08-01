QT       += core gui

TARGET = blowthemall
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++0x

include(phobos.pri)

SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/mainscreen.cpp \
    src/loginscreen.cpp \
    src/settingsscreen.cpp \
    src/aboutscreen.cpp \
    src/trackerscreen.cpp \
    src/charactersettingsscreen.cpp

HEADERS  += src/mainwindow.h \
    src/mainscreen.h \
    src/loginscreen.h \
    src/settingsscreen.h \
    src/aboutscreen.h \
    src/trackerscreen.h \
    src/charactersettingsscreen.h

FORMS    += ui/mainwindow.ui \
    ui/mainscreen.ui \
    ui/loginscreen.ui \
    ui/settingsscreen.ui \
    ui/aboutscreen.ui \
    ui/trackerscreen.ui \
    ui/charactersettingsscreen.ui

RESOURCES += \
    data/resources.qrc
