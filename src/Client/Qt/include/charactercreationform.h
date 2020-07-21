#ifndef CHARACTERCREATIONFORM_H
#define CHARACTERCREATIONFORM_H

#include <QWidget>
#include "client_qt_loginmediator.h"

namespace Ui {
class CharacterCreationForm;
}

class CharacterCreationForm : public QWidget
{
    Q_OBJECT

public:
    explicit CharacterCreationForm(LoginMediator* loginMediator,QWidget *parent = 0);
    void showMessageBox(const std::string &text);
    ~CharacterCreationForm();

private slots:
    void on_createPushButton_clicked();
    void on_backPushButton_clicked();

private:
    Ui::CharacterCreationForm *ui;
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

#endif // CHARACTERCREATIONFORM_H
