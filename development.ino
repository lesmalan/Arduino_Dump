//Add servo library and initialize servo object
#include <Servo.h>
Servo myservo;

//Define constants
#define dirPin 2
#define stepPin 3
#define laserOutputPin 4
#define stepperM0 5
#define stepperM1 6
#define stepperM2 7
#define servoPin 8

//Define global position variable for servo
int servoPosition=0;

//Define char variable to receive commands from Bluetooth
char appCommand;

//Function to move elevation up by moving servo position
void elevationUp(int localPos){
  Serial.println("Executing elevation up");
  localPos+=5;
  myservo.write(localPos);
  servoPosition=localPos;
  Serial.print("Servo Position= ");
  Serial.println(servoPosition);
  delay(10);
}

//Function to move elevation up by moving servo position
void elevationDown(int localPos){
  Serial.println("Executing elevation down");
  localPos-=5;
  myservo.write(localPos);
  servoPosition=localPos;
  Serial.print("Servo Position= ");
  Serial.println(servoPosition);
  delay(10);
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(laserOutputPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
    if(Serial.available()){ 
    //Serial.println("Serial Available.");
    appCommand = Serial.read();
    Serial.println(appCommand);
  }
    switch (appCommand){
        case 'U':
        Serial.println("Case Received: U");
        elevationUp(servoPosition);
        Serial.println("Command received: UP");
            
        break;

        case 'D':
        Serial.println("Case Received: D");
        elevationDown(servoPosition);
        Serial.println("Command received: DOWN");

        break;

        case 'L':
        Serial.println("Case Received: L");
        //azimuthLeft();
        Serial.println("Command received: LEFT");

        break;

        case 'R':
        Serial.println("Case Received: R");
        //azimuthRight();
        Serial.println("Command received: RIGHT");

        break;

        case 'S':
        Serial.println("Case Received: S");
        //stopAll();
        Serial.println("Command received: STOP");

        default:
        Serial.println("Executing default case");
        myservo.write(10);
        delay(15);
        myservo.write(-10);
        delay(15);

  }
}
