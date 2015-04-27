#-------------------------------------------------
#
# Project created by QtCreator 2015-04-21T14:19:37
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IRCClient
TEMPLATE = app


SOURCES += main.cpp\
        ircclient.cpp \
        adduser.cpp \
        login.cpp \
        mytcpsocket.cpp \
        addroom.cpp \
    worker.cpp

HEADERS  += ircclient.h \
            adduser.h \
            login.h \
            mytcpsocket.h \
            addroom.h \
    worker.h

FORMS    += ircclient.ui \
            adduser.ui \
            login.ui \
            addroom.ui
