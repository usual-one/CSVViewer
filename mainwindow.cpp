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
    pair<int, int> years = {ui->ln_init_year->text().toInt(), ui->ln_final_year->text().toInt()};
    pair<vector<string>, vector<vector<string>>> table = readCSV(path, region, years);
    headers = table.first;
    fields = table.second;

    QStandardItemModel *model = new QStandardItemModel;

    QStringList horizontal_headers;
    for (auto it = headers.begin(); it != headers.end(); it++) {
        horizontal_headers.append(QString::fromStdString(*it));
    }
    model->setHorizontalHeaderLabels(horizontal_headers);

    for (size_t i = 0; i < fields.size(); i++) {
        for (size_t j = 0; j < fields.at(i).size(); j++) {
            model->setItem(i, j, new QStandardItem(QString::fromStdString(fields.at(i).at(j))));
        }
    }

    ui->tbl_found->setModel(model);
}

void MainWindow::showCalculationResults()
{
    string column = ui->ln_column->text().toStdString();

    QStandardItemModel *model = new QStandardItemModel;
    model->setHorizontalHeaderLabels({"Metric", "Value"});
    model->setItem(0, 0, new QStandardItem("Minimum"));
    model->setItem(1, 0, new QStandardItem("Maximum"));
    model->setItem(2, 0, new QStandardItem("Median"));
    model->setItem(0, 1, new QStandardItem(QString::number(getMetrics(fields, headers, column, minimum))));
    model->setItem(1, 1, new QStandardItem(QString::number(getMetrics(fields, headers, column, maximum))));
    model->setItem(2, 1, new QStandardItem(QString::number(getMetrics(fields, headers, column, median))));

    ui->tbl_res->setModel(model);
}
