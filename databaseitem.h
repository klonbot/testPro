#ifndef DATABASEITEM_H
#define DATABASEITEM_H

#include "QString"
#include "QVector"

typedef enum {isRoot_false, isRoot_true} isRoot_t;
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

    bool getIsDeleted (void) {return isDeleted;}
    void setIsDeleted(bool del) {isDeleted = del;}

    idDataBaseItem_t getIdParent() {return idParent;}
    void setIdParent(idDataBaseItem_t id) {idParent = id;}

    void setIdChildren(idDataBaseItem_t id) {idChildren.append(id);}

    int getNumChildren(void) {return idChildren.size();}
    DataBaseItem* getChild(int i);
    idDataBaseItem_t getCildID(int i) {return idChildren.at(i);}

    void addAncestors(QVector<idDataBaseItem_t>* ancestors, idDataBaseItem_t id);
    void addAncestors(DataBaseItem *parent)
        {addAncestors(parent->getAncestors(), parent->getID());}
    int getNumAncestors(void) {return idAncestors.size();}
    idDataBaseItem_t getAncestor(int i) {return idAncestors.at(i);}
    QVector<idDataBaseItem_t>* getAncestors(void) {return &idAncestors;}

private:
    idDataBaseItem_t idThis;

    QString value;

    isRoot_t isRoot;
    bool isDeleted;

    QVector<idDataBaseItem_t> idChildren;
    idDataBaseItem_t idParent;
    QVector<idDataBaseItem_t> idAncestors; // Все дерево предков данного элемента из БД

    void init(idDataBaseItem_t id, idDataBaseItem_t idP, isRoot_t isR);
};

#endif // DATABASEITEM_H
