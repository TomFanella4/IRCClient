#ifndef ADDROOM_H
#define ADDROOM_H

#include <QDialog>

namespace Ui {
class AddRoom;
}

class AddRoom : public QDialog
{
    Q_OBJECT

public:
    explicit AddRoom(QWidget *parent = 0);
    ~AddRoom();

private:
    Ui::AddRoom *ui;
};

#endif // ADDROOM_H
