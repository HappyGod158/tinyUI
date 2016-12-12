#include "pagemanager.h"


PageManager* PageManager::pageManager{nullptr};

PageManager& PageManager::getInstance()
{
    if(!pageManager)
        pageManager = new PageManager();
    return *pageManager;
}

void PageManager::destoryInstance()
{
    delete pageManager;
    pageManager = nullptr;
}

PageManager::PageManager(QObject *parent) : QObject(parent)
{

}

void PageManager::registerPageInfo(const QString& url, PageInfo* pageInfo)
{
    pageHash.insert(url, pageInfo);
}

void PageManager::unregisterPageInfo(const QString& url)
{
    pageHash.remove(url);
}

bool PageManager::isPageInfoRegistered(const QString& url)
{
    return pageHash.contains(url);
}

PageInfo* PageManager::getPageInfo(const QString& url)
{
    if(pageHash.contains(url))
        return pageHash.value(url);
    else
        return nullptr;
}

QWidget* PageManager::getPage(const QString& url)
{
    PageInfo *pageInfo = getPageInfo(url);
    if(!pageInfo){
        return nullptr;
    }else{
        return pageInfo->getPage();
    }
}

QString PageManager::getUrl(QWidget* widget)
{
    if(!widget)
        return QString();
    else{
        auto i = pageHash.constBegin();
        while (i != pageHash.constEnd()) {
            PageInfo* pageInfo = i.value();
            if(pageInfo->getPage() == widget)
                return i.key();
            i++;
        }
        return QString();
    }
}

bool PageManager::isPageOpened(const QString& url)
{
    QWidget* page = getPage(url);
    if(!page)
        return false;
    else
        return true;
}

bool PageManager::linkPage(const QString& url, QWidget* page)
{
    PageInfo* pageInfo = getPageInfo(url);
    if(!pageInfo)
        return false;
    else{
        pageInfo->setPage(page);
        return true;
    }
}

bool PageManager::unlinkPage(const QString& url)
{
    PageInfo* pageInfo = getPageInfo(url);
    if(!pageInfo)
        return false;
    else{
        pageInfo->setPage(nullptr);
        return true;
    }
}

bool PageManager::constructPage(const QString& url, QWidget* &constructedPage)
{
    if(!isPageInfoRegistered(url)){
        constructedPage = nullptr;
        return false;
    }

    PageInfo* pageInfo = getPageInfo(url);
    QWidget* page = pageInfo->getPage();
    if(page){
        constructedPage = page;
        return true;
    }else{
        constructedPage = pageInfo->getConstructor()();
        linkPage(url, constructedPage);
        return true;
    }
}

