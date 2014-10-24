#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "LoginManager.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_login_clicked();

    void on_quit_clicked();

    void on_logout_clicked();

    void on_logout_2_clicked();

    void on_passwordLogin_returnPressed();

    void on_createAccount_clicked();

    void on_apply_clicked();

    void on_apply_2_clicked();

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

private:
    void setUser(int userType);
    void login();
    void logout();

    Ui::MainWindow *ui;
    LoginManager loginMgr;
    QString username;
    QString password;
};

#endif // MAINWINDOW_H
