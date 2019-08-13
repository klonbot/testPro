#include "databaseitem.h"

DataBaseItem::DataBaseItem(idDataBaseItem_t id, idDataBaseItem_t idP)
{
    init(id, idP, false);
}

DataBaseItem::DataBaseItem(idDataBaseItem_t id) // для создания корня
{
    idDataBaseItem_t idP = 0;
    init(id, idP, true);
}

DataBaseItem::DataBaseItem(DataBaseItem *item)
{
    *this = *item;
}

void DataBaseItem::init(idDataBaseItem_t id, idDataBaseItem_t idP, bool isR)
{
    isRoot = isR;
    idThis = id;
    setIdParent(idP);
    idChildren.clear();
    isDeleted = false;
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
