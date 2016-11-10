#ifndef SETTINGMANAGER_H
#define SETTINGMANAGER_H

#include <QObject>
#include "api_global.h"


/*!
 * \brief 配置管理
 *
 * 配置管理的作用是保存和恢复窗口工作区状态
 */
class APISHARED_EXPORT SettingManager : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief 获取SettingManager实例，单例模式，非线程安全
     * \return SettingManager实例
     */
    static SettingManager& getInstance();

    /*!
     * \brief 删除SettingManager实例
     */
    static void destroyInstance();

    /*!
     * \brief 读取配置文件
     *
     * 实现时使用QSettings来读写配置，QSettings根据程序的的organizationName和
     * applicationName来获得文件位置。
     * 所以主程序需要做如下设置：
     *  QCoreApplication::setOrganizationName("orgName");
     *  QCoreApplication::setApplicationName("appName");
     *
     * 如果主程序中不做设置，那么tingUI提供默认值：
     *  organizationName = tinyUI-Dev
     *  applicationName = tinyUI
     */
    void readSettings();

    /*!
     * \brief 写入配置文件
     */
    void writeSettings();


private:
    explicit SettingManager(QObject *parent = 0);
    void reconstructWorkspace(QJsonArray& subPanes);

private:
    static SettingManager* settingManager;
    QString orgName;
    QString appName;
};

#endif // SETTINGMANAGER_H
