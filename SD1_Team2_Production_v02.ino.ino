//Add servo library and initialize servo object
#include <Servo.h>
Servo myservo;

//Define constants
#define dirPin 2
#define stepPin 3
//#define stepsPerRevolution 200
#define laserOutputPin 4
#define stepperM0 5
#define stepperM1 6
#define stepperM2 7
#define servoPin 8
#define speed 80000
#define revs 0.05
#define stepsPerRevolution 200

//Define global position variable for servo

double servoPosition=0;
char appCommand;
//_________________________________________________________________________________
// Function Definitions
void elevationDown(){
  myservo.write(servoPosition);
  if(servoPosition<70){
    servoPosition+=0.5;
  }
  Serial.println(servoPosition);
  delay(15);
}

void elevationUp(){
  myservo.write(servoPosition);
  if(servoPosition>0){
    servoPosition-=0.5;
  }
  Serial.println(servoPosition);
  delay(15);
}

void azimuthRight(){
  digitalWrite(dirPin, HIGH);
  for (int i = 0; i < revs * stepsPerRevolution; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(speed);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(speed);
    delay(100);
  }
}

void azimuthLeft(){
  digitalWrite(dirPin, LOW);
  for (int i = 0; i < revs * stepsPerRevolution; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(speed);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(speed);
    delay(100);
  }
}


//___________________________________________________________________________

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myservo.attach(servoPin);
  pinMode(laserOutputPin, OUTPUT); 
  Serial.println("Arduino Sketch Started");
}
//___________________________________________________________________________

void loop() {
  digitalWrite(laserOutputPin, HIGH); //turn on 
  
  digitalWrite(stepperM0, HIGH); //set stepper to finest step increment
  digitalWrite(stepperM1, HIGH);
  digitalWrite(stepperM2, HIGH);


  if(Serial.available()){ //this section waits for input from the BT module and app and executes functions based on controller entry
  //Serial.println("Serial Available.");
  appCommand = Serial.read();
  Serial.println(appCommand);
  }
  switch (appCommand){
        case 'U':
        elevationUp();
        break;

        case 'D':
        elevationDown();
        break;

        case 'R':
        azimuthRight();
        break;

        case 'L':
        azimuthLeft();
        break;

        case 'S':
        break;

  }

}
//_____________________________________________________________________