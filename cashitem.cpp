#include "cacheitem.h"

CacheItem::CacheItem(CacheItem *parent)
{
    isNew = true;
    isRoot = (NULL == parent) ? isRoot_true : isRoot_false;
    Parent = parent;
    isDeleted = isDeleted_false;
    if (false == isRoot)
    {
        parent->addChild(this);
    }
}

void CacheItem::addChild(CacheItem *child)
{
    children.append(child);
}

void CacheItem::deleteItem(void)
{
    isDeleted = isDeleted_true;
    for (int ind = 0; ind < getNumChildren(); ++ind)
    {
        CacheItem *pCasheChild = getChild(ind);
        pCasheChild->deleteItem();
    }
}

