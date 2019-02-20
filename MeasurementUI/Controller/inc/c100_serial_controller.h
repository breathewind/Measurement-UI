/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 28/01/2019
 * Last modify date: 31/01/2019
 *      Description: Serial port controller.
 *
 *  Function Number: 0XX - Normal logic functions
 *                   3XX - User level functions
 *                   7XX - Slot functions
 *                   8XX - Get/set funcions
 *                   9XX - Debug functions
 ******************************************************************************/
#ifndef C000_SERIAL_CONTROLLER_H
#define C000_SERIAL_CONTROLLER_H
#include <QStringList>
#include <QObject>
#include <QtSerialPort/QSerialPortInfo>
#include <QtSerialPort/QSerialPort>
#include <QTimer>

#define SERIAL_CONTROLLER_DEBUG

#define SERIAL_CONTROLLER_READ_TIMEOUT 100

#define SERIAL_CONTROLLER_WRITE_ERROR    -1
#define SERIAL_CONTROLLER_WRITE_TIME_OUT -2

#ifdef SERIAL_CONTROLLER_DEBUG
#include <QDebug>
#endif
class Serial_Controller : public QObject
{
    Q_OBJECT
public:
    /** Function 000: Construction function. */
    Serial_Controller();

    /** Function 300: Get the names of all serial ports currently connected. */
    QStringList getSerial_port_name();

    /** Function 301: Start serial communication. */
    bool startSerial();
    /** Function 302: Close serial communication. */
    void closeSerial();
    /** Function 303: Send command via serial communication. */
    qint64 writeCommand(QString command);
    /** Function 304: Read data via serial communication. */
    QString readData();

    /** Function 800: Set name of serial port. */
    void setPortName(QString portName);
    /** Function 801: Get name of serial port. */
    QString getPortName() const;

    /** Function 802: Set baudrate of serial port. */
    void setBaudRate(qint32 baudRate);
    /** Function 803: Get baudrate of serial port. */
    qint32 getBaudRate() const;

    /** Function 804: Set parity of serial port. */
    void setParity(QSerialPort::Parity parity);
    /** Function 805: Get parity of serial port. */
    QSerialPort::Parity getParity() const;

    /** Function 806: Set data bits of serial port. */
    void setDataBits(QSerialPort::DataBits dataBits);
    /** Function 807: Get data bits of serial port. */
    QSerialPort::DataBits getDataBits() const;

    /** Function 808: Set stop bits of serial port. */
    void setStopBits(QSerialPort::StopBits stopBits);
    /** Function 809: Get stop bits of serial port. */
    QSerialPort::StopBits getStopBits() const;

    /** Function 810: Set flow control of serial port. */
    void setFlowControl(QSerialPort::FlowControl flowControl);
    /** Function 811: Get flow control of serial port. */
    QSerialPort::FlowControl getFlowControl() const;

    /** Function 812: Get Serial port. */
    QSerialPort *getSerial_port();

public slots:
    /** Function 700: Handler for dealing with received data from serial port. */
    void handleReceived_Data();
#ifdef SERIAL_CONTROLLER_DEBUG
    /** Function 900: Handler for received data timeout from serial port.
     *    - Debug function: Print received data from serial communiction.  */
    void handleTimeout(QString data);
#endif

private:
    QSerialPort* _serial_port;

    QString _portName;
    qint32 _baudRate;
    QSerialPort::Parity _parity;
    QSerialPort::DataBits _dataBits;
    QSerialPort::StopBits _stopBits;
    QSerialPort::FlowControl _flowControl;

    QString _databuffer;
    bool _data_received_flag;
signals:
    void data_received(QString data);
};

#endif // C000_SERIAL_CONTROLLER_H
