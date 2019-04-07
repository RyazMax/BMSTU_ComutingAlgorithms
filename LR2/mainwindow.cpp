#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aproxymation.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    data()
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_solveButton_clicked()
{
    bool isOk = true;
    double x = ui->xEdit->text().toDouble(&isOk);

    if (!isOk) {
        QMessageBox::warning(this, "Неверные данные", "Вы оставили одно из полей пустым или ввели неверные данные");
    } else if (this->data.GetSize() == 0) {
        QMessageBox::warning(this, "Не загружены данные", "Необходимо загрузить данные");
        isOk = false;
    }
    if (this->data.GetSize() < 2) {
        QMessageBox::warning(this, "Мало точек", "Необходимо 2 или больше точки");
        isOk = false;
    }
    if (!isOk) return;
    double a, b, c, d;
    int line;
    ui->answerLabel->setText("Y(X) = " + QString::number(solve(&this->data, x, a, b, c, d, line), 'e', 4));
    ui->tableWidget->clearSelection();
    ui->tableWidget->selectRow(line);
    ui->polLabel->setText("P(X)=" + QString::number(a,'f',1) + "+" + QString::number(b,'f',1) + "(x - xi)+" + QString::number(c,'f',1) + "(x-xi)^2+" + QString::number(d,'f',1) + "(x-xi)^3");
}

void MainWindow::fullfilTable()
{
    int tableWidth = ui->tableWidget->width();
    int len = this->data.GetSize();
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setRowCount(len);
    ui->tableWidget->setColumnWidth(0, tableWidth / 2);
    ui->tableWidget->setColumnWidth(1, tableWidth  / 2);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList{"X", "Y"});
    for (int i = 0; i < len; ++i) {
        double_pair line = this->data.GetLine(i);
        QTableWidgetItem *leftItem = new QTableWidgetItem(QString::number(line.first));
        QTableWidgetItem *rightItem = new QTableWidgetItem(QString::number(line.second));
        ui->tableWidget->setItem(i, 0, leftItem);
        ui->tableWidget->setItem(i, 1, rightItem);
    }
}

void MainWindow::on_action_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open file"), ".", tr("*.txt"));
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {

        return;
    }

    QTextStream in(&file);
    std::vector<double_pair> inputData;
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList list = line.split(";");
        inputData.push_back(std::make_pair(list.at(0).toDouble(), list.at(1).toDouble()));
    }
    this->data = CData(inputData);
    this->data.Sort();
    fullfilTable();

    file.close();
}

void MainWindow::showUsedData(int left, int right) {
    ui->tableWidget->clearSelection();
    for (int i = left; i <= right; ++i) {
        ui->tableWidget->selectRow(i);
    }
}

void MainWindow::on_pushButton_clicked()
{
    this->data.Swap();
    this->data.Sort();
    fullfilTable();

}
