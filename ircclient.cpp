#include "ircclient.h"
#include "ui_ircclient.h"
#include "adduser.h"

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
    if (addUser.getUsername() != "" || addUser.getPassword() != "")
        ui->listWidget_userList->addItem(addUser.getUsername() + " " + addUser.getPassword());
}
