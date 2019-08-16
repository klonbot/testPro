#ifndef DATABASE_H
#define DATABASE_H

#include "databaseitem.h"
#include "updatekeys.h"

class DataBase: private UpdateKeys<DataBase>
{
public:
    DataBase();

    const bool isEditable;

    ID_t addItemFromCashe(DataBaseItem *dbItem, ID_t idParent);
    ID_t refreshItemFromCashe(DataBaseItem *dbItem);
    void clear (void);
    DataBaseItem* getItem (int i) {return dataBaseItems.at(i);}
    DataBaseItem* atData (int i) {return getItem(i);}
    int getSize(void) {return dataBaseItems.size();}
    void resetIdCounter (void) {idCounter = 0;}
    int getNumChildren(DataBaseItem *item);

    DataBaseItem* getChild(DataBaseItem *parent, int ind);
private:
    QVector<DataBaseItem*>dataBaseItems;
    ID_t idCounter;

    ID_t getNextID() {return idCounter++;}
    void deleteCildrenInDB(DataBaseItem *dbItem);
};

#endif // DATABASE_H
