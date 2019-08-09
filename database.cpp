#include "database.h"

DataBase::DataBase()
{
    idCounter = 0;
}

void DataBase::addItemFromCashe(DataBaseItem *dbItem)
{
    idDataBaseItem_t id = getNextID();
    dbItem->setID(id);
    dataBaseItems.append(dbItem);
}

void DataBase::refreshItemFromCashe(DataBaseItem *dbItem)
{
    idDataBaseItem_t id = dbItem->getId();
    if (dataBaseItems.size() > id)
    {
        qDebug("ERROR id for DataBase!");
        return;
    }
    DataBaseItem *item = dataBaseItems.at(id);
    *item = *dbItem;

    if (item->getIsDeleted())
    {
        // пометить на удаление все дочерние
    }
}

