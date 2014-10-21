#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

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

    void on_usernameLogin_editingFinished();

    void on_passwordLogin_editingFinished();

    void on_logout_clicked();

    void on_logout_2_clicked();

private:
    Ui::MainWindow *ui;
    void setUser(int userType);
    QString username;
    QString password;
};

#endif // MAINWINDOW_H
