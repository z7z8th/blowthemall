QT += network

CONFIG += link_pkgconfig

PKGCONFIG += QJson

INCLUDEPATH += "$$PWD/phobos"

SOURCES += phobos/peer.cpp \
    phobos/responsehandler.cpp \
    phobos/tcphelper.cpp \
    phobos/httphelper.cpp \
    procedure.cpp

HEADERS += phobos/phobosrpc_global.h\
    phobos/peer.h \
    phobos/responsehandler.h \
    phobos/error-inl.h \
    phobos/tcphelper.h \
    phobos/httphelper.h \
    procedure.h \
    utils.h
