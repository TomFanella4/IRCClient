#include "mytcpsocket.h"

MyTcpSocket::MyTcpSocket()
{

}

char * MyTcpSocket::doConnect(char * host, int sport, char * command)
{
    socket = new QTcpSocket();

    socket->connectToHost(host, sport);

    if(socket->waitForConnected(5000))
    {
        qDebug() << "Connected!";

        // send
        //socket->write("GET-ALL-USERS jill l\r\n");
        socket->write(command);
        socket->waitForBytesWritten(1000);
        socket->waitForReadyRead(1175);

        qDebug() << "Reading: " << socket->bytesAvailable();

        // get the data
        QByteArray output = socket->readAll();
        qDebug() << output;

        // close the connection
        socket->close();

        return output.data();
    }
    else
    {
        qDebug() << "Not connected!";
    }
}
