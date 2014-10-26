#include "mainwindow.hpp"
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

void MainWindow::on_addConf_clicked()
{
    ui->confTable->insertRow(ui->confTable->rowCount());
}

void MainWindow::on_rmvConf_clicked()
{
    ui->confTable->removeRow(ui->confTable->currentRow());
}

void MainWindow::on_addUserKey_clicked()
{
//    NOTE: error: ‘class Ui::MainWindow’ has no member named ‘userKeyEntry’
//    ui->userKeyList->addItem(ui->userKeyEntry->text());
}

void MainWindow::on_rmvUserKey_clicked()
{
    delete ui->userKeyList->currentItem();
}

void MainWindow::on_quit_2_clicked()
{
    qApp->quit();
}
