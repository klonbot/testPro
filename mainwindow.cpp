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

// изменил элемент
void MainWindow::on_CachedTreeView_itemChanged(QTreeWidgetItem *item, int column)
{
    signalControlEdit();
}

// изменил выбраный элемент
void MainWindow::on_CachedTreeView_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    ui->SetValueItemBtn->setEnabled(false);
    signalRefreshCashTree();

    bool btnEnable = (NULL != current);
    ui->NewItemBtn->setEnabled(btnEnable);
    ui->DeleteItemBtn->setEnabled(btnEnable);
}

void MainWindow::on_CachedTreeView_itemEntered(QTreeWidgetItem *item, int column)
{

}

void MainWindow::on_CachedTreeView_itemClicked(QTreeWidgetItem *item, int column)
{

}

void MainWindow::on_CachedTreeView_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    ui->SetValueItemBtn->setEnabled(true);
}
