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
    void on_login_clicked(); //done

    void on_quit_clicked(); //done

    void on_logout_clicked(); //done

    void on_logout_2_clicked(); //done

    void on_passwordLogin_returnPressed(); //done

    void on_createAccount_clicked(); // done (i think)

    void on_joinConf_clicked(); // done (i think)

    void on_apply_clicked();// done (i think)
    
    void on_applyChair_clicked();// done (i think)

    void on_addConfKey_clicked(); // already done (i think)

    void on_rmvConfKey_clicked(); // already done (i think)

    void on_addAuthor_clicked(); // laurence is up to here, haven't done yet

    void on_rmvAuthor_clicked();

    void on_addPaperKey_clicked();

    void on_rmvPaperKey_clicked();

    void on_addAuthKey_clicked();

    void on_rmvAuthKey_clicked();

    void on_selectPaperAuthor_activated(int index);

//    void on_selectPaperAuthor_currentTextChanged(const int &arg1);

    void on_tabWidget_currentChanged(int index);

    void on_submit_clicked();//server stuff here

    void on_submitBid_clicked();//server stuff here

    void on_downloadReviewer_clicked();//see downloadPaper()

    void on_submitPosts_clicked();//server stuff here

    void on_downloadChair_clicked(); //see downloadPaper()

    void on_acceptPaper_clicked();//server stuff here

    void on_rejectPaper_clicked();//probably are faking this part

    void downloadPaper();//server stuff here

    void on_submitReview_clicked();//server shit here

//    void on_addAsReviewer_clicked();//server shit here

    void on_addAsReviewer_2_clicked();//server shit here

//    void on_reviewersTable_activated(const QModelIndex &index);

    void on_papersTable_itemSelectionChanged();

    void on_selectPaperAuthor_currentIndexChanged(const QString &arg1);

    void on_selectPaperReviewer_currentIndexChanged(const QString &arg1);

    void on_updateConfSettings_clicked();

private:
    void setUser(UserType_t userType);
//    void noUser(); call logout() instead
    void login(); // done (i think)
    void logout(); //done (i think)
    void populate_infoTabAuthor();
    void populate_infoTabChair();
    void populate_authorTab();
    void populate_reviewerTab();
    void populate_papersTab();
    void populate_usersTab();
    void populate_reviewTab();
    void popupBox(QString boxTitle, QString msg); // done
    
    void clearAllTabs(); //done
    
    Ui::MainWindow *ui;
    User theUser;
    Database* theDB;
    Conference theConf;
    std::vector<PaperSummary> papers;
};

#endif // MAINWINDOW_H
