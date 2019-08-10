#include "database.h"

DataBase::DataBase()
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
    if(isRoot_false == newItem->getIsRoot())
    {
        dbItem->setIdParent(idParent);
    }

    dataBaseItems.append(newItem);
    if(isRoot_false == newItem->getIsRoot())
    {   // прописаться к родителю
        DataBaseItem *item = dataBaseItems.at(idParent);
        item->setIdChildren(id);
    }
    return id;
}

idDataBaseItem_t DataBase::refreshItemFromCashe(DataBaseItem *dbItem)
{
    idDataBaseItem_t id = dbItem->getId();
    if (dataBaseItems.size() < id)
    {
        qDebug("refreshItemFromCashe: ERROR id for DataBase!");
        return id;
    }
    DataBaseItem *item = dataBaseItems.at(id);
    *item = *dbItem;

    if (item->getIsDeleted())
    {
        // пометить на удаление все дочерние
    }
    return id;
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
