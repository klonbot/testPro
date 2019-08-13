#include "cache.h"


Cache::Cache() :
    isEditable(true)
{    
    isDeletedRoot = false;
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

bool Cache::isDelitedAncestors(DataBaseItem *dataBaseItem)
{
    int numAncestors = dataBaseItem->getNumAncestors();
    for (int i = 0; i < cacheItems.size(); ++i)
    {
        CacheItem *item = cacheItems.at(i);
        idDataBaseItem_t id = item->getDataBaseItem()->getID();
        for (int i = 0; i < numAncestors; ++i)
        {
            idDataBaseItem_t idAncestor = dataBaseItem->getAncestor(i);
            if(idAncestor == id)
            {
                if (item->getIsDeleted())
                {
                    return true;
                }
            }
        }
    }
    return false;
}

CacheItem* Cache::newItem(DataBaseItem *dataBaseItem)
{
    CacheItem *item = newItem();
    DataBaseItem *cacheBaseItem = item->getDataBaseItem();
    *cacheBaseItem = *dataBaseItem;
    item->setIsOldItem();

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

CacheItem* Cache::searchInCache(DataBaseItem* baseItem)
{
    for (int i = 0; i < cacheItems.size(); ++i)
    {
         CacheItem *item = cacheItems.at(i);
         if (item->isNewItem())
             continue;
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
            if(false == item->isTop())
                continue;
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

void Cache::deleteItem(CacheItem* delItem)
{
    // найти возможных дальних потомков из не связанных веток кэша
    // и тоже отметить как удаленые
    idDataBaseItem_t id = delItem->getDataBaseItem()->getID();
    deleteAllDescendants(id);

    delItem->deleteItem();

    if (true == delItem->getIsRoot())
    {
       isDeletedRoot = true;
    }
}

void Cache::deleteAllDescendants(idDataBaseItem_t id)
{
    for (int i = 0; i < cacheItems.size(); ++i)
    {
        CacheItem *item = cacheItems.at(i);
        idDataBaseItem_t idCurrent = item->getDataBaseItem()->getID();
        if (id == idCurrent)
            continue;
        // пройтись по всем предкам и удалить элемент
        int numAncestors = item->getDataBaseItem()->getNumAncestors();
        for (int i = 0; i < numAncestors; ++i)
        {
            idDataBaseItem_t idAncestor = item->getDataBaseItem()->getAncestor(i);
            if(idAncestor == id)
            {
                item->deleteItem();
            }
        }
    }
}





