#-------------------------------------------------
#
# Project created by QtCreator 2016-12-12T14:18:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = app
TEMPLATE = app


SOURCES += main.cpp

DESTDIR = $$OUT_PWD/../../../destdir

INCLUDEPATH += $$PWD/../../../tinyUI/src
LIBS += -L$$DESTDIR -ltinyUI

