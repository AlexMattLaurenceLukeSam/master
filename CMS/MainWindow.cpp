#include "MainWindow.hpp"
#include "Review.hpp"
#include <QMessageBox>
#include <QFileDialog>
#include "Paper.hpp"
#include <QIODevice>
#include <QBuffer>
#include <QByteArray>
#include "PersonalInfo.hpp"

MainWindow::MainWindow(Database* db, QWidget *parent) : QMainWindow(parent)
{
        theUser = User();//    theUser = NULL;
        theConf = Conference();//    theConf = NULL;
    theDB = db;
    ui = new Ui::MainWindow;
    ui->setupUi(this);
    ui->passwordLogin->setEchoMode(QLineEdit::Password);
    logout();
}

MainWindow::~MainWindow()
{
//    delete theUser;
//    delete theConf;
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
    bool error = false;

    QString uname = ui->usernameLogin->text().trimmed();
    QString pword = ui->passwordLogin->text().trimmed();
    
    if (ui->confList->currentRow() == -1) {
        msg.append("Please select a conference!\n");
        error = true;
    }
    if (uname.isEmpty()) {
        msg.append("Please input a username!\n");
        error = true;
    }
    if (pword.isEmpty()) {
        msg.append("Please input a password!\n");
        error = true;
    }
    ui->usernameLogin->clear();
    ui->passwordLogin->clear();
    ui->confList->clearSelection();
    if (error) {
        popupBox(errorBox, msg);
        return;
    }
    
    QString confname = ui->confList->currentItem()->text(); // get name of conference selected
    
    theUser = theDB->fetchUser(uname.toStdString(), confname.toStdString());
    
    if (theUser.userID == -1)
    {
        msg = "User does not exist!";
        popupBox(errorBox, msg);
        logout();
    }
    else if (theUser.password != pword.toStdString())
    {
        msg = "Incorrect password!";
        popupBox(errorBox, msg);
        logout();
    }
    else // get userType and load tab
    {
        
        theConf = theDB->fetchConference(confname.toStdString());
        // get conferences from db
        
        setUser(theUser.userType);
    }
}


void MainWindow::logout()
{
    clearAllTabs();
//    delete theUser;
//    theUser = NULL;
//    delete theConf;
//    theConf = NULL;
    theUser = User();
    theConf = Conference();
    papers.clear();
    
    //return to login screen
    
    // populate conference list ui->confList
    // get current conferences from db
    std::vector<std::string> activeConfs = theDB->activeConfNames();
    
    for (unsigned int i = 0; i < activeConfs.size(); ++i)
        ui->confList->addItem(QString::fromStdString(activeConfs[i]));
    
    ui->tabWidget->addTab(ui->loginTab, "Login");
}

void MainWindow::setUser(UserType_t userType)
{
    clearAllTabs();
    
    switch(userType)
    {
    case AUTHOR://author
        ui->tabWidget->addTab(ui->infoTabAuthor, "Info");
        ui->tabWidget->addTab(ui->authorTab, "Author");
        //ui->tabWidget->removeTab(0);
        break;
    case REVIEWER://reviewer
        ui->tabWidget->addTab(ui->infoTabAuthor, "Info");
        ui->tabWidget->addTab(ui->authorTab, "Author");
        ui->tabWidget->addTab(ui->reviewerTab, "Reviewer");
        ui->tabWidget->addTab(ui->reviewTab, "Review");
        ui->tabWidget->removeTab(0);
        break;
    case PCCHAIR://pcchair
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

void MainWindow::on_createAccount_clicked() // done (i think)
{
    theUser = User();
    QString msg;
    QString errorBox = "Error!";
    bool userExists;
    bool error = false;
    
    QString uname = ui->usernameLogin->text().trimmed();
    QString pword = ui->passwordLogin->text().trimmed();
    
    if (ui->confList->currentRow() == -1) {
        msg.append("Please select a conference!\n");
        error = true;
    }
    if (uname.isEmpty()) {
        msg.append("Please input a username!\n");
        error = true;
    }
    if (pword.isEmpty()) {
        msg.append("Please input a password!\n");
        error = true;
    }
    ui->usernameLogin->clear();
    ui->passwordLogin->clear();
    ui->confList->clearSelection();
    if (error) {
        popupBox(errorBox, msg);
        return;
    }
    
    QString confname = ui->confList->currentItem()->text(); // get name of conference selected
    
    // check if user exists
    userExists = theDB->existsUserName(uname.toStdString());
    
    if (userExists)
    {
        msg = "Username already taken!";
        popupBox(errorBox, msg);
    }
    else
    {
        theUser.userName = uname.toStdString();
        theUser.password = pword.toStdString();
        theUser.userType = AUTHOR;

        // update DB with new user
        theDB->putUser(theUser.userName, theUser);
        theUser = theDB->fetchUser(theUser.userName, confname.toStdString());

        // get conference details from DB
        theConf = theDB->fetchConference(confname.toStdString());
        
        // update DB with userType
        theDB->setUserAsAuthor(theUser.userID, theConf.confID);

        setUser(theUser.userType);
    }
    
}

void MainWindow::on_joinConf_clicked()
{
    QString msg;
    QString errorBox = "Error!";
    bool error = false;

    QString uname = ui->usernameLogin->text().trimmed();
    QString pword = ui->passwordLogin->text().trimmed();
    
    if (ui->confList->currentRow() == -1) {
        msg.append("Please select a conference!\n");
        error = true;
    }
    if (uname.isEmpty()) {
        msg.append("Please input a username!\n");
        error = true;
    }
    if (pword.isEmpty()) {
        msg.append("Please input a password!\n");
        error = true;
    }
    ui->usernameLogin->clear();
    ui->passwordLogin->clear();
    ui->confList->clearSelection();
    if (error) {
        popupBox(errorBox, msg);
        return;
    }
    
    QString confname = ui->confList->currentItem()->text(); // get name of conference selected
   
    theUser = theDB->fetchUser(uname.toStdString(), confname.toStdString());
    
    if (theUser.userID == -1)
    {
        msg = "User does not exist!";
        popupBox(errorBox, msg);
        logout();
    }
    else if (theUser.password != pword.toStdString())
    {
        msg = "Incorrect password!";
        popupBox(errorBox, msg);
        logout();
    }
    else
    {
        
        // get conferences from db
        theConf = theDB->fetchConference(confname.toStdString());
        
        theUser.userType = AUTHOR;
        //update db with usertype
        theDB->setUserAsAuthor(theUser.userID, theConf.confID);
        
        setUser(theUser.userType);
    }
}

void MainWindow::on_apply_clicked() // done (i think)
{
    //update user from gui
    theUser.name = ui->name->text().toStdString();
    theUser.email = ui->email->text().toStdString();
    theUser.phone = ui->phone->text().toStdString();
    theUser.organisation = ui->organisation->text().toStdString();
    
    //clear current users keywords and populate with list from gui
    theUser.keywords.clear();
    for (int i = 0; i < ui->authKeyList->count(); ++i)
        theUser.keywords.push_back(ui->authKeyList->item(i)->text().toStdString());
    
    // send update user to db
    theDB->putUser(theUser.userName, theUser);
    
    popupBox("User Details", "Update Successful!");
}

void MainWindow::on_applyChair_clicked()
{
    //send user details to db
    //update user from gui
    theUser.name = ui->name_2->text().toStdString();
    theUser.email = ui->email_2->text().toStdString();
    theUser.phone = ui->phone_2->text().toStdString();
    theUser.organisation = ui->organisation_2->text().toStdString();
        
    // send updated user to db
    theDB->putUser(theUser.userName, theUser);
    
    //send conference details to db
    //update conf from gui
    std::string confTitleOld = theConf.title;
    theConf.title = ui->confNameMng->text().toStdString();
    theConf.topic = ui->confTopicMng->text().toStdString();
    theConf.location = ui->confLocMng->text().toStdString();
    theConf.description = ui->confDescMng->toPlainText().toStdString();
    QDate tempQdate = ui->subDateEdit->date();
    theConf.paperDeadline = Date(tempQdate.day(), tempQdate.month(), tempQdate.year());
    tempQdate = ui->allocDateEdit->date();
    theConf.allocationDate = Date(tempQdate.day(), tempQdate.month(), tempQdate.year());
    tempQdate = ui->sReviewDateEdit->date();
    theConf.reviewDeadlineSoft = Date(tempQdate.day(), tempQdate.month(), tempQdate.year());
    tempQdate = ui->hReviewDateEdit->date();
    theConf.reviewDeadlineHard = Date(tempQdate.day(), tempQdate.month(), tempQdate.year());
    tempQdate = ui->discDateEdit->date();
    theConf.discussDeadline = Date(tempQdate.day(), tempQdate.month(), tempQdate.year());
    
    //clear current conference keywords and populate with list from gui
    theConf.keywords.clear();
    for (int i = 0; i < ui->confKeyList->count(); ++i)
        theConf.keywords.push_back(ui->confKeyList->item(i)->text().toStdString());
    
    // send updated conf to db
    theDB->putConf(confTitleOld, theConf);
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

void MainWindow::on_selectPaperAuthor_currentTextChanged(const int &arg1)
{
//    ui->selectPaperAuthor->setItemText(ui->selectPaperAuthor->currentIndex(), ui->selectPaperAuthor->currentText());
//    if(ui->selectPaperAuthor->findText("*NEW*") == -1)
//        ui->selectPaperAuthor->addItem("*NEW*");
}

void MainWindow::on_tabWidget_currentChanged(int index)
{//change to current text or something
    if (index < 1)
        return;
    
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
    ui->username->setText(QString::fromStdString(theUser.userName));
    ui->userid->setText(QString::number(theUser.userID));
    ui->name->setText(QString::fromStdString(theUser.name));
    ui->email->setText(QString::fromStdString(theUser.email));
    ui->organisation->setText(QString::fromStdString(theUser.organisation));
    ui->phone->setText(QString::fromStdString(theUser.phone));

    for(std::vector<std::string>::iterator it = theUser.keywords.begin(); it != theUser.keywords.end(); ++it)
        ui->authKeyList->addItem(QString::fromStdString(*it));

    ui->conferenceName->setText(QString::fromStdString(theConf.title));
    ui->confTopic->setText(QString::fromStdString(theConf.topic));
    ui->confLocation->setText(QString::fromStdString(theConf.location));
    ui->confDesc->append(QString::fromStdString(theConf.description));
    for(std::vector<std::string>::iterator it = theConf.keywords.begin(); it != theConf.keywords.end(); ++it)
        ui->confKeyListNoEdit->addItem(QString::fromStdString(*it));
    ui->subDate->setText(QString::fromStdString(theConf.paperDeadline.convertToString()));
    ui->discDate->setText(QString::fromStdString(theConf.discussDeadline.convertToString()));
    ui->hReviewDate->setText(QString::fromStdString(theConf.reviewDeadlineHard.convertToString()));
    ui->sReviewDate->setText(QString::fromStdString(theConf.reviewDeadlineSoft.convertToString()));
    ui->allocDate->setText(QString::fromStdString((theConf.allocationDate.convertToString())));
}

void MainWindow::populate_infoTabChair()
{
    ui->name_2->setText(QString::fromStdString(theUser.name));
    ui->email_2->setText(QString::fromStdString(theUser.email));
    ui->organisation_2->setText(QString::fromStdString(theUser.organisation));
    ui->phone_2->setText(QString::fromStdString(theUser.phone));
    ui->confNameMng->setText(QString::fromStdString(theConf.title));
    ui->confTopicMng->setText(QString::fromStdString(theConf.topic));
    ui->confLocMng->setText(QString::fromStdString(theConf.location));
    ui->confDescMng->setText(QString::fromStdString(theConf.description));

    for(std::vector<std::string>::iterator it = theConf.keywords.begin(); it != theConf.keywords.end(); ++it)
        ui->confKeyList->addItem(QString::fromStdString(*it));

    ui->subDateEdit->date().setDate(theConf.paperDeadline.getDay(), theConf.paperDeadline.getMonth(), theConf.paperDeadline.getYear());
    ui->allocDateEdit->date().setDate(theConf.allocationDate.getDay(), theConf.allocationDate.getMonth(), theConf.allocationDate.getYear());
    ui->sReviewDateEdit->date().setDate(theConf.reviewDeadlineSoft.getDay(), theConf.reviewDeadlineSoft.getMonth(), theConf.reviewDeadlineSoft.getYear());
    ui->hReviewDateEdit->date().setDate(theConf.reviewDeadlineHard.getDay(), theConf.reviewDeadlineHard.getMonth(), theConf.reviewDeadlineHard.getYear());
    ui->discDateEdit->date().setDate(theConf.discussDeadline.getDay(), theConf.discussDeadline.getMonth(), theConf.discussDeadline.getYear());
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
//    Paper* paper = &theUser.getCurrentPaper();
//    std::vector<Review>* reviews = &paper->reviews;
//    std::vector<PersonalInfo>* authors = theUser.getCurrentPaper().authors;
//    std::vector<PersonalInfo> reviewers;

//    std::vector<std::string> keys = theUser.getCurrentPaper().keywords;

//    ui->paperNameMng->setText(QString::fromStdString(paper->title));
//    ui->mainKeyMng->setText(QString::fromStdString(paper->confKeyword));

//    ui->paperAbstractMng->append(QString::fromStdString(theUser.getCurrentPaper().abstract));
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

//    ui->paperAbstractReviewer->setText(QString::fromStdString(theUser.getCurrentPaper().abstract));
//    ui->mainKey->setText(QString::fromStdString(theUser.getCurrentPaper().confKeyword));
//    for(std::vector<std::string>::iterator it = keys.begin(); it != keys.end(); ++it)
//        ui->paperKeyListReview->addItem(QString::fromStdString(*it));

//    for(std::vector<Review>::iterator it = reviews.begin(); it != reviews.end(); ++it){
//        if(it->paperID == theUser.getCurrentPaper().paperID){
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
    bool existsPaper;
    
    PersonalInfo anAuth;
    std::string authName;
    std::string authEmail;
    std::string authOrg;
    std::string authPh;
    
    std::string pdf;
        
    aPaper.confID = theConf.confID;
    aPaper.leadAuthorID = theUser.userID;
    
    existsPaper = db->existsPaperTitleConf(aPaper);
            
    aPaper.title = ui->selectPaperAuthor->currentText().toStdString();
    
    // clear current auth details and populate list from gui
    aPaper.authors.clear();
    int numRows = ui->authorsTable->rowCount();
    for (int row = 0; row < numRows; ++row) {
        authName = ui->authorsTable->item(row, 0)->text().toStdString();
        authEmail = ui->authorsTable->item(row, 1)->text().toStdString();
        authOrg = ui->authorsTable->item(row, 2)->text().toStdString();
        authPh = ui->authorsTable->item(row, 3)->text().toStdString();
        anAuth = PersonalInfo(authName,
                                authEmail,
                                authOrg,
                                authPh);
        aPaper.authors.push_back(anAuth);
    }
    
    //clear current paper keywords and populate with list from gui
    aPaper.keywords.clear();
    int numKwords = ui->paperKeyListAuth->count();
    for (int i = 0; i < numKwords; ++i)
        aPaper.keywords.push_back(ui->paperKeyListAuth->item(i)->text().toStdString());
    
    aPaper.abstract = ui->paperAbstract->toPlainText().toStdString();
    
    aPaper.confKeyword = ui->selectMainKey->currentText().toStdString();
    
    
    // if new paper upload pdf
    if (!existsPaper)
    {
        pdf = ui->selectFile->text().toStdString();
        
        db->createPaper(aPaper, pdf);
    }
    else
    {
        std::string comment = ui->rebuttalEntry->toPlainText().toStdString();
        int reviewerID = theUser.userID;
        
        aPaper.discussion.discussion.push_back(DiscussionPost(comment, reviewerID));
        
        db->updatePaper(aPaper);
    }
    
    popupBox("Paper Information", "Update Successful!");
}

void MainWindow::on_submitBid_clicked()
{
    int bid = ui->selectBid->currentText().toInt();
    int userId = theUser.userID;
    int paperId;
    //paperId = theUser.getCurrentPaper();

    //send users bid on a paper to the server
    //no response from server
}

void MainWindow::downloadPaper()
{
//    //we should maybe use QDataStreams instead of QTextStreams but theres no ez way to convert them to QStrings
//    QFileDialog dialog(this);
//    QString fname, pdfString;
//
//    dialog.setWindowTitle("Save File...");
//    dialog.setFileMode(QFileDialog::AnyFile);
//    dialog.setNameFilter("Files (.pdf)");
//    if(dialog.exec())
//        fname = dialog.selectedFiles().at(0);
//    else
//        return;
//
//    //fetch pdf string from db into pdfString
//    QFile file(fname);
//    if(file.open(QIODevice::ReadWrite)){
//        QTextStream stream(&file);
//        stream << pdfString;
//    }

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
//    int paperId = theUser.getCurrentPaper().paperID;
//    int confId  = theConf.confID;

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
//    rev.paperID = theUser.getCurrentPaper.paperID;
//    rev.reviewerID = theUser.getUserID();

    //submit review to the server
    //no response from server
}

//void MainWindow::on_addAsReviewer_clicked()
//{
//    int paperId = ui->toReview()->text().toInt();
//    int userId = ui->usersTable->item(ui->usersTable->currentRow(), 2)->text().toInt();
//
//    //send paper id and user id to server to add a paper assigned table entry
//    //no response from server
//}

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

//    std::vector<PersonalInfo> authors = theUser.getCurrentPaper().authors;

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
    for(std::vector<std::string>::iterator it = theConf.keywords.begin(); it != theConf.keywords.end(); ++it){
        ui->selectMainKey->addItem(QString::fromStdString(*it));
    }
}

void MainWindow::on_selectPaperReviewer_currentIndexChanged(const QString &arg1)
{
//    Paper thePaper;
//    //thePaper = fetchPaper(  );
//
//    ui->paperAbstractReviewer->append(QString::fromStdString(thePaper.abstract));
//    for(std::vector<std::string> it = thePaper.keywords.begin(); it != thePaper.keywords.end(); ++it)
//        ui->paperKeyListReviewer->addItem(QString::fromStdString(*it));
//    ui->mainKeyReviewer->setText(QString::fromStdString(thePaper.confKeyword));
}

void MainWindow::on_selectPaperReview_currentIndexChanged(const QString &arg1)
{
 //similar to above except also fetch the appropriate review of the paper
}

void MainWindow::on_updateConfSettings_clicked()
{

}

void MainWindow::on_reviewersTable_itemActivated(QTableWidgetItem *item)
{
    //populate review values with the given reviewers review
    //the word review was used too many times in that sentence but you know what i mean
}

void MainWindow::on_papersTable_itemClicked(QTableWidgetItem *item)
{
    //populate paper info based upon the id of the paper selected
}

void MainWindow::clearAllTabs()
{
    foreach(QLineEdit *widget, this->findChildren<QLineEdit*>())
        widget->clear();
    foreach(QListWidget *widget, this->findChildren<QListWidget*>())
        widget->clear();
    foreach(QTextBrowser *widget, this->findChildren<QTextBrowser*>())
        widget->clear();
    foreach(QDateEdit *widget, this->findChildren<QDateEdit*>())
        widget->clear();
    foreach(QTextEdit *widget, this->findChildren<QTextEdit*>())
        widget->clear();
    foreach(QComboBox *widget, this->findChildren<QComboBox*>())
        widget->clear();
    foreach(QTableWidget *widget, this->findChildren<QTableWidget*>())
        widget->clear();
    foreach(QSpinBox *widget, this->findChildren<QSpinBox*>())
        widget->clear();
    
    ui->tabWidget->clear();
}
