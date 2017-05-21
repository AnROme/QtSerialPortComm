#include "serialPortComm.h"

CSerialPortComm::CSerialPortComm():sizeSendBuf(0){
}

CSerialPortComm::~CSerialPortComm(){

}


void CSerialPortComm::portOpen(QString name, QSerialPort::BaudRate baudrate){

    port.setPortName(name);

    if(port.open(QIODevice::ReadWrite))
    {
        if(port.setBaudRate(baudrate) &&
        port.setDataBits(port.Data8) &&
        port.setParity(port.NoParity) &&
        port.setStopBits(port.OneStop))
        {
            port.clear();
            connect(&port, SIGNAL(readyRead()), this, SLOT(portRead()));
            connect(&port, SIGNAL(bytesWritten(qint64)), this, SLOT(handleBytesWritten(qint64)));
            emit logMessage("Port Opened");
            emit portOpened(true);
        }
    }
    else
        emit logMessage(QString("Can't open the port %1.\nReason: %2\n").arg(name).arg(port.errorString()));
}

void CSerialPortComm::portClose(){
    if(port.isOpen())
    {
        port.close();
        emit portOpened(false);
    }
}


void CSerialPortComm::portRead(){
    rcvBuf.clear();
    rcvBuf.append(port.readAll());
    emit messageRecieved(rcvBuf);
}

void CSerialPortComm::portWrite(QByteArray &message){
    sizeSendBuf = message.size();
    qint64 byteWritten = port.write(message);

    if(byteWritten == -1)
        emit logMessage(QString("Failed to write the data to port %1, error: %2").arg(port.portName()).arg(port.errorString()));
    else if(byteWritten != sizeSendBuf)
        emit logMessage(QString("Failed to write all the data to port %1, error: %2").arg(port.portName()).arg(port.errorString()));
}

void CSerialPortComm::handleBytesWritten(qint64 batchBytes){

    static qint64 countBytesSent = 0;
    countBytesSent += batchBytes;
    if(countBytesSent == sizeSendBuf)
    {
        emit logMessage(QString("Successful write to port message"));
        countBytesSent = 0;
        sizeSendBuf = 0;
    }
}
