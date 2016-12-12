#include "menuManager.h"
#include "nexus.h"
#include <QDebug>

MenuManager* MenuManager::menuManager{nullptr};

MenuManager& MenuManager::getInstance()
{
    if(!menuManager)
        menuManager = new MenuManager();
    return *menuManager;
}

void MenuManager::addMenu(Menu* menu)
{
    QList<QString> path = menu->getPath();
    int pathSize = path.size();
    if(pathSize == 0)
        return;

    QList<QObject*> foundList = searchMenuBar(menu);

    int foundSize = foundList.size();

    //待插入路径已经存在，不做处理
    if(foundSize == pathSize)
        return;

    if(pathSize == 1)//处理插入顶级菜单的情况
    {
        getMenuBar()->addMenu(qobject_cast<QMenu*>(menu->getObj()));
    }else//处理多级菜单的情况
    {
        QMenu* qmenu;
        if(foundSize == 0)
        {
            qmenu = getMenuBar()->addMenu(path[0]);
            foundSize = 1;
        }
        else
            qmenu = qobject_cast<QMenu*>(foundList.last());
        for(int i = foundSize; i < pathSize - 1; i++)
        {
            qmenu = qmenu->addMenu(path[i]);
        }
        qmenu->addAction(qobject_cast<QAction*>(menu->getObj()));
    }
}

QMenuBar* MenuManager::getMenuBar()
{
    return Nexus::getInstance().getMainWindow()->menuBar();
}

QList<QObject*> MenuManager::searchMenuBar(Menu* menu)
{
    QMenuBar* menuBar = getMenuBar();
    QList<QMenu*> topMenuList = menuBar->findChildren<QMenu*>();

    QList<QObject*> foundList;
    foreach (QMenu* qmenu, topMenuList) {
        QList<QString> path = menu->getPath();
        QList<QObject*> foundListTmp;
        bool rst = searchMenu(qmenu, path, foundListTmp, 0);
        if(rst)
        {
            return foundListTmp;
        }
        if(foundList.size() < foundListTmp.size())
            foundList = foundListTmp;
    }
    return foundList;
}

bool MenuManager::searchMenu(QMenu* menu, QList<QString>& path, QList<QObject*>& foundList, int pathIndex)
{
    int pathSize = path.size();
    if(pathIndex == pathSize)
        return false;

    qDebug() << menu->title();
    qDebug() << path[pathIndex];
    if(menu->title() != path[pathIndex])
        return false;

    foundList.append(menu);
    pathIndex++;


    menu->dumpObjectTree();
    QList<QAction*> actionList = menu->findChildren<QAction*>(QString(), Qt::FindDirectChildrenOnly);
    int num = actionList.removeAll(menu->menuAction());
    QList<QMenu*> subMenuList = menu->findChildren<QMenu*>(QString(), Qt::FindDirectChildrenOnly);


    if(pathIndex != pathSize - 1)//在subMenuList中搜索
    {
        foreach (QMenu* subMenu, subMenuList)
        {
            bool rst = searchMenu(subMenu, path, foundList, pathIndex + 1);
            if(rst)
                return true;
            else
                continue;
        }
    }else//在actionList中搜索
    {
        foreach (QAction* action, actionList) {
            if(action->text() == path[pathIndex])
            {
                foundList.append(action);
                return true;
            }
        }
    }

    return false;
}
