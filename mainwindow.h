#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

Q_SIGNALS:
    void signalNewItem(void);
    void signalDeleteItem(void);
    void signalSetValueItem(void);
    void signalApply(void);
    void signalReset(void);
    void signalUploadToCash(void);

private slots:
    void on_NewItemBtn_clicked();

    void on_DeleteItemBtn_clicked();

    void on_SetValueItemBtn_clicked();

    void on_ApplyBtn_clicked();

    void on_ResetBtn_clicked();

    void on_UploadToCashBtn_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
