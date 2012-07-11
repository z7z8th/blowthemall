# General info

TARGET = libbta
TEMPLATE = lib
VERSION = 0.1

CONFIG += QT TUFAO link_pkgconfig
QT += network declarative
QT -= gui
PKGCONFIG += QJson

# Build info

QMAKE_CXXFLAGS += -std=c++11

DEFINES += LIBBTA_LIBRARY
DESTDIR = lib
release {
    OBJECTS_DIR = ../build/release
    MOC_DIR = ../build/release
} else {
    OBJECTS_DIR = ../build/debug
    MOC_DIR = ../build/debug
}

# Install info

target.path = $$INSTALLDIR$$[QT_INSTALL_LIBS]

qmakefile.path = $$INSTALLDIR$$[QMAKE_MKSPECS]/features
qmakefile.files = ../pkg/libbta.prf

headers.path = $$INSTALLDIR$$[QT_INSTALL_HEADERS]/libbta
headers.files = ../src/libbta/*.h \
    ../include/*

INSTALLS = target qmakefile headers

# Project files

HEADERS += ../src/libbta/libbta_global.h \
    ../src/libbta/trackerhandler.h \
    ../src/libbta/rpcnode.h \
    ../src/libbta/priv/rpcnode.h \
    ../src/libbta/priv/introspection.h \
    ../src/libbta/gii.h \
    ../src/libbta/giistate.h \
    ../src/libbta/priv/giiitem.h \
    ../src/libbta/priv/gii.h \
    ../src/libbta/priv/giistate.h \
    ../src/libbta/priv/rcc.h

SOURCES += \
    ../src/libbta/trackerhandler.cpp \
    ../src/libbta/rpcnode.cpp \
    ../src/libbta/gii.cpp \
    ../src/libbta/giistate.cpp \
    ../src/libbta/priv/rcc.cpp
