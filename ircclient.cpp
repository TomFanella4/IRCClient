#include "ircclient.h"
#include "ui_ircclient.h"

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

}
