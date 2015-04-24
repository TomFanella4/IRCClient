/*#ifndef TALKCLIENT_H
#define TALKCLIENT_H


class TalkClient
{

public:
    TalkClient();
    ~TalkClient();
    int open_client_socket(char * host, int port);
    int sendCommand(char * host, int port, char * command, char * user,
        char * pass, char * args, char * response);
    void printUsage();
    void add_user();

    void enter_room();
    void leave_room();
    void get_messages(char * msg);
    void print_users_in_room();
    void print_users();
    void printPrompt();
    void printhHelp();
    void * getMessagesThread(void * arg);
    void startGetMessageThread();

    void startCommand(char * host, char * sport, const char * user, const char * pass);
};

#endif // TALKCLIENT_H
*/
