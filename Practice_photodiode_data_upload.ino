/* Servo Libraries*/
/*
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include "utility/Adafruit_PWMServoDriver.h"
#include <Servo.h>
*/


/* Motor Sheild object*/
//Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

/*Stepper Motor Object*/
/*getStepper(steps,stepper#)*/
//Adafruit_StepperMotor *myMotor = AFMS.getStepper(200, 2);


/* Servo motor */

/* Sensor variables*/
int voltage_pin = A0;
int photo_resistor = 0;

void setup() {
  /* Adafruit Motor Sheild object*/
 // AFMS.begin(); 



  Serial.begin(9600);

}

void loop() {

  /*Turns on Lazer*/
  
  /*Photo Resistor Data Extraction*/
  photo_resistor = analogRead(voltage_pin); //Reads the value of voltage_pin
  Serial.print(millis());
  Serial.print(",");
  Serial.println(photo_resistor);
  delay(50);

  
}
