#include "addroom.h"
#include "ui_addroom.h"

AddRoom::AddRoom(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddRoom)
{
    ui->setupUi(this);
}

AddRoom::~AddRoom()
{
    delete ui;
}

void AddRoom::on_pushButton_OK_clicked()
{
    roomName = ui->plainTextEdit_name->toPlainText();

    close();
}

QString AddRoom::getRoomName() {
    return roomName;
}
