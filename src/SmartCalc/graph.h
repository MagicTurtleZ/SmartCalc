#ifndef GRAPH_H
#define GRAPH_H

#include <QDialog>
#include <QVector>

namespace Ui {
class graph;
}

class graph : public QDialog
{
    Q_OBJECT

public:
    Ui::graph *uig;
    explicit graph(QWidget *parent = nullptr);
    double xB2, xE2, h2, X2;
    int N2;
    QVector<double> x2, y2;
    ~graph();

private slots:
    void on_pushButton_clicked();

private:

};

#endif // GRAPH_H
