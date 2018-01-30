/*
  Contains the start code for the Arduino that will call everything else
*/
#include "Arduino.h"
#include "navigation.h"

#define LED 13

void setup() {
  // set the motor pins
  pinMode(INA1, OUTPUT);
  pinMode(INB1, OUTPUT);
  pinMode(PWM1, OUTPUT);
  
  pinMode(PWM2, OUTPUT);
  pinMode(INB2, OUTPUT);
  pinMode(INA2, OUTPUT);
}

void loop() {
  startNavigation();

}
