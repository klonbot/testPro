#include "databaseitem.h"

DataBaseItem::DataBaseItem(idDataBaseItem_t id, idDataBaseItem_t idP)
{
    init(id, idP, isRoot_false);
}

DataBaseItem::DataBaseItem(idDataBaseItem_t id) // для создания корня
{
    idDataBaseItem_t idP = 0;
    init(id, idP, isRoot_true);
}

DataBaseItem::DataBaseItem(DataBaseItem *item)
{
    *this = *item;
}

void DataBaseItem::init(idDataBaseItem_t id, idDataBaseItem_t idP, isRoot_t isR)
{
    isRoot = isR;
    idThis = id;
    setIdParent(idP);
    idChildren.clear();
    isDeleted = isDeleted_false;
    value.clear();
}

void DataBaseItem::setValue(QString val)
{
    value = val;
}

QString DataBaseItem::getValue(void)
{
    return value;
}

DataBaseItem* DataBaseItem::getChild(int i)
{
    idDataBaseItem_t id = idChildren.at(i);
    return NULL;
}

void DataBaseItem::addAncestors(QVector<idDataBaseItem_t>* ancestors, idDataBaseItem_t id)
{
    for(int i = 0; i < ancestors->size(); ++i)
    {
        idAncestors.append(ancestors->at(i));
    }
    idAncestors.append(id);
}
