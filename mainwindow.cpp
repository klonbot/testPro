#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_NewItemBtn_clicked()
{
    signalNewItem();
}

void MainWindow::on_DeleteItemBtn_clicked()
{;
    signalDeleteItem();
}

void MainWindow::on_SetValueItemBtn_clicked()
{
    signalSetValueItem();
    ui->SetValueItemBtn->setEnabled(false);
}

void MainWindow::on_ApplyBtn_clicked()
{
    signalApply();
}

void MainWindow::on_ResetBtn_clicked()
{
    signalReset();
}

void MainWindow::on_UploadToCashBtn_clicked()
{
   signalUploadToCash();
}

void MainWindow::refreshCachedTreeView()
{
    /*
    ui->CachedTreeView->clear();
    ui->CachedTreeView->setColumnCount(1);
    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setText(0, "тест");
    ui->CachedTreeView->addTopLevelItem (item);
    */

    //ui->CachedTreeView->
}

void MainWindow::setValueItemBtnEnabled(bool en)
{
    ui->SetValueItemBtn->setEnabled(en);
}

QTreeWidget *MainWindow::getCachedTreeView()
{
    return ui->CachedTreeView;
}

void MainWindow::on_CachedTreeView_clicked(const QModelIndex &index)
{

}

void MainWindow::on_CachedTreeView_itemChanged(QTreeWidgetItem *item, int column)
{
    signalControlEdit();
}

void MainWindow::on_CachedTreeView_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    ui->SetValueItemBtn->setEnabled(false);
    signalRefreshCashTree();
}


