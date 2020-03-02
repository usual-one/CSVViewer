#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <string>
#include <vector>

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
    void setPath();

    void showRegionFields();

    void showCalculationResults();

private:
    Ui::MainWindow *ui;

    std::vector<std::vector<std::string>> fields;

    std::vector<std::string> headers;
};
#endif // MAINWINDOW_H
