//Add servo library and initialize servo object
#include <Adafruit_MotorShield.h>
#include <stdio.h>

//Define constants
#define laserOutputPin 2
int aziStepPos = 0; //global variable to track azimuthal position of stepper
int elevStepPos = 0; //global variable to track elevation position of stepper
int aziStepInput = 0;
int elevStepInput = 0;
int modeSelection;
int speedSelection;
int RSL=0;

unsigned long previousMillis = 0; // Stores the last time a reading was taken
const long interval = 100;       // Interval at which to read sensor data (e.g., 100ms)

/* Variables for photo resistor*/
int voltage_pin = A0;
int photo_resistor = 0;

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61);

// Connect a stepper motor with 200 steps per revolution (1.8 degree)
// to motor port #2 (M3 and M4)
Adafruit_StepperMotor *aziStepper = AFMS.getStepper(200, 1);
Adafruit_StepperMotor *elevStepper = AFMS.getStepper(200, 2);


//_________________________________________________________________________________
// Function Definitions
void elevationUp(int steps){
  for(int i=0; i < steps; i++){
  elevStepper->onestep(BACKWARD, MICROSTEP);
  Serial.println(i);
  delay(200);
  }
}

void elevationDown(int steps){
  for(int i=0; i < steps; i++){
  elevStepper->onestep(FORWARD, MICROSTEP);
  Serial.println(steps-i);
  delay(200);
  }
}

void azimuthRight(int steps){
  for(int i=0; i < steps; i++){
  aziStepper->onestep(FORWARD, MICROSTEP);
  Serial.println(i);
  delay(200);
  }
}

void azimuthLeft(int steps){
  for(int i=0; i < steps; i++){
  aziStepper->onestep(BACKWARD, MICROSTEP);
  Serial.println(steps-i);
  delay(200);
  }
}

void elevationUpFast(int steps){
  for(int i=0; i < steps; i++){
  elevStepper->step(5, BACKWARD, DOUBLE);
  Serial.println(i);
  delay(200);
  }
}

void elevationDownFast(int steps){
  for(int i=0; i < steps; i++){
  elevStepper->step(5, FORWARD, DOUBLE);
  Serial.println(steps-i);
  delay(200);
  }
}

void azimuthLeftFast(int steps){
  for(int i=0; i < steps; i++){
  aziStepper->step(5, BACKWARD, DOUBLE);
  Serial.println(steps-i);
  delay(200);
  }
}

void azimuthRightFast(int steps){
  for(int i=0; i < steps; i++){
  aziStepper->step(5, FORWARD, DOUBLE);
  Serial.println(steps-i);
  delay(200);
  }
}

void releaseMotors(){
  elevStepper->release();
  aziStepper->release();
}

void serialPrintMenu(){
  //Prompt user for mode
  Serial.println("Mode Select Menu");
  Serial.println("1. Move Up");
  Serial.println("2. Move Down");
  Serial.println("3. Move Left");
  Serial.println("4. Move Right"); 
  Serial.println("5. Move Up Fast"); 
  Serial.println("6. Move Down Fast"); 
  Serial.println("7. Move Left Fast"); 
  Serial.println("8. Move Right Fast");
  Serial.println("9. Release motors");
  Serial.print("Selection: ");
  Serial.println();
}
void serialPrintMovingUp(){
  Serial.println("Mode 1 - moving up");
  Serial.print("Enter elevation steps: ");
}

void serialPrintMovingDown(){
  Serial.println("Mode 2 - moving down");
  Serial.print("Enter elevation steps: ");
}

void serialPrintMovingLeft(){
  Serial.println("Mode 3 - moving left");
  Serial.print("Enter azimuth steps: ");
}

void serialPrintMovingRight(){
  Serial.println("Mode 4 - moving right");
  Serial.print("Enter azimuth steps: ");
}

void serialPrintMovingUpFast(){
  Serial.println("Mode 5 - moving up fast");
  Serial.print("Enter elevation steps: ");
}

void serialPrintMovingDownFast(){
  Serial.println("Mode 6 - moving down fast");
  Serial.print("Enter elevation steps: ");
}

void serialPrintMovingLeftFast(){
  Serial.println("Mode 7 - moving left fast");
  Serial.print("Enter azimuth steps: ");
}

void serialPrintMovingRightFast(){
  Serial.println("Mode 8 - moving right fast");
  Serial.print("Enter azimuth steps: ");
}

void serialPrintRelease(){
  Serial.println("Mode 9 - releasing motors");
}

int getUserInt(){
  int returnInt=0;
  while (Serial.available()==0){
    returnInt = Serial.parseFloat();
    }
  return returnInt;
}

void getMenuInput(){
  modeSelection = getUserInt();
}

void getElevationInput(){
  elevStepInput = getUserInt();
}

void getAzimuthInput(){
  aziStepInput = getUserInt();
}

void pr_data(){
  photo_resistor = analogRead(voltage_pin); //Reads the value of voltage_pin
  Serial.print(millis());
  Serial.print(",");
  Serial.println(photo_resistor);
  delay(50);
}
//___________________________________________________________________________

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  /* Starts shield*/
  AFMS.begin(); 
  
  Serial.println("Motor Shield found.");
  aziStepper->setSpeed(10);
  elevStepper->setSpeed(10);

  pinMode(laserOutputPin, OUTPUT); 
  digitalWrite(laserOutputPin, HIGH); //turn on laser
}
//___________________________________________________________________________

void loop() {
    modeSelection = 0; // reset mode to main menu

    /*unsigned long currentMillis = millis();
      if (currentMillis - previousMillis >= interval) {
          // Save the last time you made a reading
          previousMillis = currentMillis;

          // Read sensor data here
          RSL = analogRead(voltage_pin); 
          Serial.println(RSL);
        }*/

    serialPrintMenu(); //just prints out menu selections to the serial console
    //getMenuInput(); // runs a command to get an integer from the user that specifies the case
    while (Serial.available()==0){
    }
    modeSelection = Serial.parseInt();

    //Switch to mode
    switch(modeSelection){
      case 1:
      serialPrintMovingUp(); //print statement
      //getElevationInput();
      while (Serial.available()==0){ // this ungainly code gets an integer from user, i hate it
      }
      elevStepInput = Serial.parseFloat();
      elevationUp(elevStepInput); //moves elevation up
      break;

      case 2:
      serialPrintMovingDown();
      //getElevationInput();
      while (Serial.available()==0){
      }
      elevStepInput = Serial.parseFloat();
      elevationDown(elevStepInput);
      break;

      case 3:
      serialPrintMovingLeft();
      //getAzimuthInput();
      while (Serial.available()==0){
      }
      aziStepInput = Serial.parseFloat();
      azimuthLeft(aziStepInput);
      break;

      case 4:
      serialPrintMovingRight();
      //getAzimuthInput();
      while (Serial.available()==0){
      }
      aziStepInput = Serial.parseFloat();
      azimuthRight(aziStepInput);
      break;

      case 5:
      serialPrintMovingUpFast(); //print statement
      //getElevationInput();
      while (Serial.available()==0){ // this ungainly code gets an integer from user, i hate it
      }
      elevStepInput = Serial.parseFloat();
      elevationUpFast(elevStepInput); //moves elevation up
      break;

      case 6:
      serialPrintMovingDownFast(); //print statement
      //getElevationInput();
      while (Serial.available()==0){ // this ungainly code gets an integer from user, i hate it
      }
      elevStepInput = Serial.parseFloat();
      elevationDownFast(elevStepInput); //moves elevation up
      break;

      case 7:
      serialPrintMovingLeftFast(); //print statement
      //getElevationInput();
      while (Serial.available()==0){ // this ungainly code gets an integer from user, i hate it
      }
      aziStepInput = Serial.parseFloat();
      azimuthLeftFast(aziStepInput); //moves elevation up
      break;

      case 8:
      serialPrintMovingRightFast(); //print statement
      //getElevationInput();
      while (Serial.available()==0){ // this ungainly code gets an integer from user, i hate it
      }
      aziStepInput = Serial.parseFloat();
      azimuthRightFast(aziStepInput); //moves elevation up
      break;

      case 9:
      serialPrintRelease();
      releaseMotors();
      break;
    } 
}
