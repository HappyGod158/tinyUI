#ifndef MENU_MANAGER_H
#define MENU_MANAGER_H

#include "api_global.h"
#include "menu.h"
#include <QMenuBar>

class APISHARED_EXPORT MenuManager
{
public:
    static MenuManager& getInstance();
    static void destoryInstance();

    void addMenu(Menu* menu);

    QMenuBar* getMenuBar();

    QList<QObject*> searchMenuBar(Menu* menu);
    bool searchMenu(QMenu* menu, QList<QString>& path, QList<QObject*>& foundList, int pathIndex);
private:
    static MenuManager* menuManager;
};

#endif
