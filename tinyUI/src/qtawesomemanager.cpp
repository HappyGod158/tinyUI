#include "qtawesomemanager.h"

QtAwesome* QtAwesomeManager::qtawesome = nullptr;
QtAwesomeManager::QtAwesomeManager(QObject *parent) : QObject(parent)
{
}

QtAwesome& QtAwesomeManager::getInstance()
{
    if(qtawesome == nullptr){
        qtawesome = new QtAwesome();
        qtawesome->initFontAwesome();
    }
    return *qtawesome;
}

void QtAwesomeManager::destoryInstance()
{
    if(qtawesome){
        delete qtawesome;
        qtawesome = nullptr;
    }
}

