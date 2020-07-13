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

    void on_createPushButton_clicked();

    void on_loginPushButton_clicked();

private:
    Ui::QtCharacterLogin *ui;
    LoginMediator* loginMediator;
    enum e_race {
        HUMAN,
        ELF,
        DWARF,
        GNOME
    };
    enum e_class {
        MAGE,
        CLERIC,
        PALADIN,
        WARRIOR
    };

    std::map<e_race, std::string> races_names;
    std::map<e_class, std::string> classes_names;
};

#endif // MAINWINDOW_H
