#include "cacheitem.h"

CacheItem::CacheItem(CacheItem *parent, DataBaseItem *cData):
    cacheData(0)
{
    isNew = (NULL == cData);
    if (isNew)
    {
        cacheData.setIsRoot((NULL == parent));
        cacheData.setIsDeleted(false);
    }
    else
    {
        cacheData = *cData;
    }
    Parent = parent;
    if (NULL != parent)
    {
        Parent->addChild(this);
    }
}

void CacheItem::deleteItem(void)
{
    cacheData.setIsDeleted(true);
    for (int ind = 0; ind < getNumChildren(); ++ind)
    {
        CacheItem *pCasheChild = getChild(ind);
        pCasheChild->deleteItem();
    }
}

void CacheItem::addChild(CacheItem *child)
{
    if(child->isNewItem())
    {
        children.append(child);
    }
    else
    {
        Key_t rk = child->getCacheData()->getRightKey();
        int numCildren = getNumChildren();
        for(int i = 0; i < numCildren; ++i)
        {
            Key_t lki = children.at(i)->getCacheData()->getLeftKey();
            if(lki > rk)
            {
                children.insert(i, child);
                return;
            }
        }
        children.append(child);
    }
}

bool CacheItem::isChild(ID_t id)
{
    for (int i = 0; i < getNumChildren(); ++i)
    {
        ID_t childId = getChild(i)->getID();
        if (childId == id)
            return true;
    }
    return false;
}

