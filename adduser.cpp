#include "adduser.h"
#include "ui_adduser.h"

AddUser::AddUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddUser)
{
    ui->setupUi(this);
}

AddUser::~AddUser()
{
    delete ui;
}

void AddUser::on_pushButton_ok_clicked()
{
    username = ui->plainTextEdit_username->toPlainText();
    password = ui->plainTextEdit_password->toPlainText();

    close();
}

QString AddUser::getUsername() {
    return username;
}

QString AddUser::getPassword() {
    return password;
}
