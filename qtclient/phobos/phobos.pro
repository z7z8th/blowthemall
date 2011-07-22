QT       -= gui

TARGET = phobosrpc
TEMPLATE = lib

CONFIG += link_pkgconfig

PKGCONFIG += QJson

QMAKE_CXXFLAGS += -std=c++0x

DEFINES += PHOBOSRPC_LIBRARY

SOURCES += peer.cpp \
    responsehandler.cpp

HEADERS +=\
    peer.h \
    responsehandler.h \
    error-inl.h \
    phobosrpc_global.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE4DBC85C
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = phobosrpc.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
