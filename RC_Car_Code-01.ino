int leftSideMotors1 = 2;
int leftSideMotors2 = 3;

int rightSideMotors1 = 4;
int rightSideMotors2 = 5;

int motorSpeedControl1 = 9;
int motorSpeedControl2 = 10;

void carBackward(int time){ //makes all 4 wheels go backwards
  digitalWrite(leftSideMotors1, HIGH);
  digitalWrite(leftSideMotors2, LOW);
  digitalWrite(rightSideMotors1, LOW);
  digitalWrite(rightSideMotors2, HIGH);
  delay(time);
}

void carForward(int time){ //makes all 4 wheels go forwards
  digitalWrite(leftSideMotors1, LOW);
  digitalWrite(leftSideMotors2, HIGH);
  digitalWrite(rightSideMotors1, HIGH);
  digitalWrite(rightSideMotors2, LOW);
  delay(time);
}

void carLeft(int time){ //makes the left side wheels go backwwards, and the right side wheels go forwards to make a zero radius turn
  digitalWrite(leftSideMotors1, HIGH);
  digitalWrite(leftSideMotors2, LOW);
  digitalWrite(rightSideMotors1, HIGH);
  digitalWrite(rightSideMotors2, LOW);
  delay(time);
}

void carRight(int time){//makes the right side wheels go backwwards, and the left side wheels go forwards to make a zero radius turn
  digitalWrite(rightSideMotors1, LOW);
  digitalWrite(rightSideMotors2, HIGH);
  digitalWrite(leftSideMotors1, LOW);
  digitalWrite(leftSideMotors2, HIGH);
  delay(time);
}

void carStop(int time){
  digitalWrite(rightSideMotors1, LOW);
  digitalWrite(rightSideMotors2, LOW);
  digitalWrite(leftSideMotors1, LOW);
  digitalWrite(leftSideMotors2, LOW);
  delay(time);
 
}

void setup() {
  // put your setup code here, to run once:
  pinMode(leftSideMotors1, OUTPUT);
  pinMode(leftSideMotors2, OUTPUT);
  pinMode(rightSideMotors1, OUTPUT);
  pinMode(rightSideMotors2, OUTPUT);


  pinMode(motorSpeedControl1, OUTPUT); 
  pinMode(motorSpeedControl2, OUTPUT);
  
    //Controlling speed (0 = off and 255 = max speed):     
  analogWrite(motorSpeedControl1, 255); //ENA pin
  analogWrite(motorSpeedControl2, 255); //ENB pin
}

void loop() {
  // put your main code here, to run repeatedly:
  carForward(3000);
  carBackward(3000);
  carRight(1000);
  carLeft(1000);
  carStop(1000);

}
