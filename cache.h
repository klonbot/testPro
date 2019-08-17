#ifndef CACHE_H
#define CACHE_H

#include "cacheitem.h"
#include "updatekeys.h"

class Cache: private UpdateKeys<Cache>
{
public:
    Cache();

    const bool isEditable;

    CacheItem* newItem(CacheItem *parent = NULL, DataBaseItem *dataBaseItem = NULL);
    CacheItem* newItem(QString val, CacheItem *parent = NULL);
    CacheItem* newItem(DataBaseItem *dataBaseItem);

    bool isDelitedAncestors(DataBaseItem *dataBaseItem);

    void reset(void);
    CacheItem* getItem (int i) {return cacheItems.at(i);}
    int getSize(void) {return cacheItems.size();}
    void insertItem (int i, CacheItem* item) {return cacheItems.insert(i, item);}
    DataBaseItem* atData (int i) {return getItem(i)->getCacheData();}

    CacheItem* getChild(CacheItem *parent, int ind);
    CacheItem* searchInCache(ID_t ID);
    bool getIsDeletedRoot(void) {return isDeletedRoot;}
    void deleteItem(CacheItem*  item);
    void deleteAllDescendants(Key_t left, Key_t right);
    void resetIsDeletedRoot(void) {isDeletedRoot = false;}
    int getNumChildren(CacheItem *item) {return item->getNumChildren();}

    void updateKeys(ID_t idParent);
private:
    QVector<CacheItem*>cacheItems;
    bool isDeletedRoot;

    CacheItem* searchParent(DataBaseItem *dataBaseItem);
    CacheItem* searchLostChildren(CacheItem *item);
    void addLostChildren(CacheItem *item);
    bool insertByKey(CacheItem *item);
};

#endif // CACHE_H
