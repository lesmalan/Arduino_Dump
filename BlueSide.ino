//Add servo library and initialize servo object
#include <Adafruit_MotorShield.h>
#include <stdio.h>



//Define constants
#define laserOutputPin 2
int stepperAbsolutePosition = 0;
int modeSelection;


/* Variables for photo resistor*/
int voltage_pin = A0;
int RSL = 0;


int potPinE = A1;
int potPinA = A2;
int potentiometerValE;
int potentiometerValA;
int elevSpeedMode=0;
int aziSpeedMode=0;

unsigned long previousMillis = 0; // Stores the last time a reading was taken
const long interval = 100;       // Interval at which to read sensor data (e.g., 100ms)




Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61);
Adafruit_StepperMotor *aziStepper = AFMS.getStepper(200, 1);
Adafruit_StepperMotor *elevStepper = AFMS.getStepper(200, 2);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  /* Starts shield*/
  AFMS.begin(); 
  
  aziStepper->setSpeed(10);
  elevStepper->setSpeed(10);


  pinMode(laserOutputPin, OUTPUT); 
  digitalWrite(laserOutputPin, HIGH); //turn on laser


}
//___________________________________________________________________________

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // Save the last time you made a reading
    previousMillis = currentMillis;

    // Read sensor data here
    RSL = analogRead(voltage_pin); 
    Serial.println(RSL);
  }

  potentiometerValE = analogRead(potPinE);
  potentiometerValA= analogRead(potPinA);
//___________________________________________________________________
  //elevator control
  if(potentiometerValE<400 && potentiometerValE>=200){
    elevStepper->onestep(BACKWARD, MICROSTEP);
    delay(200);
  }

  else if(potentiometerValE<200){
    elevStepper->step(2, BACKWARD, DOUBLE);
    delay(200);
  }

  else if(potentiometerValE>600 && potentiometerValE<=800){
    elevStepper->onestep(FORWARD, MICROSTEP);
    delay(200);     
  }

  else if(potentiometerValE>800){
    elevStepper->step(2, FORWARD, DOUBLE);
    delay(200);
  }
//______________________________________________________________
  //azimuth control
  if(potentiometerValA<400 && potentiometerValA>=200){
    aziStepper->onestep(BACKWARD, MICROSTEP);
    delay(200);
  }

  else if(potentiometerValA<200){
    aziStepper->step(2, BACKWARD, DOUBLE);
    delay(200);
  }

  else if(potentiometerValA>600 && potentiometerValA<=800){
    aziStepper->onestep(FORWARD, MICROSTEP);
    delay(200);     
  }

  else if(potentiometerValA>800){
    aziStepper->step(2, FORWARD, DOUBLE);
    delay(200);
  }

  /*switch(elevSpeedMode){
    case 1:
      elevStepper->onestep(BACKWARD, MICROSTEP);
      delay(200);
      break;

    case 2:
      elevStepper->step(5, BACKWARD, DOUBLE);
      delay(200);
      break;

    case 3:
      elevStepper->onestep(FORWARD, MICROSTEP);
      delay(200);
      break;

    case 4:
      elevStepper->step(5, FORWARD, DOUBLE);
      delay(200);
      break;
  }

  /*if(potentiometerValE <400){
  elevStepper->onestep(BACKWARD, MICROSTEP);
  delay(200);
  }else if(potentiometerValE > 600){
  elevStepper->onestep(FORWARD, MICROSTEP);
  delay(200);
  }

  if(potentiometerValA < 410){
  aziStepper->onestep(BACKWARD, MICROSTEP);
  delay(200);
  }else if(potentiometerValA > 560){
  aziStepper->onestep(FORWARD, MICROSTEP);
  delay(200);
  }*/
}
   


//_______