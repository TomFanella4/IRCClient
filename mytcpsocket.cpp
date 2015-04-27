#include "mytcpsocket.h"
#include <QDebug>

MyTcpSocket::MyTcpSocket()
{

}

char * MyTcpSocket::doConnect(char * host, int sport, char * command)
{
    socket = new QTcpSocket();

    socket->connectToHost(host, sport);

    if(socket->waitForConnected(1000)) {
        qDebug() << "Connected!";

        socket->write(command);

        socket->waitForBytesWritten(1000);
        socket->waitForReadyRead(1500);

        qDebug() << "Reading: " << socket->bytesAvailable();

        // get the data
        QByteArray output = socket->readAll();
        qDebug() << output;

        socket->close();

        return output.data();
    } else {
        qDebug() << "Not connected!";
    }
    return NULL;
}
