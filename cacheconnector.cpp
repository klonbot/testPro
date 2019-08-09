#include "cacheconnector.h"

CacheConnector::CacheConnector()
{

}

void CacheConnector::add(QTreeWidgetItem *wItem, CacheItem *cItem)
{
    connectWidgetWithCacheItem_t connect;
    connect.casheItem = cItem;
    connect.widgetItem = wItem;
    connector.append(connect);
}

CacheItem* CacheConnector::getCacheItem(QTreeWidgetItem *widgetItem)
{
    for (int ind = 0; ind < connector.size(); ++ind)
    {
        connectWidgetWithCacheItem_t connect = connector.at(ind);
        if (connect.widgetItem == widgetItem)
        {
            return connect.casheItem;
        }
    }

    qDebug ("WARNING: Not found cacheItem for widgetItem in getCacheItem!");
    return NULL;
}

void CacheConnector::refreshTreeWidgetData (void) // TODO: перенести в логику
{
    for (int ind = 0; ind < connector.size(); ++ind)
    {
        connectWidgetWithCacheItem_t connect = connector.at(ind);
        QString value = connect.casheItem->getValue();
        if (connect.casheItem->isDeleted())
        {
            value = "(Удален) " + value;
        }
        connect.widgetItem->setText(0, value);
    }
}

bool CacheConnector::isDifferent(void)
{
    for (int ind = 0; ind < connector.size(); ++ind)
    {
        connectWidgetWithCacheItem_t connect = connector.at(ind);
        if (connect.widgetItem->text(0) != connect.casheItem->getValue())
        {
            return false;
        }
    }
    return true;
}

