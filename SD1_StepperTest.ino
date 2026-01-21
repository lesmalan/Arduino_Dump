//Add servo library and initialize servo object
#include <Adafruit_MotorShield.h>
#include <stdio.h>
#include <Servo.h>

//Define constants
#define laserOutputPin 2
int stepperAbsolutePosition = 0;
int stepperInput = 0;
float servoInput = 90;
float servoAbsPos=40;
int modeSelection;


/* Variables for photo resistor*/
int voltage_pin = A0;
int photo_resistor = 0;

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61);

// Connect a stepper motor with 200 steps per revolution (1.8 degree)
// to motor port #2 (M3 and M4)
Adafruit_StepperMotor *myStepper = AFMS.getStepper(200, 1);

Servo myServo;
//_________________________________________________________________________________
// Function Definitions

void elevationDown(double angle){
  noInterrupts();
  myServo.write(angle);
  delay(3000);
  interrupts();
}

void elevationUp(float angle){
  noInterrupts();
  myServo.write(angle);
  delay(3000);
  interrupts();
}


void azimuthRight(int steps){
 
  for(int i=0; i < steps; i++){
  myStepper->onestep(FORWARD, MICROSTEP);
  Serial.println(i);
  delay(200);
  }
  
}

void azimuthLeft(int steps){

  for(int i=0; i < steps; i++){
  myStepper->onestep(BACKWARD, MICROSTEP);
  Serial.println(steps-i);
  delay(200);
  }

}


void pr_data(){
    photo_resistor = analogRead(voltage_pin); //Reads the value of voltage_pin
    Serial.print(millis());
    Serial.print(",");
    Serial.println(photo_resistor);
    delay(50);
}

void receiveStepInt(){
  if (Serial.available()>0){
    stepperInput=Serial.read();
  }
}

void showNewData(){
  
}


//___________________________________________________________________________

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Arduino serial is ready.");

  /* Starts shield*/
  AFMS.begin(); 
  
  Serial.println("Motor Shield found.");
  myStepper->setSpeed(10);  // 10 rpm

  myServo.attach(10);
  //myServo.write(100);

  

  pinMode(laserOutputPin, OUTPUT); 
  digitalWrite(laserOutputPin, HIGH); //turn on laser
}
//___________________________________________________________________________

void loop() {

    modeSelection = 0; // reset mode



    //Prompt user for mode
    Serial.println("Mode Select Menu");
    Serial.println("1. Move Up");
    Serial.println("2. Move Down");
    Serial.println("3. Move Left");
    Serial.println("4. Move Right");
    Serial.print("Selection: ");
    Serial.println();
 
    while (Serial.available()==0){
      delay(1000);
    }
    modeSelection = Serial.parseInt();

    //Switch to mode
    switch(modeSelection){
      case 1:
      Serial.println("Mode 1 - moving up");
      Serial.print("Enter elevation degree: ");
      while (Serial.available()==0){
      }
      servoInput = Serial.parseFloat();
      elevationUp(servoAbsPos-servoInput);
      servoAbsPos=servoAbsPos-servoInput;
      break;

      case 2:
      Serial.println("Mode 2 - moving down");
      Serial.print("Enter elevation degree: ");
      while (Serial.available()==0){
      }
      servoInput = Serial.parseFloat();
      elevationDown(servoAbsPos+servoInput);
      servoAbsPos=servoAbsPos+servoInput;
      break;

      case 3:
      Serial.println("Mode 3 - moving left");
      Serial.print("Enter steps: ");
      receiveStepInt();
      azimuthLeft(stepperInput);
      break;

      case 4:
      Serial.println("Mode 4 - moving right");
      Serial.print("Enter steps: ");
      receiveStepInt();
      azimuthRight(stepperInput);
      break;
    }


  
  
  
  
  
  
  
  
  
  
  
  
  
  
  /*for(int i=0; i<15; i++){
    Serial.println("Stepper moving forwards.");
    myMotor->onestep(FORWARD, MICROSTEP);
    stepperAbsolutePosition++;
    Serial.print("Stepper position: ");
    Serial.println(stepperAbsolutePosition);
    delay(200);  
  }
  Serial.println("1 second delay.");
  delay(1000);

  for(int i=0; i<15; i++){
    Serial.println("Stepper moving backwards.");
    myMotor->onestep(BACKWARD, MICROSTEP);
    stepperAbsolutePosition--;
    Serial.print("Stepper position: ");
    Serial.println(stepperAbsolutePosition);
    delay(200);  
  }
  Serial.println("1 second delay.");
  delay(1000);*/

}
//_______