#include "database.h"

DataBase::DataBase() :
    UpdateKeys<DataBase>(*this),
    isEditable(false)
{
    resetIdCounter();
}

ID_t DataBase::addItemFromCashe(DataBaseItem *dbItem, ID_t idParent)
{
    DataBaseItem *newItem = new DataBaseItem(dbItem);
    ID_t id = getNextID();
    if (dataBaseItems.size() < id)
    {
        qDebug("addItemFromCashe: ERROR id for DataBase!");
        return id;
    }
    newItem->setID(id);
    if(false == newItem->getIsRoot())
    {
        newItem->setIdParent(idParent);
    }

    if(true == newItem->getIsRoot())
    {
        newItem->setLeftKey(1);
        newItem->setRightKey(2);
        newItem->setLevel(1);
    }
    else
    {
        DataBaseItem *item = dataBaseItems.at(idParent);
        Key_t rk = item->getRightKey();
        int level = item->getLevel();

        updateKeysRightItems(rk);
        updateKeysAncestors(rk);
        newItem->setLeftKey(rk);
        newItem->setRightKey(rk + 1);
        newItem->setLevel(level);
    }

    dataBaseItems.append(newItem);
    *dbItem = *newItem;
    return id;
}

ID_t DataBase::refreshItemFromCashe(DataBaseItem *dbItem)
{
    ID_t id = dbItem->getID();
    if (dataBaseItems.size() < id)
    {
        qDebug("refreshItemFromCashe: ERROR id for DataBase!");
        return id;
    }
    DataBaseItem *item = dataBaseItems.at(id);
    dbItem->setLeftKey(item->getLeftKey());
    dbItem->setRightKey(item->getRightKey());
    dbItem->setLevel(item->getLevel());
    *item = *dbItem;

    if (item->getIsDeleted())
    {
       deleteCildrenInDB(dbItem);
    }
    return id;
}

void DataBase::deleteCildrenInDB(DataBaseItem *parentItem)
{
    Key_t lkp = parentItem->getLeftKey();
    Key_t rkp = parentItem->getRightKey();
    for (int i = 0; i < dataBaseItems.size(); ++i)
    {
        DataBaseItem *item =  dataBaseItems.at(i);
        Key_t lki = item->getLeftKey();
        Key_t rki = item->getRightKey();

        if (true == item->getIsDeleted())
            continue;
        if ((lkp < lki)&&(rki<rkp))
        {
            item->setIsDeleted(true);
        }
    }
}

void DataBase::clear (void)
{
    dataBaseItems.clear();
    resetIdCounter();
}

// use only for TreeWidget!
DataBaseItem* DataBase::getChild(DataBaseItem *parent, int ind)
{
    int cntChild = 0;
    for (int i = 0; i < dataBaseItems.size(); ++i)
    {
        DataBaseItem* item = dataBaseItems.at(i);
        if (item->getIsRoot())
            continue;
        if (item->getIdParent() == parent->getID())
        {
            if(cntChild == ind)
                return item;
            ++cntChild;
        }
    }
    return NULL;
}

// use only for TreeWidget!
int DataBase::getNumChildren(DataBaseItem *parent)
{
    int numChildren = 0;
    for (int i = 0; i < dataBaseItems.size(); ++i)
    {
        if (dataBaseItems.at(i)->getIsRoot())
            continue;
        if (dataBaseItems.at(i)->getIdParent() == parent->getID())
        {
            ++numChildren;
        }
    }
    return numChildren;
}
