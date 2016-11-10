TEMPLATE = lib

QT += widgets

include(QtAwesome/QtAwesome.pri)

DEFINES += API_LIBRARY

INCLUDEPATH += $$PWD/widget
HEADERS += menuManager.h\
           nexus.h\
           pluginInterface.h\
           pluginManager.h\
           widget/mainwindow.h\
           api_global.h \
    pane.h \
    workspace.h \
    tabwidget.h \
    sidebarManager.h \
    menu.h \
    containerpane.h \
    contentpane.h \
    global.h \
    widget/subwindow.h \
    qtawesomemanager.h \
    pagemanager.h \
    pageinfo.h \
    settingmanager.h

FORMS +=\
         widget/mainwindow.ui \
    widget/subwindow.ui


SOURCES += menuManager.cpp\
           nexus.cpp\
           pluginManager.cpp\
           widget/mainwindow.cpp\
    pane.cpp \
    workspace.cpp \
    tabwidget.cpp \
    sidebarManager.cpp \
    menu.cpp \
    containerpane.cpp \
    contentpane.cpp \
    global.cpp \
    widget/subwindow.cpp \
    qtawesomemanager.cpp \
    pagemanager.cpp \
    pageinfo.cpp \
    settingmanager.cpp

DISTFILES += \
    README.md


