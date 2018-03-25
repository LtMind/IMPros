#include <QApplication>
#include <QMetaType>

#include "logiclayer.h"

int main(int argc, char *argv[])
{
    qRegisterMetaType<UserInfo>("UserInfo");
    QApplication app(argc, argv);

    LogicLayer logic;
    logic.showLoginW();

    return app.exec();
}
