/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 28/01/2019
 * Last modify date: 31/01/2019
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
 * Last modify date: 28/01/2019
 *      Description: Construction function.
 ******************************************************************************/
Serial_definitions::Serial_definitions()
{
    serial_port_databits.insert(5,  "QSerialPort::Data5");
    serial_port_databits.insert(6,  "QSerialPort::Data6");
    serial_port_databits.insert(7,  "QSerialPort::Data7");
    serial_port_databits.insert(8,  "QSerialPort::Data8");
    serial_port_databits.insert(-1, "QSerialPort::UnknownDataBits");

    serial_port_flowcontrol.insert(0,  "QSerialPort::NoFlowControl");
    serial_port_flowcontrol.insert(1,  "QSerialPort::HardwareControl");
    serial_port_flowcontrol.insert(2,  "QSerialPort::SoftwareControl");
    serial_port_flowcontrol.insert(-1, "QSerialPort::UnknownFlowControl");

    serial_port_parity.insert(0 , "QSerialPort::NoParity");
    serial_port_parity.insert(2 , "QSerialPort::EvenParity");
    serial_port_parity.insert(3 , "QSerialPort::OddParity");
    serial_port_parity.insert(4 , "QSerialPort::SpaceParity");
    serial_port_parity.insert(5 , "QSerialPort::MarkParity");
    serial_port_parity.insert(-1, "QSerialPort::UnknownParity");

    serial_port_stopbits.insert(1 , "QSerialPort::OneStop");
    serial_port_stopbits.insert(3 , "QSerialPort::OneAndHalfStop");
    serial_port_stopbits.insert(2 , "QSerialPort::TwoStop");
    serial_port_stopbits.insert(-1, "QSerialPort::UnknownStopBits");
}

/******************************************************************************
 *             Name: getDataBits
 *      Function ID: 300
 *      Create date: 28/01/2019
 * Last modify date: 28/01/2019
 *      Description: Get serial port databits from marco.
 ******************************************************************************/
QString Serial_definitions::getDataBits(int databits)
{
    return serial_port_databits[databits];
}

/******************************************************************************
 *             Name: getParity
 *      Function ID: 301
 *      Create date: 28/01/2019
 * Last modify date: 28/01/2019
 *      Description: Get serial port parity from marco.
 ******************************************************************************/
QString Serial_definitions::getParity(int parity)
{
    return serial_port_parity[parity];
}

/******************************************************************************
 *             Name: getStopBits
 *      Function ID: 302
 *      Create date: 28/01/2019
 * Last modify date: 28/01/2019
 *      Description: Get serial port stopits from marco.
 ******************************************************************************/
QString Serial_definitions::getStopBits(int stopbits)
{
    return serial_port_stopbits[stopbits];
}

/******************************************************************************
 *             Name: getFlowcontrol
 *      Function ID: 303
 *      Create date: 28/01/2019
 * Last modify date: 28/01/2019
 *      Description: Get serial port flowcontrol from marco
 ******************************************************************************/
QString Serial_definitions::getFlowcontrol(int flowcontrol)
{
    return serial_port_flowcontrol[flowcontrol];
}
