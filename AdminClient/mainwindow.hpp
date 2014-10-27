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
    void on_addConf_clicked();

    void on_rmvConf_clicked();

    void on_addUserKey_clicked();

    void on_rmvUserKey_clicked();

    void on_quit_2_clicked();
    
private:
    Ui::MainWindow *ui;
    LoginManager* loginMgr;
    QString username;
    QString password;
};

#endif // MAINWINDOW_H
