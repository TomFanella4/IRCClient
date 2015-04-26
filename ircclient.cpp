#include "ircclient.h"
#include "ui_ircclient.h"
#include "adduser.h"
#include "login.h"
#include "stdlib.h"

IRCClient::IRCClient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::IRCClient)
{
    ui->setupUi(this);

    Login l;
    l.setModal(true);
    l.exec();

    setHost(l.getLoginH());
    setPort(l.getLoginPort());
    setCUsername(l.getLoginU());
    setCPassword(l.getLoginP());

    refreshUserList();
}

IRCClient::~IRCClient()
{
    delete ui;
}

void IRCClient::on_Button_addUser_clicked()
{
    AddUser addUser;
    addUser.setModal(true);
    addUser.exec();

    QByteArray array1 = addUser.getUsername().toUtf8();
    char * uName = array1.data();

    QByteArray array2 = addUser.getPassword().toUtf8();
    char * uPass = array2.data();

    if (strcmp(uName, "") != 0 && strcmp(uPass, "") != 0) {

        char * message = (char *)malloc(strlen(uName) + strlen(uPass) + strlen("  ADD-USER\r\n") + 1);
        sprintf(message, "ADD-USER %s %s\r\n", uName, uPass);

        printf("Host: %s\nPort: %d\nUsername: %s\nPassword: %s\nMessage: %s\n", getHost(), getPort(), uName, uPass, message);

        socket.doConnect(getHost(), getPort(), message);

        ui->listWidget_userList->addItem(addUser.getUsername());

        refreshUserList();
    }
}

void IRCClient::refreshUserList() {

    char * message = (char *)malloc(strlen(getCUsername()) + strlen(getCPassword()) + strlen("  GET-ALL-USERS\r\n") + 1);
    sprintf(message, "GET-ALL-USERS %s %s\r\n", getCUsername(), getCPassword());

    printf("Host: %s\nPort: %d\nUsername: %s\nPassword: %s\nMessage: %s\n", getHost(), getPort(), getCUsername(), getCPassword(), message);

    char * userList = socket.doConnect(getHost(), getPort(), message);
    char * token;
    QString stoken;

    ui->listWidget_userList->clear();

    token = strtok(userList, "\n");

    while (token != NULL && strcmp(token, "\n")) {
        stoken.sprintf("%s", token);
        ui->listWidget_userList->addItem(stoken);

        token = strtok(NULL, "\n");
    }
}

void IRCClient::on_Button_addRoom_clicked()
{

}

char * IRCClient::getHost() {
    return host;
}

int IRCClient::getPort() {
    return port;
}

char * IRCClient::getCUsername() {
    return cUsername;
}

char * IRCClient::getCPassword() {
    return cPassword;
}

void IRCClient::setHost(char * h) {
    host = h;
}

void IRCClient::setPort(int p) {
    port = p;
}

void IRCClient::setCUsername(char * u) {
    cUsername = u;
}

void IRCClient::setCPassword(char * p) {
    cPassword = p;
}
