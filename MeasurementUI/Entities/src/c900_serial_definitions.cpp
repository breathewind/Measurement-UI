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
#include "../inc/c900_serial_definitions.h"

/******************************************************************************
 *             Name: Serial_definitions
 *      Function ID: 000
 *      Create date: 28/01/2019
 * Last modify date: 21/02/2019
 *      Description: Construction function.
 ******************************************************************************/
Serial_definitions::Serial_definitions()
{
#ifdef USE_HASH
    _serial_port_databits.insert(5,  "5 bits");
    _serial_port_databits.insert(6,  "6 bits");
    _serial_port_databits.insert(7,  "7 bits");
    _serial_port_databits.insert(8,  "8 bits");

    _serial_port_flowcontrol.insert(0,  "QSerialPort::NoFlowControl");
    _serial_port_flowcontrol.insert(1,  "QSerialPort::HardwareControl");
    _serial_port_flowcontrol.insert(2,  "QSerialPort::SoftwareControl");

    _serial_port_parity.insert(0, "No Parity");
    _serial_port_parity.insert(2, "Even Parity");
    _serial_port_parity.insert(3, "Odd Parity");
    _serial_port_parity.insert(4, "Space Parity");
    _serial_port_parity.insert(5, "Mark Parity");

    _serial_port_stopbits.insert(1 , "1 bit");
    _serial_port_stopbits.insert(3 , "1.5 bits");
    _serial_port_stopbits.insert(2 , "2 bits");

    _serial_port_baudrate.insert(1200,   "1200 baud");
    _serial_port_baudrate.insert(2400,   "2400 baud");
    _serial_port_baudrate.insert(4800,   "4800 baud");
    _serial_port_baudrate.insert(9600,   "9600 baud");
    _serial_port_baudrate.insert(19200,  "19200 baud");
    _serial_port_baudrate.insert(38400,  "38400 baud");
    _serial_port_baudrate.insert(57600,  "57600 baud");
    _serial_port_baudrate.insert(115200, "115200 baud");
#else
    _baudrate.append(QSerialPort::Baud1200);
    _baudrate.append(QSerialPort::Baud2400);
    _baudrate.append(QSerialPort::Baud4800);
    _baudrate.append(QSerialPort::Baud9600);
    _baudrate.append(QSerialPort::Baud19200);
    _baudrate.append(QSerialPort::Baud38400);
    _baudrate.append(QSerialPort::Baud57600);
    _baudrate.append(QSerialPort::Baud115200);

    _baudrate_string.append("1200 baud");
    _baudrate_string.append("2400 baud");
    _baudrate_string.append("4800 baud");
    _baudrate_string.append("9600 baud");
    _baudrate_string.append("19200 baud");
    _baudrate_string.append("38400 baud");
    _baudrate_string.append("57600 baud");
    _baudrate_string.append("115200 baud");

    _databits.append(QSerialPort::Data5);
    _databits.append(QSerialPort::Data6);
    _databits.append(QSerialPort::Data7);
    _databits.append(QSerialPort::Data8);

    _databits_string.append("5 bits");
    _databits_string.append("6 bits");
    _databits_string.append("7 bits");
    _databits_string.append("8 bits");

    _stopbits.append(QSerialPort::OneStop);
    _stopbits.append(QSerialPort::OneAndHalfStop);
    _stopbits.append(QSerialPort::TwoStop);

    _stopbits_string.append("1 bit");
    _stopbits_string.append("1.5 bit");
    _stopbits_string.append("2 bit");

    _parity.append(QSerialPort::NoParity);
    _parity.append(QSerialPort::EvenParity);
    _parity.append(QSerialPort::OddParity);
    _parity.append(QSerialPort::SpaceParity);
    _parity.append(QSerialPort::MarkParity);

    _parity_string.append("No Parity");
    _parity_string.append("Even Parity");
    _parity_string.append("Odd Parity");
    _parity_string.append("Space Parity");
    _parity_string.append("Mark Parity");

    _flowcontrol.append(QSerialPort::NoFlowControl);
    _flowcontrol.append(QSerialPort::HardwareControl);
    _flowcontrol.append(QSerialPort::SoftwareControl);

    _flowcontrol_string.append("No Flow Control");
    _flowcontrol_string.append("Hardware Control");
    _flowcontrol_string.append("Software Control");
#endif
}

/******************************************************************************
 *             Name: getSerial_port_name
 *      Function ID: 600
 *      Create date: 21/02/2019
 * Last modify date: 21/02/2019
 *      Description: Get the names of all serial ports currently connected.
 ******************************************************************************/
QStringList Serial_definitions::getSerial_port_name()
{
    QStringList port_names;
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()){
        port_names << info.portName();
    }
    return port_names;
}

/******************************************************************************
 *             Name: getDataBits_string
 *      Function ID: 800
 *      Create date: 28/01/2019
 * Last modify date: 20/02/2019
 *      Description: Get serial port databits string from marco.
 ******************************************************************************/
QString Serial_definitions::getDataBits_string(int databits)
{
#ifdef USE_HASH
    return _serial_port_databits[databits];
#else
    return _databits_string.at(_databits.indexOf(databits));
#endif
}

/******************************************************************************
 *             Name: getParity_string
 *      Function ID: 801
 *      Create date: 28/01/2019
 * Last modify date: 20/02/2019
 *      Description: Get serial port parity string from marco.
 ******************************************************************************/
QString Serial_definitions::getParity_string(int parity)
{
#ifdef USE_HASH
    return _serial_port_parity[parity];
#else
    return _parity_string.at(_parity.indexOf(parity));
#endif
}

/******************************************************************************
 *             Name: getStopBits_string
 *      Function ID: 802
 *      Create date: 28/01/2019
 * Last modify date: 20/02/2019
 *      Description: Get serial port stopits string from marco.
 ******************************************************************************/
QString Serial_definitions::getStopBits_string(int stopbits)
{
#ifdef USE_HASH
    return _serial_port_stopbits[stopbits];
#else
    return _stopbits_string.at(_stopbits.indexOf(stopbits));
#endif
}


/******************************************************************************
 *             Name: getFlowcontrol_string
 *      Function ID: 803
 *      Create date: 28/01/2019
 * Last modify date: 21/02/2019
 *      Description: Get serial port flowcontrol string from marco.
 ******************************************************************************/
QString Serial_definitions::getFlowcontrol_string(int flowcontrol)
{
#ifdef USE_HASH
    return _serial_port_flowcontrol[flowcontrol];
#else
    return _flowcontrol_string.at(_flowcontrol.indexOf(flowcontrol));
#endif
}

/******************************************************************************
 *             Name: getFlowcontrol_string
 *      Function ID: 804
 *      Create date: 20/02/2019
 * Last modify date: 20/02/2019
 *      Description: Get serial port baudrate string from marco.
 ******************************************************************************/
QString Serial_definitions::getBaudrate_string(qint32 baudrate)
{
#ifdef USE_HASH
    return _serial_port_baudrate[baudrate];
#else
    return _baudrate_string.at(_baudrate.indexOf(baudrate));
#endif
}
/******************************************************************************
 *             Name: getDataBits
 *      Function ID: 810
 *      Create date: 20/02/2019
 * Last modify date: 20/02/2019
 *      Description: Get serial port databits marco from string.
 ******************************************************************************/
int Serial_definitions::getDataBits(QString databits_string)
{
#ifdef USE_HASH
    return _serial_port_databits.key(databits_string);
#else
    return _databits.at(_databits_string.indexOf(databits_string));
#endif
}

/******************************************************************************
 *             Name: getParity
 *      Function ID: 811
 *      Create date: 20/02/2019
 * Last modify date: 20/02/2019
 *      Description: Get serial port parity marco from string.
 ******************************************************************************/
int Serial_definitions::getParity(QString parity_string)
{
#ifdef USE_HASH
    return _serial_port_parity.key(parity_string);
#else
    return _parity.at(_parity_string.indexOf(parity_string));
#endif
}

/******************************************************************************
 *             Name: getStopBits
 *      Function ID: 812
 *      Create date: 20/02/2019
 * Last modify date: 20/02/2019
 *      Description: Get serial port stopbits marco from string.
 ******************************************************************************/
int Serial_definitions::getStopBits(QString stopbits_string)
{
#ifdef USE_HASH
    return _serial_port_stopbits.key(stopbits_string);
#else
    return _stopbits.at(_stopbits_string.indexOf(stopbits_string));
#endif
}


/******************************************************************************
 *             Name: getFlowcontrol
 *      Function ID: 813
 *      Create date: 20/02/2019
 * Last modify date: 21/02/2019
 *      Description: Get serial port flowcontrol marco from string.
 ******************************************************************************/
int Serial_definitions::getFlowcontrol(QString flowcontrol_string)
{
#ifdef USE_HASH
    return _serial_port_flowcontrol.key(flowcontrol_string);
#else
    return _flowcontrol.at(_flowcontrol_string.indexOf(flowcontrol_string));
#endif
}

/******************************************************************************
 *             Name: getBaudrate
 *      Function ID: 814
 *      Create date: 20/02/2019
 * Last modify date: 20/02/2019
 *      Description: Get serial port baudrate marco from string.
 ******************************************************************************/
qint32 Serial_definitions::getBaudrate(QString baudrate_string)
{
#ifdef USE_HASH
    return _serial_port_baudrate.key(baudrate_string);
#else
    return _baudrate.at(_baudrate_string.indexOf(baudrate_string));
#endif
}

/******************************************************************************
 *             Name: getDataBits_list
 *      Function ID: 820
 *      Create date: 20/02/2019
 * Last modify date: 20/02/2019
 *      Description: Get list of databits strings.
 ******************************************************************************/
QStringList Serial_definitions::getDataBits_list()
{
#ifdef USE_HASH
    return QStringList(_serial_port_databits.values());
#else
    return _databits_string;
#endif
}

/******************************************************************************
 *             Name: getParity_list
 *      Function ID: 821
 *      Create date: 20/02/2019
 * Last modify date: 20/02/2019
 *      Description: Get list of parity strings.
 ******************************************************************************/
QStringList Serial_definitions::getParity_list()
{
#ifdef USE_HASH
    return QStringList(_serial_port_parity.values());
#else
    return _parity_string;
#endif
}

/******************************************************************************
 *             Name: getStopBits_list
 *      Function ID: 822
 *      Create date: 20/02/2019
 * Last modify date: 20/02/2019
 *      Description: Get list of stopbits strings.
 ******************************************************************************/
QStringList Serial_definitions::getStopBits_list()
{
#ifdef USE_HASH
    return QStringList(_serial_port_stopbits.values());
#else
    return _stopbits_string;
#endif
}

/******************************************************************************
 *             Name: getStopBits_list
 *      Function ID: 823
 *      Create date: 21/02/2019
 * Last modify date: 21/02/2019
 *      Description: Get list of flowcontrol strings.
 ******************************************************************************/
QStringList Serial_definitions::getFlowcontrol_list()
{
#ifdef USE_HASH
    return QStringList(_serial_port_flowcontrol.values());
#else
    return _flowcontrol_string;
#endif
}

/******************************************************************************
 *             Name: getBaudrate_list
 *      Function ID: 824
 *      Create date: 20/02/2019
 * Last modify date: 20/02/2019
 *      Description: Get list of baudrate strings.
 ******************************************************************************/
QStringList Serial_definitions::getBaudrate_list()
{
#ifdef USE_HASH
    return QStringList(_serial_port_baudrate.values());
#else
    return _baudrate_string;
#endif
}
