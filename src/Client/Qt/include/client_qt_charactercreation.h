#ifndef CLIENT_QT_CHARACTERCREATION_H
#define CLIENT_QT_CHARACTERCREATION_H

#include <QWidget>

namespace Ui {
class client_qt_charactercreation;
}

class LoginMediator;
class QtCharacterCreation : public QWidget
{
    Q_OBJECT

public:
    explicit QtCharacterCreation(LoginMediator* loginMediator, QWidget *parent = 0);
    ~QtCharacterCreation();
    void showMessageBox(const std::string& text);

private slots:
    void on_createPushButton_clicked();

    void on_backPushButton_clicked();

private:
    Ui::client_qt_charactercreation *ui;
    LoginMediator* loginMediator;

    enum e_race {
        HUMAN,
        ELF,
        DWARF,
        GNOME
    };
    enum e_class {
        WIZARD,
        CLERIC,
        PALADIN,
        WARRIOR
    };

    std::map<e_race, std::string> races_names;
    std::map<e_class, std::string> classes_names;

};

#endif // CLIENT_QT_CHARACTERCREATION_H
