#ifndef DATABASE_H
#define DATABASE_H

#include "databaseitem.h"

class DataBase
{
public:
    DataBase();

    const bool isEditable;

    idDataBaseItem_t addItemFromCashe(DataBaseItem *dbItem, idDataBaseItem_t idParent);
    idDataBaseItem_t refreshItemFromCashe(DataBaseItem *dbItem);
    void clear (void);
    DataBaseItem* at (int i) {return dataBaseItems.at(i);}
    int size(void) {return dataBaseItems.size();}

    DataBaseItem* getChild(DataBaseItem *parent, int ind);
private:
    QVector<DataBaseItem*>dataBaseItems;
    idDataBaseItem_t idCounter;

    idDataBaseItem_t getNextID() {return idCounter++;}
    void deleteCildrenInDB(DataBaseItem *dbItem);
};

#endif // DATABASE_H
