#ifndef CLIENT_QT_SERVERLOGIN_H
#define CLIENT_QT_SERVERLOGIN_H

#include <QWidget>
#include"client_qt_characterlogin.h"

namespace Ui {
class QtServerLogin;
}

class LoginMediator;
class QtServerLogin : public QWidget
{
    Q_OBJECT

public:
    explicit QtServerLogin(LoginMediator* loginMediator, QWidget *parent = 0);
    ~QtServerLogin();
    void setServerStatus(bool status);

private slots:
    void on_connectButton_clicked();

private:
    Ui::QtServerLogin *ui;
    LoginMediator* loginMediator;
    void closeEvent(QCloseEvent *event) override ;
};

#endif // CLIENT_QT_SERVERLOGIN_H
