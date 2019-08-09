#ifndef DATABASE_H
#define DATABASE_H

#include "databaseitem.h"

class DataBase
{
public:
    DataBase();

    idDataBaseItem_t addItemFromCashe(DataBaseItem *dbItem, idDataBaseItem_t idParent);
    idDataBaseItem_t refreshItemFromCashe(DataBaseItem *dbItem);
private:
    QVector<DataBaseItem*>dataBaseItems;
    idDataBaseItem_t idCounter;

    idDataBaseItem_t getNextID() {return idCounter++;}
};

#endif // DATABASE_H
