#include "pluginManager.h"
#include <QPluginLoader>
#include "pluginInterface.h"
#include <QApplication>
#include "nexus.h"
#include "workspace.h"
#include "settingmanager.h"

PluginManager* PluginManager::pluginManager{nullptr};

PluginManager::PluginManager()
{

}

PluginManager& PluginManager::getInstance()
{
    if(pluginManager==nullptr)
        pluginManager = new PluginManager();
    return *pluginManager;
}

void PluginManager::destroyInstance()
{
    delete pluginManager;
}

PluginManager::~PluginManager()
{
    foreach (QPluginLoader* pluginLoader, pluginLoaders) {
        delete pluginLoader;
    }
}

bool PluginManager::loadPlugins(QDir& pluginsDir)
{
    if(!pluginsDir.exists())
        return false;
    //加载插件
    foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
//        if(fileName.endsWith(".dll") == false)
//            continue;
        QPluginLoader* pluginLoader = new QPluginLoader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = pluginLoader->instance();
        if (plugin) {
            PluginInterface* pluginInterface = qobject_cast<PluginInterface*>(plugin);
            if (pluginInterface) {
                pluginLoaders.append(pluginLoader);
            }
        }
    }

    //初始化插件
    foreach (QPluginLoader* pluginLoader, pluginLoaders) {
        QObject *plugin = pluginLoader->instance();
        PluginInterface* pluginInterface = qobject_cast<PluginInterface*>(plugin);
        pluginInterface->initMenu();
        pluginInterface->initSidebar();
        pluginInterface->initPage();
    }

    //恢复工作区状态
    Workspace& workspace = Workspace::getInstance();
    if(workspace.isAutoRestore())
        SettingManager::getInstance().readSettings();

    emit loadPluginsComplete();
    return true;
}

bool PluginManager::unloadPlugins()
{
    foreach (QPluginLoader* pluginLoader, pluginLoaders) {
        pluginLoader->unload();
    }
    emit unloadPluginsComplete();
    return true;
}
