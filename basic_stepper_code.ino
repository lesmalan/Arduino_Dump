/* Example sketch to control a stepper motor with 
   A4988/DRV8825 stepper motor driver and 
   Arduino without a library. 
   More info: https://www.makerguides.com */

// Define stepper motor connections and steps per revolution:
#define dirPin 2
#define stepPin 3
#define stepsPerRevolution 200
#define laserOutputPin 4

void setup() {
  // initialize serial
  Serial.begin(9600);
  pinMode(laserOutputPin, OUTPUT); 


  // Declare pins as output:
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
}

void loop() {
  digitalWrite(laserOutputPin, HIGH);
  double revs=0;
  int speed=0;
  // Set the spinning direction clockwise:
  digitalWrite(dirPin, HIGH);

  // Spin the stepper motor 0.25 revolution slowly:
  revs=0.005;
  speed=80000;
  Serial.println("Spin the stepper motor 1 revolution slowly CW.");
  Serial.print("Revs: ");
  Serial.print(revs);
  Serial.print("- Dir: ");
  Serial.print(dirPin);
  Serial.print("- Speed: ");
  Serial.println(speed);
  Serial.println("2s delay...");
  delay(2000);
  for (int i = 0; i < revs * stepsPerRevolution; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(speed);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(speed);
  }

  delay(1000);

  // Set the spinning direction counterclockwise:
  digitalWrite(dirPin, LOW);

  // Spin the stepper motor 1 revolution quickly:
  Serial.println("Spin the stepper motor 1 revolution slowly CCW.");
  revs=0.005;
  //speed=500;
  Serial.print("Revs: ");
  Serial.print(revs);
  Serial.print("- Dir: ");
  Serial.print(dirPin);
  Serial.print("- Speed: ");
  Serial.println(speed);
  Serial.println("2s delay...");
  delay(2000);
  for (int i = 0; i < revs * stepsPerRevolution; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(speed);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(speed);
  }

  delay(1000);

}