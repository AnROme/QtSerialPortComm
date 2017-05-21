#ifndef SERIALPORTCOMM_H
#define SERIALPORTCOMM_H


#include <QtSerialPort/qserialport.h>
#include <QtSerialPort/qserialportinfo.h>

class CSerialPortComm: public QObject{
    Q_OBJECT

public:
    CSerialPortComm();
    ~CSerialPortComm();

public slots:
    void portOpen(QString name, QSerialPort::BaudRate baudrate);
    void portClose();
    void portRead();
    void portWrite(QByteArray&);
    void handleBytesWritten(qint64);


private:

    QSerialPort port;
    qint64 sizeSendBuf;
    QByteArray rcvBuf;

signals:
    void portOpened(bool);
    void messageRecieved(QByteArray);
    void logMessage(QString mes);

};

#endif // SERIALPORTCOMM_H
