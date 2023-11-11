#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "graph.h"
#include "./ui_graph.h"

char proto_str[256] = {};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digits_buttons()));
    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digits_buttons()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digits_buttons()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits_buttons()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits_buttons()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits_buttons()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits_buttons()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits_buttons()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits_buttons()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits_buttons()));
    connect(ui->pushButton_add, SIGNAL(clicked()), this, SLOT(operators()));
    connect(ui->pushButton_sub, SIGNAL(clicked()), this, SLOT(operators()));
    connect(ui->pushButton_unar, SIGNAL(clicked()), this, SLOT(operators()));
    connect(ui->pushButton_mult, SIGNAL(clicked()), this, SLOT(operators()));
    connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(operators()));
    connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(operators()));
    connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(operators()));
    connect(ui->pushButton_open, SIGNAL(clicked()), this, SLOT(brackets()));
    connect(ui->pushButton_close, SIGNAL(clicked()), this, SLOT(brackets()));
    connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(func()));
    connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(func()));
    connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(func()));
    connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(func()));
    connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(func()));
    connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(func()));
    connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(func()));
    connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(func()));
    connect(ui->pushButton_sqr, SIGNAL(clicked()), this, SLOT(func()));
    connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(func()));
    connect(ui->pushButton_send, SIGNAL(clicked()), this, SLOT(calc()));
    connect(ui->pushButton_graph, SIGNAL(clicked()), this, SLOT(graph_calc()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

graph::graph(QWidget *parent) :
    QDialog(parent),
    uig(new Ui::graph)
{
    uig->setupUi(this);
 /*
    h = 0.1;
    xB = -3;
    xE = 3 + h;
    uig->widget->xAxis->setRange(-10, 10);
    uig->widget->yAxis->setRange(-10, 10);

    N = (xE - xB)/h + 2;


    for (X = xB; X <= xE; X += h) {
            x.push_back(X);
            y.push_back(X*X);

    }
    uig->widget->addGraph();
    uig->widget->graph(0)->addData(x, y);
    uig->widget->replot();
*/
}

graph::~graph()
{
    delete uig;
}

void MainWindow::digits_buttons()
{
    QPushButton *value =  (QPushButton *)sender();
    double full_number;
    QString result_str;

    full_number = (ui->inputField->text() + value->text()).toDouble();
    result_str = QString::number(full_number, 'g', 15);
    ui->inputField->setText(result_str);
}

void MainWindow::operators()
{
    QPushButton *value =  (QPushButton *)sender();

    double full_number;
    QString result_str;
    full_number = (ui->inputField->text()).toDouble();
    result_str = QString::number(full_number, 'g', 15);
    if (value->text() == "+/-") {
        full_number *= -1;
        result_str = QString::number(full_number, 'g', 15);
        ui->inputField->setText(result_str);
    } else if (ui->inputField->text() == 'x') {
        ui->resultField->setText(ui->resultField->text() + ui->inputField->text() + " " + value->text() + " ");
        ui->inputField->clear();
    } else {
            if (full_number < 0 && ui->resultField->text().size() > 0) {
               ui->inputField->setText("(" + result_str + ")");
            } else {
                ui->inputField->setText(result_str);
            }
            auto aboba = ui->resultField->text();
            if (aboba.size() > 2 && aboba[aboba.size() - 2] == ')') {
                ui->resultField->setText(ui->resultField->text() + value->text() + " ");
            } else {
                ui->resultField->setText(ui->resultField->text() + ui->inputField->text() + " " + value->text() + " ");
                ui->inputField->clear();
            }
        }
}

void MainWindow::func() {
    QPushButton *value =  (QPushButton *)sender();
    if (value->text() == "x") {
        auto aboba = ui->resultField->text();
        if (aboba.size() == 0 || aboba[aboba.size() - 2] != 'x') {
            ui->inputField->setText(value->text());
        }
    } else {
        ui->resultField->setText(ui->resultField->text() + " " + value->text() + "(");
    }
}

void MainWindow::brackets()
{
    auto aboba = ui->resultField->text();
    int o = 0, c = 0;
    for (int i = 0; i < aboba.size(); i++) {
        if (aboba[i] == '(') {
            o++;
        } else if (aboba[i] == ')') {
            c++;
        }
    }
    QPushButton *value =  (QPushButton *)sender();
    if (value->text() == "(")
        ui->resultField->setText(ui->resultField->text() + " " + value->text());
    else  if (value->text() == ')' && c < o){
        ui->resultField->setText(ui->resultField->text() + ui->inputField->text() + value->text() + " ");
        ui->inputField->clear();
    }
}

void MainWindow::on_pushButton_clear_clicked()
{
    ui->inputField->clear();
}


void MainWindow::on_pushButton_float_clicked()
{
    if (!(ui->inputField->text().contains('.')))
    ui->inputField->setText(ui->inputField->text() + '.');
}


void MainWindow::on_pushButton_all_clear_clicked()
{
    ui->inputField->clear();
    ui->resultField->clear();
}

void MainWindow::calc() {
    if (ui->resultField->text().size() > 0) {
        QString result_str;
        ui->resultField->setText(ui->resultField->text() + ui->inputField->text());
        ui->inputField->clear();
        char *str = ui->resultField->text().toLocal8Bit().data();
        char input_str[256] = {0};
        for (int i = 0; i < 255 && *str; i++) {
            input_str[i] = *str;
            proto_str[i] = *str;
            str++;
        }
        char polish[256] = {0};
        string_format(input_str, ui->x_value->text().toDouble());
        to_polish(input_str, polish);
        double res = 0;
        if (calc_comp(polish, &res)) {
            result_str = QString::number(0, 'g', 15);
        } else {
            result_str = QString::number(res, 'g', 15);
        }
        ui->inputField->setText(result_str);
        ui->resultField->clear();
        ui->pushButton_graph->setEnabled(true);
    }
}

void clearStr(char *s) {
    for (int i = 0; i < 255; i++) {
        s[i] = '\0';
    }
}

void MainWindow::graph_calc() {
    window = new graph(this);
    window->show();
    x.clear();
    y.clear();
    h = 0.2;
    xB = ui->x_value->text().toDouble();
    xE = ui->x_value->text().toDouble() + h;
    if (xB == 0) {
        xB = -6;
        xE = xB * - 1 + h;
    }
    if (xB > 0) {
        xB *= -1;
    } else {
        xE *= -1;
    }
    window->uig->widget->xAxis->setRange(-40, 40);
    window->uig->widget->yAxis->setRange(-40, 40);
    N = (xE - xB)/h + 2;

    char input_str[256] = {0};
    char polish[256] = {0};
    double res = 0;
    for (X = xB; X <= xE; X += h) {
            x.push_back(X);

            strcpy(input_str, proto_str);

            string_format(input_str, X);
            to_polish(input_str, polish);
            calc_comp(polish, &res);
            clearStr(polish);
            y.push_back(res);
            res = 0;
            clearStr(input_str);
    }
    window->uig->widget->addGraph();
    window->uig->widget->graph(0)->addData(x, y);
    window->uig->widget->replot();
}

void graph::on_pushButton_clicked()
{
    uig->widget->clearGraphs();
    x2.clear();
    y2.clear();
    h2 = uig->step->text().toDouble();

    xB2 = uig->xBegin->text().toDouble();
    xE2 =  uig->xEnd->text().toDouble() + h2;
    uig->widget->xAxis->setRange(-20, 20);
    uig->widget->yAxis->setRange(-20, 20);
    N2 = (xE2 - xB2)/h2 + 2;

    char input_str[256] = {0};
    char polish[256] = {0};
    double res = 0;
    for (X2 = xB2; X2 <= xE2; X2 += h2) {
            x2.push_back(X2);

            strcpy(input_str, proto_str);

            string_format(input_str, X2);
            to_polish(input_str, polish);
            calc_comp(polish, &res);
            y2.push_back(res);
            res = 0;
            for (int i = 0; i < 255; i++) {
                input_str[i] = '\0';
                polish[i] = '\0';
            }

    }
    uig->widget->addGraph();
    uig->widget->graph(0)->addData(x2, y2);
    uig->widget->replot();
}
