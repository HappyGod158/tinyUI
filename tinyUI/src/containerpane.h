#ifndef CONTAINERPANE_H
#define CONTAINERPANE_H

#include "api_global.h"
#include "pane.h"

/*!
 * \brief 容器面板
 *
 * 容器面板可以包含内容面板，也可以包含容器面板，主要用于工作区的任意分割
 */
class APISHARED_EXPORT ContainerPane : public Pane
{
    Q_OBJECT
public:
    /*!
     * \brief 构造函数
     * \param parent
     */
    ContainerPane(QWidget *parent = 0);

    /*!
     * \brief 添加子面板
     * \param pane
     */
    void addPane(Pane *pane);

    /*!
     * \brief 序列化容器面板，生成Json对象
     *
     *序列化的内容包括：面板方向、大小、子面板等，格式如下：
     *{
     * type: "ContainerPane",
     * orientation: "Horizontal"|"Vertical",
     * size:{"width":width, "height":height}
     * subPanes:[{...},{...},...]
     *}
     *
     * \return Json对象
     */
    QJsonObject serialize();

    /*!
     * \brief 解序列化Json对象，生成容器面板对象
     *
     * Json对象的格式参见serialize()函数
     *
     * \param Json对象
     * \return 容器面板对象
     */
    static Pane* deserialize(QJsonObject& jsonObj);
};

#endif // CONTAINERPANE_H
