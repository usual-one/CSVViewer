#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->btn_browse, SIGNAL(clicked()), this, SLOT(setPath()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setPath()
{
    ui->ln_path->setText(QFileDialog::getOpenFileName(this, "/home/", "/home/usual-alex/"));
}


