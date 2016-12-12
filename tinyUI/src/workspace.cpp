#include "workspace.h"
#include "nexus.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QMessageBox>
#include <QDebug>
#include <cassert>
#include "nexus.h"
#include "subwindow.h"
#include "pagemanager.h"

Workspace* Workspace::workspace{nullptr};

Workspace& Workspace::getInstance()
{
    if(!workspace)
        workspace = new Workspace();
    return *workspace;
}

void Workspace::destoryInstance()
{
    delete workspace;
    workspace = nullptr;
}

Workspace::Workspace():rootPane{nullptr}, activeContentPane{nullptr}, autoRestore{true}
{
    connect(this, SIGNAL(activeContentPaneChanged(ContentPane*)), this, SLOT(onActiveContentPaneChanged(ContentPane*)));
}

Workspace::~Workspace()
{
    delete rootPane;
}

ContainerPane* Workspace::getRootPane()
{
    return rootPane;
}

void Workspace::setRootPane(ContainerPane *rootPane)
{
    this->rootPane = rootPane;
}

QList<ContentPane*> Workspace::getContentPanes()
{
    QList<ContentPane*> contentPaneList;
    if(rootPane == nullptr)
        return contentPaneList;
    contentPaneList = rootPane->findChildren<ContentPane*>();
    return contentPaneList;
}

bool Workspace::isOpen(QString& url)
{
    PageManager &pageManager = PageManager::getInstance();
    return pageManager.isPageOpened(url);
}

ContentPane* Workspace::searchTab(QString& url)
{
    PageManager &pageManager = PageManager::getInstance();

    QWidget* page = pageManager.getPage(url);
    if(page == nullptr)
        return nullptr;
    QList<ContentPane*> list = getContentPanes();
    for(int i=0; i<list.size(); i++){
        if(list[i]->indexOf(page) != -1)
            return list[i];
    }
    return nullptr;
}

void Workspace::open(QString& url)
{
    if(rootPane == nullptr){
        return;
    }
    PageManager &pageManager = PageManager::getInstance();
//    QWidget* page = pageManager.getPage(url);
    ContentPane *contentPaneOpenedIn = searchTab(url);
    if(contentPaneOpenedIn != nullptr){//已经打开
        setActiveContentPane(contentPaneOpenedIn);
        QWidget* page = pageManager.getPage(url);
        contentPaneOpenedIn->getTabWidget()->setCurrentWidget(page);
    }
    else{//未打开
        QWidget* page;
        bool rst = pageManager.constructPage(url, page);
        if(!rst)
            return;
        ContentPane *activeContentPane = getActiveContentPane();
        if(activeContentPane == nullptr){
            QList<ContentPane*> list = getContentPanes();
            if(list.size() == 0){
                ContentPane *newContentPane = new ContentPane(rootPane);
                rootPane->addPane(newContentPane);
                newContentPane->addTab(url);
                emit this->activeContentPaneChanged(newContentPane);
            }else{
                emit this->activeContentPaneChanged(list[0]);
                list[0]->addTab(url);
                list[0]->getTabWidget()->setCurrentWidget(page);
            }
        }else{
            activeContentPane->addTab(url);
        }
    }
}

void Workspace::openInSubWindow(QString& url)
{
    SubWindow *subWindow = new SubWindow(url);
    subWindow->show();
}

void Workspace::setAutoRestore(bool autoRestore)
{
    this->autoRestore = autoRestore;
}

bool Workspace::isAutoRestore()
{
    return autoRestore;
}


ContentPane* Workspace::getActiveContentPane()
{
    return activeContentPane;
}

void Workspace::setActiveContentPane(ContentPane *contentPane)
{
    this->activeContentPane = contentPane;
}

void Workspace::activateNextContentPane()
{

}

void Workspace::activatePreviousContentPane()
{

}

void Workspace::closePane(Pane *pane)
{
    emit this->activeContentPaneChanged(nullptr);
    if(!pane || pane->isRootPane())
        return;
    QWidget *parent = pane->parentWidget();
    pane->setParent(nullptr);
    pane->deleteLater();

    if(parent != nullptr){
        Pane *parentPane = qobject_cast<Pane*>(parent);
        if(parentPane && parentPane->count() == 0){
            closePane(parentPane);
            return;
        }
    }
}

void Workspace::onActiveContentPaneChanged(ContentPane *activeContentPane)
{
    this->setActiveContentPane(activeContentPane);
}

void Workspace::showTempMessage(QString& message)
{
     MainWindow *mainWindow = Nexus::getInstance().getMainWindow();
     mainWindow->statusBar()->showMessage(message);
}

void Workspace::clearTempMessage()
{
    MainWindow *mainWindow = Nexus::getInstance().getMainWindow();
    mainWindow->statusBar()->clearMessage();
}

void Workspace::setConnectivity(QString& status)
{
    MainWindow *mainWindow = Nexus::getInstance().getMainWindow();
    mainWindow->getConnectivityLabel()->setText(status);
}
