#include "cache.h"


Cache::Cache()
{    
    cacheItemIDCnt = 0;
}

CacheItem* Cache::newItem(CacheItem *parent)
{
    idCacheItem_t id = getCacheItemID();
    CacheItem *item = (NULL == parent) ? new CacheItem(id) : new CacheItem(id, parent);
    cacheItems.append(item);

    return item;
}

CacheItem* Cache::newItem(CacheItem *parent, QString val)
{
    CacheItem *item = newItem(parent);
    item->setValue(val);
    return item;
}

CacheItem* Cache::newItem(QString val)
{
    CacheItem *item = newItem();
    item->setValue(val);
    return item;
}

void Cache::reset(void)
{
    for (int i = 0; i < cacheItems.size(); ++i)
    {
         CacheItem *item = cacheItems.at(i);

         delete(item);
    }
    cacheItems.clear();
    cacheItemIDCnt = 0;
}

