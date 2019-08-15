#include "databaseitem.h"

DataBaseItem::DataBaseItem(ID_t id, ID_t idP)
{
    init(id, idP, false);
}

DataBaseItem::DataBaseItem(ID_t id) // для создания корня
{
    ID_t idP = 0;
    init(id, idP, true);
}

DataBaseItem::DataBaseItem(DataBaseItem *item)
{
    *this = *item;
}

void DataBaseItem::init(ID_t id, ID_t idP, bool isR)
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

