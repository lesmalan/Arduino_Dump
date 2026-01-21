//Add servo library and initialize servo object
#include <Adafruit_MotorShield.h>
#include <stdio.h>
#include <Servo.h>



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


          // Perform any processing or actions based on the sensor data
        }


    potentiometerValE = analogRead(potPinE);
    potentiometerValA= analogRead(potPinA);

    if(potentiometerValE < 410){
    elevStepper->onestep(BACKWARD, MICROSTEP);
    delay(200);
    }else if(potentiometerValE > 560){
    elevStepper->onestep(FORWARD, MICROSTEP);
    delay(200);
    }

    if(potentiometerValA < 410){
    aziStepper->onestep(BACKWARD, MICROSTEP);
    delay(200);
    }else if(potentiometerValA > 560){
    aziStepper->onestep(FORWARD, MICROSTEP);
    delay(200);
    }
   

}