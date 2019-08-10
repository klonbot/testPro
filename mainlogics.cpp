#include "mainlogics.h"

#include "QTreeWidget"


MainLogics::MainLogics(MainWindow &w, QObject *parent)
    : QObject(parent),
      cacheConnector(*w.getCachedTreeView()),
      dbConnector(*w.getCachedTreeView())
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
        CacheItem *pCurrCashItem = cacheConnector.getItem(pCurrItem);
        if (isDeleted_false == pCurrCashItem->isDeleted())
        {
            QString text ="New ";
            text += QString::number(newIndex++);
            cache.newItem(pCurrCashItem, text);
            refreshCasheTreeView();
        }
    }
}

void MainLogics::slotDeleteItem(void)
{
    qDebug() << "slotDeleteItem!";
    QTreeWidget *pCachedTreeView = window->getCachedTreeView();
    QTreeWidgetItem *pCurrItem = pCachedTreeView->currentItem();
    if(NULL != pCurrItem)
    {
        CacheItem *pCurrCashItem = cacheConnector.getItem(pCurrItem);
        pCurrCashItem->deleteItem();
        refreshCasheTreeView();
    }
}

void MainLogics::slotSetValueItem(void)
{
    //qDebug() << "slotSetValueItem!";

    QTreeWidget *pCachedTreeView = window->getCachedTreeView();
    QTreeWidgetItem *pCurrItem = pCachedTreeView->currentItem();
    if(NULL != pCurrItem)
    {
        CacheItem *pCurrCashItem = cacheConnector.getItem(pCurrItem);
        if(isDeleted_false == pCurrCashItem->isDeleted())
        {
            QString oldValue = pCurrCashItem->getValue();
            // запись текущего значения в кэш
            pCurrCashItem->setValue(pCurrItem->text(0));            
            qDebug () << oldValue << "->" << pCurrCashItem->getValue();
        }
    }
}

void MainLogics::slotReset(void)
{    
    initTestTree();
    qDebug() << "slotReset!";
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
    QTreeWidget *pCachedTreeView = window->getCachedTreeView();
    QTreeWidgetItem *pCurrItem = pCachedTreeView->currentItem();
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
    dataBase.clear();
    cache.reset();
    newIndex = 1;

    // добавить
    CacheItem *item_1 = cache.newItem("t 1");
    CacheItem *item_11 = cache.newItem(item_1, "t 11");
    CacheItem *item_12 = cache.newItem(item_1, "t 12");
    CacheItem *item_121 = cache.newItem(item_12, "t 121");
    CacheItem *item_122 = cache.newItem(item_12, "t 122");
    CacheItem *item_1221 = cache.newItem(item_122, "t 1221");
    CacheItem *item_123 = cache.newItem(item_12, "t 123");
    refreshCasheTreeView();
}

void MainLogics::refreshCasheTreeView(void)
{
    cacheConnector.clear();
    QTreeWidget *pCachedTreeView = window->getCachedTreeView();
    pCachedTreeView->clear();
    pCachedTreeView->setColumnCount(1);

    for (int ind = 0; ind < cache.size(); ++ind)
    {
        CacheItem *pCacheItem = cache.at(ind);
        if (pCacheItem->getIsRoot())
        {
            cacheConnector.connectTree(pCacheItem);
        }
    }
}

// Применение кэша к базе данных
void MainLogics::slotApply(void)
{
    for (int ind = 0; ind < cache.size(); ++ind)
    {
        CacheItem *pCacheItem = cache.at(ind);
        if (pCacheItem->getIsRoot())
        {
            applyItem(pCacheItem, 0);
        }
        else
        {
            // также со всеми топами
        }
    }

    clearCache();
    qDebug() << "slotApply!";
}

void MainLogics::applyItem(CacheItem *pCacheItem, idDataBaseItem_t idParent)
{
    idDataBaseItem_t id = 0;
    if(pCacheItem->isNewItem())
    {
        id = dataBase.addItemFromCashe(pCacheItem->getDataBaseItem(), idParent);
    }
    else
    {
        id = dataBase.refreshItemFromCashe(pCacheItem->getDataBaseItem());
    }
    applyChildren(pCacheItem, id);
}

void MainLogics::applyChildren(CacheItem *pCacheItem, idDataBaseItem_t idParent)
{
    for (int ind = 0; ind < pCacheItem->getNumChildren(); ++ind)
    {
        CacheItem *pCasheChild = pCacheItem->getChild(ind);
        applyItem(pCasheChild, idParent);
    }
}

void MainLogics::clearCache()
{
    cacheConnector.clear();
    cache.reset();
    refreshCasheTreeView();
}
