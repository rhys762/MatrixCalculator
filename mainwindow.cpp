#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "MatCalc.hpp"
#include "MatCalcExcep.hpp"

#include <QFileDialog>
#include <string>
#include <iostream>//debug
#include <QString>

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

void MainWindow::on_actionSave_Workspace_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save Workspace As");
    mc.saveWorkspace(filename.toStdString());
}

void MainWindow::on_actionOpen_Workspace_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open Workspace");
    mc.openWorkspace(filename.toStdString());
}
