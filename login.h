#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

    QString loginH;
    int loginPort;
    QString loginU;
    QString loginP;

public:
    explicit Login(QWidget *parent = 0);

    QString getLoginH();
    int getLoginPort();
    QString getLoginU();
    QString getLoginP();

    ~Login();

private slots:
    void on_pushButton_ok_clicked();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
