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
#ifndef C900_SERIAL_DEFINITIONS_H
#define C900_SERIAL_DEFINITIONS_H
#include <QHash>

class Serial_definitions
{
public:
    /** Function 000: Construction function. */
    Serial_definitions();

    /** Function 300: Get serial port databits from marco. */
    QString getDataBits(int databits);
    /** Function 301: Get serial port parity from marco. */
    QString getParity(int parity);
    /** Function 302: Get serial port stopits from marco. */
    QString getStopBits(int stopbits);
    /** Function 303: Get serial port flowcontrol from marco. */
    QString getFlowcontrol(int flowcontrol);

private:
    QHash<int, QString> serial_port_databits;
    QHash<int, QString> serial_port_parity;
    QHash<int, QString> serial_port_stopbits;
    QHash<int, QString> serial_port_flowcontrol;
};

#endif // C900_SERIAL_DEFINITIONS_H
