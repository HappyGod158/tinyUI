#include "tabwidget.h"
#include "pane.h"
#include "workspace.h"
#include <QTabWidget>
#include <QDebug>
#include <QMimeData>
#include <QDrag>
#include <QDragEnterEvent>
#include <QDragLeaveEvent>
#include <QDragMoveEvent>
#include <QPixmap>
#include <QTabBar>
#include <QDebug>
#include <QPushButton>
#include "subwindow.h"
#include <QMessageBox>
#include "pagemanager.h"

#define CUSTOMFORMAT "application/tabwidgetCurrentIndexData"

#pragma execution_character_set("utf-8")

TabWidget::TabWidget(QWidget* parent): QTabWidget(parent)
{
    //构建action
    setContextMenuPolicy(Qt::ActionsContextMenu);

    QAction* splitLeftAction = new QAction(tr("向左切分"), this);
    addAction(splitLeftAction);
    connect(splitLeftAction, &QAction::triggered, this,  &TabWidget::splitLeft);

    QAction* splitRightAction = new QAction(tr("向右切分"), this);
    addAction(splitRightAction);
    connect(splitRightAction, &QAction::triggered, this,  &TabWidget::splitRight);

    QAction* splitTopAction = new QAction(tr("向上切分"), this);
    addAction(splitTopAction);
    connect(splitTopAction, &QAction::triggered, this,  &TabWidget::splitTop);

    QAction* splitBottomAction = new QAction(tr("向下切分"), this);
    addAction(splitBottomAction);
    connect(splitBottomAction, &QAction::triggered, this,  &TabWidget::splitBottom);

    QAction* closeAction = new QAction(tr("关闭面板"), this);
    addAction(closeAction);
    connect(closeAction, &QAction::triggered, this,  &TabWidget::closePane);

    QAction* separatorAction = new QAction(this);
    separatorAction->setSeparator(true);
    addAction(separatorAction);

    QAction* openInSubwindowAction = new QAction(tr("浮动窗口打开"), this);
    addAction(openInSubwindowAction);
    connect(openInSubwindowAction, &QAction::triggered, this,  &TabWidget::openInSubwindow);

    //关闭标签
    this->setTabsClosable(true);
    connect(this, &TabWidget::tabCloseRequested, this, &TabWidget::closeTab);

    setAcceptDrops(true);

    //tabbar双击时触发activePaneChanged信号
    connect(this->tabBar(), SIGNAL(tabBarClicked(int)), this, SLOT(onTabBarClicked(int)));
}

ContentPane* TabWidget::getContentPane()
{
    return qobject_cast<ContentPane*>(this->parent());
}

void TabWidget::splitLeft()
{
    ContentPane* pane = getContentPane();
    pane->splitLeft();
}

void TabWidget::splitRight()
{
    ContentPane* pane = getContentPane();
    pane->splitRight();
}

void TabWidget::splitTop()
{
    ContentPane* pane = getContentPane();
    pane->splitTop();
}

void TabWidget::splitBottom()
{
    ContentPane* pane = getContentPane();
    pane->splitBottom();
}

void TabWidget::openInSubwindow()
{
    int idx = this->currentIndex();
    if(idx == -1){
        QMessageBox msgBox;
        msgBox.setWindowTitle(tr("提示"));
        msgBox.setText(tr("当前面板无标签页！"));
        msgBox.exec();
        return;
    }

    Workspace &workspace = Workspace::getInstance();
    PageManager &pageManager = PageManager::getInstance();
    QString& url = pageManager.getUrl(this->currentWidget());
    if(url.isEmpty())
        return;
    else{
        this->removeTab(idx);
        workspace.openInSubWindow(url);
    }
}

void TabWidget::closePane()
{
    PageManager &pageManager = PageManager::getInstance();
    for(int i=0;i<count();i++){
        QString& url = pageManager.getUrl(this->widget(i));
        pageManager.unlinkPage(url);
    }

    ContentPane* pane = getContentPane();
    Workspace::getInstance().closePane(pane);
}

void TabWidget::closeTab(int idx)
{
    PageManager &pageManager = PageManager::getInstance();
    QString &url = pageManager.getUrl(this->widget(idx));
    pageManager.unlinkPage(url);

    QWidget *page = this->widget(idx);
    removeTab(idx);
    page->deleteLater();
}


void TabWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat(CUSTOMFORMAT)) {
        if (event->source() == this) {
            event->ignore();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void TabWidget::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat(CUSTOMFORMAT)) {
        if (event->source() == this) {
            event->ignore();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void TabWidget::dropEvent(QDropEvent *event)
{
    changeActivePane();

    if (event->mimeData()->hasFormat(CUSTOMFORMAT)) {
        QByteArray data = event->mimeData()->data(CUSTOMFORMAT);
        QDataStream dataStream(&data, QIODevice::ReadOnly);

        int sourceCurrentIndex;
        dataStream >> sourceCurrentIndex;

        if (event->source() == this) {
            event->ignore();
        } else {
            event->acceptProposedAction();

            TabWidget* source = qobject_cast<TabWidget*>(event->source());
            QWidget* sourceCurrentWidget = source->widget(sourceCurrentIndex);
            QString sourceCurrentText = source->tabText(sourceCurrentIndex);
            source->removeTab(sourceCurrentIndex);
            this->addTab(sourceCurrentWidget, sourceCurrentText);
            this->setCurrentWidget(sourceCurrentWidget);
        }
    } else {
        event->ignore();
    }
}

void TabWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        changeActivePane();
    }

    if(event->button() == Qt::LeftButton) {
        int count = this->count();
        if (count == 0)
            return;

        int currentIndex = this->currentIndex();

        QByteArray data;
        QDataStream dataStream(&data, QIODevice::WriteOnly);
        dataStream << currentIndex;

        QMimeData *mimeData = new QMimeData;
        mimeData->setData(CUSTOMFORMAT, data);

        QRect tabBarRect = this->tabBar()->rect();
        QPixmap pixmap = this->grab(QRect(0, tabBarRect.height(), this->width(), this->height() - tabBarRect.height()));

        QDrag* drag = new QDrag(this);
        drag->setMimeData(mimeData);
        drag->setPixmap(pixmap);

        drag->exec(Qt::MoveAction);

    }
}

void TabWidget::onTabBarClicked(int idx)
{
    changeActivePane();
}

void TabWidget::changeActivePane()
{
    ContentPane *contentPane = qobject_cast<ContentPane*>(this->parentWidget());
    Workspace &workspace = Workspace::getInstance();
    if(workspace.getActiveContentPane() != contentPane)
        emit workspace.activeContentPaneChanged(contentPane);
}

int TabWidget::addTab(QWidget *page, const QString &label)
{
    return QTabWidget::addTab(page, label);
}
