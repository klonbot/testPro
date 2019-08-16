#ifndef CASHITEM_H
#define CASHITEM_H

#include "databaseitem.h"
#include "QVector"
#include "QString"

class CacheItem
{
public:
    CacheItem(CacheItem *parent = NULL);

    void addChild(CacheItem *child);// {children.append(child);}
    int getNumChildren(void) const {return children.size();}
    CacheItem* getChild(int i) const {return children.at(i);}

    void setValue (QString val) {cacheData.setValue(val);}
    QString getValue(void) {return cacheData.getValue();}
    bool getIsRoot(void) {return cacheData.getIsRoot();}
    bool getIsDeleted(void) {return cacheData.getIsDeleted();}
    void setParent(CacheItem *parent) {Parent = parent;}
    CacheItem *getParent(void) const {return Parent;}

    void deleteItem(void);
    bool isNewItem(void) const {return isNew;}
    void setIsOldItem(void) {isNew = false;}
    bool isTop(void) const {return (NULL == Parent);}

    DataBaseItem* getCacheData(void) {return &cacheData;}
private:
    DataBaseItem cacheData;
    bool isNew;
    CacheItem *Parent;
    QVector<CacheItem*>children;
};

#endif // CASHITEM_H
