#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setUser(0);
    ui->passwordLogin->setEchoMode(QLineEdit::Password);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setUser(int userType)
{
    switch(userType)
    {
    case 0://no user
        ui->tabWidget->clear();
        ui->tabWidget->addTab(ui->loginTab, "Login");
        break;
    case 1://pcchair
        ui->tableWidget->clear();
        ui->tabWidget->addTab(ui->infoTabChair, "Information");
        ui->tabWidget->addTab(ui->usersTab, "User Management");
        ui->tabWidget->addTab(ui->papersTab, "Paper Management");
        ui->tabWidget->removeTab(0);
        break;
    case 2://reviewer
        ui->tableWidget->clear();
        ui->tabWidget->addTab(ui->infoTabAuthor, "Information");
        ui->tabWidget->addTab(ui->authorTab, "Author");
        ui->tabWidget->addTab(ui->reviewerTab, "Reviewer");
        ui->tabWidget->removeTab(0);
        break;
    case 3://author
        ui->tabWidget->clear();
        ui->tabWidget->addTab(ui->infoTabAuthor, "Information");
        ui->tabWidget->addTab(ui->authorTab, "Author");
        //ui->tabWidget->removeTab(0);
        break;
    }

}

void MainWindow::on_login_clicked()
{
    if(username == "PCChair" && password == "admin")
        setUser(1);
    else if(username == "Reviewer" && password == "user")
        setUser(2);
    else if(username == "Author" && password == "user")
        setUser(3);
}

void MainWindow::on_quit_clicked()
{
    qApp->quit();
}

void MainWindow::on_usernameLogin_editingFinished()
{
    username = ui->usernameLogin->text();
}

void MainWindow::on_passwordLogin_editingFinished()
{
    password = ui->passwordLogin->text();
}

void MainWindow::on_logout_clicked()
{
    setUser(0);
}

void MainWindow::on_logout_2_clicked()
{
    setUser(0);
}
