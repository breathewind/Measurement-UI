/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 27/02/2019
 * Last modify date: 27/02/2019
 *      Description: MCP41010 driver configuration.
 ******************************************************************************/
#ifndef MCP41010_CONFIGURATION_H
#define MCP41010_CONFIGURATION_H
#include "Arduino.h"
#include <SPI.h>

#define MCP41010_SPI_FREQUENCY 10000
#define MCP41010_SPI_BITS      8
#define MCP41010_SPI_MODE      SPI_MODE0

#define MCP41010_WIPER_RESISTANCE 52.0
#define MCP41010_MAX_RESISTANCE   10000.0

#define MCP41010_MOSI_PIN 11 // MOSI signal connected to pin 11
#define MCP41010_SCK_PIN  13 // SCK signal connected to pin 13
#define MCP41010_CS_PIN   5  // Chip Selected signal connected to pin 5

//#define MCP41010_DEBUG
//#define MCP41010_DEBUG_SELF_TEST

#endif //MCP41010_CONFIGURATION_H
