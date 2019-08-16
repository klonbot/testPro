#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "QTreeWidgetItem"
#include "databaseitem.h"

template <typename Item, typename Bd>
class Connector
{
public:
    Connector(QTreeWidget &tw, Bd &b):treeWiget(tw), bd(b) {}
    int getSize(void) {return connector.size();}

    void clear(void);
    void add(QTreeWidgetItem *wItem, Item *cItem);
    void refreshTreeWidgetData (void);
    Item* getItem(QTreeWidgetItem *widgetItem);
    bool isDifferent(void);

    void connectTree(Item *pItem) {connectItem(NULL, pItem);}
private:
    typedef struct
    {
        QTreeWidgetItem *widgetItem;
        Item *item;
    } connectItem_t;

    QVector<connectItem_t> connector;

    QTreeWidget &treeWiget;
    Bd &bd;

    void connectItem(QTreeWidgetItem *pWidgetItem, Item *pCasheChild);
    void connectChildrenPointMode(QTreeWidgetItem *pWidgetItem, Item *pCacheItem);
    void connectChildrenIdMode(QTreeWidgetItem *pWidgetItem, Item *pCacheItem);
    void refreshTreeWidgetItemData (QTreeWidgetItem *wItem, Item *item);
};

template<typename Item, typename Bd>
void Connector<Item, Bd>::clear(void)
{
    connector.clear();
    treeWiget.clear();
    treeWiget.setColumnCount(1);
}

template<typename Item, typename Bd>
void Connector<Item, Bd>::add(QTreeWidgetItem *wItem, Item *item)
{
    connectItem_t connect;
    connect.item = item;
    connect.widgetItem = wItem;
    connector.append(connect);
}

template<typename Item, typename Bd>
Item* Connector<Item, Bd>::getItem(QTreeWidgetItem *widgetItem)
{
    for (int ind = 0; ind < connector.size(); ++ind)
    {
        connectItem_t connect = connector.at(ind);
        if (connect.widgetItem == widgetItem)
        {
            return connect.item;
        }
    }

    qDebug ("WARNING: Not found Item for widgetItem in getItem!");
    return NULL;
}

template<typename Item, typename Bd>
void Connector<Item, Bd>::refreshTreeWidgetItemData (QTreeWidgetItem *wItem, Item *item)
{
        QString value = item->getValue();
        if (item->getIsDeleted())
        {
            value = "(Удален) " + value;
        }
        wItem->setText(0, value);
}

template<typename Item, typename Bd>
void Connector<Item, Bd>::refreshTreeWidgetData (void)
{
    for (int ind = 0; ind < connector.size(); ++ind)
    {
        connectItem_t connect = connector.at(ind);
        refreshTreeWidgetItemData (connect.widgetItem, connect.item);
    }
}

template<typename Item, typename Bd>
bool Connector<Item, Bd>::isDifferent(void)
{
    for (int ind = 0; ind < connector.size(); ++ind)
    {
        connectItem_t connect = connector.at(ind);
        if (connect.widgetItem->text(0) != connect.item->getValue())
        {
            return false;
        }
    }
    return true;
}

template<typename Item, typename Bd>
void Connector<Item, Bd>::connectItem(QTreeWidgetItem *pWidgetItem, Item *pCasheChild)
{
    QTreeWidgetItem *pWidgetChild = new QTreeWidgetItem();
    pWidgetChild->setFlags( pWidgetChild->flags() | Qt::ItemIsEditable);

    Qt::ItemFlags flags = (pCasheChild->getIsDeleted() || (false == bd.isEditable)) ?
                pWidgetChild->flags() & (~Qt::ItemIsEditable) : pWidgetChild->flags() | Qt::ItemIsEditable;
    pWidgetChild->setFlags(flags);


    if (NULL != pWidgetItem)
        pWidgetItem->addChild(pWidgetChild);
    else
        treeWiget.addTopLevelItem (pWidgetChild);
    add(pWidgetChild, pCasheChild);
    refreshTreeWidgetItemData (pWidgetChild, pCasheChild);
    if (bd.isEditable)
        connectChildrenPointMode(pWidgetChild, pCasheChild);
    else
        connectChildrenIdMode(pWidgetChild, pCasheChild);

    treeWiget.expandItem(pWidgetChild);
}

template<typename Item, typename Bd>
void Connector<Item, Bd>::connectChildrenPointMode(QTreeWidgetItem *pWidgetItem, Item *pItem)
{
    for (int ind = 0; ind < pItem->getNumChildren(); ++ind)
    {
        Item *pChild = bd.getChild(pItem, ind);
        connectItem(pWidgetItem, pChild);
    }
}

template<typename Item, typename Bd>
void Connector<Item, Bd>::connectChildrenIdMode(QTreeWidgetItem *pWidgetItem, Item *pItem)
{
    for (int ind = 0; ind < bd.getSize(); ++ind)
    {
        ID_t idParent = pItem->getID();
        DataBaseItem* item = bd.atData(ind);
        if (true == item->getIsRoot())
            continue;

        if(idParent == item->getIdParent())
        {
            Item *pChild = bd.getItem(ind);
            connectItem(pWidgetItem, pChild);
        }
    }
}

#endif // CONNECTOR_H
