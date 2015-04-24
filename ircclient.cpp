#include "ircclient.h"
#include "ui_ircclient.h"
#include "adduser.h"

#include "talk-client.cpp"

IRCClient::IRCClient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::IRCClient)
{
    ui->setupUi(this);
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

        printf("Username: %s\nPassword: %s", uName, uPass);

        startCommand("data.cs.purdue.edu", "2030", uName, uPass);
        ui->listWidget_userList->addItem(addUser.getUsername());
    }
}
