#ifndef DATABASEITEM_H
#define DATABASEITEM_H

#include "QString"

class DataBaseItem
{
public:
    DataBaseItem();

private:
     bool isRoot;
     bool isDelited;

     QVector<DataBaseItem> children;    // список дочерних элементов
     DataBaseItem *Parent;              // Ссылка на родителя
     QString value;
};

#endif // DATABASEITEM_H
