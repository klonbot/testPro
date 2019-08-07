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
    //cache.reset();

    // добавить
    /*
    CacheItem *item_1 = cache.newRoot();
    item_1->SetValue("t 1");
    CacheItem *item_11 = cache.newItem(item_1);
    item_11->SetValue("t 11");
    CacheItem *item_12 = cache.newItem(item_1);
    item_12->SetValue("t 12");
    CacheItem *item_121 = cache.newItem(item_12);
    item_121->SetValue("t 121");
    displayCache();
    */
}

void MainLogics::displayCache(void)
{
    /*
    QTreeWidget *cachedTreeView = window->getCachedTreeView();
    cachedTreeView->clear();
    cachedTreeView->setColumnCount(1);

    for (int i = 0; i < cache.size(); ++i)
    {
         CacheItem *cacheItem = cache.at(i);

         QTreeWidgetItem *widgetItem = new QTreeWidgetItem();
         widgetItem->setText(0, cacheItem->getValue());

         if (cacheItem->GetIsRoot())
         {
            displayChildren(widgetItem, cacheItem);
            widgetItem->setExpanded(false);
            cachedTreeView->addTopLevelItem (widgetItem);
         }
    }
    */
}

void MainLogics::displayChildren(QTreeWidgetItem *widgetItem, CacheItem *cacheItem)
{
    /*
    for (int j = 0; j < cacheItem->getNumChildren(); ++j)
    {
        QTreeWidgetItem *widgetChild = new QTreeWidgetItem();
        CacheItem *casheChild = cacheItem->getChild(j);
        widgetChild->setText(0, casheChild->getValue());
        widgetItem->addChild(widgetChild);
        displayChildren(widgetChild, casheChild);
    }
    */
}



