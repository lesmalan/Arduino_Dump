//Add servo library and initialize servo object
#include <Adafruit_MotorShield.h>
#include <stdio.h>
#include <Servo.h>

//Define constants
#define laserOutputPin 2
int stepperAbsolutePosition = 0;
int AzimuthStepperInput = 0;
float servoInput = 90;
float servoAbsPos = 130;
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

/*void elevationDown(double angle){
  noInterrupts();
  myServo.write(angle);
  servoAbsPos=servoAbsPos+servoInput;
  Serial.print("Servo angle is ");
  Serial.print(servoAbsPos);
  Serial.println(" degrees.");
  //delay(3000);
  interrupts();
}*/

void elevationUp(float angle){
  if (servoAbsPos-servoInput>=0){ //check if minimum angle is exceeded
    noInterrupts(); //stop interrupts
    for (int i=servoAbsPos; i>=servoAbsPos-servoInput; i=i-0.5){ //move up in increments of 0.5
      myServo.write(i);
      delay(30);
    }
    interrupts(); //resume intterupts
    servoAbsPos=servoAbsPos-servoInput; //update servo absolute position
    Serial.print("Servo angle is "); //display servo position
    Serial.print(servoAbsPos);
    Serial.println(" degrees.");
  }
  else if(servoAbsPos-servoInput<0){ //if minimum range is exceeded, display error and restore servo absolute position.
    Serial.println("Servo angle minimum range exceeded!!");
    Serial.print("Servo angle is still ");
    Serial.print(servoAbsPos);
    Serial.println(" degrees.");
  }
}

void elevationDown(float angle){
  if (servoAbsPos+servoInput<=130){ //check if maximum angle is exceeded
    noInterrupts(); //stop interrupts
    for (int i=servoAbsPos; i<=servoAbsPos+servoInput; i=i+0.5){ //move up in increments of 0.5
      myServo.write(i);
      delay(30);
    }
    interrupts(); //resume intterupts
    servoAbsPos=servoAbsPos+servoInput; //update servo absolute position
    Serial.print("Servo angle is "); //display servo position
    Serial.print(servoAbsPos);
    Serial.println(" degrees.");
  }
  else if(servoAbsPos+servoInput>130){ //if maximum range is exceeded, display error and restore servo absolute position.
    Serial.println("Servo angle maximum range exceeded!!");
    Serial.print("Servo angle is still ");
    Serial.print(servoAbsPos);
    Serial.println(" degrees.");
    }
}


void azimuthRightSlow(int steps){
 
  for(int i=0; i < steps; i++){
  myStepper->onestep(FORWARD, MICROSTEP);
  Serial.println(i);
  delay(200);
  }
  
}

void azimuthLeftSlow(int steps){
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


//___________________________________________________________________________

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  /* Starts shield*/
  AFMS.begin(); 
  
  Serial.println("Motor Shield found.");
  myStepper->setSpeed(10);  // 10 rpm

  myServo.attach(10);
  myServo.write(130);
  Serial.print("Servo angle is ");
  Serial.print(servoAbsPos);
  Serial.println(" degrees.");


  

  pinMode(laserOutputPin, OUTPUT); 
  digitalWrite(laserOutputPin, HIGH); //turn on laser
}
//___________________________________________________________________________

void loop() {
    modeSelection = 0; // reset mode to main menu

    //Prompt user for mode
    Serial.println("Mode Select Menu");
    Serial.println("1. Move Up");
    Serial.println("2. Move Down");
    Serial.println("3. Move Left Slowly");
    Serial.println("4. Move Right Slowly");    
    Serial.print("Selection: ");
    Serial.println();
 
    //get input from user
    while (Serial.available()==0){
    //delay(1000);
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
      break;

      case 2:
      Serial.println("Mode 2 - moving down");
      Serial.print("Enter elevation degree: ");
      while (Serial.available()==0){
      }
      servoInput = Serial.parseFloat();
      elevationDown(servoAbsPos+servoInput);
      break;

      case 3:
      Serial.println("Mode 3 - moving left slowly");
      Serial.print("Enter steps: ");
      //delay(10000);
      //Serial.println();
      while (Serial.available()==0){
      //delay(10000);
      }
      stepperInput = Serial.parseInt();
      azimuthLeftSlow(stepperInput);
      break;

      case 4:
      Serial.println("Mode 4 - moving right slowly");
      Serial.print("Enter steps: ");
      while (Serial.available()==0){
      //delay(000);
      }
      stepperInput = Serial.parseInt();
      azimuthRightSlow(stepperInput);
      break;

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
}
//_______