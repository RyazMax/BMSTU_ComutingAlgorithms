#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

#include <vector>
#include <utility>
#include <iostream>

#include "sollution.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_solveButton_clicked();

    void showTable();
    void selectNodes(int r1, int c1, int r2, int c2);

private:
    Ui::MainWindow *ui;
    bool isGenerated;
    data_t data;
};

#endif // MAINWINDOW_H
