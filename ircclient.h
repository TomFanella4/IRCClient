#ifndef IRCCLIENT_H
#define IRCCLIENT_H

#include <QMainWindow>

namespace Ui {
class IRCClient;
}

class IRCClient : public QMainWindow
{
    Q_OBJECT

public:
    explicit IRCClient(QWidget *parent = 0);
    ~IRCClient();

private slots:
    void on_Button_addUser_clicked();

private:
    Ui::IRCClient *ui;
};

#endif // IRCCLIENT_H
