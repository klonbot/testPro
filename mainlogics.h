#ifndef MAILLOGICS_H
#define MAILLOGICS_H

#include <QtCore>
#include <QVector>
#include "mainwindow.h"
#include "cache.h"
#include "database.h"
#include "connector.h"

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
    void slotControlAddDelete(void);

private:
    Cache cache;
    DataBase dataBase;
    MainWindow *window;
    Connector<CacheItem, Cache> cacheConnector;
    Connector<DataBaseItem, DataBase> dbConnector;
    int newIndex;

    void initTestTree(void);

    void refreshCasheTreeView(void);
    void refreshDBTreeView(void);

    void apply(void);
    void applyItem(CacheItem *pCacheItem, idDataBaseItem_t idParent);
    void applyChildren(CacheItem *pCacheItem, idDataBaseItem_t idParent);

    void clearCache();
};

#endif // MAILLOGICS_H
