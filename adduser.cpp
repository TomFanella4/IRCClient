#include "adduser.h"
#include "ui_adduser.h"

QString username;
QString password;

AddUser::AddUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddUser)
{
    ui->setupUi(this);
}

AddUser::~AddUser()
{
    username = "";
    password = "";
    delete ui;
}

void AddUser::on_pushButton_ok_clicked()
{
    username = ui->plainTextEdit_username->toPlainText();
    password = ui->plainTextEdit_password->toPlainText();
    this->close();
}

QString AddUser::getUsername() {
    return username;
}

QString AddUser::getPassword() {
    return password;
}
