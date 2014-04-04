/***
 *  SimplePing
 *  Simply gets distance measured by a HC-SR04.
 *
 *
 * ******Warning******
 *  The HC-SR04 works at 5V!!!
 *  LM4F120H5QR port are 5V-tollerant.
 *  Most Arduino boards work at 5V
 *  Check the datasheet before using it on a 3.3V Board
 *
 *  ====Connection====
 *  HC_SR04 -------  MCU
 *  ========================
 *  VCC    --------  5V/VBUS
 *  TRIG   --------  TRIGPIN
 *  ECHO   --------  ECHOPIN
 *  GND    --------  GND
 * 
 *  Created 2014/04/04 by Alessio Graziano
 ***/

#include <PingSensor.h>

#define TRIGPIN 7 //Trigger pin (Any will do)
#define ECHOPIN 8 //Echo pin (Must support interrupt)

PingSensor Ping; //Create Ping Sensor

void setup()
{
  Ping.begin(7,8); //Init Ping sensor
  Serial.begin(9600);
}

void loop()
{
  Ping.trigger(); //Trigger measurement
  
  if(Ping.waitAvailable()) //Wait for measurement complete (Or timeout)
    Serial.println(Ping.getDistance()); //Write distance
  else
  {
    //An error occurred
    Serial.print("Error:");
    switch (Ping.getError())
    {
    case PSE_TIMEOUT:
      Serial.println("Timeout");
      break;
    case PSE_NOFRONT:
      Serial.println("No Connection");
      break;
    case PSE_FASTTRIGGER:
      Serial.println("Trigger too fast"); //This error should not ever occur in this sketch
      break;
    }
  }

}


