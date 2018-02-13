
#define LED 13
// transparent motor
#define INA1 2 // non-pwm blue
#define INB1 4 // non-pwm purple
#define PWM1 5 // pwm grey

// aqua motor
#define PWM2 6 // green
#define INB2 7 // yellow
#define INA2 8 // orange

// ping sensors
#define pingL 13
#define pingC 12
#define pingR 11

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


