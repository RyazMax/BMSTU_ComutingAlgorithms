#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>

#include <algorithm>

#include "aproxymation.h"

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
    void on_swapButton_clicked();

    void on_solveButton_clicked();

    void fullfilTable();

    void on_action_triggered();

private:
    Ui::MainWindow *ui;
    CData data;
};

#endif // MAINWINDOW_H
