#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "MatCalc.hpp"

#include <string>
#include <sstream>

MatCalc mc;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->verticalLayoutWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_lineEdit_returnPressed()
{
    std::string userInput = ui->lineEdit->text().toStdString();
    ui->textBrowser->append(QString::fromStdString("<< " + userInput));
    ui->lineEdit->clear();

    try
    {
        std::stringstream response (mc.input(userInput));
        std::string line;

        while(getline(response, line))
        {
            ui->textBrowser->append(QString::fromStdString(line));
        }
    }
    catch(std::exception & e)
    {
        ui->textBrowser->append(QString::fromStdString(e.what()));
    }
    catch(...)
    {
        ui->textBrowser->append("unknown error :(");
    }
}
