#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

    char * loginH;
    int loginPort;
    char * loginU;
    char * loginP;

public:
    explicit Login(QWidget *parent = 0);

    char * getLoginH();
    int getLoginPort();
    char * getLoginU();
    char * getLoginP();

    ~Login();

private slots:
    void on_pushButton_ok_clicked();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
