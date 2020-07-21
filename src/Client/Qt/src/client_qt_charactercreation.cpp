#include <QString>
#include <QTextStream>
#include <QMessageBox>
#include "client_qt_charactercreation.h"
#include "client_qt_loginmediator.h"
#include "ui_client_qt_charactercreation.h"

QtCharacterCreation::QtCharacterCreation(LoginMediator* loginMediator, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::client_qt_charactercreation),
    loginMediator(loginMediator){
    ui->setupUi(this);
    //Seteo el ID de los radio buttons
    ui->raceButtonGroup->setId(ui->humanRButton, HUMAN);
    ui->raceButtonGroup->setId(ui->elfRButton, ELF);
    ui->raceButtonGroup->setId(ui->dwarfRButton, DWARF);
    ui->raceButtonGroup->setId(ui->gnomeRButton, GNOME);

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

QtCharacterCreation::~QtCharacterCreation()
{
    delete ui;
}

void QtCharacterCreation::on_createPushButton_clicked() {
    int race_id, class_id;
    QString qs_race, qs_class;

    race_id = ui->raceButtonGroup->checkedId();
    class_id = ui->classButtonGroup->checkedId();
    std::map<e_race, std::string>::iterator search = races_names.find((enum e_race)race_id);
    if(search != races_names.end()){
        QTextStream(&qs_race) << search->second.c_str();
        ui->selectedRaceLabel->setText(qs_race);
    }

    std::map<e_class, std::string>::iterator class_search = classes_names.find((enum e_class)class_id);
    if(class_search != classes_names.end()){
        QTextStream(&qs_class) << class_search->second.c_str();
        ui->selectedClassLabel->setText(qs_class);
    }

    loginMediator->sendCharacterCreation(qs_race.toStdString(), qs_class.toStdString());
}


void QtCharacterCreation::showMessageBox(const std::string& text){
    QMessageBox::information(this, "Creation", QString(text.c_str()));
}

void QtCharacterCreation::on_backPushButton_clicked(){
    loginMediator->changeToLoginScreen();
}


#include "moc_client_qt_charactercreation.cpp"