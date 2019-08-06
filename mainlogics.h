#ifndef MAILLOGICS_H
#define MAILLOGICS_H

#include <QtCore>

#include "mainwindow.h"

class MainLogics : public QObject
{
    Q_OBJECT

public:
    MainLogics(QObject *parent = 0);

    void CreateSignals(MainWindow &w);

private slots:
    void slotNewItem(void);
    void slotDeleteItem(void);
    void slotSetValueItem(void);
    void slotApply(void);
    void slotReset(void);
    void slotUploadToCash(void);

private:

    void initTree(void);
};

#endif // MAILLOGICS_H
