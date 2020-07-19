#include <QtWidgets/QMessageBox>
#include <QtGui/QPainter>
#include <QtGui/QCloseEvent>
#include "client_qt_serverlogin.h"
#include "client_qt_loginmediator.h"
#include "ui_client_qt_serverlogin.h"
QtServerLogin::QtServerLogin(LoginMediator* loginMediator, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QtServerLogin),
    loginMediator(loginMediator) {
    ui->setupUi(this);
}

QtServerLogin::~QtServerLogin() {
    delete ui;
}

void QtServerLogin::on_connectButton_clicked() {
    QString host = ui->hostLineEdit->text();
    QString service = ui->serviceLineEdit->text();

    loginMediator->sendServerCredentials(host.toStdString(), service.toStdString());
}

void QtServerLogin::paintEvent(QPaintEvent *event) {
    this->setFixedWidth(800);
    this->setFixedHeight(700);
    QPixmap bkgnd("./../assets/background.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
    QPainter painter(this);
    painter.drawImage(QRect(150, 100, 500, 200), QImage("./../assets/logo.png"));
    ui->hostLineEdit->setFixedWidth(600);
    ui->serviceLineEdit->setFixedWidth(600);
    ui->label->setVisible(false);
    ui->label_2->setStyleSheet("color:white;");
    ui->label_3->setStyleSheet("color:white;");
    ui->label_5->setStyleSheet("color:white;");
    ui->label_5->setAlignment(Qt::AlignCenter);
    ui->label_2->setFixedWidth(40);
    ui->connectButton->setStyleSheet("QPushButton{"
                                     "background-image:url(./../assets/hover-button.9.png);"
                                     "border: none;"
                                     "color:white;"
                                     "font: bold 14px;}");

    ui->connectButton->setFixedWidth(202);
    ui->connectButton->setFixedHeight(33);
    ui->gridLayout->setAlignment(Qt::AlignCenter);
    ui->gridLayout_2->setAlignment(Qt::AlignCenter);
    ui->gridLayout_2->setAlignment(ui->connectButton,Qt::AlignCenter);
}

void QtServerLogin::closeEvent(QCloseEvent *event) {
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "argentum",
                                                                tr("Are you sure?\n"),
                                                                QMessageBox::Cancel | QMessageBox::Yes,
                                                                QMessageBox::Yes);

    if (resBtn == QMessageBox::Yes) {
        QWidget::closeEvent(event);
    } else {
        event->ignore();
    }
}

void QtServerLogin::setServerStatus(bool status) {
    if(status){
        ui->serverStateLabel->setStyleSheet("QLabel{color: green;}");
        ui->serverStateLabel->setText("Server online!");
    } else {
        ui->serverStateLabel->setStyleSheet("QLabel{color: red;}");
        ui->serverStateLabel->setText("Server offline!");
    }
}

#include "moc_client_qt_serverlogin.cpp"