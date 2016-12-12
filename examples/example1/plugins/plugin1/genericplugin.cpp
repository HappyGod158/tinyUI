#include "genericplugin.h"


GenericPlugin::GenericPlugin()
{
    rootItem = new QTreeWidgetItem();
    QColor color = QColor("gray");
    rootItem->setBackground(0,QBrush(color));
    rootItem->setText(0, "页面列表");

    page1Item = new QTreeWidgetItem(rootItem);
    page1Item->setText(0, "page1");

    page2Item = new QTreeWidgetItem(rootItem);
    page2Item->setText(0, "page2");

    page3Item = new QTreeWidgetItem(rootItem);
    page3Item->setText(0, "page3");

    page1Url = "page://plugin1-page1";
    page2Url = "page://plugin1-page2";
    page3Url = "page://plugin1-page3";
}

void GenericPlugin::initMenu()
{

}

void GenericPlugin::initSidebar()
{
    SidebarManager& sidebarManager = SidebarManager::getInstance();
    sidebarManager.appendItem(rootItem);
    sidebarManager.getSidebar()->expandAll();
    QObject::connect(sidebarManager.getSidebar(), &QTreeWidget::itemDoubleClicked, this, &GenericPlugin::onItemDoubleClicked);
}

void GenericPlugin::initPage()
{
    PageManager& pageManager = PageManager::getInstance();
    PageInfo *page1Info = new PageInfo(page1Url, "页面1", []()->QWidget*{return new Page1();});
    PageInfo *page2Info = new PageInfo(page2Url, "页面2", []()->QWidget*{return new Page2();});
    PageInfo *page3Info = new PageInfo(page3Url, "页面3", []()->QWidget*{return new Page3();});

    pageManager.registerPageInfo(page1Url, page1Info);
    pageManager.registerPageInfo(page2Url, page2Info);
    pageManager.registerPageInfo(page3Url, page3Info);
}

void GenericPlugin::onItemDoubleClicked(QTreeWidgetItem* item, int column)
{
    Workspace& workspace = Workspace::getInstance();
    if(item == page1Item)
    {
        workspace.open(page1Url);
    }
    if(item == page2Item)
    {
        workspace.open(page2Url);
    }
    if(item == page3Item)
    {
       workspace.open(page3Url);
    }
}

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(plugin1, GenericPlugin)
#endif // QT_VERSION < 0x050000
