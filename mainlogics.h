#ifndef MAILLOGICS_H
#define MAILLOGICS_H

#include <QtCore>
#include <QVector>
#include "mainwindow.h"
#include "cache.h"
#include "cacheconnector.h"

class MainLogics : public QObject
{
    Q_OBJECT

public:
    MainLogics(MainWindow &w, QObject *parent = 0);

    void CreateSignals(void);

private slots:
    void slotNewItem(void);
    void slotDeleteItem(void);
    void slotSetValueItem(void);
    void slotApply(void);
    void slotReset(void);
    void slotUploadToCash(void);
    void slotRefreshCashTree(void);
    void slotControlEdit(void);

private:
    Cache cache;
    MainWindow *window;
    CacheConnector cacheConnector;
    int newIndex;

    //void newCacheItem(QString value, QTreeWidgetItem parent = 0);
    void initTestTree(void);

    void refreshCasheTreeView(void);
    void refreshChildren(QTreeWidgetItem *widgetItem, CacheItem *cacheItem);
    void refreshItem(QTreeWidgetItem *widgetItem, CacheItem *cacheItem);
};

#endif // MAILLOGICS_H
