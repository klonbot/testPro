#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qtreewidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setValueItemBtnEnabled(bool en);
    void setCtrlBtnEnabled(bool en);
    void setCtrlBtnEnabled(void);

    QTreeWidget *getCachedTreeView();
    QTreeWidget *getDBTreeView();

Q_SIGNALS:
    void signalNewItem(void);
    void signalDeleteItem(void);
    void signalSetValueItem(void);
    void signalApply(void);
    void signalReset(void);
    void signalUploadToCash(void);
    void signalRefreshCashTree(void);
    void signalControlEdit(void);
    void signalControlAddDelete(void);

private slots:
    void on_NewItemBtn_clicked();

    void on_DeleteItemBtn_clicked();

    void on_SetValueItemBtn_clicked();

    void on_ApplyBtn_clicked();

    void on_ResetBtn_clicked();

    void on_UploadToCashBtn_clicked();

    void on_CachedTreeView_clicked(const QModelIndex &index);

    void on_CachedTreeView_itemChanged(QTreeWidgetItem *item, int column);

    void on_CachedTreeView_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

    void on_CachedTreeView_itemEntered(QTreeWidgetItem *item, int column);

    void on_CachedTreeView_itemClicked(QTreeWidgetItem *item, int column);

    void on_CachedTreeView_itemDoubleClicked(QTreeWidgetItem *item, int column);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
