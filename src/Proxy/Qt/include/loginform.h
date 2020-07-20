#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QWidget>
#include "client_qt_loginmediator.h"

namespace Ui {
class LoginForm;
}

class LoginForm : public QWidget
{
    Q_OBJECT

public:
    explicit LoginForm(LoginMediator* loginMediator, QWidget *parent = 0);
    void showMessageBox(const std::string &text);
    void setLoginLabel(bool login);
    ~LoginForm();
private slots:
    void on_loginPushButton_clicked();
    void on_signUpPushButton_clicked();

private:
    Ui::LoginForm *ui;
    LoginMediator* loginMediator;
};

#endif // LOGINFORM_H
