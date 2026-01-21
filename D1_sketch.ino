int motorPin = 8;
int result;
void setup() {
  // put your setup code here, to run once:
  pinMode(motorPin, INPUT);
  digitalWrite(motorPin, LOW);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  result=digitalRead(motorPin);
  if (result == HIGH){
    Serial.println("HIGH");
  }
  else {
    Serial.println("LOW");
  }
delay(100);
}
