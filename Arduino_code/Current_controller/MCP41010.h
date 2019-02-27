/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 27/02/2019
 * Last modify date: 27/02/2019
 *      Description: MCP41010 driver.
 ******************************************************************************/
#ifndef MCP41010_H
#define MCP41010_H
#include "MCP41010_Definitions.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Function 000: MCP41010 driver setup. */
void MCP41010_setup();

/** Function 001: Set potentiometer value 0~255. */
void MCP41010_setValue(uint8_t value);
/** Function 002: Shut down potentiometer. */
void MCP41010_shutDown();

/** Function 100: Set potentiometer Ohm value 0~10000. */
int MCP41010_setOhm(int Ohm_value);

/** Function 200: Set PA to PW potentiometer Ohm value 0~10000. */
int MCP41010_setAWOhm(int Ohm_value);
/** Function 201: Set PW to PB potentiometer Ohm value 0~10000. */
int MCP41010_setWBOhm(int Ohm_value);

/** Function 202: Set the value in direct proportion to Ohm value to potentiometer. */
void MCP41010_setProcessing_value(uint8_t value);

/** Function 300: Calculate Ohm-value by set-value. */
int MCP41010_calculate_Ohm(uint8_t set_value);

#ifdef __cplusplus
}
#endif

#endif //MCP41010_H
