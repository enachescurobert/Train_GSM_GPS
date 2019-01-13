#include "LiquidCrystal.h"
const int rs = 31, en = 30, d4 = 29, d5 = 28, d6 = 27, d7 = 26;
// for Arduino Uno: rs = 13 , en = 12 , d4 = 11 , d5 = 10 , d6 = 9 , d7 = 8 ; 
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#include "SIM900.h"
#include <SoftwareSerial.h>
#include "sms.h"
SMSGSM sms;

//gsm module
int numdata;
boolean started=false;
char smsbuffer[160];
char n[20];

//Ultrasonic

const int trigPin = 40; //Arduino Uno : Pin 4
const int echoPin = 41; //Arduino Uno : Pin 5
long duration;
int distance;

//Buzzer
int buzzer = 36;//pin 4 for Arduino


void setup() 
{
   lcd.begin(16, 2);
   lcd.print("Totul OK!");

   pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
   pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  //Buzzer
   pinMode(buzzer,OUTPUT);//initialize the buzzer pin as an output

  //Serial connection.
   Serial.begin(9600);
   Serial.println("GSM Shield testing.");
  //Start configuration of shield with baudrate.
  //For http uses is raccomanded to use 4800 or slower.
  if (gsm.begin(2400)){
    Serial.println("\nstatus=READY");
    started=true;  
  }
  else Serial.println("\nstatus=IDLE");


/*
  if(started){
    //Read if there are messages on SIM card and print them.
    if(gsm.readSMS(smsbuffer, 160, n, 20))
    {
      Serial.println(n);
      Serial.println(smsbuffer);
    }
    delay(1000);
}
*/
}
void loop()
{
    unsigned char i;
    
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    // Calculating the distance
    distance= duration*0.034/2;
    // Prints the distance on the Serial Monitor
    Serial.print("Distance: ");
    Serial.println(distance);
    
    if(distance>50){
    if (sms.SendSMS("0736094704", "VAGxy"))
      Serial.println("\nSMS sent OK");
      sms.SendSMS("0754490582", "VAGxy");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("VAGxy");

     //Buzzer
       for(i=0;i<80;i++)
       {
        digitalWrite(buzzer,HIGH);
        delay(200);//wait for 1ms
        digitalWrite(buzzer,LOW);
        delay(20);//wait for 1ms
        }

}

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

  
    delay(5000);
};
