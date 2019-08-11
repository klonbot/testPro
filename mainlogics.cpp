#include "mainlogics.h"

#include "QTreeWidget"


MainLogics::MainLogics(MainWindow &w, QObject *parent)
    : QObject(parent),
      cacheConnector(*w.getCachedTreeView(), cache),
      dbConnector(*w.getDBTreeView(), dataBase)
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
    connect(window, SIGNAL(signalControlAddDelete()), this, SLOT(slotControlAddDelete()));
}

void MainLogics::slotNewItem(void)
{
    qDebug() << "slotNewItem!";
    QTreeWidget *pCachedTreeView = window->getCachedTreeView();
    QTreeWidgetItem *pCurrItem = pCachedTreeView->currentItem();
    if(NULL != pCurrItem)
    {
        CacheItem *pCurrCashItem = cacheConnector.getItem(pCurrItem);
        if (isDeleted_false == pCurrCashItem->getIsDeleted())
        {
            QString text ="New node ";
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
        if(isDeleted_false == pCurrCashItem->getIsDeleted())
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

    QTreeWidget *pDBTreeView = window->getDBTreeView();
    QTreeWidgetItem *pCurrItem = pDBTreeView->currentItem();

    if (NULL != pCurrItem)
    {
        DataBaseItem *pCurrBaseItem = dbConnector.getItem(pCurrItem);
        if (isDeleted_false == pCurrBaseItem->getIsDeleted())
        {
            CacheItem *cashItem = cache.searchInCache(pCurrBaseItem);
            if(NULL != cashItem)
            {
                DataBaseItem *cacheBaseItem = cashItem->getDataBaseItem();
                *cacheBaseItem = *pCurrBaseItem;
            }
            else
            {
                CacheItem* newItem = cache.newItem(pCurrBaseItem);
            }

            refreshCasheTreeView();
        }
    }
}

void MainLogics::slotRefreshCashTree(void)
{
    cacheConnector.refreshTreeWidgetData();
}

void MainLogics::slotControlEdit(void)
{
    QTreeWidget *pCachedTreeView = window->getCachedTreeView();
    QTreeWidgetItem *pCurrItem = pCachedTreeView->currentItem();
    if(NULL != pCurrItem)
    {
        if(cacheConnector.isDifferent())
        {
            window->setValueItemBtnEnabled(false);
        }
        else
        {
            window->setValueItemBtnEnabled(true);
        }
    }
    else
    {
        window->setValueItemBtnEnabled(false);
    }
}

void MainLogics::slotControlAddDelete(void)
{
    QTreeWidget *pCachedTreeView = window->getCachedTreeView();
    QTreeWidgetItem *pCurrItem = pCachedTreeView->currentItem();
    if(NULL != pCurrItem)
    {
        CacheItem *pCurrCashItem = cacheConnector.getItem(pCurrItem);
        bool enBtn = (isDeleted_false ==pCurrCashItem->getIsDeleted());
        window->setCtrlBtnEnabled(enBtn);
    }
    else
    {
        window->setCtrlBtnEnabled(false);
    }
}

void MainLogics::initTestTree(void)
{
    dataBase.clear();
    cache.reset();
    newIndex = 1;

    // добавить
    CacheItem *item_1 = cache.newItem("Node 1");
    CacheItem *item_11 = cache.newItem(item_1, "Node 11");
    CacheItem *item_12 = cache.newItem(item_1, "Node 12");
    CacheItem *item_121 = cache.newItem(item_12, "Node 121");
    CacheItem *item_122 = cache.newItem(item_12, "Node 122");
    CacheItem *item_1221 = cache.newItem(item_122, "Node 1221");
    CacheItem *item_123 = cache.newItem(item_12, "Node 123");
    apply();
    refreshCasheTreeView();
    refreshDBTreeView();
}

void MainLogics::refreshCasheTreeView(void)
{
    cacheConnector.clear();
    for (int ind = 0; ind < cache.size(); ++ind)
    {
        CacheItem *pCacheItem = cache.at(ind);
        if (pCacheItem->isTop())
        {
            cacheConnector.connectTree(pCacheItem);
        }
    }
}

void MainLogics::refreshDBTreeView(void)
{
    dbConnector.clear();

    for (int ind = 0; ind < dataBase.size(); ++ind)
    {
        DataBaseItem *pDbItem = dataBase.at(ind);
        if (pDbItem->getIsRoot())
        {
            dbConnector.connectTree(pDbItem);
            return;
        }
    }
}

// Применение кэша к базе данных
void MainLogics::slotApply(void)
{
    apply();
    qDebug() << "slotApply!";
}

void MainLogics::apply(void)
{
    for (int ind = 0; ind < cache.size(); ++ind)
    {
        CacheItem *pCacheItem = cache.at(ind);
        if (pCacheItem->isTop())
        {
            applyItem(pCacheItem, 0);
        }
    }

    clearCache();
    refreshDBTreeView();
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
