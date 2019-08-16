#include "cacheitem.h"

CacheItem::CacheItem(CacheItem *parent):
    cacheData(0)
{
    isNew = true;    
    bool isRoot = (NULL == parent);
    cacheData.setIsRoot(isRoot);
    Parent = parent;
    cacheData.setIsDeleted(false);
    if (false == isRoot)
    {
        parent->addChild(this);
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

