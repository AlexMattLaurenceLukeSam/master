#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "../DataAll/Review.hpp"
//can probably be rid of the above review include

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
    //no response needed from server
}

void MainWindow::on_applyChair_clicked()
{
    //send user details to server
    //send conference details to  server
    //no response needed from server
}

void MainWindow::on_addConfKey_clicked()
{
    ui->confKeyList->addItem(ui->confKeyEntry->text());
}

void MainWindow::on_rmvConfKey_clicked()
{
    delete ui->confKeyList->currentItem();
}

void MainWindow::on_addAuthor_clicked()
{
    int row = ui->authorsTable->rowCount();
    ui->authorsTable->insertRow(row);
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

void MainWindow::on_selectPaperAuthor_activated(int /*index*/)
{

}

void MainWindow::on_selectPaperAuthor_currentTextChanged(const QString &/*arg1*/)
{
    ui->selectPaperAuthor->setItemText(ui->selectPaperAuthor->currentIndex(), ui->selectPaperAuthor->currentText());
    if(ui->selectPaperAuthor->findText("*NEW*") == -1)
        ui->selectPaperAuthor->addItem("*NEW*");
}

void MainWindow::on_tabWidget_currentChanged(int index)
{//change to current text or something
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
}

void MainWindow::populate_infoTabAuthor()
{
    User* user;
    if(loginMgr.currentAuthor != nullptr)
        user = dynamic_cast<User*>(currentAuthor);
    if(loginMgr.currentReviewer != nullptr)
        user = dynamic_cast<User*>(currentReviewer);

    ui->username->setText(user->username);
    ui->userid->setText(user->getUserId());
    ui->name->setText(user->getName());
    ui->email->setText(user->getEmail());
    ui->organisation->setText(user->getOrganisation());
    ui->phone->setText(user->getPhone());

    if(loginMgr.currentAuthor != nullptr)
        for(std::vector<std::string>::iterator it = loginMgr.currentAuthor->keywords.begin(); it != loginMgr.currentAuthor->keywords.end(); ++it)
            ui->authKeyList->addItem(*it);
    if(loginMgr.currentReviewer != nullptr)
        for(std::vector<std::string>::iterator it = loginMgr.currentReviewer->keywords.begin(); it != loginMgr.currentReviewer->keywords.end(); ++it)
            ui->authKeyList->addItem(*it);

    ui->conferenceName->setText(loginMgr.activeConference->title);
    ui->confTopic->setText(loginMgr.activeConference->topic);
    ui->confLocation->setText(loginMgr.activeConference->location);
    ui->confDesc->setText(loginMgr.activeConference->description);
    for(std::vector<std::string>::iterator it = loginMgr.activeConference->keywords.begin(); it != loginMgr.activeConference->keywords.end(); ++it)
        ui->confKeyList->addItem(*it);
    ui->subDate->setText(loginMgr.activeConference->paperDeadline.toString());
    ui->discDate->setText(loginMgr.activeConference->discussDeadline.toString());
    ui->hReviewDate->setText(loginMgr.activeConference->reviewDeadlineHard.toString());
    ui->sReviewDate->setText(loginMgr.activeConference->reviewDeadlineSoft.toString());
    //ui->allocDate->setText(loginMgr.activeConference->);
}

void MainWindow::populate_infoTabChair()
{
    PCChair* user = loginMgr.currentPCChair;
    Conference* conf = loginMgr.activeConference;

    ui->username->setText(user->username);
    ui->userid->setText(user->getUserId());
    ui->name->setText(user->getName());
    ui->email->setText(user->getEmail());
    ui->organisation->setText(user->getOrganisation());
    ui->phone->setText(user->getPhone());

    ui->conferenceName->setText(conf->title);
    ui->confTopic->setText(conf->topic);
    ui->confLocation->setText(conf->location);
    ui->confDesc->setText(conf->description);
    for(std::vector<std::string>::iterator it = conf->keywords.begin(); it != conf->keywords.end(); ++it)
        ui->confKeyList->addItem(*it);
    ui->subDateEdit->date().setDate(conf->paperDeadline.day, conf->paperDeadline.month, conf->paperDeadline.year);
    //ui->allocDateEdit->date().setDate(conf->paperDeadline.day, conf->paperDeadline.month, conf->paperDeadline.year);
    ui->sReviewDateEdit->date().setDate(conf->reviewDeadlineSoft.day, conf->reviewDeadlineSoft.month, conf->reviewDeadlineSoft.year);
    ui->hReviewDateEdit->date().setDate(conf->reviewDeadlineHard.day, conf->reviewDeadlineHard.month, conf->reviewDeadlineHard.year);
    ui->discDateEdit->date().setDate(conf->discussDeadline.day, conf->discussDeadline.month, conf->discussDeadline.year);
}

void MainWindow::populate_authorTab()
{
    Author* user = loginMgr.currentAuthor;
    std::vector<PaperSummary> papers = user->getOwnPapers();
    std::vector<std::string> keys = user->getCurrentPaper().getKeywords();
    std::vector<User> authors = user->getCurrentPaper().getAuthors();

    for(std::vector<PaperSummary>::iterator it = papers.begin(); it != papers.end(); ++it)
        ui->selectPaperAuthor->addItem(it->paperName);

    ui->paperAbstract->setText(user->getCurrentPaper().getAbstract());
    for(std::vector<std::string> it = keys.begin(); it != keys.end(); ++it)
        ui->paperKeyListAuth->addItem(*it);

    for(std::vector<User>::iterator it = authors.begin(); it != authors.end(); ++it){
        int rows = ui->authorsTable->rowCount();
        ui->authorsTable->insertRow(rows);
        QTableWidgetItem* newItem = new QTableWidgetItem(it->getName());
        ui->authorsTable->setItem(rows, 0, newItem);
        newItem = new QTableWidgetItem(it->getName());
        ui->authorsTable->setItem(rows, 1, newItem);
        newItem = new QTableWidgetItem(it->getOrganisation());
        ui->authorsTable->setItem(rows, 2, newItem);
        newItem = new QTableWidgetItem(it->getPhone());
        ui->authorsTable->setItem(rows, 3, newItem);
    }

    ui->filenameAuth->setText(user->getCurrentPaper().getFname());
}

void MainWindow::populate_papersTab()
{

}

void MainWindow::populate_reviewerTab()
{

}

void MainWindow::populate_reviewTab()
{

}

void MainWindow::populate_usersTab()
{


}

void MainWindow::on_submit_clicked()
{
    //paper is the getCurrentPaper()

    //send paper (as in the paper details) as well as the actual paper pdf to server
    //no response from server
}

void MainWindow::on_submitBid_clicked()
{
    int bid = ui->selectBid->currentText().toInt();
    int userId = loginMgr->getCurrentUser()->getUserID();
    int paperId;
    //paperId = user->getCurrentPaper();

    //send users bid on a paper to the server
    //no response from server
}

void MainWindow::downloadPaper(int paperId)
{
    int paperId = loginMgr->getCurrentUser()->getCurrentPaper().paperID;

    //send request to server for paper pdf along with the paper id of the wanted paper
    //hopes to receive the pdf

    //after receiving pdf will just create the file in the working directory blah blah blah ill do that
}

void MainWindow::on_downloadReviewer_clicked()
{
    downloadPaper();
}

void MainWindow::on_downloadChair_clicked()
{
    downloadPaper();
}

void MainWindow::on_downloadReview_clicked()
{
    downloadPaper();
}

void MainWindow::on_submitPosts_clicked()
{
    QString post = ui->postBody->toPlainText();

    //send discussion post data to server
    //no response from server
}



void MainWindow::on_acceptPaper_clicked()
{
    int paperId = loginMgr->getCurrentUser()->getCurrentPaper().paperID;
    int confId  = loginMgr->getActiveConference().confID;

    //send paper id, conf id to server
    //no response from server
}

void MainWindow::on_rejectPaper_clicked()
{
    //this probably does dick all
}
void MainWindow::on_submitReview_clicked()
{
    Review rev;
    rev.confidence = ui->confidence->text().toInt();
    rev.evalution = ui->evaluation->text().toInt();
    rev.originality = ui->originality->text().toInt();
    rev.overall = ui->overall->text().toInt();
    rev.presentation = ui->presentation->text().toInt();
    rev.relevance = ui->relevance->text().toInt();
    rev.significance = ui->significance->text().toInt();
    rev.techQuality = ui->techQuality->text().toInt();
    rev.commentsBestAward = ui->commentsBestAward->toPlainText();
    rev.commentsShortPaper = ui->commentsShortPaper->toPlainText();
    rev.commentsStrength = ui->commentsStrengths->toPlainText();
    rev.commentsSuggestions = ui->commentsSuggestions->toPlainText();
    rev.commentsWeakness = ui->commentsWeaknesses->toPlainText();
    rev.paperID = loginMgr->getCurrentUser()->getCurrentPaper.paperID;
    rev.reviewerID = loginMgr->getCurrentUser()->getUserID();
    //probably going to move some of the above functionality to elsewhere
    

    //submit review to the server
    //no response from server
}

void MainWindow::on_addAsReviewer_clicked()
{
    int paperId = ui->toReview->text().toInt();
    int userId = ui->usersTable->item(ui->usersTable->currentRow(), 2)->text().toInt();

    //send paper id and user id to server to add a paper assigned table entry
    //no response from server
}

void MainWindow::on_addAsReviewer_2_clicked()
{
    int paperId = ui->toReview_2->text().toInt();
    //int userId = ui->reviewersTable->item(ui->usersTable->currentRow(), 2)->text().toInt();
    //above doesnt quite work may add uid field to table

    //send paper id and user id to server to add a paper assigned table entry
    //no response from server
}
