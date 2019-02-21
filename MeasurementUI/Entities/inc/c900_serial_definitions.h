/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 28/01/2019
 * Last modify date: 21/02/2019
 *      Description: Serial port debug definitions.
 *
 *  Function Number: 0XX - Normal logic functions
 *                   3XX - User level functions
 *                   7XX - Slot functions
 *                   8XX - Get/set funcions
 *                   9XX - Debug functions
 ******************************************************************************/
#ifndef C900_SERIAL_DEFINITIONS_H
#define C900_SERIAL_DEFINITIONS_H

//#define USE_HASH

#include <QHash>
#include <QtSerialPort/QSerialPortInfo>
#include <QtSerialPort/QSerialPort>

class Serial_definitions
{
public:
    /** Function 000: Construction function. */
    Serial_definitions();

    /** Function 600: Get the names of all serial ports currently connected. */
    static QStringList getSerial_port_name();

    /** Function 800: Get serial port databits string from marco. */
    QString getDataBits_string(int databits);
    /** Function 801: Get serial port parity string from marco. */
    QString getParity_string(int parity);
    /** Function 802: Get serial port stopits string from marco. */
    QString getStopBits_string(int stopbits);
    /** Function 803: Get serial port flowcontrol string from marco. */
    QString getFlowcontrol_string(int flowcontrol);
    /** Function 804: Get serial port baudrate string from marco. */
    QString getBaudrate_string(qint32 baudrate);

    /** Function 810: Get serial port databits marco from string. */
    int getDataBits(QString databits_string);
    /** Function 811: Get serial port parity marco from string. */
    int getParity(QString parity_string);
    /** Function 812: Get serial port stopits marco from string. */
    int getStopBits(QString stopbits_string);
    /** Function 813: Get serial port flowcontrol marco from string. */
    int getFlowcontrol(QString flowcontrol_string);
    /** Function 814: Get serial port baudrate marco from string. */
    qint32 getBaudrate(QString baudrate_string);

    /** Function 820: Get list of databits strings. */
    QStringList getDataBits_list();
    /** Function 821: Get list of parity strings. */
    QStringList getParity_list();
    /** Function 822: Get list of stopits strings. */
    QStringList getStopBits_list();
    /** Function 823: Get list of flowcontrol strings. */
    QStringList getFlowcontrol_list();
    /** Function 824: Get list of baudrate strings. */
    QStringList getBaudrate_list();

private:
#ifdef USE_HASH
    QHash<int, QString> _serial_port_databits;
    QHash<int, QString> _serial_port_parity;
    QHash<int, QString> _serial_port_stopbits;
    QHash<int, QString> _serial_port_flowcontrol;
    QHash<qint32, QString> _serial_port_baudrate;
#else
    QStringList _baudrate_string;
    QStringList _databits_string;
    QStringList _stopbits_string;
    QStringList _parity_string;
    QStringList _flowcontrol_string;

    QList<qint32> _baudrate;
    QList<int> _databits;
    QList<int> _stopbits;
    QList<int> _parity;
    QList<int> _flowcontrol;
#endif


};

#endif // C900_SERIAL_DEFINITIONS_H
