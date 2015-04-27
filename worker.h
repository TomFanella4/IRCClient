#ifndef WORKER_H
#define WORKER_H
#include <QtCore>
#include "ircclient.h"
#include "stdlib.h"

class Worker : public QThread {
    Q_OBJECT

    char * cRoom;
    IRCClient * client;

public:
    Worker();
    ~Worker();

public slots:
    void process();
    void setRoom(char * r);
    void setIRC (IRCClient * c);

signals:
    void finished();
    void error(QString err);
};

#endif // WORKER_H
