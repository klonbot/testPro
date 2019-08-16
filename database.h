#ifndef DATABASE_H
#define DATABASE_H

#include "databaseitem.h"
#include "updatekeys.h"

class DataBase: public UpdateKeys<DataBase>
{
public:
    DataBase();

    const bool isEditable;

    ID_t addItemFromCashe(DataBaseItem *dbItem, ID_t idParent);
    ID_t refreshItemFromCashe(DataBaseItem *dbItem);
    void clear (void);
    DataBaseItem* at (int i) {return dataBaseItems.at(i);}
    DataBaseItem* atData (int i) {return at(i);}
    int size(void) {return dataBaseItems.size();}

    DataBaseItem* getChild(DataBaseItem *parent, int ind);
private:
    QVector<DataBaseItem*>dataBaseItems;
    ID_t idCounter;

    ID_t getNextID() {return idCounter++;}
    void deleteCildrenInDB(DataBaseItem *dbItem);
};

#endif // DATABASE_H
