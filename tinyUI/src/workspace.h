#ifndef WORKSPACE_MANAGER_H
#define WORKSPACE_MANAGER_H

#include <QWidget>
#include "api_global.h"
#include "containerpane.h"
#include "contentpane.h"
#include <QHash>
#include <functional>
#include "pagemanager.h"

class MainWindow;
/*!
  \class Workspace
  \brief 管理工作区
*/
class APISHARED_EXPORT Workspace:QObject
{
    Q_OBJECT
public:
    /*! 获得Workspace实例，单例模式，非线程安全*/
    static Workspace& getInstance();

    /*! 删除Workspace实例*/
    static void destoryInstance();

    /*!
     * \brief 在主窗口的工作区中打开页面
     * \param url 页面地址
     */
    void open(QString& url);

    /*!
     * \brief 检查页面是否打开
     * \param url 页面地址
     * \return
     */
    bool isOpen(QString& url);

    /*!
     * \brief 在新的浮动窗口中打开页面
     * \param url 页面地址
     */
    void openInSubWindow(QString& url);

    /*!
     * \brief 设置工作区是否自动恢复成上次关闭时的状态
     * \param autoRestore
     */
    void setAutoRestore(bool autoRestore);

    /*!
     * \brief 获取是否自动恢复工作区
     * \return
     */
    bool isAutoRestore();

    /*!
     * \brief 在主窗口左下角的临时消息区显示消息
     * \param message 待显示的消息内容
     */
    void showTempMessage(QString& message);

    /*!
     * \brief 清除临时消息
     */
    void clearTempMessage();

    /*!
     * \brief 显示与服务器的连通性信息
     * \param status 连通性信息
     */
    void setConnectivity(QString& status);

signals:
    /*!
     * \brief 工作区的活动面板改变时触发该信号
     * \param activeContentPane
     */
    void activeContentPaneChanged(ContentPane *activeContentPane);

public slots:
    void onActiveContentPaneChanged(ContentPane *activeContentPane);

public:
    ContainerPane* getRootPane();
    void setRootPane(ContainerPane *rootPane);
    void closePane(Pane *pane);

    ContentPane* getActiveContentPane();

    QList<ContentPane*> getContentPanes();

    ContentPane* searchTab(QString& url);

    void setActiveContentPane(ContentPane *contentPane);
    void activateNextContentPane();
    void activatePreviousContentPane();

private:
    Workspace();
    ~Workspace();

private:
    static Workspace *workspace;
    ContainerPane *rootPane;
    ContentPane *activeContentPane;
    bool autoRestore;
};
#endif
