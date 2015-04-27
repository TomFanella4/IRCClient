#include "mytcpsocket.h"
#include <QDebug>
/*#include <time.h>
//#include <curses.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_MESSAGES 100
#define MAX_MESSAGE_LEN 300
#define MAX_RESPONSE (20 * 1024)*/

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
    }
}

/*int MyTcpSocket::open_client_socket(char * host, int port) {
    // Initialize socket address structure
    struct  sockaddr_in socketAddress;

    // Clear sockaddr structure
    memset((char *)&socketAddress,0,sizeof(socketAddress));

    // Set family to Internet
    socketAddress.sin_family = AF_INET;

    // Set port
    socketAddress.sin_port = htons((u_short)port);

    // Get host table entry for this host
    struct  hostent  *ptrh = gethostbyname(host);
    if ( ptrh == NULL ) {
        perror("gethostbyname");
        exit(1);
    }

    // Copy the host ip address to socket address structure
    memcpy(&socketAddress.sin_addr, ptrh->h_addr, ptrh->h_length);

    // Get TCP transport protocol entry
    struct  protoent *ptrp = getprotobyname("tcp");
    if ( ptrp == NULL ) {
        perror("getprotobyname");
        exit(1);
    }

    // Create a tcp socket
    int sock = socket(PF_INET, SOCK_STREAM, ptrp->p_proto);
    if (sock < 0) {
        perror("socket");
        exit(1);
    }

    qDebug() << sock;

    // Connect the socket to the specified server
    if (connect(sock, (struct sockaddr *)&socketAddress,
            sizeof(socketAddress)) < 0) {
        perror("connect");
        exit(1);
    }

    return sock;
}

char * MyTcpSocket::doConnect(char * host, int port, char * command) {
    char * response = (char *)malloc(50 * sizeof(char));

    qDebug() << "test";

    int sock = open_client_socket( host, port);

    qDebug() << "Socket Created";

    // Send command
    //write(sock, command, strlen(command));
    //write(sock, "\r\n",2);

    write(sock, "ADD-USER", strlen("ADD-USER"));
    write(sock, " ", strlen(" "));
    write(sock, "matt", strlen("matt"));
    write(sock, " ", strlen(" "));
    write(sock, "kak", strlen("kak"));
    write(sock, "\r\n", strlen("\r\n"));


    // Keep reading until connection is closed or MAX_REPONSE
    int n = 0;
    int len = 0;
    while ((n=read(sock, response+len, MAX_RESPONSE - len))>0) {
        len += n;
    }

    response[len] = '\0';

    printf("response:%s\n", response);

    close(sock);

    return response;
}*/
