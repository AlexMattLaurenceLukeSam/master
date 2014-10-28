#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "Review.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    ui = new Ui::MainWindow;
    ui->setupUi(this);
    noUser();
    ui->passwordLogin->setEchoMode(QLineEdit::Password);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::errorBox(QString msg)
{
        QMessageBox msgBox;
        msgBox.setWindowTitle("Error!");
        msgBox.setDetailedText(msg.c_str());
        msgBox.exec();
}

void MainWindow::loginRequest()
{
    loginMgr.loginRequest(ui->usernameLogin->text(), ui->passwordLogin->text());
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
    QString text = ui->tabWidget->tabText(index);
//    if(text == "Info")
//        populate_infoTabAuthor();
//    else if(text == "Information")
//        populate_infoTabChair();
//    else if(text == "Author")
//        populate_authorTab();
//    else if(text == "Reviewer")
//        populate_reviewerTab();
//    else if(text == "Paper Management")
//        populate_papersTab();
//    else if(text == "USer Management")
//        populate_usersTab();
//    else if(text == "Review")
//        populate_reviewTab();
}

void MainWindow::populate_infoTabAuthor()
{
//    User* user;
//    if(loginMgr->currentAuthor != nullptr)
//        user = dynamic_cast<User*>(loginMgr->currentAuthor);
//    if(loginMgr->currentReviewer != nullptr)
//        user = dynamic_cast<User*>(loginMgr->currentReviewer);

//    ui->username->setText(QString::fromStdString(user->userName));
//    ui->userid->setText(QString::number(user->getUserID()));
//    ui->name->setText(QString::fromStdString(user->getName()));
//    ui->email->setText(QString::fromStdString(user->getEmail()));
//    ui->organisation->setText(QString::fromStdString(user->getOrganisation()));
//    ui->phone->setText(QString::fromStdString(user->getPhone()));

//    if(loginMgr->currentAuthor != nullptr)
//        for(std::vector<std::string>::iterator it = loginMgr->currentAuthor->keywords.begin(); it != loginMgr->currentAuthor->keywords.end(); ++it)
//            ui->authKeyList->addItem(QString::fromStdString(*it));
//    else if(loginMgr->currentReviewer != nullptr)
//        for(std::vector<std::string>::iterator it = loginMgr->currentReviewer->keywords.begin(); it != loginMgr->currentReviewer->keywords.end(); ++it)
//            ui->authKeyList->addItem(QString::fromStdString(*it));

//    ui->conferenceName->setText(QString::fromStdString(loginMgr->activeConference->title));
//    ui->confTopic->setText(QString::fromStdString(loginMgr->activeConference->topic));
//    ui->confLocation->setText(QString::fromStdString(loginMgr->activeConference->location));
//    ui->confDesc->append(QString::fromStdString(loginMgr->activeConference->description));
//    for(std::vector<std::string>::iterator it = loginMgr->activeConference->keywords.begin(); it != loginMgr->activeConference->keywords.end(); ++it)
//        ui->confKeyList->addItem(QString::fromStdString(*it));
//    ui->subDate->setText(QString::fromStdString(loginMgr->activeConference->paperDeadline.toString()));
//    ui->discDate->setText(QString::fromStdString(loginMgr->activeConference->discussDeadline.toString()));
//    ui->hReviewDate->setText(QString::fromStdString(loginMgr->activeConference->reviewDeadlineHard.toString()));
//    ui->sReviewDate->setText(QString::fromStdString(loginMgr->activeConference->reviewDeadlineSoft.toString()));
//    ui->allocDate->setText("29/10/14");
}

void MainWindow::populate_infoTabChair()
{/*
    PCChair* user = loginMgr->currentPCChair;
    Conference* conf = loginMgr->getActiveConference();

    ui->name->setText(QString::fromStdString(user->getName()));
    ui->email->setText(QString::fromStdString(user->getEmail()));
    ui->organisation->setText(QString::fromStdString(user->getOrganisation()));
    ui->phone->setText(QString::fromStdString(user->getPhone()));
    ui->conferenceName->setText(QString::fromStdString(conf->title));
    ui->confTopic->setText(QString::fromStdString(conf->topic));
    ui->confLocation->setText(QString::fromStdString(conf->location));
    ui->confDesc->setText(QString::fromStdString(conf->description));
    for(std::vector<std::string>::iterator it = conf->keywords.begin(); it != conf->keywords.end(); ++it)
        ui->confKeyList->addItem(QString::fromStdString(*it));
    ui->subDateEdit->date().setDate(conf->paperDeadline.day, conf->paperDeadline.month, conf->paperDeadline.year);
    ui->allocDate->setText("29/10/14");
    ui->sReviewDateEdit->date().setDate(conf->reviewDeadlineSoft.day, conf->reviewDeadlineSoft.month, conf->reviewDeadlineSoft.year);
    ui->hReviewDateEdit->date().setDate(conf->reviewDeadlineHard.day, conf->reviewDeadlineHard.month, conf->reviewDeadlineHard.year);
    ui->discDateEdit->date().setDate(conf->discussDeadline.day, conf->discussDeadline.month, conf->discussDeadline.year);*/
}

void MainWindow::populate_authorTab()
{
//    Author* user;
//    if(loginMgr->currentAuthor != nullptr)
//        user = loginMgr->currentAuthor;
//    else if(loginMgr->currentReviewer != nullptr)
//        user = loginMgr->currentReviewer;
//    std::vector<PaperSummary> papers = user->getOwnPapers();
//    std::vector<std::string> keys = user->getCurrentPaper().keywords;
//    std::vector<PersonalInfo> authors = user->getCurrentPaper().authors;

//    for(std::vector<PaperSummary>::iterator it = papers.begin(); it != papers.end(); ++it)
//        ui->selectPaperAuthor->addItem(QString::fromStdString(it->paperName));

//    ui->paperAbstract->append(QString::fromStdString(user->getCurrentPaper().abstract));
//    for(std::vector<std::string>::iterator it = keys.begin(); it != keys.end(); ++it)
//        ui->paperKeyListAuth->addItem(QString::fromStdString(*it));

//    for(std::vector<PersonalInfo>::iterator it = authors.begin(); it != authors.end(); ++it){
//        int rows = ui->authorsTable->rowCount();
//        ui->authorsTable->insertRow(rows);
//        QTableWidgetItem* newItem = new QTableWidgetItem(QString::fromStdString(it->name));
//        ui->authorsTable->setItem(rows, 0, newItem);
//        newItem = new QTableWidgetItem(QString::fromStdString(it->email));
//        ui->authorsTable->setItem(rows, 1, newItem);
//        newItem = new QTableWidgetItem(QString::fromStdString(it->organisation));
//        ui->authorsTable->setItem(rows, 2, newItem);
//        newItem = new QTableWidgetItem(QString::fromStdString(it->phone));
//        ui->authorsTable->setItem(rows, 3, newItem);
//    }
//    for(std::vector<std::string>::iterator it = loginMgr->getActiveConference()->keywords.begin(); it != loginMgr->getActiveConference()->keywords.end(); ++it){
//        ui->selectMainKey->addItem(QString::fromStdString(*it));
//    }
}

void MainWindow::populate_papersTab()
{
//    PCChair* user = loginMgr->currentPCChair;
//    Paper* paper = &user->getCurrentPaper();
//    std::vector<Review>* reviews = &paper->reviews;
//    std::vector<PersonalInfo>* authors = user->getCurrentPaper().authors;
//    std::vector<PersonalInfo> reviewers;

//    std::vector<std::string> keys = user->getCurrentPaper().keywords;

//    ui->paperNameMng->setText(QString::fromStdString(paper->title));
//    ui->mainKeyMng->setText(QString::fromStdString(paper->confKeyword));

//    ui->paperAbstractMng->append(QString::fromStdString(user->getCurrentPaper().abstract));
//    for(std::vector<std::string> it = keys.begin(); it != keys.end(); ++it)
//        ui->paperKeyListMng->addItem(QString::fromStdString(*it));

//    for(std::vector<PersonalInfo>::iterator it = authors.begin(); it != authors.end(); ++it){
//        int rows = ui->authorsTableMng->rowCount();
//        ui->authorsTableMng->insertRow(rows);
//        QTableWidgetItem* newItem = new QTableWidgetItem(QString::fromStdString(it->name));
//        ui->authorsTableMng->setItem(rows, 0, newItem);
//        newItem = new QTableWidgetItem(QString::fromStdString(it->email));
//        ui->authorsTableMng->setItem(rows, 1, newItem);
//        newItem = new QTableWidgetItem(QString::fromStdString(it->organisation));
//        ui->authorsTableMng->setItem(rows, 2, newItem);
//        newItem = new QTableWidgetItem(QString::fromStdString(it->phone));
//        ui->authorsTableMng->setItem(rows, 3, newItem);
//    }
}

void MainWindow::populate_reviewerTab()
{
//    Reviewer* user = loginMgr->currentReviewer;
//    std::vector<PaperSummary> papers;
//    std::vector<std::string> keys;
//    if(loginMgr->getActiveConference()->isBeforePaperDeadline)
//        papers = user->getPapersToBid();
//    else
//        papers = user->getAllocatedPapers();
//    if(user->getCurrentPaper() == nullptr && !papers.empty()){
//        user->setCurrentPaper(papers.at(0));
//        keys = user->getCurrentPaper().getKeywords();
//    }
//    for(std::vector<PaperSummary>::iterator it = papers.begin(); it != papers.end(); ++it)
//        ui->selectPaperReviewer->addItem(QString::fromStdString(it->paperName));

//    ui->paperAbstractReviewer->append(QString::fromStdString(user->getCurrentPaper().abstract));
//    for(std::vector<std::string> it = keys.begin(); it != keys.end(); ++it)
//        ui->paperKeyListReviewer->addItem(QString::fromStdString(*it));
//    ui->mainKeyReviewer->setText(QString::fromStdString(user->getCurrentPaper().confKeyword));
}

void MainWindow::populate_reviewTab()
{
//    Reviewer* user = loginMgr->currentReviewer;
//    std::vector<PaperSummary> papers = user->getAllocatedPapers();
//    std::vector<std::string> keys = user->getCurrentPaper().keywords;
//    std::vector<Review> reviews = user->getReviews();

//    for(std::vector<PaperSummary>::iterator it = papers.begin(); it != papers.end(); ++it)
//        ui->selectPaperReview->addItem(QString::fromStdString(it->paperName));

//    ui->paperAbstractReviewer->setText(QString::fromStdString(user->getCurrentPaper().abstract));
//    ui->mainKey->setText(QString::fromStdString(user->getCurrentPaper().confKeyword));
//    for(std::vector<std::string>::iterator it = keys.begin(); it != keys.end(); ++it)
//        ui->paperKeyListReview->addItem(QString::fromStdString(*it));

//    for(std::vector<Review>::iterator it = reviews.begin(); it != reviews.end(); ++it){
//        if(it->paperID == user->getCurrentPaper().paperID){
//            ui->commentsBestAward->setText(QString::fromStdString(it->commentsBestAward));
//            ui->commentsShortPaper->setText(QString::fromStdString(it->commentsShortPaper));
//            ui->commentsStrengths->setText(QString::fromStdString(it->commentsStrength));
//            ui->commentsWeaknesses->setText(QString::fromStdString(it->commentsWeakness));
//            ui->commentsSuggestions->setText(QString::fromStdString(it->commentsSuggestions));
//        }

//    }
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

void MainWindow::downloadPaper()
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

void MainWindow::on_submitPosts_clicked()
{
    QString post = ui->postBody->toPlainText();

    //send discussion post data to server
    //no response from server
}



void MainWindow::on_acceptPaper_clicked()
{
    int paperId = loginMgr->getCurrentUser()->getCurrentPaper().paperID;
    int confId  = loginMgr->getActiveConference()->confID;

    //send paper id, conf id to server
    //no response from server
}

void MainWindow::on_rejectPaper_clicked()
{
    //this probably does dick all
}
void MainWindow::on_submitReview_clicked()
{
//    Review rev;
//    rev.confidence = ui->confidence->text().toInt();
//    rev.evaluation = ui->evaluation->text().toInt();
//    rev.originality = ui->originality->text().toInt();
//    rev.overall = ui->overall->text().toInt();
//    rev.presentation = ui->presentation->text().toInt();
//    rev.relevance = ui->relevance->text().toInt();
//    rev.significance = ui->significance->text().toInt();
//    rev.techQuality = ui->techQuality->text().toInt();
//    rev.commentsBestAward = ui->commentsBestAward->toPlainText();
//    rev.commentsShortPaper = ui->commentsShortPaper->toPlainText();
//    rev.commentsStrength = ui->commentsStrengths->toPlainText();
//    rev.commentsSuggestions = ui->commentsSuggestions->toPlainText();
//    rev.commentsWeakness = ui->commentsWeaknesses->toPlainText();
//    rev.paperID = loginMgr->getCurrentUser()->getCurrentPaper.paperID;
//    rev.reviewerID = loginMgr->getCurrentUser()->getUserID();

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

void MainWindow::on_papersTable_itemSelectionChanged()
{

//    std::vector<PersonalInfo> authors = loginMgr->currentPCChair->getCurrentPaper().authors;

//    for(std::vector<PersonalInfo>::iterator it = authors.begin(); it != authors.end(); ++it){
//        int rows = ui->reviewersTable->rowCount();
//        ui->reviewersTable->insertRow(rows);
//        QTableWidgetItem* newItem = new QTableWidgetItem(QString::fromStdString(it->name));
//        ui->reviewersTable->setItem(rows, 0, newItem);
//        newItem = new QTableWidgetItem(QString::fromStdString(it->email));
//        ui->reviewersTable->setItem(rows, 1, newItem);
//        newItem = new QTableWidgetItem(QString::fromStdString(it->organisation));
//        ui->reviewersTable->setItem(rows, 2, newItem);
//        newItem = new QTableWidgetItem(QString::fromStdString(it->phone));
//        ui->reviewersTable->setItem(rows, 3, newItem);
//    }

}
