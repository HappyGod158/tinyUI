#ifndef PLUGIN_MANAGER_H
#define PLUGIN_MANAGER_H

#include "api_global.h"
#include <QDir>
#include <QList>
#include <QObject>

class QPluginLoader;

/*!
 * \brief 插件管理
 */
class APISHARED_EXPORT PluginManager:QObject
{
    Q_OBJECT
public:
    /*!
     * \brief 获取PluginManager实例，单例模式，非线程安全
     * \return PluginManager实例
     */
    static PluginManager& getInstance();

    /*!
     * \brief 删除PluginManager实例
     */
    static void destroyInstance();

    /*!
     * \brief 加载所有插件
     * \return 是否加载成功
     */
    bool loadPlugins(QDir& pluginsDir);

    /*!
     * \brief 卸载所有插件
     * \return 是否卸载成功
     */
    bool unloadPlugins();

signals:
    void loadPluginsComplete();
    void unloadPluginsComplete();

private:
    PluginManager();
    ~PluginManager();

private:
    static PluginManager* pluginManager;
    QList<QPluginLoader*> pluginLoaders;
};

#endif
