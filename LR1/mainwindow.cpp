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
    int n = ui->nPolynomEdit->text().toInt(&isOk);
    double x = ui->xEdit->text().toDouble(&isOk);

    if (n < 1) isOk = false;
    if (!isOk) {
        QMessageBox::warning(this, "Неверные данные", "Вы оставили одно из полей пустым или ввели неверные данные");
    } else if (this->data.GetSize() == 0) {
        QMessageBox::warning(this, "Не загружены данные", "Необходимо загрузить данные");
        isOk = false;
    } else if (this->data.GetSize() < n + 1) {
        QMessageBox::warning(this, "Неверное количество точек", "Недостаточное количество точек для введеного порядка");
        isOk = false;
    }
    if (!isOk) return;
    int left, right;
    ui->answerLabel->setText("Y(X) = " + QString::number(solve(&this->data, n, x, left, right), 'e', 4));
    showUsedData(left, right);
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
