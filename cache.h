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
    CacheItem* at (int i) {return cacheItems.at(i);}
    int size(void) {return cacheItems.size();}

private:
    QVector<CacheItem*>cacheItems;
};

#endif // CACHE_H
