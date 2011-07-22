CONFIG += link_pkgconfig

PKGCONFIG += QJson

SOURCES += phobos/peer.cpp \
    phobos/responsehandler.cpp \

HEADERS += phobos/phobosrpc_global.h\
    phobos/peer.h \
    phobos/responsehandler.h \
    phobos/error-inl.h \
