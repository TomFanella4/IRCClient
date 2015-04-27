#include "ircclient.h"
#include "ui_ircclient.h"
#include "adduser.h"
#include "login.h"
#include "addroom.h"
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

    initializeUser();
    refreshRoomList();
}

IRCClient::~IRCClient()
{
    delete ui;
}

void IRCClient::initializeUser() {

    char message[100];
    sprintf(message, "ADD-USER %s %s\r\n", getCUsername(), getCPassword());

    printf("Host: %s\nPort: %d\nUsername: %s\nPassword: %s\nMessage: %s\n", getHost(), getPort(), getCUsername(), getCPassword(), message);

    socket.doConnect(getHost(), getPort(), message);
}

void IRCClient::on_Button_addUser_clicked() {
    AddUser addUser;
    addUser.setModal(true);
    addUser.exec();

    QByteArray array1 = addUser.getUsername().toUtf8();
    char * uName = array1.data();

    QByteArray array2 = addUser.getPassword().toUtf8();
    char * uPass = array2.data();

    if (strcmp(uName, "") != 0 && strcmp(uPass, "") != 0) {

        char message[100];
        sprintf(message, "ADD-USER %s %s\r\n", uName, uPass);

        printf("Host: %s\nPort: %d\nUsername: %s\nPassword: %s\nMessage: %s\n", getHost(), getPort(), uName, uPass, message);

        socket.doConnect(getHost(), getPort(), message);

        //ui->listWidget_userList->addItem(addUser.getUsername());

        //refreshUserList();
    }
}

void IRCClient::on_Button_createRoom_clicked()
{

    AddRoom addRoom;
    addRoom.setModal(true);
    addRoom.exec();

    QByteArray array1 = addRoom.getRoomName().toUtf8();
    char * rName = array1.data();

    if (strcmp(rName, "") != 0) {

        char message[100];
        sprintf(message, "CREATE-ROOM %s %s %s\r\n", cUsername, cPassword, rName);

        printf("Host: %s\nPort: %d\nUsername: %s\nPassword: %s\nMessage: %s\n", getHost(), getPort(), cUsername, cPassword, message);

        socket.doConnect(getHost(), getPort(), message);

        //ui->listWidget_roomList->addItem(addRoom.getRoomName());

        refreshRoomList();
    }
}

void IRCClient::on_Button_sendMessage_clicked() {
    char * room = strdup(ui->listWidget_roomList->currentItem()->text().toStdString().c_str());
    char * mess = strdup(ui->textbox_sendMessage->toPlainText().toStdString().c_str());

    char message[100];
    sprintf(message, "SEND-MESSAGE %s %s %s %s\r\n", getCUsername(), getCPassword(), room, mess);

    socket.doConnect(getHost(), getPort(), message);

    refreshMessageList(room);
}

void IRCClient::on_listWidget_roomList_itemClicked(QListWidgetItem *item) {
    char * room = strdup(item->text().toStdString().c_str());

    char message[100];
    sprintf(message, "ENTER-ROOM %s %s %s", getCUsername(), getCPassword(), room);

    printf("Host: %s\nPort: %d\nUsername: %s\nPassword: %s\nMessage: %s\n", getHost(), getPort(), getCUsername(), getCPassword(), message);

    socket.doConnect(getHost(), getPort(), message);
    refreshUserList(room);
    refreshMessageList(room);
}

void IRCClient::refreshUserList(char * room) {

    char message[100];
    sprintf(message, "GET-USERS-IN-ROOM %s %s %s\r\n", getCUsername(), getCPassword(), room);

    printf("Host: %s\nPort: %d\nUsername: %s\nPassword: %s\nMessage: %s\n", getHost(), getPort(), getCUsername(), getCPassword(), message);

    char * userList = socket.doConnect(getHost(), getPort(), message);
    char * token;
    QString stoken;

    ui->listWidget_userList->clear();

    token = strtok(userList, "\n");

    while (token != NULL && strcmp(token, "\0")) {
        stoken.sprintf("%s", token);
        ui->listWidget_userList->addItem(stoken);

        token = strtok(NULL, "\n");
    }
}

void IRCClient::refreshRoomList() {

    char message[100];
    sprintf(message, "LIST-ROOMS %s %s\r\n", getCUsername(), getCPassword());

    printf("Host: %s\nPort: %d\nUsername: %s\nPassword: %s\nMessage: %s\n", getHost(), getPort(), getCUsername(), getCPassword(), message);

    char * userList = socket.doConnect(getHost(), getPort(), message);
    char * token;
    QString stoken;

    ui->listWidget_roomList->clear();

    token = strtok(userList, "\n");

    while (token != NULL && strcmp(token, "\n")) {
        stoken.sprintf("%s", token);
        ui->listWidget_roomList->addItem(stoken);

        token = strtok(NULL, "\n");
    }
}

void IRCClient::refreshMessageList(char * room) {
    char message[100];
    sprintf(message, "GET-MESSAGES %s %s %d %s\r\n", getCUsername(), getCPassword(), 0, room);

    printf("Host: %s\nPort: %d\nUsername: %s\nPassword: %s\nMessage: %s\n", getHost(), getPort(), getCUsername(), getCPassword(), message);

    char * userList = socket.doConnect(getHost(), getPort(), message);
    char * token;
    QString stoken;

    ui->listWidget_messageList->clear();

    token = strtok(userList, "\n");

    while (token != NULL && strcmp(token, "\n")) {
        stoken.sprintf("%s", token);
        ui->listWidget_messageList->addItem(stoken);

        token = strtok(NULL, "\n");
    }
}

void IRCClient::on_Button_refreshList_clicked() {
    refreshRoomList();
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
