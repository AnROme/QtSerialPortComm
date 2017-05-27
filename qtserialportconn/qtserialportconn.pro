#-------------------------------------------------
#
# Project created by QtCreator 2017-05-20T17:04:59
#
#-------------------------------------------------

TEMPLATE = app
TARGET = SerialPortComm

QT += core gui widgets

CONFIG += serialport

SOURCES += src/main.cpp\
    src/mainwindow.cpp \
    src/serialPortComm.cpp

HEADERS  += src/mainwindow.h \
    src/serialPortComm.h\
    src/arrayTemp.h

FORMS += src/mainwindow.ui
