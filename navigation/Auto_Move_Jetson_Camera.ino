/* ENEE408I Capstone Project
   Team 12
   Victor Chan
   Andrew Gu
   Joshua Precilio
*/

// AQUA motor
#define INA1 2 // non-pwm blue
#define INB1 4 // non-pwm purple
#define PWM1 6 // pwm grey

// SILVER motor
#define PWM2 11 // green
#define INB2 12 // yellow
#define INA2 13 // orange

// motor powers/speeds (when we find the ratio of powers, list them here)
#define slowA 30
#define slowS 36
#define mediumA 50
#define mediumS 56
#define highA 70
#define highS 74

int turned = 0;
int startup = 0;
const int lim = 9;  // Distance when object is too close

// this constant won't change. It's the pin number of the sensor's output:
const int pingPinR = 7;
const int pingPinC = 8;
const int pingPinL = 9;

long durationL, inchL;
long durationC, inchC;
long durationR, inchR;

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

int cmd = '0';
void loop() {

  // --------------------------------------------------------------
  // Ping Sensors
  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pingAll();

  // --------------------------------------------------------------
  // Autonomous Movement Algorithm
  // goForward(1), goBackward(1), rotateRight/Left(1), turnRight/Left(1), brake()

  if (Serial.available() > 0) {

    cmd = Serial.read();

    Serial.write("Reading cmd: ");
    Serial.write(cmd);
    Serial.write("\n");

    // Case statement to drive robot
    switch (cmd) {
      case 'F':  // FORWARD
//        if (inchL > lim && inchC > lim && inchR > lim) {
//          goForward(1);
//        }
        
        
        if (inchC > lim) {
          // Too far from person, move closer
          goForward(2);
        } else if (inchC < 5) {
          goBackward(1);
        }
        else {
          // Too close to person stop
          brake();
        }
        brake();
        break;
      case 'L':  // LEFT
        rotateRight(2);
        break;
      case 'R':  // RIGHT
        rotateLeft(2);
        break;
      case 'H':  // HOLD
        brake();
        break;
      case 'X':
        search('R');
        break;
      case 'Y':
        search('L');
        break;
      default:
        brake();
        //move_with_sensor();
        break;
    }

  } // close if Serial.avail
  else {
    brake();
  }
  delay(50);
}




// --------------------------------------------------------------
// --- PING SENSORS ---------------------------------------------

// Make all sensors ping
void pingAll() {
  //long durationL, inchL;
  //long durationC, inchC;
  //long durationR, inchR;

  // Right Ping Sensor
  pinMode(pingPinR, OUTPUT);
  digitalWrite(pingPinR, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPinR, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPinR, LOW);

  pinMode(pingPinR, INPUT);                   // ping reads signal from the PING))
  durationR = pulseIn(pingPinR, HIGH);        // microsecond to get ping back from object
  inchR = microsecondsToInches(durationR);  // convert time -> distance (inch)

  // Center Ping Sensor
  pinMode(pingPinC, OUTPUT);
  digitalWrite(pingPinC, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPinC, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPinC, LOW);

  pinMode(pingPinC, INPUT);                   // ping reads signal from the PING))
  durationC = pulseIn(pingPinC, HIGH);        // microsecond to get ping back from object
  inchC = microsecondsToInches(durationC);  // convert time -> distance (inch)

  // Left Ping Sensor
  pinMode(pingPinL, OUTPUT);
  digitalWrite(pingPinL, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPinL, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPinL, LOW);

  pinMode(pingPinL, INPUT);                   // ping reads signal from the PING))
  durationL = pulseIn(pingPinL, HIGH);        // microsecond to get ping back from object
  inchL = microsecondsToInches(durationL);  // convert time -> distance (inch)

  //  // Print distance to serial window
  //  Serial.print(inchL);
  //  Serial.print("inL, ");
  //
  //  Serial.print(inchC);
  //  Serial.print("inC, ");
  //
  //  Serial.print(inchR);
  //  Serial.print("inR ");
  //
  //  Serial.println();
}

// Make right sensor ping
void pingRight() {
  //long durationR, inchR, cmR;

  pinMode(pingPinR, OUTPUT);
  digitalWrite(pingPinR, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPinR, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPinR, LOW);
  pinMode(pingPinR, INPUT);                   // ping reads signal from the PING))

  durationR = pulseIn(pingPinR, HIGH);        // microsecond to get ping back from object
  inchR = microsecondsToInches(durationR);  // convert time -> distance (inch)
  //Serial.print(inchR);
  //Serial.println("inR ");
}


// --------------------------------------------------------------
// --- TIME CONVERSION ------------------------------------------
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



// --------------------------------------------------------------
// --- ROBOT MOVEMENT FUNCTIONS ---------------------------------

void brake() {
  //For brake
  digitalWrite(INA1, HIGH);
  digitalWrite(INB1, HIGH);
  digitalWrite(INA2, HIGH);
  digitalWrite(INB2, HIGH);
  delay(100);
}

// -------------------------------
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
  digitalWrite(INA1, HIGH); // Silver is 1
  digitalWrite(INB1, LOW);
  analogWrite(PWM1, pL); // 255 is the highest value to drive the motor

  digitalWrite(INA2, LOW); // Aqua is 2
  digitalWrite(INB2, HIGH);
  analogWrite(PWM2, pR);
}

// -------------------------------
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
  digitalWrite(INA1, LOW); // Silver is 1
  digitalWrite(INB1, HIGH);
  analogWrite(PWM1, pL); // 255 is the highest value to drive the motor

  digitalWrite(INA2, HIGH); // Aqua is 2
  digitalWrite(INB2, LOW);
  analogWrite(PWM2, pR);
}

// -------------------------------
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
      pL = 15;
      pR = 15;

  }
  //For Clock-wise motion - IN_1 = LOW , INB1 = HIGH
  digitalWrite(INA1, HIGH); //Silver is 1
  digitalWrite(INB1, LOW);
  analogWrite(PWM1, pL); // 255 is the highest value to drive the motor

  digitalWrite(INA2, HIGH); //Aqua is 2
  digitalWrite(INB2, LOW);
  analogWrite(PWM2, pR);
}

// -------------------------------
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
      pL = 15;
      pR = 15;

  }
  //For Anti Clock-wise motion - IN_1 = LOW , INB1 = HIGH
  digitalWrite(INA1, LOW);    //Silver is 1
  digitalWrite(INB1, HIGH);
  analogWrite(PWM1, pL);

  digitalWrite(INA2, LOW);  //Aqua is 2
  digitalWrite(INB2, HIGH);
  analogWrite(PWM2, pR);
}

void search(char dir){
  if(dir == 'R'){
    rotateLeft(1); //Purposely triggering default case
  }
  else if(dir == 'L'){
    rotateRight(1);  //Purposely triggering default case
  }
}



// -------------------------------
// ------ MOSTLY DEPRECATED ------
// -------------------------------
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
  digitalWrite(INA1, HIGH);   //Silver is 1
  digitalWrite(INB1, LOW);
  analogWrite(PWM1, pL); // 255 is the highest value to drive the motor

  digitalWrite(INA2, HIGH);   //Aqua is 2
  digitalWrite(INB2, HIGH);
  analogWrite(PWM2, pR);
}

// -------------------------------
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
  digitalWrite(INA1, LOW);    //Silver is 1
  digitalWrite(INB1, HIGH);
  analogWrite(PWM1, pL);

  digitalWrite(INA2, HIGH);   //Aqua is 2
  digitalWrite(INB2, HIGH);
  analogWrite(PWM2, pR);
}

// --------------------------------------------------------------
// --- AUTONOMOUS MOVEMENT --------------------------------------
void move_with_sensor() { // default case
  long starttime, endtime, innerStart, innerEnd;
  // Y = see something close || N = see nothing close

  // ---------------
  // - USUAL CASES -
  // ---------------
  // L[N] C[N] R[N]
  if (inchL > lim && inchC > lim && inchR > lim) {
    goForward(1);
  }
  // L[Y] C[Y] R[N] OR L[Y] C[N] R[N]
  else if ( (inchL < lim && inchC < lim && inchR > lim) ||
            (inchL < lim && inchC > lim && inchR > lim) ) {
    rotateRight(1);
  }
  // L[N] C[Y] R[Y] OR L[N] C[N] R[Y]
  else if ( (inchL > lim && inchC < lim && inchR < lim) ||
            (inchL > lim && inchC > lim && inchR < lim) ) {
    rotateLeft(1);
  }

  // -----------------
  // - SPECIAL CASES -
  // -----------------
  // L[N] C[Y] R[N]
  else if (inchL > lim && inchC < lim && inchR > lim) {
    starttime = millis();   // Prevent robot from spinning forever
    endtime = starttime;
    while ((endtime - starttime) <= 10000) {

      pingRight();

      // Turn right until right or left sensor picks up something
      if (inchR > lim) {
        // Right sensor does not see obstacle yet
        rotateRight(1);
      } else {
        // Right Sensor sees the obstacle

        innerStart = millis();
        innerEnd = millis();
        while ((innerEnd - innerStart) <= 10000) {

          pingRight();

          if (inchR < lim) {
            // Turn right until you dont see the obstacle
            rotateRight(1);
          } else {
            // Dont see he obstacle should be clear path ahead
            brake();
            break; // break inner while
          }

          innerEnd = millis();
        } // End inner while
        brake();
        break; // break outer while
      }

      // Keep track of elasped time
      endtime = millis();

    } // End while loop
  }
  // L[Y] C[N] R[Y]
  else if ( (inchL < lim && inchC > lim && inchR < lim) ||
            (inchL < lim && inchC < lim && inchR < lim)) {
    starttime = millis();   // Prevent robot from spinning forever
    endtime = starttime;
    while ((endtime - starttime) <= 10000) {

      pingRight();

      // Turn right until right sensor sees nothing
      if (inchR < lim) {
        // Right sensor still sees the obstable
        rotateRight(1);
      } else {
        // Right sensor sees nothing

        innerStart = millis();
        innerEnd = millis();
        while ((innerEnd - innerStart) <= 10000) {

          pingRight();

          // Turn right until right sensor sees obstacle
          //(looking for the obstacle left sensor saw)
          if (inchR > lim) {
            rotateRight(1);
          }
          else {
            // Right Sensor sees nothing, path should be clear
            brake();
            break; // break inner while
          }

          innerEnd = millis();
        } // End inner while
        brake();
        break;  // break outer while
      }

      // Keep track of elasped time
      endtime = millis();
    } //End outer while loop
  }
}



