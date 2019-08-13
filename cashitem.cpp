#include "cacheitem.h"

CacheItem::CacheItem(CacheItem *parent):
    cacheData(0)
{
    isNew = true;    
    bool isRoot = (NULL == parent) ? true : false;
    cacheData.setIsRoot(isRoot);
    Parent = parent;
    cacheData.setIsDeleted(false);
    if (false == isRoot)
    {
        parent->addChild(this);
    }
}

void CacheItem::deleteItem(void)
{
    cacheData.setIsDeleted(true);
    for (int ind = 0; ind < getNumChildren(); ++ind)
    {
        CacheItem *pCasheChild = getChild(ind);
        pCasheChild->deleteItem();
    }
}


