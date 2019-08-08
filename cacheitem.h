#ifndef CASHITEM_H
#define CASHITEM_H

#include "databaseitem.h"
#include "QVector"
#include "QString"

class CacheItem
{
public:
    CacheItem(CacheItem *parent = NULL);

    void addChild(CacheItem *child);
    int getNumChildren(void) {return children.size();}
    CacheItem* getChild(int i) {return children.at(i);}
    void setValue (QString val) {value = val;}
    QString getValue(void) {return value;}
    isRoot_t getIsRoot(void) {return isRoot;}
    isDeleted_t getIsDeleted (void) {return isDeleted;}
    void deleteItem(void);
private:
    bool isNew;                         // Признак нового элемента в кэше
    idDataBaseItem_t id;                // Уникальный ID элемента в БД (для перенесенных из БД)
    CacheItem *Parent;                  // Указатель на родителя в кэше
    isRoot_t isRoot;                    // Признак корня
    QVector<CacheItem*>children;        // Указатели на дочерние в кеше
    QVector<idDataBaseItem_t>childrenID;// Идентификаторы дочерних элементов из БД
    QString value;                      // Значение Поля
    isDeleted_t isDeleted;               // Признак удаленого Поля
};

#endif // CASHITEM_H
