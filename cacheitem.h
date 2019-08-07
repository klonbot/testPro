#ifndef CASHITEM_H
#define CASHITEM_H

#include "databaseitem.h"
#include "QVector"
#include "QString"

class CacheItem
{
public:
    CacheItem();
    CacheItem(CacheItem *parent);

    void addChild(CacheItem *child);
    int getNumChildren(void) {return children.size();}
    CacheItem* getChild(int i) {return children.at(i);}
private:
    bool isNew;                     // Признак нового элемента в кэше
    idDataBaseItem_t id;            // Уникальный ID элемента в БД (для перенесенных из БД)
    CacheItem *Parent;              // Указатель на родителя в кэше
    isRoot_t isRoot;                // Признак корня
    QVector<CacheItem*>children;    // Указатели на дочерние в кеше
    QString value;
};

#endif // CASHITEM_H
