#include "LiquidCrystal.h"
const int rs = 31, en = 30, d4 = 29, d5 = 28, d6 = 27, d7 = 26; 
// for Arduino Uno: rs = 13 , en = 12 , d4 = 11 , d5 = 10 , d6 = 9 , d7 = 8 ; 
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#include "SIM900.h"
#include <SoftwareSerial.h> //50,51 for Arduino Mega; 1,2 for Arduino Uno ( GSN.cpp)

#include "sms.h"
SMSGSM sms;

//gsm module
int numdata;
boolean started=false;
char smsbuffer[160];
char n[20];

//Buzzer
int buzzer = 36;//pin 4 for Arduino

void setup() 
{
   lcd.begin(16, 2);
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
        lcd.print(exemplu.substring(0,5));
        
        //Buzzer 
         unsigned char i;
         for(i=0;i<80;i++)
         {
          digitalWrite(buzzer,HIGH);
          delay(200);
          digitalWrite(buzzer,LOW);
          delay(20);
         }
      }
      }
      Serial.println(n);
      Serial.println(smsbuffer);
     
    }
    delay(1000);
};
