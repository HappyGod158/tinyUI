#ifndef PAGEINFO_H
#define PAGEINFO_H

#include "api_global.h"
#include <QString>
#include <functional>

class QWidget;

/*!
 * \brief 页面信息
 *
 * 该类提供页面信息
 */
class APISHARED_EXPORT PageInfo
{
public:
    /*!
     * \brief 构造函数
     * \param url 页面地址
     * \param label 页面在tabWidget的tabbar上显示的文字
     * \param constructor 函数对象，调用这个函数对象可以获得该页面对象
     */
    PageInfo(const QString& url, const QString& label, std::function<QWidget*()> constructor);

    /*!
     * \brief getUrl
     * \return
     */
    QString& getUrl();

    /*!
     * \brief setUrl
     * \param url
     */
    void setUrl(const QString &url);

    /*!
     * \brief getLabel
     * \return
     */
    QString& getLabel();

    /*!
     * \brief setLabel
     * \param label
     */
    void setLabel(const QString& label);

    /*!
     * \brief getPage
     * \return
     */
    QWidget* getPage();

    /*!
     * \brief setPage
     * \param page
     */
    void setPage(QWidget *page);

    /*!
     * \brief getConstructor
     * \return
     */
    std::function<QWidget*()> getConstructor();

    /*!
     * \brief setConstructor
     * \param constructor
     */
    void setConstructor(std::function<QWidget*()>& constructor);

    bool isPageEmpty();

private:
    PageInfo();

private:
    QString url;
    QString label;
    QWidget* page;
    std::function<QWidget*()> constructor;
};

#endif // PAGEINFO_H
