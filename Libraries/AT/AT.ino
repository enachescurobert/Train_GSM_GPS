#include <SoftwareSerial.h>
SoftwareSerial SIM808(50, 51); //To select pins 50 to be Rx and 51 to be Tx; (7,8) for Arduino Uno)

void setup()
{
 SIM808.begin(19200);
 Serial.begin(19200);
 delay(100);
}

void loop()
{
 //We send and we receive data
 if (Serial.available() > 0)
 SIM808.write(Serial.read());
 if (SIM808.available() > 0)
 Serial.write(SIM808.read());
}
