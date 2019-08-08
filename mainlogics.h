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
    MainLogics(QObject *parent = 0);

    void CreateSignals(MainWindow &w);

private slots:
    void slotNewItem(void);
    void slotDeleteItem(void);
    void slotSetValueItem(void);
    void slotApply(void);
    void slotReset(void);
    void slotUploadToCash(void);

private:
    Cache cache;
    MainWindow *window;
    CacheConnector cacheConnector;

    void initTestTree(void);

    void displayCache(void);
    void displayChildren(QTreeWidgetItem *widgetItem, CacheItem *cacheItem);
};

#endif // MAILLOGICS_H
