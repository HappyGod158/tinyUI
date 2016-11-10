#ifndef CONTENTPANE_H
#define CONTENTPANE_H

#include "api_global.h"
#include "pane.h"
#include "tabwidget.h"
#pragma execution_character_set("utf-8")
enum SplitDirection{LEFT, RIGHT, TOP, BOTTOM};

class QJsonObject;

/*!
 * \brief 内容面板
 *
 * 内容面板内部包含了一个tabwidget，页面都在tabwidget中打开
 * 内容面板包含在容器面板中；
 * 内容面板不可以再包含其他面板
 */
class APISHARED_EXPORT ContentPane : public Pane
{
    Q_OBJECT
public:
    /*!
     * \brief 构造函数
     * \param parent
     */
    ContentPane(QWidget* parent = 0);

    /*!
     * \brief 获得内部的tabWidget
     * \return
     */
    TabWidget* getTabWidget();

    /*!
     * \brief 添加页面
     * \param url 页面地址
     * \return 新添加的页面在tabWidget中的位置
     */
    int addTab(const QString &url);

    /*!
     * \brief 查找某个页面的索引
     * \param page 页面对象
     * \return 该页面对象的索引位置，如果不存在，返回-1
     */
    int indexOf(QWidget* page);

    /*!
     * \brief 向左切分内容面板
     *
     * 当前内容面板的左侧会出现一个新的内容面板
     *
     * 内部实现：
     * 1. 创建一个新的容器面板，并将该容器面板的方向设为水平
     * 2. 将新创建的容器面板添加到当前内容面板的父容器面板中
     * 3. 创建一个新的内容面板
     * 4. 将新的内容面板和当前的内容面板移动到新的容器面板中
     * \return 新的内容面板
     */
    ContentPane* splitLeft();


    /*!
     * \brief 向右切分内容面板
     *
     * 当前内容面板的右侧会出现一个新的内容面板
     *
     * 内部实现：
     * 参见splitLeft()
     * \return 新的内容面板
     */
    ContentPane* splitRight();

    /*!
     * \brief 向上切分内容面板
     *
     * 当前内容面板的上方会出现一个新的内容面板
     *
     * 内部实现：
     * 参见splitLeft()
     * \return 新的内容面板
     */
    ContentPane* splitTop();

    /*!
     * \brief 向下切分内容面板
     *
     * 当前内容面板的下方会出现一个新的内容面板
     *
     * 内部实现：
     * 参见splitLeft()
     * \return 新的内容面板
     */
    ContentPane* splitBottom();


    /*!
     * \brief 序列化内容面板，生成Json对象
     *
     *序列化的内容包括：面板方向、大小、页面地址等，格式如下：
     *{
     * type: "ContentPane",
     * orientation: "Horizontal"|"Vertical",
     * size:{"width":width, "height":height}
     * pageUrls:["page1Url", "pageUrl2", ...]
     *}
     *
     * \return Json对象
     */
    QJsonObject serialize();

    /*!
     * \brief 解序列化Json对象，生成内容面板对象
     *
     * Json对象的格式参见serialize()函数
     *
     * \param Json对象
     * \return 内容面板对象
     */
    static Pane* deserialize(QJsonObject& jsonObj);

private:
    ContentPane* split(SplitDirection direction);

private:
    TabWidget *tabWidget;
};

#endif // CONTENTPANE_H
