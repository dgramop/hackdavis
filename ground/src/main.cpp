/*
* Arduino Wireless Communication Tutorial
*     Example 1 - Transmitter Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/

#include <Arduino.h>

void setup() {
  //pinMode(LED_BUILTIN, OUTPUT);
  //digitalWrite(LED_BUILTIN, LOW);
  Serial.begin(57600);
}

void loop() {
  //Serial.print(Serial1.availableForWrite());
  //Serial.print(Serial1.available());
  //Serial.print("transmitted");
  if(Serial.available()) {
      Serial.print(Serial.readString());
  };
  //delay(1000);
}
