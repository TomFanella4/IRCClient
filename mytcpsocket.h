#ifndef MYTCPSOCKET_H
#define MYTCPSOCKET_H

#include <QTcpSocket>
#include <QDebug>

class MyTcpSocket
{
public:
    MyTcpSocket();

    void doConnect();

private:
    QTcpSocket *socket;

};

#endif // MYTCPSOCKET_H
