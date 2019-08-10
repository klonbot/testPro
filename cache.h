#ifndef CACHE_H
#define CACHE_H

#include "cacheitem.h"

class Cache
{
public:
    Cache();

    CacheItem* newItem(CacheItem *parent = NULL);
    CacheItem* newItem(CacheItem *parent, QString val);
    CacheItem* newItem(QString val);   

    void reset(void);
    CacheItem* at (int i) {return cacheItems.at(i);}
    int size(void) {return cacheItems.size();}
    CacheItem* getChild(CacheItem *parent, int ind);
private:
    QVector<CacheItem*>cacheItems;
};

#endif // CACHE_H
