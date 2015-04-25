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

    loginH = ui->plainTextEdit_host->toPlainText();
    loginPort = ui->plainTextEdit_port->toPlainText().toInt();
    loginU = ui->plainTextEdit_username->toPlainText();
    loginP = ui->plainTextEdit_password->toPlainText();

    close();
}

QString Login::getLoginH() {
    return loginH;
}

int Login::getLoginPort() {
    return loginPort;
}

QString Login::getLoginU() {
    return loginU;
}

QString Login::getLoginP() {
    return loginP;
}
