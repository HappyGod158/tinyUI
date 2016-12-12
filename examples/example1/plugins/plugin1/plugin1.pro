#-------------------------------------------------
#
# Project created by QtCreator 2016-12-12T14:19:16
#
#-------------------------------------------------

QT       += core widgets

TARGET = plugin1
TEMPLATE = lib
CONFIG += plugin

DESTDIR = $$OUT_PWD/../../../../destdir

INCLUDEPATH += $$PWD/../../../../tinyUI/src
LIBS += -L$$DESTDIR -ltinyUI

SOURCES += genericplugin.cpp \
    page1.cpp \
    page2.cpp \
    page3.cpp

HEADERS += genericplugin.h \
    page1.h \
    page2.h \
    page3.h
DISTFILES += plugin1.json

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    page1.ui \
    page2.ui \
    page3.ui
