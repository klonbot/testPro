#ifndef CACHECONNECTOR_H
#define CACHECONNECTOR_H

#include "QTreeWidgetItem"
#include "cacheitem.h"

class CacheConnector
{
public:
    CacheConnector();

    void add(QTreeWidgetItem *wItem, CacheItem *cItem);
    void clear(void) {connector.clear();}
    CacheItem* getCacheItem(QTreeWidgetItem *widgetItem);
    void refreshTreeWidgetData (void);
    int getSize(void) {return connector.size();}
    bool isDifferent(void);
private:
    typedef struct
    {
        QTreeWidgetItem *widgetItem;
        CacheItem *casheItem;
    } connectWidgetWithCacheItem_t;

    QVector<connectWidgetWithCacheItem_t> connector;


};

#endif // CACHECONNECTOR_H
