#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    searchAvailablePorts();

    ui->cb_listBaudRate->addItem(QLatin1String("4800"), QSerialPort::Baud4800);
    ui->cb_listBaudRate->addItem(QLatin1String("9600"), QSerialPort::Baud9600);
    ui->cb_listBaudRate->addItem(QLatin1String("19200"), QSerialPort::Baud19200);
    ui->cb_listBaudRate->addItem(QLatin1String("38400"), QSerialPort::Baud38400);
    ui->cb_listBaudRate->addItem(QLatin1String("57600"), QSerialPort::Baud57600);
    ui->cb_listBaudRate->addItem(QLatin1String("115200"), QSerialPort::Baud115200);

    connect(ui->pushButton_open, SIGNAL(clicked()), this, SLOT(tryOpenPort()));
    connect(this, SIGNAL(openPort(QString, QSerialPort::BaudRate)), &serialPort, SLOT(portOpen(QString, QSerialPort::BaudRate)));
    connect(this, SIGNAL(closePort()), &serialPort, SLOT(portClose()));

    connect(ui->pushButton_send, SIGNAL(clicked()), this, SLOT(createMessage()));
    connect(this, SIGNAL(sendMessage(QByteArray&)), &serialPort, SLOT(portWrite(QByteArray&)));
    connect(&serialPort, SIGNAL(logMessage(QString)), this, SLOT(logMessage(QString)));
    connect(&serialPort, SIGNAL(portOpened(bool)), this, SLOT(readyForConnect(bool)));
    connect(&serialPort, SIGNAL(messageRecieved(QByteArray)), this, SLOT(printRecievedMsg(QByteArray)));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::searchAvailablePorts()
{
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        ui->cb_listPorts->addItem(info.portName());
    }
}

void MainWindow::tryOpenPort(){

    int rate = ui->cb_listBaudRate->currentText().toInt();
    QSerialPort::BaudRate selectedBaudrate = static_cast<QSerialPort::BaudRate>(rate);
    emit openPort(ui->cb_listPorts->currentText(), selectedBaudrate);
}


void MainWindow::readyForConnect(bool state){
   if(state){

    disconnect(ui->pushButton_open, SIGNAL(clicked()), this, SLOT(tryOpenPort()));
    connect(ui->pushButton_open, SIGNAL(clicked()), this, SLOT(closeSerialPort()));
    ui->pushButton_open->setText("Close");
    }
   else
   {
       disconnect(ui->pushButton_open, SIGNAL(clicked()), this, SLOT(closeSerialPort()));
       connect(ui->pushButton_open, SIGNAL(clicked()), this, SLOT(tryOpenPort()));
       ui->pushButton_open->setText("Open");
       //ui->pushButton_send->setEnabled(false);
   }
    ui->pushButton_send->setEnabled(state);
}


void MainWindow::closeSerialPort(){
    emit closePort();
}

void MainWindow::printRecievedMsg(QByteArray mes){
    ui->textEdit_messageRcv->append(mes);\
}

void MainWindow::logMessage(QString msg){
    ui->textEdit_workMessages->append(msg);
}

void MainWindow::createMessage(){

    QByteArray msg = ui->textEdit_messageForSend->toPlainText().toUtf8();
    emit sendMessage(msg);
}

