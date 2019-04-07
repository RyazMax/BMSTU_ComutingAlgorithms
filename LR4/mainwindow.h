#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QGraphicsView>

#include "datareader.h"

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
    void setup_table();
    void on_pushButton_clicked();

    void on_action_triggered();
    void plot(QGraphicsScene &scene, data_t &data, int type = 0);

private:
    Ui::MainWindow *ui;
    data_t data;
};

#endif // MAINWINDOW_H
