/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 28/01/2019
 * Last modify date: 04/03/2019
 *      Description: Serial port controller.
 *
 *  Function Number: 0XX - Normal logic functions
 *                   3XX - User level functions
 *                   7XX - Slot functions
 *                   8XX - Get/set funcions
 *                   9XX - Debug functions
 ******************************************************************************/
#include "../inc/c100_serial_controller.h"

/******************************************************************************
 *             Name: Serial_Controller
 *      Function ID: 000
 *      Create date: 28/01/2019
 * Last modify date: 04/03/2019
 *      Description: Construction function.
 ******************************************************************************/
Serial_Controller::Serial_Controller(int controller_type)
{
    _serial_port = new QSerialPort();
    _data_received_flag = false;
    switch(controller_type){
    case SERIAL_CONTROLLER_TYPE_DMM:
        connect(_serial_port, SIGNAL(readyRead()), this, SLOT(handleReceived_Data()));
        break;
    case SERIAL_CONTROLLER_TYPE_BC:
        connect(_serial_port, SIGNAL(readyRead()), this, SLOT(slot_received_data()));
        break;
    default:
        break;
    }

#ifdef SERIAL_CONTROLLER_DEBUG
    connect(this, SIGNAL(data_received(QString)), this, SLOT(handleTimeout(QString)));
#endif
}

/******************************************************************************
 *             Name: getSerial_port_name
 *      Function ID: 300
 *      Create date: 28/01/2019
 * Last modify date: 28/01/2019
 *      Description: Get the names of all serial ports currently connected.
 ******************************************************************************/
QStringList Serial_Controller::getSerial_port_name()
{
    QStringList port_name;
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()){
        port_name << info.portName();
    }
    return port_name;
}

/******************************************************************************
 *             Name: startSerial
 *      Function ID: 301
 *      Create date: 28/01/2019
 * Last modify date: 29/01/2019
 *      Description: Start serial communication.
 ******************************************************************************/
bool Serial_Controller::startSerial()
{
    _serial_port->setPortName(_portName);
    _serial_port->setBaudRate(_baudRate);
    _serial_port->setParity(_parity);
    _serial_port->setDataBits(_dataBits);
    _serial_port->setStopBits(_stopBits);
    _serial_port->setFlowControl(_flowControl);

    return _serial_port->open(QIODevice::ReadWrite);
}

/******************************************************************************
 *             Name: closeSerial
 *      Function ID: 302
 *      Create date: 28/01/2019
 * Last modify date: 29/01/2019
 *      Description: Close serial communication.
 ******************************************************************************/
void Serial_Controller::closeSerial(){
    _serial_port->close();
}

/******************************************************************************
 *             Name: writeDMM_command
 *      Function ID: 303
 *      Create date: 28/01/2019
 * Last modify date: 25/02/2019
 *      Description: Send command via serial communication.
 *
 * @return - Number greater than -1: the number of bytes that were actually
 *             written;
 *           SERIAL_CONTROLLER_WRITE_ERROR(-1): An error occurred during write
 *             operation;
 *           SERIAL_CONTROLLER_WRITE_TIME_OUT(-2): Write operation timed out.
 ******************************************************************************/
qint64 Serial_Controller::writeDMM_command(QString command,  bool command_feedback)
{
    qint64 ret = 0;
    QByteArray ba = command.toLocal8Bit();
    ba.append('\n');
    const char *c_command = ba.data();
#ifdef SERIAL_CONTROLLER_DEBUG
    qDebug() << c_command;
#endif
    ret = _serial_port->write(c_command, ba.length());
/** For the lower Qt version */
    if(!_serial_port->waitForBytesWritten(0)){
        ret = -2;
    }
    _databuffer.clear();
    if(ret > 0 && command_feedback){
        _data_received_flag = true;
    }
    return ret;
}

/******************************************************************************
 *             Name: readData
 *      Function ID: 304
 *      Create date: 28/01/2019
 * Last modify date: 29/01/2019
 *      Description: Read data via serial communication.
 ******************************************************************************/
QString Serial_Controller::readData()
{
    return QString::fromStdString(_serial_port->readAll().toStdString());
}

/******************************************************************************
 *             Name: sendMCU_Value
 *      Function ID: 305
 *      Create date: 27/02/2019
 * Last modify date: 27/02/2019
 *      Description: Send a value to control digital potentiometer via serial
 *                   communication.
 ******************************************************************************/
qint64 Serial_Controller::sendMCU_Value(char value)
{
    qint64 ret = 0;
    char command = static_cast<char>(MEASUREMENTUI_SEND_VALUE_COMMAND);
#ifdef SERIAL_CONTROLLER_DEBUG
    qDebug() << command;
#endif
    ret += _serial_port->write(&command, 1);

    command = value;
#ifdef SERIAL_CONTROLLER_DEBUG
    qDebug() << command;
#endif
    ret += _serial_port->write(&command, 1);

    return ret;
}

/******************************************************************************
 *             Name: readVoltage
 *      Function ID: 306
 *      Create date: 04/03/2019
 * Last modify date: 04/03/2019
 *      Description: Read voltage via serial communication.
 ******************************************************************************/
qint64 Serial_Controller::readVoltage()
{
    char command = static_cast<char>(MEASUREMENTUI_READ_VOLTAGE_COMMAND);

    return _serial_port->write(&command, 1);
}


/******************************************************************************
 *             Name: MCP41010_calculate_Ohm
 *      Function ID: 390
 *      Create date: 27/02/2019
 * Last modify date: 27/02/2019
 *      Description: Calculate Ohm-value by set-value. ( Set-value in direct
 *                   proportion to Ohm-value)
 *
 *  @param set_value: The set-value to be calculated. (between 0 to 255)
 *  @return value not small than 0: The Ohm-value calculated by set-valuer.
 *          MCP41010_NEGATIVE_OHM_VALUE(-1): The Ohm value is negative.
 *          MCP41010_LESS_THEN_WIPER_RESISTANCE(-2): The Ohm value is less than
 *            wiper resistance.
 ******************************************************************************/
int Serial_Controller::MCP41010_calculate_Ohm(uint8_t set_value)
{
    double Ohm_value = set_value/255.0 * MCP41010_MAX_RESISTANCE + MCP41010_WIPER_RESISTANCE;
    return static_cast<int>(Ohm_value);
}

/******************************************************************************
 *             Name: receivedData_Handler
 *      Function ID: 700
 *      Create date: 29/01/2019
 * Last modify date: 31/01/2019
 *      Description: Handler for dealing with received data from serial port.
 ******************************************************************************/
void Serial_Controller::handleReceived_Data()
{
    if(_data_received_flag){
        _databuffer.append(readData());
        if(_databuffer.contains("\r")){
            _databuffer = _databuffer.split("\r").at(0);
            emit data_received(_databuffer);
            _data_received_flag = false;
        }
    }
}

/******************************************************************************
 *             Name: receivedData_Handler
 *      Function ID: 701
 *      Create date: 04/03/2019
 * Last modify date: 04/03/2019
 *      Description: Slot for receiving data from serial port.
 ******************************************************************************/
void Serial_Controller::slot_received_data()
{
    _databuffer.append(readData());
    if(_databuffer.contains("\r\n")){
        _databuffer = _databuffer.split("\r\n").at(0);
        if(_databuffer.size() > 0)
            emit signal_pure_data_received(_databuffer);
        _databuffer.clear();
    }
}

/******************************************************************************
 *             Name: setPortName
 *      Function ID: 800
 *      Create date: 28/01/2019
 * Last modify date: 28/01/2019
 *      Description: Set name of serial port.
 ******************************************************************************/
void Serial_Controller::setPortName(QString portName)
{
    _portName = portName;
}

/******************************************************************************
 *             Name: getPortName
 *      Function ID: 801
 *      Create date: 28/01/2019
 * Last modify date: 28/01/2019
 *      Description: Get name of serial port.
 ******************************************************************************/
QString Serial_Controller::getPortName() const
{
    return _portName;
}

/******************************************************************************
 *             Name: setBaudRate
 *      Function ID: 802
 *      Create date: 28/01/2019
 * Last modify date: 28/01/2019
 *      Description: Set baudrate of serial port.
 ******************************************************************************/
void Serial_Controller::setBaudRate(qint32 baudRate)
{
    _baudRate = baudRate;
}

/******************************************************************************
 *             Name: getBaudRate
 *      Function ID: 803
 *      Create date: 28/01/2019
 * Last modify date: 28/01/2019
 *      Description: Get baudrate of serial port.
 ******************************************************************************/
qint32 Serial_Controller::getBaudRate() const
{
    return _baudRate;
}

/******************************************************************************
 *             Name: setParity
 *      Function ID: 804
 *      Create date: 28/01/2019
 * Last modify date: 28/01/2019
 *      Description: Set parity of serial port.
 ******************************************************************************/
void Serial_Controller::setParity(QSerialPort::Parity parity)
{
    _parity = parity;
}

/******************************************************************************
 *             Name: getParity
 *      Function ID: 805
 *      Create date: 28/01/2019
 * Last modify date: 28/01/2019
 *      Description: Get parity of serial port.
 ******************************************************************************/
QSerialPort::Parity Serial_Controller::getParity() const
{
    return _parity;
}

/******************************************************************************
 *             Name: setDataBits
 *      Function ID: 806
 *      Create date: 28/01/2019
 * Last modify date: 28/01/2019
 *      Description: Set data bits of serial port.
 ******************************************************************************/
void Serial_Controller::setDataBits(QSerialPort::DataBits dataBits)
{
    _dataBits = dataBits;
}

/******************************************************************************
 *             Name: getDataBits
 *      Function ID: 807
 *      Create date: 28/01/2019
 * Last modify date: 28/01/2019
 *      Description: Get data bits of serial port.
 ******************************************************************************/
QSerialPort::DataBits Serial_Controller::getDataBits() const
{
    return _dataBits;
}

/******************************************************************************
 *             Name: setStopBits
 *      Function ID: 808
 *      Create date: 28/01/2019
 * Last modify date: 28/01/2019
 *      Description: Set stop bits of serial port.
 ******************************************************************************/
void Serial_Controller::setStopBits(QSerialPort::StopBits stopBits)
{
    _stopBits = stopBits;
}

/******************************************************************************
 *             Name: getStopBits
 *      Function ID: 809
 *      Create date: 28/01/2019
 * Last modify date: 28/01/2019
 *      Description: Get stop bits of serial port.
 ******************************************************************************/
QSerialPort::StopBits Serial_Controller::getStopBits() const
{
    return _stopBits;
}

/******************************************************************************
 *             Name: setFlowControl
 *      Function ID: 810
 *      Create date: 28/01/2019
 * Last modify date: 28/01/2019
 *      Description: Set flow control of serial port.
 ******************************************************************************/
void Serial_Controller::setFlowControl(QSerialPort::FlowControl flowControl)
{
    _flowControl = flowControl;
}

/******************************************************************************
 *             Name: getFlowControl
 *      Function ID: 811
 *      Create date: 28/01/2019
 * Last modify date: 28/01/2019
 *      Description: Get flow control of serial port.
 ******************************************************************************/
QSerialPort::FlowControl Serial_Controller::getFlowControl() const
{
    return _flowControl;
}

/******************************************************************************
 *             Name: getSerial_port
 *      Function ID: 812
 *      Create date: 28/01/2019
 * Last modify date: 29/01/2019
 *      Description: Get Serial port.
 ******************************************************************************/
QSerialPort *Serial_Controller::getSerial_port()
{
    return _serial_port;
}

#ifdef SERIAL_CONTROLLER_DEBUG
/******************************************************************************
 *             Name: handleTimeout
 *      Function ID: 900
 *      Create date: 29/01/2019
 * Last modify date: 31/01/2019
 *      Description: Handler for received data timeout from serial port.
 *                   Debug function: Print received data from serial
 *                   communiction.
 ******************************************************************************/
void Serial_Controller::handleTimeout(QString data)
{
//    qDebug() << data;
    qDebug() << QString("Data received: %1.").arg(data.toDouble());
}
#endif



