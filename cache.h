#ifndef CACHE_H
#define CACHE_H

#include "cacheitem.h"
#include "stdint.h"

class Cache
{
public:
    Cache();

    CacheItem* newItem(CacheItem *parent = NULL);
    CacheItem* newItem(CacheItem *parent, QString val);
    CacheItem* newItem(QString val);

    void reset(void);
    CacheItem* at (int32_t i) {return cacheItems.at(i);}
    int size(void) {return cacheItems.size();}

private:
    QVector<CacheItem*>cacheItems;    
    idCacheItem_t cacheItemIDCnt;

    idCacheItem_t getCacheItemID(void) {return cacheItemIDCnt++;}
};

#endif // CACHE_H
