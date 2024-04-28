/*
* Arduino Wireless Communication Tutorial
*     Example 1 - Transmitter Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/

#include <Arduino.h>
#include <cstdint>

int throttle = 0;

int deadlines[4] = {0, 0, 0, 0};
int pins[4] = {
    4, //throttle
    14, //flaperon left
    2, //flaperon right
    0, //rudder
};

void zero_out(int* to) {
    for(int i=0; i < 4; i++) {
        to[i] = 0;
    }
}

// actually completely wrong
//sorts the indicies of vicim by their values (with selection sort)
void selsort(int* compare_fn, int* indicies, int s) {
    for(int i=0; i < s; i++) {

        int minidx = i;
        for(int k=i; k<s; k++) {
            if(compare_fn[indicies[k]] < compare_fn[indicies[minidx]]) {
                minidx = k;
            }
        }

        int tmp = indicies[i];
        indicies[i] = indicies[minidx];
        indicies[minidx] = tmp;
    }
}

void setup() {
  //pinMode(LED_BUILTIN, OUTPUT);
  //digitalWrite(LED_BUILTIN, LOW);

  // radio
  Serial.begin(57600);

  pinMode(pins[0], OUTPUT);
  pinMode(pins[1], OUTPUT);
  pinMode(pins[2], OUTPUT);
  pinMode(pins[3], OUTPUT);

  // setup ledc for prop
  ledcSetup((0+1), 50, 16);
  ledcAttachPin(pins[0], (0+1));

  ledcSetup((0+2), 50, 16);
  ledcAttachPin(pins[1], (0+2));

  ledcSetup((0+3), 50, 16);
  ledcAttachPin(pins[2], (0+3));

  ledcSetup((0+4), 50, 16);
  ledcAttachPin(pins[3], (0+4));
  delay(4000);

  /*
  delay(1000);
  pinMode(4, OUTPUT);

  //approx 4 seconds
  for(int i=0; i<= 4000/(20); i++) {
      digitalWrite(4, HIGH);
      delay(1);
      digitalWrite(4, LOW);
      delay(19);
  }

  //approx 1 seconds
  for(int i=0; i<= 1000/(20); i++) {
      digitalWrite(4, HIGH);
      delay(19);
      digitalWrite(4, LOW);
      delay(1);
  }*/

}

void loop() {

  int t = map(deadlines[0], 1, 20, 3275, 6553);
  //try pwm
  ledcWrite((1), t);
  
  int fl = map(deadlines[1], 1, 20, 3275, 6553);
  ledcWrite((2), fl);

  int fr = map(deadlines[2], 1, 20, 3275, 6553);
  ledcWrite((3), fr);

  int r = map(deadlines[3], 1, 20, 3275, 6553);
  ledcWrite((4), r);


  //WORKS
  if(Serial.available()) {
      Serial.print("Data available on serial!");
      char purge = 1;
      char addr = 0;
      char amt = 0;
      // every message must start with the header: the integer 12
      while(purge != 12) {
          Serial.readBytes(&purge, 1);
      }
      Serial.readBytes(&addr, 1);
      if(addr >= 0 && addr < 4) {
          Serial.readBytes(&amt, 1);
          deadlines[addr] = amt;
          Serial.print("A");
          Serial.println((int)addr);
          Serial.print("D");
          Serial.println((int)amt);
      }
      Serial.println();
  };

}

/*
void loop() {

  int order[4] = {0, 1, 2, 3};

  //works!
  selsort(deadlines, order, 4);
  for(int i=0; i<4; i++) {
      Serial.print(order[i]);
      Serial.print(",");
  }
  Serial.print("\n");

  ////////// TIMING SECTION
  // turn all the pins on
  for(int i=0; i < 4; i++) {
      digitalWrite(pins[order[i]], HIGH);
  }

  // turn pins off by deadline
  int already_slept = 0;
  for(int i=0; i < 4; i++) {
      delay(deadlines[order[i]] - already_slept); 
      digitalWrite(pins[order[i]], LOW);
      already_slept = deadlines[order[i]];
  }
  //////// TIMING SECTION

  //WORKS
  if(Serial.available()) {
      Serial.print("Data available on serial!");
      char purge = 1;
      char addr = 0;
      char amt = 0;
      // every message must start with the header: the integer 12
      while(purge != 12) {
          Serial.readBytes(&purge, 1);
      }
      Serial.readBytes(&addr, 1);
      if(addr == 0 ) { //TODO: remove, throttle restruction
      //if(addr >= 0 && addr < 4) {
          Serial.readBytes(&amt, 1);
          deadlines[addr] = amt;
          Serial.print("A");
          Serial.println((int)addr);
          Serial.print("D");
          Serial.println((int)amt);
      }
      Serial.println();
  };

  // all the pins are off. To make "inter-pulse width" ideal, sleep for 20ms
  delay(40-already_slept);

}
*/
