// Code for blinking a laser module using Arduino
// Author: Oyvind N. Dahl
// Website: https://www.build-electronic-circuits.com/
const int laserOutputPin = 2;
const int receiverInputPin = 3;

void setup() {
  pinMode(laserOutputPin, OUTPUT); 
  pinMode(receiverInputPin, INPUT);
  Serial.begin(9600);

}

void loop() {
  digitalWrite(2, HIGH);

  int laserState=digitalRead(receiverInputPin);

  if (laserState==HIGH){
    Serial.println("Laser signal RECEIVED!");
  }

  else {
    Serial.println("No signal...");
  }

  delay(100);
}