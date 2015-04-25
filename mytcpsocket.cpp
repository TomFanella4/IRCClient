#include "mytcpsocket.h"

MyTcpSocket::MyTcpSocket()
{

}

void MyTcpSocket::doConnect()
{
    socket = new QTcpSocket();

    socket->connectToHost("data.cs.purdue.edu", 2040);

    if(socket->waitForConnected(5000))
    {
        qDebug() << "Connected!";

        // send
        socket->write("GET-ALL-USERS jill l\r\n");
        socket->waitForBytesWritten(1000);
        socket->waitForReadyRead(1500);

        qDebug() << "Reading: " << socket->bytesAvailable();

        // get the data
        qDebug() << socket->readAll();

        // close the connection
        socket->close();
    }
    else
    {
        qDebug() << "Not connected!";
    }
}
