#include "MCP41010.h"

#define SET_VALUE_COMMAND 200U

bool set_value_command_start;

void setup()
{
  MCP41010_setup();    

  set_value_command_start = false;
}

void loop()
{ 
#ifdef MCP41010_DEBUG_SELF_TEST
  for(uint8_t i=0; i<4; i++){
    uint8_t temp = i*80;
    MCP41010_setProcessing_value(temp);
    Serial.print("Set value: ");
    Serial.print(temp);
    Serial.print(" - ");
    Serial.print(MCP41010_calculate_Ohm(temp));
    Serial.println(" Ohm");
    delay(2000);     
  }
#endif
}


void serialEvent() {
  uint8_t inChar;
  // get the new byte:
  while(Serial.available())  {
    inChar = (uint8_t)Serial.read();

    if(set_value_command_start){
      MCP41010_setProcessing_value(inChar);
      set_value_command_start = false;
#ifdef MCP41010_DEBUG
      Serial.print("Set value: ");
      Serial.print(inChar);
      Serial.print(" - ");
      Serial.print(MCP41010_calculate_Ohm(inChar));
      Serial.println(" Ohm");
#endif
    }

    switch(inChar){
      case SET_VALUE_COMMAND:
        set_value_command_start = true;
        break;
      default:
        break;
    }
  }
}
