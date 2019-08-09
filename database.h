#ifndef DATABASE_H
#define DATABASE_H

#include "databaseitem.h"

class DataBase
{
public:
    DataBase();

    void addItemFromCashe(DataBaseItem *dbItem);
    void refreshItemFromCashe(DataBaseItem *dbItem);
private:
    QVector<DataBaseItem*>dataBaseItems;
    idDataBaseItem_t idCounter;

    idDataBaseItem_t getNextID() {return idCounter++;}
};

#endif // DATABASE_H
