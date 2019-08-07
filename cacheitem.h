#ifndef CASHITEM_H
#define CASHITEM_H

#include "databaseitem.h"
#include "QVector"
#include "QString"
#include "stdint.h"

typedef uint64_t idCacheItem_t;

class CacheItem
{
public:
    CacheItem(idCacheItem_t id, CacheItem *parent = NULL);

    void addChild(CacheItem *child);
    int getNumChildren(void) {return children.size();}
    CacheItem* getChild(int i) {return children.at(i);}
    void setValue (QString val) {value = val;}
    QString getValue(void) {return value;}
    isRoot_t getIsRoot(void) {return isRoot;}
    uint64_t getCashItemID(void) {return (uint64_t)cashItemID;}
private:
    idCacheItem_t cashItemID;           // Уникальный идентификатор элементов в кэше
    bool isNew;                         // Признак нового элемента в кэше
    idDataBaseItem_t bdID;              // Уникальный ID элемента в БД (для перенесенных из БД)
    CacheItem *Parent;                  // Указатель на родителя в кэше
    isRoot_t isRoot;                    // Признак корня
    QVector<CacheItem*>children;        // Указатели на дочерние в кеше
    QVector<idDataBaseItem_t>childrenID;// Идентификаторы дочерних элементов из БД
    QString value;                      // Значение Поля
};

#endif // CASHITEM_H
