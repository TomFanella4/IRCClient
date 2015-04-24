
#include <time.h>
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
#include <QDebug>

#define MAX_MESSAGES 100
#define MAX_MESSAGE_LEN 300
#define MAX_RESPONSE (20 * 1024)

int lastMessage = 0;

int open_client_socket(char * host, int port) {
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

    // Connect the socket to the specified server
    if (connect(sock, (struct sockaddr *)&socketAddress,
            sizeof(socketAddress)) < 0) {
        perror("connect");
        exit(1);
    }

    return sock;
}

int sendCommand(char * host, int port, char * command, char * user,
        char * pass, char * args, char * response) {
    int sock = open_client_socket( host, port);

    // Send command
    write(sock, command, strlen(command));
    write(sock, " ", 1);
    write(sock, user, strlen(user));
    write(sock, " ", 1);
    write(sock, pass, strlen(pass));
    write(sock, " ", 1);
    write(sock, args, strlen(args));
    write(sock, "\r\n",2);

    // Keep reading until connection is closed or MAX_REPONSE
    int n = 0;
    int len = 0;
    while ((n=read(sock, response+len, MAX_RESPONSE - len))>0) {
        len += n;
    }

    printf("response:%s\n", response);

    close(sock);
}

void printUsage()
{
    printf("Usage: talk-client host port user pass\n");
    exit(1);
}

void add_user(char * host, int port, char * user, char * pass) {
    // Try first to add user in case it does not exist.
    char response[ MAX_RESPONSE ];
    sendCommand(host, port, "ADD-USER", user, pass, "", response);

    if (!strcmp(response,"OK\r\n")) {
        printf("User %s added\n", user);
    }
}

void create_room(char * host, int port, char * user, char * pass) {

}

void enter_room(char * host, int port, char * user, char * pass) {

}

void leave_room(char * host, int port, char * user, char * pass) {

}

void get_messages(char * host, int port, char * user, char * pass) {

}

void send_message(char * msg) {

}

void print_users_in_room() {

}

void print_users(char * host, int port, char * user, char * pass) {
    char response[ MAX_RESPONSE ];
    sendCommand(host, port, "GET-ALL-USERS", user, pass, "", response);
}

void printPrompt() {
    printf("talk> ");
    fflush(stdout);
}

void * getMessagesThread(void * arg) {
    // This code will be executed simultaneously with main()
    // Get messages to get last message number. Discard the initial Messages

    while (1) {
        // Get messages after last message number received.

        // Print messages

        // Sleep for ten seconds
        usleep(2*1000*1000);
    }
}

void startGetMessageThread()
{
    pthread_create(NULL, NULL, getMessagesThread, NULL);
}

void startCommand(char * host, char * sport, char * command, char * user, char * pass) {

    printf("\nStarting talk-client %s %s %s %s\n", host, sport, user, pass);

    int port;

    // Convert port to number
    sscanf(sport, "%d", &port);

    if (!strcmp(command, "ADD-USER"))
        add_user(host, port, user, pass);

    else if (!strcmp(command, "GET-ALL-USERS"))
        print_users(host, port, user, pass);

    else if (!strcmp(command, "CREATE-ROOM"))
        create_room(host, port, user, pass);

    else if (!strcmp(command, "LIST-ROOMS"))
        enter_room(host, port, user, pass);

    else if (!strcmp(command, "ENTER-ROOM"))
        leave_room(host, port, user, pass);

    else if (!strcmp(command, "LEAVE-ROOM"))
        get_messages(host, port, user, pass);

    // Start message thread
    //startGetMessageThread();
    printf("TEST ENDS\n");
}
