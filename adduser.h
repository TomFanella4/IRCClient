#ifndef ADDUSER_H
#define ADDUSER_H

#include <QDialog>

namespace Ui {
class AddUser;
}

class AddUser : public QDialog
{
    Q_OBJECT

    QString username;
    QString password;

public:
    QString getUsername();
    QString getPassword();
    explicit AddUser(QWidget *parent = 0);
    ~AddUser();

private slots:
    void on_pushButton_ok_clicked();

private:
    Ui::AddUser *ui;
};

#endif // ADDUSER_H
