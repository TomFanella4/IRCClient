#ifndef MYTCPSOCKET_H
#define MYTCPSOCKET_H

#include <QTcpSocket>
#include <QDebug>

class MyTcpSocket
{
public:
    MyTcpSocket();

    char * doConnect(char * host, int sport, char * command);

private:
    QTcpSocket *socket;

};

#endif // MYTCPSOCKET_H
