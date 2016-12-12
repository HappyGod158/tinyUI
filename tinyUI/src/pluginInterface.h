#ifndef PLUGININTERFACE_H
#define PLUGININTERFACE_H

#include <QTreeWidgetItem>
#include <QList>
#include <QMenu>
#include "api_global.h"

class Workspace;

/*!
 * \brief 插件接口
 *
 * 在编写插件时，插件需要实现这个接口
 */
class APISHARED_EXPORT PluginInterface
{
public:
    virtual ~PluginInterface(){}

    virtual void initMenu() = 0;

    /*!
     * \brief 初始化侧边栏
     *
     * 插件通过这个函数将导航节点挂载到侧边栏上
     */
    virtual void initSidebar() = 0;

    /*!
     * \brief 初始化页面信息
     *
     * 插件通过这个函数注册页面信息
     */
    virtual void initPage() = 0;
};

QT_BEGIN_NAMESPACE

#define PluginInterface_iid "org.dwzq.stormTrader.plugininterface"

Q_DECLARE_INTERFACE(PluginInterface, PluginInterface_iid)
QT_END_NAMESPACE

#endif // PLUGININTERFACE_H
