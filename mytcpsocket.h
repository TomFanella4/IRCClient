#ifndef MYTCPSOCKET_H
#define MYTCPSOCKET_H

#include <QTcpSocket>

class MyTcpSocket
{
public:
    MyTcpSocket();

    char * doConnect(char * host, int sport, char * command);
    int open_client_socket(char * host, int port);

private:
    QTcpSocket *socket;

};

#endif // MYTCPSOCKET_H
