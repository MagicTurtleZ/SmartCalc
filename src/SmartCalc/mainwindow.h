#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string.h>

#include <QByteArray>
#include <QString>
#include <QVector>
#include "graph.h"

extern "C" {
    #include "../back.h"
}
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void digits_buttons();

    void operators();

    void on_pushButton_clear_clicked();

    void on_pushButton_float_clicked();

    void on_pushButton_all_clear_clicked();

    void brackets();

    void func();

    void calc();

    void graph_calc();

private:
    Ui::MainWindow *ui;
    graph *window;
    double xB, xE, h, X;
    int N;
    QVector<double> x, y;
};
#endif // MAINWINDOW_H
