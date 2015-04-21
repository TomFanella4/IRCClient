#include "ircclient.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    IRCClient w;
    w.show();

    return a.exec();
}
