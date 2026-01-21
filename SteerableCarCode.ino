#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
#define SERVOMIN  125 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  575 // this is the 'maximum' pulse length count (out of 4096)
int servoInt = 0; //initialize int to send to servo
//String receivedData=""; //initialize empty string to receive data from serial via BT
// our servo # counter
uint8_t servonum = 0;


int leftSideMotors1 = 2;
int leftSideMotors2 = 3;
int rightSideMotors1 = 4;
int rightSideMotors2 = 5;
int motorSpeedControlLeft = 9;
int motorSpeedControlRight = 10;
char appCommand;

void carBackward(){ //makes all 4 wheels go backwards at max speed
  //Controlling speed (0 = off and 255 = max speed):     
  analogWrite(motorSpeedControlLeft, 255); //ENA pin
  analogWrite(motorSpeedControlRight, 255); //ENB pin
  //turning on motors
  digitalWrite(leftSideMotors1, HIGH);
  digitalWrite(leftSideMotors2, LOW);
  digitalWrite(rightSideMotors1, LOW);
  digitalWrite(rightSideMotors2, HIGH);
}

void carForward(){ //makes all 4 wheels go forwards at max speed
  //Controlling speed (0 = off and 255 = max speed):     
  analogWrite(motorSpeedControlLeft, 255); //ENA pin
  analogWrite(motorSpeedControlRight, 255); //ENB pin
  //turning on motors
  digitalWrite(leftSideMotors1, LOW);
  digitalWrite(leftSideMotors2, HIGH);
  digitalWrite(rightSideMotors1, HIGH);
  digitalWrite(rightSideMotors2, LOW);
}

void carLeft(){
  pwm.setPWM(0, 0, 372 );
}

void carRight(){
  pwm.setPWM(0, 0, 148 );
}

void carStraight(){
  pwm.setPWM(0, 0, 260 );
}

void carStop(){ //turns off all motors
  digitalWrite(rightSideMotors1, LOW);
  digitalWrite(rightSideMotors2, LOW);
  digitalWrite(leftSideMotors1, LOW);
  digitalWrite(leftSideMotors2, LOW);
  pwm.setPWM(0, 0, 260 );
}

void setup() {
  //myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600); // Serial communication with Serial Monitor
  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
  //yield();
  pinMode(leftSideMotors1, OUTPUT);
  pinMode(leftSideMotors2, OUTPUT);
  pinMode(rightSideMotors1, OUTPUT);
  pinMode(rightSideMotors2, OUTPUT);
  pinMode(motorSpeedControlLeft, OUTPUT); 
  pinMode(motorSpeedControlRight, OUTPUT);
}

void loop() {
  if(Serial.available()){ 
    appCommand = Serial.read();
  }
  if(appCommand == 'F'){ //move forward         
  carStraight();
  carForward();
  }
  if(appCommand == 'FL'){ //move forward         
  carLeft();
  carForward();
  }
  if(appCommand == 'FR'){ //move forward         
  carRight();
  carForward();
  }
  if(appCommand == 'B'){ //move backward          
  carStraight();
  carBackward();
  }
  if(appCommand == 'BL'){ //move forward         
  carLeft();
  carBackward();
  }
  if(appCommand == 'BR'){ //move forward         
  carRight();
  carBackward();
  }
  if(appCommand == 'L'){ //move left
  carLeft();
  }
  if(appCommand == 'R'){ //move right   
  carRight();
  }
  if(appCommand == 'S'){ // stop!!          
  carStop();
  }
}