#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

#include "include/logics.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->btn_browse, SIGNAL(clicked()), this, SLOT(setPath()));
    connect(ui->btn_load, SIGNAL(clicked()), this, SLOT(showRegionFields()));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setPath() {
    QString file_path = QFileDialog::getOpenFileName(this, "../lw-2/resource", "../lw-2/resource", tr("CSV tables (*.csv)"));
    ui->ln_path->setText(file_path);
}


void MainWindow::showRegionFields() {
//    vector<vector<string>> fields = readCSV(ui->ln_path->text().toStdString(), ui->ln_region->text().toStdString());
}
