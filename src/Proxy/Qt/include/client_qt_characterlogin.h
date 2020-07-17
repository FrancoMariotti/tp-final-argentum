#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class QtCharacterLogin;
}

class LoginMediator;
class QtCharacterLogin : public QMainWindow
{
    Q_OBJECT

public:
    explicit QtCharacterLogin(LoginMediator* loginMediator, QWidget *parent = 0);
    ~QtCharacterLogin();
    void setLoginLabel(bool login);
    void showMessageBox(const std::string& text);

private slots:

    void on_loginPushButton_clicked();

    void on_signUpPushButton_clicked();

private:
    Ui::QtCharacterLogin *ui;
    LoginMediator* loginMediator;

};

#endif // MAINWINDOW_H
