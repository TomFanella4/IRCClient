#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_ok_clicked()
{

    loginH = strdup(ui->plainTextEdit_host->toPlainText().toStdString().c_str());
    loginPort = ui->plainTextEdit_port->toPlainText().toInt();

    loginU = strdup(ui->plainTextEdit_username->toPlainText().toStdString().c_str());
    loginP = strdup(ui->plainTextEdit_password->toPlainText().toStdString().c_str());

    close();
}

char * Login::getLoginH() {
    return loginH;
}

int Login::getLoginPort() {
    return loginPort;
}

char * Login::getLoginU() {
    return loginU;
}

char * Login::getLoginP() {
    return loginP;
}
