#ifndef SIDEBAR_MANAGER_H
#define SIDEBAR_MANAGER_H

#include "api_global.h"

class QTreeWidgetItem;
class QTreeWidget;

/*!
 * \brief 侧边栏管理
 *
 * 侧边栏位于主窗口的左侧，是一个树形结构的导航栏。
 * 内部是用QTreeWidget实现的。
 */
class APISHARED_EXPORT SidebarManager
{
public:
    /*!
     * \brief 获取SidebarManager实例，单例模式，非线程安全
     * \return SidebarManager实例
     */
    static SidebarManager& getInstance();

    /*!
     * \brief 删除实例
     */
    static void destroyInstance();


    /*!
     * \brief 在侧边栏添加节点
     * \param 添加的节点
     */
    void appendItem(QTreeWidgetItem* item);

    /*!
     * \brief 获取侧边栏的QTreeWidget对象
     * \return QTreeWidget对象
     */
    QTreeWidget* getSidebar();

private:
    SidebarManager();
    ~SidebarManager();

private:
    static SidebarManager* sidebarManager;


};

#endif
