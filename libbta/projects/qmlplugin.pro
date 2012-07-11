TEMPLATE = lib
TARGET = gii
QT += declarative svg
CONFIG += qt plugin

TARGET = $$qtLibraryTarget($$TARGET)
uri = org.blowthemall.gii

QMAKE_CXXFLAGS += -std=c++11

# Input
SOURCES += \
    ../src/qmlplugin/gii_plugin.cpp \
    ../src/qmlplugin/giiitem.cpp \
    ../src/libbta/gii.cpp \
    ../src/libbta/giistate.cpp

HEADERS += \
    ../src/qmlplugin/gii_plugin.h \
    ../src/qmlplugin/giiitem.h \
    ../src/qmlplugin/priv/giiitem.h \
    ../src/libbta/giistate.h \
    ../src/libbta/gii.h

OTHER_FILES = qmldir

!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
    copy_qmldir.target = $$OUT_PWD/qmldir
    copy_qmldir.depends = $$_PRO_FILE_PWD_/qmldir
    copy_qmldir.commands = $(COPY_FILE) \"$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)\" \"$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)\"
    QMAKE_EXTRA_TARGETS += copy_qmldir
    PRE_TARGETDEPS += $$copy_qmldir.target
}

qmldir.files = qmldir
symbian {
    TARGET.EPOCALLOWDLLDATA = 1
} else:unix {
    maemo5 | !isEmpty(MEEGO_VERSION_MAJOR) {
        installPath = /usr/lib/qt4/imports/$$replace(uri, \\., /)
    } else {
        installPath = $$[QT_INSTALL_IMPORTS]/$$replace(uri, \\., /)
    }
    qmldir.path = $$installPath
    target.path = $$installPath
    INSTALLS += target qmldir
}

