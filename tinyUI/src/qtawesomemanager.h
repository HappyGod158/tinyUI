#ifndef QTAWESOMEMANAGER_H
#define QTAWESOMEMANAGER_H

#include <QObject>
#include "api_global.h"
#include "../QtAwesome/QtAwesome.h"

/*!
 * \brief QtAwesome对象获取
 *
 * QtAwesome使得FontAwesome可以在Qt中使用，具体使用方法参见：
 * https://github.com/gamecreature/QtAwesome/tree/font-awesome-4.3.0
 */
class APISHARED_EXPORT QtAwesomeManager : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief 获取QtAwesome实例，单例模式，非线程安全
     * \return QtAwesome实例
     */
    static QtAwesome& getInstance();

    /*!
     * \brief 删除QtAwesome实例
     */
    static void destoryInstance();
private:
    explicit QtAwesomeManager(QObject *parent = 0);
private:
    static QtAwesome *qtawesome;
};

#endif // QTAWESOMEMANAGER_H
