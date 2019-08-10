#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "QTreeWidgetItem"

template <typename Item>
class Connector
{
public:
    Connector(QTreeWidget &tw):treeWiget(tw) {}
    void clear(void) {connector.clear();}
    int getSize(void) {return connector.size();}

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

    void connectItem(QTreeWidgetItem *pWidgetItem, Item *pCasheChild);
    void connectChildren(QTreeWidgetItem *pWidgetItem, Item *pCacheItem);
    void refreshTreeWidgetItemData (QTreeWidgetItem *wItem, Item *item);
};

template<typename Item>
void Connector<Item>::add(QTreeWidgetItem *wItem, Item *item)
{
    connectItem_t connect;
    connect.item = item;
    connect.widgetItem = wItem;
    connector.append(connect);
}

template<typename Item>
Item* Connector<Item>::getItem(QTreeWidgetItem *widgetItem)
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

template<typename Item>
void Connector<Item>::refreshTreeWidgetItemData (QTreeWidgetItem *wItem, Item *item)
{
        QString value = item->getValue();
        if (item->isDeleted())
        {
            value = "(Удален) " + value;
        }
        wItem->setText(0, value);
}

template<typename Item>
void Connector<Item>::refreshTreeWidgetData (void)
{
    for (int ind = 0; ind < connector.size(); ++ind)
    {
        connectItem_t connect = connector.at(ind);
        refreshTreeWidgetItemData (connect.widgetItem, connect.item);
    }
}

template<typename Item>
bool Connector<Item>::isDifferent(void)
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

template<typename Item>
void Connector<Item>::connectItem(QTreeWidgetItem *pWidgetItem, Item *pCasheChild)
{
    QTreeWidgetItem *pWidgetChild = new QTreeWidgetItem();
    pWidgetChild->setFlags( pWidgetChild->flags() | Qt::ItemIsEditable);

    Qt::ItemFlags flags = (pCasheChild->isDeleted()) ?
                pWidgetChild->flags() & (~Qt::ItemIsEditable) : pWidgetChild->flags() | Qt::ItemIsEditable;
    pWidgetChild->setFlags(flags);

    if (NULL != pWidgetItem)
        pWidgetItem->addChild(pWidgetChild);
    else
        treeWiget.addTopLevelItem (pWidgetChild);
    add(pWidgetChild, pCasheChild);
    refreshTreeWidgetItemData (pWidgetChild, pCasheChild);

    connectChildren(pWidgetChild, pCasheChild); // рекурсивно
    treeWiget.expandItem(pWidgetChild);
}

template<typename Item>
void Connector<Item>::connectChildren(QTreeWidgetItem *pWidgetItem, Item *pCacheItem)
{
    for (int ind = 0; ind < pCacheItem->getNumChildren(); ++ind)
    {
        CacheItem *pCasheChild = pCacheItem->getChild(ind);
        connectItem(pWidgetItem, pCasheChild);
    }
}

#endif // CONNECTOR_H
