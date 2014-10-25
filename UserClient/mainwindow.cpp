#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    noUser();
    ui->passwordLogin->setEchoMode(QLineEdit::Password);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::login()
{
    if(loginMgr.login(ui->usernameLogin->text().toStdString(), ui->passwordLogin->text().toStdString()))
        setUser(loginMgr.currentUser->getUserType());
}

void MainWindow::logout()
{
    noUser();
    loginMgr.logout();
}

void MainWindow::noUser()
{
    ui->tabWidget->clear();
    ui->tabWidget->addTab(ui->loginTab, "Login");
}

void MainWindow::setUser(UserType_t userType)
{
    switch(userType)
    {
    case AUTHOR://author
        ui->tabWidget->clear();
        ui->tabWidget->addTab(ui->infoTabAuthor, "Information");
        ui->tabWidget->addTab(ui->authorTab, "Author");
        //ui->tabWidget->removeTab(0);
        break;
    case REVIEWER://reviewer
        ui->tableWidget->clear();
        ui->tabWidget->addTab(ui->infoTabAuthor, "Information");
        ui->tabWidget->addTab(ui->authorTab, "Author");
        ui->tabWidget->addTab(ui->reviewerTab, "Reviewer");
        ui->tabWidget->removeTab(0);
        break;
    case PCCHAIR://pcchair
        ui->tableWidget->clear();
        ui->tabWidget->addTab(ui->infoTabChair, "Information");
        ui->tabWidget->addTab(ui->usersTab, "User Management");
        ui->tabWidget->addTab(ui->papersTab, "Paper Management");
        ui->tabWidget->removeTab(0);
        break;
    }

}

void MainWindow::on_login_clicked()
{
    login();
}

void MainWindow::on_quit_clicked()
{
    qApp->quit();
}

void MainWindow::on_logout_clicked()
{
    logout();
}

void MainWindow::on_logout_2_clicked()
{
    logout();
}

void MainWindow::on_passwordLogin_returnPressed()
{
    login();
}

void MainWindow::on_createAccount_clicked()
{
    if(loginMgr.createAccount(ui->usernameLogin->text().toStdString(), ui->passwordLogin->text().toStdString()))
        setUser(loginMgr.currentUser->getUserType());
}

void MainWindow::on_apply_clicked()
{
    //send user details to server
}

void MainWindow::on_apply_2_clicked()
{
    //send user details to server
}

void MainWindow::on_addConfKey_clicked()
{
    ui->confKeyList->addItem(ui->confKeyEntry->text());
}

void MainWindow::on_rmvConfKey_clicked()
{
    //for(int i = 0; i < ui->confKeyList->selectedItems().size(); i++)
    //    ui->confKeyList->(ui->confKeyList->selectedItems().at(i));
    delete ui->confKeyList->currentItem();
}

void MainWindow::on_addAuthor_clicked()
{
    int row = ui->authorsTable->rowCount();
    ui->authorsTable->insertRow(row);
//    QTableWidgetItem item[4];
//    item[0].setText(ui->newAuthorName->text());
//    item[1].setText(ui->newAuthorEmail->text());
//    item[2].setText(ui->newAuthorOrg->text());
//    item[3].setText(ui->newAuthorPhone->text());
//    ui->authorsTable->setItem(row, 0 , &item[0]);
//    ui->authorsTable->setItem(row, 1 , &item[1]);
//    ui->authorsTable->setItem(row, 2 , &item[2]);
//    ui->authorsTable->setItem(row, 3 , &item[3]);
}

void MainWindow::on_rmvAuthor_clicked()
{
    ui->authorsTable->removeRow(ui->authorsTable->currentRow());
    ui->authorsTable->clearSelection();
}

void MainWindow::on_addPaperKey_clicked()
{
    ui->paperKeyListAuth->addItem(ui->paperKeyEntry->text());
}

void MainWindow::on_rmvPaperKey_clicked()
{
    delete ui->paperKeyListAuth->currentItem();
}

void MainWindow::on_addAuthKey_clicked()
{
    ui->authKeyList->addItem(ui->authKeyEntry->text());
}

void MainWindow::on_rmvAuthKey_clicked()
{
    delete ui->authKeyList->currentItem();
}

void MainWindow::on_selectPaperAuthor_activated(int index)
{

}

void MainWindow::on_selectPaperAuthor_currentTextChanged(const QString &arg1)
{
    ui->selectPaperAuthor->setItemText(ui->selectPaperAuthor->currentIndex(), ui->selectPaperAuthor->currentText());
    if(ui->selectPaperAuthor->findText("*NEW*") == -1)
        ui->selectPaperAuthor->addItem("*NEW*");
}
