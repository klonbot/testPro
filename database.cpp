#include "database.h"

DataBase::DataBase()
{
    idCounter = 0;
}

idDataBaseItem_t DataBase::addItemFromCashe(DataBaseItem *dbItem, idDataBaseItem_t idParent)
{
    idDataBaseItem_t id = getNextID();
    if (dataBaseItems.size() > id)
    {
        qDebug("addItemFromCashe: ERROR id for DataBase!");
        return id;
    }
    dbItem->setID(id);
    if(isRoot_false == dbItem->getIsRoot())
    {
        dbItem->setIdParent(idParent);
    }
    dataBaseItems.append(dbItem);
    if(isRoot_false == dbItem->getIsRoot())
    {
        DataBaseItem *item = dataBaseItems.at(idParent);
        item->setIdChildren(id);
    }
    return id;
}

idDataBaseItem_t DataBase::refreshItemFromCashe(DataBaseItem *dbItem)
{
    idDataBaseItem_t id = dbItem->getId();
    if (dataBaseItems.size() > id)
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

