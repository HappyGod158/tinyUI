TEMPLATE = lib

QT += widgets

DESTDIR = $$OUT_PWD/../destdir
include(QtAwesome/QtAwesome.pri)

DEFINES += API_LIBRARY

INCLUDEPATH += $$PWD/src

HEADERS += src/menuManager.h\
           src/nexus.h\
           src/pluginInterface.h\
           src/pluginManager.h\
           src/mainwindow.h\
           src/api_global.h \
    src/pane.h \
    src/workspace.h \
    src/tabwidget.h \
    src/sidebarManager.h \
    src/menu.h \
    src/containerpane.h \
    src/contentpane.h \
    src/subwindow.h \
    src/qtawesomemanager.h \
    src/pagemanager.h \
    src/pageinfo.h \
    src/settingmanager.h \
    src/tinyui.h

FORMS +=\
         src/mainwindow.ui \
    src/subwindow.ui


SOURCES += src/menuManager.cpp\
           src/nexus.cpp\
           src/pluginManager.cpp\
           src/mainwindow.cpp\
    src/pane.cpp \
    src/workspace.cpp \
    src/tabwidget.cpp \
    src/sidebarManager.cpp \
    src/menu.cpp \
    src/containerpane.cpp \
    src/contentpane.cpp \
    src/subwindow.cpp \
    src/qtawesomemanager.cpp \
    src/pagemanager.cpp \
    src/pageinfo.cpp \
    src/settingmanager.cpp


