#ifndef TESTMAINWINDOW_H
#define TESTMAINWINDOW_H

#include <QMainWindow>
#include "client_qt_loginmediator.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(LoginMediator* loginMediator, QWidget *parent = 0);
    void setServerStatus(bool status);
    ~MainWindow();
private slots:
    void on_connectButton_clicked();
private:
    Ui::MainWindow *ui;
    LoginMediator* loginMediator;
    void closeEvent(QCloseEvent *event) override;
};

#endif // MAINWINDOW_H
