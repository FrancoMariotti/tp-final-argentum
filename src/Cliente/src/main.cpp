#include "client_qt_loginmediator.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginMediator loginMediator;
    loginMediator.show();

    return a.exec();
}
