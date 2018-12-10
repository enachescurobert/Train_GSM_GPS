#include <SoftwareSerial.h>
SoftwareSerial SIM808(50, 51); //Seleccionamos los pines 7 como Rx y 8 como Tx

void setup()
{
 SIM808.begin(19200);
 Serial.begin(19200);
 delay(100);
}

void loop()
{
 //Envíamos y recibimos datos
 if (Serial.available() > 0)
 SIM808.write(Serial.read());
 if (SIM808.available() > 0)
 Serial.write(SIM808.read());
}
