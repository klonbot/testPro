#include "cacheitem.h"

CacheItem::CacheItem() :
    DataBaseItem((idDataBaseItem_t)0)
{
    isNew = true;
}

CacheItem::CacheItem(CacheItem *parent) :
    DataBaseItem((idDataBaseItem_t)0, (idDataBaseItem_t)0)
{
    isNew = true;
    Parent = parent;
    parent->addChild(this);
}

/*CashItem::CashItem(DataBaseItem dbItem):
    DataBaseItem(dbItem)
{

}*/

void CacheItem::addChild(CacheItem *child)
{
    children.append(child);
}
