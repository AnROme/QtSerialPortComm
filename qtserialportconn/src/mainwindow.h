#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "serialPortComm.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void tryOpenPort();
    void readyForConnect(bool state);
    void closeSerialPort();
    void printRecievedMsg(QByteArray mes);
    void logMessage(const QString);
    void createMessage();

private:
    Ui::MainWindow *ui;
    CSerialPortComm serialPort;

    void searchAvailablePorts();

signals:
    void sendMessage(QByteArray&);
    void openPort(QString name, QSerialPort::BaudRate baundrate);
    void closePort();


};

#endif // MAINWINDOW_H
