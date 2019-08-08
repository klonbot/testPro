#include "mainlogics.h"

#include "QTreeWidget"


MainLogics::MainLogics(QObject *parent)
    : QObject(parent)
{
    qDebug() << "init mainLogic!";
}

void MainLogics::CreateSignals(MainWindow &w)
{
    qDebug() << "CreateSignals!";

    connect(&w, SIGNAL(signalNewItem()), this, SLOT(slotNewItem()));
    connect(&w, SIGNAL(signalDeleteItem()), this, SLOT(slotDeleteItem()));
    connect(&w, SIGNAL(signalSetValueItem()), this, SLOT(slotSetValueItem()));
    connect(&w, SIGNAL(signalApply()), this, SLOT(slotApply()));
    connect(&w, SIGNAL(signalReset()), this, SLOT(slotReset()));
    connect(&w, SIGNAL(signalUploadToCash()), this, SLOT(slotUploadToCash()));

    window = &w;
}

void MainLogics::slotNewItem(void)
{
    qDebug() << "slotNewItem!";
}

void MainLogics::slotDeleteItem(void)
{
    qDebug() << "slotDeleteItem!";
}

void MainLogics::slotSetValueItem(void)
{
    qDebug() << "slotSetValueItem!";
}

void MainLogics::slotApply(void)
{
    qDebug() << "slotApply!";
}

void MainLogics::slotReset(void)
{
    qDebug() << "slotReset!";
    initTestTree();
}

void MainLogics::slotUploadToCash(void)
{
    qDebug() << "slotUploadToCash!";
}

void MainLogics::initTestTree(void)
{
    cache.reset();
    cacheConnector.clear();

    // добавить
    CacheItem *item_1 = cache.newItem("t 1");
    CacheItem *item_11 = cache.newItem(item_1, "t 11");
    CacheItem *item_12 = cache.newItem(item_1, "t 12");
    CacheItem *item_121 = cache.newItem(item_12, "t 121");
    CacheItem *item_122 = cache.newItem(item_12, "t 122");
    CacheItem *item_1221 = cache.newItem(item_122, "t 1221");
    CacheItem *item_123 = cache.newItem(item_12, "t 123");
    displayCache();
}

void MainLogics::displayCache(void)
{
    QTreeWidget *cachedTreeView = window->getCachedTreeView();
    cachedTreeView->clear();
    cachedTreeView->setColumnCount(1);

    for (int ind = 0; ind < cache.size(); ++ind)
    {
         CacheItem *cacheItem = cache.at(ind);
         QTreeWidgetItem *widgetItem = new QTreeWidgetItem();
         widgetItem->setText(0, cacheItem->getValue());
         cacheConnector.add(widgetItem, cacheItem);

         if (cacheItem->getIsRoot()) // непонятное условие
         {
            displayChildren(widgetItem, cacheItem);
            widgetItem->setExpanded(false);
            cachedTreeView->addTopLevelItem (widgetItem);            
         }
    }
}

void MainLogics::displayChildren(QTreeWidgetItem *widgetItem, CacheItem *cacheItem)
{
    for (int ind = 0; ind < cacheItem->getNumChildren(); ++ind)
    {
        QTreeWidgetItem *widgetChild = new QTreeWidgetItem();
        CacheItem *casheChild = cacheItem->getChild(ind);
        widgetChild->setText(0, casheChild->getValue());
        widgetItem->addChild(widgetChild);
        cacheConnector.add(widgetChild, casheChild);

        displayChildren(widgetChild, casheChild);
    }
}



