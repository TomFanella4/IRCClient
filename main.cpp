#include "ircclient.h"
#include "login.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //IRCClient w;
    //w.show();

    Login w;
    w.show();

    return a.exec();
}
