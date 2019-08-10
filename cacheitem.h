#ifndef CASHITEM_H
#define CASHITEM_H

#include "databaseitem.h"
#include "QVector"
#include "QString"

class CacheItem
{
public:
    CacheItem(CacheItem *parent = NULL);

    void addChild(CacheItem *child) {children.append(child);}
    int getNumChildren(void) {return children.size();}
    CacheItem* getChild(int i) {return children.at(i);}

    void setValue (QString val) {cacheData.setValue(val);}
    QString getValue(void) {return cacheData.getValue();}
    isRoot_t getIsRoot(void) {return cacheData.getIsRoot();}
    isDeleted_t getIsDeleted (void) {return cacheData.getIsDeleted();}
    void setParent(CacheItem *parent) {Parent = parent;}

    void deleteItem(void);
    bool isNewItem(void) {return isNew;}
    void setIsOldItem(void) {isNew = false;}
    bool isTop (void) {return (NULL == Parent);}

    DataBaseItem* getDataBaseItem(void) {return &cacheData;}
private:
    DataBaseItem cacheData;
    bool isNew;                         // Признак нового элемента в кэше
    CacheItem *Parent;                  // Указатель на родителя в кэше
    QVector<CacheItem*>children;        // Указатели на дочерние в кеше
};

#endif // CASHITEM_H
