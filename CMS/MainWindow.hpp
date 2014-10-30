#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModelIndex>
#include "User.hpp"
#include "Database.hpp"
#include "Conference.hpp"
#include <string>
#include <vector>
#include "PaperSummary.hpp"
#include "ui_MainWindow.h"
#include "Paper.hpp"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Database *db, QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_login_clicked();
    void on_quit_clicked();
    void on_logout_clicked();
    void on_logout_2_clicked();
    void on_passwordLogin_returnPressed();
    void on_createAccount_clicked();
    void on_joinConf_clicked();
    void on_apply_clicked();
    void on_applyChair_clicked();
    void on_addConfKey_clicked();
    void on_rmvConfKey_clicked();
    void on_addAuthor_clicked();
    void on_rmvAuthor_clicked();
    void on_addPaperKey_clicked();
    void on_rmvPaperKey_clicked();
    void on_addAuthKey_clicked();
    void on_rmvAuthKey_clicked();
    void on_tabWidget_currentChanged(int index);
    void on_submit_clicked();
    void on_submitBid_clicked();
    void on_downloadReviewer_clicked();
    void on_submitPosts_clicked();
    void on_downloadChair_clicked();
    void on_acceptPaper_clicked();
    void on_rejectPaper_clicked();
    void on_submitReview_clicked();
    
    void on_addAsReviewer_clicked();

    void on_papersTable_itemSelectionChanged();

    void on_selectPaperAuthor_currentIndexChanged(const QString &arg1);

    void on_selectPaperReviewer_currentIndexChanged(const QString &arg1);
    
    void on_reviewersTable_itemActivated(QTableWidgetItem *item);
    
    void on_selectPaperToReview_currentIndexChanged(const QString &arg1);
    
    void on_changeReviewer_clicked();
    
    void on_usersTable_itemClicked(QTableWidgetItem *item);
    
    void on_runAlgo_clicked();

private:
    void popupBox(QString boxTitle, QString msg);
    void setUser(UserType_t userType);
    void login();
    void logout();
    void updateDiscussionPosts();
    void downloadPaper();
    void populate_infoTabAuthor();
    void populate_infoTabChair();
    void populate_authorTab();
    void populate_reviewerTab();
    void populate_papersTab();
    void populate_usersTab();
    void populate_reviewTab();
    
    void clearAllTabs(); //done
    
    Ui::MainWindow *ui;
    User theUser;
    Database* theDB;
    Conference theConf;
    std::vector<PaperSummary> papers;
    Paper aPaper;
};

#endif // MAINWINDOW_H
