#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "../DataAll/Review.hpp"
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(Database* db, QWidget *parent) : QMainWindow(parent)
{
    theDB = db;
    ui = new Ui::MainWindow;
    ui->setupUi(this);
    ui->passwordLogin->setEchoMode(QLineEdit::Password);
    noUser();
}

MainWindow::~MainWindow()
{
    delete theUser;
    delete theDB;
    delete theConf;
    delete ui;
}

void MainWindow::popupBox(QString boxTitle, QString msg)
{ // first input: window title; second input: box message
        QMessageBox msgBox;
        msgBox.setWindowTitle(boxTitle);
        msgBox.setText(msg);
        msgBox.exec();
}

void MainWindow::login()
{
    // get username password from gui and grabs user from db, checks pw updates gui
    
    QString msg;
    QString errorBox = "Error!";
    
    QString uname = ui->usernameLogin->text();
    QString pword = ui->usernameLogin->text();
    QString confname = ui->confList->currentItem()->text(); // get name of conference selected
    
    ui->usernameLogin->clear();
    ui->passwordLogin->clear();
    ui->confList->clearSelection();
    
    theUser = new User;
    (*theUser) = theDB->fetchUser(uname.toStdString(), confname.toStdString());
    
    if (theUser->userID == -1)
    {
        msg = "User does not exist for !";
        popupBox(errorBox, msg);
        noUser();
    }
    else if (theUser->password != pword)
    {
        msg = "Incorrect password!";
        popupBox(errorBox, msg);
        noUser();
    }
    else // get userType and load tab
    {
        // fetch conferences
        setUser(theUser->userType)
    }
}


void MainWindow::logout()
{
    delete theUser;
    theUser = NULL;
    noUser();
}

void MainWindow::noUser()
{// clears all tabs, populates conference list, returns to login screen
    ui->tabWidget->clear();
    
    // populate conference list ui->confList
    // get current conferences from db
    std::vector<std::string> activeConfs = theDB->activeConfNames();
    // for numOfCurrConfs ui->confList->addItem(QString)
    for (int i = 0; i < activeConfs.size(); ++i)
        ui->confList->addItems(QString::fromStdString(activeConfs[i]));
    
    ui->tabWidget->addTab(ui->loginTab, "Login");
}

void MainWindow::setUser(UserType_t userType)
{
    switch(userType)
    {
    case AUTHOR://author
        ui->tabWidget->clear();
        ui->tabWidget->addTab(ui->infoTabAuthor, "Info");
        ui->tabWidget->addTab(ui->authorTab, "Author");
        //ui->tabWidget->removeTab(0); //TEST
        break;
    case REVIEWER://reviewer
        ui->tabWidget->clear();
        ui->tabWidget->addTab(ui->infoTabAuthor, "Info");
        ui->tabWidget->addTab(ui->authorTab, "Author");
        ui->tabWidget->addTab(ui->reviewerTab, "Reviewer");
        ui->tabWidget->addTab(ui->reviewTab, "Review");
        ui->tabWidget->removeTab(0);
        break;
    case PCCHAIR://pcchair
        ui->tabWidget->clear();
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

void MainWindow::on_createAccount_clicked() // laurence needs work
{
    theUser = new User();
    QString msg;
    QString errorBox = "Error!";
    bool userExists;
    
    QString uname = ui->usernameLogin->text();
    QString pword = ui->usernameLogin->text();
    ui->usernameLogin->clear();
    ui->passwordLogin->clear();
    
    userExists = theDB->existsUserName(uname);
    
    if (userExists)
    {
        msg = "Username already taken!";
        popupBox(errorBox, msg);
    }
    else
    {
        theUser->userType = AUTHOR;
        
        // update DB with new user
        theDB->putUser(uname, *theUser);
        setUser(theUser->userType);
    }
    
}

void MainWindow::on_apply_clicked() //laurence is here
{
    //update user from gui
    theUser->name = ui->name->text().toStdString();
    theUser->email = ui->email->text().toStdString();
    theUser->phone = ui->phone->text().toStdString();
    theUser->organisation = ui->organisation->text().toStdString();
    
    //clear current users keywords and populate with list from gui
    theUser->keywords.clear();
    for (int i = 0; i < ui->authKeyList->count(); ++i)
        theUser->keywords.push_back(ui->authKeyList->item(i)->text());
    
    // send update user to db
     
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

void MainWindow::on_selectPaperAuthor_activated(int index)
{

}

void MainWindow::on_selectPaperAuthor_currentTextChanged(const QString &arg1)
{
    ui->selectPaperAuthor->setItemText(ui->selectPaperAuthor->currentIndex(), ui->selectPaperAuthor->currentText());
    if(ui->selectPaperAuthor->findText("*NEW*") == -1)
        ui->selectPaperAuthor->addItem("*NEW*");
}

void MainWindow::on_tabWidget_currentChanged(int index)
{//change to current text or something
    QString text = ui->tabWidget->tabText(index);
    if(text == "Info")
        populate_infoTabAuthor();
    else if(text == "Information")
        populate_infoTabChair();
//    else if(text == "Author")
//        populate_authorTab();
//    else if(text == "Reviewer")
//        populate_reviewerTab();
//    else if(text == "Paper Management")
//        populate_papersTab();
//    else if(text == "User Management")
//        populate_usersTab();
//    else if(text == "Review")
//        populate_reviewTab();
}

void MainWindow::populate_infoTabAuthor()
{
    ui->username->setText(QString::fromStdString(theUser->userName));
    ui->userid->setText(QString::number(theUser->userID));
    ui->name->setText(QString::fromStdString(theUser->name));
    ui->email->setText(QString::fromStdString(theUser->email));
    ui->organisation->setText(QString::fromStdString(theUser->organisation));
    ui->phone->setText(QString::fromStdString(theUser->phone));

    for(std::vector<std::string>::iterator it = theUser->keywords.begin(); it != theUser->keywords.end(); ++it)
        ui->authKeyList->addItem(QString::fromStdString(*it));

    ui->conferenceName->setText(QString::fromStdString(theConf->title));
    ui->confTopic->setText(QString::fromStdString(theConf->topic));
    ui->confLocation->setText(QString::fromStdString(theConf->location));
    ui->confDesc->append(QString::fromStdString(theConf->description));
    for(std::vector<std::string>::iterator it = theConf->keywords.begin(); it != theConf->keywords.end(); ++it)
        ui->confKeyListNoEdit->addItem(QString::fromStdString(*it));
    ui->subDate->setText(QString::fromStdString(theConf->paperDeadline.convertToString()));
    ui->discDate->setText(QString::fromStdString(theConf->discussDeadline.convertToString()));
    ui->hReviewDate->setText(QString::fromStdString(theConf->reviewDeadlineHard.convertToString()));
    ui->sReviewDate->setText(QString::fromStdString(theConf->reviewDeadlineSoft.convertToString()));
    ui->allocDate->setText(QString::fromStdString((theConf->allocationDate.convertToString())));
}

void MainWindow::populate_infoTabChair()
{
    ui->name_2->setText(QString::fromStdString(theUser->name));
    ui->email_2->setText(QString::fromStdString(theUser->email));
    ui->organisation_2->setText(QString::fromStdString(theUser->organisation));
    ui->phone_2->setText(QString::fromStdString(theUser->phone));
    ui->confNameMng->setText(QString::fromStdString(theConf->title));
    ui->confTopicMng->setText(QString::fromStdString(theConf->topic));
    ui->confLocMng->setText(QString::fromStdString(theConf->location));
    ui->confDescMng->setText(QString::fromStdString(theConf->description));

    for(std::vector<std::string>::iterator it = theConf->keywords.begin(); it != theConf->keywords.end(); ++it)
        ui->confKeyList->addItem(QString::fromStdString(*it));

    ui->subDateEdit->date().setDate(theConf->paperDeadline.getDay(), theConf->paperDeadline.getMonth(), theConf->paperDeadline.getYear());
    ui->allocDateEdit->date().setDate(theConf->allocationDate.getDay(), theConf->allocationDate.getMonth(), theConf->allocationDate.getYear());
    ui->sReviewDateEdit->date().setDate(theConf->reviewDeadlineSoft.getDay(), theConf->reviewDeadlineSoft.getMonth(), theConf->reviewDeadlineSoft.getYear());
    ui->hReviewDateEdit->date().setDate(theConf->reviewDeadlineHard.getDay(), theConf->reviewDeadlineHard.getMonth(), theConf->reviewDeadlineHard.getYear());
    ui->discDateEdit->date().setDate(theConf->discussDeadline.getDay(), theConf->discussDeadline.getMonth(), theConf->discussDeadline.getYear());
}

void MainWindow::populate_authorTab()
{
    papers.clear();
    //paper = fetch papersummaries

    for(std::vector<PaperSummary>::iterator it = papers.begin(); it != papers.end(); ++it)
        ui->selectPaperAuthor->addItem(QString::fromStdString(it->paperName));
}

void MainWindow::populate_papersTab()
{
//    Paper* paper = &theUser->getCurrentPaper();
//    std::vector<Review>* reviews = &paper->reviews;
//    std::vector<PersonalInfo>* authors = theUser->getCurrentPaper().authors;
//    std::vector<PersonalInfo> reviewers;

//    std::vector<std::string> keys = theUser->getCurrentPaper().keywords;

//    ui->paperNameMng->setText(QString::fromStdString(paper->title));
//    ui->mainKeyMng->setText(QString::fromStdString(paper->confKeyword));

//    ui->paperAbstractMng->append(QString::fromStdString(theUser->getCurrentPaper().abstract));
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
    papers.clear();
    //paper = fetch papersummaries

    for(std::vector<PaperSummary>::iterator it = papers.begin(); it != papers.end(); ++it)
        ui->selectPaperReviewer->addItem(QString::fromStdString(it->paperName));
}

void MainWindow::populate_reviewTab()
{

//    for(std::vector<PaperSummary>::iterator it = papers.begin(); it != papers.end(); ++it)
//        ui->selectPaperReview->addItem(QString::fromStdString(it->paperName));

//    ui->paperAbstractReviewer->setText(QString::fromStdString(theUser->getCurrentPaper().abstract));
//    ui->mainKey->setText(QString::fromStdString(theUser->getCurrentPaper().confKeyword));
//    for(std::vector<std::string>::iterator it = keys.begin(); it != keys.end(); ++it)
//        ui->paperKeyListReview->addItem(QString::fromStdString(*it));

//    for(std::vector<Review>::iterator it = reviews.begin(); it != reviews.end(); ++it){
//        if(it->paperID == theUser->getCurrentPaper().paperID){
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
    int userId = theUser->userID;
    int paperId;
    //paperId = theUser->getCurrentPaper();

    //send users bid on a paper to the server
    //no response from server
}

void MainWindow::downloadPaper()
{

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
    int paperId = theUser->getCurrentPaper().paperID;
    int confId  = theConf->confID;

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
//    rev.paperID = theUser->getCurrentPaper.paperID;
//    rev.reviewerID = theUser->getUserID();

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

//    std::vector<PersonalInfo> authors = theUser->getCurrentPaper().authors;

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

void MainWindow::on_selectPaperAuthor_currentIndexChanged(const QString &arg1)
{
    Paper thePaper;
    //thePaper = fetchPaper(   );
    ui->paperAbstract->append(QString::fromStdString(thePaper.abstract));
    for(std::vector<std::string>::iterator it = thePaper.keywords.begin(); it != thePaper.keywords.end(); ++it)
        ui->paperKeyListAuth->addItem(QString::fromStdString(*it));

    for(std::vector<PersonalInfo>::iterator it = thePaper.authors.begin(); it != thePaper.authors.end(); ++it){
        int rows = ui->authorsTable->rowCount();
        ui->authorsTable->insertRow(rows);
        QTableWidgetItem* newItem = new QTableWidgetItem(QString::fromStdString(it->name));
        ui->authorsTable->setItem(rows, 0, newItem);
        newItem = new QTableWidgetItem(QString::fromStdString(it->email));
        ui->authorsTable->setItem(rows, 1, newItem);
        newItem = new QTableWidgetItem(QString::fromStdString(it->organisation));
        ui->authorsTable->setItem(rows, 2, newItem);
        newItem = new QTableWidgetItem(QString::fromStdString(it->phone));
        ui->authorsTable->setItem(rows, 3, newItem);
    }
    for(std::vector<std::string>::iterator it = theConf->keywords.begin(); it != theConf->keywords.end(); ++it){
        ui->selectMainKey->addItem(QString::fromStdString(*it));
    }
}

void MainWindow::on_selectPaperReviewer_currentIndexChanged(const QString &arg1)
{
    Paper thePaper;
    //thePaper = fetchPaper(  );

    ui->paperAbstractReviewer->append(QString::fromStdString(thePaper.abstract));
    for(std::vector<std::string> it = thePaper.keywords.begin(); it != thePaper.keywords.end(); ++it)
        ui->paperKeyListReviewer->addItem(QString::fromStdString(*it));
    ui->mainKeyReviewer->setText(QString::fromStdString(thePaper.confKeyword));
}


void MainWindow::on_updateConfSettings_clicked()
{

}
