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

void DataBaseItem::init(idDataBaseItem_t id, idDataBaseItem_t idP, isRoot_t isR)
{
    isRoot = isR;
    idThis = id;
    idParent = idP;
    idChildren.clear();
    isDeleted = isDeleted_false;
    value.clear();
}
