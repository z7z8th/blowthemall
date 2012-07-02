# General info

release {
    TARGET = libbta
} else {
    TARGET = libbtad
}

TEMPLATE = lib
VERSION = 0.1

CONFIG += QT
QT += network
QT -= gui

# Build info

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
    src/trackerhandler.h

SOURCES += \
    src/trackerhandler.cpp
