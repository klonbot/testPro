#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "QTreeWidgetItem"

template <typename Item>
class Connector
{
public:
    Connector() {}
    void clear(void) {connector.clear();}
    int getSize(void) {return connector.size();}

    void add(QTreeWidgetItem *wItem, Item *cItem);
    void refreshTreeWidgetData (void);
    Item* getItem(QTreeWidgetItem *widgetItem);
    bool isDifferent(void);
private:
    typedef struct
    {
        QTreeWidgetItem *widgetItem;
        Item *item;
    } connectItem_t;

    QVector<connectItem_t> connector;
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
void Connector<Item>::refreshTreeWidgetData (void)
{
    for (int ind = 0; ind < connector.size(); ++ind)
    {
        connectItem_t connect = connector.at(ind);
        QString value = connect.item->getValue();
        if (connect.item->isDeleted()) // !!!!
        {
            value = "(Удален) " + value;
        }
        connect.widgetItem->setText(0, value);
    }
}

template<typename Item>
bool Connector<Item>::isDifferent(void)
{
    for (int ind = 0; ind < connector.size(); ++ind)
    {
        connectItem_t connect = connector.at(ind);
        if (connect.widgetItem->text(0) != connect.item->getValue())// !!
        {
            return false;
        }
    }
    return true;
}

#endif // CONNECTOR_H
