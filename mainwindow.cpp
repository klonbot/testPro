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
