#ifndef PANE_H
#define PANE_H

#include "api_global.h"
#include <QSplitter>
#include <QString>

class QJsonObject;

/*!
 * \brief 面板
 *
 * 该类是一个抽象类，代表工作区的分割窗口
 * 面板有两个子类：容器面板和内容面板
 */
class APISHARED_EXPORT Pane: public QSplitter
{
    Q_OBJECT
public:
    /*!
     * \brief 构造函数
     * \param parant
     */
    Pane(QWidget* parent = 0);

    /*!
     * \brief 判断是否是根面板
     * \return bool
     */
    bool isRootPane();

    /*!
     * \brief 将面板序列化
     *
     * 纯虚函数，将面板序列化，在重新打开应用后通过保存的序列化文件恢复工作区状态
     * \return 序列化后的Json对象
     */
    virtual QJsonObject serialize() = 0;
};

#endif // PANE_H
