#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
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

void MainWindow::setValueItemBtnEnabled(bool en)
{
    ui->SetValueItemBtn->setEnabled(en);
}

void MainWindow::setCtrlBtnEnabled(bool en)
{
    ui->NewItemBtn->setEnabled(en);
    ui->DeleteItemBtn->setEnabled(en);
}

void MainWindow::setCtrlBtnEnabled(void)
{
    ui->NewItemBtn->setEnabled(true);
    ui->DeleteItemBtn->setEnabled(false);
}

QTreeWidget *MainWindow::getCachedTreeView()
{
    return ui->CachedTreeView;
}

QTreeWidget *MainWindow::getDBTreeView()
{
    return ui->DBTreeView;
}

void MainWindow::on_CachedTreeView_itemChanged(QTreeWidgetItem*, int)
{
    signalControlEdit();
    signalControlAddDelete();
}

void MainWindow::on_CachedTreeView_currentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*)
{
    signalControlAddDelete();
    ui->SetValueItemBtn->setEnabled(false);
    signalRefreshCashTree();
}

void MainWindow::on_CachedTreeView_itemDoubleClicked(QTreeWidgetItem*, int)
{
    ui->SetValueItemBtn->setEnabled(true);
}
