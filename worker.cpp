#include "worker.h"

Worker::Worker()
{

}

Worker::~Worker()
{

}

void Worker::process() {
    char * currentRoom = strdup(cRoom);

    while (strcmp(currentRoom, cRoom) == 0) {
        client->refreshMessageList(cRoom);
        usleep(2*1000*1000);
        cRoom = client->getRoom();
    }

    emit finished();
}

void Worker::setRoom(char * r) {
    cRoom = r;
}

void Worker::setIRC(IRCClient * c) {
    client = c;
}
