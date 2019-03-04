//#define PROGRAM_DEBUG

#ifdef PROGRAM_DEBUG
#define SET_VALUE_COMMAND 49U
#define READ_VOLTAGE_COMMAND 50U
#else
#define SET_VALUE_COMMAND 200U
#define READ_VOLTAGE_COMMAND 201U
#endif

int sensorValue = 0;        // value read from the pot
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
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
  // read the analog in value:
  sensorValue = analogRead(analogInPin);
    
//  Serial.println(sensorValue);
//  previous_sensorValue = sensorValue;
//  delay(500);
}

void serialEvent() {
  uint8_t inChar;
  // get the new byte:
  while(Serial.available())  {
    inChar = (uint8_t)Serial.read();

    if(inChar == READ_VOLTAGE_COMMAND && !set_value_command_start){
        Serial.println(sensorValue);
  
#ifdef PROGRAM_DEBUG
        Serial.print("read voltage: ");
        Serial.println(sensorValue);
#endif
    }

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
