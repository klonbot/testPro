#include "cacheitem.h"

CacheItem::CacheItem(CacheItem *parent):
    cacheData(0)
{
    isNew = true;
    isRoot_t isRoot = (NULL == parent) ? isRoot_true : isRoot_false;
    cacheData.setIsRoot(isRoot);
    Parent = parent;
    cacheData.setIsDeleted(isDeleted_false);
    if (false == isRoot)
    {
        parent->addChild(this);
    }
}

void CacheItem::deleteItem(void)
{
    cacheData.setIsDeleted(isDeleted_true);
    for (int ind = 0; ind < getNumChildren(); ++ind)
    {
        CacheItem *pCasheChild = getChild(ind);
        pCasheChild->deleteItem();
    }
}

