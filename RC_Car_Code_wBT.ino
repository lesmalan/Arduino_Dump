/*
by Les Malan
copyright 2023

RC Car control program for Arduino Uno


*/ 
//sets variables 
int leftSideMotors1 = 2;
int leftSideMotors2 = 3;
int rightSideMotors1 = 4;
int rightSideMotors2 = 5;
int motorSpeedControlLeft = 9;
int motorSpeedControlRight = 10;

char appCommand;

void carBackward(){ //makes all 4 wheels go backwards at max speed
  //Controlling speed (0 = off and 255 = max speed):     
  analogWrite(motorSpeedControlLeft, 255); //ENA pin
  analogWrite(motorSpeedControlRight, 255); //ENB pin
  //turning on motors
  digitalWrite(leftSideMotors1, HIGH);
  digitalWrite(leftSideMotors2, LOW);
  digitalWrite(rightSideMotors1, LOW);
  digitalWrite(rightSideMotors2, HIGH);
}


void carForward(){ //makes all 4 wheels go forwards at max speed
  //Controlling speed (0 = off and 255 = max speed):     
  analogWrite(motorSpeedControlLeft, 255); //ENA pin
  analogWrite(motorSpeedControlRight, 255); //ENB pin
  //turning on motors
  digitalWrite(leftSideMotors1, LOW);
  digitalWrite(leftSideMotors2, HIGH);
  digitalWrite(rightSideMotors1, HIGH);
  digitalWrite(rightSideMotors2, LOW);
}

void carLeft(){ //makes the left side wheels go slow, and the right side wheels go fast to make a left turn
  //Controlling speed (0 = off and 255 = max speed):     
  analogWrite(motorSpeedControlLeft, 100); //ENA pin
  analogWrite(motorSpeedControlRight, 255); //ENB pin
  //turning on motors
  digitalWrite(leftSideMotors1, LOW);
  digitalWrite(leftSideMotors2, HIGH);
  digitalWrite(rightSideMotors1, HIGH);
  digitalWrite(rightSideMotors2, LOW);
}

void carRight(){//makes the right side wheels go slow, and the left side wheels go fast to make a right turn
   //Controlling speed (0 = off and 255 = max speed):     
  analogWrite(motorSpeedControlLeft, 255); //ENA pin
  analogWrite(motorSpeedControlRight, 100); //ENB pin
  //turning on motors
  digitalWrite(leftSideMotors1, LOW);
  digitalWrite(leftSideMotors2, HIGH);
  digitalWrite(rightSideMotors1, HIGH);
  digitalWrite(rightSideMotors2, LOW);
}

void carStop(){ //turns off all motors
  digitalWrite(rightSideMotors1, LOW);
  digitalWrite(rightSideMotors2, LOW);
  digitalWrite(leftSideMotors1, LOW);
  digitalWrite(leftSideMotors2, LOW);

}

void setup() {
  // put your setup code here, to run once:
  // sets pins to output mode
  pinMode(leftSideMotors1, OUTPUT);
  pinMode(leftSideMotors2, OUTPUT);
  pinMode(rightSideMotors1, OUTPUT);
  pinMode(rightSideMotors2, OUTPUT);
  pinMode(motorSpeedControlLeft, OUTPUT); 
  pinMode(motorSpeedControlRight, OUTPUT);

  //needed for HC-06 bluetooth module
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

  //this checks to make sure that it has a serial connection of some kind. If the PC is plugged into the USB on the Uno, you can send commands straight from the serial monitor. Or if the HC-05 bluetooth module
  //is connected to the TX/RX ports on the Uno, you can send the commands from that. This code sets the value of a character variable called "appCommand" to whatever it reads from serial. I used an Android app called 
  // Bluetooth Electronics (from the app store) to create a custom control scheme for the car. It's just a simple d-pad that sends one of the following characters to the device: F = forward, B = backward, L = left, R = right
  // S = stop. appCommand gets set to the value of whatever character I send, then then if statements calls one of the predefined functions. Works great.
  if(Serial.available()){ 
    appCommand = Serial.read();

  }
  if(appCommand == 'F'){ //move forward         
  carForward();
  }
  if(appCommand == 'B'){ //move backward          
  carBackward();
  }
  if(appCommand == 'L'){ //move left
  carLeft();
  }
  if(appCommand == 'R'){ //move right   
  carRight();
  }
  if(appCommand == 'S'){ // stop!!          
  carStop();
  }

}
