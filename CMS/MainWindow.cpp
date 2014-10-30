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
    aPaper = Paper();
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
    theUser = User();
    theConf = Conference();
    aPaper = Paper();
    
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
    else if (theUser.userType == NOUSER)
    {
        msg = "Not currently signed up for selected conference!";
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
    ui->tabWidget->clear();
//    delete theUser;
//    theUser = NULL;
//    delete theConf;
//    theConf = NULL;
    theUser = User();
    theConf = Conference();
    papers.clear();
    aPaper = Paper();
    
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
    ui->tabWidget->clear();
    
    switch(userType)
    {
    case AUTHOR://author
        populate_infoTabAuthor();
        populate_authorTab();
        ui->tabWidget->addTab(ui->infoTabAuthor, "Info");
        ui->tabWidget->addTab(ui->authorTab, "Author");
        break;
    case REVIEWER://reviewer
        populate_infoTabAuthor();
        populate_authorTab();
        populate_reviewTab();
        populate_reviewerTab();
        ui->tabWidget->addTab(ui->infoTabAuthor, "Info");
        ui->tabWidget->addTab(ui->authorTab, "Author");
        ui->tabWidget->addTab(ui->reviewerTab, "Reviewer");
        ui->tabWidget->addTab(ui->reviewTab, "Review");
        break;
    case PCCHAIR://pcchair
        populate_infoTabChair();
        populate_usersTab();
        populate_papersTab();
        ui->tabWidget->addTab(ui->infoTabChair, "Information");
        ui->tabWidget->addTab(ui->usersTab, "User Management");
        ui->tabWidget->addTab(ui->papersTab, "Paper Management");
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
    if (error) {
        popupBox(errorBox, msg);
        return;
    }
    
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

        // update DB with new user
        theDB->putUser(theUser.userName, theUser);
        
        popupBox("SUCCESS!", "Username successfully created!\nPlease join a conference to continue.");
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
    else if (theUser.userType == NOUSER)
    {
        
        // get conferences from db
        theConf = theDB->fetchConference(confname.toStdString());
        
        theUser.userType = AUTHOR;
        //update db with usertype
        theDB->setUserAsAuthor(theUser.userID, theConf.confID);
        
        setUser(theUser.userType);
    }
    else
    {
        msg = "Already joined conference! Please use login instead.";
        popupBox(errorBox, msg);
        logout();
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
    theUser.name = ui->name_3->text().toStdString();
    theUser.email = ui->email_3->text().toStdString();
    theUser.phone = ui->phone_3->text().toStdString();
    theUser.organisation = ui->organisation_3->text().toStdString();
        
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
    
    theConf.postWordLimit = ui->wordsPerPost->value();
    theConf.reviewersPerPaper = ui->reviewersPerPaper->value();
    
    // send updated conf to db
    theDB->putConf(confTitleOld, theConf);
    
    popupBox("Details", "Update Successful!");
}

void MainWindow::on_addConfKey_clicked()
{
    ui->confKeyList->addItem(ui->confKeyEntry->text());
    ui->confKeyEntry->clear();
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
    ui->paperKeyEntry->clear();
}

void MainWindow::on_rmvPaperKey_clicked()
{
    delete ui->paperKeyListAuth->currentItem();
}

void MainWindow::on_addAuthKey_clicked()
{
    ui->authKeyList->addItem(ui->authKeyEntry->text());
    ui->authKeyEntry->clear();
}

void MainWindow::on_rmvAuthKey_clicked()
{
    delete ui->authKeyList->currentItem();
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    if (index < 0)
        return;
    
    QString text = ui->tabWidget->tabText(index);
    if(text == "Info")
        populate_infoTabAuthor();
    else if(text == "Information")
        populate_infoTabChair();
    else if(text == "Author")
        populate_authorTab();
    else if(text == "Reviewer")
        populate_reviewerTab();
    else if(text == "Paper Management")
        populate_papersTab();
    else if(text == "User Management")
        populate_usersTab();
    else if(text == "Review")
        populate_reviewTab();
}

void MainWindow::populate_infoTabAuthor()
{
    clearAllTabs();
    
    ui->username->setText(QString::fromStdString(theUser.userName));
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
    clearAllTabs();
    
    ui->username_3->setText(QString::fromStdString(theUser.userName));
    ui->name_3->setText(QString::fromStdString(theUser.name));
    ui->email_3->setText(QString::fromStdString(theUser.email));
    ui->organisation_3->setText(QString::fromStdString(theUser.organisation));
    ui->phone_3->setText(QString::fromStdString(theUser.phone));
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
    
    ui->wordsPerPost->setValue(theConf.postWordLimit);
    ui->reviewersPerPaper->setValue(theConf.reviewersPerPaper);
}

void MainWindow::populate_authorTab()
{
    clearAllTabs();
    
    ui->selectMainKey->clear();
    ui->selectPaperAuthor->clear();
    ui->paperKeyListAuth->clear();
    ui->authorsTable->clear();
    ui->paperAbstract->clear();
    ui->authorsTable->clearContents();
    ui->rebuttalEntry->clear();
    ui->selectFile->clear();
    
    while (ui->authorsTable->rowCount() > 0)
        ui->authorsTable->removeRow(0);
    
    aPaper = Paper();
    papers.clear();
    papers = theDB->allAuthorsPaperSummary(theConf.confID, theUser.userID);

    for(std::vector<PaperSummary>::iterator it = papers.begin(); it != papers.end(); ++it)
    {
        ui->selectPaperAuthor->addItem(QString::fromStdString(it->paperName));
    }
        
    for(std::vector<std::string>::iterator it = theConf.keywords.begin(); it != theConf.keywords.end(); ++it)
        ui->selectMainKey->addItem(QString::fromStdString(*it));
    
    ui->selectPaperAuthor->addItem("*NEW PAPER*");
}

void MainWindow::populate_papersTab()
{
    clearAllTabs();
    
    std::vector<int> allPapersConf = theDB->getPaperIDsForConf(theConf.confID);
    for(std::vector<int>::iterator itor = allPapersConf.begin(); itor != allPapersConf.end(); ++itor)
    {
        PaperSummary ps = theDB->fetchPaperSummary(*itor);
        ui->papersTable->addItem(QString::fromStdString(ps.paperName));
        papers.push_back(ps);
    }
}

void MainWindow::populate_reviewerTab()
{
    clearAllTabs();
    
    std::vector<int> allPapersConf = theDB->getPaperIDsForConf(theConf.confID);
    for(std::vector<int>::iterator itor = allPapersConf.begin(); itor != allPapersConf.end(); ++itor)
        papers.push_back(theDB->fetchPaperSummary(*itor));
    
    for(std::vector<PaperSummary>::iterator it = papers.begin(); it != papers.end(); ++it)
        ui->selectPaperReviewer->addItem(QString::fromStdString(it->paperName));
}

void MainWindow::populate_reviewTab()
{
    clearAllTabs();

    std::vector<int> papersIdsToReview = theDB->getPaperIDsForAllocatedReviewer(theUser.userID, theConf.confID);
    for(std::vector<int>::iterator itor = papersIdsToReview.begin(); itor != papersIdsToReview.end(); ++itor)
        papers.push_back(theDB->fetchPaperSummary(*itor));
    
    for(std::vector<PaperSummary>::iterator it = papers.begin(); it != papers.end(); ++it)
        ui->selectPaperToReview->addItem(QString::fromStdString(it->paperName));
}

void MainWindow::populate_usersTab()
{
    clearAllTabs();
    
    std::vector<int> uID = theDB->getUserIDsForConf(theConf.confID);
    std::vector<User> allUsers;
    QString userT = "";
    
    for (std::vector<int>::iterator itor = uID.begin(); itor != uID.end(); ++itor) {

        allUsers.push_back(theDB->fetchUserFromID(*itor, theConf.confID));

    }
    
    for(std::vector<User>::iterator itor = allUsers.begin(); itor != allUsers.end(); ++itor)
    {
        int rows = ui->usersTable->rowCount();
        ui->usersTable->insertRow(rows);
        QTableWidgetItem* newItem = new QTableWidgetItem(QString::fromStdString(itor->name));
        ui->usersTable->setItem(rows, 0, newItem);
        newItem = new QTableWidgetItem(QString::fromStdString(itor->userName));
        ui->usersTable->setItem(rows, 1, newItem);
        
        switch(itor->userType)
        {
            case AUTHOR:
                userT = "Author"; break;
            case REVIEWER:
                userT = "Reviewer"; break;
            case PCCHAIR:
                userT = "PC Chair"; break;
        }
        newItem = new QTableWidgetItem(userT);
        ui->usersTable->setItem(rows, 2, newItem);
    }
}

void MainWindow::on_submit_clicked()
{
    bool existsPaper;
    Paper newPaper;
    PersonalInfo anAuth;
    std::string authName;
    std::string authEmail;
    std::string authOrg;
    std::string authPh;
    
    std::string pdf;
    
    newPaper.confID = theConf.confID;
    newPaper.leadAuthorID = theUser.userID;

    newPaper.title = ui->selectPaperAuthor->currentText().toStdString();
    existsPaper = theDB->existsPaperTitleConf(newPaper);

    // clear current auth details and populate list from gui
    newPaper.authors.clear();
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
        newPaper.authors.push_back(anAuth);
    }

    //clear current paper keywords and populate with list from gui
    newPaper.keywords.clear();
    int numKwords = ui->paperKeyListAuth->count();
    for (int i = 0; i < numKwords; ++i)
        newPaper.keywords.push_back(ui->paperKeyListAuth->item(i)->text().toStdString());
 
    newPaper.abstract = ui->paperAbstract->toPlainText().toStdString();
    
    newPaper.confKeyword = ui->selectMainKey->currentText().toStdString();
    

    // if new paper upload pdf
    if (!existsPaper)
    {
        pdf = ui->selectFile->text().toStdString();
        theDB->createPaper(newPaper, pdf);
        
    }
    else
    {
        std::string comment = ui->rebuttalEntry->toPlainText().toStdString();
        int reviewerID = theUser.userID;
        
        theDB->createDiscussionPost(DiscussionPost(comment, reviewerID), newPaper.paperID, newPaper.confID);
        
        theDB->updatePaper(newPaper);
        
    }
    
    aPaper = theDB->fetchPaper(newPaper.paperID);

    popupBox("Paper Information", "Update Successful!");
}

void MainWindow::on_submitBid_clicked()
{
    //should have aPaper;
    
    int userId = theUser.userID;
    int paperId = aPaper.paperID;
    int confId = theConf.confID;
    int bidVal;
    std::string bid = ui->selectBid->currentText().toStdString();
    
    if (bid == "Yes")
        bidVal = 1;
    else if (bid == "Maybe")
        bidVal = 2;
    else if (bid == "No")
        bidVal = 3;
    else if (bid == "Conflict of Interest")
        bidVal = 4;

    //send users bid on a paper to the db
    theDB->setReviewerPreference(userId, confId, paperId, bidVal);
    // reviewerID, paperID, confID, bid(int)
    
    popupBox("Reviewer Preference", "Preference updated");
}

void MainWindow::downloadPaper()
{
    int paperId = aPaper.paperID;
    int confId = theConf.confID;
    std::string submittedPaperPDF = theDB->fetchPDF(paperId, confId);
    
    std::string downloadMsg;
    downloadMsg = "The paper\n" + aPaper.title + "\nhas been downloaded to the following location:\n" + submittedPaperPDF;
    
    QString boxTitle = "Paper Available to Review";
    popupBox(boxTitle, QString::fromStdString(downloadMsg));
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
    QString comment = ui->postBody->toPlainText();
    int reviewerId = theUser.userID;
    int confId = theConf.confID;
    int paperId = aPaper.paperID;
    
    DiscussionPost newPost = DiscussionPost(comment.toStdString(), reviewerId);
    //send discussion post data to server
    theDB->createDiscussionPost(newPost, paperId, confId);
    
    updateDiscussionPosts();
}

void MainWindow::on_acceptPaper_clicked()
{
    int paperId = aPaper.paperID;
    int confId  = theConf.confID;
    
    theDB->addPaperAccepted(paperId, confId);
    
    QString msgTitle = "Paper Management";
    QString msg = QString::fromStdString(aPaper.title);
    msg.append("\nhas been accepted");
    popupBox(msgTitle, msg);
}

void MainWindow::on_rejectPaper_clicked()
{
    QString msgTitle = "Paper Management";
    QString msg = QString::fromStdString(aPaper.title);
    msg.append("\nhas been rejected");
    popupBox(msgTitle, msg);
}

void MainWindow::updateDiscussionPosts()
{
    // updates discussion posts on reviewer tab`
}

void MainWindow::on_submitReview_clicked()
{
    // aPaper should be available after selecting from list
    
    int confID = theConf.confID;
    Review rev;
    
    rev.confidence = ui->confidence->value();
    rev.evaluation = ui->evaluation->value();
    rev.originality = ui->originality->value();
    rev.overall = ui->overall->value();
    rev.presentation = ui->presentation->value();
    rev.relevance = ui->relevance->value();
    rev.significance = ui->significance->value();
    rev.techQuality = ui->techQuality->value();
    rev.commentsBestAward = ui->commentsBestAward->toPlainText().toStdString();
    rev.commentsShortPaper = ui->commentsShortPaper->toPlainText().toStdString();
    rev.commentsStrength = ui->commentsStrengths->toPlainText().toStdString();
    rev.commentsSuggestions = ui->commentsSuggestions->toPlainText().toStdString();
    rev.commentsWeakness = ui->commentsWeaknesses->toPlainText().toStdString();
    rev.paperID = aPaper.paperID;
    rev.reviewerID = theUser.userID;

    //submit review to the db
    theDB->modifyReview(rev, confID);
}

void MainWindow::on_addAsReviewer_clicked()
{
    // should have aPaper
    // takes username in toReview
    QString reviewerName = ui->toReview->text();
    // checks if extsts and userType is PCMember for current conference
    User reviewer = theDB->fetchUser(reviewerName.toStdString(), theConf.title);
    if (reviewer.userID == -1)
    {
        popupBox("Error!", "User does not exist!");
        return;
    }
    else if (reviewer.userType != REVIEWER)
    {
        popupBox("Error!", "Incorrect password!");
        return;
    }
    
    // updates db with reviewer
    theDB->assignPaper(aPaper.paperID, reviewer.userID, theConf.confID);
    
    // inserts reviewer information into reviewersTable
    
    
    popupBox("", "Reviewer successfully assigned to paper");
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
    ui->paperKeyListAuth->clear();
    ui->authorsTable->clear();
    ui->selectMainKey->clear();
    ui->paperAbstract->clear();
    ui->authorsTable->clearContents();
    ui->rebuttalEntry->clear();
    ui->selectFile->clear();
    
    while (ui->authorsTable->rowCount() > 0)
        ui->authorsTable->removeRow(0);

    if (arg1 == "*NEW PAPER*")
        return;
    
    for(std::vector<PaperSummary>::iterator it = papers.begin(); it != papers.end(); ++it)
    {
        if(it->paperName == arg1.toStdString())
                aPaper = theDB->fetchPaper(it->paperID);
    }
    ui->paperAbstract->append(QString::fromStdString(aPaper.abstract));
    for(std::vector<std::string>::iterator it = aPaper.keywords.begin(); it != aPaper.keywords.end(); ++it)
        ui->paperKeyListAuth->addItem(QString::fromStdString(*it));

    for(std::vector<PersonalInfo>::iterator it = aPaper.authors.begin(); it != aPaper.authors.end(); ++it){
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
    
    ui->selectMainKey->setCurrentIndex(ui->selectMainKey->findText(QString::fromStdString(aPaper.confKeyword)));
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
    
    
    
    
    
//    QString paperkeyword = "PAPER KEYWORD: ";
//    paperkeyword.append(QString::fromStdString(aPaper.confKeyword));
//    ui->mainKeyReviewer->setText(paperkeyword);
}

void MainWindow::on_selectPaperToReview_currentIndexChanged(const QString &arg1)
{
 //similar to above except also fetch the appropriate review of the paper
}

void MainWindow::on_reviewersTable_itemActivated(QTableWidgetItem *item)
{
    //populate review values with the given reviewers review
    //the word review was used too many times in that sentence but you know what i mean
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
    foreach(QSpinBox *widget, this->findChildren<QSpinBox*>())
        widget->clear();
    foreach(QTableWidget *widget, this->findChildren<QTableWidget*>())
    {
        widget->clearContents();
        while (widget->rowCount() > 0)
            widget->removeRow(0);
    }
    foreach(QComboBox *widget, this->findChildren<QComboBox*>())
    {
        if (widget->toolTip() != "-1")
            widget->clear();
    }
    
    aPaper = Paper();
    papers.clear();
}

void MainWindow::on_changeReviewer_clicked()
{
    int row = ui->usersTable->currentRow();
    QString uName = ui->usersTable->item(row, 1)->text();
    User auser = theDB->fetchUser(uName.toStdString(), theConf.title);
    QString type;
    QTableWidgetItem* newItem;
    
    if (auser.userType == AUTHOR)
    {
        type = "Reviewer";
        theDB->updateUserAsPC(auser.userID, theConf.confID);
        newItem = new QTableWidgetItem(type);
        ui->usersTable->setItem(row, 2, newItem);
        QString msg = auser.name.c_str();
        msg.append(" is now a reviewer");
        popupBox("User Updated", msg);
    }
    else if (auser.userType == REVIEWER)
    {
        type = "Author";
        theDB->updateUserAsAuthor(auser.userID, theConf.confID);
        newItem = new QTableWidgetItem(type);
        ui->usersTable->setItem(row, 2, newItem);
        QString msg = auser.name.c_str();
        msg.append(" is no long a reviewer");
        popupBox("User Updated", msg);
    }
    else
        popupBox("Error!", "Contact admin to update PC Chairs!");
}

void MainWindow::on_usersTable_itemClicked(QTableWidgetItem *item)
{
    aPaper = Paper();
    papers.clear();
    ui->userKeyList->clear();
    ui->authoredPapers->clear();
    ui->assignedPapers->clear();
    
    QString uName = ui->usersTable->item(item->row(), 1)->text();
    User auser = theDB->fetchUser(uName.toStdString(), theConf.title);
    std::vector<int> vInts;
    
    ui->usernameMgr->setText(QString::fromStdString(auser.userName));
    ui->userIDMgr->setText(QString::number(auser.userID));
    ui->nameMgr->setText(QString::fromStdString(auser.name));
    ui->emailMgr->setText(QString::fromStdString(auser.email));
    ui->organisationMgr->setText(QString::fromStdString(auser.organisation));
    ui->phoneMgr->setText(QString::fromStdString(auser.phone));

    for(std::vector<std::string>::iterator it = auser.keywords.begin(); it != auser.keywords.end(); ++it)
        ui->userKeyList->addItem(QString::fromStdString(*it));
    
    
    
    //get users authored papaers
    vInts = theDB->getPapersForAuthor(auser.userID);
    for (std::vector<int>::iterator it = vInts.begin(); it != vInts.end(); ++it)
        ui->authoredPapers->addItem(QString::fromStdString(theDB->fetchPaper(*it).title));
    vInts.clear();
    
    // get useres papers assigned to review
}

void MainWindow::on_runAlgo_clicked()
{
    
}