/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 20/02/2019
 * Last modify date: 27/02/2019
 *      Description: Global parameters related to serial port.
 ******************************************************************************/
#ifndef H001_SERIAL_PARAMETERS_H
#define H001_SERIAL_PARAMETERS_H

#define MEASUREMENTUI_DMM_BAUDRATE       "9600 baud"
#define MEASUREMENTUI_DMM_PARITY         "No Parity"
#define MEASUREMENTUI_DMM_DATABITS       "8 bits"
#define MEASUREMENTUI_DMM_STOPBITS       "2 bit"
#define MEASUREMENTUI_DMM_FLOWCONTROL    "No Flow Control"
//#define MEASUREMENTUI_DMM_FLOWCONTROL    "Hardware Control"

#define MEASUREMENTUI_BC_BAUDRATE      "115200 baud"
#define MEASUREMENTUI_BC_PARITY        "No Parity"
#define MEASUREMENTUI_BC_DATABITS      "8 bits"
#define MEASUREMENTUI_BC_STOPBITS      "1 bit"
#define MEASUREMENTUI_BC_FLOWCONTROL   "No Flow Control"

#define MEASUREMENTUI_INDEX_BAUDRATE    0
#define MEASUREMENTUI_INDEX_DATABITS    1
#define MEASUREMENTUI_INDEX_STOPBITS    2
#define MEASUREMENTUI_INDEX_PARITY      3
#define MEASUREMENTUI_INDEX_FLOWCONTROL 4
#define MEASUREMENTUI_INDEX_PORT        5

#define MEASUREMENTUI_VOLTAGE_COMMAND ":MEAS:VOLT:DC?"

#include "Entities/inc/c900_serial_definitions.h"

#define MEASUREMENTUI_SEND_VALUE_COMMAND 200U
#define MCP41010_WIPER_RESISTANCE 52.0
#define MCP41010_MAX_RESISTANCE   10000.0

static Serial_definitions __serial_definitions;

#endif // H001_SERIAL_PARAMETERS_H
