/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 27/02/2019
 * Last modify date: 27/02/2019
 *      Description: MCP41010 driver.
 ******************************************************************************/
#include "MCP41010.h"

/******************************************************************************
 *             Name: MCP41010_setup
 *      Function ID: 000
 *      Create date: 27/02/2019
 * Last modify date: 27/02/2019
 *      Description: MCP41010 driver setup.
 ******************************************************************************/
void MCP41010_setup(){
  /** Pin configuration */
  pinMode(MCP41010_MOSI_PIN, OUTPUT);  // configure MOSI_PIN as output
  pinMode(MCP41010_SCK_PIN, OUTPUT);   // configure SCK_PIN as output
  pinMode(MCP41010_CS_PIN, OUTPUT);    // configure CS_PIN as output
   

  /** Open serial communications and wait for port to open: */
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
#ifdef MCP41010_DEBUG
  Serial.println("Serial starts.");
#endif
   
  /** Create SPI device and start it */
  SPI.beginTransaction(SPISettings(MCP41010_SPI_FREQUENCY, MSBFIRST, MCP41010_SPI_MODE));
  SPI.begin();
   
#ifdef MCP41010_DEBUG
  Serial.println("SPI starts.");
#endif

}

/******************************************************************************
 *             Name: MCP41010_setValue
 *      Function ID: 001
 *      Create date: 27/02/2019
 * Last modify date: 27/02/2019
 *      Description: Set potentiometer value 0~255.
 *
 *  @param Ohm_value: The value to be set.
 ******************************************************************************/
void MCP41010_setValue(uint8_t value) {
  digitalWrite(MCP41010_CS_PIN, LOW);  // reset CS_PIN (MCP41010 selected)
  SPI.transfer(MCP41010_COMMAND_BYTE_WRITE_DATA);
  SPI.transfer(value);
  digitalWrite(MCP41010_CS_PIN, HIGH);  // set CS_PIN (MCP41010 unselected)
}

/******************************************************************************
 *             Name: MCP41010_shutDown
 *      Function ID: 002
 *      Create date: 27/02/2019
 * Last modify date: 27/02/2019
 *      Description: Shut down potentiometer.
 ******************************************************************************/
void MCP41010_shutDown() {
  digitalWrite(MCP41010_CS_PIN, LOW);  // reset CS_PIN (MCP41010 selected)
  SPI.transfer(MCP41010_COMMAND_BYTE_WRITE_DATA);
  SPI.transfer(0U);
  digitalWrite(MCP41010_CS_PIN, HIGH);  // set CS_PIN (MCP41010 unselected)
}

/******************************************************************************
 *             Name: MCP41010_setOhm
 *      Function ID: 003
 *      Create date: 27/02/2019
 * Last modify date: 27/02/2019
 *      Description: Set potentiometer Ohm value 0~10000.
 *
 *  @param Ohm_value: The value in Ohm to be set.
 *  @return value not small than 0: The real value set to potentiometer.
 *            (between 0 to 255)
 *          MCP41010_NEGATIVE_OHM_VALUE(-1): The Ohm value is negative.
 *          MCP41010_LESS_THEN_WIPER_RESISTANCE(-2): The Ohm value is less than
 *            wiper resistance.
 ******************************************************************************/
int MCP41010_setOhm(int Ohm_value) {
  int value_set;

  if(Ohm_value < 0){
    return MCP41010_NEGATIVE_OHM_VALUE;
  }

  if(Ohm_value < MCP41010_WIPER_RESISTANCE){
    return MCP41010_LESS_THEN_WIPER_RESISTANCE;
  }

  value_set = (int)((Ohm_value - MCP41010_WIPER_RESISTANCE)/MCP41010_MAX_RESISTANCE * 255);

  MCP41010_setValue((uint8_t)value_set);
  
  return value_set;
}

/******************************************************************************
 *             Name: MCP41010_setAWOhm
 *      Function ID: 200
 *      Create date: 27/02/2019
 * Last modify date: 27/02/2019
 *      Description: Set PA to PW potentiometer Ohm value 0~10000.
 *
 *  @param Ohm_value: The value in Ohm to be set.
 *  @return value not small than 0: The real value set to potentiometer.
 *            (between 0 to 255)
 *          MCP41010_NEGATIVE_OHM_VALUE(-1): The Ohm value is negative.
 *          MCP41010_LESS_THEN_WIPER_RESISTANCE(-2): The Ohm value is less than
 *            wiper resistance.
 ******************************************************************************/
int MCP41010_setAWOhm(int Ohm_value) {
  int value_set;

  if(Ohm_value < 0){
    return MCP41010_NEGATIVE_OHM_VALUE;
  }

  if(Ohm_value < MCP41010_WIPER_RESISTANCE){
    return MCP41010_LESS_THEN_WIPER_RESISTANCE;
  }

  value_set = (int)((MCP41010_MAX_RESISTANCE - Ohm_value + MCP41010_WIPER_RESISTANCE)/MCP41010_MAX_RESISTANCE * 255);

  MCP41010_setValue((uint8_t)value_set);

  return value_set;
}

/******************************************************************************
 *             Name: MCP41010_setWBOhm
 *      Function ID: 201
 *      Create date: 27/02/2019
 * Last modify date: 27/02/2019
 *      Description: Set PW to PB potentiometer Ohm value 0~10000.
 *
 *  @param Ohm_value: The value in Ohm to be set.
 *  @return value not small than 0: The real value set to potentiometer.
 *            (between 0 to 255)
 *          MCP41010_NEGATIVE_OHM_VALUE(-1): The Ohm value is negative.
 *          MCP41010_LESS_THEN_WIPER_RESISTANCE(-2): The Ohm value is less than
 *            wiper resistance.
 ******************************************************************************/
int MCP41010_setWBOhm(int Ohm_value) {

  return MCP41010_setOhm(Ohm_value);
}

/******************************************************************************
 *             Name: MCP41010_setWBOhm
 *      Function ID: 202
 *      Create date: 27/02/2019
 * Last modify date: 27/02/2019
 *      Description: Set the value in direct proportion to Ohm value to 
 *                   potentiometer.
 *
 *  @param value: The value to be set.
 ******************************************************************************/
void MCP41010_setProcessing_value(uint8_t value) {
  MCP41010_setValue(255-value);
}

/******************************************************************************
 *             Name: MCP41010_calculate_Ohm
 *      Function ID: 300
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
int MCP41010_calculate_Ohm(uint8_t set_value) {

  double Ohm_value = set_value/255.0 * MCP41010_MAX_RESISTANCE + MCP41010_WIPER_RESISTANCE;
  return (int)Ohm_value;
}

