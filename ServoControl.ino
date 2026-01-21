/*
by Les Malan
copyright 2025
Servo control program for Arduino Uno


*/ 

#include <Servo.h>

Servo myservo;  // create servo object to control a servo



void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
}

void loop() {
if (Serial.available() > 0) {
    // Read the incoming data as a string
    String receivedData = Serial.readString();

 // appCommand = map(appCommand, 0, 1023, 0, 90);     // scale it for use with the servo (value between 0 and 180)
  myservo.write(appCommand);                  // sets the servo position according to the scaled value
  delay(15);     
  
  appCommand = 90;      
  myservo.write(appCommand);                  // sets the servo position according to the scaled value
  delay(15);                 // waits for the servo to get there
}
