
// INA - clockwise, INB - counterclockwise
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
    pinMode(INA1, OUTPUT);
  pinMode(INB1, OUTPUT);
  pinMode(PWM1, OUTPUT);

  pinMode(PWM2, OUTPUT);
  pinMode(INB2, OUTPUT);
  pinMode(INA2, OUTPUT);
  Serial.begin(9600);
  while(! Serial);
  Serial.write("setup()");
//   set the motor pins

}

void loop() {
//  Serial.write(45);
//  Serial.write("loop()");
//  digitalWrite(INB2, HIGH);
  startNavigation(); 
}

void startNavigation() {
  Serial.write("start navigation");
//  goStraight();
//   delay(3000);
  // for clockwise
  digitalWrite(INA1, HIGH);
  digitalWrite(INB1, LOW);
  analogWrite(PWM1, 255);

  digitalWrite(INA2, HIGH);
  digitalWrite(INB2, LOW);
  analogWrite(PWM2, 255);
  /*setting pwm of the motor to 255
    we can change the speed of rotaion
    by chaning pwm input but we are only
    using arduino so we are using higest
    value to driver the motor  */

  //Clockwise for 3 secs
  delay(3000);

  stop();

  //For Anti Clock-wise motion - IN_1 = LOW , INB1 = HIGH
  digitalWrite(INA1, LOW);
  digitalWrite(INB1, HIGH);
  digitalWrite(INA2, HIGH);
  digitalWrite(INB2, HIGH);
  delay(3000);

  stop();
}

void goStraight() {
  analogWrite(PWM1, 120);
  analogWrite(PWM2, 120);
}

void goLeft() {
  
}

void goRight() {
  
}
void stop() {
  digitalWrite(INA1, 0);
  digitalWrite(INB1, 0);
  digitalWrite(INA2, 0);
  digitalWrite(INB2, 0);
  delay(1000);
}

