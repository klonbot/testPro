#include "cache.h"


Cache::Cache() :
    UpdateKeys<Cache>(*this),
    isEditable(true)
{    
    isDeletedRoot = false;
}

CacheItem* Cache::newItem(CacheItem *parent, DataBaseItem *dataBaseItem)
{
    CacheItem* item = new CacheItem(parent, dataBaseItem);
    if(NULL != dataBaseItem)
    {
        DataBaseItem *cacheData = item->getCacheData();
        Key_t lk = cacheData->getLeftKey();
        for(int i = 0; i < size(); ++i)
        {
            Key_t lki = cacheItems.at(i)->getCacheData()->getLeftKey();
            if(lk < lki)
            {
                cacheItems.insert(i, item);
                return item;
            }
        }
    }
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
    CacheItem *parent = searchParent(dataBaseItem);
    CacheItem *item = newItem(parent, dataBaseItem);

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

bool Cache::isDelitedAncestors(DataBaseItem *casheData)
{
    Key_t left = casheData->getLeftKey();
    Key_t right = casheData->getRightKey();

    for (int i = 0; i < cacheItems.size(); ++i)
    {
        CacheItem *item = cacheItems.at(i);
        if (item->getCacheData()->getIsDeleted())
        {
            Key_t lk = item->getCacheData()->getLeftKey();
            Key_t rk = item->getCacheData()->getRightKey();
            if((lk < left)&&(right < rk))
            {
                return true;
            }
        }
    }
    return false;
}

void Cache::reset(void)
{
    for (int i = 0; i < cacheItems.size(); ++i)
    {
         CacheItem *item = cacheItems.at(i);

         delete(item);
    }
    cacheItems.clear();
    isDeletedRoot = false;
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

CacheItem* Cache::searchInCache(ID_t baseID)
{
    for (int i = 0; i < cacheItems.size(); ++i)
    {
         CacheItem *item = cacheItems.at(i);
         if (item->isNewItem())
             continue;
         DataBaseItem* cacheDbItem = item->getCacheData();
         ID_t casheID = cacheDbItem->getID();
         if (casheID == baseID)
         {
             return item;
         }
    }
    return NULL;
}

CacheItem* Cache::searchParent(DataBaseItem *dataBaseItem)
{
    ID_t clildId = dataBaseItem->getID();
    for (int i = 0; i < cacheItems.size(); ++i)
    {
        CacheItem *item = cacheItems.at(i);
        if(item->isNewItem())
            continue;
        DataBaseItem *baseItem = item->getCacheData();
        ID_t id = baseItem->getID();

        if (clildId == id)
        {
            return item;
        }
#if 0

        int numChildren = baseItem->getNumChildren();
        for (int j = 0; j < numChildren; ++j)
        {
            ID_t childID = baseItem->getCildID(j);
            if (childID == dataBaseItem->getID())
            {
                return item;
            }
        }
#endif
    }
    return NULL;
}

CacheItem* Cache::searchLostChildren(DataBaseItem *dataBaseItem)
{
    ID_t parentId = dataBaseItem->getID();
    for (int i = 0; i < cacheItems.size(); ++i)
    {
        CacheItem *item = cacheItems.at(i);
        if(item->isNewItem())
            continue;
        DataBaseItem *baseItem = item->getCacheData();
        ID_t id = baseItem->getIdParent();

        if (parentId == id)
        {
            return item;
        }
    }
#if 0
    int numChildren = dataBaseItem->getNumChildren();
    for (int i = 0; i < numChildren; ++i)
    {
        ID_t childID = dataBaseItem->getCildID(i);
        for (int j = 0; j < cacheItems.size(); ++j)
        {
            CacheItem *item = cacheItems.at(j);
            if(false == item->isTop())
                continue;
            if(item->isNewItem())
                continue;
            ID_t ID = item->getCacheData()->getID();
            if (childID == ID)
            {
                return item;
            }
        }
    }
#endif
    return NULL;
}

void Cache::deleteItem(CacheItem* item)
{
    Key_t lk = item->getCacheData()->getLeftKey();
    Key_t rk = item->getCacheData()->getRightKey();
    deleteAllDescendants(lk, rk);
    item->deleteItem();

    if (true == item->getIsRoot())
    {
       isDeletedRoot = true;
    }
}

void Cache::deleteAllDescendants(Key_t left, Key_t right)
{
    for (int i = 0; i < cacheItems.size(); ++i)
    {
        CacheItem *item = cacheItems.at(i);
        Key_t lk = item->getCacheData()->getLeftKey();
        Key_t rk = item->getCacheData()->getRightKey();
        if((left < lk)&&(rk < right))
        {
            item->deleteItem();
        }
    }
}

