#-------------------------------------------------
#
# Project created by QtCreator 2015-04-21T14:19:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IRCClient
TEMPLATE = app


SOURCES += main.cpp\
        ircclient.cpp \
    adduser.cpp

HEADERS  += ircclient.h \
    adduser.h

FORMS    += ircclient.ui \
    adduser.ui
