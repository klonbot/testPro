#ifndef DATABASEITEM_H
#define DATABASEITEM_H

#include "QString"
#include "QVector"

typedef int ID_t;
typedef int Key_t;

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

    void setLeftKey(Key_t lk) {leftKey = lk;}
    Key_t getLeftKey(void) const {return leftKey;}
    void setRightKey(Key_t rk) {rightKey = rk;}
    Key_t getRightKey(void) const {return rightKey;}
private:
    ID_t idThis;

    QString value;

    bool isRoot;
    bool isDeleted;

    QVector<ID_t> idChildren;
    ID_t idParent;
    Key_t leftKey;
    Key_t rightKey;

    void init(ID_t id, ID_t idP, bool isR);
};

#endif // DATABASEITEM_H
