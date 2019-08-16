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
        for(int i = 0; i < getSize(); ++i)
        {
            Key_t lki = getItem(i)->getCacheData()->getLeftKey();
            if(lk < lki)
            {
                insertItem(i, item);
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
        child = searchLostChildren(item);
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

    for (int i = 0; i < getSize(); ++i)
    {
        CacheItem *item = getItem(i);
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
    for (int i = 0; i < getSize(); ++i)
    {
         CacheItem *item = getItem(i);

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
    for (int i = 0; i < getSize(); ++i)
    {
         CacheItem *item = getItem(i);
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
    ID_t parentId = dataBaseItem->getIdParent();
    for (int i = 0; i < getSize(); ++i)
    {
        CacheItem *item = getItem(i);
        if(item->isNewItem())
            continue;
        DataBaseItem *baseItem = item->getCacheData();
        ID_t id = baseItem->getID();

        if (parentId == id)
        {
            return item;
        }
    }
    return NULL;
}

CacheItem* Cache::searchLostChildren(CacheItem *parentItem)
{
    DataBaseItem *parentBaseItem = parentItem->getCacheData();
    ID_t parentId = parentBaseItem->getID();
    for (int i = 0; i < getSize(); ++i)
    {
        CacheItem *item = getItem(i);
        if(item->isNewItem())
            continue;
        DataBaseItem *baseItem = item->getCacheData();
        ID_t id = baseItem->getIdParent();
        if (item->getIsRoot())
            continue;
        if (parentId == id)
        {
            if (parentItem->isChild(baseItem->getID()))
                continue;
            return item;
        }
    }
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
    for (int i = 0; i < getSize(); ++i)
    {
        CacheItem *item = getItem(i);
        Key_t lk = item->getCacheData()->getLeftKey();
        Key_t rk = item->getCacheData()->getRightKey();
        if((left < lk)&&(rk < right))
        {
            item->deleteItem();
        }
    }
}

void Cache::updateKeys(ID_t idParent)
{
    CacheItem *pCacheItem = searchInCache(idParent);
    updateKeysRightItems(pCacheItem->getCacheData()->getRightKey());
    updateKeysAncestors(pCacheItem->getCacheData()->getRightKey());
}

