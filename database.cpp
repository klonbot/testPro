#include "database.h"

DataBase::DataBase() :
    UpdateKeys<DataBase>(*this),
    isEditable(false)
{
    idCounter = 0;
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
    }
    else
    {
        DataBaseItem *item = dataBaseItems.at(idParent);
        Key_t rk = item->getRightKey();

        updateKeysRightItems(rk);
        updateKeysAncestors(rk);
        newItem->setLeftKey(rk);
        newItem->setRightKey(rk + 1);
    }

    dataBaseItems.append(newItem);
    *dbItem = *newItem;
    if(false == newItem->getIsRoot())
    {
        DataBaseItem *item = dataBaseItems.at(idParent);
        item->setIdChildren(id);
    }
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
    *item = *dbItem;

    if (item->getIsDeleted())
    {
       deleteCildrenInDB(dbItem);
    }
    return id;
}

void DataBase::deleteCildrenInDB(DataBaseItem *dbItem)
{
    int numChildren = dbItem->getNumChildren();
    for (int i = 0; i < numChildren; ++i)
    {
        DataBaseItem *child = getChild(dbItem, i);
        if (true == child->getIsDeleted())
            continue;
        child->setIsDeleted(true);
        deleteCildrenInDB(child);
    }
}

void DataBase::clear (void)
{
    dataBaseItems.clear();
    idCounter = 0;
}

DataBaseItem* DataBase::getChild(DataBaseItem *parent, int ind)
{
    int numChildren = parent->getNumChildren();
    if (ind >= numChildren)
    {
        qDebug("ERROR getChild: child ID in database!");
        return NULL;
    }
    ID_t childId = parent->getCildID(ind);
    DataBaseItem *item = dataBaseItems.at(childId);
    return item;
}
