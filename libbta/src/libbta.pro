# General info

TARGET = libbta
TEMPLATE = lib
VERSION = 0.1

CONFIG += QT TUFAO0 link_pkgconfig
QT += network declarative
QT -= gui
PKGCONFIG += QJson

# Build info

QMAKE_CXXFLAGS += -std=c++11

DEFINES += LIBBTA_LIBRARY
DESTDIR = lib
OBJECTS_DIR = build
MOC_DIR = build

# Install info

target.path = $$INSTALLDIR$$[QT_INSTALL_LIBS]

qmakefile.path = $$INSTALLDIR$$[QMAKE_MKSPECS]/features
qmakefile.files = ../pkg/libbta.prf

headers.path = $$INSTALLDIR$$[QT_INSTALL_HEADERS]/libbta
headers.files = libbta/*.h \
    ../include/*

INSTALLS = target qmakefile headers

# Project files

HEADERS += libbta/libbta_global.h \
    libbta/trackerhandler.h \
    libbta/rpcnode.h \
    libbta/priv/rpcnode.h \
    libbta/priv/introspection.h \
    libbta/gii.h \
    libbta/giistate.h \
    libbta/priv/giiitem.h \
    libbta/priv/gii.h \
    libbta/priv/giistate.h \
    libbta/priv/rcc.h \
    libbta/giiitem.h

SOURCES += \
    libbta/trackerhandler.cpp \
    libbta/rpcnode.cpp \
    libbta/gii.cpp \
    libbta/giistate.cpp \
    libbta/priv/rcc.cpp \
    libbta/giiitem.cpp
