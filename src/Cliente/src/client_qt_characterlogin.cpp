#include <QString>
#include <QTextStream>
#include <QMessageBox>
#include "client_qt_characterlogin.h"
#include "ui_client_qt_characterlogin.h"
#include "client_qt_loginmediator.h"

QtCharacterLogin::QtCharacterLogin(LoginMediator* loginMediator, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QtCharacterLogin),
    loginMediator(loginMediator) {
    ui->setupUi(this);

    //Seteo el ID de los radio buttons
    ui->raceButtonGroup->setId(ui->humanRButton, HUMAN);
    ui->raceButtonGroup->setId(ui->elfRButton, ELF);
    ui->raceButtonGroup->setId(ui->dwarfRButton, DWARF);
    ui->raceButtonGroup->setId(ui->gnomeRButton, GNOME);

    ui->classButtonGroup->setId(ui->mageRButton, MAGE);
    ui->classButtonGroup->setId(ui->clericRButton, CLERIC);
    ui->classButtonGroup->setId(ui->paladinRButton, PALADIN);
    ui->classButtonGroup->setId(ui->warriorRButton, WARRIOR);

    races_names.insert(std::make_pair(HUMAN,"human"));
    races_names.insert(std::make_pair(ELF,"elf"));
    races_names.insert(std::make_pair(DWARF,"dwarf"));
    races_names.insert(std::make_pair(GNOME,"gnome"));

    classes_names.insert(std::make_pair(MAGE,"mage"));
    classes_names.insert(std::make_pair(CLERIC,"cleric"));
    classes_names.insert(std::make_pair(PALADIN,"paladin"));
    classes_names.insert(std::make_pair(WARRIOR,"warrior"));

}

QtCharacterLogin::~QtCharacterLogin() {
    delete ui;
}

void QtCharacterLogin::on_createPushButton_clicked() {
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

    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();
    QMessageBox::information(this, "Lgon", "Creando personaje");
    loginMediator->sendCharacterCreation(username.toStdString(), password.toStdString(),
                                      qs_race.toStdString(), qs_class.toStdString());
}


void QtCharacterLogin::on_loginPushButton_clicked() {
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();
    QMessageBox::information(this, "Login", "Comprobando credenciales");
    loginMediator->sendCharacterLogin(username.toStdString(), password.toStdString());
}


void QtCharacterLogin::setLoginLabel(bool login){
    if(login){
        ui->loginLabel->setStyleSheet("QLabel{color:green;}");
        ui->loginLabel->setText("Login exitoso");
    } else {
        ui->loginLabel->setStyleSheet("QLabel{color:red;}");
        ui->loginLabel->setText("Usuario o contraseña incorrectos");
    }
}

void QtCharacterLogin::showMessageBox(const std::string& text){
    QMessageBox::information(this, "Login", QString(text.c_str()));
}

#include "moc_client_qt_characterlogin.cpp"
