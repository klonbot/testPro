#include "mainlogics.h"

#include "QTreeWidget"


MainLogics::MainLogics(MainWindow &w, QObject *parent)
    : QObject(parent),
      cacheConnector(*w.getCachedTreeView(), cache),
      dbConnector(*w.getDBTreeView(), dataBase)
{   
    window = &w;
    connectSignals();
    initTestTree();
}

void MainLogics::connectSignals(void)
{
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
    if(false == cache.getIsDeletedRoot())
    {
        QTreeWidget *pCachedTreeView = window->getCachedTreeView();
        QTreeWidgetItem *pCurrItem = pCachedTreeView->currentItem();
        if(NULL != pCurrItem)
        {
            CacheItem *pCurrCashItem = cacheConnector.getItem(pCurrItem);
            if (false == pCurrCashItem->getIsDeleted())
            {
                QString text ="New node ";
                text += QString::number(newIndex++);
                cache.newItem(pCurrCashItem, text);
                refreshCasheTreeView();
            }
        }
    }
}

void MainLogics::slotDeleteItem(void)
{
    QTreeWidget *pCachedTreeView = window->getCachedTreeView();
    QTreeWidgetItem *pCurrItem = pCachedTreeView->currentItem();
    if(NULL != pCurrItem)
    {
        CacheItem *pCurrCashItem = cacheConnector.getItem(pCurrItem);
        cache.deleteItem(pCurrCashItem);
        refreshCasheTreeView();
    }
}

void MainLogics::slotSetValueItem(void)
{
    QTreeWidget *pCachedTreeView = window->getCachedTreeView();
    QTreeWidgetItem *pCurrItem = pCachedTreeView->currentItem();
    if(NULL != pCurrItem)
    {
        CacheItem *pCurrCashItem = cacheConnector.getItem(pCurrItem);
        if(false == pCurrCashItem->getIsDeleted())
        {
            QString oldValue = pCurrCashItem->getValue();

            pCurrCashItem->setValue(pCurrItem->text(0));            
            qDebug () << oldValue << "->" << pCurrCashItem->getValue();
        }
    }
}

void MainLogics::slotReset(void)
{    
    initTestTree();
    window->setCtrlBtnEnabled(false);
}

void MainLogics::slotUploadToCash(void)
{
    QTreeWidget *pDBTreeView = window->getDBTreeView();
    QTreeWidgetItem *pCurrItem = pDBTreeView->currentItem();

    if (NULL != pCurrItem)
    {
        DataBaseItem *pCurrBaseItem = dbConnector.getItem(pCurrItem);
        if (false == pCurrBaseItem->getIsDeleted())
        {
            CacheItem *cashItem = cache.searchInCache(pCurrBaseItem);
            if(NULL == cashItem)
            {
                if (false == cache.isDelitedAncestors(pCurrBaseItem))
                {
                    cache.newItem(pCurrBaseItem);
                }
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
    bool isEnabe = ((NULL != pCurrItem)&&(!cacheConnector.isDifferent()));
    window->setValueItemBtnEnabled(isEnabe);
}

void MainLogics::slotControlAddDelete(void)
{
    bool enBtn = false;
    if (false == cache.getIsDeletedRoot())
    {
        QTreeWidget *pCachedTreeView = window->getCachedTreeView();
        QTreeWidgetItem *pCurrItem = pCachedTreeView->currentItem();
        if(NULL != pCurrItem)
        {
            CacheItem *pCurrCashItem = cacheConnector.getItem(pCurrItem);
            enBtn = (false == pCurrCashItem->getIsDeleted());
        }
    }
    window->setCtrlBtnEnabled(enBtn);
}

void MainLogics::initTestTree(void)
{
    dataBase.clear();
    cache.reset();
    newIndex = 1;

    CacheItem *item_1 = cache.newItem("Node 1");
    /*CacheItem *item_11 =*/cache.newItem(item_1, "Node 11");
    CacheItem *item_12 = cache.newItem(item_1, "Node 12");
    /*CacheItem *item_121 =*/cache.newItem(item_12, "Node 121");
    CacheItem *item_122 = cache.newItem(item_12, "Node 122");
    /*CacheItem *item_1221 =*/cache.newItem(item_122, "Node 1221");
    /*CacheItem *item_123 =*/cache.newItem(item_12, "Node 123");
    /*CacheItem *item_124 =*/cache.newItem(item_12, "Node 124");
    CacheItem *item_13 = cache.newItem(item_1, "Node 13");
    /*CacheItem *item_131 =*/cache.newItem(item_13, "Node 131");
    /*CacheItem *item_132 =*/cache.newItem(item_13, "Node 132");
    CacheItem *item_133 = cache.newItem(item_13, "Node 133");
    /*CacheItem *item_1331 =*/cache.newItem(item_133, "Node 1331");
    /*CacheItem *item_1332 =*/cache.newItem(item_133, "Node 1332");
    /*CacheItem *item_134 =*/cache.newItem(item_13, "Node 134");
    apply();
    clearCache();
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
        }
    }
}

void MainLogics::slotApply(void)
{
    apply();
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
    refreshDBTreeView();
}

void MainLogics::applyItem(CacheItem *pCacheItem, ID_t idParent)
{
    ID_t id = 0;
    if(pCacheItem->isNewItem())
    {
        id = dataBase.addItemFromCashe(pCacheItem->getCacheData(), idParent);
    }
    else
    {
        id = dataBase.refreshItemFromCashe(pCacheItem->getCacheData());
    }
    applyChildren(pCacheItem, id);
}

void MainLogics::applyChildren(CacheItem *pCacheItem, ID_t idParent)
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
