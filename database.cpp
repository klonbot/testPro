#include "database.h"

DataBase::DataBase() :
    isEditable(false)
{
    idCounter = 0;
}

idDataBaseItem_t DataBase::addItemFromCashe(DataBaseItem *dbItem, idDataBaseItem_t idParent)
{
    DataBaseItem *newItem = new DataBaseItem(dbItem);
    idDataBaseItem_t id = getNextID();
    if (dataBaseItems.size() < id)
    {
        qDebug("addItemFromCashe: ERROR id for DataBase!");
        return id;
    }
    newItem->setID(id);
    if(false == newItem->getIsRoot())
    {
        newItem->setIdParent(idParent);
        //родителя взять предков и добавить ребенку
        DataBaseItem *parent = dataBaseItems.at(idParent);
        newItem->addAncestors(parent);
    }

    dataBaseItems.append(newItem);
    if(false == newItem->getIsRoot())
    {
        DataBaseItem *item = dataBaseItems.at(idParent);
        item->setIdChildren(id);
    }
    return id;
}

idDataBaseItem_t DataBase::refreshItemFromCashe(DataBaseItem *dbItem)
{
    idDataBaseItem_t id = dbItem->getID();
    if (dataBaseItems.size() < id)
    {
        qDebug("refreshItemFromCashe: ERROR id for DataBase!");
        return id;
    }
    DataBaseItem *item = dataBaseItems.at(id);
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
    idDataBaseItem_t childId = parent->getCildID(ind);
    DataBaseItem *item = dataBaseItems.at(childId);
    return item;
}
