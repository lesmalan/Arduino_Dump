//Add servo library and initialize servo object
#include <Adafruit_MotorShield.h>
#include <stdio.h>

//Define constants
#define laserOutputPin 2

/* Variables for photo resistor*/
int voltage_pin = A0;
//int RSL = 0;
const int arraySize=150;

float azimuthRSLArray[arraySize]={0}; //init azimuth array with all zeros
float elevationRSLArray[arraySize]={0}; //init elevation array with all zeros
float azimuthRSLIncrease=0;
float elevationRSLIncrease=0;

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61);
Adafruit_StepperMotor *aziStepper = AFMS.getStepper(200, 1);
Adafruit_StepperMotor *elevStepper = AFMS.getStepper(200, 2);

//set initial RSL values for comparison
float initAzimuthValue=analogRead(voltage_pin);
float initElevationValue=analogRead(voltage_pin);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  /* Starts shield*/
  AFMS.begin(); 
  //set speed
  aziStepper->setSpeed(10);
  elevStepper->setSpeed(10);

  //set initial RSL values for comparison
  float initAzimuthValue=analogRead(voltage_pin);
  float initElevationValue=analogRead(voltage_pin);

  //set modes
  pinMode(laserOutputPin, OUTPUT); 
  digitalWrite(laserOutputPin, HIGH); //turn on laser
}
//___________________________________________________________________________

void loop() {


  //azimuth sweep to load array with RSL values
  for (int i=0; i<(arraySize); i++){
    aziStepper->onestep(BACKWARD, MICROSTEP);
    azimuthRSLArray[i]=analogRead(voltage_pin);
    delay(100);
  }

  //for loop to calculate index position of largest RSL from the array
  int maxAzimuthIndex = 0;         // start assuming first element is the largest
  int maxAzimuthValue = azimuthRSLArray[0];

  for(int i = 0; i < arraySize; i++) { // start from 1 since 0 is already assumed
    if(azimuthRSLArray[i] >= maxAzimuthValue) {
      maxAzimuthValue = azimuthRSLArray[i]; // update max value
      maxAzimuthIndex = i;          // update index
    }
  }

  azimuthRSLIncrease=maxAzimuthValue-initAzimuthValue;

  Serial.print("Maximum azimuthal RSL = ");
  Serial.print(maxAzimuthValue);
  Serial.print(" at step number ");
  Serial.println(maxAzimuthIndex);

  //return stepper to highest RSL index
  Serial.println("Returning to max step.");
  for (int i=0; i<(arraySize-maxAzimuthValue); i++){
    aziStepper->onestep(FORWARD, MICROSTEP);
    delay(100);
  }

  Serial.print("Azimuth RSL Increase= ");
  Serial.println(azimuthRSLIncrease);

//___________________________________________________________________________________________
    //elevation sweep to load array with RSL values
  for (int i=0; i<arraySize; i++){
    elevStepper->onestep(BACKWARD, MICROSTEP);
    elevationRSLArray[i]=analogRead(voltage_pin);
    delay(100);
  }

  //for loop to calculate index position of largest RSL from the array
  int maxElevationIndex = 0;         // start assuming first element is the largest
  int maxElevationValue = elevationRSLArray[0];

  for(int i = 1; i < arraySize; i++) { // start from 1 since 0 is already assumed
    if(elevationRSLArray[i] >= maxElevationValue) {
      maxElevationValue = elevationRSLArray[i]; // update max value
      maxElevationIndex = i;          // update index
    }
  }

  elevationRSLIncrease=maxElevationValue-initElevationValue;

  Serial.print("Maximum elevation RSL= ");
  Serial.print(maxElevationValue);
  Serial.print(" at step number ");
  Serial.println(maxElevationIndex);


  //return stepper to highest RSL index
  Serial.println("Returning to max step.");
  for (int i=0; i<(arraySize-maxElevationValue); i++){
    elevStepper->onestep(FORWARD, MICROSTEP);
    delay(100);
  }

  Serial.print("Maximum elevation RSL= ");
  Serial.println(maxElevationValue);
  Serial.print("Elevation RSL Increase= ");
  Serial.println(elevationRSLIncrease);
  Serial.print("Maximum azimuth RSL= ");
  Serial.println(maxAzimuthValue);
  Serial.print("Azimuth RSL Increase= ");
  Serial.println(azimuthRSLIncrease);

//__________________________________________________________________
  while(1) {
    // Do nothing, infinite loop
  }
}