#include "sidebarManager.h"
#include <QTreeWidgetItem>
#include <QTreeWidget>
#include "nexus.h"
#include "ui_mainwindow.h"

SidebarManager* SidebarManager::sidebarManager{nullptr};
SidebarManager& SidebarManager::getInstance()
{
    if(sidebarManager == nullptr)
        sidebarManager = new SidebarManager();
    return *sidebarManager;
}

void SidebarManager::destroyInstance()
{
    delete sidebarManager;
}

SidebarManager::SidebarManager()
{
}

SidebarManager::~SidebarManager()
{
}

void SidebarManager::appendItem(QTreeWidgetItem* item)
{
    QTreeWidget* sidebar = getSidebar();
    sidebar->addTopLevelItem(item);
}

QTreeWidget* SidebarManager::getSidebar()
{
   return Nexus::getInstance().getMainWindow()->getUi()->treeWidget;
}

