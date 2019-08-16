#ifndef CACHE_H
#define CACHE_H

#include "cacheitem.h"
#include "updatekeys.h"

class Cache: public UpdateKeys<Cache>
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
    CacheItem* getItem (int i) {return cacheItems_.at(i);}
    int getSize(void) {return cacheItems_.size();}
    void insertItem (int i, CacheItem* item) {return cacheItems_.insert(i, item);}
    DataBaseItem* atData (int i) {return getItem(i)->getCacheData();}

    CacheItem* getChild(CacheItem *parent, int ind);
    CacheItem* searchInCache(ID_t baseID);
    bool getIsDeletedRoot(void) {return isDeletedRoot;}
    void deleteItem(CacheItem*  item);
    void deleteAllDescendants(Key_t left, Key_t right);
    void resetIsDeletedRoot(void) {isDeletedRoot = false;}
private:
    QVector<CacheItem*>cacheItems_;
    bool isDeletedRoot;

    CacheItem* searchParent(DataBaseItem *dataBaseItem);
    CacheItem* searchLostChildren(CacheItem *item);
};

#endif // CACHE_H
