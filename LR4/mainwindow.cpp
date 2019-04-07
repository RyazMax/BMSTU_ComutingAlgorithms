#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setup_table();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QGraphicsView *view = new QGraphicsView();
    view->setGeometry(this->geometry());

    QGraphicsScene *scene = new QGraphicsScene(view);
    plot(*scene, this->data, 1);
    view->setScene(scene);
    view->show();
}

void MainWindow::setup_table()
{
    int columns = 3;
    ui->tableWidget->setColumnCount(columns);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList{"X", "Y", "W"});
    int width = ui->tableWidget->width() / columns - 1;
    for (int i = 0; i < columns; ++i) {
        ui->tableWidget->setColumnWidth(i, width);
    }
}

void MainWindow::on_action_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Открыть файл");
    this->data = DataReader::readFromFile(fileName);
    QMessageBox::information(this, "Информация", "Здесь будет чтение из файла");
}

void MainWindow::plot(QGraphicsScene &scene, data_t &data, int type)
{
    for (int i = 0; i < data.x.size() - 1; ++i) {
        if (type) {
            scene.addLine(data.x[i], data.y[i], data.x[i + 1], data.y[i + 1]);
        }
        else {
            scene.addEllipse(data.x[i], data.y[i], 2, 2);
        }
    }
}
