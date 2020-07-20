#include <QtWidgets/QMessageBox>
#include <QTextStream>
#include "charactercreationform.h"
#include "ui_charactercreationform.h"

CharacterCreationForm::CharacterCreationForm(LoginMediator* loginMediator, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CharacterCreationForm),
    loginMediator(loginMediator) {
    ui->setupUi(this);

    //Seteo el ID de los radio buttons
    ui->classButtonGroup->setId(ui->mageRButton, WIZARD);
    ui->classButtonGroup->setId(ui->clericRButton, CLERIC);
    ui->classButtonGroup->setId(ui->paladinRButton, PALADIN);
    ui->classButtonGroup->setId(ui->warriorRButton, WARRIOR);

    races_names.insert(std::make_pair(HUMAN,"human"));
    races_names.insert(std::make_pair(ELF,"elf"));
    races_names.insert(std::make_pair(DWARF,"dwarf"));
    races_names.insert(std::make_pair(GNOME,"gnome"));

    classes_names.insert(std::make_pair(WIZARD,"wizard"));
    classes_names.insert(std::make_pair(CLERIC,"cleric"));
    classes_names.insert(std::make_pair(PALADIN,"paladin"));
    classes_names.insert(std::make_pair(WARRIOR,"warrior"));
}

void CharacterCreationForm::on_createPushButton_clicked() {
    int class_id,race_id;
    QString qs_class;
    QString qs_race;

    class_id = ui->classButtonGroup->checkedId();
    auto class_search = classes_names.find((enum e_class)class_id);
    if(class_search != classes_names.end()){
        QTextStream(&qs_class) << class_search->second.c_str();
    }

    race_id = ui->raceComboBox->currentIndex();
    auto race_search = races_names.find((enum e_race)race_id);
    if(race_search != races_names.end()){
        QTextStream(&qs_race) << race_search->second.c_str();
    }


    loginMediator->sendCharacterCreation(qs_race.toStdString(), qs_class.toStdString());
}


void CharacterCreationForm::showMessageBox(const std::string& text){
    QMessageBox::information(this, "Creation", QString(text.c_str()));
}

void CharacterCreationForm::on_backPushButton_clicked(){
    loginMediator->changeToLoginScreen();
}

CharacterCreationForm::~CharacterCreationForm()
{
    delete ui;
}

#include "moc_charactercreationform.cpp"