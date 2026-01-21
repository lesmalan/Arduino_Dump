#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
#define SERVOMIN  125 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  575 // this is the 'maximum' pulse length count (out of 4096)

int servoInt = 0; //initialize int to send to servo
String receivedData=""; //initialize empty string to receive data from serial via BT

// our servo # counter
uint8_t servonum = 0;

void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
  yield();
}

// the code inside loop() has been updated by Robojax
void loop() {

if (Serial.available() > 0) {
    // Read the incoming data as a string
    receivedData = Serial.readString();
    servoInt = receivedData.toInt();
    pwm.setPWM(0, 0, servoInt );
	  delay(15);
  }



/*
  pwm.setPWM(0, 0, 125 );
	delay(500);
  pwm.setPWM(0, 0, 350 );
	delay(500);
*/  

 
}