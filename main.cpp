#include "ircclient.h"
#include "login.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    IRCClient irc;
    irc.show();

    return a.exec();
}
