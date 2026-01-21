/* Example sketch to control a stepper motor with 
   A4988/DRV8825 stepper motor driver and 
   Arduino without a library. 
   More info: https://www.makerguides.com */

// Define stepper motor connections and steps per revolution:

#include <Servo.h>
//#include "antennaFunctions.h"
Servo myservo;

#define dirPin 2
#define stepPin 3
//#define stepsPerRevolution 200
#define laserOutputPin 4
#define stepperM0 5
#define stepperM1 6
#define stepperM2 7
#define servoPin 8
int pos=0;

/*Currecnt Changes*/
int *new_pos; // new_pos points to the memory address of pos where 0 is stored
new_pos = &pos;


//int revs=0;
//int speed=0;
char appCommand;

/*void azimuthRight(){
	digitalWrite(2, HIGH); //set direction clockwise for "right"
	int revs=0.5;
	int speed=80000;
  int stepsPerRevolution=200;
	
	for (int i = 0; i < revs * stepsPerRevolution; i++) {
    digitalWrite(2, HIGH);
    delayMicroseconds(speed);
    digitalWrite(2, LOW);
    delayMicroseconds(speed);
  }	
}*/

/*void azimuthLeft(){
	digitalWrite(2, LOW); //set direction counter-clockwise for "left"
	int revs=0.5;
	int speed=80000;
  int stepsPerRevolution=200;
	
	for (int i = 0; i < revs * stepsPerRevolution; i++) {
    digitalWrite(2, HIGH);
    delayMicroseconds(speed);
    digitalWrite(2, LOW);
    delayMicroseconds(speed);
  }	
}*/

/*void elevationUp(int pos){
	for (pos = 0; pos <= 5; pos += 1) {
    // in steps of 1 degree
	myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
}*/



 void elevationUp(int pos){
	for (pos = 0; pos <= 5; pos += 1) {
    // in steps of 1 degree
	myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
  *new_pos = pos;
}


/*void elevationDown(int pos){
	for (pos = 5; pos >= 0; pos -= 1) {
    // in steps of 1 degree
	myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
}*/

void elevationDown(int pos){
	for (pos = 5; pos >= 0; pos -= 1) {
    // in steps of 1 degree
	myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
  *new_pos = pos;
}


void stopAll(){
	Serial.println("All functions stopped");
}

void setup() {
  // initialize serial
  Serial.begin(9600);
  Serial.println("Serial initialized.");
  pinMode(laserOutputPin, OUTPUT); 
  myservo.attach(servoPin);


  // Declare pins as output:
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
}

void loop() {
    //Serial.println("Loop started.");
    if(Serial.available()){ 
    //Serial.println("Serial Available.");
    appCommand = Serial.read();
    Serial.println(appCommand);

  }
  /*
  digitalWrite(stepperM0, HIGH);
  digitalWrite(stepperM1, HIGH);
  digitalWrite(stepperM2, HIGH);
  digitalWrite(laserOutputPin, HIGH);
  double revs=0;
  int speed=0;
  // Set the spinning direction clockwise:
  digitalWrite(dirPin, HIGH);

  // Spin the stepper motor 0.25 revolution slowly:
  revs=0.5;
  speed=80000;
  for (int i = 0; i < revs * stepsPerRevolution; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(speed);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(speed);
  }

  delay(250);

  // Set the spinning direction counterclockwise:
  digitalWrite(dirPin, LOW);

  revs=0.5;

  for (int i = 0; i < revs * stepsPerRevolution; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(speed);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(speed);
  }

  delay(250);

    for (pos = 0; pos <= 30; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
  for (pos = 30; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
 */
//Replace n with the char button variable 
  switch (appCommand){
        case 'U':
        elevationUp();
        Serial.println("Command received: UP");
            
        break;

        case 'D':
        elevationDown();
        Serial.println("Command received: DOWN");

        break;

        case 'L':
        //azimuthLeft();
        Serial.println("Command received: LEFT");

        break;

        case 'R':
        //azimuthRight();
        Serial.println("Command received: RIGHT");

        break;

        case 'S':
        //stopAll();
        Serial.println("Command received: STOP");

        //default:
        //stopAll();
      }

}