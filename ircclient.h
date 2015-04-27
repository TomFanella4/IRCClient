#ifndef IRCCLIENT_H
#define IRCCLIENT_H

#include <QMainWindow>
#include <QListWidgetItem>

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
    void on_Button_createRoom_clicked();

    void initializeUser();
    void refreshUserList(char * room);
    void refreshMessageList(char * room);
    void refreshRoomList();

    void on_Button_sendMessage_clicked();

    void on_listWidget_roomList_itemClicked(QListWidgetItem *item);

    void on_Button_refreshList_clicked();

private:
    Ui::IRCClient *ui;
};

#endif // IRCCLIENT_H
