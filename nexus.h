#ifndef NEXUS_H
#define NEXUS_H

#include <QObject>
#include "widget/mainwindow.h"

#include "api_global.h"


/*!
 * \brief 窗口管理
 *
 * 该类管理两个窗口：登录窗口和主窗口
 *
 */
class APISHARED_EXPORT Nexus: public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief 获取实例，单例模式，非线程安全
     * \return
     */
    static Nexus& getInstance();

    /*!
     * \brief 删除实例
     */
    static void destroyInstance();

    /*!
     * \brief 获取登录界面
     * \return
     */
    QWidget* getLoginScreen();

    /*!
     * \brief 获取主窗口
     * \return
     */
    MainWindow* getMainWindow();

    /*!
     * \brief 显示登录窗口
     */
    void showLogin();

    /*!
     * \brief 显示主窗口
     */
    void showMainGUI();

    /*!
     * \brief 设置登录界面
     * \param loginScreen
     */
    void setLoginScreen(QWidget* loginScreen);

private:
    explicit Nexus(QObject *parent = 0);
    ~Nexus();

private:
    static Nexus* nexus;
    QWidget* loginScreen;
    MainWindow* mainWindow;
};

#endif // NEXUS_H

