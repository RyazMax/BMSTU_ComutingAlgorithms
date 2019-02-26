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

void MainWindow::on_swapButton_clicked()
{
    QString firstColumn = ui->first_column_label->text();
    ui->first_column_label->setText(ui->second_column_label->text());
    ui->second_column_label->setText(firstColumn);
}

void MainWindow::on_solveButton_clicked()
{
    ui->answerLabel->setText("Y(X) = " + ui->xEdit->text());
    //ui->answerLabel->setText(solve(&CData(), 0, ui->xEdit->text()));
}

void MainWindow::fullfilTable()
{
    int len = this->data.GetSize();
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setRowCount(len);
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
    fullfilTable();

    file.close();
}
