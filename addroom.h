#ifndef ADDROOM_H
#define ADDROOM_H

#include <QDialog>

namespace Ui {
class AddRoom;
}

class AddRoom : public QDialog
{
    Q_OBJECT

    QString roomName;

public:
    explicit AddRoom(QWidget *parent = 0);
    QString getRoomName();
    ~AddRoom();

private slots:
    void on_pushButton_OK_clicked();

private:
    Ui::AddRoom *ui;
};

#endif // ADDROOM_H
