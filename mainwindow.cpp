#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QStandardItemModel>

#include <QDebug>

#include "include/logics.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->btn_browse, SIGNAL(clicked()), this, SLOT(setPath()));
    connect(ui->btn_load, SIGNAL(clicked()), this, SLOT(showRegionFields()));
    connect(ui->btn_calculate, SIGNAL(clicked()), this, SLOT(showCalculationResults()));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setPath() {
    QString file_path = QFileDialog::getOpenFileName(this, "../lw-2/resource", "../lw-2/resource", tr("CSV tables (*.csv)"));
    ui->ln_path->setText(file_path);
}


void MainWindow::showRegionFields() {
    string path = ui->ln_path->text().toStdString();
    string region = ui->ln_region->text().toStdString();
    int init_year = ui->ln_init_year->text().toInt() == 0 ? -1 : ui->ln_init_year->text().toInt();
    int final_year = ui->ln_final_year->text().toInt() == 0 ? -1 : ui->ln_final_year->text().toInt();
    fields = readCSV(path, region, init_year, final_year);

    QStandardItemModel *model = new QStandardItemModel;

    for (size_t i = 0; i < fields.size(); i++) {
        for (size_t j = 0; j < fields.at(i).size(); j++) {
            model->setItem(i, j, new QStandardItem(QString::fromStdString(fields.at(i).at(j))));
        }
    }

    ui->tbl_found->setModel(model);
}

void MainWindow::showCalculationResults()
{
    int column = ui->ln_column->text().toInt();
    QStandardItemModel *model = new QStandardItemModel;

    model->setItem(0, 0, new QStandardItem("Minimum"));
    model->setItem(1, 0, new QStandardItem("Maximum"));
    model->setItem(2, 0, new QStandardItem("Median"));
    model->setItem(0, 1, new QStandardItem(QString::number(getMinimum(column))));
    model->setItem(1, 1, new QStandardItem(QString::number(getMaximum(column))));
    model->setItem(2, 1, new QStandardItem(QString::number(getMedian(column))));

    ui->tbl_res->setModel(model);
}

double MainWindow::getMinimum(int column)
{
    vector<double> col;
    for (size_t i = 0; i < fields.size(); i++) {
        col.push_back(stold(fields.at(i).at(column - 1)));
    }
    sort(col.begin(), col.end());
    return col[0];
}

double MainWindow::getMaximum(int column)
{
    vector<double> col;
    for (size_t i = 0; i < fields.size(); i++) {
        col.push_back(stold(fields.at(i).at(column - 1)));
    }
    sort(col.begin(), col.end());
    return col[col.size() - 1];
}

double MainWindow::getMedian(int column)
{
    vector<double> col;
    for (size_t i = 0; i < fields.size(); i++) {
        col.push_back(stold(fields.at(i).at(column - 1)));
    }
    sort(col.begin(), col.end());
    double result;
    if (col.size() % 2 == 1) {
        result = col[col.size() / 2];
    } else {
        result = (col[col.size() / 2] + col[col.size() / 2 - 1]) / 2;
    }
    return result;
}
