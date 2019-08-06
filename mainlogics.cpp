#include "mainlogics.h"

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
    initTree();
}

void MainLogics::slotUploadToCash(void)
{
    qDebug() << "slotUploadToCash!";
}

void MainLogics::initTree(void)
{
    // добавить
}






