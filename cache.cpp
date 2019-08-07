#include "cache.h"


Cache::Cache()
{    
    root = NULL;
}

CacheItem* Cache::newRoot(void)
{
    if (NULL == root)
    {
        CacheItem *item = new CacheItem();
        root = item;
    }
    else
        qDebug("Error addition new Root!");
    return root;
}

/*
CacheItem* Cache::newItem(CacheItem *parent)
{
    CacheItem *item = new CacheItem(parent);
    cacheItems.append(item);
    return item;
}
*/

void Cache::reset(void)
{
    if (NULL != root)
    {
        delete(root);
    }
}

