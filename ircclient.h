#ifndef IRCCLIENT_H
#define IRCCLIENT_H

#include <QMainWindow>

namespace Ui {
class IRCClient;
}

class IRCClient : public QMainWindow
{
    Q_OBJECT

    QString host;
    int port;

    QString cUsername;
    QString cPassword;

public:
    explicit IRCClient(QWidget *parent = 0);

    QString getHost();
    int getPort();

    void setHost(QString h);
    void setPort(int p);

    QString getCUsername();
    QString getCPassword();

    void setCUsername(QString u);
    void setCPassword(QString p);

    ~IRCClient();

private slots:
    void on_Button_addUser_clicked();

    void on_Button_addRoom_clicked();

private:
    Ui::IRCClient *ui;
};

#endif // IRCCLIENT_H
