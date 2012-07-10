# General info

release {
    TARGET = libbta
} else {
    TARGET = libbtad
}

TEMPLATE = lib
VERSION = 0.1

CONFIG += QT TUFAO link_pkgconfig
QT += network declarative svg
QT -= gui
PKGCONFIG += QJson

# Build info

QMAKE_CXXFLAGS += -std=c++11

DEFINES += LIBBTA_LIBRARY
DESTDIR = lib
release {
    OBJECTS_DIR = build/release
    MOC_DIR = build/release
} else {
    OBJECTS_DIR = build/debug
    MOC_DIR = build/debug
}

# Install info

target.path = $$INSTALLDIR$$[QT_INSTALL_LIBS]

qmakefile.path = $$INSTALLDIR$$[QMAKE_MKSPECS]/features
qmakefile.files = pkg/libbta.prf

headers.path = $$INSTALLDIR$$[QT_INSTALL_HEADERS]/libbta
headers.files = src/*.h \
    include/*

INSTALLS = target qmakefile headers

# Project files

HEADERS += src/libbta_global.h \
    src/trackerhandler.h \
    src/rpcnode.h \
    src/priv/rpcnode.h \
    src/priv/introspection.h \
    src/gii.h \
    src/giiitem.h \
    src/giistate.h \
    src/priv/giiitem.h \
    src/priv/gii.h \
    src/priv/giistate.h

SOURCES += \
    src/trackerhandler.cpp \
    src/rpcnode.cpp \
    src/gii.cpp \
    src/giiitem.cpp \
    src/giistate.cpp
