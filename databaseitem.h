#ifndef DATABASEITEM_H
#define DATABASEITEM_H

#include "QString"
#include "QVector"
#include "stdint.h"


typedef enum {isRoot_false, isRoot_true} isRoot_t;
typedef enum {isDeleted_false, isDeleted_true} isDeleted_t;
typedef uint64_t idDataBaseItem_t;

class DataBaseItem
{
public:
    DataBaseItem(idDataBaseItem_t id, idDataBaseItem_t idP);
    DataBaseItem(idDataBaseItem_t id);

    void SetValue(QString val);
    QString getValue(void);
    isRoot_t GetIsRoot(void) { return isRoot; }
private:
    idDataBaseItem_t idThis;

    QString value;

    isRoot_t isRoot;
    isDeleted_t isDeleted;

    QVector<idDataBaseItem_t> idChildren;     // список индексов дочерних элементов
    idDataBaseItem_t idParent;                // Индекс родителя

    void init(idDataBaseItem_t id, idDataBaseItem_t idP, isRoot_t isR);
};

#endif // DATABASEITEM_H
