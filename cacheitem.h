#ifndef CASHITEM_H
#define CASHITEM_H

#include "databaseitem.h"
#include "QVector"

class CacheItem : public DataBaseItem
{
public:
    CacheItem();
    CacheItem(CacheItem *parent);
    //CashItem(DataBaseItem dbItem);

    void addChild(CacheItem *child);
private:
    bool isNew;                 // Признак нового элемента в кэше

    CacheItem *Parent;
    QVector<CacheItem*>children;
};

#endif // CASHITEM_H
