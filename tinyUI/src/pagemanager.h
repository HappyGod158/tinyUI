#ifndef PAGEMANAGER_H
#define PAGEMANAGER_H

#include "api_global.h"
#include <QObject>
#include "pageinfo.h"
#include <QHash>


/*!
 * \brief 管理所有页面
 *
 * 内部实现：
 * 内部保存了一个hash，键是页面地址，值是PageInfo指针
 */
class APISHARED_EXPORT PageManager : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief 获得PageManager对象，单例模式，非线程安全
     * \return PageManager对象
     */
    static PageManager& getInstance();

    /*!
     * \brief 删除PageManager对象
     */
    static void destoryInstance();

    /*!
     * \brief 注册页面信息
     * \param url 页面地址
     * \param pageInfo
     */
    void registerPageInfo(const QString& url, PageInfo* pageInfo);

    /*!
     * \brief 取消注册页面信息
     * \param url
     */
    void unregisterPageInfo(const QString& url);

    /*!
     * \brief 判断页面信息是否注册
     * \param url
     * \return
     */
    bool isPageInfoRegistered(const QString& url);

    /*!
     * \brief 获得地址对应的页面信息，如果地址未注册，那么返回空
     * \param url
     * \return
     */
    PageInfo* getPageInfo(const QString& url);

    /*!
     * \brief 获得地址对应的页面对象，如果地址未注册，那么返回空；
     * 如果地址已注册，那么返回对应的PageInfo对象的page值，可能为空
     * \param url
     * \return
     */
    QWidget* getPage(const QString& url);

    /*!
     * \brief 根据页面对象获得对应的页面地址，如果没有对应的地址，那么
     * 返回空字符串
     * \param widget
     * \return
     */
    QString getUrl(QWidget* widget);

    /*!
     * \brief 将页面对象和页面url关联
     * \param url
     * \param page
     * \return
     */
    bool linkPage(const QString& url, QWidget* page);

    /*!
     * \brief 取消页面地址和所对应的页面对象间的关联
     * \param url
     * \return
     */
    bool unlinkPage(const QString& url);

    /*!
     * \brief 查看页面地址是否已经打开
     * \param url
     * \return
     */
    bool isPageOpened(const QString& url);

    /*!
     * \brief 根据注册的页面信息，构造页面地址对应的页面对象
     * \param url
     * \param constructedPage
     * \return 构造后的页面对象的指针是constructedPage，bool返回值用于
     * 告知调用者页面对象是否构造成功
     */
    bool constructPage(const QString& url, QWidget* &constructedPage);


private:
    explicit PageManager(QObject *parent = 0);

private:
     static PageManager *pageManager;
    //key: url, value: pageinfo
    QHash<QString, PageInfo*> pageHash;
};

#endif // PAGEMANAGER_H
