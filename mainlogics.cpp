#include "mainlogics.h"

#include "QTreeWidget"


MainLogics::MainLogics(MainWindow &w, QObject *parent)
    : QObject(parent)
{
    qDebug() << "init mainLogic!";    
    window = &w;
    CreateSignals();
    initTestTree();
}

void MainLogics::CreateSignals(void)
{
    qDebug() << "CreateSignals!";

    connect(window, SIGNAL(signalNewItem()), this, SLOT(slotNewItem()));
    connect(window, SIGNAL(signalDeleteItem()), this, SLOT(slotDeleteItem()));
    connect(window, SIGNAL(signalSetValueItem()), this, SLOT(slotSetValueItem()));
    connect(window, SIGNAL(signalApply()), this, SLOT(slotApply()));
    connect(window, SIGNAL(signalReset()), this, SLOT(slotReset()));
    connect(window, SIGNAL(signalUploadToCash()), this, SLOT(slotUploadToCash()));
    connect(window, SIGNAL(signalRefreshCashTree()), this, SLOT(slotRefreshCashTree()));
    connect(window, SIGNAL(signalControlEdit()), this, SLOT(slotControlEdit()));
}

void MainLogics::slotNewItem(void)
{
    qDebug() << "slotNewItem!";
    QTreeWidget *pCachedTreeView = window->getCachedTreeView();
    QTreeWidgetItem *pCurrItem = pCachedTreeView->currentItem();
    if(NULL != pCurrItem)
    {
        CacheItem *pCurrCashItem = cacheConnector.getCacheItem(pCurrItem);
        CacheItem *pNewItem = cache.newItem(pCurrCashItem, "new");
        QTreeWidgetItem *pWidgetItem = new QTreeWidgetItem();
        pWidgetItem->setText(0, pCurrCashItem->getValue());
        pWidgetItem->setFlags( pWidgetItem->flags() | Qt::ItemIsEditable);
        pCurrItem->addChild(pWidgetItem);
        pCachedTreeView->expandItem(pWidgetItem);
        cacheConnector.add(pWidgetItem, pNewItem);
        cacheConnector.refreshTreeWidgetData();
    }
}

void MainLogics::slotDeleteItem(void)
{
    qDebug() << "slotDeleteItem!";
}

void MainLogics::slotSetValueItem(void)
{
    qDebug() << "slotSetValueItem!";

    QTreeWidget *pCachedTreeView = window->getCachedTreeView();
    QTreeWidgetItem *pCurrItem = pCachedTreeView->currentItem();
    if(NULL != pCurrItem)
    {
        CacheItem *pCurrCashItem = cacheConnector.getCacheItem(pCurrItem);
        if(NULL != pCurrCashItem)
        {
            QString oldValue = pCurrCashItem->getValue();

            // запись текущего значения в кэш
            pCurrCashItem->setValue(pCurrItem->text(0));

            qDebug () << oldValue << "->" << pCurrCashItem->getValue();
        }
    }
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

void MainLogics::slotRefreshCashTree(void)
{
    //qDebug() << "slotRefreshCashTree!";
    cacheConnector.refreshTreeWidgetData();
}

void MainLogics::slotControlEdit(void)
{
    //qDebug() << "slotControlEdit!";
    if(cacheConnector.isDifferent())
    {
        //qDebug("btn Disable");
        window->setValueItemBtnEnabled(false);
    }
    else
    {
        //qDebug("btn Enable");
        window->setValueItemBtnEnabled(true);
    }
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
    QTreeWidget *pCachedTreeView = window->getCachedTreeView();
    pCachedTreeView->clear();
    pCachedTreeView->setColumnCount(1);

    for (int ind = 0; ind < cache.size(); ++ind)
    {
         CacheItem *pCacheItem = cache.at(ind);
         QTreeWidgetItem *pWidgetItem = new QTreeWidgetItem();
         pWidgetItem->setText(0, pCacheItem->getValue());
         pWidgetItem->setFlags( pWidgetItem->flags() | Qt::ItemIsEditable);
         cacheConnector.add(pWidgetItem, pCacheItem);

         if (pCacheItem->getIsRoot()) // непонятное условие
         {
            displayChildren(pWidgetItem, pCacheItem);
            pCachedTreeView->addTopLevelItem (pWidgetItem);
         }
         pCachedTreeView->expandItem(pWidgetItem);
    }

}

void MainLogics::displayChildren(QTreeWidgetItem *widgetItem, CacheItem *cacheItem)
{
    for (int ind = 0; ind < cacheItem->getNumChildren(); ++ind)
    {
        QTreeWidgetItem *pWidgetChild = new QTreeWidgetItem();
        CacheItem *pCasheChild = cacheItem->getChild(ind);
        pWidgetChild->setText(0, pCasheChild->getValue());
        pWidgetChild->setFlags( pWidgetChild->flags() | Qt::ItemIsEditable);
        //pWidgetChild->setExpanded(true);

        widgetItem->addChild(pWidgetChild);
        cacheConnector.add(pWidgetChild, pCasheChild);

        displayChildren(pWidgetChild, pCasheChild);

        QTreeWidget *pCachedTreeView = window->getCachedTreeView();
        pCachedTreeView->expandItem(pWidgetChild);
    }
}



