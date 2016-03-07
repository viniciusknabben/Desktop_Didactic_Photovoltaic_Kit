#-------------------------------------------------
#
# Project created by QtCreator 2013-10-25T00:48:02
#
#-------------------------------------------------
CONFIG += staticlib

QT       += core gui
QT       += network
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = Kit_MPP_TCP
TEMPLATE = app


SOURCES += main.cpp\
        kit.cpp \
    qcustomplot.cpp \
    solarpannel.cpp \
    setaxiswindow.cpp \
    setnetworkwindow.cpp \
    serialterminal.cpp

HEADERS  += kit.h \
    qcustomplot.h \
    solarpannel.h \
    setaxiswindow.h \
    setnetworkwindow.h \
    serialterminal.h

FORMS    += kit.ui \
    setaxiswindow.ui \
    setnetworkwindow.ui \
    serialterminal.ui
