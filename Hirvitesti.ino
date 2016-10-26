/*
 Controlling a servo position using a potentiometer (variable resistor)
 by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>

 modified on 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Knob
*/

#include <Servo.h>
#include <NewPing.h>

Servo servoturn;  // create servo object to control turning servo
Servo servoaccel;  // create servo object to control acceleration servo

const short int startButtonPin = 2;        // the number of the pushbutton pin
const short int brakeSpeed = 80;          // value for braking 
const short int parkSpeed = 93;          // value for parking 
const short int minSpeed = 95;          // value for slow acceleration
const short int maxSpeed = 100;         // max speed value
const short int balance = 2;            // angle shift (neutral angle balance)
const short int maxAnglePos = 33;       // max positive angle value, left turn
const short int maxAngleNeg = -35;      // max negative angle value, right turn
const short int startDelay = 3000;      // start delay (ms)
const short int periodTime = 14;        // servo controlling period time
const short int maxRatio = 1000;         // max pulse ratio

short int exangle = 90;                 // current state of tire angle
short int startButtonState = 0;         // variable for reading the pushbutton status

// Sonar setup

#define TRIGGER_PIN  11  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN1    12  // Arduino pin tied to echo pin on the ultrasonic sensor..
#define ECHO_PIN2    13  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define ECHO_PIN3    7  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 400 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar1(TRIGGER_PIN, ECHO_PIN1, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonar2(TRIGGER_PIN, ECHO_PIN2, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonar3(TRIGGER_PIN, ECHO_PIN3, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup() {
  Serial.begin(115200);
  servoturn.attach(9);            // attaches the turning servo on pin to the servo object
  servoaccel.attach(10);          // attaches the acceleration servo on pin to the servo object
  pinMode(startButtonPin, INPUT); // initialize the pushbutton pin as an input
}

void turn(short int angle, short int turnspeed){
  
  // checks that turning angles are within safe limits
  if (angle > maxAnglePos && angle > 0){
    angle = maxAnglePos;
  } 
  else if (angle < maxAngleNeg && angle < 0){
    angle = maxAngleNeg;
  } 

  angle = angle + balance + 90;     // scale

  // sets turning angle
  if (angle == 90 + balance){
    servoturn.write(angle);
  }
  else if (angle == exangle){
  }
  else if (angle < exangle){
    for(int i=exangle; i > angle; i--){
    servoturn.write(i);
    delay(turnspeed);
    }
  }
  else {
      for(int i=exangle; i < angle; i++){
      servoturn.write(i);
      delay(turnspeed);
    }
  }
  exangle = angle;
}


void accelFast(short int accelSpeed, unsigned short int accelTime){
  
  if (accelSpeed <= maxSpeed && accelSpeed >= minSpeed){
    servoaccel.write(accelSpeed);
    delay(accelTime);
  } 
  else if (accelSpeed < minSpeed && accelSpeed > 0){
    servoaccel.write(accelSpeed);
    delay(accelTime);
  } 
  else if (accelSpeed > maxSpeed){
    servoaccel.write(maxSpeed);
    delay(accelTime);
  }
  else {
    servoaccel.write(parkSpeed);
    delay(accelTime);
  }
}

/*
void accelSlow(short int accelSpeed, short int accelTime, short int pulseRatio){

  if (pulseRatio < 2){
    pulseRatio = 2;
  }
  else if (pulseRatio > maxRatio){
    pulseRatio = maxRatio;
  }
  
  if (accelSpeed <= maxSpeed && accelSpeed >= minSpeed){
    for (;accelTime > 0; accelTime = accelTime - (periodTime * pulseRatio) ){
        servoaccel.write(accelSpeed);
        delay(periodTime * (pulseRatio-1) );
        servoaccel.write(parkSpeed);
        delay(periodTime);
      }
  }
  else if (accelSpeed < minSpeed && accelSpeed > 0){
    servoaccel.write(accelSpeed);
    delay(accelTime);
  } 
  else if (accelSpeed > maxSpeed){
    servoaccel.write(maxSpeed);
    delay(accelTime);
  }
  else {
    servoaccel.write(parkSpeed);
    delay(accelTime);
  }
}
*/

void start(){
  turn(1,5);
  int rightSonar;
  int leftSonar;
  int frontSonar;
  int brake = 0;
  Serial.println("Start");
  servoaccel.write(84);
  while(1){
    delay(32);
    rightSonar=sonar1.ping_cm();
    delay(32);
    leftSonar=sonar2.ping_cm();
    delay(32);
    frontSonar=sonar3.ping_cm();
    if (rightSonar==0){
      rightSonar=400;
    }
    if (leftSonar==0){
      leftSonar=400;
    }
    if (frontSonar==0){
      frontSonar=400;
    }
    Serial.print(leftSonar);
    Serial.print(" <-vasen eteen = ");
    Serial.print(frontSonar);
    Serial.print(" oikea-> ");
    Serial.println(rightSonar);
    if (frontSonar < 300) {
          turn(25,5);
          delay(300);
          turn(0,5);
          delay(800);
          turn(-25,5);
          delay(300);
          turn(0,5);
          delay(400);
          turn(-25,5);
          delay(120);
          turn(0,5);
          delay(700);
          turn(25,5);
          delay(120);
          turn(0,5);
          delay(50);          
          servoaccel.write(95);
          servoaccel.write(90);
          delay(70000);
    }
  }  
}


void track(bool allow){
  
}



void loop() {


start();    // main moving function


}

