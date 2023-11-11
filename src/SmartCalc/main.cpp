#include "mainwindow.h"

#include <QApplication>
#include <QLabel>
#include <QAction>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
