#include "contentpane.h"
#include "containerpane.h"
#include <QDebug>
#include "workspace.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QTabBar>
#include "pagemanager.h"

ContentPane::ContentPane(QWidget *parent):Pane(parent)
{
    tabWidget = new TabWidget(this);
    addWidget(tabWidget);
}

TabWidget* ContentPane::getTabWidget()
{
    return tabWidget;
}

int ContentPane::addTab(const QString &url)
{
    PageManager &pageManager = PageManager::getInstance();
    QWidget* page = pageManager.getPage(url);
    QString& label = pageManager.getPageInfo(url)->getLabel();
    if(page == nullptr)
        return -1;

    int idx = tabWidget->addTab(page, label);
    tabWidget->setCurrentWidget(page);
    return idx;
}

int ContentPane::indexOf(QWidget* page)
{
    return tabWidget->indexOf(page);
}


ContentPane* ContentPane::splitLeft()
{
    return split(SplitDirection::LEFT);
}

ContentPane* ContentPane::splitRight()
{
    return split(SplitDirection::RIGHT);
}

ContentPane* ContentPane::splitTop()
{
    return split(SplitDirection::TOP);
}

ContentPane* ContentPane::splitBottom()
{
    return split(SplitDirection::BOTTOM);
}

ContentPane* ContentPane::split(SplitDirection direction)
{
    int width = this->width();
    int height = this->height();

    QList<int> sizeForHorizontal = {width/2, width/2};
    QList<int> sizeForVertical = {height/2, height/2};

    QList<int> sizeForHorizontalParent = {width, width};
    QList<int> sizeForVerticalParent = {height, height};

    ContainerPane *parentContainerPane = qobject_cast<ContainerPane*>(parentWidget());
    int idxInParentContainerPane = parentContainerPane->indexOf(this);
    ContainerPane *newContainerPane = new ContainerPane();
    this->setParent(newContainerPane);
    parentContainerPane->insertWidget(idxInParentContainerPane, newContainerPane);



    ContentPane *newContentPane = new ContentPane(newContainerPane);

    int idxNewContentPane;
    switch (direction) {
    case SplitDirection::LEFT:
        newContainerPane->setOrientation(Qt::Horizontal);
        idxNewContentPane = 0;
        newContainerPane->insertWidget(idxNewContentPane, newContentPane);
        newContainerPane->setSizes(sizeForHorizontal);
        parentContainerPane->setSizes(sizeForHorizontalParent);
        break;
    case SplitDirection::RIGHT:
        newContainerPane->setOrientation(Qt::Horizontal);        
        idxNewContentPane = 1;
        newContainerPane->insertWidget(idxNewContentPane, newContentPane);
        newContainerPane->setSizes(sizeForHorizontal);
        parentContainerPane->setSizes(sizeForHorizontalParent);
        break;
    case SplitDirection::TOP:
        newContainerPane->setOrientation(Qt::Vertical);
        idxNewContentPane = 0;
        newContainerPane->insertWidget(idxNewContentPane, newContentPane);
        newContainerPane->setSizes(sizeForVertical);
        parentContainerPane->setSizes(sizeForVerticalParent);
        break;
    case SplitDirection::BOTTOM:
        newContainerPane->setOrientation(Qt::Vertical);
        idxNewContentPane = 1;
        newContainerPane->insertWidget(idxNewContentPane, newContentPane);
        newContainerPane->setSizes(sizeForVertical);
        parentContainerPane->setSizes(sizeForVerticalParent);
        break;
    default:
        break;
    }
    emit Workspace::getInstance().activeContentPaneChanged(newContentPane);
    return newContentPane;
}

QJsonObject ContentPane::serialize()
{
    QJsonObject paneState;
    QJsonArray pageUrlsArray;
    Qt::Orientation orientation = this->orientation();
    QString paneName = "ContentPane";
    paneState.insert("type", paneName);
    paneState.insert("orientation", orientation == Qt::Horizontal ? "Horizontal" : "Vertical");

    int count = this->tabWidget->count();
    PageManager &pageManager = PageManager::getInstance();
    for(int i=0; i<count; i++){
        QJsonValue url = pageManager.getUrl(tabWidget->widget(i));
        pageUrlsArray.append(url);
    }
    paneState.insert("pageUrls",pageUrlsArray);

    QSize size = this->size();
    QJsonObject sizeObj;
    sizeObj.insert("width", size.width());
    sizeObj.insert("height", size.height());
    paneState.insert("size", sizeObj);

    return paneState;
}

Pane* ContentPane::deserialize(QJsonObject& jsonObj)
{
    ContentPane* pane = new ContentPane();
    QJsonArray &pageUrls = jsonObj.value("pageUrls").toArray();

    for(int i=0; i<pageUrls.count(); i++){
        QString& url = pageUrls.at(i).toString();
        PageManager &pageManager = PageManager::getInstance();
        QWidget* page;
        bool rst = pageManager.constructPage(url, page);
        if(!rst)
            continue;
        pane->addTab(url);
    }

    QJsonObject &sizeObj = jsonObj.value("size").toObject();
    QSize size;
    size.setWidth(sizeObj.value("width").toInt());
    size.setHeight(sizeObj.value("height").toInt());
    pane->resize(size);

    return pane;
}
