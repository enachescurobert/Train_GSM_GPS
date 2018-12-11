#include "LiquidCrystal.h"
// initialize the library by providing the nuber of pins to it
const int rs = 31, en = 30, d4 = 29, d5 = 28, d6 = 27, d7 = 26;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#include "SIM900.h"
#include <SoftwareSerial.h>
//If not used, is better to exclude the HTTP library,
//for RAM saving.
//If your sketch reboots itself proprably you have finished,
//your memory available.
//#include "inetGSM.h"

//If you want to use the Arduino functions to manage SMS, uncomment the lines below.
#include "sms.h"
SMSGSM sms;

//To change pins for Software Serial, use the two lines in GSM.cpp.

//GSM Shield for Arduino
//www.open-electronics.org
//this code is based on the example of Arduino Labs.

//Simple sketch to send and receive SMS.

int numdata;
boolean started=false;
char smsbuffer[160];
char n[20];

//Ultrasonic



//Buzzer
int buzzer = 36;//the pin of the active buzzer


void setup() 
{
   lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Totul OK!");


  //Buzzer
   pinMode(buzzer,OUTPUT);//initialize the buzzer pin as an output


  //Serial connection.
  Serial.begin(9600);
  Serial.println("GSM Shield testing.");
  //Start configuration of shield with baudrate.
  if (gsm.begin(2400)){
    Serial.println("\nstatus=READY");
    started=true;  
  }
  else Serial.println("\nstatus=IDLE");

}
void loop()
{    
      if(started){
        //Serial.println("AT+CMGL=\"ALL\"");
    //Read if there are unread messages on SIM card and print them.
    if(gsm.readSMS(smsbuffer, 160, n, 20))
    {
      String exemplu = smsbuffer;
      if(exemplu.startsWith("VAG")){
          lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(exemplu);
   //output an frequency
      unsigned char i;
   for(i=0;i<80;i++)
   {
    digitalWrite(buzzer,HIGH);
    delay(1000);//wait for 1ms
    digitalWrite(buzzer,LOW);
    delay(1);//wait for 1ms
    }

    //output another frequency
     for(i=0;i<100;i++)
      {
        digitalWrite(buzzer,HIGH);
        delay(2);//wait for 2ms
        digitalWrite(buzzer,LOW);
        delay(2);//wait for 2ms
      }
}
      }
      Serial.println(n);
      Serial.println(smsbuffer);
     
    }
    delay(1000);
};
