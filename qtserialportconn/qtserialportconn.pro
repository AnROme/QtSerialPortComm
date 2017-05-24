#-------------------------------------------------
#
# Project created by QtCreator 2017-05-20T17:04:59
#
#-------------------------------------------------

QT       += core gui


greaterThan(QT_MAJOR_VERSION, 4):

QT += widgets serialport


TARGET = SerialPortComm
TEMPLATE = app


SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/serialPortComm.cpp

HEADERS  += src/mainwindow.h \
    src/serialPortComm.h\
    src/arrayTemp.h

FORMS    += src/mainwindow.ui

