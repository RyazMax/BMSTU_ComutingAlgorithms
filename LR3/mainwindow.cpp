#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    double xFrom = ui->xFromEdit->text().toDouble();
    double yFrom = ui->yFromEdit->text().toDouble();
    double xTo = ui->xToEdit->text().toDouble();
    double yTo = ui->yToEdit->text().toDouble();
    double xStep = ui->xStepEdit->text().toDouble();
    double yStep = ui->yStepEdit->text().toDouble();

    data_t newData = generate(xFrom, yFrom, xTo, yTo, xStep, yStep);
    this->isGenerated = true;
    this->data =newData;
    showTable();
}

void MainWindow::showTable()
{
    QStringList xList;
    QStringList yList;

    for (int i = 0; i < this->data.size(); ++i) {
        xList.push_back(QString::number(data[i][0].x, 'f', 2));
    }
    xList.push_back("X");
    for (int i = 0; i < this->data[0].size(); ++i) {
        yList.push_back(QString::number(data[0][i].y, 'f', 2));
    }
    yList.push_back("Y");

    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(this->data.size() + 1);
    ui->tableWidget->setColumnCount(this->data[0].size() + 1);
    ui->tableWidget->setHorizontalHeaderLabels(yList);
    ui->tableWidget->setVerticalHeaderLabels(xList);


    for (int i = 0; i < this->data.size(); ++i) {
        for (int j = 0; j < this->data[i].size(); ++j) {
            ui->tableWidget->setItem(i, j, new QTableWidgetItem(QString::number(this->data[i][j].z, 'f', 2)));
        }
    }
}

void MainWindow::on_solveButton_clicked()
{
    double xFind = ui->xFindEdit->text().toDouble();
    double yFind = ui->yFindEdit->text().toDouble();
    int nx = ui->nxEdit->text().toInt();
    int ny = ui->nyEdit->text().toInt();

    if (!this->isGenerated) {
        QMessageBox::warning(this, "Предупреждение", "Сначала сгенерируйте таблицу");
        return;
    }

    if (nx + 1 > this->data.size()) {
        QMessageBox::warning(this, "Предупреждение", "Слишком мало точек по оси X");
        return;
    }

    if (ny + 1 > this->data[0].size()) {
        QMessageBox::warning(this, "Предупреждение", "Слишком мало точек по оси Y");
        return;
    }

    // solve

    int r1, c1, r2, c2;
    double z = solve_all(this->data, xFind, yFind, nx, ny, r1, c1, r2, c2);
    selectNodes(r1, c1, r2, c2);
    ui->label->setText("Z(X,Y) =  " + QString::number(z, 'e', 3));
}

void MainWindow::selectNodes(int r1, int c1, int r2, int c2)
{
    ui->tableWidget->clearSelection();
    for (int i = r1; i <= r2; ++i)
    {
        for (int j = c1; j <= c2; ++j)
        {
            ui->tableWidget->item(i, j)->setSelected(true);
        }
    }
}
