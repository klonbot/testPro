#ifndef DATABASEITEM_H
#define DATABASEITEM_H

#include "QString"
#include "QVector"

typedef enum {isRoot_false, isRoot_true} isRoot_t;
typedef enum {isDeleted_false, isDeleted_true} isDeleted_t;
typedef int idDataBaseItem_t;

class DataBaseItem
{
public:
    DataBaseItem(idDataBaseItem_t id, idDataBaseItem_t idP);
    DataBaseItem(idDataBaseItem_t id);
    DataBaseItem(DataBaseItem *item);

    void setID(idDataBaseItem_t id) {idThis = id;}
    idDataBaseItem_t getID(void) {return idThis;}

    void setValue(QString val);
    QString getValue(void);

    isRoot_t getIsRoot(void) {return isRoot;}
    void setIsRoot(isRoot_t root) {isRoot = root;}

    isDeleted_t getIsDeleted (void) {return isDeleted;}
    void setIsDeleted(isDeleted_t del) {isDeleted = del;}

    idDataBaseItem_t getIdParent() {return idParent;}
    void setIdParent(idDataBaseItem_t id) {idParent = id;}

    void setIdChildren(idDataBaseItem_t id) {idChildren.append(id);}

    int getNumChildren(void) {return idChildren.size();}
    DataBaseItem* getChild(int i);
    idDataBaseItem_t getCildID(int i) {return idChildren.at(i);}

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
