//#define PROGRAM_DEBUG

#ifdef PROGRAM_DEBUG
#define SET_VALUE_COMMAND 49U
#else
#define SET_VALUE_COMMAND 200U
#endif

const int analogOutPin = 9; // Analog output pin that the LED is attached to

bool set_value_command_start;

void setup()
{
  // initialize serial communications at 115200 bps:
  Serial.begin(115200);   
#ifdef PROGRAM_DEBUG
  Serial.println("Current controller");
#endif

  // change the analog out value:
  analogWrite(analogOutPin, 0U);
  set_value_command_start = false;
}

void loop()
{ 
}

void serialEvent() {
  uint8_t inChar;
  // get the new byte:
  while(Serial.available())  {
    inChar = (uint8_t)Serial.read();

    if(set_value_command_start){
      // change the analog out value:
      analogWrite(analogOutPin, inChar);

      set_value_command_start = false;
#ifdef PROGRAM_DEBUG
      Serial.print("Set value: ");
      Serial.println(inChar);
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
