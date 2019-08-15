#ifndef DATABASE_H
#define DATABASE_H

#include "databaseitem.h"

class DataBase
{
public:
    DataBase();

    const bool isEditable;

    ID_t addItemFromCashe(DataBaseItem *dbItem, ID_t idParent);
    ID_t refreshItemFromCashe(DataBaseItem *dbItem);
    void clear (void);
    DataBaseItem* at (int i) {return dataBaseItems.at(i);}
    int size(void) {return dataBaseItems.size();}

    DataBaseItem* getChild(DataBaseItem *parent, int ind);
private:
    QVector<DataBaseItem*>dataBaseItems;
    ID_t idCounter;

    ID_t getNextID() {return idCounter++;}
    void deleteCildrenInDB(DataBaseItem *dbItem);
    void updateKeysRightItems(Key_t rk);
    void updateKeysAncestors(Key_t rk);
};

#endif // DATABASE_H
