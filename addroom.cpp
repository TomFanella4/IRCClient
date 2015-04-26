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
