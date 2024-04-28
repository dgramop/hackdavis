#include <Arduino.h>
#include <SPI.h>
#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int potpin = 0;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin
            

// 19ms pulse spacing
// 1ms pulse

void setup() {
  delay(1000);
  myservo.attach(3, 1000, 20000); 
  myservo.write(0);
  delay(4000);
  myservo.write(60);
  delay(1000);
}

void loop() {
  delay(2000);
  myservo.write(100);
}

