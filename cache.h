#ifndef CACHE_H
#define CACHE_H

#include "cacheitem.h"

class Cache
{
public:
    Cache();

    CacheItem* newRoot(void);
    CacheItem* newItem(CacheItem *parent);

    void reset(void);

private:
    QVector<CacheItem*>cacheItems;
};

#endif // CACHE_H
