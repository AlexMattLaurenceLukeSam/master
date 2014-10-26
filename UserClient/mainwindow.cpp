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
//    if(loginMgr.login(ui->usernameLogin->text().toStdString(), ui->passwordLogin->text().toStdString()))
//        setUser(loginMgr.getCurrentUser()->getUserType());
}

void MainWindow::logout()
{
    noUser();
    loginMgr->logout();
}

void MainWindow::noUser()
{
    ui->tabWidget->clear();
    ui->tabWidget->addTab(ui->loginTab, "Login");
}

void MainWindow::setUser(/*UserType_t*/int userType)
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
    if(loginMgr->createAccount(ui->usernameLogin->text().toStdString(), ui->passwordLogin->text().toStdString()))
        setUser(loginMgr->getCurrentUser()->getUserType());
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

//void MainWindow::on_tabWidget_currentChanged(int index)
//{//change to current text or something
//    switch(index){
//    case 1:
//        populate_infoTabAuthor();
//        break;
//    case 2:
//        populate_infoTabChair();
//        break;
//    case 3:
//        populate_authorTab();
//        break;
//    case 4:
//        populate_reviewerTab();
//        break;
//    case 5:
//        populate_papersTab();
//        break;
//    case 6:
//        populate_usersTab();
//        break;
//    case 7:
//        populate_reviewTab();
//        break;
//    default:
//        break;


//    }
//}

//void MainWindow::populate_infoTabAuthor()
//{
//    User* user;
//    if(loginMgr.currentAuthor != nullptr)
//        user = dynamic_cast<User*>(currentAuthor);
//    if(loginMgr.currentReviewer != nullptr)
//        user = dynamic_cast<User*>(currentReviewer);

//    ui->username->setText(user->username);
//    ui->userid->setText(user->getUserId());
//    ui->name->setText(user->getName());
//    ui->email->setText(user->getEmail());
//    ui->organisation->setText(user->getOrganisation());
//    ui->phone->setText(user->getPhone());

//    if(loginMgr.currentAuthor != nullptr)
//        for(std::vector<std::string>::iterator it = loginMgr.currentAuthor->keywords.begin(); it != loginMgr.currentAuthor->keywords.end(); ++it)
//            ui->authKeyList->addItem(*it);
//    if(loginMgr.currentReviewer != nullptr)
//        for(std::vector<std::string>::iterator it = loginMgr.currentReviewer->keywords.begin(); it != loginMgr.currentReviewer->keywords.end(); ++it)
//            ui->authKeyList->addItem(*it);

//    ui->conferenceName->setText(loginMgr.activeConference->title);
//    ui->confTopic->setText(loginMgr.activeConference->topic);
//    ui->confLocation->setText(loginMgr.activeConference->location);
//    ui->confDesc->setText(loginMgr.activeConference->description);
//    for(std::vector<std::string>::iterator it = loginMgr.activeConference->keywords.begin(); it != loginMgr.activeConference->keywords.end(); ++it)
//        ui->confKeyList->addItem(*it);
//    ui->subDate->setText(loginMgr.activeConference->paperDeadline.toString());
//    ui->discDate->setText(loginMgr.activeConference->discussDeadline.toString());
//    ui->hReviewDate->setText(loginMgr.activeConference->reviewDeadlineHard.toString());
//    ui->sReviewDate->setText(loginMgr.activeConference->reviewDeadlineSoft.toString());
//    //ui->allocDate->setText(loginMgr.activeConference->);
//}

//void MainWindow::populate_infoTabChair()
//{
//    PCChair* user = loginMgr.currentPCChair;
//    Conference* conf = loginMgr.activeConference;

//    ui->username->setText(user->username);
//    ui->userid->setText(user->getUserId());
//    ui->name->setText(user->getName());
//    ui->email->setText(user->getEmail());
//    ui->organisation->setText(user->getOrganisation());
//    ui->phone->setText(user->getPhone());

//    ui->conferenceName->setText(conf->title);
//    ui->confTopic->setText(conf->topic);
//    ui->confLocation->setText(conf->location);
//    ui->confDesc->setText(conf->description);
//    for(std::vector<std::string>::iterator it = conf->keywords.begin(); it != conf->keywords.end(); ++it)
//        ui->confKeyList->addItem(*it);
//    ui->subDateEdit->date().setDate(conf->paperDeadline.day, conf->paperDeadline.month, conf->paperDeadline.year);
//    //ui->allocDateEdit->date().setDate(conf->paperDeadline.day, conf->paperDeadline.month, conf->paperDeadline.year);
//    ui->sReviewDateEdit->date().setDate(conf->reviewDeadlineSoft.day, conf->reviewDeadlineSoft.month, conf->reviewDeadlineSoft.year);
//    ui->hReviewDateEdit->date().setDate(conf->reviewDeadlineHard.day, conf->reviewDeadlineHard.month, conf->reviewDeadlineHard.year);
//    ui->discDateEdit->date().setDate(conf->discussDeadline.day, conf->discussDeadline.month, conf->discussDeadline.year);
//}

//void MainWindow::populate_authorTab()
//{
//    Author* user = loginMgr.currentAuthor;
//    std::vector<PaperSummary> papers = user->getOwnPapers();
//    std::vector<std::string> keys = user->getCurrentPaper().getKeywords();
//    std::vector<User> authors = user->getCurrentPaper().getAuthors();

//    for(std::vector<PaperSummary>::iterator it = papers.begin(); it != papers.end(); ++it)
//        ui->selectPaperAuthor->addItem(it->paperName);

//    ui->paperAbstract->setText(user->getCurrentPaper().getAbstract());
//    for(std::vector<std::string> it = keys.begin(); it != keys.end(); ++it)
//        ui->paperKeyListAuth->addItem(*it);

//    for(std::vector<User>::iterator it = authors.begin(); it != authors.end(); ++it){
//        int rows = ui->authorsTable->rowCount();
//        ui->authorsTable->insertRow(rows);
//        QTableWidgetItem* newItem = new QTableWidgetItem(it->getName());
//        ui->authorsTable->setItem(rows, 0, newItem);
//        newItem = new QTableWidgetItem(it->getName());
//        ui->authorsTable->setItem(rows, 1, newItem);
//        newItem = new QTableWidgetItem(it->getOrganisation());
//        ui->authorsTable->setItem(rows, 2, newItem);
//        newItem = new QTableWidgetItem(it->getPhone());
//        ui->authorsTable->setItem(rows, 3, newItem);
//    }

//    ui->filenameAuth->setText(user->getCurrentPaper().getFname());
//}

//void MainWindow::populate_papersTab()
//{

//}

//void MainWindow::populate_reviewerTab()
//{

//}

//void MainWindow::populate_reviewTab()
//{

//}

//void MainWindow::populate_usersTab()
//{

//}
