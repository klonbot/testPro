#ifndef DATABASEITEM_H
#define DATABASEITEM_H

#include "QString"
#include "QVector"

typedef int ID_t;

class DataBaseItem
{
public:
    DataBaseItem(ID_t id, ID_t idP);
    DataBaseItem(ID_t id);
    DataBaseItem(DataBaseItem *item);

    void setID(ID_t id) {idThis = id;}
    ID_t getID(void) {return idThis;}

    void setValue(QString val);
    QString getValue(void);

    bool getIsRoot(void) {return isRoot;}
    void setIsRoot(bool root) {isRoot = root;}

    bool getIsDeleted (void) {return isDeleted;}
    void setIsDeleted(bool del) {isDeleted = del;}

    ID_t getIdParent() {return idParent;}
    void setIdParent(ID_t id) {idParent = id;}

    void setIdChildren(ID_t id) {idChildren.append(id);}

    int getNumChildren(void) {return idChildren.size();}
    ID_t getCildID(int i) {return idChildren.at(i);}

    void addAncestors(QVector<ID_t>* ancestors, ID_t id);
    void addAncestors(DataBaseItem *parent)
        {addAncestors(parent->getAncestors(), parent->getID());}
    int getNumAncestors(void) {return idAncestors.size();}
    ID_t getAncestor(int i) {return idAncestors.at(i);}
    QVector<ID_t>* getAncestors(void) {return &idAncestors;}

private:
    ID_t idThis;

    QString value;

    bool isRoot;
    bool isDeleted;

    QVector<ID_t> idChildren;
    ID_t idParent;
    QVector<ID_t> idAncestors; // Все дерево предков данного элемента из БД

    void init(ID_t id, ID_t idP, bool isR);
};

#endif // DATABASEITEM_H
