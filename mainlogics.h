#ifndef MAILLOGICS_H
#define MAILLOGICS_H

#include <QtCore>

#include "mainwindow.h"
#include "cache.h"

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
    Cache cache;

    void initTestTree(void);
};

#endif // MAILLOGICS_H
