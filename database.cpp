#include "database.h"

DataBase::DataBase() :
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

        // обновить ключи дерева за родительским узлом
        updateKeysRightItems(rk);

        // обновить правые ключи родительской ветки
        updateKeysAncestors(rk);

        // устанавливаем свои
        newItem->setLeftKey(rk);
        newItem->setRightKey(rk + 1);
    }

    dataBaseItems.append(newItem);
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

void DataBase::updateKeysRightItems(Key_t rk)
{
    for(int i = 0; i < dataBaseItems.size(); ++i)
    {
        DataBaseItem *item = dataBaseItems.at(i);
        if(item->getLeftKey() > rk)
        {
            item->setLeftKey(item->getLeftKey() + 2);
            item->setRightKey(item->getRightKey() + 2);
        }
    }
}

void DataBase::updateKeysAncestors(Key_t rk)
{
    for(int i = 0; i < dataBaseItems.size(); ++i)
    {
        DataBaseItem *item = dataBaseItems.at(i);
        if((item->getRightKey()>=rk)&&(item->getLeftKey()<rk))
        {
            item->setRightKey(item->getRightKey() + 2);
        }
    }
}
