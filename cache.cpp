#include "cache.h"


Cache::Cache()
{    

}

CacheItem* Cache::newItem(CacheItem *parent)
{
    CacheItem *item = (NULL == parent) ? new CacheItem() : new CacheItem(parent);
    cacheItems.append(item);
    return item;
}

CacheItem* Cache::newItem(CacheItem *parent, QString val)
{
    CacheItem *item = newItem(parent);
    item->setValue(val);
    return item;
}

CacheItem* Cache::newItem(QString val)
{
    CacheItem *item = newItem();
    item->setValue(val);
    return item;
}

CacheItem* Cache::newItem(DataBaseItem *dataBaseItem)
{
    CacheItem *item = newItem();
    DataBaseItem *cacheBaseItem = item->getDataBaseItem();
    *cacheBaseItem = *dataBaseItem;
    item->setIsOldItem();

    // найти родственников элемента в кэше и
    // прописаться к родственникам в кэше
    CacheItem *parent = searchParent(dataBaseItem);
    if(NULL != parent)
    {
        parent->addChild(item);
        item->setParent(parent);
    }

    CacheItem* child = NULL;
    do
    {
        child = searchLostChildren(dataBaseItem);
        if (NULL != child)
        {
            child->setParent(item);
            item->addChild(child);
        }
    }
    while (NULL != child);

    return item;
}

void Cache::reset(void)
{
    for (int i = 0; i < cacheItems.size(); ++i)
    {
         CacheItem *item = cacheItems.at(i);

         delete(item);
    }
    cacheItems.clear();
}

CacheItem* Cache::getChild(CacheItem *parent, int ind)
{
    int numChildren = parent->getNumChildren();
    if (ind >= numChildren)
    {
        qDebug("ERROR getChild: child ID in cache!");
        return NULL;
    }
    CacheItem *item = parent->getChild(ind);
    return item;
}

CacheItem* Cache::searchInCache(DataBaseItem* baseItem)
{
    for (int i = 0; i < cacheItems.size(); ++i)
    {
         CacheItem *item = cacheItems.at(i);
         DataBaseItem* cacheDbItem = item->getDataBaseItem();
         idDataBaseItem_t casheID = cacheDbItem->getID();
         idDataBaseItem_t baseID = baseItem->getID();
         if (casheID == baseID)
         {
             return item;
         }
    }
    return NULL;
}

CacheItem* Cache::searchParent(DataBaseItem *dataBaseItem)
{
    for (int i = 0; i < cacheItems.size(); ++i)
    {
        CacheItem *item = cacheItems.at(i);
        if(item->isNewItem())
            continue;
        DataBaseItem *baseItem = item->getDataBaseItem();
        int numChildren = baseItem->getNumChildren();
        // дети которые числятся по бД
        for (int j = 0; j < numChildren; ++j)
        {
            idDataBaseItem_t childID = baseItem->getCildID(j);
            if (childID == dataBaseItem->getID())
            {
                return item;
            }
        }
    }
    return NULL;
}

CacheItem* Cache::searchLostChildren(DataBaseItem *dataBaseItem)
{
    int numChildren = dataBaseItem->getNumChildren();
    for (int i = 0; i < numChildren; ++i)
    {
        idDataBaseItem_t childID = dataBaseItem->getCildID(i);
        for (int j = 0; j < cacheItems.size(); ++j)
        {
            CacheItem *item = cacheItems.at(j);
            if(item->isNewItem())
                continue;
            idDataBaseItem_t ID = item->getDataBaseItem()->getID();
            if (childID == ID)
            {
                return item;
            }
        }
    }
    return NULL;
}







