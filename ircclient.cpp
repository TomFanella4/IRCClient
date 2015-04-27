#include "ircclient.h"
#include "ui_ircclient.h"
#include "adduser.h"
#include "login.h"
#include "addroom.h"
#include "worker.h"
#include "QThread"

IRCClient::IRCClient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::IRCClient)
{
    ui->setupUi(this);

    Login l;
    l.setModal(true);
    l.exec();

    while (!strcmp(l.getLoginH(), "") || l.getLoginPort() == 0 || !strcmp(l.getLoginU(), "") || !strcmp(l.getLoginP(), "")) {
        close();
    }

    setHost(l.getLoginH());
    setPort(l.getLoginPort());
    setCUsername(l.getLoginU());
    setCPassword(l.getLoginP());

    cRoom = strdup("");

    initializeUser();
    refreshRoomList();
    refreshRoomList();
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
    QListWidgetItem * roomItem = ui->listWidget_roomList->currentItem();
    QString messItem = ui->textbox_sendMessage->toPlainText();

    if (messItem == NULL || roomItem == NULL)
        return;

    char * room = strdup(roomItem->text().toStdString().c_str());
    char * mess = strdup(messItem.toStdString().c_str());

    char message[100];
    sprintf(message, "SEND-MESSAGE %s %s %s %s\r\n", getCUsername(), getCPassword(), room, mess);

    socket.doConnect(getHost(), getPort(), message);

    ui->textbox_sendMessage->clear();

    refreshMessageList(room);
}

void IRCClient::on_listWidget_roomList_itemClicked(QListWidgetItem *item) {
    if (strcmp(cRoom, "") != 0) {
        char m[100];
        sprintf(m, "LEAVE-ROOM %s %s %s\r\n", getCUsername(), getCPassword(), cRoom);

        socket.doConnect(getHost(), getPort(), m);
    }

    char * room = strdup(item->text().toStdString().c_str());
    cRoom = strdup(room);
    printf("%s\n", room);

    char message[100];
    sprintf(message, "ENTER-ROOM %s %s %s\r\n", getCUsername(), getCPassword(), room);

    printf("Host: %s\nPort: %d\nUsername: %s\nPassword: %s\nMessage: %s\n", getHost(), getPort(), getCUsername(), getCPassword(), message);

    socket.doConnect(getHost(), getPort(), message);
    refreshUserList(room);
    refreshUserList(room);

    QThread * thread = new QThread;
    Worker* worker = new Worker();
    worker->setRoom(room);
    worker->setIRC(this);
    worker->moveToThread(thread);
    connect(thread, SIGNAL(started()), worker, SLOT(process()));
    connect(worker, SIGNAL(finished()), thread, SLOT(quit()));
    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
    //refreshMessageList(room);
}

void IRCClient::refreshUserList(char * room) {

    char message[100];
    sprintf(message, "GET-USERS-IN-ROOM %s %s %s\r\n", getCUsername(), getCPassword(), room);

    printf("Host: %s\nPort: %d\nUsername: %s\nPassword: %s\nMessage: %s\n", getHost(), getPort(), getCUsername(), getCPassword(), message);

    char * userList = socket.doConnect(getHost(), getPort(), message);

    while (strstr(userList, "\r\n\r") == NULL && strlen(userList) > 2)
        userList = socket.doConnect(getHost(), getPort(), message);

    char * token;
    QString stoken;

    ui->listWidget_userList->clear();

    token = strtok(userList, "\r\n");

    while (token != NULL) {
        stoken.sprintf("%s", token);
        ui->listWidget_userList->addItem(stoken);

        token = strtok(NULL, "\r\n");
    }
}

void IRCClient::refreshRoomList() {

    char message[100];
    sprintf(message, "LIST-ROOMS %s %s\r\n", getCUsername(), getCPassword());

    printf("Host: %s\nPort: %d\nUsername: %s\nPassword: %s\nMessage: %s\n", getHost(), getPort(), getCUsername(), getCPassword(), message);

    char * userList = socket.doConnect(getHost(), getPort(), message);

    while (strstr(userList, "\r\n\r") == NULL && strlen(userList) > 2)
        userList = socket.doConnect(getHost(), getPort(), message);

    char * token;
    QString stoken;

    ui->listWidget_roomList->clear();

    token = strtok(userList, "\r\n");

    while (token != NULL) {
        stoken.sprintf("%s", token);
        ui->listWidget_roomList->addItem(stoken);

        token = strtok(NULL, "\r\n");
    }
}

void IRCClient::refreshMessageList(char * room) {
    char message[100];
    sprintf(message, "GET-MESSAGES %s %s %d %s\r\n", getCUsername(), getCPassword(), 0, room);

    printf("Host: %s\nPort: %d\nUsername: %s\nPassword: %s\nMessage: %s\n", getHost(), getPort(), getCUsername(), getCPassword(), message);

    char * userList = socket.doConnect(getHost(), getPort(), message);

    while (strstr(userList, "\r\n\r") == NULL && strstr(userList, "NO-NEW-MESSAGES") == NULL)
        userList = socket.doConnect(getHost(), getPort(), message);

    char * token;
    QString stoken;

    ui->listWidget_messageList->clear();

    token = strtok(userList, "\r\n");

    while (token != NULL) {
        stoken.sprintf("%s", token);
        ui->listWidget_messageList->addItem(stoken);

        token = strtok(NULL, "\r\n");
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

char * IRCClient::getRoom() {
    return cRoom;
}
