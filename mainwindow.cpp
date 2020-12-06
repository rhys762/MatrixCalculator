#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "MatCalc.hpp"
#include "MatCalcExcep.hpp"

#include <string>

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
    ui->textBrowser->insertHtml(QString::fromStdString(">>" + userInput + "<br>"));
    ui->lineEdit->clear();

    try
    {   
        ui->textBrowser->insertHtml(QString::fromStdString(mc.input(userInput)));
    }
    catch(MatCalcExcep & e)
    {
        ui->textBrowser->insertHtml(QString::fromStdString(e.what()));
    }
    catch(...)
    {
        ui->textBrowser->insertHtml("unknown error :(<br>");
    }
}
