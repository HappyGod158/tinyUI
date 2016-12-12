#include "pageinfo.h"

PageInfo::PageInfo()
{

}

PageInfo::PageInfo(const QString &url, const QString &label, std::function<QWidget*()> constructor)
{
    this->url = url;
    this->label = label;
    this->constructor = constructor;
    page = nullptr;
}

QString& PageInfo::getUrl()
{
    return this->url;
}

void PageInfo::setUrl(const QString &url)
{
    this->url = url;
}

QString& PageInfo::getLabel()
{
    return this->label;
}

void PageInfo::setLabel(const QString& label)
{
    this->label = label;
}

QWidget* PageInfo::getPage()
{
    return page;
}

void PageInfo::setPage(QWidget *page)
{
    this->page = page;
}

std::function<QWidget*()> PageInfo::getConstructor()
{
    return constructor;
}

void PageInfo::setConstructor(std::function<QWidget*()>& constructor)
{
    this->constructor = constructor;
}

bool PageInfo::isPageEmpty()
{
    return page == nullptr;
}
