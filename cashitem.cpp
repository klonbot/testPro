#include "cacheitem.h"

CacheItem::CacheItem(idCacheItem_t id, CacheItem *parent)
{
    isNew = true;
    cashItemID = id;
    isRoot = (NULL == parent) ? isRoot_true : isRoot_false;
    Parent = parent;
    if (false == isRoot)
    {
        parent->addChild(this);
    }
}

void CacheItem::addChild(CacheItem *child)
{
    children.append(child);
}
