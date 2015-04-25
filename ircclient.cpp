#include "ircclient.h"
#include "ui_ircclient.h"
#include "adduser.h"
#include "login.h"
#include "stdlib.h"

#include "talk-client.cpp"

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

    QByteArray array3 = getHost().toUtf8();
    char * uHost = array3.data();

    char * uPort = (char *)malloc(sizeof(getPort()) + 1);
    snprintf(uPort, sizeof(getPort()) + 1, "%d", getPort());

    if (strcmp(uName, "") != 0 && strcmp(uPass, "") != 0) {

        printf("Username: %s\nPassword: %s", uName, uPass);

        startCommand(uHost, uPort,"ADD-USER", uName, uPass);
        ui->listWidget_userList->addItem(addUser.getUsername());
    }
}

void IRCClient::on_Button_addRoom_clicked()
{

}

QString IRCClient::getHost() {
    return host;
}

int IRCClient::getPort() {
    return port;
}

QString IRCClient::getCUsername() {
    return cUsername;
}

QString IRCClient::getCPassword() {
    return cPassword;
}

void IRCClient::setHost(QString h) {
    host = h;
}

void IRCClient::setPort(int p) {
    port = p;
}

void IRCClient::setCUsername(QString u) {
    cUsername = u;
}

void IRCClient::setCPassword(QString p) {
    cPassword = p;
}
