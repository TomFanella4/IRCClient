#ifndef IRCCLIENT_H
#define IRCCLIENT_H

#include <QMainWindow>

#include "mytcpsocket.h"

namespace Ui {
class IRCClient;
}

class IRCClient : public QMainWindow
{
    Q_OBJECT

    char * host;
    int port;

    char * cUsername;
    char * cPassword;

    MyTcpSocket socket;

public:
    explicit IRCClient(QWidget *parent = 0);

    char * getHost();
    int getPort();

    void setHost(char * h);
    void setPort(int p);

    char * getCUsername();
    char * getCPassword();

    void setCUsername(char * u);
    void setCPassword(char * p);

    ~IRCClient();

private slots:
    void on_Button_addUser_clicked();

    void on_Button_addRoom_clicked();
    void refreshUserList();

private:
    Ui::IRCClient *ui;
};

#endif // IRCCLIENT_H
