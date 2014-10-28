#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../Server/User.hpp"
#include "../Database/Database.hpp"

namespace Ui {
class MainWindow;
}

class LoginManager;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Database *db, QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_login_clicked();//done (i think)

    void on_quit_clicked();

    void on_logout_clicked();

    void on_logout_2_clicked();

    void on_passwordLogin_returnPressed();

    void on_createAccount_clicked();// done (i think)

    void on_apply_clicked();//laurence is here

    void on_applyChair_clicked();//server things here

    void on_addConfKey_clicked();

    void on_rmvConfKey_clicked();

    void on_addAuthor_clicked();

    void on_rmvAuthor_clicked();

    void on_addPaperKey_clicked();

    void on_rmvPaperKey_clicked();

    void on_addAuthKey_clicked();

    void on_rmvAuthKey_clicked();

    void on_selectPaperAuthor_activated(int index);

    void on_selectPaperAuthor_currentTextChanged(const QString &arg1);

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

    void on_addAsReviewer_clicked();//server shit here

    void on_addAsReviewer_2_clicked();//server shit here

    void on_reviewersTable_activated(const QModelIndex &index);

    void on_papersTable_itemSelectionChanged();

private:
    void setUser(UserType_t userType);
    void noUser();
    void login();
    void logout();
    void populate_infoTabAuthor();
    void populate_infoTabChair();
    void populate_authorTab();
    void populate_reviewerTab();
    void populate_papersTab();
    void populate_usersTab();
    void populate_reviewTab();
    void popupBox(QString type, QString msg);

    Ui::MainWindow *ui;
    User* theUser;
    Conference* theConf;
    Database* theDB;
    std::vector<PaperSummary> papers;
};

#endif // MAINWINDOW_H
