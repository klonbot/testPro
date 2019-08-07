#include "cacheitem.h"

CacheItem::CacheItem(CacheItem *parent)
{
    isNew = true;
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
