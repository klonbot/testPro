#include "mainwindow.h"
#include <QApplication>
#include "database.h"
#include "mainlogics.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Database db;

    MainWindow w;
    MainLogics mainLogics(w);
    w.show();

    return a.exec();
}
