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
        CacheItem *pCurrCashItem = cacheConnector.getCacheItem(pCurrItem);
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
        CacheItem *pCurrCashItem = cacheConnector.getCacheItem(pCurrItem);
        if(isDeleted_false == pCurrCashItem->isDeleted())
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
            refreshItem(NULL, pCacheItem);
        }
    }
}

void MainLogics::refreshChildren(QTreeWidgetItem *pWidgetItem, CacheItem *pCacheItem)
{
    for (int ind = 0; ind < pCacheItem->getNumChildren(); ++ind)
    {
        CacheItem *pCasheChild = pCacheItem->getChild(ind);
        refreshItem(pWidgetItem, pCasheChild);
    }
}

void MainLogics::refreshItem(QTreeWidgetItem *pWidgetItem, CacheItem *pCasheChild)
{
    QTreeWidget *pCachedTreeView = window->getCachedTreeView();
    QTreeWidgetItem *pWidgetChild = new QTreeWidgetItem();
    pWidgetChild->setFlags( pWidgetChild->flags() | Qt::ItemIsEditable);

    Qt::ItemFlags flags = (pCasheChild->isDeleted()) ?
                pWidgetChild->flags() & (~Qt::ItemIsEditable) : pWidgetChild->flags() | Qt::ItemIsEditable;
    pWidgetChild->setFlags(flags);

    if (NULL != pWidgetItem)
        pWidgetItem->addChild(pWidgetChild);
    else
        pCachedTreeView->addTopLevelItem (pWidgetChild);
    cacheConnector.add(pWidgetChild, pCasheChild);  // образует связь между элементами моего кэша и QTreeWidgetItem
    cacheConnector.refreshTreeWidgetData();         // обновляет на основе связи данные

    refreshChildren(pWidgetChild, pCasheChild); // рекурсивно
    pCachedTreeView->expandItem(pWidgetChild);
}



