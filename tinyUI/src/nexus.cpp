#include "nexus.h"
#include <QDebug>
#include <QApplication>
#include <cassert>
#include <QDesktopWidget>

Nexus* Nexus::nexus{nullptr};

Nexus::Nexus(QObject *parent) :
    QObject(parent),
    loginScreen{nullptr},
    mainWindow{new MainWindow()}
{
    ((QApplication*)qApp)->setQuitOnLastWindowClosed(true);
}

Nexus::~Nexus()
{
    if(loginScreen){
        delete loginScreen;
        loginScreen = nullptr;
    }

    if(mainWindow){
        delete mainWindow;
        mainWindow = nullptr;
    }
}

Nexus& Nexus::getInstance()
{
    if(!nexus)
        nexus = new Nexus();
    return *nexus;
}

void Nexus::destroyInstance()
{
    delete nexus;
    nexus = nullptr;
}

void Nexus::showLogin()
{
    if(!loginScreen)
        return;
    loginScreen->move(QApplication::desktop()->screen()->rect().center() - loginScreen->rect().center());
    loginScreen->show();
}

void Nexus::showMainWindow()
{
    if(loginScreen)
        loginScreen->close();
    mainWindow->showMaximized();
}

void Nexus::setLoginScreen(QWidget* loginScreen)
{
    this->loginScreen = loginScreen;
}

QWidget* Nexus::getLoginScreen()
{
    return loginScreen;
}

MainWindow* Nexus::getMainWindow()
{
    return mainWindow;
}
