#include "Arduino.h"
#include "navigation.h"

void startNavigation() {
  // for clockwise 
  digitalWrite(INA1,HIGH);
  digitalWrite(INB1,LOW);
  analogWrite(PWM1,255);
  
  digitalWrite(INA2,HIGH);
  digitalWrite(INB2,LOW);
  analogWrite(PWM2,255);
  /*setting pwm of the motor to 255
    we can change the speed of rotaion
    by chaning pwm input but we are only
    using arduino so we are using higest
    value to driver the motor  */

  //Clockwise for 3 secs
  delay(3000); 		

  //For brake
  digitalWrite(INA1,HIGH);
  digitalWrite(INB1,HIGH);
  digitalWrite(INA2,HIGH);
  digitalWrite(INB2,HIGH);
  delay(1000);

  //For Anti Clock-wise motion - IN_1 = LOW , INB1 = HIGH
  digitalWrite(INA1,LOW);
  digitalWrite(INB1,HIGH);
  digitalWrite(INA2,HIGH);
  digitalWrite(INB2,HIGH);
  delay(3000);

  //For brake
  digitalWrite(INA1,HIGH);
  digitalWrite(INB1,HIGH);
  digitalWrite(INA2,HIGH);
  digitalWrite(INB2,HIGH);
  delay(1000);
}

int pingSensor() {
  
}
