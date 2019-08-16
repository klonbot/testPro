#ifndef CACHE_H
#define CACHE_H

#include "cacheitem.h"

class Cache
{
public:
    Cache();

    const bool isEditable;

    CacheItem* newItem(CacheItem *parent = NULL, DataBaseItem *dataBaseItem = NULL);
    CacheItem* newItem(CacheItem *parent, QString val);
    CacheItem* newItem(QString val);   
    CacheItem* newItem(DataBaseItem *dataBaseItem);

    bool isDelitedAncestors(DataBaseItem *dataBaseItem);

    void reset(void);
    CacheItem* at (int i) {return cacheItems.at(i);}
    int size(void) {return cacheItems.size();}
    CacheItem* getChild(CacheItem *parent, int ind);

    CacheItem* searchInCache(ID_t baseID);
    bool getIsDeletedRoot(void) {return isDeletedRoot;}
    void deleteItem(CacheItem*  item);
    void deleteAllDescendants(Key_t left, Key_t right);
    void resetIsDeletedRoot(void) {isDeletedRoot = false;}
private:
    QVector<CacheItem*>cacheItems;
    bool isDeletedRoot;

    CacheItem* searchParent(DataBaseItem *dataBaseItem);
    CacheItem* searchLostChildren(DataBaseItem *dataBaseItem);
};

#endif // CACHE_H
