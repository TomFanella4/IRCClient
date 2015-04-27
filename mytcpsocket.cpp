#include "mytcpsocket.h"
#include <QDebug>

MyTcpSocket::MyTcpSocket()
{

}

char * MyTcpSocket::doConnect(char * host, int sport, char * command)
{
    socket = new QTcpSocket();

    socket->connectToHost(host, sport);

    if(socket->waitForConnected(1000))
    {
        qDebug() << "Connected!";

        /*char * token = strtok(command, " ");

        while (token != NULL) {
            socket->write(token);
            socket->write(" ");

            token = strtok(NULL, " ");
        }*/
        // send
        //socket->write("GET-ALL-USERS jill l\r\n");
        socket->write(command);

        //socket->flush();
        socket->waitForBytesWritten(1000);
        socket->waitForReadyRead(1500);

        qDebug() << "Reading: " << socket->bytesAvailable();

        // get the data
        QByteArray output = socket->readAll();
        qDebug() << output;

        // close the connection
        //socket->close();

        //socket->disconnectFromHost();

        socket->close();

        return output.data();
    }
    else
    {
        qDebug() << "Not connected!";
        //doConnect(host, sport, command);
    }
}
