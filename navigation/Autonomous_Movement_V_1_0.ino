/*
  Version 1.0:
    Our initial code to test the sensors and movement of our robot. 
    We want to set up the functions in a way that it is easy to call in the future when we have to do more complicated functions
    Took the Ping sensor example and combined it with our own motor control system.

    Features Added:
    + Define variables for pins with color coding
    + Movement functions that allow robot to break, moveForward, moveBackward, rotateLeft, rotateRight, turnLeft, turnRight
      + These functions take in a speed input (1 for slow, 2 for medium, 3 for high), to help robot pick speed
    + Picked arbitrary values for low, medium, and high PWD for each left and right motors to differentiate speeds
    + Loop that polls sensors and makes decision based on given distances


    Still Required:
    - Test to ensure algorith morks
    - Fine tune PWM variables for low, medium, and high for left and right, ensuring they go at the same speed
*/
// transparent motor
#define INA1 2 // non-pwm blue
#define INB1 4 // non-pwm purple
#define PWM1 6 // pwm grey

// motor powers/speeds (when we find the ratio of powers, list them here)
#define slowA 32
#define slowS 32
#define mediumA 70
#define mediumS 70
#define highA 150
#define highS 150

// aqua motor
#define PWM2 11 // green
#define INB2 12 // yellow
#define INA2 13 // orange

// this constant won't change. It's the pin number of the sensor's output:
const int pingPinR = 7;
const int pingPinC = 8;
const int pingPinL = 9;

void setup() {
  // initialize serial communication:
  Serial.begin(9600);
    // set the motor pins
  pinMode(INA1, OUTPUT);
  pinMode(INB1, OUTPUT);
  pinMode(PWM1, OUTPUT);
  
  pinMode(PWM2, OUTPUT);
  pinMode(INB2, OUTPUT);
  pinMode(INA2, OUTPUT);
}

void loop() {
  // establish variables for duration of the ping, and the distance result
  // in inches and centimeters:
  long durationL, inchesL, cmL;
  long durationC, inchesC, cmC;
  long durationR, inchesR, cmR;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPinR, OUTPUT);
  digitalWrite(pingPinR, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPinR, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPinR, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH pulse
  // whose duration is the time (in microseconds) from the sending of the ping
  // to the reception of its echo off of an object.
  pinMode(pingPinR, INPUT);
  durationR = pulseIn(pingPinR, HIGH);

  pinMode(pingPinC, OUTPUT);
  digitalWrite(pingPinC, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPinC, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPinC, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH pulse
  // whose duration is the time (in microseconds) from the sending of the ping
  // to the reception of its echo off of an object.
  pinMode(pingPinC, INPUT);
  durationC = pulseIn(pingPinC, HIGH);


  pinMode(pingPinL, OUTPUT);
  digitalWrite(pingPinL, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPinL, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPinL, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH pulse
  // whose duration is the time (in microseconds) from the sending of the ping
  // to the reception of its echo off of an object.
  pinMode(pingPinL, INPUT);
  durationL = pulseIn(pingPinL, HIGH);

  // convert the time into a distance
  inchesR = microsecondsToInches(durationR);
  //cmR = microsecondsToCentimeters(durationR);  //--- Too American, don't use cm in our code, lul

  // convert the time into a distance
  inchesC = microsecondsToInches(durationC);
  //cmC = microsecondsToCentimeters(durationC); //--- Too American, don't use cm in our code, lul

  // convert the time into a distance
  inchesL = microsecondsToInches(durationL);
  // cmL = microsecondsToCentimeters(durationL); //--- Too American, don't use cm in our code, lul

// -------- Debug Code, can uncomment if something isn't working as expected-----------

//  Serial.print(inchesR);
//  Serial.print("inR, ");
//  Serial.print(cmR);
//  Serial.print("cmR");
//  Serial.println();
//
//  Serial.print(inchesC);
//  Serial.print("inC, ");
//  Serial.print(cmC);
//  Serial.print("cmC");
//  Serial.println();
//
//
//  Serial.print(inchesL);
//  Serial.print("inL, ");
//  Serial.print(cmL);
//  Serial.print("cmL");
//  Serial.println();

// -------------------------

  if(inchesC > 6)
  {
      goForward(1);
  }
  else if(inchesL > 6)
  {
      rotateLeft(1);  //turning until we are to go forward again
      delay(2000);  //these might be optional, first thing to remove and see what happens :D
  }
  else if(inchesR > 6)
  {
      rotateRight(1); //turning until we are to go forward again
      delay(2000); //these might be optional, first thing to remove and see what happens :D
  }
  else
  {
    goBackward(1);  // backwards is complicated, we don't want it to get stuck in a loop of moving backwards and forwards
    delay(2000);
    rotateLeft(1);  // pick a way to turn so hopefully we won't get stuck in the same thing
    delay(2000);
  }
  delay(100);
}

long microsecondsToInches(long microseconds) {
  // According to Parallax's datasheet for the PING))), there are 73.746
  // microseconds per inch (i.e. sound travels at 1130 feet per second).
  // This gives the distance travelled by the ping, outbound and return,
  // so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;
}

 // ===================

void brake() {
  //For brake
  digitalWrite(INA1,HIGH);
  digitalWrite(INB1,HIGH);
  digitalWrite(INA2,HIGH);
  digitalWrite(INB2,HIGH);
}

void goForward(int s) {
  int pL = 0;
  int pR = 0;
  switch (s) {
    case 1:
      // statements
      pL = slowS; 
      pR = slowA;
      break;
    case 2:
      // statements
      pL = mediumS; 
      pR = mediumA;
      break;
    case 3:
     // statements
      pL = highS; 
      pR = highA;
      break;
    default:
      // make VERY SLOW to emphasise a value was entered wrong
      pL = 5;
      pR = 5;
      
  }
  digitalWrite(INA1,HIGH); // Blue is 1
  digitalWrite(INB1,LOW);
  analogWrite(PWM1,pR); // 255 is the highest value to drive the motor
  
  digitalWrite(INA2,LOW); // Silver is 2
  digitalWrite(INB2,HIGH);
  analogWrite(PWM2,pL);
}

void goBackward(int s) {
  int pL = 0;
  int pR = 0;
  switch (s) {
    case 1:
      // statements
      pL = slowS; 
      pR = slowA;
      break;
    case 2:
      // statements
      pL = mediumS; 
      pR = mediumA;
      break;
    case 3:
     // statements
      pL = highS; 
      pR = highA;
      break;
    default:
      // make VERY SLOW to emphasise a value was entered wrong
      pL = 5;
      pR = 5;
      
  }
  digitalWrite(INA1,LOW); // Blue is 1
  digitalWrite(INB1,HIGH);
  analogWrite(PWM1,pR); // 255 is the highest value to drive the motor
  
  digitalWrite(INA2,HIGH); // Silver is 2
  digitalWrite(INB2,LOW);
  analogWrite(PWM2,pL);  
}

void rotateLeft(int s) {
  int pL = 0;
  int pR = 0;
  switch (s) {
    case 1:
      // statements
      pL = slowS; 
      pR = slowA;
      break;
    case 2:
      // statements
      pL = mediumS; 
      pR = mediumA;
      break;
    case 3:
     // statements
      pL = highS; 
      pR = highA;
      break;
    default:
      // make VERY SLOW to emphasise a value was entered wrong
      pL = 5;
      pR = 5;
      
  }
    //For Clock-wise motion - IN_1 = LOW , INB1 = HIGH
  digitalWrite(INA1,HIGH);
  digitalWrite(INB1,LOW);
  analogWrite(PWM1,pR); // 255 is the highest value to drive the motor
  
  digitalWrite(INA2,HIGH);
  digitalWrite(INB2,LOW);
  analogWrite(PWM2,pL);
}

void rotateRight(int s) {
  int pL = 0;
  int pR = 0;
  switch (s) {
    case 1:
      // statements
      pL = slowS; 
      pR = slowA;
      break;
    case 2:
      // statements
      pL = mediumS; 
      pR = mediumA;
      break;
    case 3:
     // statements
      pL = highS; 
      pR = highA;
      break;
    default:
      // make VERY SLOW to emphasise a value was entered wrong
      pL = 5;
      pR = 5;
      
  }
    //For Anti Clock-wise motion - IN_1 = LOW , INB1 = HIGH
  digitalWrite(INA1,LOW);
  digitalWrite(INB1,HIGH);
  analogWrite(PWM1,pR);
  
  digitalWrite(INA2,LOW);
  digitalWrite(INB2,HIGH);
  analogWrite(PWM2,pL);
}

void turnLeft(int s) {
  int pL = 0;
  int pR = 0;
  switch (s) {
    case 1:
      // statements
      pL = slowS; 
      pR = slowA;
      break;
    case 2:
      // statements
      pL = mediumS; 
      pR = mediumA;
      break;
    case 3:
     // statements
      pL = highS; 
      pR = highA;
      break;
    default:
      // make VERY SLOW to emphasise a value was entered wrong
      pL = 5;
      pR = 5;
      
  }
  //For Clock-wise motion - IN_1 = LOW , INB1 = HIGH
  digitalWrite(INA1,HIGH);
  digitalWrite(INB1,LOW);
  analogWrite(PWM1,pR); // 255 is the highest value to drive the motor
  
  digitalWrite(INA2,HIGH);
  digitalWrite(INB2,HIGH);
  analogWrite(PWM2,pL);
}

void turnRight(int s) {
  int pL = 0;
  int pR = 0;
  switch (s) {
    case 1:
      // statements
      pL = slowS; 
      pR = slowA;
      break;
    case 2:
      // statements
      pL = mediumS; 
      pR = mediumA;
      break;
    case 3:
     // statements
      pL = highS; 
      pR = highA;
      break;
    default:
      // make VERY SLOW to emphasise a value was entered wrong
      pL = 5;
      pR = 5;
      
  }
  //For Anti Clock-wise motion - IN_1 = LOW , INB1 = HIGH
  digitalWrite(INA1,LOW);
  digitalWrite(INB1,HIGH);
  analogWrite(PWM1,pR);
  
  digitalWrite(INA2,HIGH);
  digitalWrite(INB2,HIGH);
  analogWrite(PWM2,pL);
}


